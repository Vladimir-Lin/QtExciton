#include <exciton.h>
#include "ui_JavFreeVideo.h"

N::JavFreeVideo:: JavFreeVideo ( QWidget * parent , Plan * p )
                : Widget       (           parent ,        p )
                , ui           ( new Ui::JavFreeVideo        )
                , album        ( NULL                        )
                , interest     ( NULL                        )
                , gallery      ( NULL                        )
                , ItemEditing  ( NULL                        )
                , Entries      ( NULL                        )
{
  ui -> setupUi ( this ) ;
}

N::JavFreeVideo::~JavFreeVideo(void)
{
  delete ui ;
}

bool N::JavFreeVideo::Skip(void)
{
  return ui -> Skip -> isChecked ( ) ;
}

bool N::JavFreeVideo::Cache(void)
{
  return ui -> Cache -> isChecked ( ) ;
}

bool N::JavFreeVideo::DownloadOnly(void)
{
  return ui -> DownloadOnly -> isChecked ( ) ;
}

bool N::JavFreeVideo::isProxy(void)
{
  return ui -> Proxy -> isChecked ( ) ;
}

int N::JavFreeVideo::Start(void)
{
  return ui -> Start -> value ( ) ;
}

int N::JavFreeVideo::Finish(void)
{
  return ui -> Finish -> value ( ) ;
}

QString N::JavFreeVideo::GZipLocation(void)
{
  return ui -> GZip -> text ( ) ;
}

QString N::JavFreeVideo::Posting(void)
{
  return ui -> Posting -> text ( ) ;
}

QString N::JavFreeVideo::Thumbnails(void)
{
  return ui -> Thumbnails -> text ( ) ;
}

SUID N::JavFreeVideo::AlbumUuid(void)
{
  return album -> toUuid ( ) ;
}

SUID N::JavFreeVideo::InterestUuid(void)
{
  return interest -> toUuid ( ) ;
}

SUID N::JavFreeVideo::GalleryUuid(void)
{
  return gallery -> toUuid ( ) ;
}

SUID N::JavFreeVideo::NameUuid(int index)
{
  if (index>=ui->JfNames->topLevelItemCount()) return 0   ;
  QTreeWidgetItem * it = ui->JfNames->topLevelItem(index) ;
  if (IsNull(it)) return 0                                ;
  return nTreeUuid ( it , 1 )                             ;
}

void N::JavFreeVideo::AlbumChanged(int index)
{ Q_UNUSED               ( index         ) ;
  SUID u = album->toUuid (               ) ;
  nDropOut               ( u <= 0        ) ;
  plan->site.beginGroup  ( Scope         ) ;
  plan->site.setValue    ( "JfAlbum" , u ) ;
  plan->site.endGroup    (               ) ;
}

void N::JavFreeVideo::InterestChanged(int index)
{ Q_UNUSED                  ( index            ) ;
  SUID u = interest->toUuid (                  ) ;
  nDropOut                  ( u <= 0           ) ;
  plan->site.beginGroup     ( Scope            ) ;
  plan->site.setValue       ( "JfInterest" , u ) ;
  plan->site.endGroup       (                  ) ;
}

void N::JavFreeVideo::GalleryChanged(int index)
{ Q_UNUSED                 ( index           ) ;
  SUID u = gallery->toUuid (                 ) ;
  nDropOut                 ( u <= 0          ) ;
  plan->site.beginGroup    ( Scope           ) ;
  plan->site.setValue      ( "JfGallery" , u ) ;
  plan->site.endGroup      (                 ) ;
}

