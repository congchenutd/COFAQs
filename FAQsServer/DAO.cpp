#include "DAO.h"
#include "SimilarityComparer.h"
#include "Settings.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QDateTime>
#include <QSettings>
#include <QSqlError>

DAO* DAO::_instance = 0;

DAO* DAO::getInstance()
{
    if(_instance == 0)
        _instance = new DAO;
    return _instance;
}

void DAO::setLogger(Logger* logger) { _logger = logger; }

DAO::DAO()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("FAQs.db");
    database.open();

    QSqlQuery query;
    query.exec("create table APIs ( \
               ID        int primary key, \
               Signature varchar unique not null)");    // e.g., lib;package.class.method

    query.exec("create table Answers ( \
               ID    int primary key, \
               Link  varchar unique not null, \
               Title varchar        not null)");

    query.exec("create table Users ( \
               ID    int primary key, \
               Name  varchar unique not null, \
               Email varchar unique)");

    query.exec("create table Questions ( \
               ID         int primary key, \
               Question   varchar unique not null, \
               AskCount   int, \
               Parent     int)");

    query.exec("create table UserReadDocument ( \
               UserID int references Users(ID) on delete cascade on update cascade, \
               APIID  int references APIs (ID) on delete cascade on update cascade, \
               Time   varchar, \
               primary key (UserID, APIID, Time))");

    query.exec("create table UserReadAnswer ( \
               UserID       int references Users        (ID) on delete cascade on update cascade, \
               APIID        int references APIs         (ID) on delete cascade on update cascade, \
               QuestionID   int references Questions    (ID) on delete cascade on update cascade, \
               AnswerID     int references Answers      (ID) on delete cascade on update cascade, \
               Time         varchar, \
               primary key (UserID, APIID, QuestionID, AnswerID, Time))");

    query.exec("create table UserRateAnswer ( \
               UserID       int references Users        (ID) on delete cascade on update cascade, \
               APIID        int references APIs         (ID) on delete cascade on update cascade, \
               QuestionID   int references Questions    (ID) on delete cascade on update cascade, \
               AnswerID     int references Answers      (ID) on delete cascade on update cascade, \
               Helpful      int, \
               Time         varchar, \
               primary key (UserID, APIID, QuestionID, AnswerID, Time))");

    query.exec("create table UserSearchQuestion ( \
               UserID       int references Users        (ID) on delete cascade on update cascade, \
               APIID        int references APIs         (ID) on delete cascade on update cascade, \
               QuestionID   int references Questions    (ID) on delete cascade on update cascade, \
               StartTime    varchar, \
               EndTime      varchar, \
               primary key (UserID, APIID, QuestionID, StartTime))");

    query.exec("create table UserReadSearchResult ( \
               UserID       int references Users        (ID) on delete cascade on update cascade, \
               APIID        int references APIs         (ID) on delete cascade on update cascade, \
               QuestionID   int references Questions    (ID) on delete cascade on update cascade, \
               AnswerID     int references Answers  (ID) on delete cascade on update cascade, \
               StartTime    varchar, \
               EndTime      varchar, \
               primary key (UserID, APIID, QuestionID, AnswerID, StartTime))");

    _comparer = new SimilarityComparer(this);
    connect(_comparer, SIGNAL(comparisonResult  (QString,QString,qreal)),
            this,      SLOT  (onComparisonResult(QString,QString,qreal)));
}

/**
 * @return  - a new ID for a given table. ID starts from 0
 */
int DAO::getNextID(const QString& tableName) const
{
    if(tableName.isEmpty())
        return 0;
    QSqlQuery query;
    query.exec(tr("select max(ID) from %1").arg(tableName));
    return query.next() ? query.value(0).toInt() + 1 : 0;
}

/**
 * Find the ID of a record
 * @param tableName - table name
 * @param section   - section (column) name
 * @param value     - value of the section
 * @return          - ID of the record matching the query
 */
int DAO::getID(const QString& tableName, const QString& section, const QString& value) const
{
    QSqlQuery query;
    query.prepare(tr("select ID from %1 where %2 = :value").arg(tableName)
                                                           .arg(section));
    query.bindValue(":value", value);
    query.exec();
    return query.next() ? query.value(0).toInt() : -1;
}

