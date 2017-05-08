#include <QApplication>
#include "Window.h"

#include "ClientHandler.h"
#include "Settings.h"
#include "qhttpserver.hpp"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

using namespace qhttp::server;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

//    Settings* settings = Settings::getInstance();
//    QHttpServer server(&app);
//    server.listen(QHostAddress::Any, settings->getServerPort(), [&](QHttpRequest* req, QHttpResponse* res) {
//        new ClientHandler(req, res);
//    });

    Window window;
    window.show();

    return app.exec();
}
