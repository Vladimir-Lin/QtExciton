#include <exciton.h>
#include "ui_PaintingFolderTool.h"

N::PaintingFolderTool:: PaintingFolderTool (QWidget * parent,Plan * p )
                      : Widget             (          parent,       p )
                      , ui                 (new Ui::PaintingFolderTool)
{
  ui -> setupUi ( this )                         ;
  nConnect ( ui->Back     , SIGNAL(clicked ())   ,
             this         , SIGNAL(Back    ()) ) ;
  nConnect ( ui->Join     , SIGNAL(clicked ())   ,
             this         , SIGNAL(Join    ()) ) ;
  nConnect ( ui->Edit     , SIGNAL(clicked ())   ,
             this         , SIGNAL(Edit    ()) ) ;
  nConnect ( ui->Delete   , SIGNAL(clicked ())   ,
             this         , SIGNAL(Delete  ()) ) ;
  nConnect ( ui->Text     , SIGNAL(clicked ())   ,
             this         , SIGNAL(Text    ()) ) ;
  nConnect ( ui->Recorder , SIGNAL(clicked ())   ,
             this         , SIGNAL(Recorder()) ) ;
}

N::PaintingFolderTool::~PaintingFolderTool(void)
{
  delete ui ;
}

void N::PaintingFolderTool::setSelected(int count)
{
  ui -> Join   -> setEnabled ( count > 0 ) ;
  ui -> Delete -> setEnabled ( count > 0 ) ;
}
