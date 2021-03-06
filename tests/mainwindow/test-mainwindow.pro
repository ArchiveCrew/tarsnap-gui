TARGET = test-mainwindow
QT = core gui widgets network sql

VALGRIND = true

# For TarsnapAccount
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

FORMS +=							\
	../../forms/aboutwidget.ui				\
	../../forms/archivelistwidgetitem.ui			\
	../../forms/archivestabwidget.ui			\
	../../forms/archivewidget.ui				\
	../../forms/backuplistwidgetitem.ui			\
	../../forms/backuptabwidget.ui				\
	../../forms/consolewidget.ui				\
	../../forms/filepickerdialog.ui				\
	../../forms/filepickerwidget.ui				\
	../../forms/helpwidget.ui				\
	../../forms/joblistwidgetitem.ui			\
	../../forms/jobstabwidget.ui				\
	../../forms/jobwidget.ui				\
	../../forms/logindialog.ui				\
	../../forms/mainwindow.ui				\
	../../forms/restoredialog.ui				\
	../../forms/settingswidget.ui				\
	../../forms/stoptasksdialog.ui

RESOURCES +=						\
	../../lib/resources/lib-resources.qrc		\
	../../resources/resources.qrc

HEADERS  +=						\
	../../lib/core/ConsoleLog.h			\
	../../lib/core/TSettings.h			\
	../../lib/widgets/TBusyLabel.h			\
	../../lib/widgets/TElidedLabel.h		\
	../../lib/widgets/TTextView.h			\
	../../src/archivefilestat.h			\
	../../src/backuptask.h				\
	../../src/basetask.h				\
	../../src/customfilesystemmodel.h		\
	../../src/dirinfotask.h				\
	../../src/filetablemodel.h			\
	../../src/parsearchivelistingtask.h		\
	../../src/persistentmodel/archive.h		\
	../../src/persistentmodel/job.h			\
	../../src/persistentmodel/persistentobject.h	\
	../../src/persistentmodel/persistentstore.h	\
	../../src/scheduling.h				\
	../../src/tarsnapaccount.h			\
	../../src/tasks/tasks-utils.h			\
	../../src/translator.h				\
	../../src/utils.h				\
	../../src/widgets/archivelistwidget.h		\
	../../src/widgets/archivelistwidgetitem.h	\
	../../src/widgets/archivestabwidget.h		\
	../../src/widgets/archivewidget.h		\
	../../src/widgets/backuplistwidget.h		\
	../../src/widgets/backuplistwidgetitem.h	\
	../../src/widgets/backuptabwidget.h		\
	../../src/widgets/confirmationdialog.h		\
	../../src/widgets/elidedannotatedlabel.h	\
	../../src/widgets/elidedclickablelabel.h	\
	../../src/widgets/filepickerdialog.h		\
	../../src/widgets/filepickerwidget.h		\
	../../src/widgets/helpwidget.h			\
	../../src/widgets/joblistwidget.h		\
	../../src/widgets/joblistwidgetitem.h		\
	../../src/widgets/jobstabwidget.h		\
	../../src/widgets/jobwidget.h			\
	../../src/widgets/mainwindow.h			\
	../../src/widgets/popuppushbutton.h		\
	../../src/widgets/restoredialog.h		\
	../../src/widgets/schedulingwidgets.h		\
	../../src/widgets/settingswidget.h		\
	../../src/widgets/stoptasksdialog.h		\
	../../src/widgets/tarsnapaccountdialog.h	\
	../../tests/qtest-platform.h

SOURCES += test-mainwindow.cpp				\
	../../lib/core/ConsoleLog.cpp			\
	../../lib/core/TSettings.cpp			\
	../../lib/widgets/TBusyLabel.cpp		\
	../../lib/widgets/TElidedLabel.cpp		\
	../../lib/widgets/TTextView.cpp			\
	../../src/backuptask.cpp			\
	../../src/basetask.cpp				\
	../../src/customfilesystemmodel.cpp		\
	../../src/dirinfotask.cpp			\
	../../src/filetablemodel.cpp			\
	../../src/parsearchivelistingtask.cpp		\
	../../src/persistentmodel/archive.cpp		\
	../../src/persistentmodel/job.cpp		\
	../../src/persistentmodel/persistentobject.cpp	\
	../../src/persistentmodel/persistentstore.cpp	\
	../../src/scheduling.cpp			\
	../../src/tarsnapaccount.cpp			\
	../../src/tasks/tasks-utils.cpp			\
	../../src/translator.cpp			\
	../../src/utils.cpp				\
	../../src/widgets/archivelistwidget.cpp		\
	../../src/widgets/archivelistwidgetitem.cpp	\
	../../src/widgets/archivestabwidget.cpp		\
	../../src/widgets/archivewidget.cpp		\
	../../src/widgets/backuplistwidget.cpp		\
	../../src/widgets/backuplistwidgetitem.cpp	\
	../../src/widgets/backuptabwidget.cpp		\
	../../src/widgets/confirmationdialog.cpp	\
	../../src/widgets/elidedannotatedlabel.cpp	\
	../../src/widgets/elidedclickablelabel.cpp	\
	../../src/widgets/filepickerdialog.cpp		\
	../../src/widgets/filepickerwidget.cpp		\
	../../src/widgets/helpwidget.cpp		\
	../../src/widgets/joblistwidget.cpp		\
	../../src/widgets/joblistwidgetitem.cpp		\
	../../src/widgets/jobstabwidget.cpp		\
	../../src/widgets/jobwidget.cpp			\
	../../src/widgets/mainwindow.cpp		\
	../../src/widgets/popuppushbutton.cpp		\
	../../src/widgets/restoredialog.cpp		\
	../../src/widgets/schedulingwidgets.cpp		\
	../../src/widgets/settingswidget.cpp		\
	../../src/widgets/stoptasksdialog.cpp		\
	../../src/widgets/tarsnapaccountdialog.cpp

include(../tests-include.pro)

test_home_prep.commands += ; mkdir -p "$${TEST_HOME}/$${TARGET}";	\
	cp -r confdir/* "$${TEST_HOME}/$${TARGET}"
