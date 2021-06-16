#include <exciton.h>
#include "ui_PaintingTextTool.h"

N::PaintingTextTool:: PaintingTextTool (QWidget * parent,Plan * p)
                    : Widget           (          parent,       p)
                    , ui               (new Ui::PaintingTextTool )
{
  ui -> setupUi ( this )                       ;
  nConnect ( ui->Back    , SIGNAL(clicked())   ,
             this        , SIGNAL(Back   ()) ) ;
  nConnect ( ui->New     , SIGNAL(clicked())   ,
             this        , SIGNAL(New    ()) ) ;
  nConnect ( ui->Save    , SIGNAL(clicked())   ,
             this        , SIGNAL(Save   ()) ) ;
}

N::PaintingTextTool::~PaintingTextTool(void)
{
  delete ui ;
}
