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
    void closeEvent(QCloseEvent* event);

private slots:
    void onLogin();
    void onRegister();
    void onLoginReply(bool successful);

private:
    Ui::LoginDlg ui;
};

#endif // LOGINDLG_H
