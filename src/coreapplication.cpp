#include "coreapplication.h"
#include "widgets/setupdialog.h"
#include "debug.h"
#include "utils.h"

#include <QMessageBox>
#include <QDialog>
#include <QFontDatabase>

CoreApplication::CoreApplication(int &argc, char **argv):
    QApplication(argc, argv), _mainWindow(NULL), _jobsOption(false)
{
    qRegisterMetaType< TaskStatus >("TaskStatus");
    qRegisterMetaType< QList<QUrl> >("QList<QUrl>");
    qRegisterMetaType< BackupTaskPtr >("BackupTaskPtr");
    qRegisterMetaType< QList<ArchivePtr > >("QList<ArchivePtr >");
    qRegisterMetaType< ArchivePtr >("ArchivePtr");
    qRegisterMetaType< ArchiveRestoreOptions >("ArchiveRestoreOptions");
    qRegisterMetaType< QSqlQuery >("QSqlQuery");
    qRegisterMetaType< JobPtr >("JobPtr");
    qRegisterMetaType< QMap<QString, JobPtr> >("QMap<QString, JobPtr>");

    QCoreApplication::setOrganizationName(QLatin1String("Tarsnap Backup Inc."));
    QCoreApplication::setOrganizationDomain(QLatin1String("tarsnap.com"));
    QCoreApplication::setApplicationName(QLatin1String("Tarsnap"));
    QCoreApplication::setApplicationVersion(APP_VERSION);
}

CoreApplication::~CoreApplication()
{
    if(_mainWindow)
        delete _mainWindow;
}

void CoreApplication::parseArgs()
{
    QCommandLineParser parser;
    parser.setApplicationDescription(QLatin1String("Tarsnap GUI - Online backups for the truly lazy"));
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption jobsOption(QStringList() << "j" << "jobs",
                                  tr("Executes all jobs sequentially that have the \'Include in scheduled backups\' option checked."
                                     " The application runs headless and useful information is printed to standard out and error."));
    QCommandLineOption appDataOption(QStringList() << "a" << "appdata",
                                    tr("Use the specified app data directory."
                                       " Useful for multiple configurations on the same machine (INI format is implied)."),
                                    tr("directory"));
    parser.addOption(jobsOption);
    parser.addOption(appDataOption);
    parser.process(arguments());
    _jobsOption = parser.isSet(jobsOption);
    _appDataDir = parser.value(appDataOption);
}

bool CoreApplication::initialize()
{
    parseArgs();

    QSettings settings;

    if(!_appDataDir.isEmpty())
    {
        settings.setPath(QSettings::IniFormat, QSettings::UserScope, _appDataDir);
        settings.setDefaultFormat(QSettings::IniFormat);
    }

    bool wizardDone = settings.value("app/wizard_done", false).toBool();
    if(!wizardDone)
    {
        // Show the first time setup dialog
        SetupDialog wizard;
        connect(&wizard, SIGNAL(getTarsnapVersion(QString)) , &_taskManager,
                SLOT(getTarsnapVersion(QString)));
        connect(&_taskManager, SIGNAL(tarsnapVersion(QString)), &wizard,
                SLOT(setTarsnapVersion(QString)));
        connect(&wizard, SIGNAL(registerMachine(QString, QString, QString, QString, QString, QString))
                , &_taskManager, SLOT(registerMachine(QString, QString, QString, QString, QString, QString)));
        connect(&_taskManager, SIGNAL(registerMachineStatus(TaskStatus, QString)) , &wizard
                , SLOT(registerMachineStatus(TaskStatus, QString)));
        connect(&_taskManager, SIGNAL(idle(bool)), &wizard, SLOT(updateLoadingAnimation(bool)), QUEUED);

        if(QDialog::Rejected == wizard.exec())
        {
            quit(); // if we're running in the loop
            return false; // if called from main
        }
    }

    bool iniFormat = settings.value("app/ini_format", false).toBool();
    if(iniFormat)
    {
        QString appData = settings.value("app/app_data", APPDATA).toString();
        settings.setPath(QSettings::IniFormat, QSettings::UserScope, appData);
        settings.setDefaultFormat(QSettings::IniFormat);
    }

    QMetaObject::invokeMethod(&_taskManager, "loadSettings", QUEUED);

    if(_jobsOption)
        QMetaObject::invokeMethod(&_taskManager, "runScheduledJobs", QUEUED);
    else
        showMainWindow();

    return true;
}

