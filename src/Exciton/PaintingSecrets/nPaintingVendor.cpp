#include <exciton.h>

N::PaintingVendor:: PaintingVendor (QWidget * parent,Plan * p)
                  : PaintWidget    (          parent,       p)
                  , Tools          (NULL                     )
                  , Docked         (false                    )
{
  Configure ( ) ;
}

N::PaintingVendor::~PaintingVendor(void)
{
}

QSize N::PaintingVendor::sizeHint(void) const
{
  if ( plan  -> Booleans [ "Desktop" ] ) {
    return QSize ( 1280 ,  900 )         ;
  } else
  if ( plan  -> Booleans [ "Pad"     ] ) {
    return QSize ( 1024 ,  720 )         ;
  } else
  if ( plan  -> Booleans [ "Phone"   ] ) {
    return QSize (  320 ,  480 )         ;
  }                                      ;
  return   QSize ( 1024 ,  720 )         ;
}

void N::PaintingVendor::Configure(void)
{
  if ( plan  -> Booleans [ "Pad" ] || plan  -> Booleans [ "Phone" ] ) {
    allowGesture = true                                               ;
    grabGesture                   ( Qt::TapGesture                  ) ;
    grabGesture                   ( Qt::TapAndHoldGesture           ) ;
    grabGesture                   ( Qt::PanGesture                  ) ;
    grabGesture                   ( Qt::PinchGesture                ) ;
    grabGesture                   ( Qt::SwipeGesture                ) ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  Tools = new PaintingSecretTools ( this , plan                     ) ;
}

QImage N::PaintingVendor::Cut(void)
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

void N::PaintingVendor::relocation (void)
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
  Mutex      . unlock (                           ) ;
  ///////////////////////////////////////////////////
  if (Docked && NotNull(Tools))                     {
    QSize r(s.width(),40)                           ;
    Tools -> move   ( 0 , s.height() - 40 )         ;
    Tools -> resize ( r                   )         ;
  }                                                 ;
}

