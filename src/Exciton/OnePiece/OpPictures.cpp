#include <exciton.h>

#include "ui_OnePiecePictures.h"

N::OpPictures:: OpPictures ( QWidget * parent , Plan * p )
              : Widget     (           parent ,        p )
              , ui         ( new Ui::OnePiecePictures    )
{
  ui -> setupUi ( this ) ;
}

N::OpPictures::~OpPictures(void)
{
  delete ui ;
}

bool N::OpPictures::isSkip(void)
{
  return ui -> OpSkip -> isChecked ( ) ;
}

bool N::OpPictures::isCache(void)
{
  return ui -> OpCache -> isChecked ( ) ;
}

bool N::OpPictures::isVolume(void)
{
  return ui -> isVolume -> isChecked ( ) ;
}

int N::OpPictures::OpStart(void)
{
    return ui -> OpStart -> value ( ) ;
}

int N::OpPictures::VolStart(void)
{
    return ui -> VolStart -> value ( ) ;
}

int N::OpPictures::VolEnd(void)
{
  return ui -> VolEnd -> value ( ) ;
}

QString N::OpPictures::OpRoot(void)
{
  return ui -> OpRoot -> text ( ) ;
}

SUID N::OpPictures::Gallery(void)
{
  if (IsNull(gallery)) return 0 ;
  return gallery->toUuid()      ;
}

void N::OpPictures::prepare(void)
{
  gallery = new ComboBox ( this , plan           )   ;
  gallery-> setGeometry  (  20 , 300 , 440 ,  28 )   ;
  gallery-> setEditable  ( true                  )   ;
  ////////////////////////////////////////////////////
  nConnect ( gallery , SIGNAL(activated     (int))   ,
             this    , SLOT  (GalleryChanged(int)) ) ;
  ////////////////////////////////////////////////////
  plan -> setFont ( this )                           ;
}

