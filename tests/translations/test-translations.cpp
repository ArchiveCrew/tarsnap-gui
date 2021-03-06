#include "warnings-disable.h"

WARNINGS_DISABLE
#include <QCoreApplication>
#include <QObject>
#include <QTest>
WARNINGS_ENABLE

#include "../qtest-platform.h"

#include "TPathComboBrowse.h"
#include "TSettings.h"

#include "translator.h"

class TestTranslations : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void pathcombobrowse();
};

void TestTranslations::initTestCase()
{
    QCoreApplication::setOrganizationName(TEST_NAME);

    // Use a custom message handler to filter out unwanted messages
    IF_NOT_VISUAL { qInstallMessageHandler(offscreenMessageOutput); }

    // Initialize the translator.
    Translator::initializeTranslator();
}

void TestTranslations::cleanupTestCase()
{
    Translator::destroy();
    TSettings::destroy();

    // Wait up to 5 seconds to delete objects scheduled with ->deleteLater()
    WAIT_FINAL;
}

void TestTranslations::pathcombobrowse()
{
    TPathComboBrowse *pcb = new TPathComboBrowse();

    VISUAL_INIT(pcb);

    // We can't (easily) access the label for the "Browse" button,
    // so this mainly a "does it crash?" test, although there will
    // also be cases where I want to run it manually.

    global_translator->translateApp(qApp, "Romanian");
    VISUAL_WAIT;

    global_translator->translateApp(qApp, "English");
    VISUAL_WAIT;

    delete pcb;
}

QTEST_MAIN(TestTranslations)
WARNINGS_DISABLE
#include "test-translations.moc"
WARNINGS_ENABLE
