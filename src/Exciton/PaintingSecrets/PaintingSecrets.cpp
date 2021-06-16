#include <exciton.h>
#include "ui_PaintingSecrets.h"

#define Decide decisions[GuiMainId]

PaintingSecrets:: PaintingSecrets (int argc,char ** argv,QWidget * parent)
                : N::MobileMain   (    argc,        argv,          parent)
                , ui              (new Ui::PaintingSecrets               )
                , master          (NULL                                  )
                , secret          (NULL                                  )
                , settings        (NULL                                  )
                , screenconf      (NULL                                  )
                , fontconf        (NULL                                  )
                , vendor          (NULL                                  )
                , editor          (NULL                                  )
                , recorder        (NULL                                  )
                , browser         (NULL                                  )
                , folder          (NULL                                  )
                , ftp             (NULL                                  )
                , steps           (0                                     )
{
  ui   -> setupUi(this)                     ;
  plan -> status      = ui->Status          ;
  setStatusBar        ( ui->Status )        ;
  statusBar() -> hide ( )                   ;
  ui->Tools   -> hide ( )                   ;
  plan->font    = N::Font(font())           ;
  #ifdef Q_OS_ANDORID
  plan->font.cm = 0.40                      ;
  plan->Application = "PaintingSecret"      ;
  #endif
  #ifdef Q_OS_IOS
  plan->font.cm = 0.36                      ;
  plan->Application = "PaintingSecrets.app" ;
  #endif
}

PaintingSecrets::~PaintingSecrets(void)
{
  delete ui ;
}

void PaintingSecrets::InstallFonts(double defaultSize)
{
  CUIDs FIDs                                      ;
  int   fid                                       ;
  Nextstep ( )                                    ;
  FIDs << N::Fonts::Default                       ;
  FIDs << N::Fonts::Menu                          ;
  FIDs << N::Fonts::Editor                        ;
  FIDs << N::Fonts::Tree                          ;
  FIDs << N::Fonts::ToolTip                       ;
  FIDs << N::Fonts::Status                        ;
  FIDs << N::Fonts::Message                       ;
  FIDs << N::Fonts::ComboBox                      ;
  FIDs << N::Fonts::TreeView                      ;
  FIDs << N::Fonts::ListView                      ;
  FIDs << N::Fonts::TableView                     ;
  FIDs << N::Fonts::Label                         ;
  FIDs << N::Fonts::CheckBox                      ;
  FIDs << N::Fonts::Progress                      ;
  FIDs << N::Fonts::Button                        ;
  FIDs << N::Fonts::Spin                          ;
  FIDs << N::Fonts::IPA                           ;
  FIDs << N::Fonts::Math                          ;
  FIDs << N::Fonts::User                          ;
  FIDs << N::Fonts::Class                         ;
  FIDs << N::Fonts::Inherit                       ;
  FIDs << N::Fonts::Keyword                       ;
  FIDs << N::Fonts::Specifier                     ;
  FIDs << N::Fonts::Qualifier                     ;
  FIDs << N::Fonts::Member                        ;
  FIDs << N::Fonts::Function                      ;
  FIDs << N::Fonts::Symbol                        ;
  FIDs << N::Fonts::Requirement                   ;
  FIDs << N::Fonts::Comment                       ;
  foreach (fid,FIDs)                              {
    Nextstep ( )                                  ;
    plan->fonts[fid]    = plan->font              ;
    plan->fonts[fid].cm = defaultSize             ;
  }                                               ;
  Nextstep ( )                                    ;
  plan->fonts[N::Fonts::Menu    ].cm = 0.28       ;
  plan->fonts[N::Fonts::ListView].cm = 0.28       ;
  foreach (fid,FIDs)                              {
    Nextstep ( )                                  ;
    QString FID = QString("Font %1").arg(fid)     ;
    plan->settings.LoadFont(FID,plan->fonts[fid]) ;
    plan->fonts[fid].setScreen(plan->screen)      ;
  }                                               ;
  Nextstep ( )                                    ;
  plan -> setFont ( this , N::Fonts::Default )    ;
  plan -> setFont ( this                     )    ;
}

