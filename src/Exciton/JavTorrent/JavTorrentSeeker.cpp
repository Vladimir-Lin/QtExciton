#include <exciton.h>

N::JavTorrent:: JavTorrent ( QObject * parent , Plan * p )
              : SiteSeeker (           parent ,        p )
              , jtvideo    ( NULL                        )
{
  Enabled [ Types :: People       ] = false ;
  Enabled [ Types :: Video        ] = true  ;
  Enabled [ Types :: Document     ] = false ;
  Enabled [ Types :: Organization ] = false ;
}

N::JavTorrent::~JavTorrent(void)
{
}

int N::JavTorrent::Type(void) const
{
  return 10005 ;
}

QString N::JavTorrent::Name(void) const
{
  return tr("JAV Torrent") ;
}

bool N::JavTorrent::Supported(int type) const
{
  switch ( type )              {
    case Types :: Video        :
    return true                ;
  }                            ;
  return false                 ;
}

QString N::JavTorrent::Name(int type) const
{
  switch ( type )                      {
    case Types :: Video                :
    return tr("JAV Torrent - Video"  ) ;
  }                                    ;
  return ""                            ;
}

QWidget * N::JavTorrent::Configurator (int type)
{
  if (Widgets.contains(type)) return Widgets [ type ]         ;
  switch ( type )                                             {
    case Types :: Video                                       :
      jtvideo          = new JavTorrentVideo  ( NULL , plan ) ;
      Widgets [ type ] = jtvideo                              ;
    return Widgets [ type ]                                   ;
  }                                                           ;
  return NULL                                                 ;
}

bool N::JavTorrent::setEnabled(int type,bool enable)
{
  switch ( type )               {
    case Types :: Video         :
      Enabled [ type ] = enable ;
    return Enabled [ type ]     ;
  }                             ;
  return false                  ;
}

bool N::JavTorrent::VideoSkip(void)
{
  if (IsNull(jtvideo)) return false ;
  return jtvideo->Skip()            ;
}

bool N::JavTorrent::VideoCache(void)
{
  if (IsNull(jtvideo)) return false ;
  return jtvideo->Cache()           ;
}

bool N::JavTorrent::DownloadOnly(void)
{
  if (IsNull(jtvideo)) return false ;
  return jtvideo->DownloadOnly()    ;
}

bool N::JavTorrent::DontParse(void)
{
  if (IsNull(jtvideo)) return false ;
  return jtvideo->DontParse()    ;
}

bool N::JavTorrent::DownloadImage(void)
{
  if (IsNull(jtvideo)) return false ;
  return jtvideo->DownloadImage()   ;
}

bool N::JavTorrent::DownloadTorrent(void)
{
  if (IsNull(jtvideo)) return false ;
  return jtvideo->DownloadTorrent() ;
}

int N::JavTorrent::VideoLastest(void)
{
  if (IsNull(jtvideo)) return 0  ;
  return jtvideo -> Lastest ( )  ;
}

int N::JavTorrent::VideoRetry(void)
{
  if (IsNull(jtvideo)) return 0 ;
  return jtvideo -> Retry ( )  ;
}

SUID N::JavTorrent::AlbumUuid(void)
{
  if (IsNull(jtvideo)) return 0 ;
  return jtvideo->AlbumUuid()   ;
}

SUID N::JavTorrent::InterestUuid(void)
{
  if (IsNull(jtvideo)) return 0  ;
  return jtvideo->InterestUuid() ;
}

SUID N::JavTorrent::GalleryUuid(void)
{
  if (IsNull(jtvideo)) return 0 ;
  return jtvideo->GalleryUuid() ;
}

SUID N::JavTorrent::VideoNameMaps(int index)
{
  if (IsNull(jtvideo)) return 0   ;
  return jtvideo->NameUuid(index) ;
}

QString N::JavTorrent::Search(int index)
{
  if (IsNull(jtvideo)) return ""   ;
  QString m = jtvideo->Pattern()   ;
  return QString(m).arg(index)     ;
}

QString N::JavTorrent::Torrent(QString ID)
{
  if (IsNull(jtvideo)) return ""        ;
  QString m = jtvideo->TorrentPattern() ;
  return m + ID                         ;
}

QString N::JavTorrent::TorrentPath(QString CODE)
{
  if (IsNull(jtvideo)) return ""      ;
  QString m = jtvideo->TorrentPath()  ;
  QString f                           ;
  f = QString("%1.torrent").arg(CODE) ;
  QDir    d ( m )                     ;
  f = d.absoluteFilePath(f)           ;
  return f                            ;
}

QString N::JavTorrent::Identifier(void)
{
  if (IsNull(jtvideo)) return "" ;
  return jtvideo->Identifier()   ;
}

bool N::JavTorrent::prepare(void)
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
          jtvideo  -> prepare ( ) ;
        break                     ;
      }                           ;
    }                             ;
  }                               ;
  /////////////////////////////////
  return true                     ;
}

bool N::JavTorrent::configure(QString scope)
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
          jtvideo  -> configure ( scope , Seeker->HunterSql() ) ;
        break                                                   ;
      }                                                         ;
    }                                                           ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                              ;
  if (SC.open("JavTorrent","configure"))                        {
    LearnSite :: Initialize ( SC )                              ;
    SC . close              (    )                              ;
  }                                                             ;
  SC.remove()                                                   ;
  ///////////////////////////////////////////////////////////////
  return true                                                   ;
}

bool N::JavTorrent::startup(int type)
{
  switch ( type )        {
    case Types::Video    :
    return RunVideo  ( ) ;
  }                      ;
  return false           ;
}

bool N::JavTorrent::Fetch(SqlConnection & SC,QUrl u,SUID & puid,QByteArray & XML)
{
  if ( VideoCache ( )    ) hadCached ( SC , u , puid , XML ) ;
  if ( XML.size ( ) <= 0 ) Obtain    ( SC , u , puid , XML ) ;
  return                             ( XML . size ( ) > 0  ) ;
}

