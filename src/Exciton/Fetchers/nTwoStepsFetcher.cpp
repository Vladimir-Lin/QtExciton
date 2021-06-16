#include <exciton.h>

#define plan NetPlan

N::TwoStepsFetcher:: TwoStepsFetcher ( Plan * p )
                    : Ftp            (          )
                    , NetworkManager (        p )
                    , PictureManager (        p )
                    , curl           ( NULL     )
{
  if (NotNull(plan))                        {
    Temporary = plan->Temporary("webcache") ;
  }                                         ;
}

N::TwoStepsFetcher::~TwoStepsFetcher (void)
{
}

QString N::TwoStepsFetcher::TemporaryHtml(SUID puid)
{
  return Temporary . absoluteFilePath ( QString("%1.html") . arg ( puid ) ) ;
}

QString N::TwoStepsFetcher::ImageFilename(QString U,SUID ruid)
{
  QStringList ILL           = U.split('/')              ;
  QString     ImageFormat   = ILL.last()                ;
  QStringList ImageEXTs     = ImageFormat.split('.')    ;
  QString     IEXT          = ImageEXTs.last()          ;
  QString     Location                                  ;
  ImageFormat = QString("%1.%2").arg(ruid).arg(IEXT)    ;
  Location    = Temporary.absoluteFilePath(ImageFormat) ;
  return Location                                       ;
}

bool N::TwoStepsFetcher::VerifyUrl(QUrl & url)
{
  return false ;
}

bool N::TwoStepsFetcher::ImportImage (
       SqlConnection & SC            ,
       QString         Location      ,
       SUID          & image         )
{
  if ( Location . length ( ) <= 0 ) return false     ;
  ////////////////////////////////////////////////////
  PictureManager :: Import ( SC , Location , image ) ;
  QFile          :: remove ( Location              ) ;
  ////////////////////////////////////////////////////
  return true                                        ;
}

void N::TwoStepsFetcher::Mismatch(QUrl & url)
{
  plan -> Debug ( 80 , QString("<%1> has different format?").arg(url.toString()) ) ;
  plan -> Debug ( 80 , QString("Please check HTML and C/C++ source code")        ) ;
}

bool N::TwoStepsFetcher::Instance(void)
{
  curl = ::curl_easy_init ( ) ;
  return NotNull(curl)        ;
}

bool N::TwoStepsFetcher::Prepare(QFile & file,QUrl & url)
{
  Ftp::Operation =  Download ;
  Ftp::File      = &file     ;
  Ftp::Url       = &url      ;
  Ftp::dlHeader  . clear ( ) ;
  ////////////////////////////
  if ( ! Instance ( ) )      {
    failure ( )              ;
    Ftp::File = NULL         ;
    Ftp::Url  = NULL         ;
    return false             ;
  }                          ;
  ////////////////////////////
  return true                ;
}

bool N::TwoStepsFetcher::setOptions(QUrl & url)
{
  QByteArray ADDR = url.toEncoded(urlFormat)                          ;
  starting           (  url , Download                              ) ;
  ::curl_easy_setopt ( curl , CURLOPT_URL,ADDR.data()               ) ;
  ::curl_easy_setopt ( curl , CURLOPT_HEADERFUNCTION,N::Ftp::hwrite ) ;
  ::curl_easy_setopt ( curl , CURLOPT_WRITEFUNCTION,N::Ftp::cwrite  ) ;
  ::curl_easy_setopt ( curl , CURLOPT_WRITEHEADER,this              ) ;
  ::curl_easy_setopt ( curl , CURLOPT_WRITEDATA,this                ) ;
  ::curl_easy_setopt ( curl , CURLOPT_VERBOSE,0L                    ) ;
  return true                                                         ;
}

bool N::TwoStepsFetcher::setTimeouts (
       int connexion                 ,
       int download                  )
{
  if (connexion>0)                                               {
    ::curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT_MS,connexion) ;
  }                                                              ;
  if (download>0)                                                {
    ::curl_easy_setopt(curl,CURLOPT_TIMEOUT_MS       ,download ) ;
  }                                                              ;
  return true                                                    ;
}

