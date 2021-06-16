#include <exciton.h>
#include "ui_AupInfoVideo.h"

N::AupInfoVideo:: AupInfoVideo ( QWidget * parent , Plan * p )
                : Widget       (           parent ,        p )
                , ui           ( new Ui::AupInfoVideo        )
                , album        ( NULL                        )
                , interest     ( NULL                        )
                , gallery      ( NULL                        )
                , ItemEditing  ( NULL                        )
                , Entries      ( NULL                        )
{
  ui -> setupUi ( this ) ;
}

N::AupInfoVideo::~AupInfoVideo(void)
{
  delete ui ;
}

bool N::AupInfoVideo::SkipExists(void)
{
  return ui->AupInfoSkip->isChecked() ;
}

bool N::AupInfoVideo::VideoCache(void)
{
  return ui->AupInfoCache->isChecked() ;
}

int N::AupInfoVideo::VideoStart(void)
{
  return ui->AupInfoDvdStart->value() ;
}

int N::AupInfoVideo::VideoEnd(void)
{
  return ui->AupInfoDvdFinish->value() ;
}

SUID N::AupInfoVideo::AlbumUuid(void)
{
  if (IsNull(album)) return 0 ;
  return album->toUuid()      ;
}

SUID N::AupInfoVideo::InterestUuid(void)
{
  if (IsNull(interest)) return 0 ;
  return interest->toUuid()      ;
}

SUID N::AupInfoVideo::GalleryUuid(void)
{
  if (IsNull(gallery)) return 0 ;
  return gallery->toUuid()      ;
}

SUID N::AupInfoVideo::NameUuid(int index)
{
  if (index>=ui->AupNames->topLevelItemCount()) return 0   ;
  QTreeWidgetItem * it = ui->AupNames->topLevelItem(index) ;
  if (IsNull(it)) return 0                                 ;
  return nTreeUuid ( it , 1 )                              ;
}

QString N::AupInfoVideo::Search(void)
{
  return ui->AupInfoDvdPattern->text() ;
}

void N::AupInfoVideo::prepare(void)
{
  album     = new ComboBox ( this , plan           )     ;
  interest  = new ComboBox ( this , plan           )     ;
  gallery   = new ComboBox ( this , plan           )     ;
  ////////////////////////////////////////////////////////
  album    -> setGeometry  (  20 , 140 , 440 ,  28 )     ;
  interest -> setGeometry  (  20 , 180 , 440 ,  28 )     ;
  gallery  -> setGeometry  (  20 , 220 , 440 ,  28 )     ;
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
  ui -> AupNames -> setHeaderLabels ( headers          ) ;
  ////////////////////////////////////////////////////////
  QTreeWidgetItem * it                                   ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Release")                    ) ;
  ui -> AupNames -> addTopLevelItem ( it               ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Actress")                    ) ;
  ui -> AupNames -> addTopLevelItem ( it               ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Product")                    ) ;
  ui -> AupNames -> addTopLevelItem ( it               ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("SKU")                        ) ;
  ui -> AupNames -> addTopLevelItem ( it               ) ;
  it  = new QTreeWidgetItem ( )                          ;
  it -> setText ( 0 , tr("Double penetration")         ) ;
  ui -> AupNames -> addTopLevelItem ( it               ) ;
  ////////////////////////////////////////////////////////
  plan -> setFont ( this )                               ;
}

void N::AupInfoVideo::configure(QString scope,Sql & sql)
{
  QString  Q                                                ;
  QString  CN = QtUUID::createUuidString()                    ;
  CMAPs    NM                                               ;
  int      ns = ui->AupNames->topLevelItemCount()           ;
  ///////////////////////////////////////////////////////////
  plan -> site . beginGroup ( "AupDvdNames" )               ;
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
      itx  = ui->AupNames->topLevelItem(i)                  ;
      nms  = SC.getName                                     (
               PlanTable(Names)                             ,
               "uuid"                                       ,
               vLanguageId                                  ,
               znm                                        ) ;
      itx -> setData ( 1 , Qt::UserRole , znm )             ;
      itx -> setText ( 1 , nms                )             ;
    }                                                       ;
    ui->AupNames->resizeColumnToContents(0)                 ;
    /////////////////////////////////////////////////////////
    SC.close()                                              ;
  }                                                         ;
  SC.remove()                                               ;
  ///////////////////////////////////////////////////////////
  plan->site.beginGroup   ( scope                         ) ;
  if (plan->site.contains("AupInfoDvdSkip"))                {
    bool skip                                               ;
    skip = plan->site.value("AupInfoDvdSkip").toBool()      ;
    ui  -> AupInfoSkip      -> blockSignals ( true  )       ;
    ui  -> AupInfoSkip      -> setChecked   ( skip  )       ;
    ui  -> AupInfoSkip      -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("AupInfoDvdCache"))               {
    bool skip                                               ;
    skip = plan->site.value("AupInfoDvdCache").toBool()     ;
    ui  -> AupInfoCache     -> blockSignals ( true  )       ;
    ui  -> AupInfoCache     -> setChecked   ( skip  )       ;
    ui  -> AupInfoCache     -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("AupInfoDvdStart"))               {
    int v                                                   ;
    v   = plan->site.value("AupInfoDvdStart").toInt()       ;
    ui -> AupInfoDvdStart   -> blockSignals ( true  )       ;
    ui -> AupInfoDvdStart   -> setValue     ( v     )       ;
    ui -> AupInfoDvdStart   -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("AupInfoDvdFinish"))              {
    int v                                                   ;
    v   = plan->site.value("AupInfoDvdFinish").toInt()      ;
    ui -> AupInfoDvdFinish  -> blockSignals ( true  )       ;
    ui -> AupInfoDvdFinish  -> setValue     ( v     )       ;
    ui -> AupInfoDvdFinish  -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("AupInfoDvdPattern"))             {
    QString xcity                                           ;
    xcity = plan->site.valueString("AupInfoDvdPattern")     ;
    ui -> AupInfoDvdPattern -> blockSignals ( true  )       ;
    ui -> AupInfoDvdPattern -> setText      ( xcity )       ;
    ui -> AupInfoDvdPattern -> blockSignals ( false )       ;
  }                                                         ;
  if (plan->site.contains("AupDvdAlbum"))                   {
    SUID suid                                               ;
    suid = plan->site.value("AupDvdAlbum").toULongLong()    ;
    *album <= suid                                          ;
    DoProcessEvents                                         ;
  }                                                         ;
  if (plan->site.contains("AupDvdInterest"))                {
    SUID suid                                               ;
    suid = plan->site.value("AupDvdInterest").toULongLong() ;
    *interest <= suid                                       ;
    DoProcessEvents                                         ;
  }                                                         ;
  if (plan->site.contains("AupDvdGallery"))                 {
    SUID suid                                               ;
    suid = plan->site.value("AupDvdGallery").toULongLong()  ;
    *gallery <= suid                                        ;
    DoProcessEvents                                         ;
  }                                                         ;
  plan -> site . endGroup ( )                               ;
  ///////////////////////////////////////////////////////////
  SqlConnection HC ( sql )                                  ;
  CN = QtUUID::createUuidString()                             ;
  if (HC.open("AupInfoVideo",CN))                           {
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    int v                                                   ;
    v = 0                                                   ;
    Q = HC.sql.SelectFrom                                   (
          "id"                                              ,
          "xcityjpdvd"                                      ,
          HC . OrderByDesc ( "id"  )                        ,
          HC . sql . Limit ( 0 , 1 )                      ) ;
    if (HC.Fetch(Q)) v = HC.Int(0)                          ;
    v++                                                     ;
    ui->XcityJpDvdStart->setValue(v)                        ;
    v += 300                                                ;
    if (v>ui->XcityJpDvdFinish->value())                    {
      ui->XcityJpDvdFinish->setValue(v)                     ;
    }                                                       ;
#endif
    HC.close()                                              ;
  } else                                                    {
    HC.close()                                              ;
  }                                                         ;
  HC.remove()                                               ;
  ///////////////////////////////////////////////////////////
  hunterSql = sql                                           ;
  Scope     = scope                                         ;
}

