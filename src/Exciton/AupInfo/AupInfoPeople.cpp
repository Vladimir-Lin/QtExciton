#include <exciton.h>
#include "ui_AupInfoPeople.h"

N::AupInfoPeople:: AupInfoPeople ( QWidget * parent , Plan * p )
                 : Widget        (           parent ,        p )
                 , ui            ( new Ui::AupInfoPeople       )
                 , newbie        ( NULL                        )
                 , merger        ( NULL                        )
                 , gallery       ( NULL                        )
                 , ItemEditing   ( NULL                        )
                 , Entries       ( NULL                        )
{
  ui -> setupUi ( this ) ;
}

N::AupInfoPeople::~AupInfoPeople(void)
{
  delete ui ;
}

bool N::AupInfoPeople::SkipExists(void)
{
  return ui->AupInfoSkip->isChecked() ;
}

int N::AupInfoPeople::PeopleStart(void)
{
  return ui->AupInfoStart->value() ;
}

int N::AupInfoPeople::PeopleEnd(void)
{
  return ui->AupInfoFinish->value() ;
}

SUID N::AupInfoPeople::NewbieUuid(void)
{
  if (IsNull(newbie)) return 0 ;
  return newbie->toUuid()      ;
}

SUID N::AupInfoPeople::MergerUuid(void)
{
  if (IsNull(merger)) return 0 ;
  return merger->toUuid()      ;
}

SUID N::AupInfoPeople::GalleryUuid(void)
{
  if (IsNull(gallery)) return 0 ;
  return gallery->toUuid()      ;
}

SUID N::AupInfoPeople::NameUuid(int index)
{
  if (index>=ui->AupNames->topLevelItemCount()) return 0   ;
  QTreeWidgetItem * it = ui->AupNames->topLevelItem(index) ;
  if (IsNull(it)) return 0                                 ;
  return nTreeUuid ( it , 1 )                              ;
}

QString N::AupInfoPeople::Search(void)
{
  return ui->AupInfoPattern->text() ;
}

QString N::AupInfoPeople::Actress(void)
{
  return ui->AupInfoActress->text() ;
}

bool N::AupInfoPeople::VerifyEnglish(void)
{
  return ui->AupInfoNames->isChecked() ;
}

void N::AupInfoPeople::prepare(void)
{
  newbie  = new ComboBox ( this , plan           )   ;
  merger  = new ComboBox ( this , plan           )   ;
  gallery = new ComboBox ( this , plan           )   ;
  ////////////////////////////////////////////////////
  newbie -> setGeometry  (  20 , 220 , 440 ,  28 )   ;
  merger -> setGeometry  (  20 , 260 , 440 ,  28 )   ;
  gallery-> setGeometry  (  20 , 300 , 440 ,  28 )   ;
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
  QStringList headers                                ;
  headers << tr("Item" )                             ;
  headers << tr("Names")                             ;
  ui -> AupNames -> setHeaderLabels ( headers      ) ;
  ////////////////////////////////////////////////////
  QTreeWidgetItem * it                               ;
  it  = new QTreeWidgetItem ( )                      ;
  it -> setText ( 0 , tr("Release")                ) ;
  ui -> AupNames -> addTopLevelItem ( it           ) ;
  it  = new QTreeWidgetItem ( )                      ;
  it -> setText ( 0 , tr("Actress")                ) ;
  ui -> AupNames -> addTopLevelItem ( it           ) ;
  it  = new QTreeWidgetItem ( )                      ;
  it -> setText ( 0 , tr("Product")                ) ;
  ui -> AupNames -> addTopLevelItem ( it           ) ;
  it  = new QTreeWidgetItem ( )                      ;
  it -> setText ( 0 , tr("SKU")                    ) ;
  ui -> AupNames -> addTopLevelItem ( it           ) ;
  it  = new QTreeWidgetItem ( )                      ;
  it -> setText ( 0 , tr("Double penetration")     ) ;
  ui -> AupNames -> addTopLevelItem ( it           ) ;
  ////////////////////////////////////////////////////
  plan -> setFont ( this )                           ;
}