int DAO::getUserID    (const QString& userName)  const { return getID("Users",     "Name",      userName); }
int DAO::getAPIID     (const QString& signature) const { return getID("APIs",      "Signature", signature); }
int DAO::getQuestionID(const QString& question)  const { return getID("Questions", "Question",  question); }
int DAO::getAnswerID  (const QString& link)      const { return getID("Answers",   "Link",      link); }

/**
 * Write an API into db
 * @return API ID
 */
int DAO::updateAPI(const QString& signature)
{
    if(signature.isEmpty())
        return -1;

    int id = getAPIID(signature);   // already exists, no need to update, because APIs don't change
    if (id >= 0)
        return id;

    id = getNextID("APIs");
    QSqlQuery query;
    query.prepare("insert into APIs values (:id, :sig)");
    query.bindValue(":id",  id);
    query.bindValue(":sig", signature);
    query.exec();
    return id;
}

/**
 * Update Users table
 * @return user ID, new or existing
 */
int DAO::updateUser(const QString& userName, const QString& email)
{
    if(userName.isEmpty())
        return -1;

    // update existing user or insert a new one
    QSqlQuery query;
    int id = getUserID(userName);
    if(id > 0) {
        query.prepare("update Users set Name = :name, Email = :email where ID = :id");
    }
    else
    {
        id = getNextID("Users");
        query.prepare("insert into Users values (:id, :name, :email)");
    }
    query.bindValue(":id", id);
    query.bindValue(":name",  userName);
    query.bindValue(":email", email);
    query.exec();
    return id;
}

/**
 * Update Questions table
 * @return question ID, new or existing
 */
int DAO::updateQuestion(const QString& question, const QString& apiSig)
{
    if(question.isEmpty())
        return -1;

    // update the ask count of the existing question
    QSqlQuery query;
    int questionID = getQuestionID(question);
    if(questionID >= 0)
    {
        // TODO: askcount can be found in UserSearchQuestion table
//        query.exec(tr("update Questions set AskCount = AskCount + 1 where ID = %1")
//                   .arg(questionID));
//        updateLead(questionID);
        return questionID;
    }

    // or insert a new question
    questionID = getNextID("Questions");
    query.prepare("insert into Questions values (:id, :question, 1, -1)");
    query.bindValue(":id",       questionID);
    query.bindValue(":question", question);
    query.exec();

    int apiID = getAPIID(apiSig);
    if (apiID > -1)
        measureSimilarity(question, apiID);  // initiate measure

    return questionID;
}

/**
 * Try to find a question group that is similar in meaning to a given search question
 * @param question  - a search question
 * @param apiID     - id of the api in the database
 */
void DAO::measureSimilarity(const QString& question, int apiID)
{
//    // find the lead questions the API has
//    QSqlQuery query;
//    query.exec(tr("select Question from QuestionAboutAPI, Questions\
//                   where APIID = %1 and QuestionID = ID and Parent = -1").arg(apiID));

//    // compare this question with each lead question
//    while(query.next())
//        _comparer->compare(query.value(0).toString(), question);
}

/**
 * Group a given question to an existing group if they are similar
 * @param leadQuestion  - the lead question of a group
 * @param question      - the question to be merged
 * @param similarity    - similarity score [0~1]
 */
void DAO::onComparisonResult(const QString& leadQuestion,
                             const QString& question, qreal similarity)
{
    double threshold = qMax(Settings::getInstance()->getSimilarityThreshold(), 0.5);
    if(similarity <= threshold)
        return;

    // set lead question to be the parent of question if similar
    QSqlQuery query;
    query.exec(tr("update Questions set Parent = %1 where ID = %2")
               .arg(getQuestionID(leadQuestion))
               .arg(getQuestionID(question)));
}

/**
 * Update the lead of a group once a question is being asked one more time
 * The lead of a similar-meaning question group is the one with highest ask count
 * @param questionID    - id of the question being updated
 */
