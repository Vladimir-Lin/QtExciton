#include <exciton.h>

N::AupInfoSeeker:: AupInfoSeeker  ( QObject * parent , Plan * p )
                 : SiteSeeker     (           parent ,        p )
                 , aupeople       ( NULL                        )
                 , auvideo        ( NULL                        )
{
  Enabled [ Types :: People       ] = true  ;
  Enabled [ Types :: Video        ] = true  ;
  Enabled [ Types :: Document     ] = false ;
  Enabled [ Types :: Organization ] = false ;
}

N::AupInfoSeeker::~AupInfoSeeker(void)
{
}

int N::AupInfoSeeker::Type(void) const
{
  return 10002 ;
}

QString N::AupInfoSeeker::Name(void) const
{
  return tr("AV actress & Adult Movie") ;
}

bool N::AupInfoSeeker::Supported(int type) const
{
  switch ( type )              {
    case Types :: People       :
    return true                ;
    case Types :: Video        :
    return true                ;
  }                            ;
  return false                 ;
}

QString N::AupInfoSeeker::Name(int type) const
{
  switch ( type )                                        {
    case Types :: People                                 :
    return tr("AV actress & Adult Movie - People"      ) ;
    case Types :: Video                                  :
    return tr("AV actress & Adult Movie - Video"       ) ;
    case Types :: Document                               :
    return tr("AV actress & Adult Movie - Documents"   ) ;
    case Types :: Organization                           :
    return tr("AV actress & Adult Movie - Organization") ;
  }                                                      ;
  return ""                                              ;
}

QWidget * N::AupInfoSeeker::Configurator (int type)
{
  if (Widgets.contains(type)) return Widgets [ type ]      ;
  switch ( type )                                          {
    case Types :: People                                   :
      aupeople         = new AupInfoPeople ( NULL , plan ) ;
      Widgets [ type ] = aupeople                          ;
    return Widgets [ type ]                                ;
    case Types :: Video                                    :
      auvideo          = new AupInfoVideo  ( NULL , plan ) ;
      Widgets [ type ] = auvideo                           ;
    return Widgets [ type ]                                ;
  }                                                        ;
  return NULL                                              ;
}

bool N::AupInfoSeeker::setEnabled(int type,bool enable)
{
  switch ( type )               {
    case Types :: People        :
    case Types :: Video         :
      Enabled [ type ] = enable ;
    return Enabled [ type ]     ;
  }                             ;
  return false                  ;
}

bool N::AupInfoSeeker::prepare(void)
{
  CUIDs IDs                       ;
  int   id                        ;
  /////////////////////////////////
  IDs << Types :: People          ;
  IDs << Types :: Video           ;
  /////////////////////////////////
  foreach ( id , IDs )            {
    if (Widgets.contains(id))     {
      switch (id)                 {
        case Types::People        :
          aupeople -> prepare ( ) ;
        break                     ;
        case Types::Video         :
          auvideo  -> prepare ( ) ;
        break                     ;
      }                           ;
    }                             ;
  }                               ;
  /////////////////////////////////
  return true                     ;
}