void N::JavFreeVideo::prepare(void)
{
  album     = new ComboBox ( this , plan           )     ;
  interest  = new ComboBox ( this , plan           )     ;
  gallery   = new ComboBox ( this , plan           )     ;
  ////////////////////////////////////////////////////////
  album    -> setGeometry  (  20 , 340 , 440 ,  28 )     ;
  interest -> setGeometry  (  20 , 380 , 440 ,  28 )     ;
  gallery  -> setGeometry  (  20 , 420 , 440 ,  28 )     ;
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
  ui -> JfNames -> setHeaderLabels ( headers           ) ;
  ////////////////////////////////////////////////////////
  QTreeWidgetItem * it                                   ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Release")                    ) ;
  ui -> JfNames -> addTopLevelItem ( it                ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Actress")                    ) ;
  ui -> JfNames -> addTopLevelItem ( it                ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Product")                    ) ;
  ui -> JfNames -> addTopLevelItem ( it                ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("SKU")                        ) ;
  ui -> JfNames -> addTopLevelItem ( it                ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Double penetration")         ) ;
  ui -> JfNames -> addTopLevelItem ( it                ) ;
  ////////////////////////////////////////////////////////
  plan -> setFont ( this )                               ;
}

void N::JavFreeVideo::configure(QString scope,Sql & sql)
{
  QString       Q                                           ;
  QString       CN = QtUUID::createUuidString()               ;
  CMAPs         NM                                          ;
  int           ns = ui->JfNames->topLevelItemCount()       ;
  ///////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "JfNames" )                   ;
  for (int i=0;i<ns;i++)                                    {
    QString m = QString::number(i)                          ;
    SUID    z = 0                                           ;
    if (plan->site.contains(m))                             {
      z = plan->site.value(m).toULongLong()                 ;
    }                                                       ;
    NM [ i ] = z                                            ;
  }                                                         ;
  plan -> site . endGroup   (              )                ;
  ///////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                          ;
  GroupItems    GI ( plan        )                          ;
  if (SC.open("Initialize",CN))                             {
    UUIDs   Uuids                                           ;
    /////////////////////////////////////////////////////////
    Uuids = SC . Uuids                                      (
             PlanTable(VideoGroups)                         ,
             "uuid"                                         ,
             SC . OrderByDesc ( "id" )                    ) ;
    /////////////////////////////////////////////////////////
    album    -> blockSignals ( true       )                 ;
    album    -> addItems     ( SC , Uuids )                 ;
    album    -> blockSignals ( false      )                 ;
    interest -> blockSignals ( true       )                 ;
    interest -> addItems     ( SC , Uuids )                 ;
    interest -> blockSignals ( false      )                 ;
    /////////////////////////////////////////////////////////
    Uuids = GI . Groups                                     (
              SC                                            ,
              Types::Gallery                                ,
              SC.OrderByAsc("position")   )                 ;
    gallery  -> blockSignals ( true       )                 ;
    gallery  -> addItems     ( SC , Uuids )                 ;
    gallery  -> blockSignals ( false      )                 ;
    /////////////////////////////////////////////////////////
    for (int i=0;i<ns;i++)                                  {
      QTreeWidgetItem * itx                                 ;
      SUID              znm = NM [ i ]                      ;
      QString           nms                                 ;
      itx  = ui->JfNames->topLevelItem(i)                   ;
      nms  = SC.getName                                     (
               PlanTable(Names)                             ,
               "uuid"                                       ,
               vLanguageId                                  ,
               znm                                        ) ;
      itx -> setData ( 1 , Qt::UserRole , znm )             ;
      itx -> setText ( 1 , nms                )             ;
    }                                                       ;
    ui->JfNames->resizeColumnToContents(0)                  ;
    /////////////////////////////////////////////////////////
    SC.close()                                              ;
  }                                                         ;
  SC.remove()                                               ;
  ///////////////////////////////////////////////////////////
  plan->site.beginGroup   ( scope                         ) ;
  if (plan->site.contains("JavFreeSkip"))                   {
    bool skip                                               ;
    skip = plan->site.value("JavFreeSkip").toBool()         ;
    ui  -> Skip             -> blockSignals ( true  )       ;
    ui  -> Skip             -> setChecked   ( skip  )       ;
    ui  -> Skip             -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JavFreeCache"))                  {
    bool skip                                               ;
    skip = plan->site.value("JavFreeCache").toBool()        ;
    ui  -> Cache            -> blockSignals ( true  )       ;
    ui  -> Cache            -> setChecked   ( skip  )       ;
    ui  -> Cache            -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JavFreeDownload"))               {
    bool skip                                               ;
    skip = plan->site.value("JavFreeDownload").toBool()     ;
    ui  -> DownloadOnly     -> blockSignals ( true  )       ;
    ui  -> DownloadOnly     -> setChecked   ( skip  )       ;
    ui  -> DownloadOnly     -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JavFreeStart"))                  {
    int v                                                   ;
    v   = plan->site.value("JavFreeStart").toInt()          ;
    ui -> Start             -> blockSignals ( true  )       ;
    ui -> Start             -> setValue     ( v     )       ;
    ui -> Start             -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JavFreeFinish"))                 {
    int v                                                   ;
    v   = plan->site.value("JavFreeFinish").toInt()         ;
    ui -> Finish            -> blockSignals ( true  )       ;
    ui -> Finish            -> setValue     ( v     )       ;
    ui -> Finish            -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JavFreePosting"))                {
    QString xcity                                           ;
    xcity = plan->site.valueString("JavFreePosting")        ;
    ui -> Posting           -> blockSignals ( true  )       ;
    ui -> Posting           -> setText      ( xcity )       ;
    ui -> Posting           -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JavFreeThumbnails"))             {
    QString xcity                                           ;
    xcity = plan->site.valueString("JavFreeThumbnails")     ;
    ui -> Thumbnails        -> blockSignals ( true  )       ;
    ui -> Thumbnails        -> setText      ( xcity )       ;
    ui -> Thumbnails        -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JavFreeGZip"))                   {
    QString xcity                                           ;
    xcity = plan->site.valueString("JavFreeGZip")           ;
    ui -> GZip              -> blockSignals ( true  )       ;
    ui -> GZip              -> setText      ( xcity )       ;
    ui -> GZip              -> blockSignals ( false )       ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if (plan->site.contains("JfAlbum"))                       {
    SUID suid                                               ;
    suid = plan->site.value("JfAlbum").toULongLong()        ;
    *album <= suid                                          ;
    DoProcessEvents                                         ;
  }                                                         ;
  if (plan->site.contains("JfInterest"))                    {
    SUID suid                                               ;
    suid = plan->site.value("JfInterest").toULongLong()     ;
    *interest <= suid                                       ;
    DoProcessEvents                                         ;
  }                                                         ;
  if (plan->site.contains("JfGallery"))                     {
    SUID suid                                               ;
    suid = plan->site.value("JfGallery").toULongLong()      ;
    *gallery <= suid                                        ;
    DoProcessEvents                                         ;
  }                                                         ;
  plan -> site . endGroup ( )                               ;
  ///////////////////////////////////////////////////////////
  SqlConnection HC ( sql )                                  ;
  CN = QtUUID::createUuidString()                             ;
  if (HC.open("JavFreeVideo",CN))                           {
    HC.close()                                              ;
  } else                                                    {
    HC.close()                                              ;
  }                                                         ;
  HC.remove()                                               ;
  ///////////////////////////////////////////////////////////
  hunterSql = sql                                           ;
  Scope     = scope                                         ;
}

void N::JavFreeVideo::JavFreeValues(int index)
{
  JavFreeChanged ( ) ;
}

void N::JavFreeVideo::JavFreeChanged(void)
{
  QString path                                                          ;
  bool    skip     = ui -> Skip         -> isChecked ( )                ;
  bool    cache    = ui -> Cache        -> isChecked ( )                ;
  bool    download = ui -> DownloadOnly -> isChecked ( )                ;
  int     startId  = ui -> Start        -> value     ( )                ;
  int     endId    = ui -> Finish       -> value     ( )                ;
  ///////////////////////////////////////////////////////////////////////
  plan->site.beginGroup         ( Scope                               ) ;
  ///////////////////////////////////////////////////////////////////////
  plan->site.setValue           ( "JavFreeSkip"       , skip          ) ;
  plan->site.setValue           ( "JavFreeCache"      , cache         ) ;
  plan->site.setValue           ( "JavFreeDownload"   , download      ) ;
  plan->site.setValue           ( "JavFreeStart"      , startId       ) ;
  plan->site.setValue           ( "JavFreeFinish"     , endId         ) ;
  ///////////////////////////////////////////////////////////////////////
  path = ui->Posting    -> text (                                     ) ;
  plan->site.setValue           ( "JavFreePosting"    , path.toUtf8() ) ;
  path = ui->Thumbnails -> text (                                     ) ;
  plan->site.setValue           ( "JavFreeThumbnails" , path.toUtf8() ) ;
  path = ui->GZip       -> text (                                     ) ;
  plan->site.setValue           ( "JavFreeGZip"       , path.toUtf8() ) ;
  ///////////////////////////////////////////////////////////////////////
  plan->site.endGroup           (                                     ) ;
}

void N::JavFreeVideo::JavFreeBrowse(void)
{
  QString suffix                          ;
  QString filename                        ;
  suffix   = "*.exe"                      ;
  filename = QFileDialog::getOpenFileName (
               this                       ,
               tr("Gzip file location")   ,
               GZipLocation ( )           ,
               suffix                   ) ;
  if (filename.length()<=0) return        ;
  ui -> GZip -> blockSignals ( true     ) ;
  ui -> GZip -> setText      ( filename ) ;
  ui -> GZip -> blockSignals ( false    ) ;
  JavFreeChanged             (          ) ;
}

void N::JavFreeVideo::NameClicked(QTreeWidgetItem * item,int column)
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
  ui -> JfNames -> setItemWidget ( item , column , Entries      ) ;
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

void N::JavFreeVideo::NameSelected(int)
{
  if (IsNull(ItemEditing)) return                           ;
  if (IsNull(Entries    )) return                           ;
  ///////////////////////////////////////////////////////////
  SUID    u = Entries -> toUuid      ( )                    ;
  QString n = Entries -> currentText ( )                    ;
  int     i = ui->JfNames->indexOfTopLevelItem(ItemEditing) ;
  QString m = QString::number        (i)                    ;
  ///////////////////////////////////////////////////////////
  ui->JfNames->removeItemWidget ( ItemEditing , 1 )         ;
  ItemEditing -> setData ( 1 , Qt::UserRole , u )           ;
  ItemEditing -> setText ( 1 , n                )           ;
  Entries      = NULL                                       ;
  ItemEditing  = NULL                                       ;
  ///////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "JfNames" )                   ;
  plan -> site . setValue   ( m , u     )                   ;
  plan -> site . endGroup   (           )                   ;
}