void N::AupInfoPeople::configure(QString scope,Sql & sql)
{
  QString Q                                               ;
  QString CN = QtUUID::createUuidString()                   ;
  CMAPs         NM                                        ;
  int           ns = ui->AupNames->topLevelItemCount()    ;
  /////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "AupNames" )                ;
  for (int i=0;i<ns;i++)                                  {
    QString m = QString::number(i)                        ;
    SUID    z = 0                                         ;
    if (plan->site.contains(m))                           {
      z = plan->site.value(m).toULongLong()               ;
    }                                                     ;
    NM [ i ] = z                                          ;
  }                                                       ;
  plan -> site . endGroup   (              )              ;
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
          Types::People                                   ,
          SC.OrderByDesc("position")                    ) ;
    ///////////////////////////////////////////////////////
    newbie -> blockSignals ( true  )                      ;
    merger -> blockSignals ( true  )                      ;
    foreach ( u , U )                                     {
      n = SC.getName                                      (
            PlanTable(Names)                              ,
            "uuid"                                        ,
            vLanguageId                                   ,
            u                                           ) ;
      newbie -> addItem ( n , u )                         ;
      merger -> addItem ( n , u )                         ;
    }                                                     ;
    newbie -> blockSignals ( false )                      ;
    merger -> blockSignals ( false )                      ;
    ///////////////////////////////////////////////////////
    U = GI . Groups                                       (
          SC                                              ,
          Types::Gallery                                  ,
          SC.OrderByAsc("position")                     ) ;
    gallery -> blockSignals ( true   )                    ;
    gallery -> addItems     ( SC , U )                    ;
    gallery -> blockSignals ( false  )                    ;
    ///////////////////////////////////////////////////////
    for (int i=0;i<ns;i++)                                {
      QTreeWidgetItem * itx                               ;
      SUID              znm = NM [ i ]                    ;
      QString           nms                               ;
      itx  = ui->AupNames->topLevelItem(i)                ;
      nms  = SC.getName                                   (
               PlanTable(Names)                           ,
               "uuid"                                     ,
               vLanguageId                                ,
               znm                                      ) ;
      itx -> setData ( 1 , Qt::UserRole , znm )           ;
      itx -> setText ( 1 , nms                )           ;
    }                                                     ;
    ui->AupNames->resizeColumnToContents(0)               ;
    ///////////////////////////////////////////////////////
    SC.close()                                            ;
  }                                                       ;
  SC.remove()                                             ;
  /////////////////////////////////////////////////////////
  plan->site.beginGroup   ( scope                       ) ;
  if (plan->site.contains("AupInfoSkip"))                 {
    bool skip                                             ;
    skip = plan->site.value("AupInfoSkip").toBool()       ;
    ui->AupInfoSkip->blockSignals(true )                  ;
    ui->AupInfoSkip->setChecked  (skip )                  ;
    ui->AupInfoSkip->blockSignals(false)                  ;
  }                                                       ;
  if (plan->site.contains("AupInfoNames"))                {
    bool skip                                             ;
    skip = plan->site.value("AupInfoNames").toBool()      ;
    ui->AupInfoNames->blockSignals(true )                 ;
    ui->AupInfoNames->setChecked  (skip )                 ;
    ui->AupInfoNames->blockSignals(false)                 ;
  }                                                       ;
  if (plan->site.contains("AupInfoStart"))                {
    int stId                                              ;
    stId = plan->site.value("AupInfoStart").toInt()       ;
    ui->AupInfoStart->blockSignals(true )                 ;
    ui->AupInfoStart->setValue    (stId )                 ;
    ui->AupInfoStart->blockSignals(false)                 ;
  }                                                       ;
  if (plan->site.contains("AupInfoFinish"))               {
    int endId                                             ;
    endId = plan->site.value("AupInfoFinish").toInt()     ;
    ui->AupInfoFinish->blockSignals(true )                ;
    ui->AupInfoFinish->setValue    (endId)                ;
    ui->AupInfoFinish->blockSignals(false)                ;
  }                                                       ;
  if (plan->site.contains("AupInfoPattern"))              {
    QString xcity                                         ;
    xcity = plan->site.valueString("AupInfoPattern")      ;
    ui->AupInfoPattern->blockSignals(true )               ;
    ui->AupInfoPattern->setText(xcity)                    ;
    ui->AupInfoPattern->setCursorPosition(0)              ;
    ui->AupInfoPattern->blockSignals(false)               ;
  }                                                       ;
  if (plan->site.contains("AupInfoActress"))              {
    QString xcity                                         ;
    xcity = plan->site.valueString("AupInfoActress")      ;
    ui->AupInfoActress->blockSignals(true )               ;
    ui->AupInfoActress->setText(xcity)                    ;
    ui->AupInfoActress->setCursorPosition(0)              ;
    ui->AupInfoActress->blockSignals(false)               ;
  }                                                       ;
  if (plan->site.contains("AupNewbie"))                   {
    SUID suid                                             ;
    suid = plan->site.value("AupNewbie").toULongLong()    ;
    *newbie <= suid                                       ;
    DoProcessEvents                                       ;
  }                                                       ;
  if (plan->site.contains("AupMerger"))                   {
    SUID suid                                             ;
    suid = plan->site.value("AupMerger").toULongLong()    ;
    *merger <= suid                                       ;
    DoProcessEvents                                       ;
  }                                                       ;
  if (plan->site.contains("AupGallery"))                  {
    SUID suid                                             ;
    suid = plan->site.value("AupGallery").toULongLong()   ;
    *gallery <= suid                                      ;
    DoProcessEvents                                       ;
  }                                                       ;
  plan->site.endGroup     (                  )            ;
  /////////////////////////////////////////////////////////
  SqlConnection HC ( sql )                                ;
  CN = QtUUID::createUuidString()                        ;
  if (HC.open("AupInfoPeople",CN))                        {
    int v                                                 ;
    v = 0                                                 ;
    Q = HC.sql.SelectFrom                                 (
          "id"                                            ,
          "aupinfo"                                       ,
          HC.OrderByDesc("id")                            ,
          HC.sql.Limit(0,1)                             ) ;
    if (HC.Fetch(Q)) v = HC.Int(0)                        ;
    v++                                                   ;
    ui->AupInfoStart->setValue(v)                         ;
    v += 50                                               ;
    if (v>ui->AupInfoFinish->value())                     {
      ui->AupInfoFinish->setValue(v)                      ;
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

void N::AupInfoPeople::NewbieChanged(int index)
{ Q_UNUSED                ( index              ) ;
  SUID uuid = N::GetUuid  ((QComboBox *)newbie ) ;
  nDropOut                ( uuid <= 0          ) ;
  plan->site.beginGroup   ( Scope              ) ;
  plan->site.setValue     ( "AupNewbie" , uuid ) ;
  plan->site.endGroup     (                    ) ;
}

void N::AupInfoPeople::MergerChanged(int index)
{ Q_UNUSED                ( index              ) ;
  SUID uuid = N::GetUuid  ((QComboBox *)merger ) ;
  nDropOut                ( uuid <= 0          ) ;
  plan->site.beginGroup   ( Scope              ) ;
  plan->site.setValue     ( "AupMerger" , uuid ) ;
  plan->site.endGroup     (                    ) ;
}

void N::AupInfoPeople::GalleryChanged(int index)
{ Q_UNUSED                ( index               ) ;
  SUID uuid = N::GetUuid  ((QComboBox *)gallery ) ;
  nDropOut                ( uuid <= 0           ) ;
  plan->site.beginGroup   ( Scope               ) ;
  plan->site.setValue     ( "AupGallery" , uuid ) ;
  plan->site.endGroup     (                     ) ;
}

void N::AupInfoPeople::AupValueChanged(int index)
{
  AupChanged ( ) ;
}

void N::AupInfoPeople::AupChanged(void)
{
  QString path                                                                 ;
  bool    skip    = ui -> AupInfoSkip   -> isChecked ( )                       ;
  bool    verify  = ui -> AupInfoNames  -> isChecked ( )                       ;
  int     startId = ui -> AupInfoStart  -> value     ( )                       ;
  int     endId   = ui -> AupInfoFinish -> value     ( )                       ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.beginGroup                ( Scope                               ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.setValue                  ( "AupInfoSkip"       , skip          ) ;
  plan->site.setValue                  ( "AupInfoNames"      , verify        ) ;
  plan->site.setValue                  ( "AupInfoStart"      , startId       ) ;
  plan->site.setValue                  ( "AupInfoFinish"     , endId         ) ;
  //////////////////////////////////////////////////////////////////////////////
  path = ui->AupInfoPattern    -> text (                                     ) ;
  plan->site.setValue                  ( "AupInfoPattern"    , path.toUtf8() ) ;
  path = ui->AupInfoActress    -> text (                                     ) ;
  plan->site.setValue                  ( "AupInfoActress"    , path.toUtf8() ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.endGroup                  (                                     ) ;
}

void N::AupInfoPeople::NameClicked(QTreeWidgetItem * item,int column)
{
  if ( NotNull ( Entries ) )                                      {
    Entries -> deleteLater()                                      ;
    Entries  = NULL                                               ;
  }                                                               ;
  if ( column <= 0 ) return                                       ;
  /////////////////////////////////////////////////////////////////
  SUID u = nTreeUuid ( item , column )                            ;
  /////////////////////////////////////////////////////////////////
  Entries  = new ComboBox ( NULL , plan )                         ;
  ui -> AupNames -> setItemWidget ( item , column , Entries   )   ;
  Entries -> addItems ( PlanTable(Entries) , Qt::AscendingOrder ) ;
  /////////////////////////////////////////////////////////////////
  if (u>0) (*(QComboBox *)Entries) <= u                           ;
  /////////////////////////////////////////////////////////////////
  nConnect ( Entries , SIGNAL ( activated   (int) )               ,
             this    , SLOT   ( NameSelected(int) )             ) ;
  /////////////////////////////////////////////////////////////////
  ItemEditing = item                                              ;
  Entries -> showPopup ( )                                        ;
}

void N::AupInfoPeople::NameSelected(int)
{
  if (IsNull(ItemEditing)) return                            ;
  if (IsNull(Entries    )) return                            ;
  ////////////////////////////////////////////////////////////
  SUID    u = Entries -> toUuid      ( )                     ;
  QString n = Entries -> currentText ( )                     ;
  int     i = ui->AupNames->indexOfTopLevelItem(ItemEditing) ;
  QString m = QString::number        (i)                     ;
  ////////////////////////////////////////////////////////////
  ui->AupNames->removeItemWidget ( ItemEditing , 1 )         ;
  ItemEditing -> setData ( 1 , Qt::UserRole , u )            ;
  ItemEditing -> setText ( 1 , n                )            ;
  Entries      = NULL                                        ;
  ItemEditing  = NULL                                        ;
  ////////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "AupNames" )                   ;
  plan -> site . setValue   ( m , u      )                   ;
  plan -> site . endGroup   (            )                   ;
}
