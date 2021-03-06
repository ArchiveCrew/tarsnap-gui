TARGET = test-taskmanager
QT = core sql network

VALGRIND = true

HEADERS  +=						\
	../../lib/core/ConsoleLog.h			\
	../../lib/core/TSettings.h			\
	../../src/archivefilestat.h			\
	../../src/backenddata.h				\
	../../src/backuptask.h				\
	../../src/basetask.h				\
	../../src/cmdlinetask.h				\
	../../src/dirinfotask.h				\
	../../src/jobrunner.h				\
	../../src/parsearchivelistingtask.h		\
	../../src/persistentmodel/archive.h		\
	../../src/persistentmodel/job.h			\
	../../src/persistentmodel/persistentobject.h	\
	../../src/persistentmodel/persistentstore.h	\
	../../src/taskmanager.h				\
	../../src/taskqueuer.h				\
	../../src/tasks/tasks-defs.h			\
	../../src/tasks/tasks-misc.h			\
	../../src/tasks/tasks-setup.h			\
	../../src/tasks/tasks-tarsnap.h			\
	../../src/tasks/tasks-utils.h			\
	../../src/utils.h				\
	../qtest-platform.h

SOURCES += test-taskmanager.cpp				\
	../../lib/core/ConsoleLog.cpp			\
	../../lib/core/TSettings.cpp			\
	../../src/backenddata.cpp			\
	../../src/backuptask.cpp			\
	../../src/basetask.cpp				\
	../../src/cmdlinetask.cpp			\
	../../src/dirinfotask.cpp			\
	../../src/jobrunner.cpp				\
	../../src/parsearchivelistingtask.cpp		\
	../../src/persistentmodel/archive.cpp		\
	../../src/persistentmodel/job.cpp		\
	../../src/persistentmodel/persistentobject.cpp	\
	../../src/persistentmodel/persistentstore.cpp	\
	../../src/taskmanager.cpp			\
	../../src/taskqueuer.cpp			\
	../../src/tasks/tasks-misc.cpp			\
	../../src/tasks/tasks-setup.cpp			\
	../../src/tasks/tasks-tarsnap.cpp		\
	../../src/tasks/tasks-utils.cpp			\
	../../src/utils.cpp

include(../tests-include.pro)

test_home_prep.commands += ; mkdir -p "$${TEST_HOME}/$${TARGET}";	\
	mkdir -p "$${TEST_HOME}/$${TARGET}/cachedir";			\
	touch "$${TEST_HOME}/$${TARGET}/cachedir/stuff"
