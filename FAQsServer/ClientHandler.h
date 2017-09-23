#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include "qhttpserver.hpp"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

using namespace qhttp::server;

class DAO;

class ClientHandler : public QObject
{
    typedef QMap<QString, QString> Parameters;   // parameter name -> parameter value, e.g., username=Carl

public:
    explicit ClientHandler(QHttpRequest* req, QHttpResponse* res);

private:
    Parameters parseParameters(const QString& url) const;
    void onRegistration     (const Parameters& params, QHttpResponse* res);
    void onPing             (const Parameters& params, QHttpResponse* res);
    void onLogin            (const Parameters& params, QHttpResponse* res);
    void onLogout           (const Parameters& params, QHttpResponse* res);
    void onOpenDocument     (const Parameters& params, QHttpResponse* res);
    void onCloseDocument    (const Parameters& params, QHttpResponse* res);
    void onOpenSearch       (const Parameters& params, QHttpResponse* res);
    void onCloseSearch      (const Parameters& params, QHttpResponse* res);
    void onOpenResult       (const Parameters& params, QHttpResponse* res);
    void onCloseResult      (const Parameters& params, QHttpResponse* res);
    void onRateAnswer       (const Parameters& params, QHttpResponse* res);
    void onOpenAnswer       (const Parameters& params, QHttpResponse* res);
    void onCloseAnswer      (const Parameters& params, QHttpResponse* res);
    void onQueryFAQs        (const Parameters& params, QHttpResponse* res);
    void onQueryUserProfile (const Parameters& params, QHttpResponse* res);
    void onSubmitPhoto      (const Parameters& params, QHttpRequest* req, QHttpResponse* res);
    void onStaticResource   (const QString& url, QHttpResponse* res);

private:
    DAO* _dao;
};

#endif // CLIENTHANDLER_H
