#ifndef PATHCOMBOBROWSE_H
#define PATHCOMBOBROWSE_H

#include <QWidget>

/* Forward declaration. */
namespace Ui
{
class PathComboBrowse;
}

/*!
 * \ingroup lib-widgets
 * \brief The PathComboBrowse is a QWidget which consists of a QLabel, a
 * QComboBox, and a QPushButton to trigger a QFileDialog to select a path.
 */
class PathComboBrowse : public QWidget
{
    Q_OBJECT

    //! Text of the QLabel.
    Q_PROPERTY(QString label READ label WRITE setLabel)
    //! Placeholder text for the QComboBox.
    Q_PROPERTY(
        QString placeholderText READ placeholderText WRITE setPlaceholderText)
    //! Title of the QFileDialog.
    Q_PROPERTY(QString dialogTitle READ dialogTitle WRITE setDialogTitle)
    //! Filter of the QFileDialog.
    Q_PROPERTY(QString dialogFilter READ dialogFilter WRITE setDialogFilter)

public:
    //! Constructor.
    explicit PathComboBrowse(QWidget *parent = nullptr);
    ~PathComboBrowse();

    //! Get the label text.
    QString label() const;
    //! Set the label text.
    void setLabel(const QString &text);

    //! Get the placeholder text of the QComboBox.
    QString placeholderText() const;
    //! Set the text of the QComboBox.
    void setPlaceholderText(const QString &text);

    //! Get the title of the QFileDialog.
    QString dialogTitle() const;
    //! Set the title of the QFileDialog.
    void setDialogTitle(const QString &text);

    //! Get the filter of the QFileDialog.
    QString dialogFilter() const;
    //! Set the filter of the QFileDialog.
    void setDialogFilter(const QString &text);

    //! Get the text of the QComboBox.
    QString text() const;

    //! Get the number of items in the QComboBox.
    int count() const;
    //! Add an item to the QComboBox.
    void addItem(const QString &text);

public slots:
    //! Set the text of the QComboBox.
    void setText(const QString &text);
    //! Clear the text of the QComboBox.
    void clear();

signals:
    //! The text of the QComboBox has changed.
    void textChanged(const QString &text);

private slots:
    void browseClicked();

private:
    Ui::PathComboBrowse *_ui;

    QString _dialogTitle;
    QString _dialogFilter;
};

#endif /* !PATHCOMBOBROWSE_H */