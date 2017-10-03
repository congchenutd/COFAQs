#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
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

#endif // LOGGER_H
