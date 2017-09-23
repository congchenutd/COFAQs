#ifndef REGISTRATIONDLG_H
#define REGISTRATIONDLG_H

#include "ui_RegistrationDlg.h"

class RegistrationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDlg(QWidget* parent = 0);

    QString getFirstName()  const;
    QString getLastName()   const;
    QString getUserName()   const;
    QString getEncryptedPassword()   const;

private slots:
    void onSubmit();
    void onRegistrationResult(bool result);

private:
    void showMessage(const QString& message);

private:
    Ui::RegistrationDlg ui;
};

#endif // REGISTRATIONDLG_H
