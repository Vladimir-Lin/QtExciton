#include <exciton.h>
#include "ui_JavTorrentVideo.h"

N::JavTorrentVideo:: JavTorrentVideo ( QWidget * parent , Plan * p )
                   : Widget          (           parent ,        p )
                   , ui              ( new Ui::JavTorrentVideo     )
                   , album           ( NULL                        )
                   , interest        ( NULL                        )
                   , gallery         ( NULL                        )
                   , ItemEditing     ( NULL                        )
                   , Entries         ( NULL                        )
{
  ui -> setupUi ( this ) ;
}

N::JavTorrentVideo::~JavTorrentVideo(void)
{
  delete ui ;
}

bool N::JavTorrentVideo::Skip(void)
{
  return ui -> Skip -> isChecked ( ) ;
}

bool N::JavTorrentVideo::Cache(void)
{
  return ui -> Cache -> isChecked ( ) ;
}

bool N::JavTorrentVideo::DownloadOnly(void)
{
  return ui -> DownloadOnly -> isChecked ( ) ;
}

bool N::JavTorrentVideo::DontParse(void)
{
  return ui -> DontParse -> isChecked ( ) ;
}

bool N::JavTorrentVideo::DownloadImage(void)
{
  return ui -> Image -> isChecked ( ) ;
}

bool N::JavTorrentVideo::DownloadTorrent(void)
{
  return ui -> Torrent -> isChecked ( ) ;
}

int N::JavTorrentVideo::Lastest(void)
{
  return ui -> Lastest -> value ( ) ;
}

int N::JavTorrentVideo::Retry(void)
{
  return ui -> Retry -> value ( ) ;
}

QString N::JavTorrentVideo::Pattern(void)
{
  return ui -> Pattern -> text ( ) ;
}

QString N::JavTorrentVideo::TorrentPattern(void)
{
  return ui -> JpTorrent -> text ( ) ;
}

QString N::JavTorrentVideo::TorrentPath(void)
{
  return ui -> TorrentPath -> text ( ) ;
}

QString N::JavTorrentVideo::Identifier(void)
{
  return ui -> Identifier -> text ( ) ;
}

SUID N::JavTorrentVideo::AlbumUuid(void)
{
  return album -> toUuid ( ) ;
}

SUID N::JavTorrentVideo::InterestUuid(void)
{
  return interest -> toUuid ( ) ;
}

SUID N::JavTorrentVideo::GalleryUuid(void)
{
  return gallery -> toUuid ( ) ;
}

SUID N::JavTorrentVideo::NameUuid(int index)
{
  if (index>=ui->Names->topLevelItemCount()) return 0   ;
  QTreeWidgetItem * it = ui->Names->topLevelItem(index) ;
  if (IsNull(it)) return 0                              ;
  return nTreeUuid ( it , 1 )                           ;
}

void N::JavTorrentVideo::AlbumChanged(int index)
{ Q_UNUSED               ( index         ) ;
  SUID u = album->toUuid (               ) ;
  nDropOut               ( u <= 0        ) ;
  plan->site.beginGroup  ( Scope         ) ;
  plan->site.setValue    ( "JtAlbum" , u ) ;
  plan->site.endGroup    (               ) ;
}

void N::JavTorrentVideo::InterestChanged(int index)
{ Q_UNUSED                  ( index            ) ;
  SUID u = interest->toUuid (                  ) ;
  nDropOut                  ( u <= 0           ) ;
  plan->site.beginGroup     ( Scope            ) ;
  plan->site.setValue       ( "JtInterest" , u ) ;
  plan->site.endGroup       (                  ) ;
}

void N::JavTorrentVideo::GalleryChanged(int index)
{ Q_UNUSED                 ( index           ) ;
  SUID u = gallery->toUuid (                 ) ;
  nDropOut                 ( u <= 0          ) ;
  plan->site.beginGroup    ( Scope           ) ;
  plan->site.setValue      ( "JtGallery" , u ) ;
  plan->site.endGroup      (                 ) ;
}

