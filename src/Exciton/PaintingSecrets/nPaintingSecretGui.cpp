#include <exciton.h>

///////////////////////////////////////////////////////////////////////////////

#define DEBUGPAINTING

#ifdef DEBUGPAINTING
#define XDEBUG(msg) if (plan->Verbose>=90) plan -> Debug ( msg)
#else
#define XDEBUG(msg)
#endif

///////////////////////////////////////////////////////////////////////////////

typedef struct    {
  int    Id       ;
  char * Path     ;
} LocaleDirectory ;

#pragma message("PaintingSecretGui LocaleDirectory requires some fix up")

LocaleDirectory LocaleDirectories[4096] ;
void * psLocaleDirectories = (void *)LocaleDirectories ;

static bool LidTo(int Id,QString & LC)
{
  int i = 0                          ;
  while (LocaleDirectories[i].Id!=0) {
    if (Id==LocaleDirectories[i].Id) {
      LC = LocaleDirectories[i].Path ;
      return true                    ;
    }                                ;
    i++                              ;
  }                                  ;
  return false                       ;
}

N::PaintingSecretGui:: PaintingSecretGui ( QWidget      * parent , Plan * p )
                     : Splitter          ( Qt::Vertical , parent ,        p )
                     , header            ( NULL                             )
                     , stack             ( NULL                             )
                     , menu              ( NULL                             )
                     , encrypt           ( NULL                             )
                     , decrypt           ( NULL                             )
                     , depot             ( NULL                             )
                     , settings          ( NULL                             )
                     , srcPicture        ( NULL                             )
                     , keyPicture        ( NULL                             )
                     , picTool           ( NULL                             )
                     , fileTool          ( NULL                             )
                     , folderTool        ( NULL                             )
                     , folderEdit        ( NULL                             )
                     , textTool          ( NULL                             )
                     , audioTool         ( NULL                             )
                     , folderList        ( NULL                             )
                     , vcf               ( NULL                             )
                     , ftp               ( NULL                             )
                     , fontconf          ( NULL                             )
                     , screenconf        ( NULL                             )
                     , mdi               ( NULL                             )
                     , label             ( NULL                             )
                     , progress          ( NULL                             )
                     , pickPicture       ( NULL                             )
                     , pickLanguage      ( NULL                             )
                     , encryptReport     ( NULL                             )
                     , decryptReport     ( NULL                             )
                     , plainText         ( NULL                             )
                     , line              ( NULL                             )
                     , archive           ( NULL                             )
                     , pickArchive       ( NULL                             )
                     , help              ( NULL                             )
                     , packaging         ( 0                                )
                     , SourcePicture     ( ""                               )
                     , KeyPicture        ( ""                               )
                     , DecryptPicture    ( ""                               )
                     , DecryptKey        ( ""                               )
                     , BackWidget        ( NULL                             )
                     , BackMenu          ( NULL                             )
                     , ReturnLabel       ( ""                               )
                     , debug             ( false                            )
{
  Configure ( ) ;
}

N::PaintingSecretGui::~PaintingSecretGui (void)
{
}

QSize N::PaintingSecretGui::sizeHint(void) const
{
  if ( plan  -> Booleans [ "Desktop" ] ) {
    return QSize ( 1280 ,  900 )         ;
  } else
  if ( plan  -> Booleans [ "Pad"     ] ) {
    return QSize ( 1024 ,  720 )         ;
  } else
  if ( plan  -> Booleans [ "Phone"   ] ) {
    return QSize (  320 ,  480 )         ;
  }                                      ;
  return   QSize ( 1024 ,  720 )         ;
}

void N::PaintingSecretGui::resizeEvent(QResizeEvent * event)
{
  QSplitter :: resizeEvent ( event ) ;
  relocation               (       ) ;
}

void N::PaintingSecretGui::showEvent(QShowEvent * event)
{
  QSplitter :: showEvent ( event ) ;
  relocation             (       ) ;
}