void N::PaintingVendor::startup(void)
{
  int w = width   (        )                                            ;
  int h = height  (        )                                            ;
  int d = w / 20                                                        ;
  int y = h - 40                                                        ;
  ///////////////////////////////////////////////////////////////////////
  Painting = Cut  (        )                                            ;
  emit reflush    (        )                                            ;
  plan -> processEvents (  )                                            ;
  ///////////////////////////////////////////////////////////////////////
  Tools -> resize ( w , 40 )                                            ;
  for (int i=0;i<=20;i++)                                               {
    int x = (20-i) * d                                                  ;
    Tools -> move ( x , y  )                                            ;
    emit reflush  (        )                                            ;
    plan -> processEvents( )                                            ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  QPalette P                                                            ;
  QString  T                                                            ;
  QFont    f = font ( )                                                 ;
  f . setPixelSize ( 60 )                                               ;
  ///////////////////////////////////////////////////////////////////////
  QMap<int,QLabel *> Labels                                             ;
  ///////////////////////////////////////////////////////////////////////
  Labels [ 0 ]  = new QLabel ( this             )                       ;
  Labels [ 1 ]  = new QLabel ( this             )                       ;
  Labels [ 2 ]  = new QLabel ( this             )                       ;
  Labels [ 3 ]  = new QLabel ( this             )                       ;
  Labels [ 0 ] -> move       (     10 ,      10 )                       ;
  Labels [ 0 ] -> resize     ( w - 20 ,      50 )                       ;
  Labels [ 1 ] -> move       (     10 ,      70 )                       ;
  Labels [ 1 ] -> resize     ( w - 20 ,      50 )                       ;
  Labels [ 2 ] -> move       (     10 , h - 140 )                       ;
  Labels [ 2 ] -> resize     ( w - 20 ,      70 )                       ;
  Labels [ 3 ] -> move       (     10 , h - 180 )                       ;
  Labels [ 3 ] -> resize     ( w - 20 ,      30 )                       ;
  ///////////////////////////////////////////////////////////////////////
  Labels [ 2 ] -> setFont    ( f                )                       ;
  f . setPixelSize           ( 40               )                       ;
  f . setItalic              ( true             )                       ;
  Labels [ 0 ] -> setFont    ( f                )                       ;
  Labels [ 1 ] -> setFont    ( f                )                       ;
  f = font ( )                                                          ;
  f . setPixelSize           ( 24               )                       ;
  Labels [ 3 ] -> setFont    ( f                )                       ;
  ///////////////////////////////////////////////////////////////////////
  Labels [ 0 ] -> setAlignment( Qt::AlignLeft  | Qt::AlignVCenter     ) ;
  Labels [ 1 ] -> setAlignment( Qt::AlignCenter                       ) ;
  Labels [ 2 ] -> setAlignment( Qt::AlignCenter                       ) ;
  Labels [ 3 ] -> setAlignment( Qt::AlignRight | Qt::AlignVCenter     ) ;
  ///////////////////////////////////////////////////////////////////////
  P = Labels [ 0 ] -> palette  (   )                                    ;
  P . setColor ( QPalette::WindowText , QColor ( 255 , 255 , 255 ) )    ;
  for (int i=0;i<4;i++)                                                 {
    Labels [ i ] -> setPalette ( P )                                    ;
    Labels [ i ] -> show       (   )                                    ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  T = "Painting"                                                        ;
  for (int i=0;i<=T.length();i++)                                       {
    QString L = T . left    ( i )                                       ;
    Labels [ 0 ] -> setText ( L )                                       ;
    emit reflush            (   )                                       ;
    plan -> processEvents   (   )                                       ;
  }                                                                     ;
  T = "Secrets"                                                         ;
  for (int i=0;i<=T.length();i++)                                       {
    QString L = T . left    ( i )                                       ;
    Labels [ 1 ] -> setText ( L )                                       ;
    emit reflush            (   )                                       ;
    plan -> processEvents   (   )                                       ;
  }                                                                     ;
  if (plan->LanguageId!=1819)                                           {
    T = tr("Painting Secrets")                                          ;
    for (int i=0;i<=T.length();i++)                                     {
      QString L = T . left    ( i )                                     ;
      Labels [ 2 ] -> setText ( L )                                     ;
      emit reflush            (   )                                     ;
      plan -> processEvents   (   )                                     ;
    }                                                                   ;
  }                                                                     ;
  T  = tr("Vendor : Neutrino")                                          ;
  T += ", Beta 2  "                                                     ;
  T += " "                                                              ;
  T += tr("Encrypt any data and hide it in your selected picture")      ;
  T += "                                              "                 ;
  T += "                                              "                 ;
  T += "                                              "                 ;
  T += "                                              "                 ;
  for (int i=0;i<=T.length();i++)                                       {
    QString L = T . left    ( i )                                       ;
    Labels [ 3 ] -> setText ( L )                                       ;
    emit reflush            (   )                                       ;
    plan -> processEvents   (   )                                       ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  Time :: skip ( 500 )                                                  ;
  for (int i=0;i<=25;i++)                                               {
    double o = 0.04 * ( 25 - i )                                        ;
    int    a = (int)(o * 255)                                           ;
    if (a>255) a = 255                                                  ;
    if (a<0  ) a = 0                                                    ;
    P . setColor ( QPalette::WindowText,QColor( 255,255,255,a ) )       ;
    Labels [ 0 ] -> setPalette ( P )                                    ;
    Labels [ 1 ] -> setPalette ( P )                                    ;
    Labels [ 2 ] -> setPalette ( P )                                    ;
    Labels [ 3 ] -> setPalette ( P )                                    ;
    Labels [ 0 ] -> update     (   )                                    ;
    Labels [ 1 ] -> update     (   )                                    ;
    Labels [ 2 ] -> update     (   )                                    ;
    Labels [ 3 ] -> update     (   )                                    ;
    emit reflush               (   )                                    ;
    plan -> processEvents      (   )                                    ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  for (int i=0;i<4;i++) Labels [ i ] -> deleteLater ( )                 ;
  Labels . clear ( )                                                    ;
  ///////////////////////////////////////////////////////////////////////
  Alert           ( Menu   )                                            ;
  ///////////////////////////////////////////////////////////////////////
  nConnect ( Tools , SIGNAL(Encryption())                               ,
             this  , SIGNAL(Encryption())                             ) ;
  nConnect ( Tools , SIGNAL(Decryption())                               ,
             this  , SIGNAL(Decryption())                             ) ;
  nConnect ( Tools , SIGNAL(Depot     ())                               ,
             this  , SIGNAL(Depot     ())                             ) ;
  nConnect ( Tools , SIGNAL(Settings  ())                               ,
             this  , SIGNAL(Settings  ())                             ) ;
  nConnect ( Tools , SIGNAL(Quit      ())                               ,
             this  , SIGNAL(Quit      ())                             ) ;
  Docked   = true                                                       ;
}

bool N::PaintingVendor::acceptTap(QTapGesture * gesture)
{ Q_UNUSED ( gesture ) ;
  return true          ;
}

bool N::PaintingVendor::acceptTapHold(QTapAndHoldGesture * gesture)
{ Q_UNUSED ( gesture ) ;
  return true          ;
}

bool N::PaintingVendor::acceptPan(QPanGesture * gesture)
{ Q_UNUSED ( gesture ) ;
  return true          ;
}

bool N::PaintingVendor::acceptPinch(QPinchGesture * gesture)
{ Q_UNUSED ( gesture ) ;
  return true          ;
}

bool N::PaintingVendor::acceptSwipe(QSwipeGesture * gesture)
{ Q_UNUSED ( gesture ) ;
  return true          ;
}

bool N::PaintingVendor::acceptCustom(QGesture * gesture)
{ Q_UNUSED ( gesture ) ;
  return true          ;
}
