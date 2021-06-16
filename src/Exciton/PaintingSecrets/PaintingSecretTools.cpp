#include <exciton.h>
#include "ui_PaintingSecretTools.h"

N::PaintingSecretTools:: PaintingSecretTools ( QWidget * parent , Plan * p )
                       : Widget              (           parent ,        p )
                       , ui                  ( new Ui::PaintingSecretTools )
{
  ui -> setupUi ( this )                             ;
  nConnect ( ui->Encryption , SIGNAL(clicked   ())   ,
             this           , SIGNAL(Encryption()) ) ;
  nConnect ( ui->Decryption , SIGNAL(clicked   ())   ,
             this           , SIGNAL(Decryption()) ) ;
  nConnect ( ui->Depot      , SIGNAL(clicked   ())   ,
             this           , SIGNAL(Depot     ()) ) ;
  nConnect ( ui->Settings   , SIGNAL(clicked   ())   ,
             this           , SIGNAL(Settings  ()) ) ;
  nConnect ( ui->Quit       , SIGNAL(clicked   ())   ,
             this           , SIGNAL(Quit      ()) ) ;
}

N::PaintingSecretTools::~PaintingSecretTools(void)
{
  delete ui ;
}

QSize N::PaintingSecretTools::sizeHint(void) const
{
  return QSize ( 300 , 40 ) ;
}
