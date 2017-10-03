#include "TextEditToQIODeviceAdapter.h"

#include <QFile>
#include <QDateTime>

TextEditToQIODeviceAdapter::TextEditToQIODeviceAdapter(QTextEdit* textEdit, const QString& filePath, QObject* parent)
    : QIODevice(parent),
      _textEdit(textEdit)
{
    // set open mode
    open(QIODevice::WriteOnly | QIODevice::Text);

    // log file
    QFile* file = new QFile(filePath);
    if (file->open(QFile::WriteOnly | QFile::Append))
        _os.setDevice(file);
    else
        writeData("Unable to open log file", 100);
}

qint64 TextEditToQIODeviceAdapter::readData(char* data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return 0;
}

// Write data to the text edit
qint64 TextEditToQIODeviceAdapter::writeData(const char* data, qint64 maxSize)
{
    QString message = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss: ") + data;

    if (_textEdit != 0)
    {
        _textEdit->append(message);     // print to text edit
    }

    _os << message << endl;             // save to file

    return maxSize;
}
