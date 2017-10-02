#include "TextEditToQIODeviceAdapter.h"
#include "Window.h"

#include <QMenu>
#include <QMessageBox>
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
    menu->addAction("About",        this, SLOT(onAbout()));
    menu->addAction("Show window",  this, SLOT(show()));
    menu->addAction("Quit",         this, SLOT(onQuit()));

    _tray = new QSystemTrayIcon(this);
    _tray->setIcon(QIcon(":/Server.png"));
    _tray->setContextMenu(menu);
    _tray->show();

    connect(ui.btClose, &QPushButton::clicked,          this, &Window::hide);
    connect(ui.btQuit,  &QPushButton::clicked,          this, &Window::onQuit);
    connect(_tray,      &QSystemTrayIcon::activated,    this, &Window::onTrayActivated);

    // redirect qdebug log to a text edit
    Logger::setDevice(new TextEditToQIODeviceAdapter(ui.teLog, "./Log.txt", this));
    DAO::getInstance()->createTables();

    // Start the server
    Settings* settings = Settings::getInstance();
    QHttpServer* server = new QHttpServer(qApp);
    server->listen(QHostAddress::Any, settings->getServerPort(), [&](QHttpRequest* req, QHttpResponse* res) {
        new ClientHandler(req, res);
    });

    Logger* logger = Logger::getInstance();
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

void Window::onAbout()
{
    QMessageBox::about(this, tr("About"),
                       tr("<h3><b>FAQs Server v0.2.2</b></h3>"
                          "<p><a href=mailto:CongChenUTD@Gmail.com>CongChenUTD@Gmail.com</a></p>"));
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

void Window::onTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
        show();
}
