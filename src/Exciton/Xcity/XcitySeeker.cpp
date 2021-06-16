#include <exciton.h>

N::XcitySeeker:: XcitySeeker ( QObject * parent , Plan * p )
               : SiteSeeker  (           parent ,        p )
{
  Enabled [ Types :: People       ] = true  ;
  Enabled [ Types :: Video        ] = true  ;
  Enabled [ Types :: Document     ] = false ;
  Enabled [ Types :: Organization ] = true  ;
  ///////////////////////////////////////////
  xcpeople       = NULL                     ;
  xcvideo        = NULL                     ;
  xcorganization = NULL                     ;
}

N::XcitySeeker::~XcitySeeker(void)
{
}

int N::XcitySeeker::Type(void) const
{
  return 10001 ;
}

QString N::XcitySeeker::Name(void) const
{
  return tr("X City / Japan") ;
}

bool N::XcitySeeker::Supported(int type) const
{
  switch ( type )              {
    case Types :: People       :
    return true                ;
    case Types :: Video        :
    return true                ;
    case Types :: Document     :
    return false               ;
    case Types :: Organization :
    return true                ;
  }                            ;
  return false                 ;
}

QString N::XcitySeeker::Name(int type) const
{
  switch ( type )                      {
    case Types :: People               :
    return tr("X City - People"      ) ;
    case Types :: Video                :
    return tr("X City - Video"       ) ;
    case Types :: Document             :
    return tr("X City - Documents"   ) ;
    case Types :: Organization         :
    return tr("X City - Organization") ;
  }                                    ;
  return ""                            ;
}

QWidget * N::XcitySeeker::Configurator (int type)
{
  if (Widgets.contains(type)) return Widgets [ type ]          ;
  switch ( type )                                              {
    case Types :: People                                       :
      xcpeople         = new XcityPeople       ( NULL , plan ) ;
      Widgets [ type ] = xcpeople                              ;
    return Widgets [ type ]                                    ;
    case Types :: Video                                        :
      xcvideo          = new XcityVideo        ( NULL , plan ) ;
      Widgets [ type ] = xcvideo                               ;
    return Widgets [ type ]                                    ;
    case Types :: Document                                     :
    return NULL                                                ;
    case Types :: Organization                                 :
      xcorganization   = new XcityOrganization ( NULL , plan ) ;
      Widgets [ type ] = xcorganization                        ;
    return Widgets [ type ]                                    ;
  }                                                            ;
  return NULL                                                  ;
}

bool N::XcitySeeker::setEnabled(int type,bool enable)
{
  switch ( type )               {
    case Types :: People        :
    case Types :: Video         :
    case Types :: Organization  :
      Enabled [ type ] = enable ;
    return Enabled [ type ]     ;
  }                             ;
  return false                  ;
}

bool N::XcitySeeker::SkipPeople(void)
{
  if (IsNull(xcpeople)) return false ;
  return xcpeople->SkipExists()      ;
}

int N::XcitySeeker::PeopleStart(void)
{
  if (IsNull(xcpeople)) return 0 ;
  return xcpeople->PeopleStart() ;
}

int N::XcitySeeker::PeopleEnd(void)
{
  if (IsNull(xcpeople)) return 0 ;
  return xcpeople->PeopleEnd()   ;
}

SUID N::XcitySeeker::NewbieUuid(void)
{
  if (IsNull(xcpeople)) return 0 ;
  return xcpeople->NewbieUuid()  ;
}

SUID N::XcitySeeker::MergerUuid(void)
{
  if (IsNull(xcpeople)) return 0 ;
  return xcpeople->MergerUuid()  ;
}

SUID N::XcitySeeker::GalleryUuid(void)
{
  if (IsNull(xcpeople)) return 0 ;
  return xcpeople->GalleryUuid() ;
}

QString N::XcitySeeker::Search(QString name)
{
  if (IsNull(xcpeople)) return ""     ;
  QString search = xcpeople->Search() ;
  return QString(search).arg(name)    ;
}

QString N::XcitySeeker::Missing(void)
{
  if (IsNull(xcpeople)) return ""       ;
  QString missing = xcpeople->Missing() ;
  return missing                        ;
}

QString N::XcitySeeker::Found(void)
{
  if (IsNull(xcpeople)) return ""   ;
  QString found = xcpeople->Found() ;
  return found                      ;
}

QString N::XcitySeeker::IdFound(void)
{
  if (IsNull(xcpeople)) return ""  ;
  QString id = xcpeople->IdFound() ;
  return id                        ;
}

QString N::XcitySeeker::IdPattern(int id)
{
  if (IsNull(xcpeople)) return ""    ;
  QString ip = xcpeople->IdPattern() ;
  return QString(ip).arg(id)         ;
}

bool N::XcitySeeker::SkipVideo(void)
{
  if (IsNull(xcvideo)) return false ;
  return xcvideo->SkipExists()      ;
}

bool N::XcitySeeker::VideoCache(void)
{
  if (IsNull(xcvideo)) return false ;
  return xcvideo->VideoCache()      ;
}

int N::XcitySeeker::VideoStart(void)
{
  if (IsNull(xcvideo)) return 0 ;
  return xcvideo->VideoStart()  ;
}

int N::XcitySeeker::VideoEnd(void)
{
  if (IsNull(xcvideo)) return 0 ;
  return xcvideo->VideoEnd()    ;
}

SUID N::XcitySeeker::AlbumUuid(void)
{
  if (IsNull(xcvideo)) return 0 ;
  return xcvideo->AlbumUuid()   ;
}

SUID N::XcitySeeker::InterestUuid(void)
{
  if (IsNull(xcvideo)) return 0  ;
  return xcvideo->InterestUuid() ;
}

SUID N::XcitySeeker::VideoGalleryUuid(void)
{
  if (IsNull(xcvideo)) return 0 ;
  return xcvideo->GalleryUuid() ;
}

QString N::XcitySeeker::VideoSearch(int id)
{
  if (IsNull(xcvideo)) return "" ;
  QString ip = xcvideo->Search() ;
  return QString(ip).arg(id)     ;
}

QString N::XcitySeeker::VideoInfo(void)
{
  if (IsNull(xcvideo)) return "" ;
  return xcvideo->Info()         ;
}

QString N::XcitySeeker::VideoGalleryString(void)
{
  if (IsNull(xcvideo)) return "" ;
  return xcvideo->Gallery()      ;
}

SUID N::XcitySeeker::VideoNameMaps(int index)
{
  if (IsNull(xcvideo)) return 0   ;
  return xcvideo->NameUuid(index) ;
}

SUID N::XcitySeeker::CompanyUuid(void)
{
  if (IsNull(xcorganization)) return 0 ;
  return xcorganization->CompanyUuid() ;
}

QString N::XcitySeeker::CompanyPath(QString name)
{
  if (IsNull(xcorganization)) return "" ;
  QString ip = xcorganization->Search() ;
  return QString(ip).arg(name)          ;
}

QString N::XcitySeeker::CompanySpot(void)
{
  if (IsNull(xcorganization)) return "" ;
  return xcorganization->CompanySpot()  ;
}

