#include "Logger.h"
#include <QDateTime>

QIODevice* Logger::_device = 0;

void Logger::setDevice(QIODevice* device) {
    _device = device;
}

Logger* Logger::getInstance()
{
    static Logger instance(_device);
    return &instance;
}

Logger::Logger(QIODevice* device)
    : QDebug (device) {}


/////////////////////////////////////////////////////////////
LoggerAdapter::LoggerAdapter() {
    open(QIODevice::WriteOnly | QIODevice::Text);
}

void LoggerAdapter::addOutlet(LoggerOutlet* outlet) {
    _outlets << outlet;
}

qint64 LoggerAdapter::readData(char* data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return 0;
}

qint64 LoggerAdapter::writeData(const char* data, qint64 maxSize)
{
    QString message = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss: ") + data;
    foreach (auto outlet, _outlets)
        outlet->write(message);
    return maxSize;
}

///////////////////////////////////////////////////////////////////
LoggerOutlet::~LoggerOutlet() {}


///////////////////////////////////////////////////////////////////
TextEditLoggerOutlet::TextEditLoggerOutlet(QTextEdit* textEdit)
    : _textEdit(textEdit)
{}

// Write data to the text edit
void TextEditLoggerOutlet::write(const QString& data)
{
    if (_textEdit != 0)
        _textEdit->append(data);     // print to text edit
}

//////////////////////////////////////////////////////////////////////
FileLoggerOutlet::FileLoggerOutlet(const QString& filePath)
{
    _file.setFileName(filePath);
    if (_file.open(QFile::WriteOnly | QFile::Append))
        _os.setDevice(&_file);
}

void FileLoggerOutlet::write(const QString& data) {
    _os << data << endl;
}
