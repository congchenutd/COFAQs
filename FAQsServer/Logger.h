#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QTextStream>

/**
 * WARNING: call setDevice first
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