bool N::AupInfoSeeker::configure(QString scope)
{
  CUIDs IDs                                                     ;
  int   id                                                      ;
  ///////////////////////////////////////////////////////////////
  IDs << Types :: People                                        ;
  IDs << Types :: Video                                         ;
  ///////////////////////////////////////////////////////////////
  foreach ( id , IDs )                                          {
    if (Widgets.contains(id))                                   {
      switch (id)                                               {
        case Types::People                                      :
          aupeople -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                   ;
        case Types::Video                                       :
          auvideo  -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                   ;
      }                                                         ;
    }                                                           ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                              ;
  if (SC.open("AupInfoSeeker","configure"))                     {
    LearnSite :: Initialize ( SC )                              ;
    SC . close              (    )                              ;
  }                                                             ;
  SC.remove()                                                   ;
  ///////////////////////////////////////////////////////////////
  return true                                                   ;
}

bool N::AupInfoSeeker::SkipPeople(void)
{
  if (IsNull(aupeople)) return 0 ;
  return aupeople->SkipExists()  ;
}

bool N::AupInfoSeeker::VerifyEnglish(void)
{
  if (IsNull(aupeople)) return 0   ;
  return aupeople->VerifyEnglish() ;
}

int N::AupInfoSeeker::PeopleStart(void)
{
  if (IsNull(aupeople)) return 0 ;
  return aupeople->PeopleStart() ;
}

int N::AupInfoSeeker::PeopleEnd(void)
{
  if (IsNull(aupeople)) return 0 ;
  return aupeople->PeopleEnd()   ;
}

SUID N::AupInfoSeeker::NewbieUuid(void)
{
  if (IsNull(aupeople)) return 0 ;
  return aupeople->NewbieUuid()  ;
}

SUID N::AupInfoSeeker::MergerUuid(void)
{
  if (IsNull(aupeople)) return 0 ;
  return aupeople->MergerUuid()  ;
}

SUID N::AupInfoSeeker::GalleryUuid(void)
{
  if (IsNull(aupeople)) return 0 ;
  return aupeople->GalleryUuid() ;
}

SUID N::AupInfoSeeker::PeopleNameMaps(int index)
{
  if (IsNull(aupeople)) return 0   ;
  return aupeople->NameUuid(index) ;
}

QString N::AupInfoSeeker::Search(int Id)
{
  if (IsNull(aupeople)) return ""     ;
  QString search = aupeople->Search() ;
  return QString(search).arg(Id)      ;
}

QString N::AupInfoSeeker::Actress(void)
{
  if (IsNull(aupeople)) return "" ;
  return aupeople->Actress()      ;
}

bool N::AupInfoSeeker::SkipVideo(void)
{
  if (IsNull(auvideo)) return 0 ;
  return auvideo->SkipExists()  ;
}

bool N::AupInfoSeeker::VideoCache(void)
{
  if (IsNull(auvideo)) return 0 ;
  return auvideo->VideoCache()  ;
}

int N::AupInfoSeeker::VideoStart(void)
{
  if (IsNull(auvideo)) return 0 ;
  return auvideo->VideoStart()  ;
}

int N::AupInfoSeeker::VideoEnd(void)
{
  if (IsNull(auvideo)) return 0 ;
  return auvideo->VideoEnd()    ;
}

SUID N::AupInfoSeeker::AlbumUuid(void)
{
  if (IsNull(auvideo)) return 0 ;
  return auvideo->AlbumUuid()   ;
}

SUID N::AupInfoSeeker::InterestUuid(void)
{
  if (IsNull(auvideo)) return 0  ;
  return auvideo->InterestUuid() ;
}

SUID N::AupInfoSeeker::VideoGalleryUuid(void)
{
  if (IsNull(auvideo)) return 0 ;
  return auvideo->GalleryUuid() ;
}

SUID N::AupInfoSeeker::VideoNameMaps(int index)
{
  if (IsNull(auvideo)) return 0   ;
  return auvideo->NameUuid(index) ;
}

QString N::AupInfoSeeker::VideoSearch(int Id)
{
  if (IsNull(auvideo)) return ""     ;
  QString search = auvideo->Search() ;
  return QString(search).arg(Id)     ;
}

bool N::AupInfoSeeker::startup(int type)
{
  switch ( type )        {
    case Types::People   :
    return RunPeople ( ) ;
    case Types::Video    :
    return RunVideo  ( ) ;
  }                      ;
  return false           ;
}

QStringList N::AupInfoSeeker::AupInfoPeoples(QByteArray & XML,QString found)
{
  QStringList Ps                                          ;
  QStringList Rs                                          ;
  int index = XML.indexOf(found.toUtf8())                          ;
  if (index<=0) return Ps                                 ;
  found  = "</span><dt>"                                  ;
  index  = XML.indexOf(found.toUtf8(),index)                       ;
  if (index<0) return Ps                                  ;
  index += found.length()                                 ;
  if (index<=0) return Ps                                 ;
  int endix = XML.indexOf("</dt>",index+1)                ;
  if (endix<=0) return Ps                                 ;
  QByteArray S = XML.mid(index,endix-index)               ;
  QString N = QString::fromUtf8(S)                        ;
  N  = N.replace("("," ")                                 ;
  N  = N.replace(")"," ")                                 ;
  N  = N.replace(","," ")                                 ;
  N  = N.replace("["," ")                                 ;
  N  = N.replace("]"," ")                                 ;
  Rs = N.split  (' '    )                                 ;
  foreach (N,Rs)                                          {
    if (N.length()>0 && !N.contains(' '))                 {
      if (N.length()<20) Ps << N                          ;
    }                                                     ;
  }                                                       ;
  return Ps                                               ;
}

QString N::AupInfoSeeker::AupInfoImageSrc(QByteArray & XML,QString found)
{
  int index = XML.indexOf(found.toUtf8())                ;
  if (index<=0) return ""                       ;
  found = "<img src="                           ;
  index = XML.indexOf(found.toUtf8(),index)              ;
  if (index<=0) return ""                       ;
  index = XML.indexOf("\"",index)               ;
  int endix = XML.indexOf("\"",index+1)         ;
  if (endix<=0) return ""                       ;
  QByteArray S = XML.mid(index+1,endix-index-1) ;
  return QString::fromUtf8(S)                   ;
}

bool N::AupInfoSeeker::BindAupInfo (
       SqlConnection & SC          ,
       SUID            people      ,
       QString         name        ,
       QString         found       ,
       QByteArray    & XML         )
{
  int index = XML.indexOf(found.toUtf8())                                 ;
  if (index<=0) return false                                     ;
  found  = "</span><dt>"                                         ;
  index  = XML.indexOf(found.toUtf8(),index)                              ;
  if (index<=0) return false                                     ;
  index += found.length()                                        ;
  found  = "</dt><dd>"                                           ;
  index  = XML.indexOf(found.toUtf8(),index+1)                            ;
  if (index<=0) return false                                     ;
  index += found.length()                                        ;
  found = "</dd>"                                                ;
  int finix = XML.indexOf(found.toUtf8(),index)                           ;
  if (finix<=0) return false                                     ;
  QByteArray BD = XML.mid(index,finix-index)                     ;
  QString    bd = QString::fromUtf8(BD)                          ;
  ////////////////////////////////////////////////////////////////
  bd = bd.replace("<b>" ,"" )                                    ;
  bd = bd.replace("</b>","" )                                    ;
  bd = bd.replace("<br>"," ")                                    ;
  ////////////////////////////////////////////////////////////////
  QStringList BL = bd.split(' ')                                 ;
  SUID        tuid = 0                                           ;
  ////////////////////////////////////////////////////////////////
  UUIDs TUIDs = Subordination                                    (
                  SC                                             ,
                  people                                         ,
                  Types  :: People                               ,
                  Types  :: History                              ,
                  Groups :: Subordination                        ,
                  SC.OrderByAsc("position")                    ) ;
  if (TUIDs.count()>0)                                           {
    tuid = GetHistoryType                                        (
             SC                                                  ,
             TUIDs                                               ,
             History::PeopleBirth                              ) ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  QString S                                                      ;
  bool    processed                                              ;
  foreach (S,BL)                                                 {
    processed = false                                            ;
    if (!processed && S.contains("B:"))                          {
      QString v = S                                              ;
      v.remove(0,2)                                              ;
      int l = v.toInt()                                          ;
      if (l>0 && l<300)                                          {
        QString ML = QString::number(l)                          ;
        showMessage ( tr("Bust [%1]").arg(l)                   ) ;
        assureVariable(SC,people,Types::People,"Bust",ML)        ;
        processed = true                                         ;
      }                                                          ;
    }                                                            ;
    if (!processed && S.contains("W:"))                          {
      QString v = S                                              ;
      v.remove(0,2)                                              ;
      int l = v.toInt()                                          ;
      if (l>0 && l<300)                                          {
        QString ML = QString::number(l)                          ;
        showMessage ( tr("Waist [%1]").arg(l)                  ) ;
        assureVariable(SC,people,Types::People,"Waist",ML)       ;
        processed = true                                         ;
      }                                                          ;
    }                                                            ;
    if (!processed && S.contains("H:"))                          {
      QString v = S                                              ;
      v.remove(0,2)                                              ;
      int l = v.toInt()                                          ;
      if (l>0 && l<300)                                          {
        QString ML = QString::number(l)                          ;
        showMessage ( tr("Hip [%1]").arg(l)                    ) ;
        assureVariable(SC,people,Types::People,"Hip",ML)         ;
        processed = true                                         ;
      }                                                          ;
    }                                                            ;
    if (!processed && S.contains("T:"))                          {
      QString v = S                                              ;
      v.remove(0,2)                                              ;
      int l = v.toInt()                                          ;
      if (l>0 && l<300)                                          {
        QString ML = QString::number(l)                          ;
        showMessage ( tr("Height [%1]").arg(l)                 ) ;
        assureVariable(SC,people,Types::People,"Height",ML)      ;
        processed = true                                         ;
      }                                                          ;
    }                                                            ;
    if (!processed && S.length()>8)                              {
      processed = true                                           ;
      if (!S.at(0).isNumber()) processed = false                 ;
      if (!S.at(1).isNumber()) processed = false                 ;
      if (!S.at(2).isNumber()) processed = false                 ;
      if (!S.at(3).isNumber()) processed = false                 ;
      if (!S.at(5).isNumber()) processed = false                 ;
      if (!S.at(6).isNumber()) processed = false                 ;
      if (!S.at(8).isNumber()) processed = false                 ;
      if (!S.at(9).isNumber()) processed = false                 ;
      if (processed)                                             {
        processed = false                                        ;
        QString Y = S.left(4)                                    ;
        QString M = S.mid(5,2)                                   ;
        QString D = S.mid(8,2)                                   ;
        int     y = Y.toInt()                                    ;
        int     m = M.toInt()                                    ;
        int     d = D.toInt()                                    ;
        QDate   DT(y,m,d)                                        ;
        if (DT.isValid())                                        {
          N::StarDate SD                                         ;
          QTime TT(21,0,0)                                       ;
          QDateTime BD                                           ;
          BD.setDate(DT)                                         ;
          BD.setTime(TT)                                         ;
          SD = BD                                                ;
          showMessage ( tr("[%1] Birthday [%2] = %3"             )
                        .arg(name                                )
                        .arg(BD.toString("yyyy/MM/dd hh:mm:ss")  )
                        .arg(SD.Stardate)                      ) ;
          SUID ouid = tuid                                       ;
          tuid = assureTime                                      (
                   SC                                            ,
                   tuid                                          ,
                   History::PeopleBirth                          ,
                   SD.Stardate                                 ) ;
          if (ouid<=0 && tuid>0)                                 {
            UUIDs ZUIDs                                          ;
            ZUIDs << tuid                                        ;
            Join                                                 (
              SC                                                 ,
              people                                             ,
              Types  :: People                                   ,
              Types  :: History                                  ,
              Groups :: Subordination                            ,
              0                                                  ,
              ZUIDs                                            ) ;
          }                                                      ;
          processed = true                                       ;
        }                                                        ;
      }                                                          ;
    }                                                            ;
    if (!processed && S.length()>1 && S.length()<4)              {
      QString Blood                                              ;
      if (S.contains("AB"))                                      {
        Blood = "AB"                                             ;
      } else
      if (S.contains("A"))                                       {
        Blood = "A"                                              ;
      } else
      if (S.contains("B"))                                       {
        Blood = "B"                                              ;
      } else
      if (S.contains("O"))                                       {
        Blood = "O"                                              ;
      }                                                          ;
      if (Blood.length()>0)                                      {
        showMessage ( tr("Blood type [%1]").arg(Blood)         ) ;
        assureVariable(SC,people,N::Types::People,"Blood",Blood) ;
        processed = true                                         ;
      }                                                          ;
    }                                                            ;
    if (!processed)                                              {
      showMessage ( tr("Ignore [%1]").arg(S)                   ) ;
    }                                                            ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  return true                                                    ;
}

bool N::AupInfoSeeker::UpdateAupPeople (
       SqlConnection & SC              ,
       int             PornstarId      ,
       SUID            nuid            ,
       QString         name            )
{
  QString Q                                   ;
  Q = SC.sql.ReplaceInto                      (
        "aupinfo"                             ,
        3                                     ,
        "id"                                  ,
        "uuid"                                ,
        "name"                              ) ;
  SC . Prepare     ( Q                      ) ;
  SC . Bind        ( "id"   , PornstarId    ) ;
  SC . Bind        ( "uuid" , nuid          ) ;
  SC . Bind        ( "name" , name.toUtf8() ) ;
  return SC . Exec (                        ) ;
}

bool N::AupInfoSeeker::RunPeople(void)
{
  NAMEs   Release                                                              ;
  NAMEs   actress                                                              ;
  NAMEs   Product                                                              ;
  NAMEs   SKU                                                                  ;
  NAMEs   Penetration                                                          ;
  int     IDX        = -1                                                      ;
  qint64     LocalValue =  0                                                      ;
  bool    LocalGo    = true                                                    ;
  qint64   * Value      = NULL                                                    ;
  bool  * Go         = NULL                                                    ;
  bool    done       = false                                                   ;
  //////////////////////////////////////////////////////////////////////////////
  QTextCodec * eucjp = NULL                                                    ;
  eucjp = QTextCodec::codecForName("EUC-JP")                                   ;
  if (IsNull(eucjp)) return false                                              ;
  //////////////////////////////////////////////////////////////////////////////
  IDX = Seeker -> ID ( )                                                       ;
  if (IDX<0)                                                                   {
    IDX   = plan->Progress                                                     (
              tr("AV actress & Adult Movie - People seeker")                   ,
              tr("%v/%m")                                                    ) ;
    Value = & LocalValue                                                       ;
    Go    = & LocalGo                                                          ;
    Time :: skip ( 1000 )                                                      ;
  } else                                                                       {
    Value = & ( Seeker -> ProgressValue )                                      ;
    Go    = & ( Seeker -> ProgressGo    )                                      ;
  }                                                                            ;
  //////////////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql           )                                     ;
  SqlConnection HC ( Seeker->HunterSql() )                                     ;
  if (SC.open("AupInfoPeopleSeeker","Source"))                                 {
  if (HC.open("AupInfoPeopleSeeker","Hunter"))                                 {
    QString Q                                                                  ;
    CUIDs   Existing                                                           ;
    ////////////////////////////////////////////////////////////////////////////
    (*Value) = PeopleStart ( )                                                 ;
    plan -> Start    ( IDX , Value         , Go          )                     ;
    plan -> setRange ( IDX , PeopleStart() , PeopleEnd() )                     ;
    Time :: skip     ( 300                               )                     ;
    ////////////////////////////////////////////////////////////////////////////
    NamesByOrder ( SC , VideoNameMaps ( 0 ) , Release      )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 1 ) , actress      )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 2 ) , Product      )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 3 ) , SKU          )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 4 ) , Penetration  )                   ;
    ////////////////////////////////////////////////////////////////////////////
    Q = HC.sql.SelectFrom                                                      (
          "id"                                                                 ,
          "aupinfo"                                                            ,
          HC.OrderByAsc("id")                                                ) ;
    SqlLoopNow ( HC , Q )                                                      ;
      Existing << HC . Int ( 0 )                                               ;
    SqlLoopErr ( HC , Q )                                                      ;
    SqlLoopEnd ( HC , Q )                                                      ;
    ////////////////////////////////////////////////////////////////////////////
    while ( ! done )                                                           {
      plan -> setRange ( IDX , PeopleStart() , PeopleEnd() )                   ;
      //////////////////////////////////////////////////////////////////////////
      int  PornstarId = *Value                                                 ;
      bool Available  = false                                                  ;
      //////////////////////////////////////////////////////////////////////////
      if ( SkipPeople() )                                                      {
        if (Existing.contains(PornstarId))                                     {
          if ( (*Value) >= PeopleEnd ( ) ) done = true                         ;
                                      else (*Value)++                          ;
          Seeker -> ProgressGo = *Go                                           ;
          if ( ! Seeker -> runnable  ( ) ) done = true                         ;
          DoProcessEvents                                                      ;
          continue                                                             ;
        }                                                                      ;
      }                                                                        ;
      //////////////////////////////////////////////////////////////////////////
      QString path = Search ( PornstarId )                                     ;
      LookUrl ( path )                                                         ;
      plan -> ProgressText  ( IDX , path )                                     ;
      DoProcessEvents                                                          ;
      //////////////////////////////////////////////////////////////////////////
      QUrl       u ( path )                                                    ;
      QByteArray XML                                                           ;
      SUID       puid = 0                                                      ;
      Obtain ( SC , u , puid , XML )                                           ;
      //////////////////////////////////////////////////////////////////////////
      if (XML.size()>0)                                                        {
        QString sss = eucjp->toUnicode(XML)                                    ;
        XML = sss.toUtf8()                                                     ;
        showMessage ( tr("Size : %1").arg(XML.size()) )                        ;
        if ( XML . indexOf ( Actress().toUtf8() ) >= 0 )                                {
          QStringList PeopleNames                                              ;
          QString     imgsrc                                                   ;
          QString     name                                                     ;
          PeopleNames = AupInfoPeoples  ( XML , Actress ( ) )                  ;
          imgsrc      = AupInfoImageSrc ( XML , Actress ( ) )                  ;
          if ( PeopleNames . count ( ) > 0 ) name = PeopleNames[0]             ;
          showMessage ( tr    ( "`%1`(%2) has information"                     )
                        . arg ( name                                           )
                        . arg ( PornstarId                                 ) ) ;
          if ( ( name . length ( ) > 0 ) && ( imgsrc . length ( ) > 0 )      ) {
            SUID nuid = FindPeople(SC,name)                                    ;
            showMessage ( imgsrc )                                             ;
            if (nuid<=0)                                                       {
              showMessage ( tr("%1 is a new pornstar").arg(name)             ) ;
              addPeople ( SC , 2726 , name )                                   ;
              nuid = FindPeople(SC,name)                                       ;
              if ( ( NewbieUuid() > 0 ) && ( nuid > 0 )                      ) {
                UUIDs NewPeople                                                ;
                NewPeople << nuid                                              ;
                Join                                                           (
                  SC                                                           ,
                  NewbieUuid ( )                                               ,
                  N::Types::Division                                           ,
                  N::Types::People                                             ,
                  N::Groups::Subordination                                     ,
                  0                                                            ,
                  NewPeople                                                  ) ;
              }                                                                ;
            }                                                                  ;
            if (nuid>0)                                                        {
              QString Q                                                        ;
              QUrl xurl ( imgsrc )                                             ;
              AttachPeople  ( SC , xurl , nuid , name , GalleryUuid()        ) ;
              BindAupInfo   ( SC , nuid , name , Actress ( ) , XML           ) ;
              if (PeopleNames.count()>1)                                       {
                MergePeople ( SC , MergerUuid() , nuid , PeopleNames , 2726  ) ;
              }                                                                ;
              //////////////////////////////////////////////////////////////////
              UpdateAupPeople ( HC , PornstarId , nuid , name                ) ;
            }                                                                  ;
          }                                                                    ;
          Available = true                                                     ;
        }                                                                      ;
      }                                                                        ;
      //////////////////////////////////////////////////////////////////////////
      if (!Available)                                                          {
        showMessage ( tr("`%1` does not have information").arg(PornstarId)   ) ;
      } else                                                                   {
        if (!Existing.contains(PornstarId)) Existing << PornstarId             ;
      }                                                                        ;
      showMessage ( "======================================================" ) ;
      if ( (*Value) >= PeopleEnd ( ) ) done = true                             ;
                                  else (*Value)++                              ;
      Seeker -> ProgressGo = *Go                                               ;
      if ( ! Seeker -> runnable  ( ) ) done = true                             ;
      DoProcessEvents                                                          ;
    }                                                                          ;
    ////////////////////////////////////////////////////////////////////////////
    if ( Seeker -> runnable ( ) && VerifyEnglish ( ) )                         {
      UUIDs   Uuids                                                            ;
      SUID    u                                                                ;
      Q = HC.sql.SelectFrom                                                    (
            "uuid"                                                             ,
            "aupinfo"                                                          ,
            QString("where id >= %1").arg(PeopleStart())                       ,
            HC.OrderByAsc("id")                                              ) ;
      SqlLoopNow ( HC , Q )                                                    ;
        Uuids << HC . Uuid ( 0 )                                               ;
      SqlLoopErr ( HC , Q )                                                    ;
      SqlLoopEnd ( HC , Q )                                                    ;
      if (Uuids.count()>0)                                                     {
        plan -> setRange ( IDX , 0 , Uuids.count() )                           ;
        (*Value) = 0                                                           ;
        for (int z = 0 ; Seeker->runnable() && z<Uuids.count() ; z++         ) {
          (*Value)++                                                           ;
          u = Uuids [ z ]                                                      ;
          UUIDs Auids = Subordination                                          (
                          SC                                                   ,
                          u                                                    ,
                          Types  :: People                                     ,
                          Types  :: URL                                        ,
                          Groups :: Subordination                              ,
                          SC.OrderByAsc("position")                          ) ;
          if (Auids.count()>0)                                                 {
            SUID p                                                             ;
            foreach (p,Auids)                                                  {
              QUrl    url     = PageUrl(SC,p)                                  ;
              QString pul     = url.toString()                                 ;
              bool    correct = true                                           ;
              if (correct && !pul.contains("www"      )) correct = false       ;
              if (correct && !pul.contains("a-up.info")) correct = false       ;
              if (correct && !pul.contains("avlady"   )) correct = false       ;
              if (correct && !pul.contains(".jpg"     )) correct = false       ;
              if (correct)                                                     {
                QString     pt = "http://www.a-up.info/avlady/img/lady/"       ;
                QString     ns                                                 ;
                QString     R                                                  ;
                QStringList ELs                                                ;
                QStringList ULs                                                ;
                ns  = pul.replace(pt,"")                                       ;
                ns  = ns.replace(".jpg","")                                    ;
                ns  = ns.replace("_"," ")                                      ;
                ELs = ns.split(' ')                                            ;
                foreach (R,ELs)                                                {
                  ns = ""                                                      ;
                  for (int i=0;i<R.length();i++)                               {
                    if (i==0) ns . append ( R.at(i).toUpper())                 ;
                         else ns . append ( R.at(i).toLower())                 ;
                  }                                                            ;
                  if (ns.length()>0) ULs << ns                                 ;
                }                                                              ;
                if (ULs.count()>1)                                             {
                  ns = ULs.join(" ")                                           ;
                  if (ns.length()>0 && ns.length()<50)                         {
                    assureEnglish(SC,u,ULs)                                    ;
                  }                                                            ;
                }                                                              ;
              }                                                                ;
            }                                                                  ;
          }                                                                    ;
        }                                                                      ;
      }                                                                        ;
    }                                                                          ;
    ////////////////////////////////////////////////////////////////////////////
    if ( Seeker -> ID ( ) < 0 ) plan -> Finish ( IDX )                         ;
    ////////////////////////////////////////////////////////////////////////////
  HC.close ()                                                                  ;
  } else                                                                       {
  HC.close ()                                                                  ;
  }                                                                            ;
  HC.remove()                                                                  ;
  SC.close ()                                                                  ;
  } else                                                                       {
  SC.close ()                                                                  ;
  }                                                                            ;
  SC.remove()                                                                  ;
  return true                                                                  ;
}