void N::JavTorrentVideo::prepare(void)
{
  ////////////////////////////////////////////////////////
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
  ui -> Names -> setHeaderLabels ( headers             ) ;
  ////////////////////////////////////////////////////////
  QTreeWidgetItem * it                                   ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Release")                    ) ;
  ui -> Names -> addTopLevelItem ( it                  ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Actress")                    ) ;
  ui -> Names -> addTopLevelItem ( it                  ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Product")                    ) ;
  ui -> Names -> addTopLevelItem ( it                  ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("SKU")                        ) ;
  ui -> Names -> addTopLevelItem ( it                  ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Double penetration")         ) ;
  ui -> Names -> addTopLevelItem ( it                  ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Symbols")                    ) ;
  ui -> Names -> addTopLevelItem ( it                  ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Company")                    ) ;
  ui -> Names -> addTopLevelItem ( it                  ) ;
  ////////////////////////////////////////////////////////
  plan -> setFont ( this )                               ;
}

void N::JavTorrentVideo::configure(QString scope,Sql & sql)
{
  ///////////////////////////////////////////////////////////
  QString       Q                                           ;
  QString       CN = QtUUID::createUuidString()               ;
  CMAPs         NM                                          ;
  int           ns = ui->Names->topLevelItemCount()         ;
  ///////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "JtNames" )                   ;
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
      itx  = ui->Names->topLevelItem(i)                     ;
      nms  = SC.getName                                     (
               PlanTable(Names)                             ,
               "uuid"                                       ,
               vLanguageId                                  ,
               znm                                        ) ;
      itx -> setData ( 1 , Qt::UserRole , znm )             ;
      itx -> setText ( 1 , nms                )             ;
    }                                                       ;
    ui->Names->resizeColumnToContents(0)                    ;
    /////////////////////////////////////////////////////////
    SC.close()                                              ;
  }                                                         ;
  SC.remove()                                               ;
  ///////////////////////////////////////////////////////////
  plan->site.beginGroup   ( scope                         ) ;
  if (plan->site.contains("JtSkip"))                        {
    bool skip                                               ;
    skip = plan->site.value("JtSkip").toBool()              ;
    ui  -> Skip             -> blockSignals ( true  )       ;
    ui  -> Skip             -> setChecked   ( skip  )       ;
    ui  -> Skip             -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtCache"))                       {
    bool skip                                               ;
    skip = plan->site.value("JtCache").toBool()             ;
    ui  -> Cache            -> blockSignals ( true  )       ;
    ui  -> Cache            -> setChecked   ( skip  )       ;
    ui  -> Cache            -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtDownload"))                    {
    bool skip                                               ;
    skip = plan->site.value("JtDownload").toBool()          ;
    ui  -> DownloadOnly     -> blockSignals ( true  )       ;
    ui  -> DownloadOnly     -> setChecked   ( skip  )       ;
    ui  -> DownloadOnly     -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtDontParse"))                   {
    bool skip                                               ;
    skip = plan->site.value("JtDontParse").toBool()         ;
    ui  -> DontParse        -> blockSignals ( true  )       ;
    ui  -> DontParse        -> setChecked   ( skip  )       ;
    ui  -> DontParse        -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtImage"))                       {
    bool skip                                               ;
    skip = plan->site.value("JtImage").toBool()             ;
    ui  -> Image            -> blockSignals ( true  )       ;
    ui  -> Image            -> setChecked   ( skip  )       ;
    ui  -> Image            -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtTorrent"))                     {
    bool skip                                               ;
    skip = plan->site.value("JtTorrent").toBool()           ;
    ui  -> Torrent          -> blockSignals ( true  )       ;
    ui  -> Torrent          -> setChecked   ( skip  )       ;
    ui  -> Torrent          -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtLastest"))                     {
    int v                                                   ;
    v   = plan->site.value("JtLastest").toInt()             ;
    ui -> Lastest           -> blockSignals ( true  )       ;
    ui -> Lastest           -> setValue     ( v     )       ;
    ui -> Lastest           -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtRetry"))                       {
    int v                                                   ;
    v   = plan->site.value("JtRetry").toInt()               ;
    ui -> Retry             -> blockSignals ( true  )       ;
    ui -> Retry             -> setValue     ( v     )       ;
    ui -> Retry             -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtPattern"))                {
    QString xcity                                           ;
    xcity = plan->site.valueString("JtPattern")             ;
    ui -> Pattern           -> blockSignals ( true  )       ;
    ui -> Pattern           -> setText      ( xcity )       ;
    ui -> Pattern           -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtJpTorrent"))                   {
    QString xcity                                           ;
    xcity = plan->site.valueString("JtJpTorrent")           ;
    ui -> JpTorrent         -> blockSignals ( true  )       ;
    ui -> JpTorrent         -> setText      ( xcity )       ;
    ui -> JpTorrent         -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtTorrentPath"))                 {
    QString xcity                                           ;
    xcity = plan->site.valueString("JtTorrentPath")         ;
    ui -> TorrentPath       -> blockSignals ( true  )       ;
    ui -> TorrentPath       -> setText      ( xcity )       ;
    ui -> TorrentPath       -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("JtIdentifier"))                  {
    QString xcity                                           ;
    xcity = plan->site.valueString("JtIdentifier")          ;
    ui -> Identifier        -> blockSignals ( true  )       ;
    ui -> Identifier        -> setText      ( xcity )       ;
    ui -> Identifier        -> blockSignals ( false )       ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if (plan->site.contains("JtAlbum"))                       {
    SUID suid                                               ;
    suid = plan->site.value("JtAlbum").toULongLong()        ;
    *album <= suid                                          ;
    DoProcessEvents                                         ;
  }                                                         ;
  if (plan->site.contains("JtInterest"))                    {
    SUID suid                                               ;
    suid = plan->site.value("JtInterest").toULongLong()     ;
    *interest <= suid                                       ;
    DoProcessEvents                                         ;
  }                                                         ;
  if (plan->site.contains("JtGallery"))                     {
    SUID suid                                               ;
    suid = plan->site.value("JtGallery").toULongLong()      ;
    *gallery <= suid                                        ;
    DoProcessEvents                                         ;
  }                                                         ;
  plan -> site . endGroup ( )                               ;
  ///////////////////////////////////////////////////////////
  SqlConnection HC ( sql )                                  ;
  CN = QtUUID::createUuidString()                             ;
  if (HC.open("JavFreeVideo",CN))                           {
    int v                                                   ;
    v = 0                                                   ;
    Q = HC.sql.SelectFrom                                   (
          "id"                                              ,
          "freedl"                                          ,
          HC . OrderByDesc ( "id"  )                        ,
          HC . sql . Limit ( 0 , 1 )                      ) ;
    if (HC.Fetch(Q)) v = HC.Int(0)                          ;
    v++                                                     ;
    if ( v > ui->Lastest->value() )                         {
      ui->Lastest->setValue(v)                              ;
    }                                                       ;
    HC.close()                                              ;
  } else                                                    {
    HC.close()                                              ;
  }                                                         ;
  HC.remove()                                               ;
  ///////////////////////////////////////////////////////////
  hunterSql = sql                                           ;
  Scope     = scope                                         ;
}

void N::JavTorrentVideo::JavTorrentValues(int index)
{
  JavTorrentChanged ( ) ;
}

void N::JavTorrentVideo::JavTorrentChanged(void)
{
  QString path                                                       ;
  bool    skip      = ui -> Skip         -> isChecked ( )            ;
  bool    cache     = ui -> Cache        -> isChecked ( )            ;
  bool    download  = ui -> DownloadOnly -> isChecked ( )            ;
  bool    dontparse = ui -> DontParse    -> isChecked ( )            ;
  bool    image     = ui -> Image        -> isChecked ( )            ;
  bool    torrent   = ui -> Torrent      -> isChecked ( )            ;
  int     lastest   = ui -> Lastest      -> value     ( )            ;
  int     retry     = ui -> Retry        -> value     ( )            ;
  ////////////////////////////////////////////////////////////////////
  plan->site.beginGroup          ( Scope                           ) ;
  ////////////////////////////////////////////////////////////////////
  plan->site.setValue            ( "JtSkip"        , skip          ) ;
  plan->site.setValue            ( "JtCache"       , cache         ) ;
  plan->site.setValue            ( "JtDownload"    , download      ) ;
  plan->site.setValue            ( "JtDontParse"   , dontparse     ) ;
  plan->site.setValue            ( "JtImage"       , image         ) ;
  plan->site.setValue            ( "JtTorrent"     , torrent       ) ;
  plan->site.setValue            ( "JtLastest"     , lastest       ) ;
  plan->site.setValue            ( "JtRetry"       , retry         ) ;
  ////////////////////////////////////////////////////////////////////
  path = ui->Pattern     -> text (                                 ) ;
  plan->site.setValue            ( "JtPattern"     , path.toUtf8() ) ;
  path = ui->JpTorrent   -> text (                                 ) ;
  plan->site.setValue            ( "JtJpTorrent"   , path.toUtf8() ) ;
  path = ui->TorrentPath -> text (                                 ) ;
  plan->site.setValue            ( "JtTorrentPath" , path.toUtf8() ) ;
  path = ui->Identifier  -> text (                                 ) ;
  plan->site.setValue            ( "JtIdentifier"  , path.toUtf8() ) ;
  ////////////////////////////////////////////////////////////////////
  plan->site.endGroup            (                                 ) ;
}

void N::JavTorrentVideo::BrowseTorrent(void)
{
  QString path = ui->TorrentPath->text()      ;
  path = QFileDialog :: getExistingDirectory  (
           this                               ,
           tr("Assign torrent path")          ,
           path                             ) ;
  if (path.length()<=0) return                ;
  ui -> TorrentPath -> blockSignals ( true  ) ;
  ui -> TorrentPath -> setText      ( path  ) ;
  ui -> TorrentPath -> blockSignals ( false ) ;
  JavTorrentChanged ( )                       ;
}

void N::JavTorrentVideo::NameClicked(QTreeWidgetItem * item,int column)
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
  ui -> Names -> setItemWidget ( item , column , Entries        ) ;
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

void N::JavTorrentVideo::NameSelected(int)
{
  if (IsNull(ItemEditing)) return                         ;
  if (IsNull(Entries    )) return                         ;
  /////////////////////////////////////////////////////////
  SUID    u = Entries -> toUuid      ( )                  ;
  QString n = Entries -> currentText ( )                  ;
  int     i = ui->Names->indexOfTopLevelItem(ItemEditing) ;
  QString m = QString::number        (i)                  ;
  /////////////////////////////////////////////////////////
  ui->Names->removeItemWidget ( ItemEditing , 1 )         ;
  ItemEditing -> setData ( 1 , Qt::UserRole , u )         ;
  ItemEditing -> setText ( 1 , n                )         ;
  Entries      = NULL                                     ;
  ItemEditing  = NULL                                     ;
  /////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "JtNames" )                 ;
  plan -> site . setValue   ( m , u     )                 ;
  plan -> site . endGroup   (           )                 ;
}
