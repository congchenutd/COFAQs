#include "LoginDlg.h"
#include "RegistrationDlg.h"
#include "Connection.h"

#include <QCryptographicHash>
#include <QCloseEvent>
#include <QDebug>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

    // message label
    ui.labelMessage->hide();
    QPalette palette = ui.labelMessage->palette();
    palette.setColor(ui.labelMessage->foregroundRole(), Qt::red);
    ui.labelMessage->setPalette(palette);

    connect(ui.btLogin,     SIGNAL(clicked(bool)), this, SLOT(onLogin()));
    connect(ui.btRegister,  SIGNAL(clicked(bool)), this, SLOT(onRegister()));
    connect(ui.btQuit,      SIGNAL(clicked(bool)), qApp, SLOT(quit()));
    connect(Connection::getInstance(), SIGNAL(loginReply(bool)), this, SLOT(onLoginReply(bool)));
}

QString LoginDlg::getUserName() const {
    return ui.leUserName->text();
}

QString LoginDlg::getEncrytedPassword() const {
    return QCryptographicHash::hash(ui.lePassword->text().toUtf8(), QCryptographicHash::Md5);
}

void LoginDlg::closeEvent(QCloseEvent* event) {
    event->ignore();
}

void LoginDlg::onLogin()
{
    if (!getUserName().isEmpty() && !getEncrytedPassword().isEmpty())
    {
        Connection::getInstance()->login(getUserName(), getEncrytedPassword());
    }
}

void LoginDlg::onLoginReply(bool successful)
{
    if (successful)
        accept();
    else
    {

    }
}

void LoginDlg::onRegister()
{
    RegistrationDlg dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        ui.leUserName->setText(dlg.getUserName());
        ui.lePassword->setText(dlg.getEncryptedPassword());
        onLogin();
    }
}

