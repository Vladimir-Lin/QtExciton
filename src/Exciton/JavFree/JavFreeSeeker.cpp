#include <exciton.h>

N::JavFree:: JavFree       ( QObject * parent , Plan * p )
           : SiteSeeker    (           parent ,        p )
           , jfvideo       ( NULL                        )
           , Proxying      ( false                       )
{
  Enabled [ Types :: People       ] = false ;
  Enabled [ Types :: Video        ] = true  ;
  Enabled [ Types :: Document     ] = false ;
  Enabled [ Types :: Organization ] = false ;
}

N::JavFree::~JavFree(void)
{
}

int N::JavFree::Type(void) const
{
  return 10004 ;
}

QString N::JavFree::Name(void) const
{
  return tr("Free JAV Share") ;
}

bool N::JavFree::Supported(int type) const
{
  switch ( type )              {
    case Types :: Video        :
    return true                ;
  }                            ;
  return false                 ;
}

QString N::JavFree::Name(int type) const
{
  switch ( type )                         {
    case Types :: Video                   :
    return tr("Free JAV Share - Video"  ) ;
  }                                       ;
  return ""                               ;
}

QWidget * N::JavFree::Configurator (int type)
{
  if (Widgets.contains(type)) return Widgets [ type ]      ;
  switch ( type )                                          {
    case Types :: Video                                    :
      jfvideo          = new JavFreeVideo  ( NULL , plan ) ;
      Widgets [ type ] = jfvideo                           ;
    return Widgets [ type ]                                ;
  }                                                        ;
  return NULL                                              ;
}

bool N::JavFree::setEnabled(int type,bool enable)
{
  switch ( type )               {
    case Types :: Video         :
      Enabled [ type ] = enable ;
    return Enabled [ type ]     ;
  }                             ;
  return false                  ;
}

bool N::JavFree::setOptions(Ftp & ftp)
{
  if (useProxy())                                 {
    ftp . Requests [ "Proxy" ] = ProxyAddress ( ) ;
  }                                               ;
  return false                                    ;
}

bool N::JavFree::useProxy(void)
{
  return Proxying ;
}

QString N::JavFree::ProxyAddress(void)
{
  QString PS                                  ;
  PS = QString ( "%1:%2"                      )
      . arg    ( Seeker -> ProxyAddress ( )   )
      . arg    ( Seeker -> ProxyPort    ( ) ) ;
  return PS                                   ;
}

bool N::JavFree::VideoSkip(void)
{
  if (IsNull(jfvideo)) return false ;
  return jfvideo->Skip()            ;
}

bool N::JavFree::VideoCache(void)
{
  if (IsNull(jfvideo)) return false ;
  return jfvideo->Cache()           ;
}

bool N::JavFree::DownloadOnly(void)
{
  if (IsNull(jfvideo)) return false ;
  return jfvideo->DownloadOnly()    ;
}

int N::JavFree::VideoStart(void)
{
  if (IsNull(jfvideo)) return 0 ;
  return jfvideo -> Start  ( )  ;
}

int N::JavFree::VideoEnd(void)
{
  if (IsNull(jfvideo)) return 0 ;
  return jfvideo -> Finish ( )  ;
}

SUID N::JavFree::AlbumUuid(void)
{
  if (IsNull(jfvideo)) return 0 ;
  return jfvideo->AlbumUuid()   ;
}

SUID N::JavFree::InterestUuid(void)
{
  if (IsNull(jfvideo)) return 0  ;
  return jfvideo->InterestUuid() ;
}

SUID N::JavFree::GalleryUuid(void)
{
  if (IsNull(jfvideo)) return 0 ;
  return jfvideo->GalleryUuid() ;
}

SUID N::JavFree::VideoNameMaps(int index)
{
  if (IsNull(jfvideo)) return 0   ;
  return jfvideo->NameUuid(index) ;
}

QString N::JavFree::Search(int index)
{
  if (index<=1) return "http://javfree.me"               ;
  return QString("http://javfree.me/page/%1").arg(index) ;
}

QString N::JavFree::GZipLocation(void)
{
  if (IsNull(jfvideo)) return "" ;
  return jfvideo->GZipLocation() ;
}

QString N::JavFree::Posting(void)
{
  if (IsNull(jfvideo)) return "" ;
  return jfvideo -> Posting ( )  ;
}

QString N::JavFree::Thumbnails(void)
{
  if (IsNull(jfvideo)) return ""   ;
  return jfvideo -> Thumbnails ( ) ;
}

bool N::JavFree::prepare(void)
{
  CUIDs IDs                       ;
  int   id                        ;
  /////////////////////////////////
  IDs << Types :: Video           ;
  /////////////////////////////////
  foreach ( id , IDs )            {
    if (Widgets.contains(id))     {
      switch (id)                 {
        case Types::Video         :
          jfvideo  -> prepare ( ) ;
        break                     ;
      }                           ;
    }                             ;
  }                               ;
  /////////////////////////////////
  return true                     ;
}

