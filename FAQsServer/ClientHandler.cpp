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
    _dao = DAO::getInstance();

    // automatically collect http body(data) up to 10MB
    req->collectData(10*1024*1024);

    // when all the incoming data are gathered, send some response to client.
    req->onEnd([this, req, res]()
    {
        qDebug() << "Received request: " << qhttp::Stringify::toString(req->method()) << req->url().toString();

        QString url = req->url().toString();
        if(!url.startsWith("/?action"))
        {
            onStaticResource(url, res);
            return;
        }

        url.remove(0, 2);  // remove "/?"
        Parameters params = parseParameters(url);   // parameters in the request
        QString action = params["action"];
        if(action == "ping")
            onPing(params, res);
        else if (action == "opendoc")
            onOpenDocument(params, res);
        else if (action == "closedoc")
            onCloseDocument(params, res);
        else if (action == "opensearch")
            onOpenSearch(params, res);
        else if (action == "closesearch")
            onCloseSearch(params, res);
        else if (action == "openresult")
            onOpenResult(params, res);
        else if (action == "closeresult")
            onCloseResult(params, res);
        else if (action == "rateanswer")
            onRateAnswer(params, res);
        else if (action == "answerclicking")
            onAnswerClicking(params, res);
        else if(action == "queryfaqs")
            onQueryFAQs(params, res);
        else if(action == "profile")
            onQueryUserProfile(params, res);
        else if(action == "submitphoto")
        {
            QByteArray data = req->collectedData();
            onSubmitPhoto(params, req, res);
        }
    });
}

/**
 * Parse a request URL and get its parameters
 * e.g., the URL is in the form of XXX/?action=query&apisig=YYY
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
void ClientHandler::onPing(const Parameters& params, QHttpResponse* res)
{
    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    QString userName = params.contains("username") ? params["username"] : "anonymous";
    res->write(tr("Hello %1, I'm alive!").arg(userName).toUtf8());
    res->end();
}

/**
 * Log start document reading
 */
void ClientHandler::onOpenDocument(const ClientHandler::Parameters &params, QHttpResponse *res)
{
    _dao->logOpenDocument(
            params["username"],
            params["email"],
            params["apisig"]);

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Document reading start is logged").toUtf8());
    res->end();
}

/**
 * Log end document reading
 */
void ClientHandler::onCloseDocument(const ClientHandler::Parameters &params, QHttpResponse *res)
{
    _dao->logCloseDocument(
            params["username"],
            params["email"],
            params["apisig"]);

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Document reading end is logged").toUtf8());
    res->end();
}

void ClientHandler::onOpenSearch(const Parameters& params, QHttpResponse* res)
{
    _dao->logOpenSearch(
            params["username"],
            params["email"],
            params["apisig"],
            params["question"]);

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Search start is logged").toUtf8());
    res->end();
}

void ClientHandler::onCloseSearch(const Parameters& params, QHttpResponse* res)
{
    _dao->logCloseSearch(
            params["username"],
            params["email"],
            params["apisig"],
            params["question"]);

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Search end is logged").toUtf8());
    res->end();
}

void ClientHandler::onOpenResult(const Parameters& params, QHttpResponse* res)
{
    _dao->logOpenResult(
            params["username"],
            params["email"],
            params["apisig"],
            params["question"],
            QUrl::fromPercentEncoding(params["link"].toUtf8()),
            QUrl::fromPercentEncoding(params["title"].toUtf8()));

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Open result is logged").toUtf8());
    res->end();
}

void ClientHandler::onCloseResult(const Parameters& params, QHttpResponse* res)
{
    _dao->logCloseResult(
            params["username"],
            params["email"],
            params["apisig"],
            params["question"],
            QUrl::fromPercentEncoding(params["link"].toUtf8()));

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Close result is logged").toUtf8());
    res->end();
}

void ClientHandler::onRateAnswer(const Parameters& params, QHttpResponse* res)
{
    // link and title may contain percentage encoded reserved chars, such as & < > #
    // convert them back to human readable chars
    _dao->logRating(
            params["username"],
            params["email"],
            params["apisig"],
            params["question"],
            QUrl::fromPercentEncoding(params["link"] .toUtf8()),
            params["helpful"].toLower() == "true");

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Your rating is saved").toUtf8());
    res->end();
}

/**
 * Process log answer clicking request
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::onAnswerClicking(const Parameters& params, QHttpResponse* res)
{
    // link may contain percentage encoded reserved chars, such as & < > #
    // convert them back to human readable chars
    _dao->logAnswerClicking(
            params["username"],
            params["email"],
            params["apisig"],
            params["question"],
            QUrl::fromPercentEncoding(params["link"].toUtf8()));

    res->addHeader("Content-Type", "text/html");
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->write(tr("Your Answer is logged").toUtf8());
    res->end();
}

void ClientHandler::onOpenAnswer(const Parameters& params, QHttpResponse* res)
{

}

void ClientHandler::onCloseAnswer(const Parameters& params, QHttpResponse* res)
{

}

/**
 * Process query FAQs request
 * @param params    - parameters of the request
 * @param res       - response
 */
void ClientHandler::onQueryFAQs(const Parameters& params, QHttpResponse* res)
{
    QJsonArray jaFAQs = _dao->queryFAQs(params["class"]).array();
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
void ClientHandler::onQueryUserProfile(const Parameters& params, QHttpResponse* res)
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
void ClientHandler::onSubmitPhoto(const Parameters& params, QHttpRequest* req, QHttpResponse* res)
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
void ClientHandler::onStaticResource(const QString& url, QHttpResponse* res)
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
