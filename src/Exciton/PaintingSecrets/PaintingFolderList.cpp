#include <exciton.h>
#include "ui_PaintingFolderList.h"

N::PaintingFolderList:: PaintingFolderList (QWidget * parent,Plan * p )
                      : Widget             (          parent,       p )
                      , ui                 (new Ui::PaintingFolderList)
{
  Configure ( ) ;
}

N::PaintingFolderList::~PaintingFolderList(void)
{
  delete ui;
}

void N::PaintingFolderList::resizeEvent(QResizeEvent * event)
{
  QWidget :: resizeEvent ( event ) ;
  relocation             (       ) ;
}

void N::PaintingFolderList::showEvent(QShowEvent * event)
{
  QWidget :: showEvent ( event ) ;
  relocation           (       ) ;
}

void N::PaintingFolderList::Configure(void)
{
  ui -> setupUi ( this ) ;
}

void N::PaintingFolderList::relocation(void)
{
  ui -> Dirs -> resize ( width() - ui->Dirs->x() , ui->Dirs->height() ) ;
}

void N::PaintingFolderList::Back(void)
{
  emit CdUp ( ) ;
}

void N::PaintingFolderList::Go(void)
{
  QString path = ui->Dirs->currentText( ) ;
  emit Directory ( path )                 ;
}

void N::PaintingFolderList::Folders(bool topmost,QStringList folders)
{
  ui -> CdUp -> setEnabled   ( !topmost          ) ;
  ui -> Go   -> setEnabled   ( folders.count()>0 ) ;
  ui -> Dirs -> setEnabled   ( folders.count()>0 ) ;
  ui -> Dirs -> blockSignals ( true              ) ;
  ui -> Dirs -> clear        (                   ) ;
  ui -> Dirs -> addItems     ( folders           ) ;
  ui -> Dirs -> blockSignals ( false             ) ;
}