void N::PaintingSecretGui::Configure (void)
{
  setHandleWidth                        ( 1            ) ;
  ////////////////////////////////////////////////////////
  plan -> settings . beginGroup         ( "System"     ) ;
  if (plan->settings.contains("Debug"))                  {
    debug = plan->settings.value("Debug").toBool()       ;
  }                                                      ;
  plan -> settings . endGroup           (              ) ;
  ////////////////////////////////////////////////////////
  header   = new StackedWidget          ( this , plan  ) ;
  stack    = new StackedWidget          ( this , plan  ) ;
  menu     = new StackedWidget          ( this , plan  ) ;
  ////////////////////////////////////////////////////////
  header  -> setMinimumHeight           ( 28           ) ;
  header  -> setMaximumHeight           ( 28           ) ;
  menu    -> setMinimumHeight           ( 40           ) ;
  menu    -> setMaximumHeight           ( 40           ) ;
  ////////////////////////////////////////////////////////
  addWidget                             ( header       ) ;
  addWidget                             ( stack        ) ;
  addWidget                             ( menu         ) ;
  ////////////////////////////////////////////////////////
  encrypt  = new PaintingEncryptionTool ( menu , plan  ) ;
  decrypt  = new PaintingDecryptionTool ( menu , plan  ) ;
  depot    = new PaintingDepotTool      ( menu , plan  ) ;
  settings = new PaintingSettingsTool   ( menu , plan  ) ;
  srcPicture  = new PaintingPickTool    ( menu , plan  ) ;
  keyPicture  = new PaintingPickTool    ( menu , plan  ) ;
  getEncrypt  = new PaintingPickTool    ( menu , plan  ) ;
  getKeyPic   = new PaintingPickTool    ( menu , plan  ) ;
  viewImages  = new PaintingPickTool    ( menu , plan  ) ;
  viewEncrypt = new PaintingPickTool    ( menu , plan  ) ;
  viewKeys    = new PaintingPickTool    ( menu , plan  ) ;
  fileTool    = new PaintingFilesTool   ( menu , plan  ) ;
  folderTool  = new PaintingFolderTool  ( menu , plan  ) ;
  textTool    = new PaintingTextTool    ( menu , plan  ) ;
  textEdit    = new PaintingTextTool    ( menu , plan  ) ;
  audioTool   = new PaintingAudioTool   ( menu , plan  ) ;
  folderEdit  = new PaintingFolderEdit  ( menu , plan  ) ;
  ////////////////////////////////////////////////////////
  menu    -> addWidget                  ( encrypt      ) ;
  menu    -> addWidget                  ( decrypt      ) ;
  menu    -> addWidget                  ( depot        ) ;
  menu    -> addWidget                  ( settings     ) ;
  menu    -> addWidget                  ( srcPicture   ) ;
  menu    -> addWidget                  ( keyPicture   ) ;
  menu    -> addWidget                  ( getEncrypt   ) ;
  menu    -> addWidget                  ( getKeyPic    ) ;
  menu    -> addWidget                  ( viewImages   ) ;
  menu    -> addWidget                  ( viewEncrypt  ) ;
  menu    -> addWidget                  ( viewKeys     ) ;
  menu    -> addWidget                  ( fileTool     ) ;
  menu    -> addWidget                  ( folderTool   ) ;
  menu    -> addWidget                  ( textTool     ) ;
  menu    -> addWidget                  ( textEdit     ) ;
  menu    -> addWidget                  ( audioTool    ) ;
  menu    -> addWidget                  ( folderEdit   ) ;
  ////////////////////////////////////////////////////////
  viewImages  -> canPick = false                         ;
  viewEncrypt -> canPick = false                         ;
  viewKeys    -> canPick = false                         ;
  ////////////////////////////////////////////////////////
  ftp      = new FtpControl             ( stack , plan ) ;
  stack   -> addWidget                  ( ftp          ) ;
  ftp     -> startup                    (              ) ;
  ftp     -> setBack                    ( false        ) ;
  ////////////////////////////////////////////////////////
  label    = new QLabel                 ( header       ) ;
  header  -> addWidget                  ( label        ) ;
  label   -> setStyleSheet                               (
               "QLabel{background:rgb(255,255,255);}"  ) ;
  ////////////////////////////////////////////////////////
  progress = new QProgressBar           ( header       ) ;
  header  -> addWidget                  ( progress     ) ;
  ////////////////////////////////////////////////////////
  folderList = new PaintingFolderList   ( header       ) ;
  header  -> addWidget                  ( folderList   ) ;
  ////////////////////////////////////////////////////////
  fontconf = new FontConfigurator ( stack , plan       ) ;
  fontconf->addItem(Fonts::Default    ,tr("Default"   )) ;
  fontconf->addItem(Fonts::Menu       ,tr("Menu"      )) ;
  fontconf->addItem(Fonts::Status     ,tr("Status"    )) ;
  fontconf->addItem(Fonts::Message    ,tr("Message"   )) ;
  fontconf->addItem(Fonts::ComboBox   ,tr("Drop items")) ;
  fontconf->addItem(Fonts::TreeView   ,tr("Text items")) ;
  fontconf->addItem(Fonts::ListView   ,tr("Icon text" )) ;
  fontconf->addItem(Fonts::TableView  ,tr("Table"     )) ;
  fontconf->addItem(Fonts::Label      ,tr("Label"     )) ;
  fontconf->addItem(Fonts::CheckBox   ,tr("CheckBox"  )) ;
  fontconf->addItem(Fonts::Progress   ,tr("Progress"  )) ;
  fontconf->addItem(Fonts::Button     ,tr("Button"    )) ;
  fontconf->addItem(Fonts::Spin       ,tr("Spin"      )) ;
  stack   ->addWidget(fontconf)                          ;
  fontconf->startup()                                    ;
  fontconf->ItemChanged(0)                               ;
  ////////////////////////////////////////////////////////
  screenconf = new ScreenConfigurator ( stack , plan   ) ;
  stack        -> addWidget  ( screenconf )              ;
  screenconf   -> setMeasure ( false      )              ;
  ////////////////////////////////////////////////////////
  pickLanguage  = new TreeWidget      ( stack , plan   ) ;
  stack        -> addWidget           ( pickLanguage   ) ;
  pickLanguage -> setColumnCount      ( 1              ) ;
  pickLanguage -> setHeaderHidden     ( true           ) ;
  pickLanguage -> setRootIsDecorated  ( false          ) ;
  pickLanguage -> setAlternatingRowColors ( true       ) ;
  nConnect ( pickLanguage , SIGNAL(itemClicked    (QTreeWidgetItem*,int))   ,
             this         , SLOT  (languageClicked(QTreeWidgetItem*,int)) ) ;
  ////////////////////////////////////////////////////////
  encryptReport = new TextEdit        ( stack , plan   ) ;
  stack        -> addWidget           ( encryptReport  ) ;
  encryptReport-> setReadOnly         ( true           ) ;
  ////////////////////////////////////////////////////////
  decryptReport = new TextEdit        ( stack , plan   ) ;
  stack        -> addWidget           ( decryptReport  ) ;
  decryptReport-> setReadOnly         ( true           ) ;
  ////////////////////////////////////////////////////////
  depotReport   = new TextEdit        ( stack , plan   ) ;
  stack        -> addWidget           ( depotReport    ) ;
  depotReport  -> setReadOnly         ( true           ) ;
  ////////////////////////////////////////////////////////
  plainText     = new TextEdit        ( stack , plan   ) ;
  stack        -> addWidget           ( plainText      ) ;
  ////////////////////////////////////////////////////////
  line          = new LineEdit        ( header , plan  ) ;
  header       -> addWidget           ( line           ) ;
  ////////////////////////////////////////////////////////
  lineRename    = new LineEdit        ( header , plan  ) ;
  header       -> addWidget           ( lineRename     ) ;
  ////////////////////////////////////////////////////////
  lineMove      = new LineEdit        ( header , plan  ) ;
  header       -> addWidget           ( lineMove       ) ;
  ////////////////////////////////////////////////////////
  lineDirectory = new LineEdit        ( header , plan  ) ;
  header       -> addWidget           ( lineDirectory  ) ;
  ////////////////////////////////////////////////////////
  archive       = new ArchiveList     ( stack , plan   ) ;
  stack        -> addWidget           ( archive        ) ;
  ////////////////////////////////////////////////////////
  pickArchive   = new ArchivePick     ( stack , plan   ) ;
  stack        -> addWidget           ( pickArchive    ) ;
  ////////////////////////////////////////////////////////
  help          = new WebBrowser      ( stack , plan   ) ;
  stack        -> addWidget           ( help           ) ;
  ////////////////////////////////////////////////////////
  mdi        = new MdiArea            ( stack , plan   ) ;
  stack     -> addWidget              ( mdi            ) ;
  ////////////////////////////////////////////////////////
  nConnect ( encrypt    , SIGNAL(Back      ())           ,
             this       , SIGNAL(Back      ())         ) ;
  nConnect ( decrypt    , SIGNAL(Back      ())           ,
             this       , SIGNAL(Back      ())         ) ;
  nConnect ( depot      , SIGNAL(Back      ())           ,
             this       , SIGNAL(Back      ())         ) ;
  nConnect ( settings   , SIGNAL(Back      ())           ,
             this       , SIGNAL(Back      ())         ) ;
  nConnect ( srcPicture , SIGNAL(Back      ())           ,
             this       , SLOT  (Encryption())         ) ;
  nConnect ( keyPicture , SIGNAL(Back      ())           ,
             this       , SLOT  (Encryption())         ) ;
  nConnect ( getEncrypt , SIGNAL(Back      ())           ,
             this       , SLOT  (Decryption())         ) ;
  nConnect ( getKeyPic  , SIGNAL(Back      ())           ,
             this       , SLOT  (Decryption())         ) ;
  nConnect ( viewImages , SIGNAL(Back      ())           ,
             this       , SLOT  (Depot     ())         ) ;
  nConnect ( viewEncrypt, SIGNAL(Back      ())           ,
             this       , SLOT  (Depot     ())         ) ;
  nConnect ( viewKeys   , SIGNAL(Back      ())           ,
             this       , SLOT  (Depot     ())         ) ;
  nConnect ( fileTool   , SIGNAL(Back      ())           ,
             this       , SLOT  (Encryption())         ) ;
  nConnect ( folderTool , SIGNAL(Back      ())           ,
             this       , SLOT  (MakeFile  ())         ) ;
  nConnect ( textTool   , SIGNAL(Back      ())           ,
             this       , SLOT  (AddFile   ())         ) ;
  nConnect ( textEdit   , SIGNAL(Back      ())           ,
             this       , SLOT  (BackEdit  ())         ) ;
  nConnect ( audioTool  , SIGNAL(Back      ())           ,
             this       , SLOT  (AddFile   ())         ) ;
  nConnect ( folderEdit , SIGNAL(Back      ())           ,
             this       , SLOT  (FolderMenu())         ) ;
  ////////////////////////////////////////////////////////
  nConnect ( settings , SIGNAL(Ftp           ())         ,
             this     , SLOT  (Sharing       ())       ) ;
  nConnect ( settings , SIGNAL(Language      ())         ,
             this     , SLOT  (Language      ())       ) ;
  nConnect ( settings , SIGNAL(Fonts         ())         ,
             this     , SLOT  (Fonts         ())       ) ;
  nConnect ( settings , SIGNAL(Display       ())         ,
             this     , SLOT  (Display       ())       ) ;
  nConnect ( settings , SIGNAL(Help          ())         ,
             this     , SLOT  (Help          ())       ) ;
  ////////////////////////////////////////////////////////
  nConnect ( encrypt  , SIGNAL(Files         ())         ,
             this     , SLOT  (MakeFile      ())       ) ;
  nConnect ( encrypt  , SIGNAL(Picture       ())         ,
             this     , SLOT  (GetPicture    ())       ) ;
  nConnect ( encrypt  , SIGNAL(Key           ())         ,
             this     , SLOT  (PickKey       ())       ) ;
  nConnect ( encrypt  , SIGNAL(Encrypt       ())         ,
             this     , SLOT  (DoEncrypt     ())       ) ;
  ////////////////////////////////////////////////////////
  nConnect ( decrypt  , SIGNAL(Picture       ())         ,
             this     , SLOT  (DataPicture   ())       ) ;
  nConnect ( decrypt  , SIGNAL(Key           ())         ,
             this     , SLOT  (DataKey       ())       ) ;
  nConnect ( decrypt  , SIGNAL(Decrypt       ())         ,
             this     , SLOT  (DoDecrypt     ())       ) ;
  ////////////////////////////////////////////////////////
  nConnect ( depot    , SIGNAL(List          ())         ,
             this     , SLOT  (DepotList     ())       ) ;
  nConnect ( depot    , SIGNAL(Pictures      ())         ,
             this     , SLOT  (DepotPictures ())       ) ;
  nConnect ( depot    , SIGNAL(Keys          ())         ,
             this     , SLOT  (DepotKeys     ())       ) ;
  nConnect ( depot    , SIGNAL(Encrypted     ())         ,
             this     , SLOT  (DepotEncrypted())       ) ;
  nConnect ( depot    , SIGNAL(Ftp           ())         ,
             this     , SLOT  (DepotFtp      ())       ) ;
  ////////////////////////////////////////////////////////
  pickPicture = new PickPicture ( stack , plan )         ;
  stack      -> addWidget       ( pickPicture  )         ;
  nConnect ( pickPicture,SIGNAL(FileSelected(QString))   ,
             this       ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickPicture,SIGNAL(FileSelected(QString))   ,
             srcPicture ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickPicture,SIGNAL(Full      (int,bool))    ,
             srcPicture ,SLOT  (Full      (int,bool))  ) ;
  nConnect ( pickPicture,SIGNAL(Empty     ())            ,
             srcPicture ,SLOT  (Empty     ())          ) ;
  nConnect ( srcPicture ,SIGNAL(Previous  ())            ,
             pickPicture,SLOT  (Previous  ())          ) ;
  nConnect ( srcPicture ,SIGNAL(Next      ())            ,
             pickPicture,SLOT  (Next      ())          ) ;
  nConnect ( srcPicture ,SIGNAL(Pick      ())            ,
             this       ,SLOT  (ObtainPic ())          ) ;
  nConnect ( srcPicture ,SIGNAL(View      ())            ,
             this       ,SLOT  (ViewPicture())         ) ;
  nConnect ( srcPicture ,SIGNAL(Import    ())            ,
             this       ,SLOT  (ImportPicture())       ) ;
  nConnect ( pickPicture,SIGNAL(FileSelected(QString))   ,
             keyPicture ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickPicture,SIGNAL(Full      (int,bool))    ,
             keyPicture ,SLOT  (Full      (int,bool))  ) ;
  nConnect ( pickPicture,SIGNAL(Empty     ())            ,
             keyPicture ,SLOT  (Empty     ())          ) ;
  nConnect ( keyPicture ,SIGNAL(Previous  ())            ,
             pickPicture,SLOT  (Previous  ())          ) ;
  nConnect ( keyPicture ,SIGNAL(Next      ())            ,
             pickPicture,SLOT  (Next      ())          ) ;
  nConnect ( keyPicture ,SIGNAL(Pick      ())            ,
             this       ,SLOT  (ObtainKey ())          ) ;
  nConnect ( keyPicture ,SIGNAL(View      ())            ,
             this       ,SLOT  (ViewPicture())         ) ;
  nConnect ( keyPicture ,SIGNAL(Import    ())            ,
             this       ,SLOT  (ImportKey ())          ) ;
  nConnect ( pickPicture,SIGNAL(FileSelected(QString))   ,
             viewImages ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickPicture,SIGNAL(Full      (int,bool))    ,
             viewImages ,SLOT  (Full      (int,bool))  ) ;
  nConnect ( pickPicture,SIGNAL(Empty     ())            ,
             viewImages ,SLOT  (Empty     ())          ) ;
  nConnect ( viewImages ,SIGNAL(Previous  ())            ,
             pickPicture,SLOT  (Previous  ())          ) ;
  nConnect ( viewImages ,SIGNAL(Next      ())            ,
             pickPicture,SLOT  (Next      ())          ) ;
  nConnect ( viewImages ,SIGNAL(View      ())            ,
             this       ,SLOT  (ViewDepot ())          ) ;
  nConnect ( viewImages ,SIGNAL(Import       ())         ,
             this       ,SLOT  (ImportPicture())       ) ;
  ////////////////////////////////////////////////////////
  pickEncrypt = new PickPicture ( stack , plan )         ;
  stack      -> addWidget       ( pickEncrypt  )         ;
  nConnect ( pickEncrypt,SIGNAL(FileSelected(QString))   ,
             this       ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickEncrypt,SIGNAL(FileSelected(QString))   ,
             getEncrypt ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickEncrypt,SIGNAL(Full      (int,bool))    ,
             getEncrypt ,SLOT  (Full      (int,bool))  ) ;
  nConnect ( pickEncrypt,SIGNAL(Empty     ())            ,
             getEncrypt ,SLOT  (Empty     ())          ) ;
  nConnect ( getEncrypt ,SIGNAL(Previous  ())            ,
             pickEncrypt,SLOT  (Previous  ())          ) ;
  nConnect ( getEncrypt ,SIGNAL(Next      ())            ,
             pickEncrypt,SLOT  (Next      ())          ) ;
  nConnect ( getEncrypt ,SIGNAL(Pick      ())            ,
             this       ,SLOT  (ObtainEncrypted())     ) ;
  nConnect ( getEncrypt ,SIGNAL(View      ())            ,
             this       ,SLOT  (ViewEncrypted())       ) ;
  nConnect ( getEncrypt ,SIGNAL(Import    ())            ,
             this       ,SLOT  (ImportEncrypted())     ) ;
  nConnect ( pickEncrypt,SIGNAL(FileSelected(QString))   ,
             viewEncrypt,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickEncrypt,SIGNAL(Full      (int,bool))    ,
             viewEncrypt,SLOT  (Full      (int,bool))  ) ;
  nConnect ( pickEncrypt,SIGNAL(Empty     ())            ,
             viewEncrypt,SLOT  (Empty     ())          ) ;
  nConnect ( viewEncrypt,SIGNAL(Previous  ())            ,
             pickEncrypt,SLOT  (Previous  ())          ) ;
  nConnect ( viewEncrypt,SIGNAL(Next      ())            ,
             pickEncrypt,SLOT  (Next      ())          ) ;
  nConnect ( viewEncrypt,SIGNAL(View      ())            ,
             this       ,SLOT  (ViewDepot ())       ) ;
  nConnect ( viewEncrypt,SIGNAL(Import    ())            ,
             this       ,SLOT  (ImportEncrypted())     ) ;
  ////////////////////////////////////////////////////////
  pickKey     = new PickPicture ( stack , plan )         ;
  stack      -> addWidget       ( pickKey      )         ;
  nConnect ( pickKey    ,SIGNAL(FileSelected(QString))   ,
             this       ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickKey    ,SIGNAL(FileSelected(QString))   ,
             getKeyPic  ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickKey    ,SIGNAL(Full      (int,bool))    ,
             getKeyPic  ,SLOT  (Full      (int,bool))  ) ;
  nConnect ( pickKey    ,SIGNAL(Empty     ())            ,
             getKeyPic  ,SLOT  (Empty     ())          ) ;
  nConnect ( getKeyPic  ,SIGNAL(Previous  ())            ,
             pickKey    ,SLOT  (Previous  ())          ) ;
  nConnect ( getKeyPic  ,SIGNAL(Next      ())            ,
             pickKey    ,SLOT  (Next      ())          ) ;
  nConnect ( getKeyPic  ,SIGNAL(Pick      ())            ,
             this       ,SLOT  (ObtainKeys())          ) ;
  nConnect ( getKeyPic  ,SIGNAL(View      ())            ,
             this       ,SLOT  (ViewKeys  ())          ) ;
  nConnect ( getKeyPic  ,SIGNAL(Import    ())            ,
             this       ,SLOT  (ImportKeys())          ) ;
  nConnect ( pickKey    ,SIGNAL(FileSelected(QString))   ,
             viewKeys   ,SLOT  (FileSelected(QString)) ) ;
  nConnect ( pickKey    ,SIGNAL(Full      (int,bool))    ,
             viewKeys   ,SLOT  (Full      (int,bool))  ) ;
  nConnect ( pickKey    ,SIGNAL(Empty     ())            ,
             viewKeys   ,SLOT  (Empty     ())          ) ;
  nConnect ( viewKeys   ,SIGNAL(Previous  ())            ,
             pickKey    ,SLOT  (Previous  ())          ) ;
  nConnect ( viewKeys   ,SIGNAL(Next      ())            ,
             pickKey    ,SLOT  (Next      ())          ) ;
  nConnect ( viewKeys   ,SIGNAL(View      ())            ,
             this       ,SLOT  (ViewDepot ())          ) ;
  nConnect ( viewKeys   ,SIGNAL(Import    ())            ,
             this       ,SLOT  (ImportKeys())          ) ;
  ////////////////////////////////////////////////////////
  nConnect ( fileTool   , SIGNAL(New          ())        ,
             this       , SLOT  (NewFile      ())      ) ;
  nConnect ( fileTool   , SIGNAL(Add          ())        ,
             this       , SLOT  (AddFile      ())      ) ;
  nConnect ( fileTool   , SIGNAL(Remove       ())        ,
             this       , SLOT  (RemoveFile   ())      ) ;
  nConnect ( fileTool   , SIGNAL(Packaging    ())        ,
             this       , SLOT  (CreatePackage())      ) ;
  ////////////////////////////////////////////////////////
  nConnect ( folderTool , SIGNAL(Join          ())       ,
             this       , SLOT  (FolderJoin    ())     ) ;
  nConnect ( folderTool , SIGNAL(Edit          ())       ,
             this       , SLOT  (FolderEdit    ())     ) ;
  nConnect ( folderTool , SIGNAL(Delete        ())       ,
             this       , SLOT  (FolderDelete  ())     ) ;
  nConnect ( folderTool , SIGNAL(Text          ())       ,
             this       , SLOT  (FolderText    ())     ) ;
  nConnect ( folderTool , SIGNAL(Recorder      ())       ,
             this       , SLOT  (FolderRecorder())     ) ;
  ////////////////////////////////////////////////////////
  nConnect ( folderList  , SIGNAL(CdUp     ())                 ,
             pickArchive , SLOT  (CdUp     ())               ) ;
  nConnect ( folderList  , SIGNAL(Directory(QString))          ,
             pickArchive , SLOT  (Directory(QString))        ) ;
  nConnect ( pickArchive , SIGNAL(Folders(bool,QStringList))   ,
             folderList  , SLOT  (Folders(bool,QStringList)) ) ;
  nConnect ( pickArchive , SIGNAL(Listing         ())          ,
             this        , SLOT  (FolderListing   ())        ) ;
  nConnect ( pickArchive , SIGNAL(Ready           ())          ,
             this        , SLOT  (FolderReady     ())        ) ;
  nConnect ( pickArchive , SIGNAL(selectionChanged())          ,
             this        , SLOT  (FolderSelected  ())        ) ;
  nConnect ( archive     , SIGNAL(selectionChanged())          ,
             this        , SLOT  (FileSelected    ())        ) ;
  ////////////////////////////////////////////////////////
  nConnect ( textTool    , SIGNAL(New       ())          ,
             this        , SLOT  (FolderText())        ) ;
  nConnect ( textTool    , SIGNAL(Save      ())          ,
             this        , SLOT  (SaveText  ())        ) ;
  ////////////////////////////////////////////////////////
  nConnect ( textEdit   , SIGNAL(New       ())           ,
             this       , SLOT  (NewEdit   ())         ) ;
  nConnect ( textEdit   , SIGNAL(Save      ())           ,
             this       , SLOT  (SaveEdit  ())         ) ;
  ////////////////////////////////////////////////////////
  nConnect ( lineRename    , SIGNAL(returnPressed  ())   ,
             this          , SLOT  (RenameAction   ()) ) ;
  nConnect ( lineMove      , SIGNAL(returnPressed  ())   ,
             this          , SLOT  (MoveAction     ()) ) ;
  nConnect ( lineDirectory , SIGNAL(returnPressed  ())   ,
             this          , SLOT  (DirectoryAction()) ) ;
  nConnect ( lineRename    , SIGNAL(editingFinished())   ,
             this          , SLOT  (FolderBack     ()) ) ;
  nConnect ( lineMove      , SIGNAL(editingFinished())   ,
             this          , SLOT  (FolderBack     ()) ) ;
  nConnect ( lineDirectory , SIGNAL(editingFinished())   ,
             this          , SLOT  (FolderBack     ()) ) ;
  ////////////////////////////////////////////////////////
  nConnect ( folderEdit , SIGNAL(Rename        ())       ,
             this       , SLOT  (FileRename    ())     ) ;
  nConnect ( folderEdit , SIGNAL(Move          ())       ,
             this       , SLOT  (FileMove      ())     ) ;
  nConnect ( folderEdit , SIGNAL(Directory     ())       ,
             this       , SLOT  (FileDirectory ())     ) ;
  nConnect ( folderEdit , SIGNAL(Edit          ())       ,
             this       , SLOT  (EditText      ())     ) ;
  nConnect ( folderEdit , SIGNAL(Ftp           ())       ,
             this       , SLOT  (FileFtp       ())     ) ;
  ////////////////////////////////////////////////////////
}

