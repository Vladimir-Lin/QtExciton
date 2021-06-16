#include <exciton.h>
#include "ui_PaintingEncryptionTool.h"

N::PaintingEncryptionTool:: PaintingEncryptionTool (QWidget * parent,Plan * p)
                          : Widget                 (          parent,       p)
                          , ui                (new Ui::PaintingEncryptionTool)
{
  ui -> setupUi ( this ) ;
  nConnect ( ui->Back    , SIGNAL(clicked())   ,
             this        , SIGNAL(Back   ()) ) ;
  nConnect ( ui->Files   , SIGNAL(clicked())   ,
             this        , SIGNAL(Files  ()) ) ;
  nConnect ( ui->Picture , SIGNAL(clicked())   ,
             this        , SIGNAL(Picture()) ) ;
  nConnect ( ui->Key     , SIGNAL(clicked())   ,
             this        , SIGNAL(Key    ()) ) ;
  nConnect ( ui->Encrypt , SIGNAL(clicked())   ,
             this        , SIGNAL(Encrypt()) ) ;
}

N::PaintingEncryptionTool::~PaintingEncryptionTool(void)
{
  delete ui ;
}