void N::TwoStepsFetcher::setAgent(QString agent)
{
  QByteArray AGENT   = agent.toUtf8()                                      ;
  ::curl_easy_setopt ( curl , CURLOPT_USERAGENT  , AGENT . constData ( ) ) ;
  ::curl_easy_setopt ( curl , CURLOPT_COOKIEFILE , ""                    ) ;
}

void N::TwoStepsFetcher::setProxy(QString proxy)
{
  QByteArray BX = proxy.toUtf8()                                   ;
  ::curl_easy_setopt ( curl , CURLOPT_PROXYTYPE , CURLPROXY_HTTP ) ;
  ::curl_easy_setopt ( curl , CURLOPT_PROXY     , BX.constData() ) ;
}

void N::TwoStepsFetcher::setReferer(QString referer)
{
  QUrl       UR ( referer )                                   ;
  QByteArray RDDR = UR.toEncoded(urlFormat)                   ;
  ::curl_easy_setopt ( curl , CURLOPT_REFERER , RDDR.data() ) ;
}

bool N::TwoStepsFetcher::Perform(void)
{
  CURLcode result                       ;
  bool     success = false              ;
  result = ::curl_easy_perform ( curl ) ;
  success = ( CURLE_OK == result )      ;
  finished ( success )                  ;
  return success                        ;
}

bool N::TwoStepsFetcher::ObtainXML(QString filename,QByteArray & XML)
{
  N::File:: toByteArray ( filename , XML ) ;
  QFile  :: remove      ( filename       ) ;
  return true                              ;
}