void N::PaintingSecretGui::BootupFtp(void)
{
  if ( ! plan  -> Booleans [ "Desktop" ] )   {
    if (ftp->AutoStartup()) ftp->begin(true) ;
  }                                          ;
}

void N::PaintingSecretGui::FileSelected(QString path)
{
  label -> setText ( path ) ;
}

void N::PaintingSecretGui::AndroidPathes(void)
{
  #define AFP(NX)  N::FtpSettings::addFolder(plan->Path("files/" NX),QString(NX),true) ; \
                   if (debug) qDebug ( plan->Path("files/" NX).toUtf8().constData() )
  AFP   ( "Documents"  ) ;
  AFP   ( "Download"   ) ;
  AFP   ( "Encryption" ) ;
  AFP   ( "Files"      ) ;
  AFP   ( "Images"     ) ;
  AFP   ( "Keys"       ) ;
  AFP   ( "Upload"     ) ;
  if (debug)             {
    AFP ( "Temp"       ) ;
    AFP ( "Sounds"     ) ;
    AFP ( "Users"      ) ;
  }                      ;
  #undef  AFP
}

void N::PaintingSecretGui::ApplePathes(void)
{
  #define AFP(NX)  N::FtpSettings::addFolder(plan->Path("Documents/" NX),QString(NX),true) ; \
                   if (debug) qDebug ( plan->Path("Documents/" NX).toUtf8().constData() )
  AFP   ( "Documents"  ) ;
  AFP   ( "Download"   ) ;
  AFP   ( "Encryption" ) ;
  AFP   ( "Files"      ) ;
  AFP   ( "Images"     ) ;
  AFP   ( "Keys"       ) ;
  AFP   ( "Upload"     ) ;
  if (debug)             {
    AFP   ( "Temp"     ) ;
    AFP ( "Sounds"     ) ;
    AFP ( "Users"      ) ;
  }                      ;
  #undef  AFP
}

void N::PaintingSecretGui::InstallPathes(void)
{
  if ( plan  -> Booleans [ "Desktop" ] )                          {
    pickPicture -> setRoot ( plan->Path("Images"  ) )             ;
    pickEncrypt -> setRoot ( plan->Path("Download") )             ;
    pickKey     -> setRoot ( plan->Path("Upload"  ) )             ;
    archive     -> setRoot ( plan->Path("Files"   ) )             ;
    pickArchive -> setRoot ( plan->Path("Files"   ) )             ;
  } else                                                          {
    #ifdef Q_OS_ANDROID
    pickPicture -> setRoot ( plan->Path("files/Images"    )     ) ;
    pickEncrypt -> setRoot ( plan->Path("files/Encryption")     ) ;
    pickKey     -> setRoot ( plan->Path("files/Keys"      )     ) ;
    archive     -> setRoot ( plan->Path("files/Documents" )     ) ;
    pickArchive -> setRoot ( plan->Path("files/Documents" )     ) ;
    #endif
    #ifdef Q_OS_IOS
    pickPicture -> setRoot ( plan->Path("Documents/Images"    ) ) ;
    pickEncrypt -> setRoot ( plan->Path("Documents/Encryption") ) ;
    pickKey     -> setRoot ( plan->Path("Documents/Keys"      ) ) ;
    archive     -> setRoot ( plan->Path("Documents/Documents" ) ) ;
    pickArchive -> setRoot ( plan->Path("Documents/Documents" ) ) ;
    #endif
  }                                                               ;
}

void N::PaintingSecretGui::relocation(void)
{
}

QString N::PaintingSecretGui::LanguagePath(QString filename)
{
  QString    LC                                                   ;
  LidTo(plan->LanguageId,LC)                                      ;
  QString p = QString("Translations/%1/%2").arg(LC).arg(filename) ;
  return Root.absoluteFilePath(p)                                 ;
}

void N::PaintingSecretGui::Encryption(void)
{
  header -> setCurrentWidget ( label                             ) ;
  stack  -> setCurrentWidget ( encryptReport                     ) ;
  menu   -> setCurrentWidget ( encrypt                           ) ;
  label  -> setText          ( tr("Encrypt data into a picture") ) ;
  //////////////////////////////////////////////////////////////////
  QString p = LanguagePath("steganoencrypt.html")                  ;
  QFileInfo F(p)                                                   ;
  if (!F.exists()) return                                          ;
  QByteArray Body                                                  ;
  File::toByteArray ( p , Body )                                   ;
  encryptReport      -> clear         (                         )  ;
  encryptReport      -> append        ( QString::fromUtf8(Body) )  ;
  encryptReport      -> verticalScrollBar ( ) -> setValue ( 0   )  ;
}

void N::PaintingSecretGui::Decryption(void)
{
  header -> setCurrentWidget ( label                           ) ;
  stack  -> setCurrentWidget ( decryptReport                   ) ;
  menu   -> setCurrentWidget ( decrypt                         ) ;
  label  -> setText          ( tr("Decrypt data from picture") ) ;
  ////////////////////////////////////////////////////////////////
  QString p = LanguagePath("steganodecrypt.html")                ;
  QFileInfo F(p)                                                 ;
  if (!F.exists()) return                                        ;
  QByteArray Body                                                ;
  File::toByteArray ( p , Body )                                 ;
  decryptReport    -> clear         (                         )  ;
  decryptReport    -> append        ( QString::fromUtf8(Body) )  ;
  decryptReport    -> verticalScrollBar ( ) -> setValue ( 0   )  ;
}

void N::PaintingSecretGui::Depot(void)
{
  header -> setCurrentWidget ( label                        ) ;
  stack  -> setCurrentWidget ( depotReport                  ) ;
  menu   -> setCurrentWidget ( depot                        ) ;
  label  -> setText          ( tr("Painting secrets depot") ) ;
  /////////////////////////////////////////////////////////////
  QString p = LanguagePath("steganodepot.html")               ;
  QFileInfo F(p)                                              ;
  if (!F.exists()) return                                     ;
  QByteArray Body                                             ;
  File::toByteArray ( p , Body )                              ;
  depotReport -> clear       (                              ) ;
  depotReport -> append      ( QString::fromUtf8(Body)      ) ;
  depotReport -> verticalScrollBar ( ) -> setValue ( 0 )      ;
}

