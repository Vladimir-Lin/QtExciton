#include <exciton.h>

#define plan    PicturePlan
#define STARTPS "onload=\"scale(this);\" onclick=\"scale(this);\""
#define MIDPS   "src=\""
#define ENDPS   "\""

N::ImageDinoFetcher:: ImageDinoFetcher ( Plan * p )
                    : TwoStepsFetcher  (        p )
{
  if (NotNull(plan))                        {
    Temporary = plan->Temporary("webcache") ;
  }                                         ;
}

N::ImageDinoFetcher::~ImageDinoFetcher (void)
{
}

bool N::ImageDinoFetcher::VerifyUrl(QUrl & url)
{
  QString imgdino   = "http://imgdino.com/viewer.php?file="           ;
  QString imgchili  = "http://imgchili.net/show/"                     ;
  QString urlstring = url.toString()                                  ;
  bool    correct   = false                                           ;
  if ( ( ! correct ) && urlstring.contains(imgdino ) ) correct = true ;
  if ( ( ! correct ) && urlstring.contains(imgchili) ) correct = true ;
  return correct                                                      ;
}

bool N::ImageDinoFetcher::Obtain (
       SqlConnection & SC        ,
       QUrl            url       ,
       SUID            puid      ,
       SUID          & ruid      ,
       SUID          & image     ,
       int             mtimeout  )
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