int PaintingSecrets::abort(void)
{
  return 0 ;
}

bool PaintingSecrets::Shutdown(void)
{
  return true ;
}

void PaintingSecrets::Quit(void)
{
  DefaultEnding ( ) ;
}

bool PaintingSecrets::TurnOff(void)
{
  if (NotNull(plan->Ftp))                {
    if (N::FileSharing::serverRunning()) {
      N::FileSharing :: stopServer ( )   ;
    }                                    ;
  }                                      ;
  return true                            ;
}

void PaintingSecrets::Nextstep(void)
{
  steps++                             ;
  #ifdef CIOSDEBUG
  qDebug   ( "Step %d" , steps )      ;
  #endif
  if (NotNull(vendor))                {
    vendor -> setStep       ( steps ) ;
    plan   -> processEvents (       ) ;
  }                                   ;
}

void PaintingSecrets::Hide(void)
{
  hide ( ) ;
}

bool PaintingSecrets::bootup(void)
{
  QTimer :: singleShot ( 500 , this , SLOT ( startup ( ) ) ) ;
  return true                                                ;
}

bool PaintingSecrets::prepare(void)
{
  //////////////////////////////////////////////////////////////
  plan -> settings   . Username = "CIOS"                       ;
  plan -> LanguageId = N :: SystemLanguageId (               ) ;
  #ifdef Q_OS_ANDROID
  plan -> setSettings ( "files/Users/PaintingSecret.ndb"     ) ;
  #endif
  #ifdef Q_OS_IOS
  plan -> setSettings ( "Documents/Users/PaintingSecrets.ndb" ) ;
  #endif
  plan -> Initialize  (                                      ) ;
  N::InstallTables    ( *plan                                ) ;
  setFont             ( plan->font                           ) ;
  plan-> fonts[N::Fonts::Default] = plan->font                 ;
  //////////////////////////////////////////////////////////////
  InstallStackMdi     (                                      ) ;
  showMaximized       (                                      ) ;
  statusBar() -> hide (                                      ) ;
  ui->Tools   -> hide (                                      ) ;
  //////////////////////////////////////////////////////////////
  plan->processEvents (                                      ) ;
  plan->processEvents (                                      ) ;
  plan->processEvents (                                      ) ;
  plan->processEvents (                                      ) ;
  showLogo            (                                      ) ;
  plan->processEvents (                                      ) ;
  showMaximized       (                                      ) ;
  plan->processEvents (                                      ) ;
  plan->processEvents (                                      ) ;
  plan->processEvents (                                      ) ;
  plan->processEvents (                                      ) ;
  //////////////////////////////////////////////////////////////
  Decide.setCondition(Configured,true)                         ;
  //////////////////////////////////////////////////////////////
  return true                                                  ;
}

bool PaintingSecrets::configure(void)
{
  return true ;
}

