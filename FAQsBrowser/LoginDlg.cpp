#include "LoginDlg.h"
#include "RegistrationDlg.h"
#include "Connection.h"
#include "MainWindow.h"
#include "OptionsDlg.h"

#include <QCryptographicHash>
#include <QCloseEvent>
#include <QDebug>
#include <QTimer>
#include <QDesktopServices>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    ui.labelMessage->hide();

    connect(ui.btLogin,     SIGNAL(clicked(bool)),  this, SLOT(onLogin()));
    connect(ui.btRegister,  SIGNAL(clicked(bool)),  this, SLOT(onRegister()));
    connect(ui.btHelp,      SIGNAL(clicked(bool)),  this, SLOT(onHelp()));
    connect(ui.btOptions,   SIGNAL(clicked()),      this, SLOT(onOptions()));

    Connection* connection = Connection::getInstance();
    connect(connection, SIGNAL(loginReply(bool)),  this, SLOT(onLoginReply(bool)));
    connect(connection, SIGNAL(serverAlive(bool)), this, SLOT(onServerAlive(bool)));
}

QString LoginDlg::getUserName() const {
    return ui.leUserName->text();
}

QString LoginDlg::getEncrytedPassword() const {
    return QCryptographicHash::hash(ui.lePassword->text().toUtf8(), QCryptographicHash::Md5);
}

void LoginDlg::closeEvent(QCloseEvent*) {
    qApp->quit();
}

void LoginDlg::onLogin()
{
    if (!getUserName().isEmpty() && !getEncrytedPassword().isEmpty())
        Connection::getInstance()->login(getUserName(), getEncrytedPassword());
}

void LoginDlg::onLoginReply(bool successful)
{
    if (successful)
    {
        accept();
        MainWindow* mainWindow = new MainWindow;
        mainWindow->showMaximized();
        mainWindow->setUserName(getUserName());
    }
    else {
        showMessage(tr("Login failed!"), true);
    }
}

void LoginDlg::onHelp() {
    QDesktopServices::openUrl(QUrl("mailto:congchenutd@gmail.com?subject=Need help with COFAQs"));
}

void LoginDlg::onOptions()
{
    OptionsDlg dlg(this);
    dlg.exec();
}

void LoginDlg::onServerAlive(bool alive)
{
    if (!alive)
        showMessage(tr("Server is unavailable!"), true);

    ui.btLogin   ->setEnabled(alive);
    ui.btRegister->setEnabled(alive);
}

void LoginDlg::showMessage(const QString& message, bool error)
{
    ui.labelMessage->setText(message);
    ui.labelMessage->show();

    QPalette palette = ui.labelMessage->palette();
    palette.setColor(ui.labelMessage->foregroundRole(), error? Qt::red : Qt::black);
    ui.labelMessage->setPalette(palette);
}

void LoginDlg::onRegister()
{
    RegistrationDlg dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        ui.leUserName->setText(dlg.getUserName());
        ui.lePassword->setText(dlg.getPlainTextPassword());
        onLogin();
    }
}

