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

private slots:
    void onLogin();
    void onRegister();
    void onLoginReply(bool successful);
    void onQuit();

private:
    void showMessage(const QString& message);

private:
    Ui::LoginDlg ui;
};

#endif // LOGINDLG_H