void N::OpPictures::configure (QString scope,Sql & sql)
{
  QString Q                                               ;
  QString CN = QtUUID::createUuidString()                   ;
  CMAPs         NM                                        ;
  /////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql )                          ;
  GroupItems    GI ( plan      )                          ;
  if (SC.open("configure",CN))                            {
    UUIDs   U                                             ;
    SUID    u                                             ;
    QString n                                             ;
    ///////////////////////////////////////////////////////
    U = GI . Groups                                       (
          SC                                              ,
          Types::Gallery                                  ,
          SC.OrderByAsc("position")                     ) ;
    gallery -> blockSignals ( true   )                    ;
    gallery -> addItems     ( SC , U )                    ;
    gallery -> blockSignals ( false  )                    ;
    ///////////////////////////////////////////////////////
    SC.close()                                            ;
  }                                                       ;
  SC.remove()                                             ;
  /////////////////////////////////////////////////////////
  plan->site.beginGroup   ( scope                       ) ;
  if (plan->site.contains("OpSkip"))                      {
    bool skip                                             ;
    skip = plan->site.value("OpSkip").toBool()            ;
    ui->OpSkip->blockSignals(true )                       ;
    ui->OpSkip->setChecked  (skip )                       ;
    ui->OpSkip->blockSignals(false)                       ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if (plan->site.contains("OpCache"))                     {
    bool skip                                             ;
    skip = plan->site.value("OpCache").toBool()           ;
    ui->OpCache->blockSignals(true )                      ;
    ui->OpCache->setChecked  (skip )                      ;
    ui->OpCache->blockSignals(false)                      ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if (plan->site.contains("isVolume"))                    {
    bool skip                                             ;
    skip = plan->site.value("isVolume").toBool()          ;
    ui->isVolume->blockSignals(true )                     ;
    ui->isVolume->setChecked  (skip )                     ;
    ui->isVolume->blockSignals(false)                     ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if (plan->site.contains("OpStart"))                     {
    int stId                                              ;
    stId = plan->site.value("OpStart").toInt()            ;
    ui->OpStart->blockSignals(true )                      ;
    ui->OpStart->setValue    (stId )                      ;
    ui->OpStart->blockSignals(false)                      ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if (plan->site.contains("VolStart"))                    {
    int endId                                             ;
    endId = plan->site.value("VolStart").toInt()          ;
    ui->VolStart->blockSignals(true )                     ;
    ui->VolStart->setValue    (endId)                     ;
    ui->VolStart->blockSignals(false)                     ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if (plan->site.contains("VolEnd"))                      {
    int endId                                             ;
    endId = plan->site.value("VolEnd").toInt()            ;
    ui->VolEnd->blockSignals(true )                       ;
    ui->VolEnd->setValue    (endId)                       ;
    ui->VolEnd->blockSignals(false)                       ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if (plan->site.contains("OpRoot"))                      {
    QString xcity                                         ;
    xcity = plan->site.valueString("OpRoot")              ;
    ui->OpRoot->blockSignals(true )                       ;
    ui->OpRoot->setText(xcity)                            ;
    ui->OpRoot->setCursorPosition(0)                      ;
    ui->OpRoot->blockSignals(false)                       ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if (plan->site.contains("OpGallery"))                   {
    SUID suid                                             ;
    suid = plan->site.value("OpGallery").toULongLong()    ;
    *gallery <= suid                                      ;
    DoProcessEvents                                       ;
  }                                                       ;
  plan->site.endGroup     (                  )            ;
  /////////////////////////////////////////////////////////
  SqlConnection HC ( sql )                                ;
  CN = QtUUID::createUuidString()                        ;
  if (HC.open("OpPictures",CN))                           {
    Q = HC . sql . SelectFrom                             (
          "issue"                                         ,
          "oppages"                                       ,
          HC.OrderByDesc("issue")                         ,
          HC.sql.Limit(0,1)                             ) ;
    if (HC.Fetch(Q))                                      {
      int lastest = HC.Int(0)                             ;
      ui -> OpStart -> blockSignals ( true    )           ;
      ui -> OpStart -> setValue     ( lastest )           ;
      ui -> OpStart -> blockSignals ( false   )           ;
    }                                                     ;
    HC.close()                                            ;
  } else                                                  {
    HC.close()                                            ;
  }                                                       ;
  HC.remove()                                             ;
  /////////////////////////////////////////////////////////
  hunterSql = sql                                         ;
  Scope     = scope                                       ;
}

void N::OpPictures::GalleryChanged(int index)
{ Q_UNUSED                ( index               ) ;
  SUID uuid = N::GetUuid  ((QComboBox *)gallery ) ;
  nDropOut                ( uuid <= 0           ) ;
  plan->site.beginGroup   ( Scope               ) ;
  plan->site.setValue     ( "OpGallery" , uuid  ) ;
  plan->site.endGroup     (                     ) ;
}

void N::OpPictures::stateChanged(int)
{
  OpChanged ( ) ;
}

void N::OpPictures::OpChanged(void)
{
  QString path                                               ;
  bool    skip     = ui -> OpSkip   -> isChecked ( )         ;
  bool    cache    = ui -> OpCache  -> isChecked ( )         ;
  int     startId  = ui -> OpStart  -> value     ( )         ;
  bool    isVolume = ui -> isVolume -> isChecked ( )         ;
  int     VolStart = ui -> VolStart -> value     ( )         ;
  int     VolEnd   = ui -> VolEnd   -> value     ( )         ;
  ////////////////////////////////////////////////////////////
  plan->site.beginGroup       ( Scope                      ) ;
  ////////////////////////////////////////////////////////////
  plan->site.setValue         ( "OpSkip"   , skip          ) ;
  plan->site.setValue         ( "OpCache"  , cache         ) ;
  plan->site.setValue         ( "OpStart"  , startId       ) ;
  plan->site.setValue         ( "isVolume" , isVolume      ) ;
  plan->site.setValue         ( "VolStart" , VolStart      ) ;
  plan->site.setValue         ( "VolEnd"   , VolEnd        ) ;
  ////////////////////////////////////////////////////////////
  path = ui -> OpRoot -> text (                            ) ;
  plan->site.setValue         ( "OpRoot"   , path.toUtf8() ) ;
  ////////////////////////////////////////////////////////////
  plan->site.endGroup         (                            ) ;
}
