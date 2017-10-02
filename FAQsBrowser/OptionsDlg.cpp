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

    // load settings
    Settings* settings = Settings::getInstance();
    ui.leServerIP       ->setText(settings->getServerIP());
    ui.leServerPort     ->setText(QString::number(settings->getServerPort()));
    ui.btFont           ->setFont(settings->getFont());
    ui.radioGoogle->setChecked(settings->getSearchEngine() == "Google");
    ui.radioBaidu ->setChecked(settings->getSearchEngine() == "Baidu");

    Connection* connection = Connection::getInstance();
    connect(connection, SIGNAL(serverAlive(bool)),  this, SLOT(onServerAlive(bool)));
    connect(ui.btFont,  SIGNAL(clicked()),          this, SLOT(onFont()));

    onServerAlive(connection->isServerAlive());
}

void OptionsDlg::accept()
{
    // save settings
    Settings* settings = Settings::getInstance();
    settings->setServerIP   (ui.leServerIP  ->text());
    settings->setServerPort (ui.leServerPort->text().toInt());
    settings->setFont       (ui.btFont      ->font());
    settings->setSearchEngine(ui.radioGoogle->isChecked() ? "Google" : "Baidu");

    QDialog::accept();
}

void OptionsDlg::onPingServer() {
    Connection::getInstance()->ping();
}

void OptionsDlg::onServerAlive(bool alive) {
    ui.labelServerStatus->setText(alive ? tr("Server is available :)")
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