bool PaintingSecrets::loading(void)
{
  Decide.setCondition(Loading,true)                                  ;
  Nextstep      (      )                                             ;
  ////////////////////////////////////////////////////////////////////
  #ifdef Q_OS_ANDROID
  plan->sql.SqlMode       = "SQLITE"                                 ;
  plan->sql.dbName        = plan->Path("files/Users/PaintingSecret.ndb") ;
  ////////////////////////////////////////////////////////////////////
  plan->LocalSql.SqlMode  = "SQLITE"                                 ;
  plan->LocalSql.dbName   = plan->Path("files/Users/PaintingSecret.ndb") ;
  ////////////////////////////////////////////////////////////////////
  plan->site.SQL          = new N::Sql()                             ;
  plan->site.SQL->SqlMode = "SQLITE"                                 ;
  plan->site.SQL->dbName  = plan->Path("files/Users/PaintingSecret.ndb") ;
  plan->site.Table        = "settings"                               ;
  plan->site.Username     = "CIOS"                                   ;
  plan->site.Initialize ( )                                          ;
  #endif
  #ifdef Q_OS_IOS
  plan->sql.SqlMode       = "SQLITE"                                 ;
  plan->sql.dbName        = plan->Path("Documents/Users/PaintingSecrets.ndb") ;
  ////////////////////////////////////////////////////////////////////
  plan->LocalSql.SqlMode  = "SQLITE"                                 ;
  plan->LocalSql.dbName   = plan->Path("Documents/Users/PaintingSecrets.ndb") ;
  ////////////////////////////////////////////////////////////////////
  plan->site.SQL          = new N::Sql()                             ;
  plan->site.SQL->SqlMode = "SQLITE"                                 ;
  plan->site.SQL->dbName  = plan->Path("Documents/Users/PaintingSecrets.ndb") ;
  plan->site.Table        = "settings"                               ;
  plan->site.Username     = "CIOS"                                   ;
  plan->site.Initialize ( )                                          ;
  #endif
  ////////////////////////////////////////////////////////////////////
  Nextstep      (                 )                                  ;
  #ifdef Q_OS_ANDORID
  InstallFonts  ( 0.40            )                                  ;
  #endif
  #ifdef Q_OS_IOS
  InstallFonts  ( 0.36            )                                  ;
  #endif
  InstallDirs   (                 )                                  ;
  LoadSupports  ( plan->languages )                                  ;
  Nextstep      (                 )                                  ;
  AttachActions (                 )                                  ;
  Nextstep      (                 )                                  ;
  InstallIcons  ( 0               )                                  ;
  InstallSounds (                 )                                  ;
  ////////////////////////////////////////////////////////////////////
  Decide.setCondition(Loading,false)                                 ;
  Decide.setCondition(Loaded ,true )                                 ;
  return true                                                        ;
}

void PaintingSecrets::LoadSupports(N::Languages & L)
{
  L . Default   = plan->LanguageId                             ;
  L . languages . clear ( )                                    ;
  L . Uuids     . clear ( )                                    ;
  L . Names     . clear ( )                                    ;
  if (!plan->containsTable(N::Tables::MajorUuid)) return       ;
  if (!plan->containsTable(N::Tables::Names    )) return       ;
  if (!plan->containsTable(N::Tables::Languages)) return       ;
  N::SqlConnection LC(plan->sql)                               ;
  if (LC.open("nLanguages","equal"))                           {
    QString Q                                                  ;
    Q = LC.sql.SelectFrom                                      (
          "id,uuid,native"                                     ,
          PlanTable(Languages)                                 ,
          "order by rank asc ;"                              ) ;
    SqlLoopNow(LC,Q)                                           ;
      int     id     = LC.Value (0).toInt()                    ;
      SUID    uuid   = LC.Uuid  (1)                            ;
      QString Native = LC.String(2)                            ;
      if (uuid>0)                                              {
        L.languages       << id                                ;
        L.Uuids   [ id   ] = uuid                              ;
        L.UuidIDs [ uuid ] = id                                ;
        L.Names   [ uuid ] = Native                            ;
      }                                                        ;
      plan -> processEvents ( )                                ;
    SqlLoopErr(LC,Q)                                           ;
    SqlLoopEnd(LC,Q)                                           ;
    int gap = L.languages.count()                              ;
    int cnx = 0                                                ;
    gap /= 64                                                  ;
    ForLanguage(LID,L.languages)                               ;
      SUID u = L.Uuids[LID]                                    ;
      Q = LC . sql . SelectFrom                                (
            "name"                                             ,
            PlanTable(Names)                                   ,
            QString ( "where uuid = %1 and language = %2"      )
            .arg    ( u                                        )
            .arg    ( L.Default                            ) ) ;
      IfSqlQuery(LC,Q) L.Names[u] = LC.String(0)               ;
      cnx++                                                    ;
      if ( ( gap > 0 ) && ( ( cnx % gap ) == 0 ) )             {
        Nextstep ( )                                           ;
      }                                                        ;
      plan -> processEvents ( )                                ;
    EndLanguage(LID,L.languages)                               ;
    LC.close()                                                 ;
  }                                                            ;
  LC.remove()                                                  ;
}

