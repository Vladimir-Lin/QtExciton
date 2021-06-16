#include <exciton.h>

#define plan NetPlan

N::JpTorrentFetcher:: JpTorrentFetcher ( Plan * p )
                    : TwoStepsFetcher  (        p )
{
  if (NotNull(plan))                        {
    Temporary = plan->Temporary("webcache") ;
  }                                         ;
}

N::JpTorrentFetcher::~JpTorrentFetcher (void)
{
}

bool N::JpTorrentFetcher::Obtain (
       SqlConnection & SC        ,
       QUrl            url       ,
       SUID            puid      ,
       SUID          & ruid      ,
       QString       & torrent   ,
       int             mtimeout  )
{
  QString jptorrent  = ".jptorrent.org/link.php?ref="                           ;
  QString nexturl   = "<FORM name=\"form1\" action='"                           ;
  QString urlstring = url.toString()                                            ;
  bool    correct   = false                                                     ;
  if ( ( ! correct ) && urlstring.contains(jptorrent) ) correct = true          ;
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
  torrent        = ""                                                           ;
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
  QString    TorrentUrl      = ""                                               ;
  QString    TorrentName     = ""                                               ;
  QString    TorrentLocation                                                    ;
  QString    PostFields                                                         ;
  QUrl       torrentUrl                                                         ;
  QUrl       virtualUrl                                                         ;
  QByteArray btXML                                                              ;
  int        realidx                                                            ;
  N::File::toByteArray(HtmlTmp,btXML)                                           ;
  QFile :: remove ( HtmlTmp )                                                   ;
  realidx = btXML . indexOf ( nexturl.toUtf8() )                                         ;
  if ( ( btXML.size() > 0 ) && ( realidx > 0 ) )                                {
    realidx += nexturl.length()                                                 ;
    if (realidx>0)                                                              {
      int endix                                                                 ;
      endix    = btXML.indexOf("'",realidx)                                     ;
      if (endix>0)                                                              {
        QString     H   = urlstring                                             ;
        QByteArray  B   = btXML.mid(realidx,endix-realidx)                      ;
        QString     PHP = QString::fromUtf8(B)                                  ;
        QString     A                                                           ;
        QStringList L                                                           ;
        H               = H . replace         ( "http://" , "" )                ;
        L               = H . split           ( '/'            )                ;
        A               = L . first           (                )                ;
        TorrentName     = L . last            (                )                ;
        L               = TorrentName . split ( '?'            )                ;
        TorrentName     = L . last            (                )                ;
        L               = TorrentName . split ( '='            )                ;
        TorrentName     = L . last            (                )                ;
        TorrentUrl      = QString("http://%1/%2").arg(A).arg(PHP)               ;
        torrentUrl      = QUrl ( TorrentUrl )                                   ;
        PostFields      = QString("ref=%1").arg(TorrentName)                    ;
        H               = QString("%1?%2").arg(TorrentUrl).arg(PostFields)      ;
        virtualUrl      = QUrl ( H )                                            ;
        TorrentLocation = QString("%1.torrent").arg(TorrentName)                ;
        TorrentLocation = Temporary.absoluteFilePath(TorrentLocation)           ;
      }                                                                         ;
    }                                                                           ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  if ( ( TorrentUrl      . length ( ) > 0 )                                    &&
       ( TorrentLocation . length ( ) > 0 )                                    &&
       ( PostFields      . length ( ) > 0 )                                   ) {
    ruid = assurePage ( SC , virtualUrl )                                       ;
    if ( ruid > 0 )                                                             {
      QFile      TorrentFile ( TorrentLocation )                                ;
      QByteArray FIELDs = PostFields.toUtf8()                                   ;
      assureParent ( SC , ruid , puid )                                         ;
      ///////////////////////////////////////////////////////////////////////////
      Ftp::Operation =  Download                                                ;
      Ftp::File      = &TorrentFile                                             ;
      Ftp::Url       = &torrentUrl                                              ;
      Ftp::dlHeader  . clear ( )                                                ;
      ///////////////////////////////////////////////////////////////////////////
      QByteArray IADDR = torrentUrl.toEncoded(urlFormat)                        ;
      starting           (  virtualUrl , Download                             ) ;
      ::curl_easy_setopt ( curl , CURLOPT_URL            , IADDR.data()       ) ;
      ::curl_easy_setopt ( curl , CURLOPT_POST           , 1                  ) ;
      ::curl_easy_setopt ( curl , CURLOPT_POSTFIELDS     , FIELDs.data()      ) ;
      ::curl_easy_setopt ( curl , CURLOPT_HEADERFUNCTION , N::Ftp::hwrite     ) ;
      ::curl_easy_setopt ( curl , CURLOPT_WRITEFUNCTION  , N::Ftp::cwrite     ) ;
      ::curl_easy_setopt ( curl , CURLOPT_WRITEHEADER    , this               ) ;
      ::curl_easy_setopt ( curl , CURLOPT_WRITEDATA      , this               ) ;
      ::curl_easy_setopt ( curl , CURLOPT_VERBOSE        , 0L                 ) ;
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
    QFile :: remove ( TorrentLocation )                                         ;
    return success                                                              ;
  }                                                                             ;
  ///////////////////////////////////////////////////////////////////////////////
  torrent = TorrentLocation                                                     ;
  ///////////////////////////////////////////////////////////////////////////////
  return success                                                                ;
}
