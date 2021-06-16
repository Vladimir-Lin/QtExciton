#include <exciton.h>
#include "ui_PaintingSettingsTool.h"

N::PaintingSettingsTool:: PaintingSettingsTool (QWidget * parent,Plan * p)
                        : Widget               (          parent,       p)
                        , ui                (new Ui::PaintingSettingsTool)
{
  ui -> setupUi ( this )                         ;
  nConnect ( ui->Back     , SIGNAL(clicked ())   ,
             this         , SIGNAL(Back    ()) ) ;
  nConnect ( ui->Ftp      , SIGNAL(clicked ())   ,
             this         , SIGNAL(Ftp     ()) ) ;
  nConnect ( ui->Language , SIGNAL(clicked ())   ,
             this         , SIGNAL(Language()) ) ;
  nConnect ( ui->Fonts    , SIGNAL(clicked ())   ,
             this         , SIGNAL(Fonts   ()) ) ;
  nConnect ( ui->Display  , SIGNAL(clicked ())   ,
             this         , SIGNAL(Display ()) ) ;
  nConnect ( ui->Help     , SIGNAL(clicked ())   ,
             this         , SIGNAL(Help    ()) ) ;
}

N::PaintingSettingsTool::~PaintingSettingsTool(void)
{
  delete ui ;
}