void N::AupInfoVideo::AlbumChanged(int index)
{ Q_UNUSED               ( index             ) ;
  SUID u = album->toUuid (                   ) ;
  nDropOut               ( u <= 0            ) ;
  plan->site.beginGroup  ( Scope             ) ;
  plan->site.setValue    ( "AupDvdAlbum" , u ) ;
  plan->site.endGroup    (                   ) ;
}

void N::AupInfoVideo::InterestChanged(int index)
{ Q_UNUSED                  ( index                ) ;
  SUID u = interest->toUuid (                      ) ;
  nDropOut                  ( u <= 0               ) ;
  plan->site.beginGroup     ( Scope                ) ;
  plan->site.setValue       ( "AupDvdInterest" , u ) ;
  plan->site.endGroup       (                      ) ;
}

void N::AupInfoVideo::GalleryChanged(int index)
{ Q_UNUSED                 ( index               ) ;
  SUID u = gallery->toUuid (                     ) ;
  nDropOut                 ( u <= 0              ) ;
  plan->site.beginGroup    ( Scope               ) ;
  plan->site.setValue      ( "AupDvdGallery" , u ) ;
  plan->site.endGroup      (                     ) ;
}

void N::AupInfoVideo::AupValueChanged(int)
{
  AupChanged ( ) ;
}

void N::AupInfoVideo::AupChanged(void)
{
  QString path                                                                 ;
  bool    skip    = ui -> AupInfoSkip      -> isChecked ( )                    ;
  bool    cache   = ui -> AupInfoCache     -> isChecked ( )                    ;
  int     startId = ui -> AupInfoDvdStart  -> value     ( )                    ;
  int     endId   = ui -> AupInfoDvdFinish -> value     ( )                    ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.beginGroup                ( Scope                               ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.setValue                  ( "AupInfoDvdSkip"    , skip          ) ;
  plan->site.setValue                  ( "AupInfoDvdCache"   , cache         ) ;
  plan->site.setValue                  ( "AupInfoDvdStart"   , startId       ) ;
  plan->site.setValue                  ( "AupInfoDvdFinish"  , endId         ) ;
  //////////////////////////////////////////////////////////////////////////////
  path = ui->AupInfoDvdPattern -> text (                                     ) ;
  plan->site.setValue                  ( "AupInfoDvdPattern" , path.toUtf8() ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.endGroup                  (                                     ) ;
}

void N::AupInfoVideo::NameClicked(QTreeWidgetItem * item,int column)
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

void N::AupInfoVideo::NameSelected(int)
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
  plan -> site . beginGroup ( "AupDvdNames" )                ;
  plan -> site . setValue   ( m , u         )                ;
  plan -> site . endGroup   (               )                ;
}
