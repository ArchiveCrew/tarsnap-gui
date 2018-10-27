#ifndef BACKUPTABWIDGET_H
#define BACKUPTABWIDGET_H

#include "ui_backuptabwidget.h"

#include <QEvent>
#include <QWidget>

/*!
 * \ingroup widgets-main
 * \brief The BackupTabWidget is a QWidget which shows the list of jobs.
 */
class BackupTabWidget : public QWidget
{
    Q_OBJECT

#ifdef QT_TESTLIB_LIB
    friend class TestBackupTabWidget;
#endif

public:
    //! Constructor.
    explicit BackupTabWidget(QWidget *parent = nullptr);

    //! Does the Backup have a name?
    bool validateBackupTab();

    //! Can we make a backup now?
    void backupTabValidStatus(bool valid);

    // Temp for refactoring
    QString temp_lineText() { return _ui.backupNameLineEdit->text(); }
    void    temp_uncheck_timestamped()
    {
        _ui.appendTimestampCheckBox->setChecked(false);
    }

public slots:
    // Will be private after refactoring
    void updateBackupItemTotals(quint64 count, quint64 size);

signals:
    void backupButtonClicked();
    void backupMorphIntoJobClicked();

protected:
    //! Handles translation change of language.
    void changeEvent(QEvent *event);

private slots:
    void appendTimestampCheckBoxToggled(bool checked);

private:
    Ui::BackupTabWidget _ui;

    QString _lastTimestamp;

    void updateUi();
};

#endif // BACKUPTABWIDGET_H