#include "ClientHandler.h"
#include "Settings.h"
#include "qhttpserver.hpp"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

#include <QCoreApplication>

using namespace qhttp::server;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    Settings* settings = Settings::getInstance();
    QHttpServer server(&app);
    server.listen(QHostAddress::Any, settings->getServerPort(), [&](QHttpRequest* req, QHttpResponse* res) {
            new ClientHandler(req, res);
    });

    if (server.isListening())
        qDebug() << "FAQsServer running on port" << settings->getServerPort();
    else
        return -1;

    return app.exec();
}
