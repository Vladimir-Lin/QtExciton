#include <exciton.h>

N::OnePiecePictures:: OnePiecePictures ( QObject * parent , Plan * p )
                    : SiteSeeker       (           parent ,        p )
                    , opconf           ( NULL                        )
                    , removeImage      ( false                       )
{
  Enabled [ Types :: Picture ] = true  ;
}

N::OnePiecePictures::~OnePiecePictures (void)
{
}

int N::OnePiecePictures::Type(void) const
{
  return 20001 ;
}

QString N::OnePiecePictures::Name(void) const
{
  return tr("One Piece") ;
}

bool N::OnePiecePictures::Supported(int type) const
{
  return ( Types::Picture == type );
}

QString N::OnePiecePictures::Name(int type) const
{
  switch ( type )                  {
    case Types :: Picture          :
    return tr("FZDM - One Piece" ) ;
  }                                ;
  return ""                        ;
}

QWidget * N::OnePiecePictures::Configurator (int type)
{
  if (Widgets.contains(type)) return Widgets [ type ]   ;
  switch ( type )                                       {
    case Types :: Picture                               :
      opconf           = new OpPictures ( NULL , plan ) ;
      Widgets [ type ] = opconf                         ;
    return Widgets [ type ]                             ;
  }                                                     ;
  return NULL                                           ;
}

bool N::OnePiecePictures::setEnabled(int type,bool enable)
{
  switch ( type )               {
    case Types :: Picture       :
      Enabled [ type ] = enable ;
    return Enabled [ type ]     ;
  }                             ;
  return false                  ;
}

bool N::OnePiecePictures::prepare(void)
{
  CUIDs IDs                     ;
  int   id                      ;
  ///////////////////////////////
  IDs << Types :: Picture       ;
  ///////////////////////////////
  foreach ( id , IDs )          {
    if (Widgets.contains(id))   {
      switch (id)               {
        case Types::Picture     :
          opconf -> prepare ( ) ;
        break                   ;
      }                         ;
    }                           ;
  }                             ;
  ///////////////////////////////
  return true                   ;
}

