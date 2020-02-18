#ifndef SETUPWIZARD_FINAL_H
#define SETUPWIZARD_FINAL_H

#include <TWizardPage.h>

/* Forward declaration. */
namespace Ui
{
class FinalPage;
}

/**
 * \ingroup widgets-setup
 * \brief The FinalPage is a TWizardPage which tells the user
 * about their keyfile.
 */
class FinalPage : public TWizardPage
{
    Q_OBJECT

public:
    //! Constructor.
    FinalPage(QWidget *parent = nullptr);
    ~FinalPage() override;

    //! Initialize the page when it first becomes visible.
    void initializePage() override;

#ifdef QT_TESTLIB_LIB
    Ui::FinalPage *get_ui() const { return _ui; }
#endif

private:
    Ui::FinalPage *_ui;
};

#endif /* !SETUPWIZARD_FINAL_H */