void N::PaintingSecretGui::Settings(void)
{
  header -> setCurrentWidget ( label                           ) ;
  stack  -> setCurrentWidget ( ftp                             ) ;
  menu   -> setCurrentWidget ( settings                        ) ;
  label  -> setText          ( tr("Painting secrets settings") ) ;
}

void N::PaintingSecretGui::Sharing(void)
{
  header -> setCurrentWidget ( label                    )                      ;
  stack  -> setCurrentWidget ( ftp                      )                      ;
  menu   -> setCurrentWidget ( settings                 )                      ;
  label  -> setText          ( tr("Ftp sharing server") )                      ;
  Alert                      ( Error                    )                      ;
  //////////////////////////////////////////////////////////////////////////////
  QHostInfo info                                                               ;
  QString   qstr = info.localHostName()                                        ;
  QHostInfo info2 ( QHostInfo ::fromName ( qstr ) )                            ;
  QList<QHostAddress> list                                                     ;
  bool                found = false                                            ;
  list = info2.addresses()                                                     ;
  if (list.count()<=0) list = QNetworkInterface::allAddresses()                ;
  //////////////////////////////////////////////////////////////////////////////
  for (int i=0;!found && i<list.count();i++)                                   {
    if (!list[i].isLoopback())                                                 {
      if (list[i].protocol() == QAbstractSocket::IPv4Protocol)                 {
        label -> setText ( tr("Local address : %1") .arg(list[i].toString()) ) ;
        found  = true                                                          ;
      }                                                                        ;
    }                                                                          ;
  }                                                                            ;
}

void N::PaintingSecretGui::Fonts(void)
{
  header -> setCurrentWidget ( label             ) ;
  stack  -> setCurrentWidget ( fontconf          ) ;
  menu   -> setCurrentWidget ( settings          ) ;
  label  -> setText          ( tr("Setup fonts") ) ;
  Alert                      ( Error             ) ;
}

void N::PaintingSecretGui::Language(void)
{
  header -> setCurrentWidget ( label                ) ;
  stack  -> setCurrentWidget ( pickLanguage         ) ;
  menu   -> setCurrentWidget ( settings             ) ;
  ListLanguage               (                      ) ;
  Alert                      ( Error                ) ;
}

void N::PaintingSecretGui::languageClicked(QTreeWidgetItem * item,int column)
{ Q_UNUSED ( column )                                                       ;
  for (int i=0;i<pickLanguage->topLevelItemCount();i++)                     {
    QTreeWidgetItem * it = pickLanguage->topLevelItem(i)                    ;
    if (it==item)                                                           {
      QString s = it->text(0)                                               ;
      QString m                                                             ;
      int l  = item->data(0,Qt::UserRole).toInt()                           ;
      it    -> setIcon ( 0 , QIcon(":/images/yes.png" ) )                   ;
      it    -> setData ( 0 , Qt::UserRole+1 , 1         )                   ;
      plan  -> settings . beginGroup ( "System" )                           ;
      plan  -> settings . setValue   ( "Language" , l   )                   ;
      plan  -> settings . endGroup   (          )                           ;
      m = tr("Language change to %1 will take effect after restart").arg(s) ;
      label -> setText ( m )                                                ;
    } else                                                                  {
      it -> setIcon ( 0 , QIcon(":/icons/empty.png")  )                     ;
      it -> setData ( 0 , Qt::UserRole+1 , 0          )                     ;
    }                                                                       ;
  }                                                                         ;
}

void N::PaintingSecretGui::ListLanguage(void)
{
  int LID                                                          ;
  menu -> setEnabled ( false                          )            ;
  pickLanguage -> clear (                             )            ;
  ForLanguage        ( LID , plan->languages.Supports )            ;
    QString LC                                                     ;
    if (LidTo(LID,LC) || LID==1819)                                {
      QString p = QString("Translations/%1/%2").arg(LC).arg(QM)    ;
      p = Root.absoluteFilePath(p)                                 ;
      QFileInfo F(p)                                               ;
      if (F.exists() || LID==1819)                                 {
        QString n = (plan->languages)[LID]                         ;
        NewTreeWidgetItem ( IT )                                   ;
        IT           -> setData         ( 0 , Qt::UserRole , LID ) ;
        IT           -> setText         ( 0 , n                  ) ;
        if (LID==plan->LanguageId)                                 {
          IT         -> setIcon ( 0 , QIcon(":/images/yes.png"  )) ;
          IT         -> setData         ( 0 , Qt::UserRole+1 , 1 ) ;
        } else                                                     {
          IT         -> setIcon ( 0 , QIcon(":/icons/empty.png" )) ;
          IT         -> setData         ( 0 , Qt::UserRole+1 , 0 ) ;
        }                                                          ;
        pickLanguage -> addTopLevelItem ( IT                     ) ;
      }                                                            ;
    }                                                              ;
    if (debug)                                                     {
      QString nn = (plan->languages)[LID]                          ;
      qDebug ( nn.toUtf8().constData() )                           ;
    }                                                              ;
  EndLanguage        ( LID , plan->languages.Supports )            ;
  QString l = (plan->languages)[plan->LanguageId]                  ;
  QString m                                                        ;
  m = tr("Setup language, current language is %1").arg(l)          ;
  label -> setText    ( m    )                                     ;
  menu  -> setEnabled ( true )                                     ;
}

void N::PaintingSecretGui::Display(void)
{
  header -> setCurrentWidget ( label                    ) ;
  stack  -> setCurrentWidget ( screenconf               ) ;
  menu   -> setCurrentWidget ( settings                 ) ;
  label  -> setText          ( tr("Setup display size") ) ;
  Alert                      ( Error                    ) ;
}

void N::PaintingSecretGui::Help(void)
{
  emit Manual ( ) ;
}

void N::PaintingSecretGui::MakeFile(void)
{
  if (packaging<=0) packaging = ObtainUuid (             )         ;
  header -> setCurrentWidget ( label                     )         ;
  stack  -> setCurrentWidget ( archive                   )         ;
  menu   -> setCurrentWidget ( fileTool                  )         ;
  QString m                                                        ;
  m = tr("Create data package, signature is `%1`.").arg(packaging) ;
  label  -> setText          ( m                         )         ;
  fileTool -> setDeletion    ( archive->Selections       () > 0 )  ;
  fileTool -> setPackaging   ( archive->topLevelItemCount() > 0 )  ;
  Alert                      ( Error                     )         ;
}

SUID N::PaintingSecretGui::ObtainUuid(void)
{
  SUID u = 0                                     ;
  SqlConnection SC(plan->sql)                    ;
  if (SC.open("PaintingSecretGui","ObtainUuid")) {
    u = SC.Unique (PlanTable(MajorUuid),"uuid")  ;
    SC.close()                                   ;
  }                                              ;
  SC.remove()                                    ;
  return u                                       ;
}

void N::PaintingSecretGui::NewFile(void)
{
  if (packaging>0)                                                  {
    QString t = QString("Temp/%1.tar.xz").arg(packaging)            ;
    t = Root.absoluteFilePath(t)                                    ;
    QFile::remove(t)                                                ;
  }                                                                 ;
  packaging = ObtainUuid       (                         )          ;
  archive  -> clear            (                         )          ;
  header   -> setCurrentWidget ( label                   )          ;
  stack    -> setCurrentWidget ( archive                 )          ;
  menu     -> setCurrentWidget ( fileTool                )          ;
  QString m                                                         ;
  m = tr("Create data package, signature is `%1`.").arg(packaging ) ;
  label    -> setText          ( m                                ) ;
  fileTool -> setDeletion      ( archive->Selections       () > 0 ) ;
  fileTool -> setPackaging     ( archive->topLevelItemCount() > 0 ) ;
  Alert                        ( Error                            ) ;
}

void N::PaintingSecretGui::AddFile(void)
{
  header      -> setCurrentWidget ( folderList  ) ;
  stack       -> setCurrentWidget ( pickArchive ) ;
  menu        -> setCurrentWidget ( folderTool  ) ;
  plan        -> processEvents    (             ) ;
  pickArchive -> List             (             ) ;
}

void N::PaintingSecretGui::RemoveFile(void)
{
  archive  -> Delete       (                                  ) ;
  fileTool -> setDeletion  ( archive->Selections       () > 0 ) ;
  fileTool -> setPackaging ( archive->topLevelItemCount() > 0 ) ;
}

void N::PaintingSecretGui::CreatePackage(void)
{
  XDEBUG ( "N::PaintingSecretGui::CreatePackage" ) ;
  //////////////////////////////////////////
  if (packaging<=0) return                 ;
  //////////////////////////////////////////
  header -> setCurrentWidget ( label    )  ;
  stack  -> setCurrentWidget ( archive  )  ;
  menu   -> setCurrentWidget ( fileTool )  ;
  //////////////////////////////////////////
  QStringList L = archive -> PickFiles( )  ;
  if (L.count()<=0) return                 ;
  //////////////////////////////////////////
  QString m                                ;
  m = tr("Compress %1") . arg( packaging ) ;
  label  -> setText          ( m         ) ;
  stack  -> setEnabled       ( false     ) ;
  menu   -> setEnabled       ( false     ) ;
  plan   -> processEvents    (           ) ;
  //////////////////////////////////////////
  XDEBUG ( "N::PaintingSecretGui::CreatePackage@Bale" ) ;
  //////////////////////////////////////////
  QString   XZ                             ;
  VirtualIO IO                             ;
  XZ = QString("%1.tar.xz").arg(packaging) ;
  XZ = QString("Temp/%1"  ).arg(XZ       ) ;
  XZ = Root.absoluteFilePath   (XZ       ) ;
  IO . setDirectory  ( archive -> Path() ) ;
  IO . setFile       ( File::Xz          ) ;
  IO . setVIO        ( VirtualDisk::Tar  ) ;
  IO . append        ( L                 ) ;
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  qDebug ( "N::PaintingSecretGui::CreatePackage@IO.append" ) ;
  #endif
  IO . Bale          ( XZ                ) ;
  //////////////////////////////////////////
  XDEBUG ( "N::PaintingSecretGui::CreatePackage@Display" ) ;
  //////////////////////////////////////////
  QFileInfo F(XZ)                          ;
  m = tr("Compressed data size is %1").arg(F.size()) ;
  label  -> setText          ( m         ) ;
  //////////////////////////////////////////
  plan   -> processEvents    (           ) ;
  stack  -> setEnabled       ( true      ) ;
  menu   -> setEnabled       ( true      ) ;
  plan   -> processEvents    (           ) ;
  //////////////////////////////////////////
  Alert                      ( Error     ) ;
}

void N::PaintingSecretGui::FileSelected(void)
{
  fileTool -> setDeletion  ( archive->Selections       () > 0 ) ;
  fileTool -> setPackaging ( archive->topLevelItemCount() > 0 ) ;
}

void N::PaintingSecretGui::FolderJoin(void)
{
  QStringList L = pickArchive -> PickFiles ( )                      ;
  if (L.count()<=0) return                                          ;
  header   -> setCurrentWidget ( label                            ) ;
  stack    -> setCurrentWidget ( archive                          ) ;
  menu     -> setCurrentWidget ( fileTool                         ) ;
  plan     -> processEvents    (                                  ) ;
  archive  -> Append           ( L                                ) ;
  plan     -> processEvents    (                                  ) ;
  fileTool -> setDeletion      ( archive->Selections       () > 0 ) ;
  fileTool -> setPackaging     ( archive->topLevelItemCount() > 0 ) ;
}