void DAO::updateLead(int questionID)
{
    // get lead id and this question's ask count
    QSqlQuery query;
    query.exec(tr("select Parent, AskCount from Questions where ID = %1 and Parent <> -1")
               .arg(questionID));
    if(!query.next())   // questionID is the lead, nothing needs to be done
        return;

    int leadID    = query.value(0).toInt();
    int thisCount = query.value(1).toInt();   // this question's ask count

    // ask count of the lead question
    query.exec(tr("select AskCount from Questions where ID = %1").arg(leadID));
    int leadCount = query.next() ? query.value(0).toInt() : 0;

    // cannot beat lead, no change
    if(thisCount <= leadCount)
        return;

    // This question has higher ask count than the lead question
    // all children of lead now become this question's chidren
    query.exec(tr("update Questions set Parent = %1 where Parent = %2")
               .arg(questionID).arg(leadID));

    // lead is now this question's child
    query.exec(tr("update Questions set Parent = %1 where ID = %2")
               .arg(questionID).arg(leadID));

    // Set this question to be nobody's child
    query.exec(tr("update Questions set Parent = -1 where ID = %1")
               .arg(questionID));
}

/**
 * Update Answers table
 * @param link  - link to the answer page
 * @param title - title of the web page
 * @return      - answer ID, new or existing
 */
int DAO::updateAnswer(const QString& link, const QString& title)
{
    if(link.isEmpty())
        return -1;

    // update existing answer or insert a new one
    QSqlQuery query;
    int id = getAnswerID(link);
    if(id > 0) {
        query.prepare("update Answers set Link = :link, Title = :title where ID = :id");
    }
    else
    {
        id = getNextID("Answers");
        query.prepare("insert into Answers values (:id, :link, :title)");
    }
    query.bindValue(":id", id);
    query.bindValue(":link",  link);
    query.bindValue(":title", title);
    query.exec();
    return id;
}

/**
 * Save document reading event
 * @param userName  - user names
 * @param email     - user email
 * @param apiSig    - signature of the related API
 */
void DAO::logDocumentReading(const QString& userName, const QString& email, const QString& apiSig)
{
    int userID  = updateUser(userName, email);
    int apiID   = updateAPI (apiSig);

    QSqlQuery query;
    query.prepare("insert into UserReadDocument values (:userID, :apiID, :time)");
    query.bindValue(":userID", userID);
    query.bindValue(":apiID",  apiID);
    query.bindValue(":time",   getCurrentDateTime());
    query.exec();

    *_logger << userName << "read document:" << apiSig << endl;

    // TODO: log document reading start and end?
}

void DAO::logSearchStart(const QString& userName, const QString& email, const QString& apiSig, const QString& question)
{
    int userID      = updateUser(userName, email);
    int apiID       = updateAPI(apiSig);
    int questionID  = updateQuestion(question, apiSig);

    QSqlQuery query;
    query.prepare("insert into UserSearchQuestion values (:userID, :api, :questionID, :start, \'\')");
    query.bindValue(":userID",      userID);
    query.bindValue(":api",         apiID);
    query.bindValue(":questionID",  questionID);
    query.bindValue(":start",       getCurrentDateTime());
    query.exec();

    *_logger << userName << "started search question:" << question << "for API:" << apiSig << endl;
}

void DAO::logSearchEnd(const QString& userName, const QString& email, const QString& apiSig, const QString& question)
{
    int userID      = getUserID(userName);
    int apiID       = updateAPI(apiSig);
    int questionID  = getQuestionID(question);

    // find existing end time
    QSqlQuery query;
    query.exec(tr("select StartTime from UserSearchQuestion where UserID = %1 and QuestionID = %2 and APIID = %3 \
                   order by StartTime desc").arg(userID).arg(questionID).arg(apiID));
    if (query.next())
    {
        // update end time to current time
        QString startTime = query.value(0).toString();
        query.prepare("update UserSearchQuestion set EndTime = :EndTime \
                       where UserID = :UserID and QuestionID = :QuestionID and APIID = :APIID and StartTime = :StartTime");
        query.bindValue(":UserID",      userID);
        query.bindValue(":QuestionID",  questionID);
        query.bindValue(":APIID",       apiID);
        query.bindValue(":StartTime",   startTime);
        query.bindValue(":EndTime",     getCurrentDateTime());
        query.exec();

        *_logger << userName << "ended search question:" << question << "for API:" << apiSig << endl;
    }
}

