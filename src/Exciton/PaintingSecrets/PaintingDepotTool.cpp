#include <exciton.h>
#include "ui_PaintingDepotTool.h"

N::PaintingDepotTool:: PaintingDepotTool (QWidget * parent,Plan * p)
                     : Widget            (          parent,       p)
                     , ui                (new Ui::PaintingDepotTool)
{
  ui -> setupUi ( this )                           ;
  nConnect ( ui->Back      , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Back     ()) ) ;
  nConnect ( ui->List      , SIGNAL(clicked  ())   ,
             this          , SIGNAL(List     ()) ) ;
  nConnect ( ui->Pictures  , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Pictures ()) ) ;
  nConnect ( ui->Keys      , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Keys     ()) ) ;
  nConnect ( ui->Encrypted , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Encrypted()) ) ;
  nConnect ( ui->Ftp       , SIGNAL(clicked  ())   ,
             this          , SIGNAL(Ftp      ()) ) ;
}

N::PaintingDepotTool::~PaintingDepotTool(void)
{
  delete ui ;
}