bool PaintingSecrets::brand(void)
{
  N::Time::skip       (  2500        ) ;
  Decide.setCondition ( Brand , true ) ;
  return true                          ;
}

bool PaintingSecrets::advertising(void)
{
  N::Time::skip       (   300              ) ;
  Decide.setCondition ( Advertising , true ) ;
  return true                                ;
}

bool PaintingSecrets::primary(void)
{
  Decide . setCondition ( Started     , true  ) ;
  ///////////////////////////////////////////////
  Actual                (                     ) ;
  ///////////////////////////////////////////////
  Decide . setCondition ( Loaded      , false ) ;
  Decide . setCondition ( Started     , true  ) ;
  Decide . setCondition ( Interactive , true  ) ;
  ///////////////////////////////////////////////
  Ready = true                                  ;
  return true                                   ;
}

void PaintingSecrets::Settings(void)
{
  Alert                       ( Error  ) ;
  Stacked -> setCurrentWidget ( secret ) ;
  secret  -> Settings         (        ) ;
}

void PaintingSecrets::Start(void)
{
}

void PaintingSecrets::Stop(void)
{
}

void PaintingSecrets::showLogo(void)
{
  if (IsNull(vendor))                                                  {
    vendor   = new N::PaintingSecretSurface ( Stacked                ) ;
    vendor  -> Background = QImage          ( ":/icons/Painting.jpg" ) ;
    Stacked -> addWidget                    ( vendor                 ) ;
    vendor  -> StartBusy                    ( plan , 158             ) ;
  }                                                                    ;
  Stacked   -> setCurrentWidget             ( vendor                 ) ;
}

void PaintingSecrets::logoPage(void)
{
  showLogo                  (                  ) ;
  plan->processEvents       (                  ) ;
  N::Time::skip             ( 2500             ) ;
  ////////////////////////////////////////////////
  QTimer::singleShot   (300,this,SLOT(adPage())) ;
}

void PaintingSecrets::adPage(void)
{
  QTimer::singleShot (300,this,SLOT(Actual())) ;
}

