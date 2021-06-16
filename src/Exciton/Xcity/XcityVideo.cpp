#include <exciton.h>
#include "ui_XcityVideo.h"

N::XcityVideo:: XcityVideo  ( QWidget * parent , Plan * p )
              : Widget      (           parent ,        p )
              , ui          ( new Ui::XcityVideo          )
              , album       ( NULL                        )
              , interest    ( NULL                        )
              , gallery     ( NULL                        )
              , ItemEditing ( NULL                        )
              , Entries     ( NULL                        )
{
  ui -> setupUi ( this ) ;
}

N::XcityVideo::~XcityVideo(void)
{
  delete ui ;
}

void N::XcityVideo::prepare(void)
{
  album     = new ComboBox ( this , plan           )     ;
  interest  = new ComboBox ( this , plan           )     ;
  gallery   = new ComboBox ( this , plan           )     ;
  ////////////////////////////////////////////////////////
  album    -> setGeometry  (  20 , 220 , 440 ,  28 )     ;
  interest -> setGeometry  (  20 , 260 , 440 ,  28 )     ;
  gallery  -> setGeometry  (  20 , 300 , 440 ,  28 )     ;
  ////////////////////////////////////////////////////////
  album    -> setEditable  ( true                  )     ;
  interest -> setEditable  ( true                  )     ;
  gallery  -> setEditable  ( true                  )     ;
  ////////////////////////////////////////////////////////
  nConnect ( album    , SIGNAL ( activated      (int))   ,
             this     , SLOT   ( AlbumChanged   (int)) ) ;
  nConnect ( interest , SIGNAL ( activated      (int))   ,
             this     , SLOT   ( InterestChanged(int)) ) ;
  nConnect ( gallery  , SIGNAL ( activated      (int))   ,
             this     , SLOT   ( GalleryChanged (int)) ) ;
  ////////////////////////////////////////////////////////
  QStringList headers                                    ;
  headers << tr("Item" )                                 ;
  headers << tr("Names")                                 ;
  ui -> XcityNames -> setHeaderLabels ( headers        ) ;
  ////////////////////////////////////////////////////////
  QTreeWidgetItem * it                                   ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Release")                    ) ;
  ui -> XcityNames -> addTopLevelItem ( it             ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Actress")                    ) ;
  ui -> XcityNames -> addTopLevelItem ( it             ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Product")                    ) ;
  ui -> XcityNames -> addTopLevelItem ( it             ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("SKU")                        ) ;
  ui -> XcityNames -> addTopLevelItem ( it             ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Double penetration")         ) ;
  ui -> XcityNames -> addTopLevelItem ( it             ) ;
  ////////////////////////////////////////////////////////
  plan -> setFont ( this )                               ;
}

void N::XcityVideo::configure(QString scope,Sql & sql)
{
  QString       Q                                         ;
  QString       CN = QtUUID::createUuidString()             ;
  CMAPs         NM                                        ;
  int           ns = ui->XcityNames->topLevelItemCount()  ;
  /////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "XcityNames" )              ;
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
  SqlConnection SC ( plan -> sql )                        ;
  GroupItems    GI ( plan        )                        ;
  if (SC.open("Initialize",CN))                           {
    UUIDs   Uuids                                         ;
    ///////////////////////////////////////////////////////
    Uuids = SC . Uuids                                    (
             PlanTable(VideoGroups)                       ,
             "uuid"                                       ,
             SC . OrderByDesc ( "id" )                  ) ;
    ///////////////////////////////////////////////////////
    album    -> blockSignals ( true       )               ;
    album    -> addItems     ( SC , Uuids )               ;
    album    -> blockSignals ( false      )               ;
    interest -> blockSignals ( true       )               ;
    interest -> addItems     ( SC , Uuids )               ;
    interest -> blockSignals ( false      )               ;
    ///////////////////////////////////////////////////////
    Uuids = GI . Groups                                   (
              SC                                          ,
              Types::Gallery                              ,
              SC.OrderByAsc("position")   )               ;
    gallery  -> blockSignals ( true       )               ;
    gallery  -> addItems     ( SC , Uuids )               ;
    gallery  -> blockSignals ( false      )               ;
    ///////////////////////////////////////////////////////
    for (int i=0;i<ns;i++)                                {
      QTreeWidgetItem * itx                               ;
      SUID              znm = NM [ i ]                    ;
      QString           nms                               ;
      itx  = ui->XcityNames->topLevelItem(i)              ;
      nms  = SC.getName                                   (
               PlanTable(Names)                           ,
               "uuid"                                     ,
               vLanguageId                                ,
               znm                                      ) ;
      itx -> setData ( 1 , Qt::UserRole , znm )           ;
      itx -> setText ( 1 , nms                )           ;
    }                                                     ;
    ui->XcityNames->resizeColumnToContents(0)             ;
    ///////////////////////////////////////////////////////
    SC.close()                                            ;
  }                                                       ;
  SC.remove()                                             ;
  /////////////////////////////////////////////////////////
  plan->site.beginGroup   ( scope                       ) ;
  if (plan->site.contains("XcityJpDvdSkip"))              {
    bool skip                                             ;
    skip = plan->site.value("XcityJpDvdSkip").toBool()    ;
    ui  -> XcityJpSkip      -> blockSignals ( true  )     ;
    ui  -> XcityJpSkip      -> setChecked   ( skip  )     ;
    ui  -> XcityJpSkip      -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpDvdCache"))             {
    bool skip                                             ;
    skip = plan->site.value("XcityJpDvdCache").toBool()   ;
    ui  -> XcityJpCache     -> blockSignals ( true  )     ;
    ui  -> XcityJpCache     -> setChecked   ( skip  )     ;
    ui  -> XcityJpCache     -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpDvdStart"))             {
    int v                                                 ;
    v   = plan->site.value("XcityJpDvdStart").toInt()     ;
    ui -> XcityJpDvdStart   -> blockSignals ( true  )     ;
    ui -> XcityJpDvdStart   -> setValue     ( v     )     ;
    ui -> XcityJpDvdStart   -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpDvdEnd"))               {
    int v                                                 ;
    v   = plan->site.value("XcityJpDvdEnd").toInt()       ;
    ui -> XcityJpDvdFinish  -> blockSignals ( true  )     ;
    ui -> XcityJpDvdFinish  -> setValue     ( v     )     ;
    ui -> XcityJpDvdFinish  -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpDvdId"))                {
    QString xcity                                         ;
    xcity = plan->site.valueString("XcityJpDvdId")        ;
    ui -> XcityJpDvdId      -> blockSignals ( true  )     ;
    ui -> XcityJpDvdId      -> setText      ( xcity )     ;
    ui -> XcityJpDvdId      -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpDvdInfo"))              {
    QString xcity                                         ;
    xcity = plan->site.valueString("XcityJpDvdInfo")      ;
    ui -> XcityJpDvdInfo    -> blockSignals ( true  )     ;
    ui -> XcityJpDvdInfo    -> setText      ( xcity )     ;
    ui -> XcityJpDvdInfo    -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpDvdGallery"))           {
    QString xcity                                         ;
    xcity = plan->site.valueString("XcityJpDvdGallery")   ;
    ui -> XcityJpDvdGallery -> blockSignals ( true  )     ;
    ui -> XcityJpDvdGallery -> setText      ( xcity )     ;
    ui -> XcityJpDvdGallery -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("Album"))                       {
    SUID suid                                             ;
    suid = plan->site.value("Album").toULongLong()        ;
    *album <= suid                                        ;
    DoProcessEvents                                       ;
  }                                                       ;
  if (plan->site.contains("Interest"))                    {
    SUID suid                                             ;
    suid = plan->site.value("Interest").toULongLong()     ;
    *interest <= suid                                     ;
    DoProcessEvents                                       ;
  }                                                       ;
  if (plan->site.contains("VideoGallery"))                {
    SUID suid                                             ;
    suid = plan->site.value("VideoGallery").toULongLong() ;
    *gallery <= suid                                      ;
    DoProcessEvents                                       ;
  }                                                       ;
  plan -> site . endGroup ( )                             ;
  /////////////////////////////////////////////////////////
  SqlConnection HC ( sql )                                ;
  CN = QtUUID::createUuidString()                           ;
  if (HC.open("XcityVideo",CN))                           {
    int v                                                 ;
    v = 0                                                 ;
    Q = HC.sql.SelectFrom                                 (
          "id"                                            ,
          "xcityjpdvd"                                    ,
          HC . OrderByDesc ( "id"  )                      ,
          HC . sql . Limit ( 0 , 1 )                    ) ;
    if (HC.Fetch(Q)) v = HC.Int(0)                        ;
    v++                                                   ;
    ui->XcityJpDvdStart->setValue(v)                      ;
    v += 300                                              ;
    if (v>ui->XcityJpDvdFinish->value())                  {
      ui->XcityJpDvdFinish->setValue(v)                   ;
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

void N::XcityVideo::AlbumChanged(int index)
{ Q_UNUSED               ( index       ) ;
  SUID u = album->toUuid (             ) ;
  nDropOut               ( u <= 0      ) ;
  plan->site.beginGroup  ( Scope       ) ;
  plan->site.setValue    ( "Album" , u ) ;
  plan->site.endGroup    (             ) ;
}

void N::XcityVideo::InterestChanged(int index)
{ Q_UNUSED                  ( index          ) ;
  SUID u = interest->toUuid (                ) ;
  nDropOut                  ( u <= 0         ) ;
  plan->site.beginGroup     ( Scope          ) ;
  plan->site.setValue       ( "Interest" , u ) ;
  plan->site.endGroup       (                ) ;
}

void N::XcityVideo::GalleryChanged(int index)
{ Q_UNUSED                 ( index              ) ;
  SUID u = gallery->toUuid (                    ) ;
  nDropOut                 ( u <= 0             ) ;
  plan->site.beginGroup    ( Scope              ) ;
  plan->site.setValue      ( "VideoGallery" , u ) ;
  plan->site.endGroup      (                    ) ;
}

void N::XcityVideo::XcityJpChanged(void)
{
  QString path                                                                 ;
  bool    skip    = ui -> XcityJpSkip      -> isChecked ( )                    ;
  bool    cache   = ui -> XcityJpCache     -> isChecked ( )                    ;
  int     startId = ui -> XcityJpDvdStart  -> value     ( )                    ;
  int     endId   = ui -> XcityJpDvdFinish -> value     ( )                    ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.beginGroup                ( Scope                               ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.setValue                  ( "XcityJpDvdSkip"    , skip          ) ;
  plan->site.setValue                  ( "XcityJpDvdCache"   , cache         ) ;
  plan->site.setValue                  ( "XcityJpDvdStart"   , startId       ) ;
  plan->site.setValue                  ( "XcityJpDvdEnd"     , endId         ) ;
  //////////////////////////////////////////////////////////////////////////////
  path = ui->XcityJpDvdId      -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpDvdId"      , path.toUtf8() ) ;
  path = ui->XcityJpDvdInfo    -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpDvdInfo"    , path.toUtf8() ) ;
  path = ui->XcityJpDvdGallery -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpDvdGallery" , path.toUtf8() ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.endGroup                  (                                     ) ;
}

void N::XcityVideo::NameClicked(QTreeWidgetItem * item,int column)
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
  ui -> XcityNames -> setItemWidget ( item , column , Entries   ) ;
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

void N::XcityVideo::NameSelected(int)
{
  if (IsNull(ItemEditing)) return                              ;
  if (IsNull(Entries    )) return                              ;
  //////////////////////////////////////////////////////////////
  SUID    u = Entries -> toUuid      ( )                       ;
  QString n = Entries -> currentText ( )                       ;
  int     i = ui->XcityNames->indexOfTopLevelItem(ItemEditing) ;
  QString m = QString::number        (i)                       ;
  //////////////////////////////////////////////////////////////
  ui->XcityNames->removeItemWidget ( ItemEditing , 1 )         ;
  ItemEditing -> setData ( 1 , Qt::UserRole , u )              ;
  ItemEditing -> setText ( 1 , n                )              ;
  Entries      = NULL                                          ;
  ItemEditing  = NULL                                          ;
  //////////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "XcityNames" )                   ;
  plan -> site . setValue   ( m , u        )                   ;
  plan -> site . endGroup   (              )                   ;
}

void N::XcityVideo::XcityValueChanged(int)
{
  XcityJpChanged ( ) ;
}

bool N::XcityVideo::SkipExists(void)
{
  return ui -> XcityJpSkip -> isChecked ( ) ;
}

bool N::XcityVideo::VideoCache(void)
{
  return ui -> XcityJpCache -> isChecked ( ) ;
}

int N::XcityVideo::VideoStart(void)
{
  return ui -> XcityJpDvdStart -> value ( ) ;
}

int N::XcityVideo::VideoEnd(void)
{
  return ui -> XcityJpDvdFinish -> value ( ) ;
}

SUID N::XcityVideo::AlbumUuid(void)
{
  return album    -> toUuid ( ) ;
}

SUID N::XcityVideo::InterestUuid(void)
{
  return interest -> toUuid ( ) ;
}

SUID N::XcityVideo::GalleryUuid(void)
{
  return gallery  -> toUuid ( ) ;
}

SUID N::XcityVideo::NameUuid(int index)
{
  if (index>=ui->XcityNames->topLevelItemCount()) return 0   ;
  QTreeWidgetItem * it = ui->XcityNames->topLevelItem(index) ;
  if (IsNull(it)) return 0                                   ;
  return nTreeUuid ( it , 1 )                                ;
}

QString N::XcityVideo::Search(void)
{
  return ui -> XcityJpDvdId      -> text ( ) ;
}

QString N::XcityVideo::Info(void)
{
  return ui -> XcityJpDvdInfo    -> text ( ) ;
}

QString N::XcityVideo::Gallery(void)
{
  return ui -> XcityJpDvdGallery -> text ( ) ;
}
