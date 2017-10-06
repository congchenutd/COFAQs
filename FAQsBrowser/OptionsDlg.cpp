#include "OptionsDlg.h"
#include "Connection.h"
#include "Settings.h"

#include <QFontDialog>
#include <QDebug>
#include <QTimer>

OptionsDlg::OptionsDlg(QWidget* parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    ui.labelMessage->hide();

    // load settings
    Settings* settings = Settings::getInstance();
    ui.leServerIP       ->setText(settings->getServerIP());
    ui.leServerPort     ->setText(QString::number(settings->getServerPort()));
    ui.btFont           ->setFont(settings->getFont());
    ui.radioGoogle->setChecked(settings->getSearchEngine() == "Google");
    ui.radioBaidu ->setChecked(settings->getSearchEngine() == "Baidu");

    Connection* connection = Connection::getInstance();
    connect(connection,     SIGNAL(serverAlive(bool)),          this, SLOT(onServerAlive(bool)));
    connect(connection,     SIGNAL(changePasswordReply(bool)),  this, SLOT(onChangePasswordResult(bool)));
    connect(ui.btFont,      SIGNAL(clicked()),                  this, SLOT(onFont()));
    connect(ui.btSubmit,    SIGNAL(clicked()),                  this, SLOT(onChangePassword()));

    onServerAlive(connection->isServerAlive());
}

void OptionsDlg::accept()
{
    // save settings
    Settings* settings = Settings::getInstance();
    settings->setServerIP       (ui.leServerIP  ->text());
    settings->setServerPort     (ui.leServerPort->text().toInt());
    settings->setFont           (ui.btFont      ->font());
    settings->setSearchEngine   (ui.radioGoogle->isChecked() ? "Google" : "Baidu");

    QDialog::accept();
}

void OptionsDlg::onPingServer() {
    Connection::getInstance()->ping();
}

void OptionsDlg::onServerAlive(bool alive) {
    showMessage(alive ? tr("Server is available :)")
                      : tr("Server is not available :("));
}

void OptionsDlg::onFont()
{
    Settings* settings = Settings::getInstance();
    bool ok;
    QFont font = QFontDialog::getFont(&ok, settings->getFont(), this);
    if(ok)
        ui.btFont->setFont(font);
}

void OptionsDlg::onChangePassword()
{
    if (ui.leUserName->text().isEmpty())
    {
        showMessage(tr("User name cannot be empty!"));
        return;
    }

    if (ui.leOldPassword ->text().isEmpty())
    {
        showMessage(tr("Old password cannot be empty!"));
        return;
    }

    if (ui.leNewPassword ->text().isEmpty() ||
        ui.leNewPassword2->text().isEmpty() ||
        ui.leNewPassword->text() != ui.leNewPassword2->text())
    {
        showMessage(tr("Passwords do not match!"));
        return;
    }

    Connection::getInstance()->changePassword(ui.leUserName->text(),
                                              Connection::getEncrytedPassword(ui.leOldPassword->text()),
                                              Connection::getEncrytedPassword(ui.leNewPassword->text()));
}

void OptionsDlg::onChangePasswordResult(bool successful) {
    showMessage(successful ? tr("Your password is successfully changed.")
                           : tr("Failed to change your password!"));
}

void OptionsDlg::showMessage(const QString& message)
{
    ui.labelMessage->setText(message);
    ui.labelMessage->show();
}
