#include <exciton.h>
#include "ui_XcityPeople.h"

N::XcityPeople:: XcityPeople ( QWidget * parent , Plan * p )
               : Widget      (           parent ,        p )
               , ui          ( new Ui::XcityPeople         )
               , newbie      ( NULL                        )
               , merger      ( NULL                        )
               , gallery     ( NULL                        )
{
  ui -> setupUi ( this ) ;
}

N::XcityPeople::~XcityPeople (void)
{
  delete ui ;
}

void N::XcityPeople::prepare(void)
{
  newbie  = new ComboBox ( this , plan           )   ;
  merger  = new ComboBox ( this , plan           )   ;
  gallery = new ComboBox ( this , plan           )   ;
  ////////////////////////////////////////////////////
  newbie -> setGeometry  (  20 , 300 , 440 ,  28 )   ;
  merger -> setGeometry  (  20 , 340 , 440 ,  28 )   ;
  gallery-> setGeometry  (  20 , 380 , 440 ,  28 )   ;
  ////////////////////////////////////////////////////
  newbie -> setEditable  ( true                  )   ;
  merger -> setEditable  ( true                  )   ;
  gallery-> setEditable  ( true                  )   ;
  ////////////////////////////////////////////////////
  nConnect ( newbie  , SIGNAL(activated     (int))   ,
             this    , SLOT  (NewbieChanged (int)) ) ;
  nConnect ( merger  , SIGNAL(activated     (int))   ,
             this    , SLOT  (MergerChanged (int)) ) ;
  nConnect ( gallery , SIGNAL(activated     (int))   ,
             this    , SLOT  (GalleryChanged(int)) ) ;
  ////////////////////////////////////////////////////
  plan -> setFont ( this )                           ;
}

