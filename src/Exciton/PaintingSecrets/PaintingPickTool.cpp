#include <exciton.h>
#include "ui_PaintingPickTool.h"

N::PaintingPickTool:: PaintingPickTool (QWidget * parent,Plan * p )
                    : Widget           (          parent,       p )
                    , ui               (new Ui::PaintingPickTool  )
                    , canPick          (true                      )
{
  ui -> setupUi ( this )                          ;
  nConnect ( ui->Back     , SIGNAL(clicked  ())   ,
             this         , SIGNAL(Back     ()) ) ;
  nConnect ( ui->Pick     , SIGNAL(clicked  ())   ,
             this         , SIGNAL(Pick     ()) ) ;
  nConnect ( ui->View     , SIGNAL(clicked  ())   ,
             this         , SIGNAL(View     ()) ) ;
  nConnect ( ui->Previous , SIGNAL(clicked  ())   ,
             this         , SIGNAL(Previous ()) ) ;
  nConnect ( ui->Next     , SIGNAL(clicked  ())   ,
             this         , SIGNAL(Next     ()) ) ;
  nConnect ( ui->Import   , SIGNAL(clicked  ())   ,
             this         , SIGNAL(Import   ()) ) ;
}

N::PaintingPickTool::~PaintingPickTool(void)
{
  delete ui ;
}

void N::PaintingPickTool::Full(int index,bool full)
{
  ui -> Pick     -> setEnabled ( canPick   ) ;
  ui -> View     -> setEnabled ( false     ) ;
  ui -> Previous -> setEnabled ( index > 0 ) ;
  ui -> Next     -> setEnabled ( full      ) ;
}

void N::PaintingPickTool::Empty(void)
{
  ui -> Pick     -> setEnabled ( false ) ;
  ui -> View     -> setEnabled ( false ) ;
  ui -> Next     -> setEnabled ( false ) ;
}

void N::PaintingPickTool::FileSelected(QString path)
{
  ui -> View -> setEnabled ( path.length() > 0 ) ;
}
