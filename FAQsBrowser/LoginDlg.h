#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "ui_LoginDlg.h"

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget* parent = 0);
    QString getUserName() const;
    QString getEncrytedPassword() const;

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void onLogin();
    void onRegister();
    void onLoginReply(bool successful);
    void onHelp();
    void onOptions();
    void onServerAlive(bool alive);

private:
    void showMessage(const QString& message, bool error = false);

private:
    Ui::LoginDlg ui;
};

#endif // LOGINDLG_H