void DAO::logOpenResult(const QString& userName, const QString& email, const QString& apiSig,
                        const QString& question, const QString& link, const QString& title)
{
    int userID      = updateUser(userName, email);
    int apiID       = getAPIID(apiSig);
    int questionID  = getQuestionID(question);
    int answerID    = updateAnswer(link, title);

    QSqlQuery query;
    query.prepare("insert into UserReadSearchResult values (:UserID, :API, :QuestionID, :AnswerID, :Start, \'\')");
    query.bindValue(":UserID",      userID);
    query.bindValue(":API",         apiID);
    query.bindValue(":QuestionID",  questionID);
    query.bindValue(":AnswerID",    answerID);
    query.bindValue(":Start",       getCurrentDateTime());
    query.exec();

    *_logger << userName << "opened search result page:" << link << "for question:" << question
             << "about API:" << apiSig << "at:" << getCurrentDateTime() << endl;
}

void DAO::logCloseResult(const QString& userName, const QString& email, const QString& apiSig,
                         const QString& question, const QString& link)
{
    int userID      = updateUser(userName, email);
    int apiID       = getAPIID(apiSig);
    int questionID  = getQuestionID(question);
    int answerID    = getAnswerID(link);

    // find start time of this result viewing
    QSqlQuery query;
    query.exec(tr("select StartTime from UserReadSearchResult where UserID = %1 and QuestionID = %2 and APIID = %3 and AnswerID = \'%4\' \
                   order by StartTime desc").arg(userID).arg(questionID).arg(apiID).arg(answerID));
    if (query.next())
    {
        QString startTime = query.value(0).toString();
        query.prepare("update UserReadSearchResult set EndTime = :EndTime \
                       where UserID = :UserID and QuestionID = :QuestionID and APIID = :APIID and AnswerID = :AnswerID and StartTime = :StartTime");
        query.bindValue(":UserID",      userID);
        query.bindValue(":APIID",       apiID);
        query.bindValue(":QuestionID",  questionID);
        query.bindValue(":AnswerID",    answerID);
        query.bindValue(":StartTime",   startTime);
        query.bindValue(":EndTime",     getCurrentDateTime());  // update end time
        query.exec();

        logSearchEnd(userName, email, apiSig, question);    // update search end in case the search page is closed first
    }

    *_logger << userName << "closed search result page:" << link << "for question:" << question
             << "about API:" << apiSig << "at:" << getCurrentDateTime() << endl;
}

void DAO::logRating(const QString& userName, const QString& email, const QString& apiSig, const QString& question,
                    const QString& link, bool helpful)
{
    // update relationships
    int apiID       = updateAPI     (apiSig);       // because we may have a new apiID
    int answerID    = getAnswerID   (link);
    int userID      = updateUser    (userName, email);
    int questionID  = updateQuestion(question, apiSig);

    QSqlQuery query;
    query.prepare("insert into UserRateAnswer values (:UserID, :APIID, :QuestionID, :AnswerID, :Helpfulness, :Time)");

    query.bindValue(":UserID",      userID);
    query.bindValue(":APIID",       apiID);
    query.bindValue(":QuestionID",  questionID);
    query.bindValue(":AnswerID",    answerID);
    query.bindValue(":Helpfulness", helpful ? 1 : -1);
    query.bindValue(":Time",        getCurrentDateTime());
    query.exec();

    *_logger << userName << "rated answer:" << link << (helpful ? "helpful" : "unhelpful")
             << "for question:" << question << "about API:" << apiSig << "at:" << getCurrentDateTime() << endl;
}

/**
 * Save an answer clicking event
 */
void DAO::logAnswerClicking(const QString& userName, const QString& email, const QString& apiSig, const QString& question, const QString& link)
{
    int userID      = updateUser(userName, email);
    int apiID       = getAPIID(apiSig);
    int questionID  = getQuestionID(question);
    int answerID    = getAnswerID(link);

    // add a UserReadAnswer record
    QSqlQuery query;
    query.prepare("insert into UserReadAnswer values (:UserID, :ApiID, :QuestionID, :AnswerID, :Time)");
    query.bindValue(":UserID",      userID);
    query.bindValue(":ApiID",       apiID);
    query.bindValue(":QuestionID",  questionID);
    query.bindValue(":AnswerID",    answerID);
    query.bindValue(":Time",        getCurrentDateTime());
    query.exec();

    *_logger << userName << "opened answer link: " << link << "for question:" << question << "about API:" << apiSig << endl;
}

