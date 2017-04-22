#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include "qhttpserver.hpp"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

using namespace qhttp::server;

class ClientHandler : public QObject
{
    typedef QMap<QString, QString> Parameters;   // parameter name -> parameter value, e.g., username=Carl

public:
    explicit ClientHandler(QHttpRequest* req, QHttpResponse* res);

private:
    Parameters parseParameters(const QString& url) const;
    void processPingRequest                 (const Parameters& params, QHttpResponse* res);
    void processSaveRequest                 (const Parameters& params, QHttpResponse* res);
    void processLogDocumentReadingRequest   (const Parameters& params, QHttpResponse* res);
    void processLogAnswerClickingRequest    (const Parameters& params, QHttpResponse* res);
    void processQueryRequest                (const Parameters& params, QHttpResponse* res);
    void processQueryUserProfileRequest     (const Parameters& params, QHttpResponse* res);
    void processSubmitPhotoRequest          (const Parameters& params, QHttpRequest* req, QHttpResponse* res);
    void processStaticResourceRequest(const QString& url, QHttpResponse* res);
};

#endif // CLIENTHANDLER_H
