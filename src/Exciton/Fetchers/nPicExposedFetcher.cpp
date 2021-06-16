#include <exciton.h>

#define plan    PicturePlan
#define STARTPS "<br><img src=\""
#define ENDPS   "\""

N::PicExposedFetcher:: PicExposedFetcher ( Plan * p )
                     : TwoStepsFetcher   (        p )
{
  if (NotNull(plan))                        {
    Temporary = plan->Temporary("webcache") ;
  }                                         ;
}

N::PicExposedFetcher::~PicExposedFetcher (void)
{
}

bool N::PicExposedFetcher::VerifyUrl(QUrl & url)
{
  QString picexposed = "http://picexposed.com"                          ;
  QString imgpaying  = "http://imgpaying.com"                           ;
  QString imgclick   = "http://imgclick.net"                            ;
  QString urlstring  = url.toString()                                   ;
  bool    correct    = false                                            ;
  if ( ( ! correct ) && urlstring.contains(picexposed) ) correct = true ;
  if ( ( ! correct ) && urlstring.contains(imgpaying ) ) correct = true ;
  if ( ( ! correct ) && Requests.contains("proxy")                    ) {
    correct = urlstring . contains ( imgclick )                         ;
  }                                                                     ;
  return correct                                                        ;
}

bool N::PicExposedFetcher::Obtain (
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
           ENDPS                 ) ;
}