QString DAO::getCurrentDateTime() const {
    return QDateTime::currentDateTime().toString(getDateTimeFormat());
}

QString DAO::getDateTimeFormat() const {
    return "yyyy-MM-dd hh:mm:ss";
}

// An example of returned JSON array:
//[
//{
//	"api": "java.util.ArrayList.ensureCapacity",
//	"questions":
//	[
//		{
//			"question": "question1",
//			"users"   : [{"username": "user1", "email": "user1@gmai.com"},
//						 {"username": "user2", "email": "user2@gmail.com"}],
//			"answers" : [{"link": "link1", "title": "title1"},
//						 {"link": "link2", "title": "title2"}]
//		},
//		{
//			"question": "question2",
//			"users"   : [{"username": "user1", "email": "user1@gmai.com"},
//						 {"username": "user2", "email": "user2@gmail.com"}],
//			"answers" : []
//		},
//	]
//},
//{...}
//]

/**
 * Get all FAQs related to a given class
 * @param classSig  - signature of a class
 * @return          - a json document containing all the FAQs of the class
 */
QJsonDocument DAO::queryFAQs(const QString& classSig) const
{
    QJsonArray apisJson;

    // find all APIs under this class
    // fuzzy search finds all methods of this class, because they look like classSig.methodName()
    QSqlQuery query;
    query.exec(tr("select ID, Signature from APIs where Signature like \'%1%\'").arg(classSig));

    while(query.next())
    {
        int apiID = query.value(0).toInt();
        QJsonArray questions = createQuestionsJson(apiID);  // questions about this API
        if(!questions.isEmpty())
        {
            QString apiSig = query.value(1).toString()/*.section(";", -1, -1)*/;  // remove library
            QJsonObject apiJson;
            apiJson.insert("apisig",    apiSig);
            apiJson.insert("questions", questions);
            apisJson.append(apiJson);
        }
    }

    *_logger << "Server returned query result: " << apisJson << endl;

    return QJsonDocument(apisJson);
}

/**
 * @return - a json object representing an answer
 */
QJsonObject DAO::createAnswerJson(int answerID) const
{
    QJsonObject result;
    QSqlQuery query;
    query.exec(tr("select Link, Title from Answers where ID = %1").arg(answerID));
    if(query.next())
    {
        result.insert("link",  query.value(0).toString());
        result.insert("title", query.value(1).toString());
    }
    return result;
}

/**
 * @return - a json object representing a user
 */
QJsonObject DAO::createUserJson(int userID) const
{
    QJsonObject result;
    QSqlQuery query;
    query.exec(tr("select Name, Email from Users where ID = %1").arg(userID));
    if(query.next())
    {
        result.insert("name",  query.value(0).toString());
        result.insert("email", query.value(1).toString());
    }
    return result;
}

/**
 * Find answers to the question on a given API
 * @return - a QJsonArray consisting of QJsonObject for the answers
 */
QJsonArray DAO::createAnswersJson(int apiID, int questionID) const
{
    QJsonArray result;
    QSqlQuery query;
    query.exec(tr("select AnswerID from ( \
                  select AnswerID, sum(Helpful) as Helpful \
                  from UserRateAnswer \
                  where APIID = %1 and QuestionID = %2 \
                  group by AnswerID) \
                  where Helpful > 0 \
                  order by Helpful desc").arg(apiID).arg(questionID));
    while(query.next())
    {
        QJsonObject answerJson = createAnswerJson(query.value(0).toInt());
        if(!answerJson.isEmpty())   // answers may not exist
            result.append(answerJson);
    }
    return result;
}

/**
 * Find users who are interested in the question on the given API
 * @return - a QJsonArray consisting of QJsonObject for the users
 */
QJsonArray DAO::createUsersJson(int apiID, int questionID) const
{
    QJsonArray result;
    QSqlQuery query;
    query.exec(tr("select distinct UserID from UserRateAnswer \
                  where APIID = %1 and QuestionID = %2").arg(apiID).arg(questionID));
    while(query.next())
        result.append(createUserJson(query.value(0).toInt()));
    return result;
}

