#include <exciton.h>

#define plan    PicturePlan
#define STARTPS "<span id=\"zoomimage\" style=\"visibility:hidden\"><img"
#define MIDPS   "src=\""
#define ENDPS   "\""

N::ImageFlareFetcher:: ImageFlareFetcher ( Plan * p )
                     : TwoStepsFetcher   (        p )
{
  if (NotNull(plan))                        {
    Temporary = plan->Temporary("webcache") ;
  }                                         ;
}

N::ImageFlareFetcher::~ImageFlareFetcher (void)
{
}

bool N::ImageFlareFetcher::VerifyUrl(QUrl & url)
{
  QString imgflare  = "http://www.imgflare.com/"                      ;
  QString imgbabes  = "http://www.imgbabes.com/"                      ;
  QString urlstring = url.toString()                                  ;
  bool    correct   = false                                           ;
  if ( ( ! correct ) && urlstring.contains(imgflare) ) correct = true ;
  if ( ( ! correct ) && urlstring.contains(imgbabes) ) correct = true ;
  return correct                                                      ;
}

bool N::ImageFlareFetcher::Obtain (
       SqlConnection & SC         ,
       QUrl            url        ,
       SUID            puid       ,
       SUID          & ruid       ,
       SUID          & image      ,
       int             mtimeout   )
{
  return TwoStepsFetcher :: Obtain (
           SC                      ,
           url                     ,
           puid                    ,
           ruid                    ,
           image                   ,
           mtimeout                ,
           STARTPS                 ,
           MIDPS                   ,
           ENDPS                 ) ;
}

