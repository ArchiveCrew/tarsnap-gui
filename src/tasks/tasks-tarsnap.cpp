#include "tasks-tarsnap.h"

WARNINGS_DISABLE
#include <QStringList>
WARNINGS_ENABLE

#include "TSettings.h"

#include "persistentmodel/archive.h"

#include "backuptask.h"
#include "tasks-defs.h"
#include "tasks-utils.h"

TarsnapTask *listArchivesTask()
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    args << "--list-archives"
         << "-vv";

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *printStatsTask(const QString &archiveName)
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    args << "--print-stats"
         << "--no-humanize-numbers"
         << "-f" << archiveName;

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *archiveContentsTask(const QString &archiveName)
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    TSettings settings;
    if(settings.value("tarsnap/preserve_pathnames", DEFAULT_PRESERVE_PATHNAMES)
           .toBool())
        args << "-P";
    args << "-tv"
         << "-f" << archiveName;

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *deleteArchivesTask(const QStringList &archiveNames)
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    args << "--print-stats"
         << "-d";
    for(const QString &archiveName : archiveNames)
        args << "-f" << archiveName;

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *overallStatsTask()
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    args << "--print-stats"
         << "--no-humanize-numbers";

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *nukeArchivesTask()
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    args << "--nuke";
    task->setStdIn("No Tomorrow\n");

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *restoreArchiveTask(const QString &       archiveName,
                                ArchiveRestoreOptions options)
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    if(options.optionRestore)
    {
        TSettings settings;
        args << "-x"
             << "-P"
             << "-C"
             << settings.value("app/downloads_dir", DEFAULT_DOWNLOADS)
                    .toString();
    }
    if(options.optionRestoreDir)
    {
        args << "-x"
             << "-C" << options.path;
    }
    if((options.optionRestore || options.optionRestoreDir))
    {
        if(!options.overwriteFiles)
            args << "-k";
        if(options.keepNewerFiles)
            args << "--keep-newer-files";
        if(options.preservePerms)
            args << "-p";
    }
    if(options.optionTarArchive)
    {
        args << "-r";
        task->setStdOutFile(options.path);
    }
    if(!options.files.isEmpty())
    {
        args << "-T"
             << "-";
        task->setStdIn(options.files.join(QChar('\n')));
    }
    args << "-f" << archiveName;

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *backupArchiveTask(BackupTaskDataPtr backupTaskData)
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    TSettings settings;
    if(settings
           .value("tarsnap/aggressive_networking",
                  DEFAULT_AGGRESSIVE_NETWORKING)
           .toBool())
        args << "--aggressive-networking";
    if(backupTaskData->optionDryRun())
        args << "--dry-run";
    if(backupTaskData->optionSkipNoDump())
        args << "--nodump";
    if(backupTaskData->optionPreservePaths())
        args << "-P";
    if(!backupTaskData->optionTraverseMount())
        args << "--one-file-system";
    if(backupTaskData->optionFollowSymLinks())
        args << "-L";
    args << "--creationtime"
         << QString::number(backupTaskData->timestamp().toTime_t());
    args << "--quiet"
         << "--print-stats"
         << "--no-humanize-numbers"
         << "-c"
         << "-f" << backupTaskData->name();
    for(const QString &exclude : backupTaskData->getExcludesList())
        args << "--exclude" << exclude;
    for(const QUrl &url : backupTaskData->urls())
        args << url.toLocalFile();

    /* Generic setup. */
    task->setCommand(makeTarsnapCommand());
    task->setArguments(args);
    return (task);
}

TarsnapTask *keyIdTask(const QString &key_filename)
{
    TarsnapTask *task = new TarsnapTask();
    QStringList  args = makeTarsnapArgs();

    /* Specific arguments. */
    task->setCommand(makeTarsnapCommand("tarsnap-keymgmt"));
    args << "--print-key-id" << key_filename;

    /* Generic setup. */
    task->setArguments(args);
    return (task);
}