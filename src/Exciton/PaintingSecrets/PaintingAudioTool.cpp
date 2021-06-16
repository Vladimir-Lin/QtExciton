#include <exciton.h>
#include "ui_PaintingAudioTool.h"

N::PaintingAudioTool:: PaintingAudioTool (QWidget * parent,Plan * p )
                     : Widget            (          parent,       p )
                     , ui                (new Ui::PaintingAudioTool )
{
  ui -> setupUi ( this )                       ;
  nConnect ( ui->Back    , SIGNAL(clicked())   ,
             this        , SIGNAL(Back   ()) ) ;
  nConnect ( ui->New     , SIGNAL(clicked())   ,
             this        , SIGNAL(New    ()) ) ;
  nConnect ( ui->Start   , SIGNAL(clicked())   ,
             this        , SIGNAL(Start  ()) ) ;
  nConnect ( ui->Stop    , SIGNAL(clicked())   ,
             this        , SIGNAL(Stop   ()) ) ;
}

N::PaintingAudioTool::~PaintingAudioTool(void)
{
  delete ui ;
}

void N::PaintingAudioTool::EnableNew(bool enable)
{
  ui -> New   -> setEnabled ( enable ) ;
}

void N::PaintingAudioTool::EnableStart(bool enable)
{
  ui -> Start -> setEnabled ( enable ) ;
}

void N::PaintingAudioTool::EnableStop(bool enable)
{
  ui -> Stop  -> setEnabled ( enable ) ;
}