void N::PaintingSecretGui::FolderEdit(void)
{
  menu -> setCurrentWidget ( folderEdit ) ;
  Alert                    ( Click      ) ;
}

void N::PaintingSecretGui::FolderMenu(void)
{
  menu -> setCurrentWidget ( folderTool ) ;
  Alert                    ( Click      ) ;
}

void N::PaintingSecretGui::DeletePath(QDir & root,QStringList files)
{
  QString S                                  ;
  foreach (S,files)                          {
    QFileInfo F ( S )                        ;
    if (F.isDir())                           {
      QDir          D ( S )                  ;
      QFileInfoList L                        ;
      QStringList   M                        ;
      QString       p = S                    ;
      p = root.relativeFilePath(p)           ;
      L = D.entryInfoList                    (
            QDir::Dirs                       |
            QDir::Files                      |
            QDir::NoDotAndDotDot             |
            QDir::NoSymLinks               ) ;
      for (int i=0;i<L.count();i++)          {
        M << L[i].absoluteFilePath()         ;
      }                                      ;
      DeletePath    ( root , M )             ;
      label->setText(tr("Delete %1").arg(p)) ;
      root . rmpath ( S        )             ;
    } else
    if (F.isFile())                          {
      QString p = S                          ;
      p = root.relativeFilePath(p)           ;
      label->setText(tr("Delete %1").arg(p)) ;
      QFile::remove(S)                       ;
    }                                        ;
    plan -> processEvents ( )                ;
  }                                          ;
}

void N::PaintingSecretGui::FolderDelete(void)
{
  QStringList L = pickArchive -> PickFiles (    ) ;
  if (L.count()<=0) return                        ;
  folderTool  -> setEnabled        ( false      ) ;
  header      -> setCurrentWidget  ( label      ) ;
  plan        -> processEvents     (            ) ;
  QDir r       = pickArchive->Path (            ) ;
  DeletePath                       ( r , L      ) ;
  header      -> setCurrentWidget  ( folderList ) ;
  folderTool  -> setEnabled        ( true       ) ;
  plan        -> processEvents     (            ) ;
  pickArchive -> List              (            ) ;
}

void N::PaintingSecretGui::FolderText(void)
{
  emit NewText ( pickArchive -> Path() , pickArchive -> CurrentPath() ) ;
  #ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  plainText -> clear            (                          ) ;
  header    -> setCurrentWidget ( line                     ) ;
  stack     -> setCurrentWidget ( plainText                ) ;
  menu      -> setCurrentWidget ( textTool                 ) ;
  label     -> setText          ( tr("Plain text editor" ) ) ;
  ////////////////////////////////////////////////////////////
  bool    e = false                                          ;
  QDir    r = pickArchive -> Path        (                 ) ;
  QDir    c = pickArchive -> CurrentPath (                 ) ;
  QString f = tr("Noname")                                   ;
  QString t                                                  ;
  int     i = 1                                              ;
  do                                                         {
    t = QString("%1-%2.txt").arg(f).arg(i)                   ;
    i++                                                      ;
    t = c.absoluteFilePath(t)                                ;
    QFileInfo F(t)                                           ;
    if (!F.exists())                                         {
      t = r.relativeFilePath(t)                              ;
      e = true                                               ;
    }                                                        ;
  } while (!e)                                               ;
  line   -> blockSignals ( true                            ) ;
  line   -> setText      ( t                               ) ;
  line   -> blockSignals ( false                           ) ;
  ////////////////////////////////////////////////////////////
  Alert                  ( Error                           ) ;
  #endif
}

void N::PaintingSecretGui::SaveText(void)
{
  QString note = line->text()                    ;
  if (note.length()<=0) return                   ;
  QDir    r    = pickArchive -> Path(      )     ;
  QString file = r.absoluteFilePath ( note )     ;
  QString head = r.absoluteFilePath ( ""   )     ;
  if (!file.contains(head)) return               ;
  QString    text = plainText -> toPlainText ( ) ;
  QByteArray body = text . toUtf8 ( )            ;
  QFileInfo  fdir ( file                    )    ;
  r . mkpath      ( fdir . absolutePath ( ) )    ;
  File :: toFile  ( file , body             )    ;
  AddFile ( )                                    ;
}

void N::PaintingSecretGui::FolderRecorder(void)
{
  QString path = pickArchive->CurrentPath().absoluteFilePath("") ;
  emit Recording ( path )                                        ;
}

void N::PaintingSecretGui::FolderListing(void)
{
  folderList -> setEnabled ( false ) ;
  folderTool -> setEnabled ( false ) ;
}

void N::PaintingSecretGui::FolderReady(void)
{
  folderList -> setEnabled ( true  ) ;
  folderTool -> setEnabled ( true  ) ;
  FolderSelected           (       ) ;
}

void N::PaintingSecretGui::FolderSelected(void)
{
  QTreeWidgetItem * item = pickArchive->currentItem ( )   ;
  bool isText = false                                     ;
  if (NotNull(item))                                      {
    int t = item->data(1,Qt::UserRole).toInt()            ;
    if (t==0)                                             {
      QFileInfo F(item->text(0))                          ;
      QString   S = F.suffix()                            ;
      S = S.toLower()                                     ;
      isText = ( S == "txt" )                             ;
    }                                                     ;
  }                                                       ;
  folderTool -> setSelected ( pickArchive->Selections() ) ;
  folderEdit -> setSelected ( pickArchive->Selections() ) ;
  folderEdit -> setEdit     ( isText                    ) ;
}

void N::PaintingSecretGui::GetPicture(void)
{
  header -> setCurrentWidget ( label                             ) ;
  stack  -> setCurrentWidget ( pickPicture                       ) ;
  menu   -> setCurrentWidget ( srcPicture                        ) ;
  label  -> setText          ( tr("Pick picture for encryption") ) ;
  Alert                      ( Error                             ) ;
  srcPicture -> setEnabled   ( false                             ) ;
  plan   -> processEvents    (                                   ) ;
  pickPicture -> Index = 0                                         ;
  pickPicture -> Refresh     (                                   ) ;
  srcPicture  -> setEnabled  ( true                              ) ;
}

void N::PaintingSecretGui::PickKey(void)
{
  header -> setCurrentWidget ( label                       ) ;
  stack  -> setCurrentWidget ( pickPicture                 ) ;
  menu   -> setCurrentWidget ( keyPicture                  ) ;
  label  -> setText          ( tr("Pick a picture as key") ) ;
  Alert                      ( Error                       ) ;
  keyPicture -> setEnabled   ( false                       ) ;
  plan   -> processEvents    (                             ) ;
  pickPicture -> Index = 0                                   ;
  pickPicture -> Refresh     (                             ) ;
  keyPicture  -> setEnabled  ( true                        ) ;
}