void N::XcityPeople::configure(QString scope,Sql & sql)
{
  QString Q                                          ;
  QString CN = QtUUID::createUuidString()           ;
  SqlConnection SC ( plan->sql )                     ;
  GroupItems    GI ( plan      )                     ;
  if (SC.open("configure",CN))                       {
    UUIDs   U                                        ;
    SUID    u                                        ;
    QString n                                        ;
    //////////////////////////////////////////////////
    U = GI . Groups                                  (
          SC                                         ,
          Types::People                              ,
          SC.OrderByDesc("position")               ) ;
    //////////////////////////////////////////////////
    newbie -> blockSignals ( true  )                 ;
    merger -> blockSignals ( true  )                 ;
    foreach ( u , U )                                {
      n = SC.getName                                 (
            PlanTable(Names)                         ,
            "uuid"                                   ,
            vLanguageId                              ,
            u                                      ) ;
      newbie -> addItem ( n , u )                    ;
      merger -> addItem ( n , u )                    ;
    }                                                ;
    newbie -> blockSignals ( false )                 ;
    merger -> blockSignals ( false )                 ;
    //////////////////////////////////////////////////
    U = GI . Groups                                  (
          SC                                         ,
          Types::Gallery                             ,
          SC.OrderByAsc("position")                ) ;
    gallery -> blockSignals ( true   )               ;
    gallery -> addItems     ( SC , U )               ;
    gallery -> blockSignals ( false  )               ;
    //////////////////////////////////////////////////
    SC.close()                                       ;
  }                                                  ;
  SC.remove()                                        ;
  ////////////////////////////////////////////////////
  plan->site.beginGroup   ( scope                  ) ;
  if (plan->site.contains("XcityJpSkip"))            {
    bool skip                                        ;
    skip = plan->site.value("XcityJpSkip").toBool()  ;
    ui->XcityJpSkip->blockSignals(true )             ;
    ui->XcityJpSkip->setChecked  (skip )             ;
    ui->XcityJpSkip->blockSignals(false)             ;
  }                                                  ;
  if (plan->site.contains("XcityJpStart"))           {
    int stId                                         ;
    stId = plan->site.value("XcityJpStart").toInt()  ;
    ui->XcityJpStart->blockSignals(true )            ;
    ui->XcityJpStart->setValue    (stId )            ;
    ui->XcityJpStart->blockSignals(false)            ;
  }                                                  ;
  if (plan->site.contains("XcityJpEnd"))             {
    int endId                                        ;
    endId = plan->site.value("XcityJpEnd").toInt()   ;
    ui->XcityJpFinish->blockSignals(true )           ;
    ui->XcityJpFinish->setValue    (endId)           ;
    ui->XcityJpFinish->blockSignals(false)           ;
  }                                                  ;
  if (plan->site.contains("XcityJP"))                {
    QString xcity                                    ;
    xcity = plan->site.valueString("XcityJP")        ;
    ui->XcityJpSearch->blockSignals(true )           ;
    ui->XcityJpSearch->setText(xcity)                ;
    ui->XcityJpSearch->setCursorPosition(0)          ;
    ui->XcityJpSearch->blockSignals(false)           ;
  }                                                  ;
  if (plan->site.contains("XcityJpMissing"))         {
    QString xcity                                    ;
    xcity = plan->site.valueString("XcityJpMissing") ;
    ui->XcityJpMissing->blockSignals(true )          ;
    ui->XcityJpMissing->setText(xcity)               ;
    ui->XcityJpMissing->setCursorPosition(0)         ;
    ui->XcityJpMissing->blockSignals(false)          ;
  }                                                  ;
  if (plan->site.contains("XcityJpFound"))           {
    QString xcity                                    ;
    xcity = plan->site.valueString("XcityJpFound")   ;
    ui->XcityJpFound->blockSignals(true )            ;
    ui->XcityJpFound->setText(xcity)                 ;
    ui->XcityJpFound->setCursorPosition(0)           ;
    ui->XcityJpFound->blockSignals(false)            ;
  }                                                  ;
  if (plan->site.contains("XcityJpIdFound"))         {
    QString xcity                                    ;
    xcity = plan->site.valueString("XcityJpIdFound") ;
    ui->XcityJpIdFound->blockSignals(true )          ;
    ui->XcityJpIdFound->setText(xcity)               ;
    ui->XcityJpIdFound->setCursorPosition(0)         ;
    ui->XcityJpIdFound->blockSignals(false)          ;
  }                                                  ;
  if (plan->site.contains("XcityJpId"))              {
    QString xcity                                    ;
    xcity = plan->site.valueString("XcityJpId")      ;
    ui->XcityJpId->blockSignals(true )               ;
    ui->XcityJpId->setText(xcity)                    ;
    ui->XcityJpId->setCursorPosition(0)              ;
    ui->XcityJpId->blockSignals(false)               ;
  }                                                  ;
  if (plan->site.contains("Newbie"))                 {
    SUID suid                                        ;
    suid = plan->site.value("Newbie").toULongLong()  ;
    *newbie <= suid                                  ;
    DoProcessEvents                                  ;
  }                                                  ;
  if (plan->site.contains("Merger"))                 {
    SUID suid                                        ;
    suid = plan->site.value("Merger").toULongLong()  ;
    *merger <= suid                                  ;
    DoProcessEvents                                  ;
  }                                                  ;
  if (plan->site.contains("Gallery"))                {
    SUID suid                                        ;
    suid = plan->site.value("Gallery").toULongLong() ;
    *gallery <= suid                                 ;
    DoProcessEvents                                  ;
  }                                                  ;
  plan->site.endGroup     (                  )       ;
  ////////////////////////////////////////////////////
  SqlConnection HC ( sql )                           ;
  CN = QtUUID::createUuidString()                   ;
  if (HC.open("Xcity",CN))                           {
    int v                                            ;
    v = 0                                            ;
    Q = HC.sql.SelectFrom                            (
          "id"                                       ,
          "xcityjp"                                  ,
          "order by id desc limit 0,1"             ) ;
    if (HC.Fetch(Q)) v = HC.Int(0)                   ;
    v++                                              ;
    ui->XcityJpStart->setValue(v)                    ;
    v += 50                                          ;
    if ( v > ui->XcityJpFinish->value() )            {
      ui -> XcityJpFinish -> setValue ( v )          ;
    }                                                ;
    HC.close()                                       ;
  } else                                             {
    HC.close()                                       ;
  }                                                  ;
  HC.remove()                                        ;
  ////////////////////////////////////////////////////
  hunterSql = sql                                    ;
  Scope     = scope                                  ;
}

