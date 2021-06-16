#include <exciton.h>
#include "ui_PaintingViewTool.h"

N::PaintingViewTool:: PaintingViewTool (QWidget * parent,Plan * p )
                    : Widget           (          parent,       p )
                    , ui               (new Ui::PaintingViewTool  )
{
  ui -> setupUi ( this )                         ;
  nConnect ( ui->Back     , SIGNAL(clicked ())   ,
             this         , SIGNAL(Back    ()) ) ;
  nConnect ( ui->ZoomIn   , SIGNAL(clicked ())   ,
             this         , SIGNAL(ZoomIn  ()) ) ;
  nConnect ( ui->ZoomOut  , SIGNAL(clicked ())   ,
             this         , SIGNAL(ZoomOut ()) ) ;
}

N::PaintingViewTool::~PaintingViewTool(void)
{
  delete ui ;
}