#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool N::ImageFlareFetcher::Obtain (
       SqlConnection & SC        ,
       QUrl            url       ,
       SUID            puid      ,
       SUID          & ruid      ,
       SUID          & image     ,
       int             mtimeout  )
{
  QString imgflare  = "http://www.imgflare.com/"                                ;
  QString imgbabes  = "http://www.imgbabes.com/"                                ;
  QString nexturl   = "<span id=\"zoomimage\" style=\"visibility:hidden\"><img" ;
  QString urlstring = url.toString()                                            ;
  bool    correct   = false                                                     ;
  if ( ( ! correct ) && urlstring.contains(imgflare) ) correct = true           ;
  if ( ( ! correct ) && urlstring.contains(imgbabes) ) correct = true           ;
  if (   ! correct                                   ) return false             ;
  ///////////////////////////////////////////////////////////////////////////////
  QString    agent = N::XML::UserAgents[rand()%40]                              ;
  QByteArray AGENT   = agent.toUtf8()                                           ;
  bool       success = false                                                    ;
  CURLcode   result                                                             ;
  QString    HtmlTmp = Temporary.absoluteFilePath(QString("%1.html").arg(puid)) ;
  QFile      file ( HtmlTmp )                                                   ;
  ///////////////////////////////////////////////////////////////////////////////
  ruid           = 0                                                            ;
  image          = 0                                                            ;
  ///////////////////////////////////////////////////////////////////////////////
  Ftp::Operation =  Download                                                    ;
  Ftp::File      = &file                                                        ;
  Ftp::Url       = &url                                                         ;
  Ftp::dlHeader  . clear ( )                                                    ;
  ///////////////////////////////////////////////////////////////////////////////
  curl = ::curl_easy_init ( )                                                   ;
  if (IsNull(curl))                                                             {
    failure ( )                                                                 ;
    Ftp::File = NULL                                                            ;
    Ftp::Url  = NULL                                                            ;
    return false                                                                ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  QByteArray ADDR = url.toEncoded(urlFormat)                                    ;
  starting           (  url , Download                                        ) ;
  ::curl_easy_setopt ( curl , CURLOPT_URL,ADDR.data()                         ) ;
  ::curl_easy_setopt ( curl , CURLOPT_HEADERFUNCTION,N::Ftp::hwrite           ) ;
  ::curl_easy_setopt ( curl , CURLOPT_WRITEFUNCTION,N::Ftp::cwrite            ) ;
  ::curl_easy_setopt ( curl , CURLOPT_WRITEHEADER,this                        ) ;
  ::curl_easy_setopt ( curl , CURLOPT_WRITEDATA,this                          ) ;
  ::curl_easy_setopt ( curl , CURLOPT_VERBOSE,0L                              ) ;
  ///////////////////////////////////////////////////////////////////////////////
  if (connectionTimeout>0)                                                      {
    ::curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT_MS,connectionTimeout)        ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  if (mtimeout>0)                                                               {
    ::curl_easy_setopt(curl,CURLOPT_TIMEOUT_MS,mtimeout)                        ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  ::curl_easy_setopt ( curl , CURLOPT_USERAGENT  , AGENT . constData ( )      ) ;
  ::curl_easy_setopt ( curl , CURLOPT_COOKIEFILE , ""                         ) ;
  ///////////////////////////////////////////////////////////////////////////////
  QStringList keys = Requests.keys()                                            ;
  QString     K                                                                 ;
  ///////////////////////////////////////////////////////////////////////////////
  foreach ( K , keys )                                                          {
    if (K.toLower()=="proxy")                                                   {
      QByteArray BX = Requests[K].toUtf8()                                      ;
      ::curl_easy_setopt(curl,CURLOPT_PROXYTYPE,CURLPROXY_HTTP                ) ;
      ::curl_easy_setopt(curl,CURLOPT_PROXY,BX.constData()                    ) ;
    } else
    if (K.toLower()=="referer")                                                 {
      QUrl UR(Requests[K])                                                      ;
      QByteArray RDDR = UR.toEncoded(urlFormat)                                 ;
      ::curl_easy_setopt(curl,CURLOPT_REFERER,RDDR.data()                     ) ;
    }                                                                           ;
  }                                                                             ;
  result = ::curl_easy_perform ( curl                                         ) ;
  success = ( CURLE_OK == result )                                              ;
  finished ( success )                                                          ;
  if ( ! success )                                                              {
    ::curl_easy_cleanup ( curl )                                                ;
    Ftp::File = NULL                                                            ;
    Ftp::Url  = NULL                                                            ;
    QFile :: remove ( HtmlTmp )                                                 ;
    return false                                                                ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  QString    ImageUrl = ""                                                      ;
  QString    ImageLocation                                                      ;
  QUrl       imageUrl                                                           ;
  QByteArray AdXML                                                              ;
  int        realidx                                                            ;
  N::File::toByteArray(HtmlTmp,AdXML)                                           ;
  QFile :: remove ( HtmlTmp )                                                   ;
  realidx = AdXML . indexOf ( nexturl )                                         ;
  if ( ( AdXML.size() > 0 ) && ( realidx > 0 ) )                                {
    realidx += nexturl.length()                                                 ;
    nexturl  = "src=\""                                                         ;
    realidx  = AdXML.indexOf(nexturl,realidx)                                   ;
    if (realidx>0)                                                              {
      int endix                                                                 ;
      realidx += nexturl.length()                                               ;
      endix    = AdXML.indexOf("\"",realidx)                                    ;
      if (endix>0)                                                              {
        QByteArray B = AdXML.mid(realidx,endix-realidx)                         ;
        ImageUrl = QString::fromUtf8(B)                                         ;
        imageUrl = QUrl ( ImageUrl )                                            ;
      }                                                                         ;
    }                                                                           ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  if ( ImageUrl . length ( ) > 0 )                                              {
    ruid = assurePage ( SC , imageUrl )                                         ;
    if ( ruid > 0 )                                                             {
      QStringList ILL           = ImageUrl.split('/')                           ;
      QString     ImageFormat   = ILL.last()                                    ;
      QStringList ImageEXTs     = ImageFormat.split('.')                        ;
      QString     IEXT          = ImageEXTs.last()                              ;
      ImageFormat = QString("%1.%2").arg(ruid).arg(IEXT)                        ;
      ///////////////////////////////////////////////////////////////////////////
      ImageLocation = Temporary.absoluteFilePath(ImageFormat)                   ;
      QFile       ImageFile ( ImageLocation )                                   ;
      assureParent ( SC , ruid , puid )                                         ;
      ///////////////////////////////////////////////////////////////////////////
      Ftp::Operation =  Download                                                ;
      Ftp::File      = &ImageFile                                               ;
      Ftp::Url       = &imageUrl                                                ;
      Ftp::dlHeader  . clear ( )                                                ;
      ///////////////////////////////////////////////////////////////////////////
      QByteArray IADDR = imageUrl.toEncoded(urlFormat)                          ;
      starting           (  imageUrl , Download                               ) ;
      ::curl_easy_setopt ( curl , CURLOPT_URL,IADDR.data()                    ) ;
      ::curl_easy_setopt ( curl , CURLOPT_HEADERFUNCTION,N::Ftp::hwrite       ) ;
      ::curl_easy_setopt ( curl , CURLOPT_WRITEFUNCTION,N::Ftp::cwrite        ) ;
      ::curl_easy_setopt ( curl , CURLOPT_WRITEHEADER,this                    ) ;
      ::curl_easy_setopt ( curl , CURLOPT_WRITEDATA,this                      ) ;
      ::curl_easy_setopt ( curl , CURLOPT_VERBOSE,0L                          ) ;
      ///////////////////////////////////////////////////////////////////////////
      if (connectionTimeout>0)                                                  {
        ::curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT_MS,connectionTimeout)    ;
      }                                                                         ;
      ///////////////////////////////////////////////////////////////////////////
      if (mtimeout>0)                                                           {
        ::curl_easy_setopt(curl,CURLOPT_TIMEOUT_MS,mtimeout)                    ;
      }                                                                         ;
      ///////////////////////////////////////////////////////////////////////////
      ::curl_easy_setopt ( curl , CURLOPT_USERAGENT  , AGENT . constData ( )  ) ;
      ///////////////////////////////////////////////////////////////////////////
      ::curl_easy_setopt(curl,CURLOPT_REFERER,ADDR.data()                     ) ;
      ///////////////////////////////////////////////////////////////////////////
      QStringList keys = Requests.keys()                                        ;
      QString     K                                                             ;
      ///////////////////////////////////////////////////////////////////////////
      foreach ( K , keys )                                                      {
        if (K.toLower()=="proxy")                                               {
          QByteArray BX = Requests[K].toUtf8()                                  ;
          ::curl_easy_setopt(curl,CURLOPT_PROXYTYPE,CURLPROXY_HTTP            ) ;
          ::curl_easy_setopt(curl,CURLOPT_PROXY,BX.constData()                ) ;
        }                                                                       ;
      }                                                                         ;
      ///////////////////////////////////////////////////////////////////////////
      result = ::curl_easy_perform ( curl                                     ) ;
      success = ( CURLE_OK == result )                                          ;
      finished ( success )                                                      ;
      ///////////////////////////////////////////////////////////////////////////
    }                                                                           ;
  } else                                                                        {
    plan -> Debug ( 30 , QString("<%1> has different format?").arg(urlstring) ) ;
    plan -> Debug ( 30 , QString("Please check HTML and C/C++ source code")   ) ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  ::curl_easy_cleanup          ( curl                                         ) ;
  ///////////////////////////////////////////////////////////////////////////////
  Ftp::File = NULL                                                              ;
  Ftp::Url  = NULL                                                              ;
  if ( ! success )                                                              {
    QFile :: remove ( ImageLocation )                                           ;
    return success                                                              ;
  }                                                                             ;
  if ( ImageLocation.length() <= 0 ) return false                               ;
  ///////////////////////////////////////////////////////////////////////////////
  PictureManager :: Import ( SC , ImageLocation , image )                       ;
  QFile          :: remove ( ImageLocation              )                       ;
  ///////////////////////////////////////////////////////////////////////////////
  return success                                                                ;
}

#endif