QString N::TwoStepsFetcher::MiddleString (
          QByteArray & XML               ,
          QString      left              ,
          QString      right             )
{
  QString U = ""                                      ;
  int     realidx                                     ;
  realidx = XML . indexOf ( left.toUtf8() )           ;
  if ( ( XML.size() > 0 ) && ( realidx > 0 ) )        {
    realidx += left.length()                          ;
    if (realidx>0)                                    {
      int endix                                       ;
      endix = XML.indexOf(right.toUtf8(),realidx)     ;
      if (endix>0)                                    {
        QByteArray B = XML.mid(realidx,endix-realidx) ;
        U = QString::fromUtf8(B)                      ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  return U                                            ;
}

QString N::TwoStepsFetcher::TwoStepsString (
          QByteArray & XML                 ,
          QString      left                ,
          QString      middle              ,
          QString      right               )
{
  QString U = ""                                      ;
  int     realidx                                     ;
  realidx = XML . indexOf ( left.toUtf8() )           ;
  if ( ( XML.size() > 0 ) && ( realidx > 0 ) )        {
    realidx += left.length()                          ;
    realidx  = XML.indexOf(middle.toUtf8(),realidx)            ;
    if (realidx>0)                                    {
      int endix                                       ;
      realidx += middle.length()                      ;
      endix    = XML.indexOf(right.toUtf8(),realidx)           ;
      if (endix>0)                                    {
        QByteArray B = XML.mid(realidx,endix-realidx) ;
        U = QString::fromUtf8(B)                      ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  return U                                            ;
}

void N::TwoStepsFetcher::setTags(void)
{
  QStringList keys = Requests.keys()                            ;
  QString     K                                                 ;
  foreach ( K , keys )                                          {
    if (K.toLower()=="proxy"  ) setProxy   ( Requests[K] ) ; else
    if (K.toLower()=="referer") setReferer ( Requests[K] )      ;
  }                                                             ;
}

void N::TwoStepsFetcher::setProxyOnly(void)
{
  QStringList keys = Requests.keys()                       ;
  QString     K                                            ;
  foreach ( K , keys )                                     {
    if (K.toLower()=="proxy"  ) setProxy   ( Requests[K] ) ;
  }                                                        ;
}

void N::TwoStepsFetcher::Cleanup(void)
{
  ::curl_easy_cleanup ( curl ) ;
  Ftp::File = NULL             ;
  Ftp::Url  = NULL             ;
}

bool N::TwoStepsFetcher::Obtain (
       SqlConnection & SC       ,
       QUrl            url      ,
       SUID            puid     ,
       SUID          & ruid     ,
       SUID          & image    ,
       int             mtimeout ,
       QString         nexturl  ,
       QString         endmark  )
{
  if ( ! VerifyUrl ( url ) ) return false                                       ;
  ///////////////////////////////////////////////////////////////////////////////
  QString    agent = N::XML::UserAgents[rand()%40]                              ;
  QByteArray AGENT   = agent.toUtf8()                                           ;
  bool       success = false                                                    ;
  QString    HtmlTmp = TemporaryHtml ( puid )                                   ;
  QByteArray ADDR    = url.toEncoded(urlFormat)                                 ;
  QFile      file ( HtmlTmp )                                                   ;
  ///////////////////////////////////////////////////////////////////////////////
  ruid           = 0                                                            ;
  image          = 0                                                            ;
  if ( ! Prepare ( file , url ) ) return false                                  ;
  ///////////////////////////////////////////////////////////////////////////////
  setOptions  ( url                          )                                  ;
  setTimeouts ( connectionTimeout , mtimeout )                                  ;
  setAgent    ( agent                        )                                  ;
  setTags     (                              )                                  ;
  ///////////////////////////////////////////////////////////////////////////////
  success = Perform ( )                                                         ;
  if ( ! success )                                                              {
    ::curl_easy_cleanup ( curl )                                                ;
    Ftp::File = NULL                                                            ;
    Ftp::Url  = NULL                                                            ;
    QFile :: remove ( HtmlTmp )                                                 ;
    return false                                                                ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  QString    ImageUrl      = ""                                                 ;
  QString    ImageLocation = ""                                                 ;
  QUrl       imageUrl                                                           ;
  QByteArray AdXML                                                              ;
  ObtainXML ( HtmlTmp,AdXML )                                                   ;
  ImageUrl = MiddleString ( AdXML , nexturl , endmark )                         ;
  if (ImageUrl.length()>0) imageUrl = QUrl ( ImageUrl )                         ;
  ///////////////////////////////////////////////////////////////////////////////
  if ( ( ImageUrl . length ( ) > 0 ) && imageUrl.isValid() )                    {
    ruid = assurePage ( SC , imageUrl )                                         ;
    if ( ruid > 0 )                                                             {
      ImageLocation = ImageFilename ( ImageUrl , ruid )                         ;
      ///////////////////////////////////////////////////////////////////////////
      QFile ImageFile ( ImageLocation )                                         ;
      QFile :: remove ( ImageLocation )                                         ;
      assureParent ( SC , ruid , puid )                                         ;
      ///////////////////////////////////////////////////////////////////////////
      Ftp::Operation =  Download                                                ;
      Ftp::File      = &ImageFile                                               ;
      Ftp::Url       = &imageUrl                                                ;
      Ftp::dlHeader  . clear ( )                                                ;
      ///////////////////////////////////////////////////////////////////////////
      setOptions  ( imageUrl                     )                              ;
      setTimeouts ( connectionTimeout , mtimeout )                              ;
      ///////////////////////////////////////////////////////////////////////////
      ::curl_easy_setopt ( curl , CURLOPT_USERAGENT  , AGENT . constData ( )  ) ;
      ::curl_easy_setopt ( curl , CURLOPT_REFERER    , ADDR  . data      ( )  ) ;
      setProxyOnly       (                                                    ) ;
      success = Perform  (                                                    ) ;
      ///////////////////////////////////////////////////////////////////////////
    }                                                                           ;
  } else Mismatch ( url )                                                       ;
  ///////////////////////////////////////////////////////////////////////////////
  Cleanup ( )                                                                   ;
  ///////////////////////////////////////////////////////////////////////////////
  if ( ! success )                                                              {
    QFile :: remove ( ImageLocation )                                           ;
    return success                                                              ;
  }                                                                             ;
  if ( ! ImportImage ( SC , ImageLocation , image ) ) success = false           ;
  ///////////////////////////////////////////////////////////////////////////////
  return success                                                                ;
}

bool N::TwoStepsFetcher::Obtain (
       SqlConnection & SC       ,
       QUrl            url      ,
       SUID            puid     ,
       SUID          & ruid     ,
       SUID          & image    ,
       int             mtimeout ,
       QString         nexturl  ,
       QString         middle   ,
       QString         endmark  )
{
  if ( ! VerifyUrl ( url ) ) return false                                       ;
  ///////////////////////////////////////////////////////////////////////////////
  QString    agent = N::XML::UserAgents[rand()%40]                              ;
  QByteArray AGENT   = agent.toUtf8()                                           ;
  bool       success = false                                                    ;
  QString    HtmlTmp = TemporaryHtml ( puid )                                   ;
  QByteArray ADDR    = url.toEncoded(urlFormat)                                 ;
  QFile      file ( HtmlTmp )                                                   ;
  ///////////////////////////////////////////////////////////////////////////////
  ruid           = 0                                                            ;
  image          = 0                                                            ;
  if ( ! Prepare ( file , url ) ) return false                                  ;
  ///////////////////////////////////////////////////////////////////////////////
  setOptions  ( url                          )                                  ;
  setTimeouts ( connectionTimeout , mtimeout )                                  ;
  setAgent    ( agent                        )                                  ;
  setTags     (                              )                                  ;
  ///////////////////////////////////////////////////////////////////////////////
  success = Perform ( )                                                         ;
  if ( ! success )                                                              {
    ::curl_easy_cleanup ( curl )                                                ;
    Ftp::File = NULL                                                            ;
    Ftp::Url  = NULL                                                            ;
    QFile :: remove ( HtmlTmp )                                                 ;
    return false                                                                ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  QString    ImageUrl      = ""                                                 ;
  QString    ImageLocation = ""                                                 ;
  QUrl       imageUrl                                                           ;
  QByteArray AdXML                                                              ;
  ObtainXML ( HtmlTmp,AdXML )                                                   ;
  ImageUrl = TwoStepsString ( AdXML , nexturl , middle , endmark )              ;
  if (ImageUrl.length()>0) imageUrl = QUrl ( ImageUrl )                         ;
  ///////////////////////////////////////////////////////////////////////////////
  if ( ( ImageUrl . length ( ) > 0 ) && imageUrl.isValid() )                    {
    ruid = assurePage ( SC , imageUrl )                                         ;
    if ( ruid > 0 )                                                             {
      ImageLocation = ImageFilename ( ImageUrl , ruid )                         ;
      ///////////////////////////////////////////////////////////////////////////
      QFile ImageFile ( ImageLocation )                                         ;
      QFile :: remove ( ImageLocation )                                         ;
      assureParent ( SC , ruid , puid )                                         ;
      ///////////////////////////////////////////////////////////////////////////
      Ftp::Operation =  Download                                                ;
      Ftp::File      = &ImageFile                                               ;
      Ftp::Url       = &imageUrl                                                ;
      Ftp::dlHeader  . clear ( )                                                ;
      ///////////////////////////////////////////////////////////////////////////
      setOptions  ( imageUrl                     )                              ;
      setTimeouts ( connectionTimeout , mtimeout )                              ;
      ///////////////////////////////////////////////////////////////////////////
      ::curl_easy_setopt ( curl , CURLOPT_USERAGENT  , AGENT . constData ( )  ) ;
      ::curl_easy_setopt ( curl , CURLOPT_REFERER    , ADDR  . data      ( )  ) ;
      setProxyOnly       (                                                    ) ;
      success = Perform  (                                                    ) ;
      ///////////////////////////////////////////////////////////////////////////
    }                                                                           ;
  } else Mismatch ( url )                                                       ;
  ///////////////////////////////////////////////////////////////////////////////
  Cleanup ( )                                                                   ;
  ///////////////////////////////////////////////////////////////////////////////
  if ( ! success )                                                              {
    QFile :: remove ( ImageLocation )                                           ;
    return success                                                              ;
  }                                                                             ;
  if ( ! ImportImage ( SC , ImageLocation , image ) ) success = false           ;
  ///////////////////////////////////////////////////////////////////////////////
  return success                                                                ;
}