void CoreApplication::showMainWindow()
{
    _mainWindow = new MainWindow();
    Q_ASSERT(_mainWindow != NULL);

    connect(_mainWindow, SIGNAL(getTarsnapVersion(QString)) , &_taskManager,
            SLOT(getTarsnapVersion(QString)));
    connect(&_taskManager, SIGNAL(tarsnapVersion(QString)), _mainWindow,
            SLOT(setTarsnapVersion(QString)));
    connect(_mainWindow, SIGNAL(backupNow(BackupTaskPtr)), &_taskManager
            , SLOT(backupNow(BackupTaskPtr)), QUEUED);
    connect(_mainWindow, SIGNAL(loadArchives()), &_taskManager
            , SLOT(loadArchives()), QUEUED);
    connect(&_taskManager, SIGNAL(archiveList(QList<ArchivePtr>, bool))
            , _mainWindow, SIGNAL(archiveList(QList<ArchivePtr>, bool)), QUEUED);
    connect(_mainWindow, SIGNAL(deleteArchives(QList<ArchivePtr>)), &_taskManager,
            SLOT(deleteArchives(QList<ArchivePtr>)), QUEUED);
    connect(&_taskManager, SIGNAL(archivesDeleted(QList<ArchivePtr>)), _mainWindow
            , SLOT(archivesDeleted(QList<ArchivePtr>)), QUEUED);
    connect(_mainWindow, SIGNAL(loadArchiveStats(ArchivePtr)), &_taskManager
            , SLOT(getArchiveStats(ArchivePtr)), QUEUED);
    connect(_mainWindow, SIGNAL(loadArchiveContents(ArchivePtr)), &_taskManager
            , SLOT(getArchiveContents(ArchivePtr)), QUEUED);
    connect(&_taskManager, SIGNAL(idle(bool)), _mainWindow
            , SLOT(updateLoadingAnimation(bool)), QUEUED);
    connect(_mainWindow, SIGNAL(getOverallStats()), &_taskManager
            , SLOT(getOverallStats()), QUEUED);
    connect(&_taskManager, SIGNAL(overallStats(quint64, quint64, quint64, quint64, quint64))
            , _mainWindow, SLOT(updateSettingsSummary(quint64, quint64, quint64, quint64, quint64)), QUEUED);
    connect(_mainWindow, SIGNAL(repairCache()), &_taskManager
            , SLOT(fsck()), QUEUED);
    connect(&_taskManager, SIGNAL(fsckStatus(TaskStatus, QString)), _mainWindow
            , SLOT(repairCacheStatus(TaskStatus, QString)), QUEUED);
    connect(_mainWindow, SIGNAL(settingsChanged()), &_taskManager
            , SLOT(loadSettings()), QUEUED);
    connect(_mainWindow, SIGNAL(purgeArchives()), &_taskManager
            , SLOT(nuke()), QUEUED);
    connect(&_taskManager, SIGNAL(nukeStatus(TaskStatus, QString)), _mainWindow
            , SLOT(purgeArchivesStatus(TaskStatus, QString)), QUEUED);
    connect(_mainWindow, SIGNAL(restoreArchive(ArchivePtr, ArchiveRestoreOptions))
            , &_taskManager, SLOT(restoreArchive(ArchivePtr, ArchiveRestoreOptions))
            , QUEUED);
    connect(&_taskManager, SIGNAL(restoreArchiveStatus(ArchivePtr, TaskStatus, QString)), _mainWindow
            , SLOT(restoreArchiveStatus(ArchivePtr, TaskStatus, QString)), QUEUED);
    connect(_mainWindow, SIGNAL(runSetupWizard()), this, SLOT(reinit()), QUEUED);
    connect(_mainWindow, SIGNAL(stopTasks()), &_taskManager, SLOT(stopTasks()), QUEUED);
    connect(_mainWindow, SIGNAL(loadJobs()), &_taskManager, SLOT(loadJobs()), QUEUED);
    connect(&_taskManager, SIGNAL(jobsList(QMap<QString, JobPtr>))
            , _mainWindow, SIGNAL(jobsList(QMap<QString, JobPtr>)), QUEUED);
    connect(_mainWindow, SIGNAL(deleteJob(JobPtr, bool)), &_taskManager, SLOT(deleteJob(JobPtr, bool)), QUEUED);
    connect(&_taskManager, SIGNAL(message(QString, QString)), _mainWindow, SLOT(updateStatusMessage(QString, QString)), QUEUED);
    _mainWindow->show();
    _mainWindow->initialize();
}

bool CoreApplication::reinit()
{
    if(_mainWindow)
    {
        delete _mainWindow;
        _mainWindow = NULL;
    }

    // reset existing persistent store and app settings
    PersistentStore &store = PersistentStore::instance();
    store.purge();

    QSettings settings;
    settings.setDefaultFormat(QSettings::NativeFormat);
    QSettings defaultSettings;
    if(defaultSettings.contains("app/wizard_done"))
    {
        defaultSettings.clear();
        defaultSettings.sync();
    }

    return initialize();
}

