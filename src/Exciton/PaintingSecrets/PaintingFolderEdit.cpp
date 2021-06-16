#include <exciton.h>
#include "ui_PaintingFolderEdit.h"

N::PaintingFolderEdit:: PaintingFolderEdit (QWidget * parent,Plan * p )
                      : Widget             (          parent,       p )
                      , ui                 (new Ui::PaintingFolderEdit)
{
  ui -> setupUi ( this )                            ;
  nConnect ( ui->Back      , SIGNAL(clicked   ())   ,
             this          , SIGNAL(Back      ()) ) ;
  nConnect ( ui->Rename    , SIGNAL(clicked   ())   ,
             this          , SIGNAL(Rename    ()) ) ;
  nConnect ( ui->Move      , SIGNAL(clicked   ())   ,
             this          , SIGNAL(Move      ()) ) ;
  nConnect ( ui->Directory , SIGNAL(clicked   ())   ,
             this          , SIGNAL(Directory ()) ) ;
  nConnect ( ui->Edit      , SIGNAL(clicked   ())   ,
             this          , SIGNAL(Edit      ()) ) ;
  nConnect ( ui->Ftp       , SIGNAL(clicked   ())   ,
             this          , SIGNAL(Ftp       ()) ) ;
}

N::PaintingFolderEdit::~PaintingFolderEdit(void)
{
  delete ui ;
}

void N::PaintingFolderEdit::setSelected(int count)
{
  ui -> Rename -> setEnabled ( count > 0 ) ;
  ui -> Move   -> setEnabled ( count > 0 ) ;
}

void N::PaintingFolderEdit::setEdit(bool enable)
{
  ui -> Edit -> setEnabled ( enable ) ;
}
