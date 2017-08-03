#include "WebPage.h"
#include "WebView.h"
#include "MainWindow.h"
#include "TabWidget.h"
#include "DocVisitor.h"
#include "Connection.h"
#include "Settings.h"
#include "API.h"

#include <QDesktopServices>
#include <QNetworkRequest>
#include <QDebug>
#include <QWebFrame>
#include <QWebElement>
#include <QNetworkReply>

WebPage::WebPage(QObject* parent)
    : QWebPage(parent)
{
    const QString libName = Settings::getInstance()->getLibrary();
    _visitor = DocVisitorFactory::getInstance()->getVisitor(libName);
    connect(networkAccessManager(), SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), SLOT(onSslErrors(QNetworkReply*)));
}

void WebPage::onSslErrors(QNetworkReply* reply) {
    reply->ignoreSslErrors();
}

/**
 * Overwrite default navigation actions
 * @param frame     - web frame
 * @param request   - contains url
 * @param type      - nagivation type
 * @return          - true for default action
 */
bool WebPage::acceptNavigationRequest(QWebFrame* frame, const QNetworkRequest& request, NavigationType type)
{
    if(type == NavigationTypeLinkClicked)
    {
        // personal profile link
        if(request.url().toString().startsWith("profile:", Qt::CaseInsensitive))
        {
            QString userName = request.url().toString().remove("profile:");
            MainWindow::getInstance()->newPersonalTab(userName);
            return false;
        }

        WebView* thisView = static_cast<WebView*>(view());

        // document page
        if(thisView->getRole() == WebView::DOC_ROLE)
        {
            QString url = QUrl::fromPercentEncoding(request.url().toString().toUtf8()); // decode non-ascii chars

            // document link clicked
            if(url.startsWith(Settings::getInstance()->getDocUrl()))
                Connection::getInstance()->logDocumentReading(_visitor->urlToAPI(url).toSignature());
            // external link (answer link) clicked
            else
            {
                // extract embedded apisig and question
                int apiIndex = url.indexOf("#API#=");
                int questionIndex = url.indexOf("#Question#=");
                QString apiSig = url.mid(apiIndex + 6, questionIndex - apiIndex - 6);
                QString question = url.mid(questionIndex + 11);
                url = url.left(apiIndex);

                Connection::getInstance()->logAnswerClicking(apiSig, question, url);
                WebView* newView = MainWindow::getInstance()->newTab(WebView::ANSWER_ROLE);
                newView->setAPI(API::fromSignature(apiSig));    // transfer the attributes
                newView->setQuestion(question);
                newView->load(url);
                return false;
            }
        }

        // links on the search page open in new tab
        else if(thisView->getRole() == WebView::SEARCH_ROLE)
        {
            WebView* newView = MainWindow::getInstance()->newTab(WebView::RESULT_ROLE);
            newView->setAPI     (thisView->getAPI());    // transfer the attributes
            newView->setQuestion(thisView->getQuestion());
            newView->load(request);
            return false;
        }
    }
    else if (type == NavigationTypeFormSubmitted)
    {
        qDebug() << "Search within search page" << request.url();
        // TODO: this is the place where we can capture if the user reuses the search page
        // Best option is perhaps to replace the original search line and button with our own,
        // thus we are able to constrain the related API
    }
    return QWebPage::acceptNavigationRequest(frame, request, type);
}

// always open in tab
QWebPage* WebPage::createWindow(QWebPage::WebWindowType) {
    return MainWindow::getInstance()->newTab()->page();
}
