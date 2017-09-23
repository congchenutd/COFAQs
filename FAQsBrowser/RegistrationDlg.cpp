#include "RegistrationDlg.h"
#include "Connection.h"
#include <QTimer>
#include <QPalette>
#include <QCryptographicHash>

RegistrationDlg::RegistrationDlg(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

    // message label
    ui.labelMessage->hide();
    QPalette palette = ui.labelMessage->palette();
    palette.setColor(ui.labelMessage->foregroundRole(), Qt::red);
    ui.labelMessage->setPalette(palette);

    connect(ui.btSubmit, SIGNAL(clicked(bool)), this, SLOT(onSubmit()));
    connect(Connection::getInstance(), SIGNAL(registrationReply(bool)), this, SLOT(onRegistrationResult(bool)));
}

QString RegistrationDlg::getFirstName() const {
    return ui.leFirstName->text();
}

QString RegistrationDlg::getLastName() const {
   return ui.leLastName->text();
}

QString RegistrationDlg::getUserName() const {
    return ui.leUserName->text();
}

QString RegistrationDlg::getEncryptedPassword() const {
    return QCryptographicHash::hash(ui.lePassword->text().toUtf8(), QCryptographicHash::Md5);
}

void RegistrationDlg::onSubmit()
{
    if (getUserName().isEmpty())
    {
        showMessage(tr("User name cannot be empty!"));
        return;
    }

    if (getFirstName().isEmpty())
    {
        showMessage(tr("First name cannot be empty!"));
        return;
    }

    if (getLastName().isEmpty())
    {
        showMessage(tr("Last name cannot be empty!"));
        return;
    }

    if (getEncryptedPassword().isEmpty())
    {
        showMessage(tr("Password cannot be empty!"));
        return;
    }

    if (getEncryptedPassword() != ui.lePassword2->text())
    {
        showMessage(tr("Passwords do not match!"));
        return;
    }

    Connection::getInstance()->registration(getUserName(), getEncryptedPassword(), getFirstName(), getLastName());
}

void RegistrationDlg::onRegistrationResult(bool result)
{
    if (result)
    {
        accept();
    }
    else
    {
        showMessage(tr("Registration failed! The user name %1 already exists.").arg(getUserName()));
    }
}

void RegistrationDlg::showMessage(const QString& message)
{
    ui.labelMessage->setText(message);
    ui.labelMessage->show();

    QTimer::singleShot(2000, ui.labelMessage, SLOT(hide()));
}