void N::XcityPeople::NewbieChanged(int index)
{ Q_UNUSED                ( index             ) ;
  SUID uuid = N::GetUuid  ((QComboBox *)newbie) ;
  nDropOut                ( uuid <= 0         ) ;
  plan->site.beginGroup   ( Scope             ) ;
  plan->site.setValue     ( "Newbie" , uuid   ) ;
  plan->site.endGroup     (                   ) ;
}

void N::XcityPeople::MergerChanged(int index)
{ Q_UNUSED                ( index             ) ;
  SUID uuid = N::GetUuid  ((QComboBox *)merger) ;
  nDropOut                ( uuid <= 0         ) ;
  plan->site.beginGroup   ( Scope             ) ;
  plan->site.setValue     ( "Merger" , uuid   ) ;
  plan->site.endGroup     (                   ) ;
}

void N::XcityPeople::GalleryChanged(int index)
{ Q_UNUSED                ( index              ) ;
  SUID uuid = N::GetUuid  ((QComboBox *)gallery) ;
  nDropOut                ( uuid <= 0          ) ;
  plan->site.beginGroup   ( Scope              ) ;
  plan->site.setValue     ( "Gallery" , uuid   ) ;
  plan->site.endGroup     (                    ) ;
}

void N::XcityPeople::XcityJpChanged(void)
{
  QString path                                                                 ;
  bool    skip    = ui -> XcityJpSkip   -> isChecked ( )                       ;
  int     startId = ui -> XcityJpStart  -> value     ( )                       ;
  int     endId   = ui -> XcityJpFinish -> value     ( )                       ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.beginGroup                ( Scope                               ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.setValue                  ( "XcityJpSkip"       , skip          ) ;
  plan->site.setValue                  ( "XcityJpStart"      , startId       ) ;
  plan->site.setValue                  ( "XcityJpEnd"        , endId         ) ;
  //////////////////////////////////////////////////////////////////////////////
  path = ui->XcityJpSearch     -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJP"           , path.toUtf8() ) ;
  path = ui->XcityJpMissing    -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpMissing"    , path.toUtf8() ) ;
  path = ui->XcityJpFound      -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpFound"      , path.toUtf8() ) ;
  path = ui->XcityJpIdFound    -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpIdFound"    , path.toUtf8() ) ;
  path = ui->XcityJpId         -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpId"         , path.toUtf8() ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.endGroup                  (                                     ) ;
}

void N::XcityPeople::XcityValueChanged(int)
{
  XcityJpChanged ( ) ;
}

bool N::XcityPeople::SkipExists(void)
{
  return ui -> XcityJpSkip   -> isChecked ( ) ;
}

int N::XcityPeople::PeopleStart(void)
{
  return ui -> XcityJpStart  -> value     ( ) ;
}

int N::XcityPeople::PeopleEnd(void)
{
  return ui -> XcityJpFinish -> value     ( ) ;
}

SUID N::XcityPeople::NewbieUuid(void)
{
  if (IsNull(newbie)) return 0 ;
  return newbie->toUuid()      ;
}

SUID N::XcityPeople::MergerUuid(void)
{
  if (IsNull(merger)) return 0 ;
  return merger->toUuid()      ;
}

SUID N::XcityPeople::GalleryUuid(void)
{
  if (IsNull(gallery)) return 0 ;
  return gallery->toUuid()      ;
}

QString N::XcityPeople::Search(void)
{
  return ui->XcityJpSearch     -> text ( ) ;
}

QString N::XcityPeople::Missing(void)
{
  return ui->XcityJpMissing    -> text ( ) ;
}

QString N::XcityPeople::Found(void)
{
  return ui->XcityJpFound      -> text ( ) ;
}

QString N::XcityPeople::IdFound(void)
{
  return ui->XcityJpIdFound    -> text ( ) ;
}

QString N::XcityPeople::IdPattern(void)
{
  return ui->XcityJpId         -> text ( ) ;
}