bool N::XcitySeeker::prepare(void)
{
  CUIDs IDs                                                    ;
  int   id                                                     ;
  //////////////////////////////////////////////////////////////
  IDs << Types :: People                                       ;
  IDs << Types :: Video                                        ;
  IDs << Types :: Organization                                 ;
  //////////////////////////////////////////////////////////////
  foreach ( id , IDs )                                         {
    if (Widgets.contains(id))                                  {
      switch (id)                                              {
        case Types::People                                     :
          xcpeople       -> prepare ( )                        ;
        break                                                  ;
        case Types::Video                                      :
          xcvideo        -> prepare ( )                        ;
        break                                                  ;
        case Types::Organization                               :
          xcorganization -> prepare ( )                        ;
        break                                                  ;
      }                                                        ;
    }                                                          ;
  }                                                            ;
  //////////////////////////////////////////////////////////////
  return true                                                  ;
}

bool N::XcitySeeker::configure(QString scope)
{
  CUIDs IDs                                                           ;
  int   id                                                            ;
  /////////////////////////////////////////////////////////////////////
  IDs << Types :: People                                              ;
  IDs << Types :: Video                                               ;
  IDs << Types :: Organization                                        ;
  /////////////////////////////////////////////////////////////////////
  foreach ( id , IDs )                                                {
    if (Widgets.contains(id))                                         {
      switch (id)                                                     {
        case Types::People                                            :
          xcpeople       -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                         ;
        case Types::Video                                             :
          xcvideo        -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                         ;
        case Types::Organization                                      :
          xcorganization -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                         ;
      }                                                               ;
    }                                                                 ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                                    ;
  if (SC.open("XcitySeeker","configure"))                             {
    LearnSite :: Initialize ( SC )                                    ;
    SC . close              (    )                                    ;
  }                                                                   ;
  SC.remove()                                                         ;
  /////////////////////////////////////////////////////////////////////
  return true                                                         ;
}

bool N::XcitySeeker::startup(int type)
{
  switch ( type )              {
    case Types::People         :
    return RunPeople       ( ) ;
    case Types::Video          :
    return RunVideo        ( ) ;
    case Types::Organization   :
    return RunOrganization ( ) ;
  }                            ;
  return false                 ;
}

QString N::XcitySeeker::XcityImageSrc(QByteArray & XML,QString found)
{
  int index = XML.indexOf(found.toUtf8())       ;
  if (index<=0) return ""                       ;
  found = "<img src="                           ;
  index = XML.indexOf(found.toUtf8(),index)     ;
  if (index<=0) return ""                       ;
  index = XML.indexOf("\"",index)               ;
  int endix = XML.indexOf("?",index+1)          ;
  if (endix<=0) return ""                       ;
  QByteArray S = XML.mid(index+1,endix-index-1) ;
  return QString::fromUtf8(S)                   ;
}

QString N::XcitySeeker::XcityPeopleSrc(QByteArray & XML,QString found)
{
  int index = XML.indexOf(found.toUtf8())                    ;
  if (index<=0) return ""                           ;
  ///////////////////////////////////////////////////
  RangeInt range                                    ;
  range . L = index                                 ;
  if (!Between(range,"<h2>","</h2>",XML)) return "" ;
  ///////////////////////////////////////////////////
  int bndix = XML . indexOf ( "(" , range . L + 1 ) ;
  if ( bndix < range . R ) range . R  = bndix       ;
  ///////////////////////////////////////////////////
  QString R = Between ( range , XML )               ;
  if (R.length()>20) return ""                      ;
  return R                                          ;
}

QStringList N::XcitySeeker::XcityPeoples(QByteArray & XML,QString found)
{
  QStringList Ps                                    ;
  int index = XML.indexOf(found.toUtf8())                    ;
  if (index<=0) return Ps                           ;
  ///////////////////////////////////////////////////
  RangeInt range                                    ;
  range . L = index                                 ;
  if (!Between(range,"<h2>","</h2>",XML)) return Ps ;
  ///////////////////////////////////////////////////
  QStringList Rs                                    ;
  QString     N = Between ( range , XML )           ;
  ///////////////////////////////////////////////////
  N  = N . replace ( "(" , " " )                    ;
  N  = N . replace ( ")" , " " )                    ;
  N  = N . replace ( "," , " " )                    ;
  N  = N . replace ( "[" , " " )                    ;
  N  = N . replace ( "]" , " " )                    ;
  ///////////////////////////////////////////////////
  Rs = N . split   ( ' '       )                    ;
  ///////////////////////////////////////////////////
  foreach ( N , Rs )                                {
    if ( (N.length() >  0) && ! N.contains(' ')   ) {
      if (N.length() < 20) Ps << N                  ;
    }                                               ;
  }                                                 ;
  ///////////////////////////////////////////////////
  return Ps                                         ;
}

QString N::XcitySeeker::MeasureString(QString SRC,int index)
{
  QString ML                             ;
  for (int i=index+1;i<SRC.length();i++) {
    QChar c = SRC.at(i)                  ;
    if (c>=QChar('0') && c<=QChar('9'))  {
      ML . append ( c )                  ;
    } else return ML                     ;
  }                                      ;
  return ML                              ;
}

QString N::XcitySeeker::XcityProduct(QString product)
{
  int l = product . length ( ) - 1                          ;
  while ( l >= 0 && product . at ( l ) . isNumber ( ) ) l-- ;
  if ( ( l >= 0 ) && ( ( l + 2 ) < product . length ( ) ) ) {
    product . insert ( l + 1 , QChar('-') )                 ;
  }                                                         ;
  return product                                            ;
}

bool N::XcitySeeker::XcityDvdInfo (
       QByteArray & XML           ,
       KMAPs      & INFOs         ,
       int        & index         ,
       NAMEs      & References    )
{
  QString found = VideoInfo ( )                       ;
  /////////////////////////////////////////////////////
  INFOs  . clear         (       )                    ;
  index  = XML . indexOf ( found.toUtf8() )                    ;
  if (index<0) return false                           ;
  /////////////////////////////////////////////////////
  found  = "<span id=\"program_detail_title\">"       ;
  index  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (index<0) return false                           ;
  /////////////////////////////////////////////////////
  int endix                                           ;
  index += found.length()                             ;
  found  = "</span>"                                  ;
  endix  = XML . indexOf ( found.toUtf8() , index     )        ;
  if (endix<0) return false                           ;
  /////////////////////////////////////////////////////
  QByteArray B                                        ;
  B = XML . mid ( index , endix - index )             ;
  if (B.size()<=0) return false                       ;
  INFOs [ "title" ] = QString :: fromUtf8 ( B )       ;
  index  = endix + found.length()                     ;
  /////////////////////////////////////////////////////
  found = "<div class=\"subTitle\">"                  ;
  if (XML.indexOf(found.toUtf8(),index+1)>0)                   {
    found = "<p class=\"rearSub\">"                   ;
    int sid = XML.indexOf(found.toUtf8(),index+1)              ;
    if (sid>0)                                        {
      sid  += found.length()                          ;
      found = "</p>"                                  ;
      int eid = XML.indexOf(found.toUtf8(),sid+1)              ;
      if (eid>0)                                      {
        B = XML.mid( sid , eid - sid )                ;
        INFOs [ "subtitle" ] = QString::fromUtf8(B)   ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  /////////////////////////////////////////////////////
  found  = "<a href=\""                               ;
  index  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (index<0) return false                           ;
  index  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (index<0) return false                           ;
  index  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (index<0) return false                           ;
  index += found.length()                             ;
  found  = "\""                                       ;
  endix  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (endix<0) return false                           ;
  B = XML . mid ( index , endix - index )             ;
  INFOs [ "image" ] = QString :: fromUtf8 ( B )       ;
  index  = endix + found.length()                     ;
  /////////////////////////////////////////////////////
  found  = References [ 0 ]                           ; // 32 - Release date , References [ 0 ]
  endix  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (endix>0)                                        {
    found  = "</span>"                                ;
    endix  = XML . indexOf ( found.toUtf8() , endix + 1 )      ;
    if (endix>0)                                      {
      int sid = endix + found.length()                ;
      found = "</li>"                                 ;
      endix = XML . indexOf ( found.toUtf8() , sid )           ;
      if (endix>0)                                    {
        B = XML . mid ( sid , endix - sid )           ;
        QString sss = QString::fromUtf8(B)            ;
        sss = sss.replace("\t","")                    ;
        sss = sss.replace("\r","")                    ;
        sss = sss.replace("\n","")                    ;
        sss = PurgeSpace (sss    )                    ;
        INFOs [ "Release" ] = sss                     ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  /////////////////////////////////////////////////////
  found  = "<li id=\"program_detail_credit\">"        ; // 34 - Actress
  endix  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (endix>0)                                        {
    int sid                                           ;
    endix += found.length()                           ;
    found  = "</li>"                                  ;
    sid    = XML . indexOf ( found.toUtf8() , endix )          ;
    if (sid>0)                                        {
      QStringList IDs                                 ;
      B = XML . mid ( endix , sid - endix )           ;
      QString s = QString::fromUtf8(B)                ;
      index = sid + 1                                 ;
      found = "<a href=\"/avod/idol/detail/?id="      ;
      sid = 0                                         ;
      while (sid>=0)                                  {
        sid = s.indexOf(found.toUtf8(),sid)                    ;
        if (sid>=0)                                   {
          sid += found.length()                       ;
          int eid = s.indexOf("\"",sid)               ;
          if (eid>0)                                  {
            QString m = s.mid(sid,eid-sid)            ;
            sid = eid + 1                             ;
            if (m.length()>0) IDs << m                ;
          } else sid = -1                             ;
        }                                             ;
      }                                               ;
      if (IDs.count()>0)                              {
        INFOs [ "Actress" ] = IDs.join(" ")           ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  /////////////////////////////////////////////////////
  found  = "<span id=\"program_detail_maker_name\">"  ;
  endix  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (endix>0)                                        {
    int sid                                           ;
    endix += found.length()                           ;
    found  = "</span>"                                ;
    sid    = XML . indexOf ( found.toUtf8() , endix )          ;
    if (sid>0)                                        {
      B = XML . mid ( endix , sid - endix )           ;
      QString s = QString::fromUtf8(B)                ;
      if (s.length()>0)                               {
        index = sid + 1                               ;
        INFOs [ "Maker" ] = s                         ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  /////////////////////////////////////////////////////
  found  = "<p class=\"lead\">"                       ;
  endix  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (endix>0)                                        {
    int sid                                           ;
    endix += found.length()                           ;
    found  = "</p>"                                   ;
    sid    = XML . indexOf ( found.toUtf8() , endix )          ;
    if (sid>0)                                        {
      B = XML . mid ( endix , sid - endix )           ;
      QString s = QString::fromUtf8(B)                ;
      if (s.length()>0)                               {
        index = sid + 1                               ;
        INFOs [ "Content" ] = s                       ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  /////////////////////////////////////////////////////
  found  = References [ 1 ]                           ; // 33 - SKU , References [ 1 ]
  endix  = XML . indexOf ( found.toUtf8() , index + 1 )        ;
  if (endix>0)                                        {
    found  = "</span>"                                ;
    endix  = XML . indexOf ( found.toUtf8() , endix + 1 )      ;
    if (endix>0)                                      {
      int sid = endix + found.length()                ;
      found = "</li>"                                 ;
      endix = XML . indexOf ( found.toUtf8() , sid )           ;
      if (endix>0)                                    {
        index = endix + found.length()                ;
        B = XML . mid ( sid , endix - sid )           ;
        QString sss = QString::fromUtf8(B)            ;
        sss = sss.replace  ( "\t" , "" )              ;
        sss = sss.replace  ( "\r" , "" )              ;
        sss = sss.replace  ( "\n" , "" )              ;
        sss = PurgeSpace   ( sss       )              ;
        sss = XcityProduct ( sss       )              ;
        INFOs [ "SKU" ] = sss                         ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  /////////////////////////////////////////////////////
  if (!INFOs.contains("Release"))                     {
    found  = References [ 2 ]                         ; // 35 - Distribution , References [ 2 ]
    endix  = XML . indexOf ( found.toUtf8() , index + 1 )      ;
    if (endix>0)                                      {
      found  = "</span>"                              ;
      endix  = XML . indexOf ( found.toUtf8() , endix + 1 )    ;
      if (endix>0)                                    {
        int sid = endix + found.length()              ;
        found = "</li>"                               ;
        endix = XML . indexOf ( found.toUtf8() , sid )         ;
        if (endix>0)                                  {
          index = endix + found.length()              ;
          B = XML . mid ( sid , endix - sid )         ;
          QString sss = QString::fromUtf8(B)          ;
          sss = sss.replace  ( "\t" , "" )            ;
          sss = sss.replace  ( "\r" , "" )            ;
          sss = sss.replace  ( "\n" , "" )            ;
          sss = PurgeSpace   ( sss       )            ;
          INFOs [ "Release" ] = sss                   ;
        }                                             ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  /////////////////////////////////////////////////////
  return true                                         ;
}

QStringList N::XcitySeeker::XcityDvdURLs(QByteArray & XML,int & index)
{
  QStringList Sections                                 ;
  QStringList URLs                                     ;
  QString     gravure = "<div class=\"gravureScene\">" ;
  QString     scene   = "<div class=\"photoScene\">"   ;
  QString     div     = "</div>"                       ;
  QString     ref     = "<a href=\""                   ;
  QString     S                                        ;
  int         gid                                      ;
  int         sid                                      ;
  int         eid                                      ;
  //////////////////////////////////////////////////////
  gid = XML . indexOf ( gravure.toUtf8() , index )              ;
  sid = XML . indexOf ( scene  .toUtf8() , index )              ;
  if (gid<0 && sid<0) return URLs                      ;
  //////////////////////////////////////////////////////
  if (gid>0)                                           {
    gid = index                                        ;
    do                                                 {
      gid = XML . indexOf ( gravure.toUtf8() , gid )            ;
      if (gid>0)                                       {
        gid += gravure.length()                        ;
        eid  = XML . indexOf ( div.toUtf8() , gid )             ;
        if (eid>0)                                     {
          QByteArray B = XML.mid(gid,eid-gid)          ;
          Sections << QString::fromUtf8(B)             ;
          gid = eid + div.length()                     ;
        } else gid = -1                                ;
      }                                                ;
    } while (gid>0)                                    ;
  }                                                    ;
  //////////////////////////////////////////////////////
  if (sid>0)                                           {
    sid = index                                        ;
    do                                                 {
      sid = XML . indexOf ( scene.toUtf8() , sid )              ;
      if (sid>0)                                       {
        sid += scene.length()                          ;
        eid  = XML . indexOf ( div.toUtf8() , sid )             ;
        if (eid>0)                                     {
          QByteArray B = XML.mid(sid,eid-sid)          ;
          Sections << QString::fromUtf8(B)             ;
          sid = eid + div.length()                     ;
        } else sid = -1                                ;
      }                                                ;
    } while (sid>0)                                    ;
  }                                                    ;
  //////////////////////////////////////////////////////
  if (Sections.count()<=0) return URLs                 ;
  //////////////////////////////////////////////////////
  foreach (S,Sections)                                 {
    int p = S.indexOf(ref.toUtf8())                             ;
    if (p>0)                                           {
      p += ref.length()                                ;
      int e = S.indexOf("\"",p)                        ;
      if (e>0)                                         {
        QString u = S.mid(p,e-p)                       ;
        if (u.contains(".jpg",Qt::CaseInsensitive))    {
          URLs << u                                    ;
        } else
        if (u.contains(".gif",Qt::CaseInsensitive))    {
          URLs << u                                    ;
        } else
        if (u.contains(".png",Qt::CaseInsensitive))    {
          URLs << u                                    ;
        }                                              ;
      }                                                ;
    }                                                  ;
  }                                                    ;
  return URLs                                          ;
}

bool N::XcitySeeker::UpdateXcity  (
       SqlConnection & SC         ,
       int             PornstarId ,
       SUID            nuid       ,
       QString         name       )
{
  QString Q                                   ;
  Q = SC.sql.ReplaceInto                      (
        "xcityjp"                             ,
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

bool N::XcitySeeker::UpdateXcityDvd (
       SqlConnection & SC           ,
       int             VideoId      ,
       SUID            puid         ,
       QString         name         )
{
  QString Q                               ;
  Q = SC.sql.ReplaceInto                  (
        "xcityjpdvd"                      ,
        3                                 ,
        "id"                              ,
        "uuid"                            ,
        "name"                          ) ;
  SC . Prepare ( Q                      ) ;
  SC . Bind    ( "id"   , VideoId       ) ;
  SC . Bind    ( "uuid" , puid          ) ;
  SC . Bind    ( "name" , name.toUtf8() ) ;
  return SC . Exec (                    ) ;
}

bool N::XcitySeeker::BindPeople (
       SqlConnection & SC       ,
       SUID            people   ,
       QString         name     ,
       QString         found    ,
       QByteArray    & XML      )
{
  int index = XML.indexOf(found.toUtf8())                                         ;
  if (index<=0) return false                                             ;
  QStringList INS                                                        ;
  QStringList LLL                                                        ;
  QString     QQQ                                                        ;
  SUID        tuid = 0                                                   ;
  UUIDs TUIDs = Subordination                                            (
                  SC                                                     ,
                  people                                                 ,
                  Types  :: People                                       ,
                  Types  :: History                                      ,
                  Groups :: Subordination                                ,
                  SC.OrderByAsc("position")                            ) ;
  if (TUIDs.count()>0)                                                   {
    tuid = GetHistoryType                                                (
             SC                                                          ,
             TUIDs                                                       ,
             History::PeopleBirth                                      ) ;
  }                                                                      ;
  found = "<dd><span class=\"koumoku\">"                                 ;
  do                                                                     {
    index = XML.indexOf(found.toUtf8(),index+1)                                   ;
    if (index>0)                                                         {
      int endix = XML.indexOf("</dd>",index+1)                           ;
      if (endix>0)                                                       {
        QByteArray M = XML.mid(index,endix-index)                        ;
        INS << QString::fromUtf8(M)                                      ;
      } else index = -1                                                  ;
    }                                                                    ;
  } while (index>0)                                                      ;
  if (INS.count()<=0) return false                                       ;
  foreach (QQQ,INS)                                                      {
    QQQ = QQQ.replace(found,"")                                          ;
    LLL = QQQ.split("</span>")                                           ;
    if (LLL.count()==2)                                                  {
      if ( LLL [ 1 ] . contains ( " " )                                 &&
           LLL [ 1 ] . contains ( 'B' )                                 &&
           LLL [ 1 ] . contains ( 'W' )                                 &&
           LLL [ 1 ] . contains ( 'H' )                                ) {
        QStringList BWH = LLL[1].split(' ')                              ;
        QString     bwh                                                  ;
        showMessage ( tr("Body measurement [%1]").arg(LLL[1]) )          ;
        foreach (bwh,BWH)                                                {
          int idx                                                        ;
          QString ML                                                     ;
          if (bwh.contains('B'))                                         {
            idx = bwh.indexOf('B')                                       ;
            if (idx>=0)                                                  {
              ML = MeasureString(bwh,idx)                                ;
              if (ML.length()>0)                                         {
                assureVariable(SC,people,Types::People,"Bust",ML)        ;
              }                                                          ;
            }                                                            ;
          } else
          if (bwh.contains('W'))                                         {
            idx = bwh.indexOf('W')                                       ;
            if (idx>=0)                                                  {
              ML = MeasureString(bwh,idx)                                ;
              if (ML.length()>0)                                         {
                assureVariable(SC,people,Types::People,"Waist",ML)       ;
              }                                                          ;
            }                                                            ;
          } else
          if (bwh.contains('H'))                                         {
            idx = bwh.indexOf('H')                                       ;
            if (idx>=0)                                                  {
              ML = MeasureString(bwh,idx)                                ;
              if (ML.length()>0)                                         {
                assureVariable ( SC,people,Types::People,"Hip",ML)       ;
              }                                                          ;
            }                                                            ;
          }                                                              ;
        }                                                                ;
      } else
      if (LLL[0].length()==2 && LLL[1].contains("cm"))                   {
        QString HHH = LLL[1].left(3)                                     ;
        showMessage    ( tr("Body height [%1]").arg(LLL[1])            ) ;
        assureVariable ( SC , people , Types::People , "Height" , HHH  ) ;
      } else
      if (  LLL [ 0 ] . length   (     ) == 3                           &&
          ( LLL [ 1 ] . contains ( 'A' )                                ||
            LLL [ 1 ] . contains ( 'B' )                                ||
            LLL [ 1 ] . contains ( 'O' )                             ) ) {
        QString Blood                                                    ;
        if (LLL[1].contains("AB"))                                       {
          Blood = "AB"                                                   ;
        } else
        if (LLL[1].contains("A"))                                        {
          Blood = "A"                                                    ;
        } else
        if (LLL[1].contains("B"))                                        {
          Blood = "B"                                                    ;
        } else
        if (LLL[1].contains("O"))                                        {
          Blood = "O"                                                    ;
        }                                                                ;
        if (Blood.length()>0)                                            {
          showMessage ( tr("Blood type [%1]").arg(Blood) )               ;
          assureVariable(SC,people,Types::People,"Blood",Blood)          ;
        }                                                                ;
      } else
      if (LLL[0].length()==4 && LLL[1].length()>8)                       {
        QString Y = LLL[1].left(4)                                       ;
        QString M = LLL[1].mid(5,2)                                      ;
        QString D = LLL[1].mid(8,2)                                      ;
        int     y = Y.toInt()                                            ;
        int     m = M.toInt()                                            ;
        int     d = D.toInt()                                            ;
        QDate   DT(y,m,d)                                                ;
        if (DT.isValid())                                                {
          StarDate  SD                                                   ;
          QTime     TT ( 21 , 0 , 0 )                                    ;
          QDateTime BD                                                   ;
          BD . setDate ( DT )                                            ;
          BD . setTime ( TT )                                            ;
          SD = BD                                                        ;
          showMessage (    tr ( "[%1] Birthday [%2] = %3"                )
                        . arg ( name                                     )
                        . arg ( BD.toString("yyyy/MM/dd hh:mm:ss")       )
                        . arg ( SD.Stardate                          ) ) ;
          SUID ouid = tuid                                               ;
          tuid = assureTime                                              (
                   SC                                                    ,
                   tuid                                                  ,
                   History::PeopleBirth                                  ,
                   SD.Stardate                                         ) ;
          if (ouid<=0 && tuid>0)                                         {
            UUIDs ZUIDs                                                  ;
            ZUIDs << tuid                                                ;
            Join                                                         (
              SC                                                         ,
              people                                                     ,
              Types  :: People                                           ,
              Types  :: History                                          ,
              Groups :: Subordination                                    ,
              0                                                          ,
              ZUIDs                                                    ) ;
          }                                                              ;
        }                                                                ;
      } else                                                             {
        showMessage ( tr("Information[%1]=%2").arg(LLL[0]).arg(LLL[1]) ) ;
      }                                                                  ;
    }                                                                    ;
  }                                                                      ;
  return true                                                            ;
}

bool N::XcitySeeker::RunPeople(void)
{
  int      IDX        = -1                                                   ;
  qint64   LocalValue =  0                                                   ;
  bool     LocalGo    = true                                                 ;
  qint64 * Value      = NULL                                                 ;
  bool   * Go         = NULL                                                 ;
  bool     done       = false                                                ;
  ////////////////////////////////////////////////////////////////////////////
  IDX = Seeker -> ID ( )                                                       ;
  if (IDX<0)                                                                   {
    IDX   = plan->Progress                                                     (
              tr("X City People seeker")                                       ,
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
  if (SC.open("XcityPeopleSeeker","Source"))                                   {
  if (HC.open("XcityPeopleSeeker","Hunter"))                                   {
    (*Value) = PeopleStart ( )                                                 ;
    plan -> Start    ( IDX , Value         , Go          )                     ;
    plan -> setRange ( IDX , PeopleStart() , PeopleEnd() )                     ;
    Time :: skip     ( 300                               )                     ;
    ////////////////////////////////////////////////////////////////////////////
    QString Q                                                                  ;
    CUIDs   Existing                                                           ;
    Q = HC.sql.SelectFrom                                                      (
          "id"                                                                 ,
          "xcityjp"                                                            ,
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
      QString path = IdPattern ( PornstarId )                                  ;
      LookUrl ( path )                                                         ;
      plan -> ProgressText ( IDX , path )                                      ;
      DoProcessEvents                                                          ;
      //////////////////////////////////////////////////////////////////////////
      QUrl       u ( path )                                                    ;
      QByteArray XML                                                           ;
      SUID       puid = 0                                                      ;
      Obtain ( SC , u , puid , XML )                                           ;
      //////////////////////////////////////////////////////////////////////////
      if (XML.size()>0)                                                        {
        showMessage ( tr("Size : %1").arg(XML.size()) )                        ;
        if ( XML . indexOf ( IdFound ( ).toUtf8() ) >= 0 )                     {
          QStringList PeopleNames                                              ;
          QString     imgsrc                                                   ;
          QString     name                                                     ;
          QString     m                                                        ;
          name        = XcityPeopleSrc ( XML , IdFound ( ) )                   ;
          imgsrc      = XcityImageSrc  ( XML , IdFound ( ) )                   ;
          PeopleNames = XcityPeoples   ( XML , IdFound ( ) )                   ;
          if (name.length()>0)                                                 {
            Available = true                                                   ;
            m = tr("`%1`(%2) has information").arg(name).arg(PornstarId)       ;
            showMessage ( m )                                                  ;
            if (imgsrc=="/imgsrc/wp-content/themes/xcity-ja/img/noimage.gif")  {
              imgsrc = ""                                                      ;
            }                                                                  ;
            ////////////////////////////////////////////////////////////////////
            SUID nuid = FindPeople ( SC , name )                               ;
            if (nuid<=0)                                                       {
              showMessage ( tr("%1 is a new pornstar").arg(name) )             ;
              addPeople         ( SC , 2726 , name )                           ;
              nuid = FindPeople ( SC , name        )                           ;
              if (NewbieUuid()>0 && nuid>0)                                    {
                UUIDs NewPeople                                                ;
                NewPeople << nuid                                              ;
                Join                                                           (
                  SC                                                           ,
                  NewbieUuid()                                                 ,
                  N::Types::Division                                           ,
                  N::Types::People                                             ,
                  N::Groups::Subordination                                     ,
                  0                                                            ,
                  NewPeople                                                  ) ;
              }                                                                ;
            }                                                                  ;
            ////////////////////////////////////////////////////////////////////
            if (nuid>0 && imgsrc.length()>0)                                   {
              showMessage          (       imgsrc )                            ;
              plan -> ProgressText ( IDX , imgsrc )                            ;
              QUrl xurl ( imgsrc )                                             ;
              AttachPeople ( SC , xurl , nuid , name , GalleryUuid() )         ;
            }                                                                  ;
            if (nuid>0)                                                        {
              BindPeople ( SC , nuid , name , IdFound() , XML )                ;
              if (PeopleNames.count()>1)                                       {
                MergePeople(SC,MergerUuid(),nuid,PeopleNames,2726)             ;
              }                                                                ;
              UpdateXcity(HC,PornstarId,nuid,name)                             ;
            }                                                                  ;
            ////////////////////////////////////////////////////////////////////
          }                                                                    ;
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

bool N::XcitySeeker::Fetch(SqlConnection & SC,QUrl u,SUID & puid,QByteArray & XML)
{
  if ( VideoCache ( )      ) hadCached ( SC , u , puid , XML ) ;
  if ( XML . size ( ) <= 0 ) Obtain    ( SC , u , puid , XML ) ;
  return                               ( XML . size ( ) > 0  ) ;
}

bool N::XcitySeeker::RunVideo(void)
{
  NAMEs  Release                                                               ;
  NAMEs  Actress                                                               ;
  NAMEs  Product                                                               ;
  NAMEs  SKU                                                                   ;
  NAMEs  Penetration                                                           ;
  NAMEs  InfoMaps                                                              ;
  int    IDX        = -1                                                       ;
  qint64 LocalValue =  0                                                       ;
  bool   LocalGo    = true                                                     ;
  qint64 * Value      = NULL                                                     ;
  bool * Go         = NULL                                                     ;
  bool   done       = false                                                    ;
  //////////////////////////////////////////////////////////////////////////////
  IDX = Seeker -> ID ( )                                                       ;
  if (IDX<0)                                                                   {
    IDX   = plan->Progress                                                     (
              tr("X City Video seeker")                                        ,
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
  if (SC.open("XcityVideoSeeker","Source"))                                    {
  if (HC.open("XcityVideoSeeker","Hunter"))                                    {
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
    CMAPs   XcityPorn                                                          ;
    NAMEs   XcityName                                                          ;
    CUIDs   Existing                                                           ;
    Q = HC.sql.SelectFrom                                                      (
          "id,uuid,name"                                                       ,
          "xcityjp"                                                            ,
          HC.OrderByAsc("id")                                                ) ;
    SqlLoopNow ( HC , Q )                                                      ;
      XcityPorn [ HC . Int  ( 0 ) ] = HC.Uuid  (1)                             ;
      XcityName [ HC . Uuid ( 1 ) ] = HC.String(2)                             ;
    SqlLoopErr ( HC , Q )                                                      ;
    SqlLoopEnd ( HC , Q )                                                      ;
    Q = HC.sql.SelectFrom                                                      (
          "id"                                                                 ,
          "xcityjpdvd"                                                         ,
          HC.OrderByAsc("id")                                                ) ;
    SqlLoopNow ( HC , Q )                                                      ;
      Existing << HC . Int ( 0 )                                               ;
    SqlLoopErr ( HC , Q )                                                      ;
    SqlLoopEnd ( HC , Q )                                                      ;
    ////////////////////////////////////////////////////////////////////////////
    while ( ! done )                                                           {
      plan -> setRange ( IDX , VideoStart() , VideoEnd() )                     ;
      //////////////////////////////////////////////////////////////////////////
      int  VideoId   = *Value                                                  ;
      bool Available = false                                                   ;
      //////////////////////////////////////////////////////////////////////////
      if ( SkipVideo() )                                                       {
        if (Existing.contains(VideoId))                                        {
          if ( (*Value) >= VideoEnd ( ) ) done = true                          ;
                                     else (*Value)++                           ;
          Seeker -> ProgressGo = *Go                                           ;
          if ( ! Seeker -> runnable  ( ) ) done = true                         ;
          DoProcessEvents                                                      ;
          continue                                                             ;
        }                                                                      ;
      }                                                                        ;
      //////////////////////////////////////////////////////////////////////////
      QString path = VideoSearch ( VideoId )                                   ;
      LookUrl ( path )                                                         ;
      plan -> ProgressText ( IDX , path )                                      ;
      DoProcessEvents                                                          ;
      //////////////////////////////////////////////////////////////////////////
      QUrl       u ( path )                                                    ;
      QByteArray XML                                                           ;
      SUID       puid = 0                                                      ;
      Fetch ( SC , u , puid , XML )                                            ;
      //////////////////////////////////////////////////////////////////////////
      if (XML.size()>0)                                                        {
        showMessage ( tr("Size : %1").arg(XML.size()) )                        ;
        ////////////////////////////////////////////////////////////////////////
        if ( XML . indexOf ( VideoInfo ( ).toUtf8() ) >= 0 )                            {
          KMAPs INFOs                                                          ;
          int   position = 0                                                   ;
          if ( XcityDvdInfo ( XML , INFOs , position , InfoMaps )            ) {
            ////////////////////////////////////////////////////////////////////
            QStringList photos                                                 ;
            QString     title       = ""                                       ;
            QString     imgsrc      = ""                                       ;
            QString     product     = ""                                       ;
            SUID        ProductId   = 0                                        ;
            SUID        MakerId     = 0                                        ;
            QByteArray  body                                                   ;
            UUIDs       peoples                                                ;
            QDateTime   publish                                                ;
            bool        timeCorrect = false                                    ;
            ////////////////////////////////////////////////////////////////////
            photos = XcityDvdURLs(XML,position)                                ;
            if (INFOs.contains("title"))                                       {
              title    = INFOs["title"   ]                                     ;
            }                                                                  ;
            if (INFOs.contains("subtitle"))                                    {
              title   += " / "                                                 ;
              title   += INFOs["subtitle"]                                     ;
            }                                                                  ;
            if (INFOs.contains("image"))                                       {
              imgsrc   = INFOs["image"   ]                                     ;
            }                                                                  ;
            if (INFOs.contains("Maker"))                                       {
              MakerId   = FindCompany(SC,INFOs["Maker"])                       ;
            }                                                                  ;
            if (INFOs.contains("SKU"))                                         {
              product   = INFOs["SKU"   ]                                      ;
              product   = product.toUpper()                                    ;
              ProductId = FindIdentifier(SC,product)                           ;
            }                                                                  ;
            if (INFOs.contains("Content"))                                     {
              body     = INFOs["Content"].toUtf8()                             ;
            }                                                                  ;
            if (INFOs.contains("Actress"))                                     {
              QString     s = INFOs["Actress"]                                 ;
              QStringList l = s.split(' ')                                     ;
              foreach (s,l)                                                    {
                int pxid = s.toInt()                                           ;
                if ( XcityPorn.contains(pxid) && ( XcityPorn [ pxid ]  > 0 ) ) {
                  peoples << XcityPorn [ pxid ]                                ;
                }                                                              ;
              }                                                                ;
            }                                                                  ;
            ////////////////////////////////////////////////////////////////////
            showMessage ( "------------------------------------------------" ) ;
            showMessage ( tr("Video [%1]").arg(title  )                      ) ;
            showMessage ( imgsrc                                             ) ;
            for (int i=0;i<photos.count();i++) showMessage (  photos[i]      ) ;
            ////////////////////////////////////////////////////////////////////
            showMessage ( "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" ) ;
            if (ProductId>0)                                                   {
              QString pa                                                       ;
              pa = tr("Product [%1] = [%2]").arg(product).arg(ProductId)       ;
              showMessage ( pa                                               ) ;
            } else                                                             {
              showMessage ( tr("Product [%1]").arg(product)                  ) ;
            }                                                                  ;
            if (MakerId>0)                                                     {
              QString pa                                                       ;
              pa = tr("Maker [%1] = [%2]").arg(INFOs["Maker"]).arg(MakerId)    ;
              showMessage ( pa                                               ) ;
            }                                                                  ;
            if (INFOs.contains("Release"))                                     {
              QString   release                                                ;
              release  = INFOs["Release"   ]                                   ;
              if (DvdPublish(release,publish))                                 {
                QString ra                                                     ;
                ra = tr("Release [%1]").arg(publish.toString("yyyy/MM/dd hh:mm:ss")) ;
                showMessage ( ra )                                             ;
                timeCorrect = true                                             ;
              }                                                                ;
            }                                                                  ;
            if (INFOs.contains("Actress"))                                     {
              QString     s = INFOs["Actress"]                                 ;
              QStringList l = s.split(' ')                                     ;
              foreach (s,l)                                                    {
                int  id = s.toInt()                                            ;
                if ( XcityPorn.contains(id)  && ( XcityPorn [ id ]  > 0 ) )    {
                  SUID ud = XcityPorn[id]                                      ;
                  QString ma                                                   ;
                  ma = tr("Found [%1] = [%2]").arg(XcityName[ud]).arg(ud)      ;
                  showMessage ( ma )                                           ;
                }                                                              ;
              }                                                                ;
            }                                                                  ;
            ////////////////////////////////////////////////////////////////////
            showMessage ( "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" ) ;
            showMessage ( QString::fromUtf8(body)                            ) ;
            ////////////////////////////////////////////////////////////////////
            if (ProductId<=0)                                                  {
              ProductId = assureProduct ( SC , title , product , peoples )     ;
            }                                                                  ;
            ////////////////////////////////////////////////////////////////////
            SUID vuid = 0                                                      ;
            vuid = LookForVideo(SC,puid,product)                               ;
            if (vuid<=0)                                                       {
              QString content = QString::fromUtf8(body)                        ;
              SUID    duid    = 0                                              ;
              duid = assureDocument(SC,title,content)                          ;
              vuid = assureVideo(SC,title)                                     ;
              if (vuid>0)                                                      {
                UUIDs DUIDs                                                    ;
                DUIDs << duid                                                  ;
                Join                                                           (
                  SC                                                           ,
                  vuid                                                         ,
                  N::Types::Album                                              ,
                  N::Types::Document                                           ,
                  N::Groups::Subordination                                     ,
                  0                                                            ,
                  DUIDs                                                      ) ;
                if (ProductId>0)                                               {
                  Join                                                         (
                    SC                                                         ,
                    ProductId                                                  ,
                    N::Types::Commodity                                        ,
                    N::Types::Document                                         ,
                    N::Groups::Subordination                                   ,
                    0,DUIDs                                                  ) ;
                  DUIDs . clear ( )                                            ;
                  DUIDs << vuid                                                ;
                  Join                                                         (
                    SC                                                         ,
                    ProductId                                                  ,
                    N::Types::Commodity                                        ,
                    N::Types::Album                                            ,
                    N::Groups::Subordination                                   ,
                    0,DUIDs                                                  ) ;
                }                                                              ;
              }                                                                ;
            } else                                                             {
              UUIDs DUIDs                                                      ;
              DUIDs . clear ( )                                                ;
              DUIDs << vuid                                                    ;
              Join                                                             (
                SC                                                             ,
                ProductId                                                      ,
                N::Types::Commodity                                            ,
                N::Types::Album                                                ,
                N::Groups::Subordination                                       ,
                0,DUIDs                                                      ) ;
            }                                                                  ;
            if (vuid>0)                                                        {
              Join                                                             (
                SC                                                             ,
                vuid                                                           ,
                N::Types::Album                                                ,
                N::Types::People                                               ,
                N::Groups::Subordination                                       ,
                0                                                              ,
                peoples                                                      ) ;
              UUIDs ZUIDs                                                      ;
              ZUIDs << puid                                                    ;
              Join                                                             (
                SC                                                             ,
                vuid                                                           ,
                N::Types::Album                                                ,
                N::Types::URL                                                  ,
                N::Groups::Subordination                                       ,
                0                                                              ,
                ZUIDs                                                        ) ;
              JoinAlbum(SC,AlbumUuid(),vuid)                                   ;
              //////////////////////////////////////////////////////////////////
              QString wc = QString::fromUtf8(body)                             ;
              bool    match = false                                            ;
              for (int x=0;!match && x<Penetration.count();x++)                {
                QString cw = Penetration[x]                                    ;
                if (wc.contains(cw)) match = true                              ;
              }                                                                ;
              if (match)                                                       {
                JoinAlbum(SC,InterestUuid(),vuid)                              ;
              }                                                                ;
              //////////////////////////////////////////////////////////////////
              if (timeCorrect && publish.isValid())                            {
                SUID ttid = 0                                                  ;
                UUIDs TUIDs = Subordination                                    (
                                SC                                             ,
                                vuid                                           ,
                                N::Types::Album                                ,
                                N::Types::History                              ,
                                N::Groups::Subordination                       ,
                                SC.OrderByAsc("position")                    ) ;
              if (TUIDs.count()>0)                                             {
                ttid = GetHistoryType                                          (
                         SC                                                    ,
                         TUIDs                                                 ,
                         N::History::PublishDate                             ) ;
              }                                                                ;
              N::StarDate SD                                                   ;
              SD = publish                                                     ;
              SUID ouid = ttid                                                 ;
              ttid = assureTime                                                (
                       SC                                                      ,
                       ttid                                                    ,
                       N::History::PublishDate                                 ,
                       SD.Stardate                                           ) ;
              if (ouid<=0 && ttid>0)                                           {
                UUIDs XUIDs                                                    ;
                XUIDs << ttid                                                  ;
                Join                                                           (
                  SC                                                           ,
                  vuid                                                         ,
                  N::Types::Album                                              ,
                  N::Types::History                                            ,
                  N::Groups::Subordination                                     ,
                  0                                                            ,
                  XUIDs                                                      ) ;
                }                                                              ;
              }                                                                ;
              //////////////////////////////////////////////////////////////////
              QUrl purls(imgsrc)                                               ;
              AttachVideo(SC,purls,u,vuid,VideoGalleryUuid(),peoples)          ;
              if (photos.count()>0)                                            {
                for (int i=0;i<photos.count();i++)                             {
                  QUrl purlx(photos[i])                                        ;
                  AttachVideo(SC,purlx,u,vuid,VideoGalleryUuid(),peoples)      ;
                }                                                              ;
              }                                                                ;
              //////////////////////////////////////////////////////////////////
              if (ProductId>0 && vuid>0 && product.length()>0)                 {
                QString MN                                                     ;
                if (INFOs.contains("Maker")) MN = INFOs["Maker"]               ;
                AttachCompany (SC,product,ProductId,MakerId,MN,vuid,peoples)   ;
              }                                                                ;
              //////////////////////////////////////////////////////////////////
              UpdateXcityDvd ( HC , VideoId , puid , title )                   ;
              QString QQ                                                       ;
              QQ = HC.sql.Update                                               (
                    "xcityjpdvd"                                               ,
                    HC.sql.Where(1,"uuid")                                     ,
                    3                                                          ,
                    "video"                                                    ,
                    "commodity"                                                ,
                    "identifier"                                             ) ;
              HC . Prepare ( QQ                              )                 ;
              HC . Bind    ( "uuid"       , puid             )                 ;
              HC . Bind    ( "video"      , vuid             )                 ;
              HC . Bind    ( "commodity"  , ProductId        )                 ;
              HC . Bind    ( "identifier" , product.toUtf8() )                 ;
              HC . Exec    (                                 )                 ;
              //////////////////////////////////////////////////////////////////
              Available = true                                                 ;
            }                                                                  ;
          }                                                                    ;
        }                                                                      ;
        ////////////////////////////////////////////////////////////////////////
      }                                                                        ;
      //////////////////////////////////////////////////////////////////////////
      if (!Available)                                                          {
        showMessage ( tr("`%1` does not have information").arg(VideoId)      ) ;
      } else                                                                   {
        if (!Existing.contains(VideoId)) Existing << VideoId                   ;
      }                                                                        ;
      showMessage ( "======================================================" ) ;
      if ( (*Value) >= VideoEnd ( ) ) done = true                              ;
                                  else (*Value)++                              ;
      Seeker -> ProgressGo = *Go                                               ;
      if ( ! Seeker -> runnable  ( ) ) done = true                             ;
      DoProcessEvents                                                          ;
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

bool N::XcitySeeker::XcityCompany(QByteArray & XML,int index,QString & name,QString & logo)
{
  QByteArray B                      ;
  QString    HREF = "<a href="      ;
  QString    IMGS = "<img src="     ;
  int        Hindex                 ;
  int        Iindex                 ;
  Hindex = XML.indexOf(HREF.toUtf8(),index ) ;
  if (Hindex<0) return false        ;
  Iindex = XML.indexOf(IMGS.toUtf8(),Hindex) ;
  if (Iindex<0) return false        ;
  Hindex = XML.indexOf("\"",Iindex) ;
  if (Hindex<0) return false        ;
  Hindex++                          ;
  Iindex = XML.indexOf("\"",Hindex) ;
  if (Iindex<0) return false        ;
  ///////////////////////////////////
  B = XML.mid(Hindex,Iindex-Hindex) ;
  logo = QString::fromUtf8(B)       ;
  ///////////////////////////////////
  Iindex++                          ;
  Hindex = XML.indexOf("\"",Iindex) ;
  if (Hindex<0) return false        ;
  Hindex++                          ;
  Iindex = XML.indexOf("\"",Hindex) ;
  if (Iindex<0) return false        ;
  ///////////////////////////////////
  B = XML.mid(Hindex,Iindex-Hindex) ;
  name = QString::fromUtf8(B)       ;
  ///////////////////////////////////
  return true                       ;
}

bool N::XcitySeeker::RunOrganization(void)
{
  QStringList Lost                                                             ;
  QString     Hira       = Acoustics::Hiragana()                               ;
  int         L          = Hira.length()                                       ;
  int         IDX        = -1                                                  ;
  qint64         LocalValue =  0                                                  ;
  bool        LocalGo    = true                                                ;
  qint64       * Value      = NULL                                                ;
  bool      * Go         = NULL                                                ;
  //////////////////////////////////////////////////////////////////////////////
  if (L>48) L = 48                                                             ;
  IDX = Seeker -> ID ( )                                                       ;
  if (IDX<0)                                                                   {
    IDX   = plan->Progress                                                     (
              tr("X City Organization seeker")                                 ,
              tr("%v/%m")                                                    ) ;
    Value = & LocalValue                                                       ;
    Go    = & LocalGo                                                          ;
    Time :: skip ( 500 )                                                       ;
  } else                                                                       {
    Value = & ( Seeker -> ProgressValue )                                      ;
    Go    = & ( Seeker -> ProgressGo    )                                      ;
  }                                                                            ;
  //////////////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql           )                                     ;
  SqlConnection HC ( Seeker->HunterSql() )                                     ;
  if (SC.open("XcityOrganizationSeeker","Source"))                             {
  if (HC.open("XcityOrganizationSeeker","Hunter"))                             {
    ////////////////////////////////////////////////////////////////////////////
    QString Q                                                                  ;
    UUIDs   U                                                                  ;
    ////////////////////////////////////////////////////////////////////////////
    (*Value) = 0                                                               ;
    plan -> Start    ( IDX , Value , Go )                                      ;
    plan -> setRange ( IDX , 0     , L  )                                      ;
    Time :: skip     ( 300              )                                      ;
    ////////////////////////////////////////////////////////////////////////////
    U = Subordination                                                          (
          SC                                                                   ,
          CompanyUuid ( )                                                      ,
          Types  :: Division                                                   ,
          Types  :: Organization                                               ,
          Groups :: Subordination                                              ,
          SC      . OrderByAsc ( "position" )                                ) ;
    showMessage ( tr("Total %1 organizations").arg(U.count()))                 ;
    ////////////////////////////////////////////////////////////////////////////
    for (int i=0;Seeker->runnable() && i<L;i++)                                {
      QString path                                                             ;
      path = CompanyPath ( Hira.at(i) )                                        ;
      LookUrl      ( path )                                                    ;
      showMessage  ( path )                                                    ;
      //////////////////////////////////////////////////////////////////////////
      plan -> ProgressText ( IDX , path )                                      ;
      DoProcessEvents                                                          ;
      //////////////////////////////////////////////////////////////////////////
      QUrl       u ( path )                                                    ;
      QByteArray XML                                                           ;
      SUID       puid = 0                                                      ;
      Obtain ( SC , u , puid , XML )                                           ;
      //////////////////////////////////////////////////////////////////////////
      if ( ( XML.size() > 0 ) && ( XML . indexOf ( CompanySpot ( ).toUtf8() ) > 0 ) )   {
        showMessage ( tr("Size : %1").arg(XML.size()) )                        ;
        QString LOGO   = "<p class=\"logo\">"                                  ;
        QString NAME   = "<p class=\"name\">"                                  ;
        int     index  = XML . indexOf ( CompanySpot ( ).toUtf8() )                     ;
        bool    having = false                                                 ;
        do                                                                     {
          int Lindex                                                           ;
          int Nindex                                                           ;
          having = false                                                       ;
          Lindex = XML.indexOf(LOGO.toUtf8(),index)                                     ;
          if ( Lindex > index )                                                {
            Nindex = Lindex + LOGO.length()                                    ;
            Nindex = XML . indexOf ( NAME.toUtf8() , Nindex )                           ;
            if ( Nindex > Lindex )                                             {
              QString name                                                     ;
              QString logo                                                     ;
              if (XcityCompany(XML,Lindex,name,logo))                          {
                SUID cu = FindCompany(SC,name)                                 ;
                if ( ( cu > 0 ) && U.contains(cu) )                            {
                  QUrl url ( logo )                                            ;
                  showMessage ( tr("Have a company `%1`").arg(name) )          ;
                  showMessage ( tr("Icon at <%1>"       ).arg(logo) )          ;
                  showMessage ( tr("Company Uuid = %1"  ).arg(cu  ) )          ;
                  AttachOrganization ( SC , url , cu )                         ;
                } else                                                         {
                  showMessage ( "*********************************************" ) ;
                  showMessage ( "* " + tr("Company `%1` did not have record").arg(name) ) ;
                  showMessage ( "*********************************************" ) ;
                  Lost << name                                                 ;
                }                                                              ;
                showMessage ( "--------------------------------------------" ) ;
                having = true                                                  ;
              }                                                                ;
              index = XML.indexOf("</p>",Nindex)                               ;
            }                                                                  ;
          }                                                                    ;
        } while ( Seeker->runnable() && having )                               ;
      }                                                                        ;
      //////////////////////////////////////////////////////////////////////////
      showMessage ( "======================================================" ) ;
      DoProcessEvents                                                          ;
      Seeker -> ProgressGo = *Go                                               ;
      (*Value)++                                                               ;
    }                                                                          ;
    ////////////////////////////////////////////////////////////////////////////
    if ( Lost . count ( ) > 0 ) showMessage ( Lost . join ( "\n" ) )           ;
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
