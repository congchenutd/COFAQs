#include "TextEditToQIODeviceAdapter.h"
#include "Window.h"

#include <QMenu>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include "DAO.h"

#include "ClientHandler.h"
#include "Settings.h"
#include "qhttpserver.hpp"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

Window::Window(QWidget* parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    setAttribute(Qt::WA_QuitOnClose, false);

    QMenu* menu = new QMenu(this);
    menu->addAction("Show window",  this, SLOT(show()));
    menu->addAction("Quit",         this, SLOT(onQuit()));

    _tray = new QSystemTrayIcon(this);
    _tray->setIcon(QIcon(":/Server.png"));
    _tray->setContextMenu(menu);
    _tray->show();

    connect(ui.btClose, SIGNAL(clicked()), SLOT(hide()));
    connect(ui.btQuit,  SIGNAL(clicked()), SLOT(onQuit()));

    Logger* logger = new Logger(new TextEditToQIODeviceAdapter(ui.teLog, this));
    DAO::getInstance()->setLogger(logger);

    // Start the server
    Settings* settings = Settings::getInstance();
    QHttpServer* server = new QHttpServer(qApp);
    server->listen(QHostAddress::Any, settings->getServerPort(), [&](QHttpRequest* req, QHttpResponse* res) {
        new ClientHandler(req, res);
    });

    if (server->isListening())
        *logger << "FAQsServer is running on port " << settings->getServerPort() << endl;
    else
        *logger << "FAQsServer failed to start on port " << settings->getServerPort() << endl;
}

void Window::closeEvent(QCloseEvent* event)
{
    hide();
    event->ignore();
}

void Window::onQuit()
{
    if (QMessageBox::warning(this, tr("Warning"), tr("Are you sure to quit?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        qApp->quit();
    else if (!isVisible())   // WORKAROUND: otherwise the app will quit if window is hidden and the user clicks "No"
    {
        show();
        hide();
    }
}