bool N::OnePiecePictures::configure(QString scope)
{
  CUIDs IDs                                                   ;
  int   id                                                    ;
  /////////////////////////////////////////////////////////////
  IDs << Types :: Picture                                     ;
  /////////////////////////////////////////////////////////////
  foreach ( id , IDs )                                        {
    if (Widgets.contains(id))                                 {
      switch (id)                                             {
        case Types::Picture                                   :
          opconf -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                 ;
      }                                                       ;
    }                                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                            ;
  if (SC.open("OnePieceSeeker","configure"))                  {
    LearnSite :: Initialize ( SC )                            ;
    SC . close              (    )                            ;
  }                                                           ;
  SC.remove()                                                 ;
  /////////////////////////////////////////////////////////////
  return true                                                 ;
}

bool N::OnePiecePictures::isSkip(void)
{
  if (IsNull(opconf)) return false ;
  return opconf->isSkip()          ;
}

bool N::OnePiecePictures::isCache(void)
{
  if (IsNull(opconf)) return false ;
  return opconf->isCache()         ;
}

bool N::OnePiecePictures::isVolume(void)
{
  if (IsNull(opconf)) return false ;
  return opconf->isVolume()        ;
}

int N::OnePiecePictures::OpStart(void)
{
  if (IsNull(opconf)) return 0 ;
  return opconf->OpStart()     ;
}

int N::OnePiecePictures::VolStart(void)
{
  if (IsNull(opconf)) return 0 ;
  return opconf->VolStart()    ;
}

int N::OnePiecePictures::VolEnd(void)
{
  if (IsNull(opconf)) return 0 ;
  return opconf->VolEnd()      ;
}

QString N::OnePiecePictures::OpRoot(void)
{
  if (IsNull(opconf)) return "" ;
  return opconf->OpRoot()       ;
}

SUID N::OnePiecePictures::Gallery(void)
{
  if (IsNull(opconf)) return 0 ;
  return opconf->Gallery()     ;
}

bool N::OnePiecePictures::startup(int type)
{
  switch ( type )          {
    case Types::Picture    :
    return RunPictures ( ) ;
  }                        ;
  return false             ;
}

bool N::OnePiecePictures::Fetch(SqlConnection & SC,QUrl u,SUID & puid,QByteArray & XML)
{
  if ( isCache  ( )      ) hadCached ( SC , u , puid , XML ) ;
  if ( XML.size ( ) <= 0 ) Obtain    ( SC , u , puid , XML ) ;
  return                             ( XML.size() > 0      ) ;
}

int N::OnePiecePictures::LastestPage(QByteArray & XML)
{
  QString Mark  = "<a href=\"index_"                ;
  QString Dot   = ".html\""                         ;
  int     LID   = 0                                 ;
  int     Start = 0                                 ;
  int     EDX                                       ;
  while ( ( Start = XML.indexOf(Mark.toUtf8(),Start) ) > 0 ) {
    Start += Mark.length()                          ;
    EDX    = XML.indexOf(Dot.toUtf8(),Start)                 ;
    if ( EDX > Start )                              {
      QByteArray B = XML.mid(Start,EDX-Start)       ;
      QString    S = QString::fromUtf8(B)           ;
      Start = EDX + Dot.length()                    ;
      LID = S.toInt()                               ;
    }                                               ;
  }                                                 ;
  return LID                                        ;
}

bool N::OnePiecePictures::RemoveImage(void)
{
  return removeImage ;
}

bool N::OnePiecePictures::EachIssue (
       SqlConnection & SC           ,
       SqlConnection & HC           ,
       QString         Root         ,
       int             Issue        ,
       bool          & done         ,
       int             IDX          ,
       bool            volume       )
{
  int     PID       = 0                                                      ;
  int     LID       = 0                                                      ;
  bool    Available = true                                                   ;
  QString Mark      = "</h1>\n<li><img src=\""                               ;
  int     Pos                                                                ;
  int     Start                                                              ;
  ////////////////////////////////////////////////////////////////////////////
  while ( ( ! done ) && Available )                                          {
    Pos = ( Issue * 1000 ) + PID                                             ;
    //////////////////////////////////////////////////////////////////////////
    QString path = QString("%1/index_%2.html").arg(Root).arg(PID)            ;
    LookUrl ( path )                                                         ;
    plan -> ProgressText ( IDX , path )                                      ;
    DoProcessEvents                                                          ;
    //////////////////////////////////////////////////////////////////////////
    QUrl       u ( path )                                                    ;
    QByteArray XML                                                           ;
    SUID       puid = 0                                                      ;
    Fetch ( SC , u , puid , XML )                                            ;
    //////////////////////////////////////////////////////////////////////////
    if ( ( XML . size ( ) > 0 ) && ( ( Start = XML.indexOf(Mark.toUtf8()) ) > 0 ) )   {
      int EndMark                                                            ;
      Start  += Mark . length  (                  )                          ;
      EndMark = XML  . indexOf ( "\"" , Start + 1 )                          ;
      if ( EndMark > Start )                                                 {
        QByteArray B    = XML.mid(Start,EndMark-Start)                       ;
        QString    S    = QString::fromUtf8(B)                               ;
        if (S.length()>0)                                                    {
          GroupItems GI  ( plan )                                            ;
          QUrl       url ( S    )                                            ;
          SUID       xuid = assurePage ( SC , url  )                         ;
          SUID       zuid = UrlPicture ( SC , xuid )                         ;
          GI . AutoMap = true                                                ;
          ////////////////////////////////////////////////////////////////////
          if (zuid <= 0 )                                                    {
            assureParent( SC , xuid , puid                                 ) ;
            showMessage ( nTimeNow.toString("yyyy/MM/dd hh:mm:ss")         ) ;
            showMessage ( tr("Download %1").arg(url.toString())            ) ;
            Download    ( SC , xuid , url                                  ) ;
            showMessage ( nTimeNow.toString("yyyy/MM/dd hh:mm:ss")         ) ;
            zuid = UrlPicture ( SC , xuid )                                  ;
          }                                                                  ;
          ////////////////////////////////////////////////////////////////////
          if ( zuid > 0 )                                                    {
            GI . GroupTable = GI . LookTable                                 (
                                Types  :: Gallery                            ,
                                Types  :: Picture                            ,
                                Groups :: Subordination                    ) ;
            GI . InsertItem ( SC                                             ,
              Gallery()                                                      ,
              zuid                                                           ,
              Types  :: Gallery                                              ,
              Types  :: Picture                                              ,
              Groups :: Subordination                                        ,
              Pos                                                          ) ;
          }                                                                  ;
          if ( zuid > 0 && xuid > 0 )                                        {
            QString Q                                                        ;
            int     V = volume ? 1 : 0                                       ;
            Q = HC . sql . InsertInto                                        (
                  "oppages"                                                  ,
                  5                                                          ,
                  "issue"                                                    ,
                  "page"                                                     ,
                  "volume"                                                   ,
                  "uuid"                                                     ,
                  "picture"                                                ) ;
            HC . Prepare ( Q                 )                               ;
            HC . Bind    ( "issue"   , Issue )                               ;
            HC . Bind    ( "page"    , PID   )                               ;
            HC . Bind    ( "volume"  , V     )                               ;
            HC . Bind    ( "uuid"    , xuid  )                               ;
            HC . Bind    ( "picture" , zuid  )                               ;
            HC . Exec    (                   )                               ;
            showMessage ( tr("Assign %1 at %2").arg(zuid).arg(Pos) )         ;
          }                                                                  ;
          PID++                                                              ;
        } else Available = false                                             ;
      } else Available = false                                               ;
      LID = LastestPage ( XML )                                              ;
    } else                                                                   {
      Available = false                                                      ;
    }                                                                        ;
    showMessage( tr("%1 of %2").arg(PID).arg(LID+1) )                        ;
    if ( PID > LID ) Available = false                                       ;
    if ( ! Seeker -> runnable  ( ) ) done = true                             ;
    DoProcessEvents                                                          ;
  }                                                                          ;
  return ( PID > 0 ) ;
}

bool N::OnePiecePictures::RunPictures(void)
{
  int         IDX        = -1                                                        ;
  qint64      LocalValue =  0                                                        ;
  bool        LocalGo    = true                                                      ;
  qint64    * Value      = NULL                                                      ;
  bool      * Go         = NULL                                                      ;
  bool        done       = false                                                     ;
  ////////////////////////////////////////////////////////////////////////////////////
  IDX = Seeker -> ID ( )                                                             ;
  if (IDX<0)                                                                         {
    IDX   = plan->Progress                                                           (
              tr("One Piece Picture seeker")                                         ,
              tr("%v/%m (%p%)")                                                    ) ;
    Value = & LocalValue                                                             ;
    Go    = & LocalGo                                                                ;
  } else                                                                             {
    Value = & ( Seeker -> ProgressValue )                                            ;
    Go    = & ( Seeker -> ProgressGo    )                                            ;
  }                                                                                  ;
  ProgressId    = plan->Progress                                                     (
                    tr("One Picture Picture Download")                               ,
                    tr("%v/%m (%p%)")                                              ) ;
  ProgressValue = 0                                                                  ;
  ProgressGo    = true                                                               ;
  plan -> Start ( ProgressId , &ProgressValue , &ProgressGo )                        ;
  Time :: skip ( 1000 )                                                              ;
  ////////////////////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql           )                                           ;
  SqlConnection HC ( Seeker->HunterSql() )                                           ;
  if (SC.open("OpSeeker","Source"))                                                  {
  if (HC.open("OpSeeker","Hunter"))                                                  {
    if ( isVolume() )                                                                {
      bool completed = false                                                         ;
      (*Value) = VolStart ( )                                                        ;
      plan -> Start    ( IDX , Value      , Go       )                               ;
      plan -> setRange ( IDX , VolStart() , VolEnd() )                               ;
      Time :: skip     ( 300                         )                               ;
      while ( ( ! done ) && ( ! completed ) )                                        {
        plan -> setRange ( IDX , VolStart() , VolEnd() )                             ;
        //////////////////////////////////////////////////////////////////////////////
        int  PageId    = *Value                                                      ;
        bool Available = false                                                       ;
        QString VRoot                                                                ;
        VRoot = QString("%1/Vol_%2").arg(OpRoot()).arg(PageId,3,10,QChar('0'))       ;
        Available = EachIssue ( SC , HC , VRoot , PageId + 100 , done , IDX , true ) ;
        //////////////////////////////////////////////////////////////////////////////
        if (!Available)                                                              {
          showMessage ( tr("`%1` does not have information").arg(PageId)           ) ;
        }                                                                            ;
        showMessage ( "==========================================================" ) ;
        if ( (*Value) >= VolEnd ( ) ) completed = true                               ;
                                else (*Value)++                                      ;
        Seeker -> ProgressGo = *Go                                                   ;
        if ( ! Seeker -> runnable  ( ) ) done = true                                 ;
        DoProcessEvents                                                              ;
      }                                                                              ;
    }                                                                                ;
    //////////////////////////////////////////////////////////////////////////////////
    if ( ! done )                                                                    {
      (*Value) = OpStart()                                                           ;
      plan -> Start    ( IDX , Value     , Go     )                                  ;
      plan -> setRange ( IDX , OpStart() , 1500   )                                  ;
      Time :: skip     ( 300                      )                                  ;
      while ( ! done )                                                               {
        plan -> setRange ( IDX , OpStart() , 1500 )                                  ;
        //////////////////////////////////////////////////////////////////////////////
        int  PageId    = *Value                                                      ;
        bool Available = false                                                       ;
        QString SRoot                                                                ;
        SRoot = QString("%1/%2").arg(OpRoot()).arg(PageId,3,10,QChar('0'))           ;
        Available = EachIssue ( SC , HC , SRoot , PageId , done , IDX , false )      ;
        //////////////////////////////////////////////////////////////////////////////
        if (!Available)                                                              {
          showMessage ( tr("`%1` does not have information").arg(PageId)           ) ;
          done = true                                                                ;
        }                                                                            ;
        showMessage ( "==========================================================" ) ;
        if ( (*Value) >= 1500 ) done = true                                          ;
                          else (*Value)++                                            ;
        Seeker -> ProgressGo = *Go                                                   ;
        if ( ! Seeker -> runnable  ( ) ) done = true                                 ;
        DoProcessEvents                                                              ;
      }                                                                              ;
    };
    //////////////////////////////////////////////////////////////////////////////////
    if ( Seeker -> ID ( ) < 0 ) plan -> Finish ( IDX )                               ;
    //////////////////////////////////////////////////////////////////////////////////
  HC.close ()                                                                        ;
  } else                                                                             {
  HC.close ()                                                                        ;
  }                                                                                  ;
  HC.remove()                                                                        ;
  SC.close ()                                                                        ;
  } else                                                                             {
  SC.close ()                                                                        ;
  }                                                                                  ;
  SC.remove()                                                                        ;
  ////////////////////////////////////////////////////////////////////////////////////
  plan -> Finish ( ProgressId )                                                      ;
  return true                                                                        ;
}
