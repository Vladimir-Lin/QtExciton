#include <exciton.h>
#include "ui_PaintingFilesTool.h"

N::PaintingFilesTool:: PaintingFilesTool (QWidget * parent,Plan * p)
                     : Widget            (          parent,       p)
                     , ui                (new Ui::PaintingFilesTool)
{
  ui -> setupUi ( this )                           ;
  nConnect ( ui->Back      , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Back     ()) ) ;
  nConnect ( ui->New       , SIGNAL(clicked  ())   ,
             this          , SIGNAL(New      ()) ) ;
  nConnect ( ui->Add       , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Add      ()) ) ;
  nConnect ( ui->Remove    , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Remove   ()) ) ;
  nConnect ( ui->Packaging , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Packaging()) ) ;
}

N::PaintingFilesTool::~PaintingFilesTool(void)
{
  delete ui ;
}

void N::PaintingFilesTool::setDeletion(bool enable)
{
  ui -> Remove -> setEnabled ( enable ) ;
}

void N::PaintingFilesTool::setPackaging(bool enable)
{
  ui -> Packaging -> setEnabled ( enable ) ;
}
