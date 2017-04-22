#include "ClientHandler.h"
#include "DAO.h"
#include "SnippetCreator.h"
#include "Settings.h"

#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>
#include <QDebug>
#include <QFile>
#include <QDir>

ClientHandler::ClientHandler(QHttpRequest* req, QHttpResponse* res)
    : QObject(req)
{
    // automatically collect http body(data) up to 10MB
    req->collectData(10*1024*1024);

    // when all the incoming data are gathered, send some response to client.
    req->onEnd([this, req, res]()
    {
        qDebug() << "Received request: " << qhttp::Stringify::toString(req->method()) << req->url().toString();

        QString url = req->url().toString();
        if(!url.startsWith("/?action"))
        {
            processStaticResourceRequest(url, res);
            return;
        }

        url.remove(0, 2);  // remove "/?"
        Parameters params = parseParameters(url);   // parameters in the request
        QString action = params["action"];
        if(action == "ping")
            processPingRequest(params, res);
        else if(action == "save")
            processSaveRequest(params, res);
        else if(action == "logapi")
            processLogDocumentReadingRequest(params, res);
        else if(action == "loganswer")
            processLogAnswerClickingRequest(params, res);
        else if(action == "query")
            processQueryRequest(params, res);
        else if(action == "personal")
            processQueryUserProfileRequest(params, res);
        else if(action == "submitphoto")
        {
            QByteArray data = req->collectedData();
            processSubmitPhotoRequest(params, req, res);
        }
    });
}

/**
 * Parse a request URL and get its parameters
 * e.g., the URL is XXX/?action=query&apisig=YYY
 * @param url   - the URL
 * @return      - a Parameters object
 */
ClientHandler::Parameters ClientHandler::parseParameters(const QString& url) const
{
    Parameters result;
    if(url.isEmpty())
        return result;

    QStringList sections = url.split("&");
    if(sections.length() == 0)
        return result;

    foreach(const QString& section, sections)
        result.insert(section.section('=', 0,  0),   // left part of the 1st =
                      section.section('=', 1, -1));  // right of the =

    return result;
}

/**
 * Process ping request and respond with a pong
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::processPingRequest(const Parameters& params, QHttpResponse* res)
{
    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    QString userName = params.contains("username") ? params["username"] : "anonymous";
    res->write(tr("Hello %1, I'm alive!").arg(userName).toUtf8());
    res->end();
}

/**
 * Process saving FAQ request
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::processSaveRequest(const Parameters& params, QHttpResponse* res)
{
    // link and title may contain percentage encoded reserved chars, such as & < > #
    // convert them back to human readable chars
    DAO::getInstance()->save(params["username"],
                             params["email"],
                             params["apisig"],
                             params["question"],
                             QUrl::fromPercentEncoding(params["link"] .toUtf8()),
                             QUrl::fromPercentEncoding(params["title"].toUtf8()));

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Your FAQ is saved").toUtf8());
    res->end();
}

/**
 * Process log document reading request
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::processLogDocumentReadingRequest(const Parameters& params, QHttpResponse* res)
{
    DAO::getInstance()->logDocumentReading(
            params["username"],
            params["email"],
            params["apisig"]);

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Your API is logged").toUtf8());
    res->end();
}

/**
 * Process log answer clicking request
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::processLogAnswerClickingRequest(const Parameters& params, QHttpResponse* res)
{
    // link may contain percentage encoded reserved chars, such as & < > #
    // convert them back to human readable chars
    DAO::getInstance()->logAnswerClicking(
            params["username"],
            params["email"],
            QUrl::fromPercentEncoding(params["link"] .toUtf8()));

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Your Answer is logged").toUtf8());
    res->end();
}

/**
 * Process query FAQs request
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::processQueryRequest(const Parameters& params, QHttpResponse* res)
{
    QJsonArray jaFAQs = DAO::getInstance()->queryFAQs(params["class"]).array();
    if(jaFAQs.isEmpty())   // returned is a json array
        return;
    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    QJsonDocument jdSnippet = SnippetCreator().createFAQs(jaFAQs);  // create html, encapsulated in a json doc
    res->write(jdSnippet.toJson());
    res->end();
}

/**
 * Process query user profile request
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::processQueryUserProfileRequest(const Parameters& params, QHttpResponse* res)
{
    QJsonDocument json = DAO::getInstance()->queryUserProfile(params["username"]);
    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(SnippetCreator().createProfilePage(json.object()));
    res->end();
}

/**
 * Process user photo submission
 * @param params
 * @param res
 */
void ClientHandler::processSubmitPhotoRequest(const Parameters& params, QHttpRequest* req, QHttpResponse* res)
{
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write("Photo received.");
    res->end();

    QDir::current().mkdir("Photos");
    QString userName = params["username"];
    QFile file("./Photos/" + userName + ".png");
    if(file.open(QFile::WriteOnly))
        file.write(req->collectedData());
}

/**
 * Process static web page request
 * @param url   - requested URL
 * @param res   - response
 */
void ClientHandler::processStaticResourceRequest(const QString& url, QHttpResponse* res)
{
    QFile file("." + url);
    if(file.open(QFile::ReadOnly))  // open the local file and send it back
    {
        res->setStatusCode(qhttp::ESTATUS_OK);
        res->write(file.readAll());
    }
    else {
        res->setStatusCode(qhttp::ESTATUS_NOT_FOUND);
    }
    res->end();
}
