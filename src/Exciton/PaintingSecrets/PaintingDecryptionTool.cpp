#include <exciton.h>
#include "ui_PaintingDecryptionTool.h"

N::PaintingDecryptionTool:: PaintingDecryptionTool (QWidget * parent,Plan * p)
                          : Widget                 (          parent,       p)
                          , ui                (new Ui::PaintingDecryptionTool)
{
  ui -> setupUi ( this ) ;
  nConnect ( ui->Back    , SIGNAL(clicked())   ,
             this        , SIGNAL(Back   ()) ) ;
  nConnect ( ui->Picture , SIGNAL(clicked())   ,
             this        , SIGNAL(Picture()) ) ;
  nConnect ( ui->Key     , SIGNAL(clicked())   ,
             this        , SIGNAL(Key    ()) ) ;
  nConnect ( ui->Decrypt , SIGNAL(clicked())   ,
             this        , SIGNAL(Decrypt()) ) ;
}

N::PaintingDecryptionTool::~PaintingDecryptionTool(void)
{
  delete ui ;
}