void N::PaintingSecretGui::DoEncrypt(void)
{
  header -> setCurrentWidget ( label                           ) ;
  stack  -> setCurrentWidget ( encryptReport                   ) ;
  menu   -> setCurrentWidget ( encrypt                         ) ;
  menu   -> setEnabled       ( false                           ) ;
  ////////////////////////////////////////////////////////////////
  QString m                                                      ;
  QString rp                                                     ;
  m = tr("Creating steganographic picture `%1`.").arg(packaging) ;
  label  -> setText          ( m                               ) ;
  ////////////////////////////////////////////////////////////////
  encryptReport -> clear     (                                 ) ;
  plan -> processEvents      (                                 ) ;
  Alert                      ( Click                           ) ;
  ////////////////////////////////////////////////////////////////
  bool       hasData = false                                     ;
  QByteArray XzData                                              ;
  QByteArray PackData                                            ;
  QByteArray KeyData                                             ;
  QString    XZ                                                  ;
  QImage     SrcImage                                            ;
  QImage     KeyImage                                            ;
  ////////////////////////////////////////////////////////////////
  if (packaging>0)                                               {
    XZ = QString("Temp/%1.tar.xz").arg(packaging)                ;
    XZ = Root.absoluteFilePath ( XZ )                            ;
    QFileInfo F ( XZ )                                           ;
    if (F.exists() && F.size()>0)                                {
      if (F.size()<(8*1024*1024))                                {
        File :: toByteArray ( XZ , XzData )                      ;
        if (XzData.size()==F.size())                             {
          hasData = true                                         ;
          m = tr ( "Compressed data size for %1 is %2"           )
              . arg ( packaging                                  )
              . arg ( F.size()                                 ) ;
          encryptReport -> append ( m )                          ;
          plan -> processEvents      (                         ) ;
        } else                                                   {
          m = tr ( "Failure to read compressed data" )           ;
          encryptReport -> append ( m )                          ;
          menu -> setEnabled      ( true                       ) ;
          plan -> processEvents      (                         ) ;
          Alert ( Error )                                        ;
          return                                                 ;
        }                                                        ;
      } else                                                     {
        m = tr ( "Compressed data size %1 exceeds limit %2"      )
            . arg ( F.size()                                     )
            . arg ( (8*1024*1024)                              ) ;
        encryptReport -> append ( m )                            ;
        menu -> setEnabled      ( true                         ) ;
        plan -> processEvents   (                              ) ;
        Alert ( Error )                                          ;
        return                                                   ;
      }                                                          ;
    }                                                            ;
  }                                                              ;
  if (!hasData)                                                  {
    m = tr("You did not specify the data you want to encrypt." ) ;
    encryptReport -> append ( m )                                ;
    menu -> setEnabled       ( true                            ) ;
    plan -> processEvents    (                                 ) ;
    Alert                    ( Error                           ) ;
    return                                                       ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  if (SourcePicture.length()<=0)                                 {
    m = tr("You did not specify your source picture."          ) ;
    encryptReport -> append  ( m                               ) ;
    menu -> setEnabled       ( true                            ) ;
    plan -> processEvents    (                                 ) ;
    Alert                    ( Error                           ) ;
    return                                                       ;
  }                                                              ;
  rp = SourcePicture                                             ;
  rp = Root.relativeFilePath(rp)                                 ;
  m  = tr("Source image filename is `%1`").arg(rp)               ;
  encryptReport -> append ( m )                                  ;
  plan -> processEvents   (   )                                  ;
  if (!SrcImage.load(SourcePicture)                             ||
       SrcImage . width  ( ) <= 0                               ||
       SrcImage . height ( ) <= 0                              ) {
    m = tr("Source picture can not be loaded."                 ) ;
    encryptReport -> append  ( m                               ) ;
    menu -> setEnabled       ( true                            ) ;
    plan -> processEvents    (                                 ) ;
    Alert                    ( Error                           ) ;
    return                                                       ;
  }                                                              ;
  m = tr("Source image size is %1 x %2").arg(SrcImage.width()).arg(SrcImage.height()) ;
  encryptReport -> append ( m )                                  ;
  plan -> processEvents   (   )                                  ;
  ////////////////////////////////////////////////////////////////
  if (KeyPicture.length()<=0)                                    {
    m = tr("You did not specify your key picture."             ) ;
    encryptReport -> append  ( m                               ) ;
    menu -> setEnabled       ( true                            ) ;
    plan -> processEvents    (                                 ) ;
    Alert                    ( Error                           ) ;
    return                                                       ;
  }                                                              ;
  rp = KeyPicture                                                ;
  rp = Root.relativeFilePath(rp)                                 ;
  m  = tr("Key image filename is `%1`").arg(rp)                  ;
  encryptReport -> append ( m )                                  ;
  plan -> processEvents   (   )                                  ;
  if (!KeyImage.load(KeyPicture)                                ||
       KeyImage . width  ( ) <= 0                               ||
       KeyImage . height ( ) <= 0                              ) {
    m = tr("Key picture can not be loaded."                    ) ;
    encryptReport -> append  ( m                               ) ;
    menu -> setEnabled       ( true                            ) ;
    plan -> processEvents    (                                 ) ;
    Alert                    ( Error                           ) ;
    return                                                       ;
  }                                                              ;
  m = tr("Key image size is %1 x %2").arg(KeyImage.width()).arg(KeyImage.height()) ;
  encryptReport -> append ( m )                                  ;
  plan -> processEvents   (   )                                  ;
  ////////////////////////////////////////////////////////////////
  bool encrypted = false                                         ;
  if (Images::EncryptPair(packaging,XzData,PackData,KeyData))    {
    encrypted = true                                             ;
    if ( PackData . size ( ) <= 0 ) encrypted = false            ;
    if ( KeyData  . size ( ) <= 0 ) encrypted = false            ;
  }                                                              ;
  if (!encrypted)                                                {
    m = tr("Encryption failure")                                 ;
    encryptReport -> append  ( m                               ) ;
    menu -> setEnabled       ( true                            ) ;
    plan -> processEvents    (                                 ) ;
    Alert                    ( Error                           ) ;
    return                                                       ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  QDir K                                                         ;
  QDir E                                                         ;
  if ( plan  -> Booleans [ "Desktop" ] )                         {
    K = QDir ( Root.absoluteFilePath("Upload"    ) )             ;
    E = QDir ( Root.absoluteFilePath("Download"  ) )             ;
  } else                                                         {
    K = QDir ( Root.absoluteFilePath("Keys"      ) )             ;
    E = QDir ( Root.absoluteFilePath("Encryption") )             ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  if (PackData.size()>0)                                         {
    QImage O                                                     ;
    if (N::Images::Embedded(SrcImage,O,PackData))                {
      QString FO = QString("PSH-%1.png").arg(packaging)          ;
      FO = E . absoluteFilePath  ( FO )                          ;
      if ( O  . save ( FO ) )                                    {
        QString XP                                               ;
        XP = FO                                                  ;
        XP = Root.relativeFilePath ( XP )                        ;
        m = tr("Steganographic picture saved at `%1`.").arg(XP)  ;
        encryptReport -> append ( m                            ) ;
        plan -> processEvents   (                              ) ;
      } else                                                     {
        m = tr("Steganographic picture can not be saved.")       ;
        encryptReport -> append ( m )                            ;
        menu -> setEnabled      ( true                         ) ;
        Alert                   ( Error                        ) ;
        plan -> processEvents   (                              ) ;
        return                                                   ;
      }                                                          ;
    } else                                                       {
      m = tr("Data is too big to fit into the picture.")         ;
      encryptReport -> append  ( m                             ) ;
      menu -> setEnabled       ( true                          ) ;
      plan -> processEvents    (                               ) ;
      Alert                    ( Error                         ) ;
      return                                                     ;
    }                                                            ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  if (KeyData .size()>0)                                         {
    QImage O                                                     ;
    if (N::Images::Embedded(KeyImage,O,KeyData))                 {
      QString FO = QString("KEY-%1.png").arg(packaging)          ;
      FO = K . absoluteFilePath  ( FO )                          ;
      if ( O  . save ( FO ) )                                    {
        QString XP                                               ;
        XP = FO                                                  ;
        XP = Root.relativeFilePath ( XP )                        ;
        m = tr("Steganographic key saved at `%1`.").arg(XP)      ;
        encryptReport -> append  ( m                           ) ;
        plan -> processEvents    (                             ) ;
      } else                                                     {
        m = tr("Steganographic key can not be saved.")           ;
        encryptReport -> append  ( m                           ) ;
        menu -> setEnabled       ( true                        ) ;
        plan -> processEvents    (                             ) ;
        Alert                    ( Error                       ) ;
        return                                                   ;
      }                                                          ;
    } else                                                       {
      m = tr("Key data is too big to fit into the picture.")     ;
      encryptReport -> append  ( m                             ) ;
      menu -> setEnabled       ( true                          ) ;
      plan -> processEvents    (                               ) ;
      Alert                    ( Error                         ) ;
      return                                                     ;
    }                                                            ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  if (XZ.length()>0)                                             {
    QFileInfo FXZ ( XZ )                                         ;
    if (FXZ.exists()) QFile :: remove ( XZ )                     ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  if ( ! plan  -> Booleans [ "Desktop" ] )                       {
    SqlConnection SC ( plan -> sql )                             ;
    if (SC.open("PaintingSecretGui","DoEncrypt"))                {
      SC . assureUuid ( PlanTable(MajorUuid) , packaging , 260 ) ;
      SC . close ( )                                             ;
    }                                                            ;
    SC . remove ( )                                              ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  SourcePicture = ""                                             ;
  KeyPicture    = ""                                             ;
  ////////////////////////////////////////////////////////////////
  m = tr("Encryption successful, please go to `Depot` to see the results, or use FTP upload to your target machine.") ;
  encryptReport -> append    ( m                               ) ;
  m = tr("Do not change the image file format, otherwise the data hidden in the picture will be lost.") ;
  encryptReport -> append    ( m                               ) ;
  menu -> setEnabled         ( true                            ) ;
  plan -> processEvents      (                                 ) ;
  Alert                      ( Error                           ) ;
}

void N::PaintingSecretGui::DataPicture(void)
{
  header -> setCurrentWidget ( label                             ) ;
  stack  -> setCurrentWidget ( pickEncrypt                       ) ;
  menu   -> setCurrentWidget ( getEncrypt                        ) ;
  label  -> setText          ( tr("Pick picture for decryption") ) ;
  Alert                      ( Error                             ) ;
  getEncrypt  -> setEnabled  ( false                             ) ;
  plan   -> processEvents    (                                   ) ;
  pickEncrypt -> Index = 0                                         ;
  pickEncrypt -> Refresh     (                                   ) ;
  getEncrypt  -> setEnabled  ( true                              ) ;
}

void N::PaintingSecretGui::DataKey(void)
{
  header -> setCurrentWidget ( label                             ) ;
  stack  -> setCurrentWidget ( pickKey                           ) ;
  menu   -> setCurrentWidget ( getKeyPic                         ) ;
  label  -> setText      ( tr("Pick key picture for decryption") ) ;
  Alert                      ( Error                             ) ;
  getKeyPic   -> setEnabled  ( false                             ) ;
  plan   -> processEvents    (                                   ) ;
  pickKey     -> Index = 0                                         ;
  pickKey     -> Refresh     (                                   ) ;
  getKeyPic   -> setEnabled  ( true                              ) ;
}

void N::PaintingSecretGui::DoDecrypt(void)
{
  header -> setCurrentWidget ( label         )                             ;
  stack  -> setCurrentWidget ( decryptReport )                             ;
  menu   -> setCurrentWidget ( decrypt       )                             ;
  menu   -> setEnabled       ( false         )                             ;
  //////////////////////////////////////////////////////////////////////////
  QString m                                                                ;
  QString rp                                                               ;
  decryptReport -> clear ( )                                               ;
  plan   -> processEvents    (               )                             ;
  if (DecryptPicture.length()<=0)                                          {
    m = tr("You did not specify your encrypted picture."       )           ;
    decryptReport -> append  ( m                               )           ;
    menu -> setEnabled       ( true                            )           ;
    plan -> processEvents    (                                 )           ;
    Alert                    ( Error                           )           ;
    return                                                                 ;
  }                                                                        ;
  //////////////////////////////////////////////////////////////////////////
  QFileInfoList L = pickKey->Root.entryInfoList                            (
                      QDir::Files                                          |
                      QDir::NoDotAndDotDot                                 |
                      QDir::NoSymLinks                                   ) ;
  QStringList   S                                                          ;
  for (int i=0;i<L.count();i++) S << L[i].fileName()                       ;
  //////////////////////////////////////////////////////////////////////////
  if (DecryptKey.length()>0)                                               {
    int index = S . indexOf ( DecryptKey )                                 ;
    if (index>=0) S . takeAt ( index )                                     ;
    S . prepend ( DecryptKey )                                             ;
  }                                                                        ;
  if (S.count()<=0)                                                        {
    m = tr("No decryption picture found.")                                 ;
    decryptReport -> append  ( m                               )           ;
    menu -> setEnabled       ( true                            )           ;
    plan -> processEvents    (                                 )           ;
    Alert                    ( Error                           )           ;
    return                                                                 ;
  }                                                                        ;
  //////////////////////////////////////////////////////////////////////////
  QImage     SRC                                                           ;
  QImage     KEY                                                           ;
  QByteArray Body                                                          ;
  SUID       srid    = 0                                                   ;
  bool       correct = true                                                ;
  rp = pickEncrypt->Root.absoluteFilePath ( DecryptPicture )               ;
  if (!SRC.load(rp)) correct = false                                       ;
  if (correct)                                                             {
    if (!Images::Extract(SRC,Body)) correct = false                        ;
  }                                                                        ;
  if (correct)                                                             {
    int t = Images::DecryptPair(Body,srid)                                 ;
    if (t!=1) correct = false                                              ;
  }                                                                        ;
  if (!correct)                                                            {
    m = tr("Decryption failure.")                                          ;
    decryptReport -> append  ( m                               )           ;
    menu -> setEnabled       ( true                            )           ;
    plan -> processEvents    (                                 )           ;
    Alert                    ( Error                           )           ;
    return                                                                 ;
  }                                                                        ;
  //////////////////////////////////////////////////////////////////////////
  correct = false                                                          ;
  for (int i=0;!correct && i<S.count();i++)                                {
    QString s = S[i]                                                       ;
    rp  = pickKey->Root.absoluteFilePath(s)                                ;
    KEY = QImage()                                                         ;
    if (KEY.load(rp))                                                      {
      QByteArray KB                                                        ;
      decryptReport -> append  ( s )                                       ;
      plan -> processEvents    (   )                                       ;
      if (Images::Extract(KEY,KB))                                         {
        SUID krid = 0                                                      ;
        int t = Images::DecryptPair(KB,krid)                               ;
        if (t==0 && krid==srid)                                            {
          QByteArray XZB                                                   ;
          if (Images::DecryptBody(srid,XZB,Body,KB))                       {
            if (XZB.size()>0)                                              {
              QString fs = QString("Temp/%1.tar.xz").arg(srid)             ;
              fs = Root.absoluteFilePath(fs)                               ;
              File :: toFile ( fs , XZB )                                  ;
              QString dd = QString("Files/%1").arg(srid)                   ;
              dd = Root.absoluteFilePath ( dd )                            ;
              VirtualIO VIO                                                ;
              QDir      vdd ( dd )                                         ;
              VIO . setDirectory ( vdd              )                      ;
              VIO . setFile      ( File::Xz         )                      ;
              VIO . setVIO       ( VirtualDisk::Tar )                      ;
              VIO . setFileName  ( fs               )                      ;
              VIO . Unpack       (                  )                      ;
              m = tr("Decrypt %1 successful").arg(srid)                    ;
              decryptReport -> append  ( m )                               ;
              if (VIO.files.count()>0)                                     {
                m = "==================="                                  ;
                decryptReport -> append  ( m )                             ;
                m = tr("Decrypted files")                                  ;
                decryptReport -> append  ( m )                             ;
                m = "==================="                                  ;
                decryptReport -> append  ( m )                             ;
                plan -> processEvents    (   )                             ;
                for (int i=0;i<VIO.files.count();i++)                      {
                  m = QString("Files/%1/%2").arg(srid).arg(VIO.files[i].Filename) ;
                  decryptReport -> append  ( m )                           ;
                  plan -> processEvents    (   )                           ;
                }                                                          ;
                m = "==================="                                  ;
                decryptReport -> append  ( m )                             ;
                plan -> processEvents    (   )                             ;
                m = tr("Please use FTP download to your machine for usage.") ;
                decryptReport -> append  ( m )                             ;
                plan -> processEvents    (   )                             ;
              }                                                            ;
              QFile :: remove ( fs )                                       ;
              correct = true                                               ;
            }                                                              ;
          }                                                                ;
        }                                                                  ;
      }                                                                    ;
    }                                                                      ;
  }                                                                        ;
  if (!correct)                                                            {
    m = tr("Decryption failure.")                                          ;
    decryptReport -> append  ( m                               )           ;
    menu -> setEnabled       ( true                            )           ;
    plan -> processEvents    (                                 )           ;
    Alert                    ( Error                           )           ;
    return                                                                 ;
  }                                                                        ;
  //////////////////////////////////////////////////////////////////////////
  DecryptPicture = ""                                                      ;
  DecryptKey     = ""                                                      ;
  //////////////////////////////////////////////////////////////////////////
  menu -> setEnabled       ( true                            )           ;
  Alert                    ( Error                           )             ;
}

void N::PaintingSecretGui::DepotList(void)
{
  emit FullDepot ( ) ;
}

void N::PaintingSecretGui::DepotPictures(void)
{
  header -> setCurrentWidget ( label          ) ;
  stack  -> setCurrentWidget ( pickPicture    ) ;
  menu   -> setCurrentWidget ( viewImages     ) ;
  label  -> setText          ( tr("Pictures") ) ;
  Alert                      ( Error          ) ;
  viewImages -> setEnabled   ( false          ) ;
  plan   -> processEvents    (                ) ;
  pickPicture -> Index = 0                      ;
  pickPicture -> Refresh     (                ) ;
  viewImages  -> setEnabled  ( true           ) ;
  ///////////////////////////////////////////////
  BackWidget  = pickPicture                     ;
  BackMenu    = viewImages                      ;
  ReturnLabel = tr("Pictures")                  ;
}

void N::PaintingSecretGui::DepotKeys(void)
{
  header -> setCurrentWidget ( label                         ) ;
  stack  -> setCurrentWidget ( pickKey                       ) ;
  menu   -> setCurrentWidget ( viewKeys                      ) ;
  label  -> setText          ( tr("Decryption key pictures") ) ;
  Alert                      ( Error                         ) ;
  viewKeys   -> setEnabled   ( false                         ) ;
  plan      -> processEvents (                               ) ;
  pickKey     -> Index = 0                                     ;
  pickKey     -> Refresh     (                               ) ;
  viewKeys    -> setEnabled  ( true                          ) ;
  //////////////////////////////////////////////////////////////
  BackWidget  = pickKey                                        ;
  BackMenu    = viewKeys                                       ;
  ReturnLabel = tr("Decryption key pictures")                  ;
}

void N::PaintingSecretGui::DepotEncrypted(void)
{
  header -> setCurrentWidget ( label                    ) ;
  stack  -> setCurrentWidget ( pickEncrypt              ) ;
  menu   -> setCurrentWidget ( viewEncrypt              ) ;
  label  -> setText          ( tr("Encrypted pictures") ) ;
  Alert                      ( Error                    ) ;
  viewEncrypt -> setEnabled  ( false                    ) ;
  plan   -> processEvents    (                          ) ;
  pickEncrypt -> Index = 0                                ;
  pickEncrypt -> Refresh     (                          ) ;
  viewEncrypt -> setEnabled  ( true                     ) ;
  /////////////////////////////////////////////////////////
  BackWidget  = pickEncrypt                               ;
  BackMenu    = viewEncrypt                               ;
  ReturnLabel = tr("Encrypted pictures")                  ;
}

void N::PaintingSecretGui::DepotFtp(void)
{
  emit FullFtp   ( ) ;
}

void N::PaintingSecretGui::ViewPicture(void)
{
  QString path                                               ;
  if (!pickPicture->CurrentPath(path)) return                ;
  QString file = pickPicture->Root.absoluteFilePath ( path ) ;
  ////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                        ;
  if (!IFG.exists()) return                                  ;
  picTool = new PaintingViewTool ( menu  , plan            ) ;
  vcf     = new VcfView          ( stack , plan            ) ;
  menu   -> addWidget            ( picTool                 ) ;
  stack  -> addWidget            ( vcf                     ) ;
  menu   -> setCurrentWidget     ( picTool                 ) ;
  stack  -> setCurrentWidget     ( vcf                     ) ;
  header -> setCurrentWidget     ( label                   ) ;
  plan   -> processEvents        (                         ) ;
  vcf    -> ViewPicture          ( IFG , NULL              ) ;
  vcf    -> resize               ( stack->size()           ) ;
  Alert                          ( Done                    ) ;
  ////////////////////////////////////////////////////////////
  vcf    -> skipMouse = true                                 ;
  nConnect ( picTool , SIGNAL(Back      ())                  ,
             this    , SLOT  (ReturnPick())                ) ;
  nConnect ( picTool , SIGNAL(ZoomIn    ())                  ,
             vcf     , SLOT  (ZoomIn    ())                ) ;
  nConnect ( picTool , SIGNAL(ZoomOut   ())                  ,
             vcf     , SLOT  (ZoomOut   ())                ) ;
}

void N::PaintingSecretGui::ReturnPick(void)
{
  header  -> setCurrentWidget ( label                             ) ;
  stack   -> setCurrentWidget ( pickPicture                       ) ;
  menu    -> setCurrentWidget ( srcPicture                        ) ;
  label   -> setText          ( tr("Pick picture for encryption") ) ;
  Alert                       ( Error                             ) ;
  ///////////////////////////////////////////////////////////////////
  picTool -> deleteLater      (                                   ) ;
  vcf     -> deleteLater      (                                   ) ;
  ///////////////////////////////////////////////////////////////////
  picTool  = NULL                                                   ;
  vcf      = NULL                                                   ;
}

void N::PaintingSecretGui::ViewEncrypted(void)
{
  QString path                                               ;
  if (!pickEncrypt->CurrentPath(path)) return                ;
  QString file = pickEncrypt->Root.absoluteFilePath ( path ) ;
  ////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                        ;
  if (!IFG.exists()) return                                  ;
  picTool = new PaintingViewTool ( menu  , plan            ) ;
  vcf     = new VcfView          ( stack , plan            ) ;
  menu   -> addWidget            ( picTool                 ) ;
  stack  -> addWidget            ( vcf                     ) ;
  menu   -> setCurrentWidget     ( picTool                 ) ;
  stack  -> setCurrentWidget     ( vcf                     ) ;
  header -> setCurrentWidget     ( label                   ) ;
  plan   -> processEvents        (                         ) ;
  vcf    -> ViewPicture          ( IFG , NULL              ) ;
  vcf    -> resize               ( stack->size()           ) ;
  Alert                          ( Done                    ) ;
  ////////////////////////////////////////////////////////////
  vcf    -> skipMouse = true                                 ;
  nConnect ( picTool , SIGNAL(Back      ())                  ,
             this    , SLOT  (ReturnEncrypted())           ) ;
  nConnect ( picTool , SIGNAL(ZoomIn    ())                  ,
             vcf     , SLOT  (ZoomIn    ())                ) ;
  nConnect ( picTool , SIGNAL(ZoomOut   ())                  ,
             vcf     , SLOT  (ZoomOut   ())                ) ;
}

void N::PaintingSecretGui::ReturnEncrypted(void)
{
  header  -> setCurrentWidget ( label                             ) ;
  stack   -> setCurrentWidget ( pickEncrypt                       ) ;
  menu    -> setCurrentWidget ( getEncrypt                        ) ;
  label   -> setText          ( tr("Pick picture for decryption") ) ;
  Alert                       ( Error                             ) ;
  ///////////////////////////////////////////////////////////////////
  picTool -> deleteLater      (                                   ) ;
  vcf     -> deleteLater      (                                   ) ;
  ///////////////////////////////////////////////////////////////////
  picTool  = NULL                                                   ;
  vcf      = NULL                                                   ;
}

void N::PaintingSecretGui::ViewKeys(void)
{
  QString path                                               ;
  if (!pickKey->CurrentPath(path)) return                    ;
  QString file = pickKey->Root.absoluteFilePath ( path )     ;
  ////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                        ;
  if (!IFG.exists()) return                                  ;
  picTool = new PaintingViewTool ( menu  , plan            ) ;
  vcf     = new VcfView          ( stack , plan            ) ;
  menu   -> addWidget            ( picTool                 ) ;
  stack  -> addWidget            ( vcf                     ) ;
  menu   -> setCurrentWidget     ( picTool                 ) ;
  stack  -> setCurrentWidget     ( vcf                     ) ;
  header -> setCurrentWidget     ( label                   ) ;
  plan   -> processEvents        (                         ) ;
  vcf    -> ViewPicture          ( IFG , NULL              ) ;
  vcf    -> resize               ( stack->size()           ) ;
  Alert                          ( Done                    ) ;
  ////////////////////////////////////////////////////////////
  vcf    -> skipMouse = true                                 ;
  nConnect ( picTool , SIGNAL(Back      ())                  ,
             this    , SLOT  (ReturnKeys())                ) ;
  nConnect ( picTool , SIGNAL(ZoomIn    ())                  ,
             vcf     , SLOT  (ZoomIn    ())                ) ;
  nConnect ( picTool , SIGNAL(ZoomOut   ())                  ,
             vcf     , SLOT  (ZoomOut   ())                ) ;
}

void N::PaintingSecretGui::ReturnKeys(void)
{
  header  -> setCurrentWidget ( label                             ) ;
  stack   -> setCurrentWidget ( pickKey                           ) ;
  menu    -> setCurrentWidget ( getKeyPic                         ) ;
  label   -> setText      ( tr("Pick key picture for decryption") ) ;
  Alert                       ( Error                             ) ;
  ///////////////////////////////////////////////////////////////////
  picTool -> deleteLater      (                                   ) ;
  vcf     -> deleteLater      (                                   ) ;
  ///////////////////////////////////////////////////////////////////
  picTool  = NULL                                                   ;
  vcf      = NULL                                                   ;
}

void N::PaintingSecretGui::ViewDepot(void)
{
  QString path                                               ;
  PickPicture * pp = (PickPicture *)BackWidget               ;
  if (!pp->CurrentPath(path)) return                         ;
  QString file = pp->Root.absoluteFilePath ( path )          ;
  ////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                        ;
  if (!IFG.exists()) return                                  ;
  picTool = new PaintingViewTool ( menu  , plan            ) ;
  vcf     = new VcfView          ( stack , plan            ) ;
  menu   -> addWidget            ( picTool                 ) ;
  stack  -> addWidget            ( vcf                     ) ;
  menu   -> setCurrentWidget     ( picTool                 ) ;
  stack  -> setCurrentWidget     ( vcf                     ) ;
  header -> setCurrentWidget     ( label                   ) ;
  plan   -> processEvents        (                         ) ;
  vcf    -> ViewPicture          ( IFG , NULL              ) ;
  vcf    -> resize               ( stack->size()           ) ;
  Alert                          ( Done                    ) ;
  ////////////////////////////////////////////////////////////
  vcf    -> skipMouse = true                                 ;
  nConnect ( picTool , SIGNAL(Back       ())                 ,
             this    , SLOT  (ReturnDepot())               ) ;
  nConnect ( picTool , SIGNAL(ZoomIn     ())                 ,
             vcf     , SLOT  (ZoomIn     ())               ) ;
  nConnect ( picTool , SIGNAL(ZoomOut    ())                 ,
             vcf     , SLOT  (ZoomOut    ())               ) ;
}

void N::PaintingSecretGui::ReturnDepot(void)
{
  header  -> setCurrentWidget ( label        ) ;
  stack   -> setCurrentWidget ( BackWidget   ) ;
  menu    -> setCurrentWidget ( BackMenu     ) ;
  label   -> setText          ( ReturnLabel  ) ;
  Alert                       ( Error        ) ;
  //////////////////////////////////////////////
  picTool -> deleteLater      (              ) ;
  vcf     -> deleteLater      (              ) ;
  //////////////////////////////////////////////
  picTool  = NULL                              ;
  vcf      = NULL                              ;
}

void N::PaintingSecretGui::ObtainPic(void)
{
  QString path                                                     ;
  if (!pickPicture->CurrentPath(path)) return                      ;
  QString file = pickPicture->Root.absoluteFilePath ( path )       ;
  //////////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                              ;
  if (!IFG.exists()) return                                        ;
  //////////////////////////////////////////////////////////////////
  header -> setCurrentWidget ( label                             ) ;
  stack  -> setCurrentWidget ( encryptReport                     ) ;
  menu   -> setCurrentWidget ( encrypt                           ) ;
  label  -> setText          ( tr("Encrypt data into a picture") ) ;
  //////////////////////////////////////////////////////////////////
  SourcePicture = file                                             ;
}

void N::PaintingSecretGui::ObtainKey(void)
{
  QString path                                                     ;
  if (!pickPicture->CurrentPath(path)) return                      ;
  QString file = pickPicture->Root.absoluteFilePath ( path )       ;
  //////////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                              ;
  if (!IFG.exists()) return                                        ;
  //////////////////////////////////////////////////////////////////
  header -> setCurrentWidget ( label                             ) ;
  stack  -> setCurrentWidget ( encryptReport                     ) ;
  menu   -> setCurrentWidget ( encrypt                           ) ;
  label  -> setText          ( tr("Encrypt data into a picture") ) ;
  //////////////////////////////////////////////////////////////////
  KeyPicture = file                                                ;
}

void N::PaintingSecretGui::ObtainEncrypted(void)
{
  QString path                                                   ;
  if (!pickEncrypt->CurrentPath(path)) return                    ;
  QString file = pickEncrypt->Root.absoluteFilePath ( path )     ;
  ////////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                            ;
  if (!IFG.exists()) return                                      ;
  ////////////////////////////////////////////////////////////////
  header -> setCurrentWidget ( label                           ) ;
  stack  -> setCurrentWidget ( decryptReport                   ) ;
  menu   -> setCurrentWidget ( decrypt                         ) ;
  label  -> setText          ( tr("Decrypt data from picture") ) ;
  ////////////////////////////////////////////////////////////////
  DecryptPicture = file                                          ;
}

void N::PaintingSecretGui::ObtainKeys(void)
{
  QString path                                                   ;
  if (!pickKey->CurrentPath(path)) return                        ;
  QString file = pickKey->Root.absoluteFilePath ( path )         ;
  ////////////////////////////////////////////////////////////////
  QFileInfo IFG(file)                                            ;
  if (!IFG.exists()) return                                      ;
  ////////////////////////////////////////////////////////////////
  header -> setCurrentWidget ( label                           ) ;
  stack  -> setCurrentWidget ( decryptReport                   ) ;
  menu   -> setCurrentWidget ( decrypt                         ) ;
  label  -> setText          ( tr("Decrypt data from picture") ) ;
  ////////////////////////////////////////////////////////////////
  DecryptKey = file                                              ;
}

void N::PaintingSecretGui::FileRename(void)
{
  header     -> setCurrentWidget ( lineRename         ) ;
  QTreeWidgetItem * item = pickArchive->currentItem ( ) ;
  if (NotNull(item))                                    {
    QString path = item -> text ( 0 )                   ;
    QDir    cp   = pickArchive -> CurrentPath ( )       ;
    QDir    rp   = pickArchive -> Path        ( )       ;
    path = cp . absoluteFilePath ( path  )              ;
    path = rp . relativeFilePath ( path  )              ;
    lineRename -> blockSignals   ( true  )              ;
    lineRename -> setText        ( path  )              ;
    lineRename -> blockSignals   ( false )              ;
  } else                                                {
    lineRename -> blockSignals   ( true  )              ;
    lineRename -> setText        ( ""    )              ;
    lineRename -> blockSignals   ( false )              ;
  }                                                     ;
  lineRename -> setFocus         ( Qt::TabFocusReason ) ;
}

void N::PaintingSecretGui::RenameAction(void)
{
  QTreeWidgetItem * item = pickArchive->currentItem ( ) ;
  if (NotNull(item))                                    {
    QString name = lineRename->text()                   ;
    QString path = item -> text ( 0 )                   ;
    QDir    cp   = pickArchive -> CurrentPath ( )       ;
    QDir    rp   = pickArchive -> Path        ( )       ;
    path =  cp   . absoluteFilePath ( path  )           ;
    if (name.length()>0)                                {
      name = rp  . absoluteFilePath ( name  )           ;
      if (name.length()>0 && path.length())             {
        QFile :: rename ( path , name )                 ;
      }                                                 ;
    }                                                   ;
  }                                                     ;
  header      -> setCurrentWidget ( folderList )        ;
  plan        -> processEvents    (            )        ;
  pickArchive -> List             (            )        ;
  Alert ( Error )                                       ;
}

void N::PaintingSecretGui::FileMove(void)
{
  header   -> setCurrentWidget ( lineMove )             ;
  QTreeWidgetItem * item = pickArchive->currentItem ( ) ;
  if (NotNull(item))                                    {
    QString path = item -> text ( 0 )                   ;
    QDir    cp   = pickArchive -> CurrentPath ( )       ;
    QDir    rp   = pickArchive -> Path        ( )       ;
    path = cp . absoluteFilePath ( path  )              ;
    path = rp . relativeFilePath ( path  )              ;
    lineMove -> blockSignals     ( true  )              ;
    lineMove -> setText          ( path  )              ;
    lineMove -> blockSignals     ( false )              ;
  } else                                                {
    lineMove -> blockSignals     ( true  )              ;
    lineMove -> setText          ( ""    )              ;
    lineMove -> blockSignals     ( false )              ;
  }                                                     ;
  lineMove -> setFocus           ( Qt::TabFocusReason ) ;
}

void N::PaintingSecretGui::MoveAction(void)
{
  QTreeWidgetItem * item = pickArchive->currentItem ( ) ;
  if (NotNull(item))                                    {
    QString name = lineMove->text()                     ;
    QString path = item -> text ( 0 )                   ;
    QDir    cp   = pickArchive -> CurrentPath ( )       ;
    QDir    rp   = pickArchive -> Path        ( )       ;
    path =  cp   . absoluteFilePath ( path  )           ;
    if (name.length()>0)                                {
      name = rp  . absoluteFilePath ( name  )           ;
      if (name.length()>0 && path.length())             {
        QFile :: rename ( path , name )                 ;
      }                                                 ;
    }                                                   ;
  }                                                     ;
  header      -> setCurrentWidget ( folderList )        ;
  plan        -> processEvents    (            )        ;
  pickArchive -> List             (            )        ;
  Alert ( Error )                                       ;
}

void N::PaintingSecretGui::FileDirectory(void)
{
  header        -> setCurrentWidget ( lineDirectory      ) ;
  lineDirectory -> blockSignals     ( true               ) ;
  lineDirectory -> setText          ( ""                 ) ;
  lineDirectory -> blockSignals     ( false              ) ;
  lineDirectory -> setFocus         ( Qt::TabFocusReason ) ;
}

void N::PaintingSecretGui::DirectoryAction(void)
{
  QString name = lineDirectory -> text (         ) ;
  if (name.length()>0)                             {
    QDir    cp   = pickArchive -> CurrentPath  ( ) ;
    QDir    rp   = pickArchive -> Path         ( ) ;
    QString path = cp . absoluteFilePath ( name  ) ;
    QString tp   = rp . absoluteFilePath ( ""    ) ;
    if (path.contains(tp))                         {
      cp . mkdir ( name )                          ;
    }                                              ;
  }                                                ;
  header      -> setCurrentWidget ( folderList )   ;
  plan        -> processEvents    (            )   ;
  pickArchive -> List             (            )   ;
  Alert ( Error )                                  ;
}

void N::PaintingSecretGui::FolderBack(void)
{
  header -> setCurrentWidget ( folderList  ) ;
}

void N::PaintingSecretGui::EditText(void)
{
  QTreeWidgetItem * item = pickArchive->currentItem ( )      ;
  if (IsNull(item)) return                                   ;
  QDir    cp   = pickArchive -> CurrentPath ( )              ;
  QString path = item -> text ( 0 )                          ;
  path =  cp   . absoluteFilePath ( path  )                  ;
  QFileInfo F ( path )                                       ;
  QString S = F.suffix ()                                    ;
  S = S.toLower()                                            ;
  if ( S != "txt" ) return                                   ;
  emit LoadText ( pickArchive->Path() , pickArchive -> CurrentPath() , path ) ;
  #ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  ////////////////////////////////////////////////////////////
  plainText -> clear            (                          ) ;
  header    -> setCurrentWidget ( line                     ) ;
  stack     -> setCurrentWidget ( plainText                ) ;
  menu      -> setCurrentWidget ( textEdit                 ) ;
  label     -> setText          ( tr("Plain text editor" ) ) ;
  ////////////////////////////////////////////////////////////
  QByteArray Body                                            ;
  File :: toByteArray ( path , Body )                        ;
  plainText -> blockSignals ( true                         ) ;
  plainText -> append       ( QString::fromUtf8(Body)      ) ;
  plainText -> verticalScrollBar ( ) -> setValue ( 0 )       ;
  plainText -> blockSignals ( false                        ) ;
  ////////////////////////////////////////////////////////////
  line      -> blockSignals ( true                         ) ;
  line      -> setText      ( item -> text ( 0 )           ) ;
  line      -> blockSignals ( false                        ) ;
  ////////////////////////////////////////////////////////////
  Alert                  ( Error                           ) ;
  #endif
}

void N::PaintingSecretGui::BackEdit(void)
{
  header      -> setCurrentWidget ( folderList  ) ;
  stack       -> setCurrentWidget ( pickArchive ) ;
  menu        -> setCurrentWidget ( folderEdit  ) ;
  plan        -> processEvents    (             ) ;
  pickArchive -> List             (             ) ;
  Alert                           ( Click       ) ;
}

void N::PaintingSecretGui::NewEdit(void)
{
  plainText -> clear ( ) ;
}

void N::PaintingSecretGui::SaveEdit(void)
{
  QString note = line->text()                     ;
  if (note.length()<=0) return                    ;
  QDir    r    = pickArchive -> Path(      )      ;
  QString file = r.absoluteFilePath ( note )      ;
  QString head = r.absoluteFilePath ( ""   )      ;
  if (!file.contains(head)) return                ;
  QString    text = plainText -> toPlainText ( )  ;
  QByteArray body = text . toUtf8 ( )             ;
  QFileInfo  fdir ( file                    )     ;
  r . mkpath      ( fdir . absolutePath ( ) )     ;
  File :: toFile  ( file , body             )     ;
  /////////////////////////////////////////////////
  header      -> setCurrentWidget ( folderList  ) ;
  stack       -> setCurrentWidget ( pickArchive ) ;
  menu        -> setCurrentWidget ( folderEdit  ) ;
  plan        -> processEvents    (             ) ;
  pickArchive -> List             (             ) ;
  Alert                           ( Click       ) ;
}

void N::PaintingSecretGui::FileFtp(void)
{
  QString path = pickArchive->CurrentPath().absoluteFilePath("") ;
  emit Transfer ( path )                                              ;
}

void N::PaintingSecretGui::ImportPicture(void)
{
  QString path = pickPicture->Root.absoluteFilePath("") ;
  emit Obtain ( path )                                       ;
}

void N::PaintingSecretGui::ImportKey(void)
{
  QString path = pickPicture->Root.absoluteFilePath("") ;
  emit Obtain ( path )                                       ;
}

void N::PaintingSecretGui::ImportEncrypted(void)
{
  QString path = pickEncrypt->Root.absoluteFilePath("") ;
  emit Transfer ( path )                                     ;
}

void N::PaintingSecretGui::ImportKeys(void)
{
  QString path = pickKey->Root.absoluteFilePath("") ;
  emit Transfer ( path )                                 ;
}