void PaintingSecrets::Actual(void)
{
  vendor  -> StopBusy ( )                                                     ;
  /////////////////////////////////////////////////////////////////////////////
  master  = new N::PaintingVendor ( Stacked , plan                          ) ;
  master  -> Background = QImage  ( ":/icons/Painting.jpg"                  ) ;
  Stacked -> addWidget        ( master                                      ) ;
  Stacked -> setCurrentWidget ( master                                      ) ;
  nConnect      ( master , SIGNAL(Quit      ()) , this , SLOT(Quit      ()) ) ;
  nConnect      ( master , SIGNAL(Settings  ()) , this , SLOT(Settings  ()) ) ;
  nConnect      ( master , SIGNAL(Encryption()) , this , SLOT(Encryption()) ) ;
  nConnect      ( master , SIGNAL(Decryption()) , this , SLOT(Decryption()) ) ;
  nConnect      ( master , SIGNAL(Depot     ()) , this , SLOT(Depot     ()) ) ;
  /////////////////////////////////////////////////////////////////////////////
  secret = new N::PaintingSecretGui ( Stacked , plan )                        ;
  Stacked -> addWidget         ( secret                                     ) ;
  #ifdef Q_OS_ANDROID
  secret  -> Root = QDir       ( plan->Path("files") )                        ;
  secret  -> QM   = "PaintingSecret.qm"                                       ;
  secret  -> InstallPathes ( )                                                ;
  secret  -> AndroidPathes ( )                                                ;
  #endif
  #ifdef Q_OS_IOS
  secret  -> Root = QDir       ( plan->Path("Documents") )                    ;
  secret  -> QM   = "PaintingSecrets.qm"                                      ;
  secret  -> InstallPathes ( )                                                ;
  secret  -> ApplePathes   ( )                                                ;
  #endif
  nConnect ( secret , SIGNAL(Back ())                                         ,
             this   , SLOT  (Front())                                       ) ;
  nConnect ( secret , SIGNAL(Recording(QString))                              ,
             this   , SLOT  (Recording(QString))                            ) ;
  nConnect ( secret , SIGNAL(Obtain(QString))                                 ,
             this   , SLOT  (Obtain(QString))                               ) ;
  nConnect ( secret , SIGNAL(Transfer(QString))                               ,
             this   , SLOT  (Transfer(QString))                             ) ;
  nConnect ( secret , SIGNAL(FullFtp())                                       ,
             this   , SLOT  (FullFtp())                                     ) ;
  nConnect ( secret , SIGNAL(FullDepot())                                     ,
             this   , SLOT  (FullDepot())                                   ) ;
  nConnect ( secret , SIGNAL(Manual())                                        ,
             this   , SLOT  (Manual())                                      ) ;
  nConnect ( secret , SIGNAL(NewText(QDir,QDir))                              ,
             this   , SLOT  (NewText(QDir,QDir))                            ) ;
  nConnect ( secret , SIGNAL(LoadText(QDir,QDir,QString))                     ,
             this   , SLOT  (LoadText(QDir,QDir,QString))                   ) ;
  /////////////////////////////////////////////////////////////////////////////
  editor    = new N::PadEditor  ( Stacked , plan                            ) ;
  Stacked  -> addWidget         ( editor                                    ) ;
  #ifdef Q_OS_ANDROID
  editor   -> Root    = QDir    ( plan -> Path ( "files"           )        ) ;
  editor   -> Current = QDir    ( plan -> Path ( "files/Documents" )        ) ;
  #endif
  #ifdef Q_OS_IOS
  editor   -> Root    = QDir    ( plan -> Path ( "Documents"           )    ) ;
  editor   -> Current = QDir    ( plan -> Path ( "Documents/Documents" )    ) ;
  #endif
  nConnect ( editor , SIGNAL(Back()) , this , SLOT(BackSecrets()) )           ;
  /////////////////////////////////////////////////////////////////////////////
  recorder  = new N::PadRecorder ( Stacked , plan                           ) ;
  Stacked  -> addWidget          ( recorder                                 ) ;
  #ifdef Q_OS_ANDROID
  recorder -> Root    = QDir     ( plan -> Path ( "files"               )   ) ;
  recorder -> Current = QDir     ( plan -> Path ( "files/Documents"     )   ) ;
  #endif
  #ifdef Q_OS_IOS
  recorder -> Root    = QDir     ( plan -> Path ( "Documents"           )   ) ;
  recorder -> Current = QDir     ( plan -> Path ( "Documents/Documents" )   ) ;
  #endif
  recorder -> setPlay            ( false                                    ) ;
  recorder -> Detect             (                                          ) ;
  nConnect ( recorder , SIGNAL(Back()) , this , SLOT(BackSecrets()) )         ;
  /////////////////////////////////////////////////////////////////////////////
  browser   = new N::PadBrowser  ( Stacked , plan                           ) ;
  Stacked  -> addWidget          ( browser                                  ) ;
  #ifdef Q_OS_ANDROID
  browser  -> Root    = QDir     ( plan -> Path ( "files"               )   ) ;
  browser  -> Current = QDir     ( plan -> Path ( "files/Documents"     )   ) ;
  #endif
  #ifdef Q_OS_IOS
  browser  -> Root    = QDir     ( plan -> Path ( "Documents"           )   ) ;
  browser  -> Current = QDir     ( plan -> Path ( "Documents/Documents" )   ) ;
  #endif
  browser  -> TopLevels << "Documents"                                        ;
  browser  -> TopLevels << "Download"                                         ;
  browser  -> TopLevels << "Encryption"                                       ;
  browser  -> TopLevels << "Files"                                            ;
  browser  -> TopLevels << "Images"                                           ;
  browser  -> TopLevels << "Keys"                                             ;
  browser  -> TopLevels << "Upload"                                           ;
  if (plan->Verbose>=90)                                                      {
    browser-> TopLevels << "Temp"                                             ;
    browser-> TopLevels << "Sounds"                                           ;
    browser-> TopLevels << "Users"                                            ;
  }                                                                           ;
  nConnect ( browser , SIGNAL(Back()) , this , SLOT(FullFtp()) )              ;
  nConnect ( browser , SIGNAL ( SelectFiles (QStringList) )                   ,
             this    , SLOT   ( DropFiles   (QStringList) )                 ) ;
  /////////////////////////////////////////////////////////////////////////////
  folder    = new N::PadBrowser  ( Stacked , plan                           ) ;
  Stacked  -> addWidget          ( folder                                   ) ;
  #ifdef Q_OS_ANDROID
  folder   -> Root    = QDir     ( plan -> Path ( "files"               )   ) ;
  folder   -> Current = QDir     ( plan -> Path ( "files/Documents"     )   ) ;
  #endif
  #ifdef Q_OS_IOS
  folder   -> Root    = QDir     ( plan -> Path ( "Documents"           )   ) ;
  folder   -> Current = QDir     ( plan -> Path ( "Documents/Documents" )   ) ;
  #endif
  folder   -> TopLevels << "Documents"                                        ;
  folder   -> TopLevels << "Download"                                         ;
  folder   -> TopLevels << "Encryption"                                       ;
  folder   -> TopLevels << "Files"                                            ;
  folder   -> TopLevels << "Images"                                           ;
  folder   -> TopLevels << "Keys"                                             ;
  folder   -> TopLevels << "Upload"                                           ;
  if (plan->Verbose>=90)                                                      {
    folder -> TopLevels << "Temp"                                             ;
    folder -> TopLevels << "Sounds"                                           ;
    folder -> TopLevels << "Users"                                            ;
  }                                                                           ;
  folder  -> setAnswer          ( false                                     ) ;
  folder  -> setFlags           ( 0x03                                      ) ;
  nConnect ( folder , SIGNAL(Back()) , this , SLOT(BackSecrets()) )           ;
  /////////////////////////////////////////////////////////////////////////////
  ftp       = new N::PadFtp      ( Stacked , plan                           ) ;
  Stacked  -> addWidget          ( ftp                                      ) ;
  #ifdef Q_OS_ANDROID
  ftp      -> Root    = QDir     ( plan -> Path ( "files"               )   ) ;
  ftp      -> Current = QDir     ( plan -> Path ( "files/Documents"     )   ) ;
  #endif
  #ifdef Q_OS_IOS
  ftp      -> Root    = QDir     ( plan -> Path ( "Documents"           )   ) ;
  ftp      -> Current = QDir     ( plan -> Path ( "Documents/Documents" )   ) ;
  #endif
  nConnect ( ftp , SIGNAL(Back   ()) , this , SLOT(BackSecrets()) )           ;
  nConnect ( ftp , SIGNAL(Picking()) , this , SLOT(PickFiles  ()) )           ;
  /////////////////////////////////////////////////////////////////////////////
  #ifdef Q_OS_ANDROID
  QDir        DP ( plan -> Path ( "files"     ) )                             ;
  #endif
  #ifdef Q_OS_IOS
  QDir        DP ( plan -> Path ( "Documents" ) )                             ;
  #endif
  #if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
  QDir        DP ( plan -> Path ( "Files"     ) )                             ;
  #endif
  QStringList SDF                                                             ;
  SDF << "Temp"                                                               ;
  secret  -> DeletePath ( DP , SDF )                                          ;
  DP . mkdir            ( "Temp"   )                                          ;
  /////////////////////////////////////////////////////////////////////////////
  master  -> startup    (          )                                          ;
  secret  -> BootupFtp  (          )                                          ;
  secret  -> ftp -> removeWidget ( secret -> ftp -> widget ( 4 ) )            ;
  secret  -> ftp -> removeWidget ( secret -> ftp -> widget ( 1 ) )            ;
  browser -> List       (          )                                          ;
  folder  -> List       (          )                                          ;
}