bool N::JavFree::configure(QString scope)
{
  CUIDs IDs                                                     ;
  int   id                                                      ;
  ///////////////////////////////////////////////////////////////
  IDs << Types :: Video                                         ;
  ///////////////////////////////////////////////////////////////
  foreach ( id , IDs )                                          {
    if (Widgets.contains(id))                                   {
      switch (id)                                               {
        case Types::Video                                       :
          jfvideo  -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                   ;
      }                                                         ;
    }                                                           ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                              ;
  if (SC.open("JavFree","configure"))                           {
    LearnSite :: Initialize ( SC )                              ;
    SC . close              (    )                              ;
  }                                                             ;
  SC.remove()                                                   ;
  ///////////////////////////////////////////////////////////////
  return true                                                   ;
}

bool N::JavFree::startup(int type)
{
  switch ( type )        {
    case Types::Video    :
    return RunVideo  ( ) ;
  }                      ;
  return false           ;
}

bool N::JavFree::ObtainPages(QByteArray & XML,QList<QUrl> & URLs)
{
  int index = XML . indexOf ( Posting ( ).toUtf8() )          ;
  if (index<0) return false                          ;
  QString  TN = Thumbnails ( )                       ;
  QString  U                                         ;
  int      p                                         ;
  RangeInt L                                         ;
  while ( ( p = XML . indexOf ( TN.toUtf8() , index ) ) > 0 ) {
    p += TN.length()                                 ;
    L . L = p                                        ;
    if ( Between ( L , "http://" , "\"" , XML ) )    {
      L . L -= 7                                     ;
      U      = Between ( L , XML )                   ;
      URLs << QUrl ( U )                             ;
      index = L . R                                  ;
    } else index = p                                 ;
  }                                                  ;
  return ( URLs.count() > 0 )                        ;
}

bool N::JavFree::isProduct(QString & product)
{
  product = product.replace("XXX-AV-","XXXAV-")  ;
  QStringList L = product.split('-')             ;
  if (L.count()!=2) return false                 ;
  int index                                      ;
  if ( "1000GIRI" == L[0].toUpper() )            {
    product = product.replace("1000GIRI","GIRI") ;
    index   = product.indexOf('-')               ;
    if (index>0)                                 {
      QString PN                                 ;
      index++                                    ;
      while (index<product.length()             &&
             product.at(index)>='0'             &&
             product.at(index)<='9'            ) {
        PN.append(product.at(index))             ;
        index++                                  ;
      }                                          ;
      if (PN.length()>0)                         {
        product = "GIRI-" + PN                   ;
      }                                          ;
    }                                            ;
    L = product.split('-')                       ;
  }                                              ;
  bool Okay = false                              ;
  L [ 1 ] . toInt ( &Okay )                      ;
  return Okay                                    ;
}

bool N::JavFree::Fetch(SqlConnection & SC,QUrl u,SUID & puid,QByteArray & XML)
{
  if ( VideoCache ( ) ) hadCached ( SC , u , puid , XML ) ;
  if ( XML.size ( ) <= 0 )                                {
    Proxying = jfvideo->isProxy ( )                       ;
    Obtain    ( SC , u , puid , XML )                     ;
    Proxying = false                                      ;
  }                                                       ;
  if ( XML.size ( ) > 0 ) Convert ( SC , XML , puid )     ;
  return ( XML.size() > 0 )                               ;
}

int N::JavFree::FetchTags (
      QByteArray & XML       ,
      int          index     ,
      NAMEs      & INFOs     ,
      KMAPs      & TAGs      )
{
  QByteArray B                                            ;
  QString    TitleTag  = "class=\"entry-title\"><a href=" ;
  QString    ButtonEnd = "<!-- AddThis Button END -->"    ;
  QString    imgclass  = "<img class=\"lazy\""            ;
  QString    Title     = ""                               ;
  int        endix     = -1                               ;
  int        idx       =  0                               ;
  /////////////////////////////////////////////////////////
  idx   = XML . indexOf ( TitleTag.toUtf8() , index )              ;
  if ( idx   < 0 ) return -1                              ;
  idx  += TitleTag . length ( )                           ;
  idx   = XML . indexOf ( ">" , idx + 1 )                 ;
  if ( idx   < 0 ) return -1                              ;
  idx  += 1                                               ;
  endix = XML . indexOf ( "<" , idx )                     ;
  if ( endix < 0 ) return -1                              ;
  /////////////////////////////////////////////////////////
  B     = XML . mid ( idx , endix - idx )                 ;
  Title = QString::fromUtf8(B)                            ;
  if (Title.at(0)=='[')                                   {
    idx = Title.indexOf("]")                              ;
    if (idx>0) Title . remove ( 0 , idx + 1 )             ;
  }                                                       ;
  while (Title.length()>0 && Title.at(0)==' ')            {
    Title . remove ( 0 , 1 )                              ;
  }                                                       ;
  if ( Title . length ( ) > 0 ) TAGs [ "Title" ] = Title  ;
  /////////////////////////////////////////////////////////
  endix += 1                                              ;
  /////////////////////////////////////////////////////////
  idx    = XML . indexOf ( ButtonEnd.toUtf8() , endix )            ;
  if ( idx   < 0 ) return -1                              ;
  idx   += ButtonEnd.length()                             ;
  endix  = XML . indexOf ( imgclass.toUtf8()  , idx   )            ;
  if ( endix < 0 ) return -1                              ;
  B     = XML . mid ( idx , endix - idx )                 ;
  /////////////////////////////////////////////////////////
  QString S = QString::fromUtf8(B)                        ;
  if (S.contains("<p>"))                                  {
    idx = S.indexOf("<p>",0)                              ;
    if ( idx >= 0 ) S . remove ( 0 , idx + 3 )            ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  QStringList L = S.split("<br />")                       ;
  QStringList R                                           ;
  QStringList E                                           ;
  QStringList I                                           ;
  foreach ( S , L )                                       {
    S = S . replace ( "<br />" , "" )                     ;
    S = S . replace ( "\n"     , "" )                     ;
    S = S . replace ( "\r"     , "" )                     ;
    if ( S . length ( ) > 0 )                             {
      if ( ! S . contains ( "href=" ) ) R << S            ;
                                   else E << S            ;
    }                                                     ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  foreach ( S , R )                                       {
    bool marked = false                                   ;
    ///////////////////////////////////////////////////////
    if ( ( ! marked ) && ( ! TAGs.contains("Actors" ) ) ) {
      for (int j=1100;!marked && j>=1000;j--)             {
        if (INFOs.contains(j))                            {
          QString ITF = INFOs[j]                          ;
          QString RTF = S.left(ITF.length())              ;
          if ( ITF == RTF )                               {
            S.remove(0,ITF.length())                      ;
            TAGs [ "Actors" ] = S                         ;
            marked            = true                      ;
          }                                               ;
        }                                                 ;
      }                                                   ;
    }                                                     ;
    ///////////////////////////////////////////////////////
    if ( ( ! marked ) && ( ! TAGs.contains("Release") ) ) {
      for (int j=2100;!marked && j>=2000;j--)             {
        if (INFOs.contains(j))                            {
          QString ITF = INFOs[j]                          ;
          QString RTF = S.left(ITF.length())              ;
          if ( ITF == RTF )                               {
            S.remove(0,ITF.length())                      ;
            TAGs [ "Release" ] = S                        ;
          }                                               ;
        }                                                 ;
      }                                                   ;
    }                                                     ;
    ///////////////////////////////////////////////////////
    if ( ! marked )                                       {
      QString Full = Pool[":"]                            ;
      if ( S.contains(":") || S.contains(Full) )          {
        QString HX                                        ;
        QString TX                                        ;
        bool    MX = false                                ;
        if (S.contains(":" ))                             {
          QStringList Z = S.split(":")                    ;
          if ( Z . count ( ) > 1 )                        {
            HX = Z [ 0 ]                                  ;
            TX = HX + ":"                                 ;
            MX = true                                     ;
          }                                               ;
        } else
        if (S.contains(Full))                             {
          QStringList Z = S.split(Full)                   ;
          if ( Z . count ( ) > 1 )                        {
            HX = Z [ 0 ]                                  ;
            TX = HX + Full                                ;
            MX = true                                     ;
          }                                               ;
        }                                                 ;
        ///////////////////////////////////////////////////
        if ( MX )                                         {
          S = S . replace ( TX , "" )                     ;
          while ( S.length() > 0 && S.at(0)==' ')         {
            S.remove(0,1)                                 ;
          }                                               ;
          HX = PurgeSpace ( HX )                          ;
          if ( S . length ( ) > 0 ) TAGs [ HX ] = S       ;
        } else I << S                                     ;
      } else                                              {
        I << S                                            ;
      }                                                   ;
    }                                                     ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  I << E                                                  ;
  for (int i=0;i<I.count();i++)                           {
    QString G = QString::number(i+1)                      ;
    TAGs [ G ] = I [ i ]                                  ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if ( TAGs . contains ( "Release") )                     {
    QString G = TAGs [ "Release" ]                        ;
    if (G.contains(":"))                                  {
      G = G.replace(":"," ")                              ;
    }                                                     ;
    if (G.contains(Pool[":"]))                            {
      G = G.replace(Pool[":"]," ")                        ;
    }                                                     ;
    if (G.contains(Pool[" "]))                            {
      G = G.replace(Pool[" "]," ")                        ;
    }                                                     ;
    G                  = PurgeSpace ( G )                 ;
    if ( G.contains(' ') )                                {
      int ued = G.indexOf(' ')                            ;
      if (ued>0) G = G.left(ued)                          ;
    }                                                     ;
    if ( G.contains('(') )                                {
      int ued = G.indexOf('(')                            ;
      if (ued>0) G = G.left(ued)                          ;
    }                                                     ;
    if (G.length()>0) TAGs [ "Release" ] = G ; else       {
      TAGs . take ( "Release" )                           ;
    }                                                     ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if ( TAGs . contains ( "Actors") )                      {
    QString G = TAGs [ "Actors" ]                         ;
    if (G.contains("\t"))                                 {
      G = G.replace("\t"," ")                             ;
    }                                                     ;
    if (G.contains(":"))                                  {
      G = G.replace(":"," ")                              ;
    }                                                     ;
    if (G.contains(QChar(0x3001)))                        {
      G = G.replace(QChar(0x3001)," ")                    ;
    }                                                     ;
    if (G.contains(Pool[":"]))                            {
      G = G.replace(Pool[":"]," ")                        ;
    }                                                     ;
    if (G.contains(Pool[" "]))                            {
      G = G.replace(Pool[" "]," ")                        ;
    }                                                     ;
    if (G.contains("----"))                               {
      G = G.replace("----","")                            ;
    }                                                     ;
    if (G.contains("---"))                                {
      G = G.replace("---","")                             ;
    }                                                     ;
    G                 = PurgeSpace ( G )                  ;
    G                 = G.replace("("      ," ")          ;
    G                 = G.replace(")"      ," ")          ;
    G                 = G.replace(","      ," ")          ;
    G                 = G.replace(Pool["("]," ")          ;
    G                 = G.replace(Pool[")"]," ")          ;
    G                 = G.replace(Pool[","]," ")          ;
    L                 = G.split(" ")                      ;
    I . clear ( )                                         ;
    foreach ( S , L )                                     {
      if ( S . length() > 0 ) I << S                      ;
    }                                                     ;
    if ( I.count() <= 0 ) TAGs.take("Actors") ; else      {
      G = I.join(" ")                                     ;
      TAGs [ "Actors" ] = G                               ;
    }                                                     ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  return 0                                                ;
}

int N::JavFree::FetchImages (
      QByteArray  & XML     ,
      int           index   ,
      QList<QUrl> & URLs    )
{
  QString imgclass     = "<img class=\"lazy\""              ;
  QString dataoriginal = "data-original=\""                 ;
  int endix = XML.indexOf(imgclass.toUtf8(),index)                   ;
  if ( endix <= 0 ) return -1                               ;
  ///////////////////////////////////////////////////////////
  QByteArray B                                              ;
  int idx = 0                                               ;
  int edx                                                   ;
  while ( ( idx = XML . indexOf ( imgclass.toUtf8() , idx ) ) >= 0 ) {
    idx  = XML . indexOf ( dataoriginal.toUtf8() , idx     )         ;
    if ( idx > 0 )                                          {
      idx += dataoriginal.length()                          ;
      edx  = XML . indexOf ( "\"" , idx + 1 )               ;
      if (edx>0)                                            {
        QByteArray U                                        ;
        U = XML . mid ( idx , edx - idx )                   ;
        QString AU = QString::fromUtf8(U)                   ;
        QUrl    UR ( AU )                                   ;
        URLs << UR                                          ;
        idx   = edx + 1                                     ;
        endix = idx                                         ;
      }                                                     ;
    } else break                                            ;
  }                                                         ;
  return endix                                              ;
}

bool N::JavFree::RunVideo(void)
{
  NAMEs       Release                                                                ;
  NAMEs       Actress                                                                ;
  NAMEs       Product                                                                ;
  NAMEs       SKU                                                                    ;
  NAMEs       Penetration                                                            ;
  NAMEs       InfoMaps                                                               ;
  QStringList NewAV                                                                  ;
  int         IDX        = -1                                                        ;
  qint64         LocalValue =  0                                                        ;
  bool        LocalGo    = true                                                      ;
  qint64       * Value      = NULL                                                      ;
  bool      * Go         = NULL                                                      ;
  bool        done       = false                                                     ;
  ////////////////////////////////////////////////////////////////////////////////////
  IDX = Seeker -> ID ( )                                                             ;
  if (IDX<0)                                                                         {
    IDX   = plan->Progress                                                           (
              tr("Free JAV Share Video seeker")                                      ,
              tr("%v/%m (%p%)")                                                    ) ;
    Value = & LocalValue                                                             ;
    Go    = & LocalGo                                                                ;
  } else                                                                             {
    Value = & ( Seeker -> ProgressValue )                                            ;
    Go    = & ( Seeker -> ProgressGo    )                                            ;
  }                                                                                  ;
  ProgressId    = plan->Progress                                                     (
                    tr("Free JAV Share Download")                                    ,
                    tr("%v/%m (%p%)")                                              ) ;
  ProgressValue = 0                                                                  ;
  ProgressGo    = true                                                               ;
  plan -> Start ( ProgressId , &ProgressValue , &ProgressGo )                        ;
  Time :: skip ( 1000 )                                                              ;
  ////////////////////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql           )                                           ;
  SqlConnection HC ( Seeker->HunterSql() )                                           ;
  if (SC.open("JavFreeSeeker","Source"))                                             {
  if (HC.open("JavFreeSeeker","Hunter"))                                             {
    QString Q                                                                        ;
    UUIDs   PageUuids                                                                ;
    //////////////////////////////////////////////////////////////////////////////////
    (*Value) = VideoStart ( )                                                        ;
    plan -> Start    ( IDX , Value        , Go         )                             ;
    plan -> setRange ( IDX , VideoStart() , VideoEnd() )                             ;
    Time :: skip     ( 300                             )                             ;
    //////////////////////////////////////////////////////////////////////////////////
    NamesByOrder ( SC , VideoNameMaps ( 0 ) , Release      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 1 ) , Actress      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 2 ) , Product      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 3 ) , SKU          )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 4 ) , Penetration  )                         ;
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    NamesByOrder ( SC , VideoNameMaps ( 0 ) , Release      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 1 ) , Actress      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 2 ) , Product      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 3 ) , SKU          )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 4 ) , Penetration  )                         ;
    //////////////////////////////////////////////////////////////////////////////////
    for (int i=0;i<100;i++)                                                          {
      if (Actress.contains(i)) InfoMaps [ i + 1000 ] = Actress [ i ]                 ;
    }                                                                                ;
    for (int i=0;i<100;i++)                                                          {
      if (Release.contains(i)) InfoMaps [ i + 2000 ] = Release [ i ]                 ;
    }                                                                                ;
    for (int i=0;i<100;i++)                                                          {
      if (Product.contains(i)) InfoMaps [ i + 3000 ] = Product [ i ]                 ;
    }                                                                                ;
    for (int i=0;i<100;i++)                                                          {
      if (SKU    .contains(i)) InfoMaps [ i + 4000 ] = SKU     [ i ]                 ;
    }                                                                                ;
    for (int i=0;i<100;i++)                                                          {
      if (Penetration.contains(i)) InfoMaps [ i + 5000 ] = Penetration [ i ]         ;
    }                                                                                ;
    //////////////////////////////////////////////////////////////////////////////////
    LoadCompanyProducts ( SC )                                                       ;
    //////////////////////////////////////////////////////////////////////////////////
    while ( ! done )                                                                 {
      plan -> setRange ( IDX , VideoStart() , VideoEnd() )                           ;
      ////////////////////////////////////////////////////////////////////////////////
      int  PageId    = *Value                                                        ;
      bool Available = false                                                         ;
      ////////////////////////////////////////////////////////////////////////////////
      QString path = Search ( PageId )                                               ;
      LookUrl ( path )                                                               ;
      plan -> ProgressText ( IDX , path )                                            ;
      DoProcessEvents                                                                ;
      ////////////////////////////////////////////////////////////////////////////////
      QUrl       u ( path )                                                          ;
      QByteArray XML                                                                 ;
      SUID       puid = 0                                                            ;
      Fetch ( SC , u , puid , XML )                                                  ;
      ////////////////////////////////////////////////////////////////////////////////
      if ( ( XML . size ( ) > 0 ) && ( XML . indexOf ( Posting ( ).toUtf8() ) > 0 )         ) {
        QList<QUrl> URLs                                                             ;
        ObtainPages ( XML , URLs )                                                   ;
        for (int i=0;i<URLs.count();i++)                                             {
          QUrl urlp = URLs[i]                                                        ;
          SUID zuid = assurePage ( SC, urlp )                                        ;
          if ( zuid > 0 )                                                            {
            QStringList IDS                                                          ;
            QString     IDV    = urlp.toString()                                     ;
            QString     STATE                                                        ;
            int         flags  = 0                                                   ;
            bool        exists = true                                                ;
            IDV = IDV . replace ( "http://" , "" )                                   ;
            IDS = IDV . split   ( "/"            )                                   ;
            if ( 3 == IDS.count() )                                                  {
              int     id  = IDS [ 1 ] . toInt ( )                                    ;
              QString TAG = IDS [ 2 ]                                                ;
              TAG = TAG . toUpper ( )                                                ;
              Q = HC.sql.InsertInto("freejav",4,"id","uuid","flags","tag")           ;
              HC . Prepare ( Q                          )                            ;
              HC . Bind    ( "id"    , id               )                            ;
              HC . Bind    ( "uuid"  , zuid             )                            ;
              HC . Bind    ( "flags" , flags            )                            ;
              HC . Bind    ( "tag"   , TAG . toUtf8 ( ) )                            ;
              exists = HC . Exec    (                   )                            ;
            } else                                                                   {
              Q = HC.sql.InsertInto("freejav",2,"uuid","flags")                      ;
              HC . Prepare ( Q                    )                                  ;
              HC . Bind    ( "uuid"  , zuid       )                                  ;
              HC . Bind    ( "flags" , flags      )                                  ;
              exists = HC . Exec    (             )                                  ;
            }                                                                        ;
            exists = !exists                                                         ;
            Q = HC.sql.SelectFrom("flags","freejav",HC.WhereUuid(zuid))              ;
            if (HC.Fetch(Q)) flags = HC.Int(0)                                       ;
            if ( flags > 0 )                                                         {
              switch ( flags )                                                       {
                case 1                                                               :
                  STATE = tr("Downloaded")                                           ;
                break                                                                ;
                case 2                                                               :
                  STATE = tr("Parsed"    )                                           ;
                break                                                                ;
                case 3                                                               :
                  STATE = tr("Completed" )                                           ;
                break                                                                ;
              }                                                                      ;
            } else                                                                   {
              STATE = exists  ? tr("Queue") : tr("Appended")                         ;
            }                                                                        ;
            showMessage( tr ("<%1> %2").arg(urlp.toString()).arg(STATE) )            ;
          }                                                                          ;
        }                                                                            ;
        Available = ( URLs . count ( ) > 0 )                                         ;
      } else                                                                         {
        if ( XML . size ( ) > 0 )                                                    {
          QString FN                                                                 ;
          FN = plan->Temporary(QString("video/%1.html").arg(puid))                   ;
          File :: toFile ( FN , XML )                                                ;
          showMessage ( tr("`%1` can not identify information spots.").arg(PageId) ) ;
        }                                                                            ;
      }                                                                              ;
      ////////////////////////////////////////////////////////////////////////////////
      if (!Available)                                                                {
        showMessage ( tr("`%1` does not have information").arg(PageId)             ) ;
      }                                                                              ;
      showMessage ( "============================================================" ) ;
      if ( (*Value) >= VideoEnd ( ) ) done = true                                    ;
                                 else (*Value)++                                     ;
      Seeker -> ProgressGo = *Go                                                     ;
      if ( ! Seeker -> runnable  ( ) ) done = true                                   ;
      DoProcessEvents                                                                ;
    }                                                                                ;
    //////////////////////////////////////////////////////////////////////////////////
    if ( Seeker -> runnable  ( ) ) done = false                                      ;
    //////////////////////////////////////////////////////////////////////////////////
    if ( ! done )                                                                    {
      PageUuids . clear ( )                                                          ;
      Q = HC . sql . SelectFrom                                                      (
            "uuid"                                                                   ,
            "freejav"                                                                ,
            "where `flags` != 3"                                                     ,
            HC.OrderByDesc("id")                                                   ) ;
      SqlLoopNow ( HC , Q )                                                          ;
        PageUuids << HC . Uuid ( 0 )                                                 ;
      SqlLoopErr ( HC , Q )                                                          ;
      SqlLoopEnd ( HC , Q )                                                          ;
      if ( Seeker -> runnable  ( ) && ( PageUuids . count ( ) > 0 ) )                {
        *Value = 0                                                                   ;
        plan -> setRange ( IDX , 0 , PageUuids . count ( ) )                         ;
        while ( ! done && ( PageUuids . count ( ) > 0 ) )                            {
          bool Available = false                                                     ;
          int  result    = 3                                                         ;
          SUID pageUuid  = PageUuids [ 0 ]                                           ;
          QUrl u         = PageUrl   ( SC , pageUuid )                               ;
          PageUuids . takeAt ( 0 )                                                   ;
          ////////////////////////////////////////////////////////////////////////////
          LookUrl              (       u . toString() )                              ;
          plan -> ProgressText ( IDX , u . toString() )                              ;
          DoProcessEvents                                                            ;
          ////////////////////////////////////////////////////////////////////////////
          QByteArray XML                                                             ;
          SUID       puid = 0                                                        ;
          bool       downloadExists = false                                          ;
          if ( VideoSkip ( ) )                                                       {
            puid = assurePage ( SC , u )                                             ;
            Q = HC.sql.SelectFrom("size","freejav",HC.WhereUuid(puid))               ;
            if (HC.Fetch(Q))                                                         {
              int bs = HC.Int(0)                                                     ;
              downloadExists = ( bs > 0 )                                            ;
            }                                                                        ;
          }                                                                          ;
          if ( ! downloadExists )                                                    {
            Fetch ( SC , u , puid , XML )                                            ;
            //////////////////////////////////////////////////////////////////////////
            if ( ( ! DownloadOnly ( ) ) && ( XML . size ( ) > 0 ) )                  {
              QString   ProductID                                                    ;
              int       PageId                                                       ;
              SUID      CompanyID = 0                                                ;
              SUID      ProductId = 0                                                ;
              SUID      VideoId   = 0                                                ;
              SUID      VideoIcon = 0                                                ;
              UUIDs     AlbumUuids                                                   ;
              UUIDs     ImageUuids                                                   ;
              UUIDs     PEOPLEs                                                      ;
              QDateTime publish                                                      ;
              bool      timeCorrect = false                                          ;
              Q = HC.sql.SelectFrom("id,tag","freejav",HC.WhereUuid(puid))           ;
              if (HC.Fetch(Q))                                                       {
                PageId    = HC . Int    ( 0 )                                        ;
                ProductID = HC . String ( 1 )                                        ;
              }                                                                      ;
              Q  = HC.sql.Update("freejav",HC.sql.Where(1,"uuid"),1,"size")          ;
              HC . Prepare ( Q                   )                                   ;
              HC . Bind    ( "uuid" , puid       )                                   ;
              HC . Bind    ( "size" , XML.size() )                                   ;
              HC . Exec    (                     )                                   ;
              showMessage ( "<hr><br>" )                                             ;
              ////////////////////////////////////////////////////////////////////////
              QList<QUrl> URLs                                                       ;
              KMAPs       TAGs                                                       ;
              FetchTags   ( XML , 0 , InfoMaps , TAGs )                              ;
              FetchImages ( XML , 0 , URLs            )                              ;
              if ( ! TAGs.contains("Title") ) TAGs [ "Title"] = ProductID            ;
              ////////////////////////////////////////////////////////////////////////
              QStringList L = TAGs.keys()                                            ;
              QString     S                                                          ;
              foreach ( S , L )                                                      {
                showMessage ( QString("[%1] = <%2>").arg(S).arg(TAGs[S]) )           ;
              }                                                                      ;
              showMessage ( "<hr><br>" )                                             ;
              if ( TAGs . contains ( "Release" ) )                                   {
                QString release                                                      ;
                release = TAGs["Release"   ]                                         ;
                if (DvdPublish(release,publish))                                     {
                  QString ra                                                         ;
                  ra = tr("Release [%1]").arg(publish.toString("yyyy/MM/dd hh:mm:ss")) ;
                  showMessage ( ra )                                                 ;
                  timeCorrect = true                                                 ;
                }                                                                    ;
              }                                                                      ;
              if ( TAGs . contains ( "Actors" ) )                                    {
                QString     AA = TAGs [ "Actors" ]                                   ;
                QStringList PL = AA.split(" ")                                       ;
                foreach ( AA , PL ) if ( AA.length() > 0 )                           {
                  AA = PurgeSpace ( AA )                                             ;
                  SUID pu = FindPeople ( SC , AA )                                   ;
                  if ( pu > 0 )                                                      {
                    QString ma                                                       ;
                    ma = tr("Found [%1] = [%2]").arg(AA).arg(pu)                     ;
                    showMessage ( ma )                                               ;
                    if ( ! PEOPLEs.contains(pu) ) PEOPLEs << pu                      ;
                  } else                                                             {
                    if ( ! NewAV.contains(AA) )                                      {
                      NewAV << AA                                                    ;
                      showMessage ( tr("%1 is a new pornstar").arg(AA) )             ;
                    }                                                                ;
                  }                                                                  ;
                }                                                                    ;
              }                                                                      ;
              if ( URLs.count() > 0 )                                                {
                for (int i=0;i<URLs.count();i++)                                     {
                  showMessage ( tr("Image address <%1>").arg(URLs[i].toString()))    ;
                }                                                                    ;
                showMessage ( "<hr><br>" )                                           ;
                for (int i=0;i<URLs.count();i++)                                     {
                  SUID pxid                                                          ;
                  SUID zuid                                                          ;
                  pxid = assurePage ( SC , URLs[i] )                                 ;
                  if ( pxid > 0 ) assureParent ( SC , pxid , puid )                  ;
                  zuid = UrlPicture ( SC , pxid    )                                 ;
                  if ( ( pxid > 0 ) && ( ! AlbumUuids.contains(pxid) )             ) {
                    AlbumUuids << pxid                                               ;
                  }                                                                  ;
                  if ( zuid <= 0 )                                                   {
                    showMessage ( QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") ) ;
                    showMessage ( QString("%1 : %2").arg(pxid).arg(URLs[i].toString())         ) ;
                    Download    ( SC , pxid , URLs[i]                                          ) ;
                    showMessage ( QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") ) ;
                    zuid = UrlPicture ( SC , pxid )                                  ;
                  }                                                                  ;
                  if ( zuid > 0 )                                                    {
                    showMessage ( tr    ( "Image <%1> (%2 of %3)"                    )
                                  . arg ( zuid                                       )
                                  . arg ( i + 1                                      )
                                  . arg ( URLs.count()                           ) ) ;
                    //////////////////////////////////////////////////////////////////
                    if ( ( i == 0 ) ) VideoIcon = zuid                               ;
                    if ( ! ImageUuids.contains(zuid) ) ImageUuids << zuid            ;
                  } else result = 1                                                  ;
                  ////////////////////////////////////////////////////////////////////
                }                                                                    ;
              }                                                                      ;
              if ( ! AlbumUuids . contains ( puid ) ) AlbumUuids . prepend ( puid )  ;
              ////////////////////////////////////////////////////////////////////////
              if ( isProduct ( ProductID ) ) CompanyID = MapToCompany ( ProductID )  ;
              if ( ProductID.length() > 0 ) ProductId = FindIdentifier(SC,ProductID) ;
              if ( ( ProductId              <= 0 )                                  &&
                   ( ProductID . length ( ) >  0 )                                  &&
                   TAGs.contains("Title")                                          ) {
                QString PRODUCT = ProductID.toUpper()                                ;
                QString TITLEXX   = TAGs [ "Title"   ]                               ;
                ProductId = assureProduct ( SC , TITLEXX , PRODUCT , PEOPLEs )       ;
              }                                                                      ;
              if (ProductId>0)                                                       {
                QString pa                                                           ;
                pa = tr    ( "Product [%1] = [%2] (%3)"                              )
                     . arg ( ProductID                                               )
                     . arg ( ProductId                                               )
                     . arg ( PageId                                                ) ;
                showMessage ( pa                                                   ) ;
                //////////////////////////////////////////////////////////////////////
                VideoId = LookForVideo ( SC , puid , ProductID  )                    ;
                //////////////////////////////////////////////////////////////////////
              } else                                                                 {
                showMessage ( tr("Product [%1]").arg(ProductID)                    ) ;
              }                                                                      ;
              if ( CompanyID > 0 )                                                   {
                showMessage ( tr("Company : %1").arg(CompanyNames[CompanyID]) )      ;
              }                                                                      ;
              ////////////////////////////////////////////////////////////////////////
              if ( puid > 0 && TAGs.contains("Title") )                              {
                //////////////////////////////////////////////////////////////////////
                bool        match   = false                                          ;
                QStringList LL      = TAGs . keys ( )                                ;
                QString     TITLE   = TAGs [ "Title" ]                               ;
                QString     CONTENT                                                  ;
                QString     SS                                                       ;
                //////////////////////////////////////////////////////////////////////
                foreach ( SS , LL )                                                  {
                  CONTENT . append ( TAGs [ SS ] )                                   ;
                  CONTENT . append ( "\n"        )                                   ;
                }                                                                    ;
                for (int x=5100;!match && x>=5000;x--) if (InfoMaps.contains(x))     {
                  QString cw = InfoMaps[x]                                           ;
                  if (CONTENT.contains(cw)) match = true                             ;
                }                                                                    ;
                //////////////////////////////////////////////////////////////////////
                if ( ( VideoId <= 0 ) ) VideoId = assureVideo ( SC , TITLE )         ;
                //////////////////////////////////////////////////////////////////////
                if ( ( VideoId > 0 ) && ( ProductId > 0 ) )                          {
                  CommodityJoinAlbum ( SC , ProductId , VideoId )                    ;
                }                                                                    ;
                //////////////////////////////////////////////////////////////////////
                if ( VideoId > 0 )                                                   {
                  ////////////////////////////////////////////////////////////////////
                  if ( PEOPLEs . count ( ) > 0 )                                     {
                    AlbumJoinPeople ( SC , VideoId , PEOPLEs )                       ;
                    if ( ProductId > 0 )                                             {
                      CommodityJoinPeople ( SC , ProductId , PEOPLEs )               ;
                    }                                                                ;
                  }                                                                  ;
                  ////////////////////////////////////////////////////////////////////
                  if ( ( ImageUuids.count() > 0 ) )                                  {
                    AlbumJoinPictures ( SC , VideoId , ImageUuids )                  ;
                    if ( GalleryUuid() > 0  )                                        {
                      GalleryJoinPictures ( SC , GalleryUuid() , ImageUuids )        ;
                    }                                                                ;
                  }                                                                  ;
                  ////////////////////////////////////////////////////////////////////
                  if ( AlbumUuids.count() > 0 )                                      {
                    AlbumJoinURLs ( SC , VideoId , AlbumUuids )                      ;
                  }                                                                  ;
                  JoinAlbum ( SC , AlbumUuid ( ) , VideoId )                         ;
                  if (match) JoinAlbum ( SC , InterestUuid ( ) , VideoId )           ;
                  ////////////////////////////////////////////////////////////////////
                  if ( VideoIcon > 0 )                                               {
                    QString TVF = PlanTable(IconGroups)                              ;
                    Q  = SC.sql.SelectFrom                                           (
                          "second"                                                   ,
                          TVF                                                        ,
                          FirstItem ( VideoId                                        ,
                                      Types  :: Album                                ,
                                      Types  :: Picture                              ,
                                      Groups :: Icon                             ) ) ;
                    if (SC.Fetch(Q))                                                 {
                      showMessage  ( tr("%1 icon already exists").arg(VideoId)     ) ;
                    } else                                                           {
                      showMessage  ( tr("assign %1 icon into %2").arg(VideoIcon).arg(VideoId) ) ;
                      InsertItem   ( SC                                              ,
                                     VideoId                                         ,
                                     VideoIcon                                       ,
                                     Types  :: Album                                 ,
                                     Types  :: Picture                               ,
                                     Groups :: Icon                                ) ;
                    }                                                                ;
                  }                                                                  ;
                  ////////////////////////////////////////////////////////////////////
                  SUID pzid                                                          ;
                  foreach ( pzid , PEOPLEs )                                         {
                    //////////////////////////////////////////////////////////////////
                    if ( ImageUuids.count() > 0 )                                    {
                      showMessage  ( tr("Attach pictures to people %1").arg(pzid) )  ;
                      PeopleJoinPictures ( SC , pzid , ImageUuids )                  ;
                    }                                                                ;
                    //////////////////////////////////////////////////////////////////
                    if ( AlbumUuids.count() > 0 )                                    {
                      showMessage  ( tr("Attach URLs to people %1").arg(pzid)      ) ;
                      PeopleJoinURLs ( SC , pzid , AlbumUuids )                      ;
                    }                                                                ;
                    //////////////////////////////////////////////////////////////////
                  }                                                                  ;
                  ////////////////////////////////////////////////////////////////////
                  if ( timeCorrect && publish.isValid() && ( VideoId > 0 ) )         {
                    SUID ttid = 0                                                    ;
                    UUIDs TUIDs = Subordination                                      (
                                    SC                                               ,
                                    VideoId                                          ,
                                    Types  :: Album                                  ,
                                    Types  :: History                                ,
                                    Groups :: Subordination                          ,
                                    SC.OrderByAsc("position")                      ) ;
                    if (TUIDs.count()>0)                                             {
                      ttid = GetHistoryType                                          (
                               SC                                                    ,
                               TUIDs                                                 ,
                               History::PublishDate                                ) ;
                    }                                                                ;
                    N::StarDate SD                                                   ;
                    SD = publish                                                     ;
                    SUID ouid = ttid                                                 ;
                    ttid = assureTime                                                (
                             SC                                                      ,
                             ttid                                                    ,
                             History::PublishDate                                    ,
                             SD.Stardate                                           ) ;
                    if ( ( ouid <= 0 ) && ( ttid > 0 ) )                             {
                      UUIDs XUIDs                                                    ;
                      XUIDs << ttid                                                  ;
                      Join                                                           (
                        SC                                                           ,
                        VideoId                                                      ,
                        Types  :: Album                                              ,
                        Types  :: History                                            ,
                        Groups :: Subordination                                      ,
                        0                                                            ,
                        XUIDs                                                      ) ;
                    }                                                                ;
                  }                                                                  ;
                  ////////////////////////////////////////////////////////////////////
                  if ( ( ProductId > 0 )                                            &&
                       ( VideoId   > 0 )                                            &&
                       ( CompanyID > 0 )                                            &&
                       ( ProductID . length ( ) > 0 )                              ) {
                    QString MN = CompanyNames[CompanyID]                             ;
                    QString PD = ProductID.toUpper()                                 ;
                    AttachCompany (SC,PD,ProductId,CompanyID,MN,VideoId,PEOPLEs)     ;
                  }                                                                  ;
                  ////////////////////////////////////////////////////////////////////
                } else result = 0                                                    ;
                //////////////////////////////////////////////////////////////////////
                if ( result > 0 )                                                    {
                  Q = HC .sql.Update("freejav",HC.sql.Where(1,"uuid"),1,"flags")     ;
                  HC . Prepare ( Q                )                                  ;
                  HC . Bind    ( "uuid"  , puid   )                                  ;
                  HC . Bind    ( "flags" , result )                                  ;
                  HC . Exec    (                  )                                  ;
                  Available = true                                                   ;
                  showMessage  ( tr("Page %1 updated").arg(PageId)                 ) ;
                }                                                                    ;
                //////////////////////////////////////////////////////////////////////
              }                                                                      ;
            }                                                                        ;
          }                                                                          ;
          ////////////////////////////////////////////////////////////////////////////
          if ( ! Available && ( ! DownloadOnly ( ) ) )                               {
            showMessage ( tr("`%1` does not have information").arg(pageUuid)       ) ;
          }                                                                          ;
          if ( PageUuids.count() <= 0 ) done = true                                  ;
                                   else (*Value)++                                   ;
          Seeker -> ProgressGo = *Go                                                 ;
          if ( ! Seeker -> runnable  ( ) ) done = true                               ;
          DoProcessEvents                                                            ;
        }                                                                            ;
      }                                                                              ;
    }                                                                                ;
    //////////////////////////////////////////////////////////////////////////////////
    if ( NewAV.count() > 0 )                                                         {
      showMessage ( "<hr><br>"                                                     ) ;
      showMessage ( "************************************************************" ) ;
      showMessage ( tr("Possible new AV pornstars appear for her first movie.")    ) ;
      showMessage ( "************************************************************" ) ;
      showMessage ( NewAV.join("\n")                                               ) ;
      showMessage ( "************************************************************" ) ;
    }                                                                                ;
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