bool N::JavTorrent::RunVideo(void)
{
  QStringList NewAV                                                                  ;
  NAMEs       Release                                                                ;
  NAMEs       Actress                                                                ;
  NAMEs       Product                                                                ;
  NAMEs       SKU                                                                    ;
  NAMEs       Penetration                                                            ;
  NAMEs       Symbols                                                                ;
  NAMEs       Companies                                                              ;
  NAMEs       InfoMaps                                                               ;
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
              tr("JAV Torrent Video seeker")                                         ,
              tr("%v/%m (%p%)")                                                    ) ;
    Value = & LocalValue                                                             ;
    Go    = & LocalGo                                                                ;
  } else                                                                             {
    Value = & ( Seeker -> ProgressValue )                                            ;
    Go    = & ( Seeker -> ProgressGo    )                                            ;
  }                                                                                  ;
  ////////////////////////////////////////////////////////////////////////////////////
  ProgressId = plan->Progress                                                        (
        tr("JAV Torrent Downloader")                                                 ,
        tr("%v/%m (%p%)")                                                          ) ;
  ProgressValue = 0                                                                  ;
  ProgressGo    = true                                                               ;
  plan -> Start    ( ProgressId , &ProgressValue , &ProgressGo                     ) ;
  Time :: skip ( 1000 )                                                              ;
  ////////////////////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql           )                                           ;
  SqlConnection HC ( Seeker->HunterSql() )                                           ;
  if (SC.open("JavTorrent","Source"))                                                {
  if (HC.open("JavTorrent","Hunter"))                                                {
    QString Q                                                                        ;
    int     EndId                                                                    ;
    int     Failure = 0                                                              ;
    //////////////////////////////////////////////////////////////////////////////////
    (*Value) = VideoLastest ( )                                                      ;
    EndId    = (*Value) + 100                                                        ;
    plan -> Start    ( IDX , Value          , Go    )                                ;
    plan -> setRange ( IDX , VideoLastest() , EndId )                                ;
    Time :: skip     ( 300                          )                                ;
    //////////////////////////////////////////////////////////////////////////////////
    NamesByOrder ( SC , VideoNameMaps ( 0 ) , Release      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 1 ) , Actress      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 2 ) , Product      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 3 ) , SKU          )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 4 ) , Penetration  )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 5 ) , Symbols      )                         ;
    NamesByOrder ( SC , VideoNameMaps ( 6 ) , Companies    )                         ;
    //////////////////////////////////////////////////////////////////////////////////
    for (int i=0;i<100;i++)                                                          {
      if (Symbols.contains(i)) InfoMaps [ i        ] = Symbols [ i ]                 ;
    }                                                                                ;
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
    for (int i=0;i<100;i++)                                                          {
      if (Companies.contains(i)) InfoMaps [ i + 6000 ] = Companies [ i ]             ;
    }                                                                                ;
    //////////////////////////////////////////////////////////////////////////////////
    LoadCompanyProducts ( SC )                                                       ;
    //////////////////////////////////////////////////////////////////////////////////
    while ( ! done )                                                                 {
      plan -> setRange ( IDX , VideoLastest() , EndId )                              ;
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
      XML . clear ( )                                                                ;
      Fetch ( SC , u , puid , XML )                                                  ;
      ////////////////////////////////////////////////////////////////////////////////
      if ( ( puid > 0 ) && ( XML . size ( ) > 0 )                                  ) {
        Q = HC.sql.InsertInto("freedl",3,"id","uuid","size")                         ;
        HC . Prepare ( Q                    )                                        ;
        HC . Bind    ( "id"    , PageId     )                                        ;
        HC . Bind    ( "uuid"  , puid       )                                        ;
        HC . Bind    ( "size"  , XML.size() )                                        ;
        HC . Exec    (                      )                                        ;
        if ( ! DontParse() && ! DownloadOnly ( ) )                                   {
          Available = Parse ( SC , HC , u , PageId , puid , XML , InfoMaps , NewAV ) ;
          if ( ( ! Available ) && ( puid > 0 ) && ( XML . size ( ) > 0 )           ) {
            Q  = SC.sql.DeleteFrom(PlanTable(ImportBodies),SC.WhereUuid(puid))       ;
            SC . Query ( Q )                                                         ;
            Q  = SC.sql.DeleteFrom(PlanTable(XmlDepot    ),SC.WhereUuid(puid))       ;
            SC . Query ( Q )                                                         ;
            Q  = HC.sql.DeleteFrom("freedl"               ,SC.WhereUuid(puid))       ;
            HC . Query ( Q )                                                         ;
          }                                                                          ;
        } else Available = true                                                      ;
      }                                                                              ;
      ////////////////////////////////////////////////////////////////////////////////
      if (!Available)                                                                {
        showMessage ( tr("`%1` does not have information").arg(PageId)             ) ;
        Failure++                                                                    ;
      } else Failure = 0                                                             ;
      showMessage ( "<hr><br>" )                                                     ;
      if ( (*Value) >= EndId )                                                       {
        if ( Failure < VideoRetry() )                                                {
          EndId    += 100                                                            ;
          (*Value) ++                                                                ;
        } else done = true                                                           ;
      } else (*Value)++                                                              ;
      if ( Failure >= VideoRetry ( ) ) done = true                                   ;
      Seeker -> ProgressGo = *Go                                                     ;
      if ( ! Seeker -> runnable  ( ) ) done = true                                   ;
      DoProcessEvents                                                                ;
      Time :: msleep ( 200 )                                                         ;
    }                                                                                ;
    //////////////////////////////////////////////////////////////////////////////////
    if ( NewAV.count() > 0 )                                                         {
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

QString N::JavTorrent::Compact(QString source)
{
  for (int i=0;i<10;i++)                       {
    source = source.replace("   "," ")         ;
  }                                            ;
  for (int i=0;i<20;i++)                       {
    source = source.replace("  " ," ")         ;
  }                                            ;
  while ( source.length()>0                   &&
          source.at(0)==' '                  ) {
    source . remove ( 0 , 1 )                  ;
  }                                            ;
  while ( source.length()>0                   &&
          source.at(source.length()-1)==' '  ) {
    source . remove ( source.length()-1 , 1 )  ;
  }                                            ;
  return PurgeSpace ( source )                 ;
}

bool N::JavTorrent::isLatin(QString s)
{
  for (int i=0;i<s.length();i++)            {
    if (s.at(i).unicode()>255) return false ;
  }                                         ;
  return true                               ;
}

int N::JavTorrent::FetchTags (
      QByteArray & XML       ,
      int          index     ,
      NAMEs      & INFOs     ,
      KMAPs      & TAGs      )
{
  QByteArray B                                   ;
  RangeInt   R                                   ;
  ////////////////////////////////////////////////
  R . L = index                                  ;
  if (!Between(R,">","</font>",XML)) return -1   ;
  ////////////////////////////////////////////////
  B = XML . mid ( R . L , R . V ( ) )            ;
  TAGs [ "Title" ] = QString::fromUtf8(B)        ;
  R . R += 7                                     ;
  index  = R . R                                 ;
  index  = XML.indexOf("<a href=",index)         ;
  if (index<=0) return -1                        ;
  B = XML . mid ( R.R , index - R.R )            ;
  int idx                                        ;
  int E  = 0                                     ;
  idx = B.indexOf("<blockquote>")                ;
  if ( idx >= 0 )                                {
    QByteArray  LX                               ;
    QString     LS                               ;
    QStringList NS                               ;
    int         SE = B.size()                    ;
    idx += 12                                    ;
    LX   = B . mid ( idx , SE - idx )            ;
    LS   = QString::fromUtf8(LX)                 ;
    NS   = LS . split ( "<br />" )               ;
    for (int i=0;i<NS.count();i++)               {
      if ( NS[i].length() > 0 )                  {
        if ( NS[i] != TAGs [ "Title" ] )         {
          QString     ML = NS [ i ]              ;
          QStringList LL                         ;
          if (ML.contains(':'))                  {
            LL = ML . split ( ':'      )         ;
          } else
          if (ML.contains(INFOs[0]))             {
            LL = ML . split ( INFOs[0] )         ;
          }                                      ;
          if (LL.count()>1)                      {
            QString T = LL[0]                    ;
            QString R = LL[1]                    ;
            for (int j=1100;j>=1000;j--)         {
              if (INFOs.contains(j))             {
                if (T.contains(INFOs[j]))        {
                  T = "Actors"                   ;
                }                                ;
              }                                  ;
            }                                    ;
            for (int j=2100;j>=2000;j--)         {
              if (INFOs.contains(j))             {
                if (T.contains(INFOs[j]))        {
                  T = "Release"                  ;
                }                                ;
              }                                  ;
            }                                    ;
            for (int j=3100;j>=3000;j--)         {
              if (INFOs.contains(j))             {
                if (T.contains(INFOs[j]))        {
                  T = "Product"                  ;
                }                                ;
              }                                  ;
            }                                    ;
            for (int j=6100;j>=6000;j--)         {
              if (INFOs.contains(j))             {
                if (T.contains(INFOs[j]))        {
                  T = "Company"                  ;
                }                                ;
              }                                  ;
            }                                    ;
            if (T.length()>0 && R.length()>0)    {
              TAGs [ T ] =  R                    ;
            }                                    ;
          } else                                 {
            E++                                  ;
            TAGs [ QString::number(E) ] = NS [i] ;
          }                                      ;
        } else                                   {
          E++                                    ;
          TAGs [ QString::number(E) ] = NS [i]   ;
        }                                        ;
      }                                          ;
    }                                            ;
  }                                              ;
  ////////////////////////////////////////////////
  if ( ( E > 0 ) && TAGs.contains("1") )         {
    if (TAGs.contains("Title"))                  {
      if ( TAGs["1"] == TAGs["Title"] )          {
        TAGs . take ( "1" )                      ;
      }                                          ;
    }                                            ;
  }                                              ;
  ////////////////////////////////////////////////
  if (E>=2)                                      {
    for (int i=2;i<E;i++)                        {
      if (TAGs.contains(QString::number(i)))     {
        QString NID = QString::number(i)         ;
        QString G   = TAGs [ NID ]               ;
        if (!TAGs.contains("Actors"))            {
          for (int j=1100;j>=1000;j--)           {
            if (INFOs.contains(j))               {
              QString ITF = INFOs[j]             ;
              QString RTF = G.left(ITF.length()) ;
              if ( ITF == RTF )                  {
                G.remove(0,ITF.length())         ;
                TAGs [ "Actors" ] = G            ;
                TAGs . take ( NID )              ;
              }                                  ;
            }                                    ;
          }                                      ;
        }                                        ;
        if (!TAGs.contains("Release"))           {
          for (int j=2100;j>=2000;j--)           {
            if (INFOs.contains(j))               {
              QString ITF = INFOs[j]             ;
              QString RTF = G.left(ITF.length()) ;
              if ( ITF == RTF )                  {
                G.remove(0,ITF.length())         ;
                TAGs [ "Release" ] = G           ;
                TAGs . take ( NID )              ;
              }                                  ;
            }                                    ;
          }                                      ;
        }                                        ;
      }                                          ;
    }                                            ;
  }                                              ;
  ////////////////////////////////////////////////
  if (TAGs.contains("1"))                        {
    if (TAGs.contains("Title"))                  {
      QString OTITLE = TAGs [ "Title" ]          ;
      QString POSSIB = TAGs [ "1"     ]          ;
      int     INDEX  = OTITLE.indexOf(POSSIB)    ;
      bool    marked = false                     ;
      if ( INDEX > 0 )                           {
        TAGs [ "Title" ] = POSSIB                ;
        POSSIB = OTITLE.left(INDEX)              ;
        marked = true                            ;
      } else
      if ( isLatin(OTITLE) && !isLatin(POSSIB) ) {
        TAGs [ "Title" ] = POSSIB                ;
        POSSIB           = OTITLE                ;
        marked           = true                  ;
      }                                          ;
      if ( marked )                              {
        TAGs . take ( "1" )                      ;
        if ( ! TAGs.contains("Product")         &&
               POSSIB.contains(']')            ) {
          INDEX = POSSIB.indexOf("]")            ;
          if (INDEX>0)                           {
            POSSIB . remove  ( 0 , INDEX + 1   ) ;
            POSSIB = Compact ( POSSIB          ) ;
            POSSIB = POSSIB.replace(" ","")      ;
            TAGs [ "Product" ] = POSSIB          ;
          } else                                 {
            QString NXD = QString::number(E)     ;
            TAGs [ NXD ] = POSSIB                ;
            E++                                  ;
          }                                      ;
        } else                                   {
          QString NXD = QString::number(E)       ;
          TAGs [ NXD ] = POSSIB                  ;
          E++                                    ;
        }                                        ;
      }                                          ;
    }                                            ;
  }                                              ;
  ////////////////////////////////////////////////
  if ( !TAGs.contains("Product")                &&
        TAGs.contains("ID"     )               ) {
    TAGs [ "Product" ] = TAGs [ "ID" ]           ;
    TAGs .take ( "ID" )                          ;
  }                                              ;
  ////////////////////////////////////////////////
  if ( TAGs.contains("Product") )                {
    QString PRODUCT = TAGs [ "Product" ]         ;
    if (INFOs.contains(1))                       {
      PRODUCT = PRODUCT.replace(INFOs[1],"")     ;
    }                                            ;
    PRODUCT = Compact ( PRODUCT )                ;
    PRODUCT = PRODUCT.replace(" ","")            ;
    if (PRODUCT.length()<=0)                     {
      TAGs . take ( "Product" )                  ;
    } else                                       {
      TAGs [ "Product" ] = PRODUCT               ;
    }                                            ;
  }                                              ;
  ////////////////////////////////////////////////
  if ( TAGs.contains("Actors") )                 {
    SymbolPool SP                                ;
    QString ACTORS = TAGs [ "Actors" ]           ;
    if (INFOs.contains(1))                       {
      ACTORS = ACTORS.replace(INFOs[1]," ")      ;
    }                                            ;
    ACTORS = Compact ( ACTORS )                  ;
    ACTORS = ACTORS . replace ( "("     , " "  ) ;
    ACTORS = ACTORS . replace ( ")"     , " "  ) ;
    ACTORS = ACTORS . replace ( SP["("] , " "  ) ;
    ACTORS = ACTORS . replace ( SP[")"] , " "  ) ;
    if (ACTORS.length()<=0)                      {
      TAGs . take ( "Actors" )                   ;
    } else                                       {
      TAGs [ "Actors" ] = ACTORS                 ;
    }                                            ;
  }                                              ;
  ////////////////////////////////////////////////
  if ( !TAGs.contains("Release"     )           &&
        TAGs.contains("Release Date")          ) {
    TAGs [ "Release" ] = TAGs [ "Release Date" ] ;
    TAGs .take ( "Release Date" )                ;
  }                                              ;
  ////////////////////////////////////////////////
  #define REPACK(NAME)                           \
  if (TAGs.contains(NAME))                     { \
    TAGs[NAME] = Compact ( TAGs[NAME] )        ; \
    if (TAGs[NAME].length()<=0)                { \
      TAGs.take(NAME)                          ; \
    }                                          } \
  ////////////////////////////////////////////////
  REPACK ( "Title"   )                           ;
  REPACK ( "Actors"  )                           ;
  REPACK ( "Release" )                           ;
  REPACK ( "Product" )                           ;
  REPACK ( "Company" )                           ;
  ////////////////////////////////////////////////
  #undef  REPACK
  ////////////////////////////////////////////////
  if (TAGs.contains("Release"))                  {
    QString R = TAGs [ "Release" ]               ;
    if (R.contains(' '))                         {
      int idx = R.indexOf(' ')                   ;
      if (idx>0)                                 {
        R = R.left(idx)                          ;
      }                                          ;
    }                                            ;
    if (R.contains('-'))                         {
      R = R.replace('-','/')                     ;
    }                                            ;
    R = Compact ( R )                            ;
    TAGs [ "Release" ] = R                       ;
  }                                              ;
  return index                                   ;
}

int N::JavTorrent::FetchImages (
      QByteArray  & XML        ,
      int           index      ,
      QList<QUrl> & URLs       )
{
  int endix = XML.indexOf("Link URL",index)                ;
  if ( endix <= 0 )                                        {
    endix = XML.indexOf("link.php?ref=",index)             ;
    if (endix>0)                                           {
      endix -= 40                                          ;
      endix  = XML.indexOf("<a href=",endix)               ;
      if (endix<0) return -1                               ;
    } else                                                 {
      return -1                                            ;
    }                                                      ;
  }                                                        ;
  QByteArray B                                             ;
  B = XML . mid ( index , endix - index )                  ;
  int idx = 0                                              ;
  int edx                                                  ;
  while ( ( idx = B . indexOf ( "<a href" , idx ) ) >= 0 ) {
    idx  = B . indexOf ( "\"" , idx     )                  ;
    if ( idx > 0 )                                         {
      idx += 1                                             ;
      edx  = B . indexOf ( "\"" , idx + 1 )                ;
      if (edx>0)                                           {
        QByteArray U                                       ;
        U = B . mid ( idx , edx - idx )                    ;
        idx = B . indexOf ( "<a href" , edx )              ;
        QString AU = QString::fromUtf8(U)                  ;
        QUrl    UR ( AU )                                  ;
        URLs << UR                                         ;
      }                                                    ;
    } else break                                           ;
  }                                                        ;
  return endix                                             ;
}

int N::JavTorrent::FetchTorrents (
      QByteArray  & XML          ,
      int           index        ,
      QList<QUrl> & URLs         )
{
  int idx = XML . indexOf ( "<a href" , index ) ;
  int edx                                       ;
  if ( idx <= 0 )                               {
    idx = XML.indexOf("link.php?ref=",index)    ;
    if (idx>0)                                  {
      idx -= 40                                 ;
      idx  = XML.indexOf("<a href=",idx)        ;
      if (idx<0) return -1                      ;
    } else                                      {
      return -1                                 ;
    }                                           ;
  }                                             ;
  idx  = XML . indexOf ( "\"" , idx     )       ;
  if ( idx > 0 )                                {
    idx += 1                                    ;
    edx  = XML . indexOf ( "\"" , idx + 1 )     ;
    if (edx>0)                                  {
      QByteArray U                              ;
      U = XML . mid ( idx , edx - idx )         ;
      QString AU = QString::fromUtf8(U)         ;
      QUrl    UR ( AU )                         ;
      URLs << UR                                ;
      index = edx                               ;
    }                                           ;
  }                                             ;
  return index                                  ;
}

bool N::JavTorrent::ObtainImage (
       SqlConnection & SC       ,
       QUrl            url      ,
       SUID            puid     ,
       SUID          & ruid     ,
       SUID          & image    )
{
  QString PROXY                                     ;
  PROXY = QString ( "%1:%2"                         )
          . arg   ( Seeker->ProxyAddress()          )
          . arg   ( Seeker->ProxyPort   ()        ) ;
  ///////////////////////////////////////////////////
  ImageDinoFetcher  DinoFetcher  ( plan )           ;
  ImageFlareFetcher FlareFetcher ( plan )           ;
  ImageServeFetcher ServeFetcher ( plan )           ;
  PicExposedFetcher PicExposed   ( plan )           ;
  PicExposedFetcher ImgClick     ( plan )           ;
  bool              success = false                 ;
  int               ds                              ;
  QDir              TmpDir                          ;
  ///////////////////////////////////////////////////
  ds      = Seeker -> DownloadTime ( ) * 1000       ;
  TmpDir  = QDir ( Seeker->Temporary( "" ) )        ;
  DinoFetcher  . Temporary = TmpDir                 ;
  FlareFetcher . Temporary = TmpDir                 ;
  ServeFetcher . Temporary = TmpDir                 ;
  PicExposed   . Temporary = TmpDir                 ;
  ImgClick     . Temporary = TmpDir                 ;
  ImgClick     . Requests [ "proxy" ] = PROXY       ;
  ///////////////////////////////////////////////////
  if ( ! success )                                  {
    success = DinoFetcher  . Obtain                 (
                SC                                  ,
                url                                 ,
                puid                                ,
                ruid                                ,
                image                               ,
                Seeker -> DownloadTime ( ) * 1000 ) ;
  }                                                 ;
  ///////////////////////////////////////////////////
  if ( ! success )                                  {
    success = FlareFetcher . Obtain                 (
                SC                                  ,
                url                                 ,
                puid                                ,
                ruid                                ,
                image                               ,
                Seeker -> DownloadTime ( ) * 1000 ) ;
  }                                                 ;
  ///////////////////////////////////////////////////
  if ( ! success )                                  {
    success = ServeFetcher . Obtain                 (
                SC                                  ,
                url                                 ,
                puid                                ,
                ruid                                ,
                image                               ,
                Seeker -> DownloadTime ( ) * 1000 ) ;
  }                                                 ;
  ///////////////////////////////////////////////////
  if ( ! success )                                  {
    success = PicExposed . Obtain                   (
                SC                                  ,
                url                                 ,
                puid                                ,
                ruid                                ,
                image                               ,
                Seeker -> DownloadTime ( ) * 1000 ) ;
  }                                                 ;
  ///////////////////////////////////////////////////
  if ( ! success )                                  {
    success = ImgClick . Obtain                     (
                SC                                  ,
                url                                 ,
                puid                                ,
                ruid                                ,
                image                               ,
                Seeker -> DownloadTime ( ) * 1000 ) ;
  }                                                 ;
  ///////////////////////////////////////////////////
  return success                                    ;
}

bool N::JavTorrent::Parse     (
       SqlConnection & SC     ,
       SqlConnection & HC     ,
       QUrl            url    ,
       int             PageId ,
       SUID          & zuid   ,
       QByteArray    & XML    ,
       NAMEs         & INFOs  ,
       QStringList   & NewAV  )
{
  QTextCodec * codec  = QTextCodec::codecForName("Shift-JIS")        ;
  QString      bs     = codec->toUnicode(XML)                        ;
  QByteArray   ZML    = bs . toUtf8 ( )                              ;
  QString      FreeDL = "http://www.freedl.org"                      ;
  QString      USN    = url . toString (    )                        ;
  QString      IDF    = Identifier     (    )                        ;
  QString      TILI                                                  ;
  QString      Q                                                     ;
  KMAPs        TAGs                                                  ;
  QList<QUrl>  URLs                                                  ;
  QList<QUrl>  TORRENTs                                              ;
  int          index                                                 ;
  ////////////////////////////////////////////////////////////////////
  USN = USN . replace ( FreeDL , "" )                                ;
  showMessage ( tr("Size : %1,%2").arg(XML.size()).arg(ZML.size()) ) ;
  TILI  = IDF + USN + ">"                                            ;
  index = ZML.indexOf(TILI.toUtf8())                                          ;
  if ( index <= 0 ) return false                                     ;
  index += TILI.length()                                             ;
  index  = ZML.indexOf("</a>] <",index)                              ;
  if ( index <= 0 ) return false                                     ;
  index += 7                                                         ;
  ////////////////////////////////////////////////////////////////////
  index  = FetchTags     ( ZML , index , INFOs , TAGs )              ;
  if ( index <= 0            ) return false                          ;
  index  = FetchImages   ( ZML , index , URLs         )              ;
  if ( index <= 0            ) return false                          ;
  index  = FetchTorrents ( ZML , index , TORRENTs     )              ;
  if ( TORRENTs.count() <= 0 ) return false                          ;
  ////////////////////////////////////////////////////////////////////
  QStringList Ks = TAGs.keys()                                       ;
  for (int i=0;i<Ks.count();i++)                                     {
    showMessage ( tr("[%1] => <%2>").arg(Ks[i]).arg(TAGs[Ks[i]]) )   ;
    Time :: skip ( 50 )                                              ;
  }                                                                  ;
  showMessage("---------------------------------------------------") ;
  for (int i=0;i<URLs.count();i++)                                   {
    showMessage ( URLs[i].toString() )                               ;
    assurePage  ( SC , URLs[i]       )                               ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if (TORRENTs.count()>0)                                            {
    QString IDX = TORRENTs[0].toString()                             ;
    QString REF = "/link.php?ref="                                   ;
    int     POS = IDX.indexOf(REF)                                   ;
    if (POS>0)                                                       {
      POS += REF.length()                                            ;
      IDX  = IDX.mid(POS,IDX.length()-POS)                           ;
      IDX  = IDX.replace(" ","")                                     ;
    } else IDX = ""                                                  ;
    if (IDX.length()>0)                                              {
      showMessage("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^") ;
      showMessage ( tr("Torrent Identifier : %1").arg(IDX) )         ;
      showMessage("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^") ;
      Q = HC.sql.Update("freedl",SC.sql.Where(1,"uuid"),1,"torrent") ;
      HC . Prepare ( Q                            )                  ;
      HC . Bind    ( "uuid"    , zuid             )                  ;
      HC . Bind    ( "torrent" , IDX . toUtf8 ( ) )                  ;
      HC . Exec    (                              )                  ;
    }                                                                ;
    for (int i=0;i<TORRENTs.count();i++)                             {
      showMessage ( TORRENTs[i].toString() )                         ;
      assurePage  ( SC , TORRENTs[i]       )                         ;
    }                                                                ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  UUIDs PEOPLEs                                                      ;
  SUID  MakerId   = 0                                                ;
  SUID  ProductId = 0                                                ;
  SUID  VideoId   = 0                                                ;
  showMessage("---------------------------------------------------") ;
  if ( TAGs . contains ( "Actors" )                                ) {
    QStringList ACTORS = TAGs [ "Actors" ] . split(' ')              ;
    QString     actor                                                ;
    foreach ( actor , ACTORS ) if ( actor.length() > 0 )             {
      SUID pu = FindPeople ( SC , actor )                            ;
      if ( pu > 0 )                                                  {
        QString ma                                                   ;
        ma = tr("Found [%1] = [%2]").arg(actor).arg(pu)              ;
        showMessage ( ma )                                           ;
        PEOPLEs << pu                                                ;
      } else                                                         {
        if ( ! NewAV.contains(actor) )                               {
          NewAV << actor                                             ;
        }                                                            ;
        showMessage ( tr("%1 is a new pornstar").arg(actor) )        ;
      }                                                              ;
    }                                                                ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  showMessage("---------------------------------------------------") ;
  if ( TAGs . contains ( "Product" )                               ) {
    QString PRODUCT = TAGs [ "Product" ]                             ;
    PRODUCT   = PRODUCT . toUpper ( )                                ;
    if ( PRODUCT.length() > 0 ) ProductId=FindIdentifier(SC,PRODUCT) ;
    if (ProductId>0)                                                 {
      QString pa                                                     ;
      pa = tr("Product [%1] = [%2]").arg(PRODUCT).arg(ProductId)     ;
      showMessage ( pa                                             ) ;
      ////////////////////////////////////////////////////////////////
      VideoId = LookForVideo ( SC , zuid , PRODUCT  )                ;
      ////////////////////////////////////////////////////////////////
      Q = HC.sql.Update                                              (
            "freedl"                                                 ,
            SC.sql.Where(1,"uuid")                                   ,
            1                                                        ,
            "commodity"                                            ) ;
      HC . Prepare ( Q                        )                      ;
      HC . Bind    ( "uuid"       , zuid      )                      ;
      HC . Bind    ( "commodity"  , ProductId )                      ;
      HC . Exec    (                          )                      ;
    } else                                                           {
      showMessage ( tr("Product [%1]").arg(PRODUCT)                ) ;
    }                                                                ;
    if (PRODUCT.length()>0)                                          {
      Q = HC.sql.Update("freedl",SC.sql.Where(1,"uuid"),1,"tag"    ) ;
      HC . Prepare ( Q                             )                 ;
      HC . Bind    ( "uuid" , zuid                 )                 ;
      HC . Bind    ( "tag"  , PRODUCT . toUtf8 ( ) )                 ;
      HC . Exec    (                               )                 ;
    }                                                                ;
  }                                                                  ;
  if ( TAGs .contains ( "Company" ) )                                {
    if ( TAGs [ "Company" ].length() > 0 )                           {
      MakerId = FindCompany ( SC , TAGs [ "Company" ] )              ;
    }                                                                ;
    if ( MakerId > 0 )                                               {
      QString pa                                                     ;
      pa = tr("Maker [%1] = [%2]").arg(TAGs["Company"]).arg(MakerId) ;
      showMessage ( pa                                             ) ;
      Q = HC.sql.Update                                              (
            "freedl"                                                 ,
            SC.sql.Where(1,"uuid")                                   ,
            1                                                        ,
            "maker"                                                ) ;
      HC . Prepare ( Q                 )                             ;
      HC . Bind    ( "uuid"  , zuid    )                             ;
      HC . Bind    ( "maker" , MakerId )                             ;
      HC . Exec    (                   )                             ;
    }                                                                ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( VideoId > 0 )                                                 {
    QString vn = SC . getName                                        (
                   PlanTable(Names)                                  ,
                   "uuid"                                            ,
                   plan->LanguageId                                  ,
                   VideoId                                         ) ;
    QString vm                                                       ;
    vm = tr("Found video [%1] is <%2>").arg(VideoId).arg(vn)         ;
    showMessage ( vm )                                               ;
    Q = HC.sql.Update                                                (
          "freedl"                                                   ,
          SC.sql.Where(1,"uuid")                                     ,
          1                                                          ,
          "video"                                                  ) ;
    HC . Prepare ( Q                 )                               ;
    HC . Bind    ( "uuid"  , zuid    )                               ;
    HC . Bind    ( "video" , VideoId )                               ;
    HC . Exec    (                   )                               ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( TAGs .contains ( "Title" ) )                                  {
    QString TITLE = TAGs [ "Title" ]                                 ;
    Q = HC.sql.Update                                                (
          "freedl"                                                   ,
          SC.sql.Where(1,"uuid")                                     ,
          1                                                          ,
          "title"                                                  ) ;
    HC . Prepare ( Q                        )                        ;
    HC . Bind    ( "uuid"  , zuid           )                        ;
    HC . Bind    ( "title" , TITLE.toUtf8() )                        ;
    HC . Exec    (                          )                        ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  ZMAPs UrlToUuid                                                    ;
  SMAPs UrlToActual                                                  ;
  SMAPs ActualToImage                                                ;
  UUIDs ImageUuids                                                   ;
  UUIDs TorrentUuids                                                 ;
  UUIDs AlbumURLs                                                    ;
  SUID  VideoIcon = 0                                                ;
  if ( DownloadImage() && ( URLs . count ( ) > 0 ) )                 {
    ProgressValue = 0                                                ;
    ProgressGo    = true                                             ;
    plan -> Start    ( ProgressId , &ProgressValue , &ProgressGo   ) ;
    plan -> setRange ( ProgressId , 0              , URLs.count()  ) ;
    for (int i=0;ProgressGo && i<URLs.count();i++)                   {
      QString MX                                                     ;
      SUID    puid  = 0                                              ;
      SUID    ruid  = 0                                              ;
      SUID    image = 0                                              ;
      ////////////////////////////////////////////////////////////////
      ++ProgressValue                                                ;
      puid = assurePage  ( SC , URLs[i] )                            ;
      ////////////////////////////////////////////////////////////////
      if ( puid > 0 )                                                {
        bool success = false                                         ;
        //////////////////////////////////////////////////////////////
        UrlToUuid [ URLs[i].toString() ] = puid                      ;
        if ( ! AlbumURLs.contains(puid) ) AlbumURLs << puid          ;
        //////////////////////////////////////////////////////////////
        Q = SC . sql . SelectFrom                                    (
              "second"                                               ,
              PlanTable(NetGroups)                                      ,
              FirstItem                                              (
                puid                                                 ,
                Types  :: URL                                        ,
                Types  :: URL                                        ,
                Groups :: Equivalent                                 ,
                SC.sql.Limit(0,1)                                ) ) ;
        if (SC.Fetch(Q)) ruid = SC . Uuid ( 0 )                      ;
        if ( ruid > 0 )                                              {
          Q = SC . sql . SelectFrom                                  (
                "first"                                              ,
                PlanTable(PictureGroups)                             ,
                SecondItem                                           (
                  ruid                                               ,
                  Types  :: Picture                                  ,
                  Types  :: URL                                      ,
                  Groups :: Subordination                            ,
                  SC.sql.Limit(0,1)                              ) ) ;
          if (SC.Fetch(Q)) image = SC . Uuid ( 0 )                   ;
        }                                                            ;
        //////////////////////////////////////////////////////////////
        if ( image <= 0 )                                            {
          MX = "+++++++++++++++++++++++++++++++++++++++++++++++++++" ;
          showMessage ( MX                                         ) ;
          MX = tr   ( "Fetch image (%1)<%2>"                         )
              . arg ( puid                                           )
              . arg ( URLs[i].toString()                           ) ;
          showMessage ( MX                                         ) ;
          plan -> ProgressText  ( ProgressId , MX                  ) ;
          success = ObtainImage                                      (
                      SC                                             ,
                      URLs[i]                                        ,
                      puid                                           ,
                      ruid                                           ,
                      image                                        ) ;
          if ( success && ( ruid > 0 ) && ( image > 0 )            ) {
            UUIDs PURLs                                              ;
            PURLs << puid                                            ;
            PURLs << ruid                                            ;
            Delegate ( SC                                            ,
                       puid                                          ,
                       ruid                                          ,
                       Types  :: URL                                 ,
                       Types  :: URL                                 ,
                       Groups :: Equivalent                        ) ;
            Join     ( SC                                            ,
                       image                                         ,
                       Types  :: Picture                             ,
                       Types  :: URL                                 ,
                       Groups :: Subordination                       ,
                       0                                             ,
                       PURLs                                       ) ;
          }                                                          ;
        }                                                            ;
        //////////////////////////////////////////////////////////////
        if ( ruid > 0 )                                              {
          QUrl imageUrl = PageUrl ( SC , ruid )                      ;
          MX = tr  ( "Actual image address <%1>"                     )
              .arg ( imageUrl.toString()                           ) ;
          showMessage ( MX                                         ) ;
          UrlToActual [ puid ] = ruid                                ;
          if ( ! AlbumURLs.contains(ruid) ) AlbumURLs << ruid        ;
        }                                                            ;
        //////////////////////////////////////////////////////////////
        if ( ( ruid > 0 ) && ( image > 0 ) )                         {
          QSize GS = Geometry ( SC , image )                         ;
          MX = tr   ( "Image size : (%1)<%2,%3>"                     )
              . arg ( image                                          )
              . arg ( GS . width  ( )                                )
              . arg ( GS . height ( )                              ) ;
          showMessage ( MX                                         ) ;
          ActualToImage [ ruid ] = image                             ;
          if ( ! ImageUuids.contains(image) ) ImageUuids << image    ;
        }                                                            ;
        //////////////////////////////////////////////////////////////
        if ( ( i == 0 ) && ( image > 0 ) )                           {
          VideoIcon = image                                          ;
        }                                                            ;
      }                                                              ;
    }                                                                ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( DownloadTorrent() && TORRENTs.count()>0)                      {
    ProgressValue = 0                                                ;
    ProgressGo    = true                                             ;
    plan -> Start    ( ProgressId , &ProgressValue , &ProgressGo   ) ;
    plan -> setRange ( ProgressId , 0          , TORRENTs.count()  ) ;
    for (int i=0;ProgressGo && i<TORRENTs.count();i++)               {
      ++ProgressValue                                                ;
      QString IDX = TORRENTs[i].toString()                           ;
      QString REF = "/link.php?ref="                                 ;
      int     POS = IDX.indexOf(REF)                                 ;
      if (POS>0)                                                     {
        POS += REF.length()                                          ;
        IDX  = IDX.mid(POS,IDX.length()-POS)                         ;
        IDX  = IDX.replace(" ","")                                   ;
      } else IDX = ""                                                ;
      ////////////////////////////////////////////////////////////////
      if (IDX.length()>0)                                            {
        QString MX                                                   ;
        SUID    puid = 0                                             ;
        SUID    ruid = 0                                             ;
        SUID    file = 0                                             ;
        MX = tr("Download %1").arg(TORRENTs[i].toString())           ;
        showMessage ( MX )                                           ;
        plan -> ProgressText ( ProgressId , MX )                     ;
        //////////////////////////////////////////////////////////////
        puid = assurePage  ( SC , TORRENTs[i] )                      ;
        //////////////////////////////////////////////////////////////
        if ( puid > 0 )                                              {
          bool    success = false                                    ;
          QString torrent = ""                                       ;
          ////////////////////////////////////////////////////////////
          UrlToUuid [ TORRENTs[i].toString() ] = puid                ;
          if ( ! AlbumURLs.contains(puid) ) AlbumURLs << puid        ;
          ////////////////////////////////////////////////////////////
          Q = SC . sql . SelectFrom                                  (
                "second"                                             ,
                PlanTable(NetGroups)                                 ,
                FirstItem                                            (
                  puid                                               ,
                  Types  :: URL                                      ,
                  Types  :: URL                                      ,
                  Groups :: Equivalent                               ,
                  SC.sql.Limit(0,1)                              ) ) ;
          if (SC.Fetch(Q)) ruid = SC . Uuid ( 0 )                    ;
          if ( ruid > 0 )                                            {
            UrlToActual [ puid ] = ruid                              ;
            if ( ! AlbumURLs.contains(ruid) ) AlbumURLs << ruid      ;
            Q = SC . sql . SelectFrom                                (
                  "first"                                            ,
                  PlanTable(Groups)                                  ,
                  SecondItem                                         (
                    ruid                                             ,
                    Types  :: File                                   ,
                    Types  :: URL                                    ,
                    Groups :: Subordination                          ,
                    SC.sql.Limit(0,1)                            ) ) ;
            if (SC.Fetch(Q)) file = SC . Uuid ( 0 )                  ;
          }                                                          ;
          if ( file <= 0 )                                           {
            JpTorrentFetcher TorrentFetcher ( plan )                 ;
            MX = "+++++++++++++++++++++++++++++++++++++++++++++++++" ;
            showMessage ( MX                                       ) ;
            MX = tr   ( "Fetch torrent (%1)<%2>"                     )
                . arg ( puid                                         )
                . arg ( TORRENTs[i].toString()                     ) ;
            showMessage ( MX                                       ) ;
            plan -> ProgressText  ( ProgressId , MX                ) ;
            success = TorrentFetcher . Obtain                        (
                        SC                                           ,
                        TORRENTs[i]                                  ,
                        puid                                         ,
                        ruid                                         ,
                        torrent                                      ,
                        Seeker -> DownloadTime ( ) * 1000          ) ;
            if ( success && ( ruid > 0 ) && ( torrent.length()>0 ) ) {
              ////////////////////////////////////////////////////////
              QString FinalIdx = IDX                                 ;
              if ( TAGs . contains ( "Product" )                   ) {
                QString PRODUCT = TAGs [ "Product" ]                 ;
                PRODUCT = PRODUCT . toUpper ( )                      ;
                if ( ! PRODUCT . contains ( ' ' ) )                  {
                  FinalIdx = PRODUCT                                 ;
                }                                                    ;
              }                                                      ;
              if ( FinalIdx.length() > 0 )                           {
                QString btDepot                                      ;
                btDepot = TorrentPath ( FinalIdx )                   ;
                QFileInfo FXDT ( btDepot )                           ;
                if ( ! FXDT . exists ( ) )                           {
                  QByteArray TML                                     ;
                  File::toByteArray ( torrent , TML )                ;
                  if ( TML.size() > 0 )                              {
                    File::toFile ( btDepot , TML )                   ;
                    torrent = btDepot                                ;
                  }                                                  ;
                }                                                    ;
              }                                                      ;
              ////////////////////////////////////////////////////////
              CodeManager CM ( plan )                                ;
              int TID = 724                                          ;
              file = CM . assureFile ( SC , torrent )                ;
              if ( file > 0 )                                        {
                //////////////////////////////////////////////////////
                Q = SC.sql.SelectFrom                                (
                      "id",PlanTable(FileManager)                    ,
                      QString("where uuid = %1 and type = %2 "
                              "and extension = %3 and depot = %4"    )
                      . arg ( file                                   )
                      . arg ( Types::File                            )
                      . arg ( TID                                    )
                      . arg ( Types::Video                       ) ) ;
                if (!SC.Fetch(Q))                                    {
                  QFileInfo FL ( torrent )                           ;
                  QString path = FL.absolutePath()                   ;
                  QString name = FL.fileName    ()                   ;
                  Q = SC.sql.InsertInto                              (
                        PlanTable(FileManager)                       ,
                        6                                            ,
                        "uuid"                                       ,
                        "type"                                       ,
                        "extension"                                  ,
                        "depot"                                      ,
                        "path"                                       ,
                        "filename"                                 ) ;
                  SC . Prepare ( Q                                 ) ;
                  SC . Bind    ( "uuid"      , file                ) ;
                  SC . Bind    ( "type"      , Types::File         ) ;
                  SC . Bind    ( "extension" , TID                 ) ;
                  SC . Bind    ( "depot"     , Types::Video        ) ;
                  SC . Bind    ( "path"      , path.toUtf8()       ) ;
                  SC . Bind    ( "filename"  , name.toUtf8()       ) ;
                  SC . Exec    (                                   ) ;
                }                                                    ;
                //////////////////////////////////////////////////////
                UUIDs PURLs                                          ;
                PURLs << puid                                        ;
                PURLs << ruid                                        ;
                Delegate ( SC                                        ,
                           puid                                      ,
                           ruid                                      ,
                           Types  :: URL                             ,
                           Types  :: URL                             ,
                           Groups :: Equivalent                    ) ;
                Join     ( SC                                        ,
                           file                                      ,
                           Types  :: File                            ,
                           Types  :: URL                             ,
                           Groups :: Subordination                   ,
                           0                                         ,
                           PURLs                                   ) ;
                //////////////////////////////////////////////////////
              }                                                      ;
            }                                                        ;
          }                                                          ;
          ////////////////////////////////////////////////////////////
          if ( ( ruid > 0 ) && ( file > 0 ) )                        {
            if ( ! TorrentUuids.contains(file) )                     {
              TorrentUuids << file                                   ;
            }                                                        ;
            if ( torrent.length() >0 )                               {
              QFileInfo FXL ( torrent )                              ;
              QString   msg                                          ;
              msg = tr    ( "Torrent size : (%1)<%2>"                )
                  . arg   ( file                                     )
                  . arg   ( FXL . size ( )                         ) ;
              showMessage ( msg                                    ) ;
            }                                                        ;
          }                                                          ;
          ////////////////////////////////////////////////////////////
        } else                                                       {
          QString   msg                                              ;
          msg = tr    ( "Torrent lost <%1>"                          )
              . arg   ( TORRENTs[i].toString()                     ) ;
          showMessage ( msg                                        ) ;
        }                                                            ;
      }                                                              ;
    }                                                                ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( ( ProductId <= 0 ) || ( VideoId <= 0 ) || ( MakerId <= 0 ) )  {
    Q = HC . sql . SelectFrom                                        (
          "video,commodity,maker"                                    ,
          "freedl"                                                   ,
          HC.WhereUuid(zuid)                                       ) ;
    if (HC.Fetch(Q))                                                 {
      SUID video  = HC.Uuid(0)                                       ;
      SUID commo  = HC.Uuid(1)                                       ;
      SUID maker  = HC.Uuid(2)                                       ;
      if ( ( ProductId <= 0 ) && ( commo > 0 ) )                     {
        ProductId = commo                                            ;
        if ( ( ProductId > 0 ) && PEOPLEs.count()>0)                 {
          CommodityJoinPeople ( SC , ProductId , PEOPLEs )           ;
        }                                                            ;
      }                                                              ;
      if ( ( VideoId <= 0 ) && ( video > 0 ) ) VideoId = video       ;
      if ( ( MakerId <= 0 ) && ( maker > 0 ) ) MakerId = maker       ;
    }                                                                ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( (ProductId <= 0 )                                            &&
       TAGs.contains("Product")                                     &&
       TAGs.contains("Title") )                                      {
    QString PRODUCT = TAGs [ "Product" ]                             ;
    QString TITLE   = TAGs [ "Title"   ]                             ;
    PRODUCT   = PRODUCT . toUpper ( )                                ;
    ProductId = assureProduct ( SC , TITLE , PRODUCT , PEOPLEs )     ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( ( VideoId <= 0 ) && ( TAGs["Title"].length() > 0 ) )          {
    QString TITLE = TAGs [ "Title" ]                                 ;
    VideoId = assureVideo ( SC , TITLE )                             ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( ( VideoId > 0 ) && ( ProductId > 0 ) )                        {
    CommodityJoinAlbum ( SC , ProductId , VideoId )                  ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( VideoId <= 0 ) return false                                   ;
  ////////////////////////////////////////////////////////////////////
  if ( PEOPLEs . count ( ) > 0 )                                     {
    AlbumJoinPeople ( SC , VideoId , PEOPLEs )                       ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( ( ImageUuids.count() > 0 ) )                                  {
    AlbumJoinPictures ( SC , VideoId , ImageUuids )                  ;
    if ( GalleryUuid() > 0  )                                        {
      GalleryJoinPictures ( SC , GalleryUuid() , ImageUuids )        ;
    }                                                                ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( ( TorrentUuids.count() > 0 ) && ( VideoId > 0 ) )             {
    Join                                                             (
      SC                                                             ,
      VideoId                                                        ,
      Types  :: Album                                                ,
      Types  :: File                                                 ,
      Groups :: Subordination                                        ,
      0                                                              ,
      TorrentUuids                                                 ) ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  if ( ! AlbumURLs . contains ( zuid ) ) AlbumURLs << zuid           ;
  if ( AlbumURLs.count() > 0 )                                       {
    AlbumJoinURLs ( SC , VideoId , AlbumURLs )                       ;
  }                                                                  ;
  JoinAlbum ( SC , AlbumUuid ( ) , VideoId )                         ;
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
    if ( AlbumURLs.count() > 0 )                                     {
      showMessage  ( tr("Attach URLs to people %1").arg(pzid)      ) ;
      PeopleJoinURLs ( SC , pzid , AlbumURLs )                       ;
    }                                                                ;
    //////////////////////////////////////////////////////////////////
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  QString     wc                                                     ;
  QStringList TLS = TAGs.keys()                                      ;
  QString     ZCL                                                    ;
  foreach ( ZCL , TLS )                                              {
    wc . append ( TAGs [ ZCL ] )                                     ;
    wc . append ( "\n"         )                                     ;
  }                                                                  ;
  bool    match = false                                              ;
  for (int x=5100;!match && x>=5000;x--) if (INFOs.contains(x))      {
    QString cw = INFOs[x]                                            ;
    if (wc.contains(cw)) match = true                                ;
  }                                                                  ;
  if (match)                                                         {
    JoinAlbum ( SC , InterestUuid ( ) , VideoId )                    ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  QDateTime publish                                                  ;
  bool      timeCorrect = false                                      ;
  if ( TAGs . contains ( "Release" ) )                               {
    QString release                                                  ;
    release = TAGs["Release"   ]                                     ;
    if (DvdPublish(release,publish))                                 {
      QString ra                                                     ;
      ra = tr("Release [%1]").arg(publish.toString("yyyy/MM/dd hh:mm:ss")) ;
      showMessage ( ra )                                             ;
      timeCorrect = true                                             ;
    }                                                                ;
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
       ( TAGs [ "Product" ] . length ( ) > 0 )                     ) {
    QString MN                                                       ;
    QString PD = TAGs [ "Product" ]                                  ;
    PD = PD.toUpper()                                                ;
    if (TAGs.contains("Maker")) MN = TAGs["Maker"]                   ;
    AttachCompany (SC,PD,ProductId,MakerId,MN,VideoId,PEOPLEs)       ;
  }                                                                  ;
  ////////////////////////////////////////////////////////////////////
  QString QQ                                                         ;
  int     FLAGs = 1                                                  ;
  QQ = HC.sql.Update                                                 (
        "freedl"                                                     ,
        HC.sql.Where(1,"uuid")                                       ,
        4                                                            ,
        "video"                                                      ,
        "commodity"                                                  ,
        "maker"                                                      ,
        "flags"                                                    ) ;
  HC . Prepare ( QQ                      )                           ;
  HC . Bind    ( "uuid"      , zuid      )                           ;
  HC . Bind    ( "video"     , VideoId   )                           ;
  HC . Bind    ( "commodity" , ProductId )                           ;
  HC . Bind    ( "maker"     , MakerId   )                           ;
  HC . Bind    ( "flags"     , FLAGs     )                           ;
  HC . Exec    (                         )                           ;
  ////////////////////////////////////////////////////////////////////
  showMessage  ( tr("Page %1 updated").arg(PageId)                 ) ;
  ////////////////////////////////////////////////////////////////////
  return true                                                        ;
}
