/****************************************************************************
 *                                                                          *
 * Copyright (C) 2015 Neutrino International Inc.                           *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_EXCITON_H
#define QT_EXCITON_H

#include <QtCore>
#include <QtNetwork>
#include <QtSql>
#include <QtScript>
#include <QtPositioning>
#include <QtCURL>
#include <QtCUDA>
#include <QtTorrent>
#include <QtZMQ>
#include <QtPCAP>
#include <QtOpenCV>
#include <QtProlog>
#include <QtLISP>
#include <QtPython>
#include <QtFFmpeg>
#include <QtAudio>
#include <Essentials>
#include <QtCalendar>
#include <QtCryptography>
#include <QtMIME>
#include <SqlAnalyzer>
#include <QtGMP>
#include <QtDAI>
#include <QtGSL>
#include <QtANN>
#include <QtAlgebra>
#include <QtDiscrete>
#include <QtFFT>
#include <Mathematics>
#include <QtFuzzy>
#include <QtFLP>
#include <QtGeography>
#include <NetProtocol>
#include <QtXmlRPC>
#include <QtUDT>
#include <QtFTP>
#include <QtRPC>
#include <QtJsonRPC>
#include <AudioIO>
#include <QtPhonemes>
#include <QtVocal>
#include <QtSpeech>
#include <QtNLP>
#include <QtMatcher>
#include <QtLinguistics>
#include <QtForth>
#include <QtNLC>
#include <QtYacc>
#include <QtFoundation>
#include <QtInference>
#include <QtDecision>
#include <Science>
#include <QtAutomation>
#include <QtAutonomy>
#include <QtGeometry>
#include <QtGadgets>
#include <QtWorld>
#include <QtComponents>
#include <QtAIV>
#include <QtManagers>
#include <Physics>
#include <Chemistry>
#include <Biology>
#include <Business>
#include <QtForex>
#include <Marketing>
#include <QtModels>
#include <QtAnalog>
#include <NetWidgets>
#include <MathWidgets>
#include <QtGIS>
#include <QtCLF>
#include <QtVCF>
#include <DataWidgets>
#include <QtTasks>
#include <QtPhotography>
#include <QtHuman>
#include <Society>
#include <QtAV>
#include <Domination>
#include <curl/curl.h>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_EXCITON_LIB)
#      define Q_EXCITON_EXPORT Q_DECL_EXPORT
#    else
#      define Q_EXCITON_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_EXCITON_EXPORT
#endif

namespace Ui                                  {
class Q_EXCITON_EXPORT PaintingSecretTools    ;
class Q_EXCITON_EXPORT PaintingEncryptionTool ;
class Q_EXCITON_EXPORT PaintingDecryptionTool ;
class Q_EXCITON_EXPORT PaintingDepotTool      ;
class Q_EXCITON_EXPORT PaintingSettingsTool   ;
class Q_EXCITON_EXPORT PaintingPickTool       ;
class Q_EXCITON_EXPORT PaintingViewTool       ;
class Q_EXCITON_EXPORT PaintingFilesTool      ;
class Q_EXCITON_EXPORT PaintingFolderTool     ;
class Q_EXCITON_EXPORT PaintingFolderEdit     ;
class Q_EXCITON_EXPORT PaintingFolderList     ;
class Q_EXCITON_EXPORT PaintingTextTool       ;
class Q_EXCITON_EXPORT PaintingAudioTool      ;
class Q_EXCITON_EXPORT PaintingSecrets        ;
class Q_EXCITON_EXPORT XcityPeople            ;
class Q_EXCITON_EXPORT XcityVideo             ;
class Q_EXCITON_EXPORT XcityOrganization      ;
class Q_EXCITON_EXPORT AupInfoPeople          ;
class Q_EXCITON_EXPORT AupInfoVideo           ;
class Q_EXCITON_EXPORT JavTorrentVideo        ;
class Q_EXCITON_EXPORT JavFreeVideo           ;
class Q_EXCITON_EXPORT OnePiecePictures       ;
}

namespace N
{

class Q_EXCITON_EXPORT TwoStepsFetcher   ;
class Q_EXCITON_EXPORT ImageDinoFetcher  ;
class Q_EXCITON_EXPORT ImageFlareFetcher ;
class Q_EXCITON_EXPORT ImageServeFetcher ;
class Q_EXCITON_EXPORT PicExposedFetcher ;
class Q_EXCITON_EXPORT JpTorrentFetcher  ;

class Q_EXCITON_EXPORT XcityPeople       ;
class Q_EXCITON_EXPORT XcityVideo        ;
class Q_EXCITON_EXPORT XcityOrganization ;
class Q_EXCITON_EXPORT XcitySeeker       ;
class Q_EXCITON_EXPORT AupInfoPeople     ;
class Q_EXCITON_EXPORT AupInfoVideo      ;
class Q_EXCITON_EXPORT AupInfoSeeker     ;
class Q_EXCITON_EXPORT JavTorrentVideo   ;
class Q_EXCITON_EXPORT JavTorrent        ;
class Q_EXCITON_EXPORT JavFreeVideo      ;
class Q_EXCITON_EXPORT JavFree           ;
class Q_EXCITON_EXPORT OpPictures        ;
class Q_EXCITON_EXPORT OnePiecePictures  ;

class Q_EXCITON_EXPORT TwoStepsFetcher : public Ftp
                                       , public NetworkManager
                                       , public PictureManager
{
  public:

    QDir   Temporary ;
    CURL * curl      ;

    explicit        TwoStepsFetcher (Plan * plan) ;
    virtual        ~TwoStepsFetcher (void) ;

    virtual QString TemporaryHtml   (SUID            puid     ) ;
    virtual QString ImageFilename   (QString         url        ,
                                     SUID            ruid     ) ;
    virtual bool    VerifyUrl       (QUrl          & url      ) ;
    virtual bool    ImportImage     (SqlConnection & Connection ,
                                     QString         Location   ,
                                     SUID          & image    ) ;
    virtual void    Mismatch        (QUrl          & url      ) ;
    virtual bool    Instance        (void                     ) ;
    virtual bool    Prepare         (QFile         & file       ,
                                     QUrl          & url      ) ;
    virtual bool    setOptions      (QUrl          & url      ) ;
    virtual bool    setTimeouts     (int             connexion  ,
                                     int             download ) ;
    virtual void    setAgent        (QString         agent    ) ;
    virtual void    setProxy        (QString         proxy    ) ;
    virtual void    setReferer      (QString         referer  ) ;
    virtual bool    Perform         (void                     ) ;
    virtual bool    ObtainXML       (QString         filename   ,
                                     QByteArray    & XML      ) ;
    virtual QString MiddleString    (QByteArray    & XML        ,
                                     QString         left       ,
                                     QString         right    ) ;
    virtual QString TwoStepsString  (QByteArray    & XML        ,
                                     QString         left       ,
                                     QString         middle     ,
                                     QString         right    ) ;
    virtual void    setTags         (void) ;
    virtual void    setProxyOnly    (void) ;
    virtual void    Cleanup         (void) ;
    virtual bool    Obtain          (SqlConnection & Connection ,
                                     QUrl            url        ,
                                     SUID            puid       ,
                                     SUID          & ruid       ,
                                     SUID          & image      ,
                                     int             mtimeout   ,
                                     QString         nexturl    ,
                                     QString         endmark  ) ;
    virtual bool    Obtain          (SqlConnection & Connection ,
                                     QUrl            url        ,
                                     SUID            puid       ,
                                     SUID          & ruid       ,
                                     SUID          & image      ,
                                     int             mtimeout   ,
                                     QString         nexturl    ,
                                     QString         middlemark ,
                                     QString         endmark  ) ;

  protected:

  private:

};

class Q_EXCITON_EXPORT ImageDinoFetcher : public TwoStepsFetcher
{
  public:

    explicit ImageDinoFetcher (Plan * plan) ;
    virtual ~ImageDinoFetcher (void) ;

    virtual bool    VerifyUrl (QUrl          & url      ) ;
    virtual bool    Obtain    (SqlConnection & Connection ,
                               QUrl            url        ,
                               SUID            puid       ,
                               SUID          & ruid       ,
                               SUID          & image      ,
                               int             mtimeout ) ;

  protected:

  private:

};

class Q_EXCITON_EXPORT ImageFlareFetcher : public TwoStepsFetcher
{
  public:

    explicit ImageFlareFetcher (Plan * plan) ;
    virtual ~ImageFlareFetcher (void) ;

    virtual bool    VerifyUrl  (QUrl          & url      ) ;
    virtual bool    Obtain     (SqlConnection & Connection ,
                                QUrl            url        ,
                                SUID            puid       ,
                                SUID          & ruid       ,
                                SUID          & image      ,
                                int             mtimeout ) ;

  protected:

  private:

};

class Q_EXCITON_EXPORT ImageServeFetcher : public TwoStepsFetcher
{
  public:

    explicit ImageServeFetcher (Plan * plan) ;
    virtual ~ImageServeFetcher (void) ;

    virtual bool    VerifyUrl  (QUrl          & url      ) ;
    virtual bool    Obtain     (SqlConnection & Connection ,
                                QUrl            url        ,
                                SUID            puid       ,
                                SUID          & ruid       ,
                                SUID          & image      ,
                                int             mtimeout ) ;

  protected:

  private:

};

class Q_EXCITON_EXPORT PicExposedFetcher : public TwoStepsFetcher
{
  public:

    explicit PicExposedFetcher (Plan * plan) ;
    virtual ~PicExposedFetcher (void) ;

    virtual bool    VerifyUrl  (QUrl          & url      ) ;
    virtual bool    Obtain     (SqlConnection & Connection ,
                                QUrl            url        ,
                                SUID            puid       ,
                                SUID          & ruid       ,
                                SUID          & image      ,
                                int             mtimeout ) ;

  protected:

  private:

};

class Q_EXCITON_EXPORT JpTorrentFetcher : public TwoStepsFetcher
{
  public:

    explicit JpTorrentFetcher (Plan * plan) ;
    virtual ~JpTorrentFetcher (void) ;

    virtual bool Obtain       (SqlConnection & Connection ,
                               QUrl            url        ,
                               SUID            puid       ,
                               SUID          & ruid       ,
                               QString       & torrent    ,
                               int             mtimeout ) ;

  protected:

  private:

};

class Q_EXCITON_EXPORT XcityPeople : public Widget
{
  Q_OBJECT
  public:


    explicit XcityPeople   (QWidget * parent = NULL,Plan * plan = NULL) ;
    virtual ~XcityPeople   (void) ;

    bool     SkipExists    (void) ;
    int      PeopleStart   (void) ;
    int      PeopleEnd     (void) ;
    SUID     NewbieUuid    (void) ;
    SUID     MergerUuid    (void) ;
    SUID     GalleryUuid   (void) ;
    QString  Search        (void) ;
    QString  Missing       (void) ;
    QString  Found         (void) ;
    QString  IdFound       (void) ;
    QString  IdPattern     (void) ;

  protected:

    Ui::XcityPeople * ui        ;
    ComboBox        * newbie    ;
    ComboBox        * merger    ;
    ComboBox        * gallery   ;
    QString           Scope     ;
    Sql               hunterSql ;

  private:

  public slots:

    virtual void prepare   (void) ;
    virtual void configure (QString scope,Sql & sql) ;

  protected slots:

    void NewbieChanged     (int index) ;
    void MergerChanged     (int index) ;
    void GalleryChanged    (int index) ;
    void XcityValueChanged (int index) ;
    void XcityJpChanged    (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT XcityVideo : public Widget
{
  Q_OBJECT
  public:

    explicit XcityVideo    (QWidget * parent = NULL,Plan * plan = NULL) ;
    virtual ~XcityVideo    (void);

    bool     SkipExists    (void) ;
    bool     VideoCache    (void) ;
    int      VideoStart    (void) ;
    int      VideoEnd      (void) ;
    SUID     AlbumUuid     (void) ;
    SUID     InterestUuid  (void) ;
    SUID     GalleryUuid   (void) ;
    SUID     NameUuid      (int index) ;
    QString  Search        (void) ;
    QString  Info          (void) ;
    QString  Gallery       (void) ;

  protected:

    Ui::XcityVideo  * ui          ;
    ComboBox        * album       ;
    ComboBox        * interest    ;
    ComboBox        * gallery     ;
    QString           Scope       ;
    Sql               hunterSql   ;
    QTreeWidgetItem * ItemEditing ;
    ComboBox        * Entries     ;

  private:

  public slots:

    virtual void prepare   (void) ;
    virtual void configure (QString scope,Sql & sql) ;

  protected slots:

    void AlbumChanged      (int index) ;
    void InterestChanged   (int index) ;
    void GalleryChanged    (int index) ;
    void XcityValueChanged (int index) ;
    void XcityJpChanged    (void) ;

    void NameClicked       (QTreeWidgetItem * item,int column) ;
    void NameSelected      (int index) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT XcityOrganization : public Widget
{
  Q_OBJECT
  public:

    explicit XcityOrganization (QWidget * parent = NULL,Plan * plan = NULL) ;
    virtual ~XcityOrganization (void);

    SUID     CompanyUuid       (void) ;
    QString  Search            (void) ;
    QString  CompanySpot       (void) ;

  protected:

    Ui::XcityOrganization * ui        ;
    ComboBox              * groups    ;
    QString                 Scope     ;
    Sql                     hunterSql ;

  private:

  public slots:

    virtual void prepare       (void) ;
    virtual void configure     (QString scope,Sql & sql) ;

  protected slots:

    void GroupChanged          (int index) ;
    void XcityValueChanged     (int index) ;
    void XcityJpChanged        (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT XcitySeeker : public SiteSeeker
{
  Q_OBJECT
  public:

    explicit          XcitySeeker     (QObject * parent,Plan * plan) ;
    virtual          ~XcitySeeker     (void) ;

    virtual int       Type            (void    ) const ;
    virtual QString   Name            (void    ) const ;
    virtual bool      Supported       (int type) const ;
    virtual QString   Name            (int type) const ;
    virtual QWidget * Configurator    (int type) ;

  protected:

    XcityPeople       * xcpeople       ;
    XcityVideo        * xcvideo        ;
    XcityOrganization * xcorganization ;

    QStringList     XcityPeoples      (QByteArray & XML,QString found) ;
    QString         XcityImageSrc     (QByteArray & XML,QString found) ;
    QString         XcityPeopleSrc    (QByteArray & XML,QString found) ;
    QString         XcityProduct      (QString product) ;
    bool            XcityDvdInfo      (QByteArray & XML,KMAPs & INFOs,int & index,NAMEs & References) ;
    QStringList     XcityDvdURLs      (QByteArray & XML,int & index) ;
    bool            XcityCompany      (QByteArray & XML,int index,QString & name,QString & logo) ;
    bool            UpdateXcity       (SqlConnection & SC,int PornstarId,SUID nuid,QString name) ;
    bool            UpdateXcityDvd    (SqlConnection & SC,int VideoId   ,SUID puid,QString name) ;
    virtual bool    BindPeople        (SqlConnection & SC        ,
                                       SUID            people    ,
                                       QString         name      ,
                                       QString         found     ,
                                       QByteArray   & XML      ) ;
    virtual QString MeasureString     (QString SRC,int index) ;

    bool     SkipPeople               (void) ;
    int      PeopleStart              (void) ;
    int      PeopleEnd                (void) ;
    SUID     NewbieUuid               (void) ;
    SUID     MergerUuid               (void) ;
    SUID     GalleryUuid              (void) ;
    QString  Search                   (QString name) ;
    QString  Missing                  (void) ;
    QString  Found                    (void) ;
    QString  IdFound                  (void) ;
    QString  IdPattern                (int Id) ;

    bool     SkipVideo                (void) ;
    bool     VideoCache               (void) ;
    int      VideoStart               (void) ;
    int      VideoEnd                 (void) ;
    SUID     AlbumUuid                (void) ;
    SUID     InterestUuid             (void) ;
    SUID     VideoGalleryUuid         (void) ;
    SUID     VideoNameMaps            (int index) ;
    QString  VideoSearch              (int Id) ;
    QString  VideoInfo                (void) ;
    QString  VideoGalleryString       (void) ;

    SUID     CompanyUuid              (void) ;
    QString  CompanyPath              (QString name) ;
    QString  CompanySpot              (void) ;

    virtual bool    Fetch             (SqlConnection & SC,QUrl url,SUID & zuid,QByteArray & XML) ;

  private:

  public slots:

    virtual bool      setEnabled      (int type,bool enable) ;
    virtual bool      prepare         (void) ;
    virtual bool      configure       (QString scope) ;
    virtual bool      startup         (int type) ;

  protected slots:

    virtual bool      RunPeople       (void) ;
    virtual bool      RunVideo        (void) ;
    virtual bool      RunOrganization (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT AupInfoPeople : public Widget
{
  Q_OBJECT
  public:
    explicit AupInfoPeople (StandardConstructor) ;
    virtual ~AupInfoPeople (void) ;

    bool     SkipExists    (void) ;
    int      PeopleStart   (void) ;
    int      PeopleEnd     (void) ;
    SUID     NewbieUuid    (void) ;
    SUID     MergerUuid    (void) ;
    SUID     GalleryUuid   (void) ;
    SUID     NameUuid      (int index) ;
    QString  Search        (void) ;
    QString  Actress       (void) ;
    bool     VerifyEnglish (void) ;

  protected:

    Ui::AupInfoPeople * ui          ;
    ComboBox          * newbie      ;
    ComboBox          * merger      ;
    ComboBox          * gallery     ;
    QString             Scope       ;
    Sql                 hunterSql   ;
    QTreeWidgetItem   * ItemEditing ;
    ComboBox          * Entries     ;

  private:

  public slots:

    virtual void prepare   (void) ;
    virtual void configure (QString scope,Sql & sql) ;

  protected slots:

    void NewbieChanged     (int index) ;
    void MergerChanged     (int index) ;
    void GalleryChanged    (int index) ;
    void AupValueChanged   (int index) ;
    void AupChanged        (void) ;

    void NameClicked       (QTreeWidgetItem * item,int column) ;
    void NameSelected      (int index) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT AupInfoVideo : public Widget
{
  Q_OBJECT
  public:

    explicit AupInfoVideo (StandardConstructor) ;
    virtual ~AupInfoVideo (void) ;

    bool     SkipExists    (void) ;
    bool     VideoCache    (void) ;
    int      VideoStart    (void) ;
    int      VideoEnd      (void) ;
    SUID     AlbumUuid     (void) ;
    SUID     InterestUuid  (void) ;
    SUID     GalleryUuid   (void) ;
    SUID     NameUuid      (int index) ;
    QString  Search        (void) ;

  protected:

    Ui::AupInfoVideo * ui ;
    ComboBox         * album       ;
    ComboBox         * interest    ;
    ComboBox         * gallery     ;
    QString            Scope       ;
    Sql                hunterSql   ;
    QTreeWidgetItem  * ItemEditing ;
    ComboBox         * Entries     ;

  private:

  public slots:

    virtual void prepare   (void) ;
    virtual void configure (QString scope,Sql & sql) ;

  protected slots:

    void AlbumChanged      (int index) ;
    void InterestChanged   (int index) ;
    void GalleryChanged    (int index) ;
    void AupValueChanged   (int index) ;
    void AupChanged        (void) ;

    void NameClicked       (QTreeWidgetItem * item,int column) ;
    void NameSelected      (int index) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT AupInfoSeeker : public SiteSeeker
{
  Q_OBJECT
  public:

    explicit          AupInfoSeeker (QObject * parent,Plan * plan) ;
    virtual          ~AupInfoSeeker (void) ;

    virtual int       Type          (void    ) const ;
    virtual QString   Name          (void    ) const ;
    virtual bool      Supported     (int type) const ;
    virtual QString   Name          (int type) const ;
    virtual QWidget * Configurator  (int type) ;

  protected:

    AupInfoPeople       * aupeople       ;
    AupInfoVideo        * auvideo        ;

    QStringList AupInfoPeoples      (QByteArray & XML,QString found) ;
    QString     AupInfoImageSrc     (QByteArray & XML,QString found) ;
    bool        BindAupInfo         (SqlConnection & SC         ,
                                     SUID            people     ,
                                     QString         name       ,
                                     QString         found      ,
                                     QByteArray    & XML      ) ;
    bool        UpdateAupPeople     (SqlConnection & SC         ,
                                     int             PornstarId ,
                                     SUID            nuid       ,
                                     QString         name     ) ;

    bool     SkipPeople             (void) ;
    bool     VerifyEnglish          (void) ;
    int      PeopleStart            (void) ;
    int      PeopleEnd              (void) ;
    SUID     NewbieUuid             (void) ;
    SUID     MergerUuid             (void) ;
    SUID     GalleryUuid            (void) ;
    SUID     PeopleNameMaps         (int index) ;
    QString  Search                 (int Id) ;
    QString  Actress                (void) ;

    bool     SkipVideo              (void) ;
    bool     VideoCache             (void) ;
    int      VideoStart             (void) ;
    int      VideoEnd               (void) ;
    SUID     AlbumUuid              (void) ;
    SUID     InterestUuid           (void) ;
    SUID     VideoGalleryUuid       (void) ;
    SUID     VideoNameMaps          (int index) ;
    QString  VideoSearch            (int Id) ;

    virtual bool Fetch              (SqlConnection & SC,QUrl url,SUID & zuid,QByteArray & XML) ;

  private:

  public slots:

    virtual bool      setEnabled    (int type,bool enable) ;
    virtual bool      prepare       (void) ;
    virtual bool      configure     (QString scope) ;
    virtual bool      startup       (int type) ;

  protected slots:

    virtual bool      RunPeople     (void) ;
    virtual bool      RunVideo      (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT JavTorrentVideo : public Widget
{
  Q_OBJECT
  public:

    explicit JavTorrentVideo (StandardConstructor) ;
    virtual ~JavTorrentVideo (void) ;

    virtual bool    Skip            (void) ;
    virtual bool    Cache           (void) ;
    virtual bool    DownloadOnly    (void) ;
    virtual bool    DontParse       (void) ;
    virtual bool    DownloadImage   (void) ;
    virtual bool    DownloadTorrent (void) ;
    virtual int     Lastest         (void) ;
    virtual int     Retry           (void) ;
    virtual SUID    AlbumUuid       (void) ;
    virtual SUID    InterestUuid    (void) ;
    virtual SUID    GalleryUuid     (void) ;
    virtual SUID    NameUuid        (int index) ;
    virtual QString Pattern         (void) ;
    virtual QString TorrentPattern  (void) ;
    virtual QString TorrentPath     (void) ;
    virtual QString Identifier      (void) ;

  protected:

    Ui::JavTorrentVideo * ui          ;
    ComboBox            * album       ;
    ComboBox            * interest    ;
    ComboBox            * gallery     ;
    QString               Scope       ;
    Sql                   hunterSql   ;
    QTreeWidgetItem     * ItemEditing ;
    ComboBox            * Entries     ;

  private:

  public slots:

    virtual void prepare            (void) ;
    virtual void configure          (QString scope,Sql & sql) ;

  protected slots:

    virtual void AlbumChanged       (int index) ;
    virtual void InterestChanged    (int index) ;
    virtual void GalleryChanged     (int index) ;
    virtual void JavTorrentValues   (int index) ;
    virtual void JavTorrentChanged  (void) ;
    virtual void BrowseTorrent      (void) ;

    virtual void NameClicked        (QTreeWidgetItem * item,int column) ;
    virtual void NameSelected       (int index) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT JavTorrent : public SiteSeeker
{
  Q_OBJECT
  public:

    explicit          JavTorrent       (QObject * parent,Plan * plan) ;
    virtual          ~JavTorrent       (void) ;

    virtual int       Type             (void    ) const ;
    virtual QString   Name             (void    ) const ;
    virtual bool      Supported        (int type) const ;
    virtual QString   Name             (int type) const ;
    virtual QWidget * Configurator     (int type) ;

  protected:

    JavTorrentVideo  * jtvideo  ;

    virtual bool      VideoSkip        (void) ;
    virtual bool      VideoCache       (void) ;
    virtual bool      DownloadOnly     (void) ;
    virtual bool      DontParse        (void) ;
    virtual bool      DownloadImage    (void) ;
    virtual bool      DownloadTorrent  (void) ;
    virtual int       VideoLastest     (void) ;
    virtual int       VideoRetry       (void) ;
    virtual SUID      AlbumUuid        (void) ;
    virtual SUID      InterestUuid     (void) ;
    virtual SUID      GalleryUuid      (void) ;
    virtual SUID      VideoNameMaps    (int index) ;
    virtual QString   Search           (int index) ;
    virtual QString   Torrent          (QString ID) ;
    virtual QString   TorrentPath      (QString CODE) ;
    virtual QString   Identifier       (void) ;
    virtual QString   Compact          (QString source) ;
    virtual bool      isLatin          (QString source) ;

    virtual bool      Fetch            (SqlConnection & SC    ,
                                        QUrl            url   ,
                                        SUID          & zuid  ,
                                        QByteArray    & XML ) ;
    virtual bool      Parse            (SqlConnection & SC      ,
                                        SqlConnection & HC      ,
                                        QUrl            url     ,
                                        int             PageId  ,
                                        SUID          & zuid    ,
                                        QByteArray    & XML     ,
                                        NAMEs         & INFOs   ,
                                        QStringList   & NewAV ) ;
    virtual int       FetchTags        (QByteArray    & XML     ,
                                        int             index   ,
                                        NAMEs         & INFOs   ,
                                        KMAPs         & TAGs  ) ;
    virtual int       FetchImages      (QByteArray    & XML     ,
                                        int             index   ,
                                        QList<QUrl>   & URLs  ) ;
    virtual int       FetchTorrents    (QByteArray    & XML     ,
                                        int             index   ,
                                        QList<QUrl>   & URLs  ) ;
    virtual bool      ObtainImage      (SqlConnection & Connection ,
                                        QUrl            url        ,
                                        SUID            puid       ,
                                        SUID          & ruid       ,
                                        SUID          & image    ) ;

  private:

  public slots:

    virtual bool      setEnabled   (int type,bool enable) ;
    virtual bool      prepare      (void) ;
    virtual bool      configure    (QString scope) ;
    virtual bool      startup      (int type) ;

  protected slots:

    virtual bool      RunVideo     (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT JavFreeVideo : public Widget
{
  Q_OBJECT
  public:

    explicit        JavFreeVideo    (StandardConstructor) ;
    virtual        ~JavFreeVideo    (void) ;

    virtual bool    Skip            (void) ;
    virtual bool    Cache           (void) ;
    virtual bool    DownloadOnly    (void) ;
    virtual bool    isProxy         (void) ;
    virtual int     Start           (void) ;
    virtual int     Finish          (void) ;
    virtual SUID    AlbumUuid       (void) ;
    virtual SUID    InterestUuid    (void) ;
    virtual SUID    GalleryUuid     (void) ;
    virtual SUID    NameUuid        (int index) ;
    virtual QString GZipLocation    (void) ;
    virtual QString Posting         (void) ;
    virtual QString Thumbnails      (void) ;

  protected:

    Ui::JavFreeVideo * ui          ;
    ComboBox         * album       ;
    ComboBox         * interest    ;
    ComboBox         * gallery     ;
    QString            Scope       ;
    Sql                hunterSql   ;
    QTreeWidgetItem  * ItemEditing ;
    ComboBox         * Entries     ;

  private:

  public slots:

    virtual void    prepare         (void) ;
    virtual void    configure       (QString scope,Sql & sql) ;

  protected slots:

    virtual void    AlbumChanged    (int index) ;
    virtual void    InterestChanged (int index) ;
    virtual void    GalleryChanged  (int index) ;
    virtual void    JavFreeValues   (int index) ;
    virtual void    JavFreeChanged  (void) ;
    virtual void    JavFreeBrowse   (void) ;

    virtual void    NameClicked     (QTreeWidgetItem * item,int column) ;
    virtual void    NameSelected    (int index) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT JavFree : public SiteSeeker
{
  Q_OBJECT
  public:

    explicit          JavFree       (QObject * parent,Plan * plan) ;
    virtual          ~JavFree       (void) ;

    virtual int       Type          (void    ) const ;
    virtual QString   Name          (void    ) const ;
    virtual bool      Supported     (int type) const ;
    virtual QString   Name          (int type) const ;
    virtual QWidget * Configurator  (int type) ;

    virtual bool      useProxy      (void) ;
    virtual QString   ProxyAddress  (void) ;
    virtual bool      setOptions    (Ftp & ftp) ;

  protected:

    JavFreeVideo  * jfvideo  ;
    bool            Proxying ;
    SymbolPool      Pool     ;

    virtual bool      VideoSkip     (void) ;
    virtual bool      VideoCache    (void) ;
    virtual bool      DownloadOnly  (void) ;
    virtual int       VideoStart    (void) ;
    virtual int       VideoEnd      (void) ;
    virtual SUID      AlbumUuid     (void) ;
    virtual SUID      InterestUuid  (void) ;
    virtual SUID      GalleryUuid   (void) ;
    virtual SUID      VideoNameMaps (int index) ;
    virtual QString   Search        (int index) ;
    virtual QString   Posting       (void) ;
    virtual QString   Thumbnails    (void) ;

    virtual bool      isProduct     (QString & product) ;

    virtual bool      ObtainPages   (QByteArray & XML,QList<QUrl> & URLs) ;

    virtual QString   GZipLocation  (void) ;

    virtual bool      Fetch         (SqlConnection & SC,QUrl url,SUID & zuid,QByteArray & XML) ;

    virtual int       FetchTags     (QByteArray  & XML    ,
                                     int           index  ,
                                     NAMEs       & INFOs  ,
                                     KMAPs       & TAGs ) ;
    virtual int       FetchImages   (QByteArray  & XML    ,
                                     int           index  ,
                                     QList<QUrl> & URLs ) ;

  private:

  public slots:

    virtual bool      setEnabled    (int type,bool enable) ;
    virtual bool      prepare       (void) ;
    virtual bool      configure     (QString scope) ;
    virtual bool      startup       (int type) ;

  protected slots:

    virtual bool      RunVideo      (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT OpPictures : public Widget
{
  Q_OBJECT
  public:

    explicit OpPictures    (QWidget * parent = NULL,Plan * plan = NULL) ;
    virtual ~OpPictures    (void) ;

    bool    isSkip         (void) ;
    bool    isCache        (void) ;
    bool    isVolume       (void) ;
    int     OpStart        (void) ;
    int     VolStart       (void) ;
    int     VolEnd         (void) ;
    QString OpRoot         (void) ;
    SUID    Gallery        (void) ;

  protected:

    Ui::OnePiecePictures * ui        ;
    ComboBox             * gallery   ;
    QString                Scope     ;
    Sql                    hunterSql ;

  private:

  public slots:

    virtual void prepare   (void) ;
    virtual void configure (QString scope,Sql & sql) ;

  protected slots:

    void GalleryChanged    (int index) ;
    void stateChanged      (int index) ;
    void OpChanged         (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT OnePiecePictures : public SiteSeeker
{
  Q_OBJECT
  public:

    explicit OnePiecePictures (QObject * parent,Plan * plan) ;
    virtual ~OnePiecePictures (void) ;

    virtual int       Type         (void    ) const ;
    virtual QString   Name         (void    ) const ;
    virtual bool      Supported    (int type) const ;
    virtual QString   Name         (int type) const ;
    virtual QWidget * Configurator (int type)       ;

  protected:

    OpPictures * opconf      ;
    bool         removeImage ;

    bool    isSkip                 (void) ;
    bool    isCache                (void) ;
    bool    isVolume               (void) ;
    int     OpStart                (void) ;
    int     VolStart               (void) ;
    int     VolEnd                 (void) ;
    QString OpRoot                 (void) ;
    SUID    Gallery                (void) ;

    virtual bool RemoveImage       (void) ;
    bool Fetch                     (SqlConnection & SC       ,
                                    QUrl            u        ,
                                    SUID          & puid     ,
                                    QByteArray    & XML    ) ;
    bool EachIssue                 (SqlConnection & SC       ,
                                    SqlConnection & HC       ,
                                    QString         Root     ,
                                    int             Issue    ,
                                    bool          & done     ,
                                    int             IDX      ,
                                    bool            volume ) ;
    int  LastestPage               (QByteArray    & XML    ) ;

  private:

  public slots:

    virtual bool      setEnabled   (int type,bool enable) ;
    virtual bool      prepare      (void) ;
    virtual bool      configure    (QString scope) ;
    virtual bool      startup      (int type) ;

  protected slots:

    virtual bool      RunPictures  (void) ;

  private slots:

  signals:

};

class Q_EXCITON_EXPORT PaintingSecretTools : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingSecretTools (StandardConstructor) ;
    virtual ~PaintingSecretTools (void);

    virtual QSize sizeHint       (void) const ;

  protected:

    Ui::PaintingSecretTools * ui ;

  private:

  public slots:

  protected slots:

  private:

  signals:

    void Encryption (void) ;
    void Decryption (void) ;
    void Depot      (void) ;
    void Settings   (void) ;
    void Quit       (void) ;

};

class Q_EXCITON_EXPORT PaintingSecretSurface : public QWidget
{
  Q_OBJECT
  public:

    QImage              Painting   ;
    QImage              Background ;
    QImage              Drawing    ;
    QProgressBar      * progress   ;
    ProgressIndicator * indicator  ;

    explicit PaintingSecretSurface (QWidget * parent) ;
    virtual ~PaintingSecretSurface (void) ;

  protected:

    QMutex Mutex ;

    virtual void showEvent   (QShowEvent   * event) ;
    virtual void resizeEvent (QResizeEvent * event) ;
    virtual void paintEvent  (QPaintEvent  * event) ;

  private:

    QImage       Cut         (void) ;
    void MoveIndicator       (void) ;

  public slots:

    virtual void relocation  (void) ;

    virtual void StartBusy   (N::Plan * plan,int total) ;
    virtual void StopBusy    (void) ;
    virtual void setStep     (int index) ;

  protected slots:

  private slots:

  signals:

};

class Q_EXCITON_EXPORT PaintingVendor : public PaintWidget
{
  Q_OBJECT
  public:

    explicit PaintingVendor    (StandardConstructor) ;
    virtual ~PaintingVendor    (void) ;

    virtual QSize sizeHint     (void) const ;

  protected:

    PaintingSecretTools * Tools  ;
    bool                  Docked ;

    virtual bool acceptTap     (QTapGesture        * gesture) ;
    virtual bool acceptTapHold (QTapAndHoldGesture * gesture) ;
    virtual bool acceptPan     (QPanGesture        * gesture) ;
    virtual bool acceptPinch   (QPinchGesture      * gesture) ;
    virtual bool acceptSwipe   (QSwipeGesture      * gesture) ;
    virtual bool acceptCustom  (QGesture           * gesture) ;

    virtual void Configure     (void) ;

  private:

    QImage       Cut           (void) ;

  public slots:

    virtual void relocation    (void) ;
    virtual void startup       (void) ;

  protected slots:

  private slots:

  signals:

    void Quit                  (void) ;
    void Encryption            (void) ;
    void Decryption            (void) ;
    void Depot                 (void) ;
    void Settings              (void) ;

};


class Q_EXCITON_EXPORT PaintingEncryptionTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingEncryptionTool (StandardConstructor) ;
    virtual ~PaintingEncryptionTool (void);

  protected:

    Ui::PaintingEncryptionTool * ui ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void Back    (void) ;
    void Files   (void) ;
    void Picture (void) ;
    void Key     (void) ;
    void Encrypt (void) ;

};

class Q_EXCITON_EXPORT PaintingDecryptionTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingDecryptionTool (StandardConstructor) ;
    virtual ~PaintingDecryptionTool (void) ;

  protected:

    Ui::PaintingDecryptionTool * ui ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void Back      (void) ;
    void Picture   (void) ;
    void Key       (void) ;
    void Decrypt   (void) ;

};

class Q_EXCITON_EXPORT PaintingDepotTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingDepotTool (StandardConstructor) ;
    virtual ~PaintingDepotTool (void) ;

  protected:

    Ui::PaintingDepotTool * ui ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void Back      (void) ;
    void List      (void) ;
    void Pictures  (void) ;
    void Keys      (void) ;
    void Encrypted (void) ;
    void Ftp       (void) ;

};

class Q_EXCITON_EXPORT PaintingSettingsTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingSettingsTool (StandardConstructor) ;
    virtual ~PaintingSettingsTool (void);

  protected:

    Ui::PaintingSettingsTool * ui ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void Back     (void) ;
    void Ftp      (void) ;
    void Language (void) ;
    void Fonts    (void) ;
    void Display  (void) ;
    void Help     (void) ;

};

class Q_EXCITON_EXPORT PaintingPickTool : public Widget
{
  Q_OBJECT
  public:

    bool canPick ;

    explicit PaintingPickTool (StandardConstructor) ;
    virtual ~PaintingPickTool (void);

  protected:

    Ui::PaintingPickTool * ui ;

  private:

  public slots:

    void Full                 (int index,bool full) ;
    void Empty                (void) ;
    void FileSelected         (QString path) ;

  protected slots:

  private slots:

  signals:

    void Back                 (void) ;
    void Pick                 (void) ;
    void View                 (void) ;
    void Previous             (void) ;
    void Next                 (void) ;
    void Import               (void) ;

};

class Q_EXCITON_EXPORT PaintingViewTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingViewTool (StandardConstructor) ;
    virtual ~PaintingViewTool (void);

  protected:

    Ui::PaintingViewTool * ui ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void Back                 (void) ;
    void ZoomIn               (void) ;
    void ZoomOut              (void) ;

};

class Q_EXCITON_EXPORT PaintingFilesTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingFilesTool (StandardConstructor) ;
    virtual ~PaintingFilesTool (void) ;

  protected:

    Ui::PaintingFilesTool * ui ;

  private:

  public slots:

    void setDeletion  (bool enable) ;
    void setPackaging (bool enable) ;

  protected slots:

  private slots:

  signals:

    void Back      (void) ;
    void New       (void) ;
    void Add       (void) ;
    void Remove    (void) ;
    void Packaging (void) ;

};

class Q_EXCITON_EXPORT PaintingFolderTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingFolderTool (StandardConstructor) ;
    virtual ~PaintingFolderTool (void) ;

  protected:

    Ui::PaintingFolderTool * ui ;

  private:

  public slots:

    void setSelected (int count) ;

  protected slots:

  private slots:

  signals:

    void Back     (void) ;
    void Join     (void) ;
    void Delete   (void) ;
    void Edit     (void) ;
    void Text     (void) ;
    void Recorder (void) ;

};

class Q_EXCITON_EXPORT PaintingFolderEdit : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingFolderEdit (StandardConstructor) ;
    virtual ~PaintingFolderEdit (void) ;

  protected:

    Ui::PaintingFolderEdit * ui ;

  private:

  public slots:

    void setSelected (int  count) ;
    void setEdit     (bool enable) ;

  protected slots:

  private slots:

  signals:

    void Back      (void) ;
    void Rename    (void) ;
    void Move      (void) ;
    void Directory (void) ;
    void Edit      (void) ;
    void Ftp       (void) ;

};

class Q_EXCITON_EXPORT PaintingTextTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingTextTool (StandardConstructor) ;
    virtual ~PaintingTextTool (void) ;

  protected:

    Ui::PaintingTextTool * ui ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void Back     (void) ;
    void New      (void) ;
    void Save     (void) ;

};

class Q_EXCITON_EXPORT PaintingAudioTool : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingAudioTool (StandardConstructor) ;
    virtual ~PaintingAudioTool (void) ;

  protected:

    Ui::PaintingAudioTool * ui ;

  private:

  public slots:

    void EnableNew   (bool enable) ;
    void EnableStart (bool enable) ;
    void EnableStop  (bool enable) ;

  protected slots:

  private slots:

  signals:

    void Back     (void) ;
    void New      (void) ;
    void Start    (void) ;
    void Stop     (void) ;

};

class Q_EXCITON_EXPORT PaintingFolderList : public Widget
{
  Q_OBJECT
  public:

    explicit PaintingFolderList (StandardConstructor) ;
    virtual ~PaintingFolderList (void) ;

  protected:

    Ui::PaintingFolderList * ui ;

    virtual void resizeEvent    (QResizeEvent * event) ;
    virtual void showEvent      (QShowEvent   * event) ;

    virtual void Configure      (void) ;

  private:

  public slots:

    virtual void relocation     (void) ;
    virtual void Back           (void) ;
    virtual void Go             (void) ;
    virtual void Folders        (bool topmost,QStringList folders) ;

  protected slots:

  private slots:

  signals:

    void CdUp                   (void) ;
    void Directory              (QString path) ;

};

class Q_EXCITON_EXPORT PaintingSecretGui : public Splitter
{
  Q_OBJECT
  public:

    QDir                     Root           ;
    QString                  QM             ;
    StackedWidget          * header         ;
    StackedWidget          * stack          ;
    StackedWidget          * menu           ;
    PaintingEncryptionTool * encrypt        ;
    PaintingDecryptionTool * decrypt        ;
    PaintingDepotTool      * depot          ;
    PaintingSettingsTool   * settings       ;
    PaintingPickTool       * srcPicture     ;
    PaintingPickTool       * keyPicture     ;
    PaintingPickTool       * getEncrypt     ;
    PaintingPickTool       * getKeyPic      ;
    PaintingPickTool       * viewImages     ;
    PaintingPickTool       * viewEncrypt    ;
    PaintingPickTool       * viewKeys       ;
    PaintingViewTool       * picTool        ;
    PaintingFilesTool      * fileTool       ;
    PaintingFolderTool     * folderTool     ;
    PaintingFolderEdit     * folderEdit     ;
    PaintingTextTool       * textTool       ;
    PaintingTextTool       * textEdit       ;
    PaintingAudioTool      * audioTool      ;
    PaintingFolderList     * folderList     ;
    VcfView                * vcf            ;
    FtpControl             * ftp            ;
    FontConfigurator       * fontconf       ;
    ScreenConfigurator     * screenconf     ;
    MdiArea                * mdi            ;
    QLabel                 * label          ;
    QProgressBar           * progress       ;
    PickPicture            * pickPicture    ;
    PickPicture            * pickEncrypt    ;
    PickPicture            * pickKey        ;
    TreeWidget             * pickLanguage   ;
    TextEdit               * encryptReport  ;
    TextEdit               * decryptReport  ;
    TextEdit               * depotReport    ;
    TextEdit               * plainText      ;
    LineEdit               * line           ;
    LineEdit               * lineRename     ;
    LineEdit               * lineMove       ;
    LineEdit               * lineDirectory  ;
    ArchiveList            * archive        ;
    ArchivePick            * pickArchive    ;
    WebBrowser             * help           ;
    SUID                     packaging      ;
    QString                  SourcePicture  ;
    QString                  KeyPicture     ;
    QString                  DecryptPicture ;
    QString                  DecryptKey     ;

    explicit PaintingSecretGui  (StandardConstructor) ;
    virtual ~PaintingSecretGui  (void) ;

    virtual QSize sizeHint      (void) const ;

    QString  LanguagePath       (QString filename) ;

  protected:

    QWidget * BackWidget  ;
    QWidget * BackMenu    ;
    QString   ReturnLabel ;
    bool      debug       ;

    virtual void resizeEvent    (QResizeEvent * event) ;
    virtual void showEvent      (QShowEvent   * event) ;

    virtual void Configure      (void) ;

    SUID         ObtainUuid     (void) ;

  private:

  public slots:

    virtual void relocation     (void) ;

    virtual void Encryption     (void) ;
    virtual void Decryption     (void) ;
    virtual void Depot          (void) ;
    virtual void Settings       (void) ;

    virtual void AndroidPathes  (void) ;
    virtual void ApplePathes    (void) ;
    virtual void InstallPathes  (void) ;
    virtual void BootupFtp      (void) ;

    void         DeletePath     (QDir & root,QStringList files) ;

  protected slots:

    virtual void MakeFile       (void) ;
    virtual void GetPicture     (void) ;
    virtual void PickKey        (void) ;
    virtual void DoEncrypt      (void) ;

    virtual void NewFile        (void) ;
    virtual void AddFile        (void) ;
    virtual void RemoveFile     (void) ;
    virtual void CreatePackage  (void) ;
    virtual void FileSelected   (void) ;

    virtual void FolderJoin     (void) ;
    virtual void FolderDelete   (void) ;
    virtual void FolderEdit     (void) ;
    virtual void FolderText     (void) ;
    virtual void FolderRecorder (void) ;
    virtual void FolderListing  (void) ;
    virtual void FolderReady    (void) ;
    virtual void FolderSelected (void) ;
    virtual void FolderMenu     (void) ;

    virtual void SaveText       (void) ;

    virtual void DataPicture    (void) ;
    virtual void DataKey        (void) ;
    virtual void DoDecrypt      (void) ;

    virtual void DepotList      (void) ;
    virtual void DepotPictures  (void) ;
    virtual void DepotKeys      (void) ;
    virtual void DepotEncrypted (void) ;
    virtual void DepotFtp       (void) ;

    virtual void Sharing        (void) ;
    virtual void Fonts          (void) ;
    virtual void Language       (void) ;
    virtual void Display        (void) ;
    virtual void Help           (void) ;

    virtual void FileRename     (void) ;
    virtual void FileMove       (void) ;
    virtual void FileDirectory  (void) ;
    virtual void EditText       (void) ;
    virtual void BackEdit       (void) ;
    virtual void NewEdit        (void) ;
    virtual void SaveEdit       (void) ;
    virtual void FileFtp        (void) ;

    virtual void RenameAction   (void) ;
    virtual void MoveAction     (void) ;
    virtual void DirectoryAction(void) ;
    virtual void FolderBack     (void) ;

  private slots:

    void FileSelected           (QString path) ;
    void ViewPicture            (void) ;
    void ReturnPick             (void) ;
    void ViewEncrypted          (void) ;
    void ReturnEncrypted        (void) ;
    void ViewKeys               (void) ;
    void ReturnKeys             (void) ;
    void ViewDepot              (void) ;
    void ReturnDepot            (void) ;
    void ObtainPic              (void) ;
    void ObtainKey              (void) ;
    void ObtainEncrypted        (void) ;
    void ObtainKeys             (void) ;
    void ImportPicture          (void) ;
    void ImportKey              (void) ;
    void ImportEncrypted        (void) ;
    void ImportKeys             (void) ;
    void ListLanguage           (void) ;
    void languageClicked        (QTreeWidgetItem * item,int column) ;

  signals:

    void Back                   (void) ;
    void Recording              (QString path) ;
    void Obtain                 (QString path) ;
    void Transfer               (QString path) ;
    void FullFtp                (void) ;
    void FullDepot              (void) ;
    void Manual                 (void) ;
    void NewText                (QDir root,QDir current) ;
    void LoadText               (QDir root,QDir current,QString filename) ;

};

}

Q_EXCITON_EXPORT extern int    PaintingSecretsMain(int argc,char ** argv) ;
Q_EXCITON_EXPORT extern void * psLocaleDirectories ;

class Q_EXCITON_EXPORT PaintingSecrets : public N::MobileMain
{
  Q_OBJECT
  public:

    explicit PaintingSecrets (int argc,char ** argv,QWidget * parent = NULL) ;
    virtual ~PaintingSecrets (void);

  protected:

    Ui :: PaintingSecrets       * ui         ;
    N  :: PaintingVendor        * master     ;
    N  :: PaintingSecretGui     * secret     ;
    N  :: IconDock              * settings   ;
    N  :: ScreenConfigurator    * screenconf ;
    N  :: FontConfigurator      * fontconf   ;
    N  :: PaintingSecretSurface * vendor     ;
    N  :: PadEditor             * editor     ;
    N  :: PadRecorder           * recorder   ;
    N  :: PadBrowser            * browser    ;
    N  :: PadBrowser            * folder     ;
    N  :: PadFtp                * ftp        ;

    virtual void InstallFonts  (double defaultSize = 0.40) ;

  private:

    int steps ;

    void LoadSupports          (N::Languages & L) ;

  public slots:

    virtual int  abort         (void) ;
    virtual bool Shutdown      (void) ;
    virtual bool TurnOff       (void) ;

    virtual bool bootup        (void) ;
    virtual bool prepare       (void) ;
    virtual bool configure     (void) ;
    virtual bool loading       (void) ;
    virtual bool brand         (void) ;
    virtual bool advertising   (void) ;
    virtual bool primary       (void) ;

    virtual void Quit          (void) ;
    virtual void Hide          (void) ;
    virtual void Settings      (void) ;
    virtual void Start         (void) ;
    virtual void Stop          (void) ;
    virtual void showLogo      (void) ;
    virtual void logoPage      (void) ;
    virtual void adPage        (void) ;
    virtual void Actual        (void) ;

    void Encryption            (void) ;
    void Decryption            (void) ;
    void Depot                 (void) ;
    void Front                 (void) ;

  protected slots:

    virtual void Nextstep      (void) ;

    void BackSecrets           (void) ;
    void Recording             (QString path) ;
    void Obtain                (QString path) ;
    void Transfer              (QString path) ;
    void FullFtp               (void) ;
    void FullDepot             (void) ;
    void Manual                (void) ;
    void NewText               (QDir root,QDir current) ;
    void LoadText              (QDir root,QDir current,QString filename) ;
    void DropFiles             (QStringList files) ;
    void PickFiles             (void) ;

  private slots:

  signals:

};

namespace N
{

class Q_EXCITON_EXPORT Manifests   ;
class Q_EXCITON_EXPORT CiosMain    ;

class Q_EXCITON_EXPORT Manifests : public TreeWidget
                                 , public Object
{
  Q_OBJECT
  public:

    typedef enum    {
      Inventory = 0 ,
      CheckItem = 1 }
      ManifestTypes ;

    Sql           Book    ;
    Qt::SortOrder Sorting ;

    explicit Manifests            (ManifestTypes mType,StandardConstructor) ;
    virtual ~Manifests            (void) ;

  protected:

    ManifestTypes CheckType ;

    virtual void InstallDecisions (void) ;
    virtual void Configure        (void) ;
    virtual bool FocusIn          (void) ;
    virtual bool FocusOut         (void) ;
    virtual void run              (int Type,ThreadData * Data) ;

    virtual void mousePressEvent  (QMouseEvent * event) ;
    virtual bool acceptTap        (QTapGesture        * gesture) ;
    virtual bool acceptTapHold    (QTapAndHoldGesture * gesture) ;
    virtual bool acceptPan        (QPanGesture        * gesture) ;
    virtual bool acceptPinch      (QPinchGesture      * gesture) ;
    virtual bool acceptSwipe      (QSwipeGesture      * gesture) ;
    QString      CreateManifest   (QString table) ;

  private:

  public slots:

    virtual bool startup          (void) ;
    virtual bool startup          (QString name,SUID uuid) ;
    virtual void GainFocus        (void) ;

    virtual void Go               (void) ;
    virtual void InsertInventory  (void) ;
    virtual void DeleteInventory  (void) ;
    virtual void RenameInventory  (void) ;
    virtual void Insert           (void) ;
    virtual void Delete           (void) ;
    virtual void Rename           (void) ;

    virtual void CheckInventory   (void) ;
    virtual void ListInventory    (void) ;
    virtual void VerifyItems      (void) ;
    virtual void ListItems        (void) ;

  protected slots:

    virtual void CheckButtons     (void) ;

    virtual void doubleClicked    (QTreeWidgetItem *item, int column) ;
    virtual void nameFinished     (void) ;
    virtual void itemFinished     (void) ;

  private slots:

  signals:

    void         Edit             (nDeclWidget,QString name,SUID uuid) ;

};

class Q_EXCITON_EXPORT CiosMain : public CommonMain
{
  Q_OBJECT
  public:

    explicit CiosMain (int argc,char ** argv,QWidget * parent) ;
    virtual ~CiosMain (void) ;

  protected:

  private:

  public slots:

  protected slots:

  private slots:

  signals:

};

}

QT_END_NAMESPACE

#endif