void PaintingSecrets::Encryption(void)
{
  Alert                       ( Error  ) ;
  Stacked -> setCurrentWidget ( secret ) ;
  secret  -> Encryption       (        ) ;
}

void PaintingSecrets::Decryption(void)
{
  Alert                       ( Error  ) ;
  Stacked -> setCurrentWidget ( secret ) ;
  secret  -> Decryption       (        ) ;
}

void PaintingSecrets::Depot(void)
{
  Alert                       ( Error  ) ;
  Stacked -> setCurrentWidget ( secret ) ;
  secret  -> Depot            (        ) ;
}

void PaintingSecrets::Front(void)
{
  Alert                        ( Error  ) ;
  Stacked  -> setCurrentWidget ( master ) ;
}

void PaintingSecrets::BackSecrets(void)
{
  Alert                       ( Error  ) ;
  Stacked -> setCurrentWidget ( secret ) ;
}

void PaintingSecrets::Recording(QString path)
{
  recorder -> Current = QDir   ( path     ) ;
  Stacked  -> setCurrentWidget ( recorder ) ;
  recorder -> Detect           (          ) ;
  Alert                        ( Error    ) ;
}

void PaintingSecrets::NewText(QDir root,QDir current)
{
  editor  -> Root    = root              ;
  editor  -> Current = current           ;
  Stacked -> setCurrentWidget ( editor ) ;
  editor  -> New              (        ) ;
  Alert                       ( Error  ) ;
}