bool N::AupInfoSeeker::Fetch(SqlConnection & SC,QUrl u,SUID & puid,QByteArray & XML)
{
  if ( VideoCache ( )    ) hadCached ( SC , u , puid , XML ) ;
  if ( XML.size ( ) <= 0 ) Obtain    ( SC , u , puid , XML ) ;
  return                             ( XML.size() > 0      ) ;
}

bool N::AupInfoSeeker::RunVideo(void)
{
  NAMEs  Release                                                               ;
  NAMEs  Actress                                                               ;
  NAMEs  Product                                                               ;
  NAMEs  SKU                                                                   ;
  NAMEs  Penetration                                                           ;
  NAMEs  InfoMaps                                                              ;
  int    IDX        = -1                                                       ;
  qint64    LocalValue =  0                                                       ;
  bool   LocalGo    = true                                                     ;
  qint64  * Value      = NULL                                                     ;
  bool * Go         = NULL                                                     ;
  bool   done       = false                                                    ;
  //////////////////////////////////////////////////////////////////////////////
  IDX = Seeker -> ID ( )                                                       ;
  if (IDX<0)                                                                   {
    IDX   = plan->Progress                                                     (
              tr("AV actress & Adult Movie - Video seeker")                    ,
              tr("%v/%m")                                                    ) ;
    Value = & LocalValue                                                       ;
    Go    = & LocalGo                                                          ;
    Time :: skip ( 1000 )                                                      ;
  } else                                                                       {
    Value = & ( Seeker -> ProgressValue )                                      ;
    Go    = & ( Seeker -> ProgressGo    )                                      ;
  }                                                                            ;
  //////////////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql           )                                     ;
  SqlConnection HC ( Seeker->HunterSql() )                                     ;
  if (SC.open("AupInfoVideoSeeker","Source"))                                  {
  if (HC.open("AupInfoVideoSeeker","Hunter"))                                  {
    ////////////////////////////////////////////////////////////////////////////
    QString Q                                                                  ;
    ////////////////////////////////////////////////////////////////////////////
    (*Value) = VideoStart ( )                                                  ;
    plan -> Start    ( IDX , Value        , Go         )                       ;
    plan -> setRange ( IDX , VideoStart() , VideoEnd() )                       ;
    Time :: skip     ( 300                             )                       ;
    ////////////////////////////////////////////////////////////////////////////
    NamesByOrder ( SC , VideoNameMaps ( 0 ) , Release      )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 1 ) , Actress      )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 2 ) , Product      )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 3 ) , SKU          )                   ;
    NamesByOrder ( SC , VideoNameMaps ( 4 ) , Penetration  )                   ;
    ////////////////////////////////////////////////////////////////////////////
    InfoMaps [ 0 ] = Release [ 0 ]                                             ;
    InfoMaps [ 1 ] = Product [ 0 ]                                             ;
    InfoMaps [ 2 ] = Release [ 1 ]                                             ;
    ////////////////////////////////////////////////////////////////////////////
    LoadCompanyProducts ( SC )                                                 ;
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    if ( Seeker -> ID ( ) < 0 ) plan -> Finish ( IDX )                         ;
    ////////////////////////////////////////////////////////////////////////////
  HC.close ()                                                                  ;
  } else                                                                       {
  HC.close ()                                                                  ;
  }                                                                            ;
  HC.remove()                                                                  ;
  SC.close ()                                                                  ;
  } else                                                                       {
  SC.close ()                                                                  ;
  }                                                                            ;
  SC.remove()                                                                  ;
  return true                                                                  ;
}