/**
 * @param leadID    - ID of the lead question of a group
 * @return          - a json object representing a question and all related answers and users
 */
QJsonObject DAO::createQuestionJson(int apiID, int leadID) const
{
    QJsonObject result;
    QSqlQuery query;

    // lead question content
    query.exec(tr("select Question from Questions where ID = %1").arg(leadID));
    if (!query.next())
        return result;

    result.insert("question", query.value(0).toString());

    // questions group
    QList<int> questionIDs;
    query.exec(tr("select ID from Questions where Parent = %1 or ID = %1").arg(leadID));
    while(query.next())
        questionIDs << query.value(0).toInt();

    QJsonArray users;
    QJsonArray answers;
    foreach (int questionID, questionIDs)
    {
        foreach (QJsonValue v, createUsersJson(apiID, questionID))
            users.append(v.toObject());
        foreach (QJsonValue v, createAnswersJson(apiID, questionID))
            answers.append(v.toObject());
    }

    if (!users.isEmpty())
        result.insert("users", users);
    if (!answers.isEmpty())
        result.insert("answers", answers);
    return result;
}

/**
 * @param apiID - ID of an API
 * @return      - a json array representing all the questions of the API
 */
QJsonArray DAO::createQuestionsJson(int apiID) const
{
    QJsonArray result;

    // find all lead questions of the API
    QSqlQuery query;
    query.exec(tr("select distinct QuestionID from UserRateAnswer where APIID = %1").arg(apiID));
    while (query.next())
        result.append(createQuestionJson(apiID, query.value(0).toInt()));

    return result;
}

/**
 * @param userName  - user name
 * @return          - a json document representing a user's profile, including her questions and answers
 */
QJsonDocument DAO::queryUserProfile(const QString& userName) const
{
    int userID = getUserID(userName);
    if(userID == -1)
        return QJsonDocument();

    // this person's profile
    QJsonObject profileJson;
    profileJson.insert("name", userName);
    QSqlQuery query;
    query.exec(tr("select Email from Users where ID = %1").arg(userID));
    if(query.next())
        profileJson.insert("email", query.value(0).toString());

    // get all the questions userID relates to
    // 1. get all the lead questions asked  by userID
    // 2. get all the lead questions viewed by userID
    // 3. merge (union) 1 and 2
    query.exec(tr("select QuestionID from UserAskQuestion, Questions \
                     where QuestionID = ID and Parent = -1 and UserID = %1 \
                   union \
                   select QuestionID from UserReadAnswer, Questions \
                     where QuestionID = ID and Parent = -1 and UserID = %1 \
                   order by QuestionID").arg(userID));
    QStringList questions;
    while(query.next())
        questions << query.value(0).toString();

    // get all the APIs associated with the questions
    query.exec(tr("select distinct ID, Signature from APIs, QuestionAboutAPI \
                  where ID = APIID and QuestionID in (%1)").arg(questions.join(",")));

    QJsonArray apisJson;
    while(query.next())
    {
        int     apiID  = query.value(0).toInt();
        QString apiSig = query.value(1).toString().section(";", -1, -1);  // remove library
        QJsonObject apiJson;                                          // json for this api
        apiJson.insert("apisig",    apiSig);                          // save api to json
        apiJson.insert("questions", createQuestionsJson(apiID));      // save questions to json
        apisJson.append(apiJson);                                     // add this json to api json array
    }
    profileJson.insert("apis", apisJson);   // add apis

    // get all other users associated with the questions
    query.exec(tr("select Name, Email from UserAskQuestion, Users \
                     where QuestionID in (%1) and UserID = ID and UserID != %2 \
                   union \
                   select Name, Email from UserReadAnswer, Users \
                     where QuestionID in (%1) and UserID = ID and UserID != %2")
               .arg(questions.join(",")).arg(userID));

    QJsonArray usersJson;
    while(query.next())
    {
        QString name  = query.value(0).toString();
        QString email = query.value(1).toString();
        QJsonObject userJson;             // json for this user
        userJson.insert("name",  name);
        userJson.insert("email", email);
        usersJson.append(userJson);       // add this json to users json array
    }
    profileJson.insert("relatedusers", usersJson);   // add related users

    *_logger << "Query user profile: " << userName << endl;
    return QJsonDocument(profileJson);
}