void PaintingSecrets::LoadText(QDir root,QDir current,QString filename)
{
  editor  -> Root    = root                ;
  editor  -> Current = current             ;
  Stacked -> setCurrentWidget ( editor   ) ;
  editor  -> setFilename      ( filename ) ;
  editor  -> Load             ( filename ) ;
  Alert                       ( Error    ) ;
}

void PaintingSecrets::Obtain(QString path)
{ // Temporary in this way , obtain should be `Obtain` images
  // `Obtain` provides a series of picture sites
  ftp     -> Current = QDir   ( path  ) ;
  Stacked -> setCurrentWidget ( ftp   ) ;
  Alert                       ( Error ) ;
}

void PaintingSecrets::Transfer(QString path)
{
  ftp     -> Current = QDir   ( path  ) ;
  Stacked -> setCurrentWidget ( ftp   ) ;
  Alert                       ( Error ) ;
}

void PaintingSecrets::FullFtp(void)
{
  Stacked -> setCurrentWidget ( ftp   ) ;
  Alert                       ( Error ) ;
}

void PaintingSecrets::DropFiles(QStringList files)
{
  ftp     -> Root    = browser -> Root    ;
  ftp     -> Current = browser -> Current ;
  Stacked -> setCurrentWidget ( ftp   )   ;
  ftp     -> DropFiles        ( files )   ;
  Alert                       ( Error )   ;
}

void PaintingSecrets::FullDepot(void)
{
  Stacked -> setCurrentWidget ( folder ) ;
  Alert                       ( Error  ) ;
}

void PaintingSecrets::PickFiles(void)
{
  Stacked -> setCurrentWidget ( browser ) ;
  Alert                       ( Error   ) ;
}

void PaintingSecrets::Manual(void)
{
  QString address                                        ;
  address = "http://manual.paintingsecrets.neutrino.com" ;
  plan -> settings . beginGroup ( "PaintingSecrets"    ) ;
  if (plan->settings.contains("Manual"))                 {
    address = plan -> settings. valueString ( "Manual" ) ;
  }                                                      ;
  plan -> settings . endGroup   (                      ) ;
  QUrl help ( address )                                  ;
  QDesktopServices :: openUrl ( help )                   ;
}
