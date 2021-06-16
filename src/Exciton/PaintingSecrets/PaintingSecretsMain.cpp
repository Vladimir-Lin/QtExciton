#include <exciton.h>

int PaintingSecretsMain(int argc,char ** argv)
{
  #ifdef Q_OS_ANDROID
  QString U = "CIOS"                                                ;
  QString Q = "PaintingSecret.qm"                                   ;
  QString D = "Users/PaintingSecret.ndb"                            ;
  ///////////////////////////////////////////////////////////////////
  N :: AndroidPreparation       ( D , "assets:/Arena.tar.xz"      ) ;
  #endif
  #ifdef Q_OS_IOS
  QString U = "CIOS"                                                ;
  QString Q = "PaintingSecrets.qm"                                  ;
  QString D = "Users/PaintingSecrets.ndb"                           ;
  ///////////////////////////////////////////////////////////////////
  N :: ApplePreparation  ( D,"PaintingSecrets.app","Arena.tar.xz" ) ;
  #endif
  #if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
  QString U = "CIOS"                                                ;
  QString Q = "PaintingSecrets.qm"                                  ;
  QString D = "Users/PaintingSecrets.ndb"                           ;
  #endif
  QTranslator     T                                                 ;
  QApplication    a             ( argc , argv                     ) ;
  N::Install                    ( argc , argv , a , T , U , Q , D ) ;
  PaintingSecrets w             ( argc , argv                     ) ;
  if (w.bootup()) return a.exec (                                 ) ;
  return w . abort              (                                 ) ;
}
