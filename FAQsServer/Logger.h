#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QTextEdit>
#include <QTextStream>

/**
 * WARNING: call setDevice first
 * WARNING: always end a output with endl
 */
class Logger: public QDebug
{
public:
    static void setDevice(QIODevice* device);
    static Logger* getInstance();

private:
    Logger(QIODevice* device);

    static QIODevice* _device;
};

class LoggerOutlet;

/**
 *  Implements the QIODevice interface so that it can redirect qDebug() output to other QIODevices
 */
class LoggerAdapter: public QIODevice
{
public:
    LoggerAdapter();
    void addOutlet(LoggerOutlet* outlet);

    // QIODevice interface
protected:
    qint64 readData (char* data, qint64 maxSize);
    qint64 writeData(const char* data, qint64 maxSize);

private:
    QList<LoggerOutlet*> _outlets;
};

/**
 * An outlet is a device that text output can be written to
 */
class LoggerOutlet
{
public:
    virtual ~LoggerOutlet();
    virtual void write(const QString& data) = 0;
};

/**
 * Redirects output to a QTextEdit
 */
class TextEditLoggerOutlet : public LoggerOutlet
{
public:
    TextEditLoggerOutlet(QTextEdit* textEdit);
    void write(const QString& data);

private:
    QTextEdit*  _textEdit;
};

/**
 * Redirects output to a file
 */
class FileLoggerOutlet : public LoggerOutlet
{
public:
    FileLoggerOutlet(const QString& filePath);
    void write(const QString& data);

private:
    QFile       _file;
    QTextStream _os;
};

#endif // LOGGER_H
