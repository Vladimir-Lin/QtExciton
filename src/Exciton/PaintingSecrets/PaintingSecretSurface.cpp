#include <exciton.h>

N::PaintingSecretSurface:: PaintingSecretSurface (QWidget * parent)
                         : QWidget               (          parent)
                         , progress              (NULL            )
                         , indicator             (NULL            )
{
}

N::PaintingSecretSurface::~PaintingSecretSurface (void)
{
}

void N::PaintingSecretSurface::showEvent(QShowEvent * event)
{
  QWidget :: showEvent   ( event ) ;
  relocation             (       ) ;
}

void N::PaintingSecretSurface::resizeEvent (QResizeEvent * event)
{
  QWidget :: resizeEvent ( event ) ;
  relocation             (       ) ;
}

void N::PaintingSecretSurface::paintEvent(QPaintEvent * event)
{ Q_UNUSED      ( event            ) ;
  QPainter p    ( this             ) ;
  p . drawImage ( 0 , 0 , Painting ) ;
}

QImage N::PaintingSecretSurface::Cut(void)
{
  QImage I                             ;
  QImage S                             ;
  int    x  = 0                        ;
  int    y  = 0                        ;
  int    w  = 0                        ;
  int    h  = 0                        ;
  double wf = width       ( )          ;
  double hf = height      ( )          ;
  wf /= Background.width  ( )          ;
  hf /= Background.height ( )          ;
  if (wf<hf)                           {
    y   = 0                            ;
    h   = Background.height()          ;
    wf  = width  ( )                   ;
    wf /= height ( )                   ;
    wf *= h                            ;
    w   = wf                           ;
    x   = Background.width ()          ;
    x  -= w                            ;
    x  /= 2                            ;
    x  += Background.width () * 3 / 16 ;
    if ((x+w)>Background.width())      {
      x = Background.width() - w       ;
    }                                  ;
  } else                               {
    x   = 0                            ;
    w   = Background.width ()          ;
    hf  = height ( )                   ;
    hf /= width  ( )                   ;
    hf *= w                            ;
    h   = hf                           ;
    y   = Background.height()          ;
    y  -= h                            ;
    y  /= 2                            ;
  }                                    ;
  S = Background.copy(x,y,w,h)         ;
  I = S.scaled                         (
        size()                         ,
        Qt::KeepAspectRatio            ,
        Qt::SmoothTransformation )     ;
  return I                             ;
}

void N::PaintingSecretSurface::relocation (void)
{
  QColor   w = QColor ( 255 , 255 , 255           ) ;
  QSize    s = size   (                           ) ;
  ///////////////////////////////////////////////////
  Mutex      . lock   (                           ) ;
  Painting   = QImage ( s , QImage::Format_ARGB32 ) ;
  Drawing    = QImage ( s , QImage::Format_ARGB32 ) ;
  Painting   . fill   ( w                         ) ;
  Drawing    . fill   ( w                         ) ;
  ///////////////////////////////////////////////////
  Painting   = Cut    (                           ) ;
  ///////////////////////////////////////////////////
  MoveIndicator       (                           ) ;
  Mutex      . unlock (                           ) ;
}

void N::PaintingSecretSurface::StartBusy(N::Plan * plan,int total)
{
  if (IsNull(indicator))                          {
    QColor green ( 0 , 255 , 0 )                  ;
    indicator  = new ProgressIndicator(this,plan) ;
    indicator -> setColor           ( green     ) ;
    indicator -> setAnimationDelay  ( 100       ) ;
    indicator -> show               (           ) ;
  }                                               ;
  if (IsNull(progress))                           {
    progress  = new QProgressBar ( this         ) ;
    progress -> setTextVisible   ( false        ) ;
    progress -> hide             (              ) ;
    progress -> setRange         ( 0 , total    ) ;
  }                                               ;
  MoveIndicator ( )                               ;
  indicator->startAnimation()                     ;
}

void N::PaintingSecretSurface::StopBusy(void)
{
  if (IsNull(indicator)) return        ;
  int cnt = indicator->stopAnimation() ;
  if (cnt<=0)                          {
    indicator -> deleteLater ( )       ;
    indicator  = NULL                  ;
  }                                    ;
  if (IsNull(progress)) return         ;
  progress -> deleteLater ( )          ;
  progress  = NULL                     ;
}

void N::PaintingSecretSurface::setStep(int index)
{
  if (IsNull(progress)) return   ;
  if (index>0)                   {
    progress -> show ( )         ;
  }                              ;
  progress -> setValue ( index ) ;
}

void N::PaintingSecretSurface::MoveIndicator(void)
{
  if (IsNull(indicator)) return           ;
  int w = width ()                        ;
  int h = height()                        ;
  int x = w / 2                           ;
  int y = h / 2                           ;
  indicator -> move   ( x - 20 , y - 20 ) ;
  indicator -> resize (     40 ,     40 ) ;
  if (IsNull(progress)) return            ;
  y = h - 12                              ;
  progress  -> move   ( 0      , y      ) ;
  progress  -> resize ( w      , 12     ) ;
}
