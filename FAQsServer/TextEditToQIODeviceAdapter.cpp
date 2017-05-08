#include "TextEditToQIODeviceAdapter.h"

TextEditToQIODeviceAdapter::TextEditToQIODeviceAdapter(QTextEdit* textEdit, QObject* parent)
    : QIODevice(parent),
      _textEdit(textEdit)
{
    open(QIODevice::WriteOnly | QIODevice::Text);
}

qint64 TextEditToQIODeviceAdapter::readData(char* data, qint64 maxSize) { return 0; }

qint64 TextEditToQIODeviceAdapter::writeData(const char* data, qint64 maxSize)
{
    if(_textEdit)
        _textEdit->append(data);
    return maxSize;
}
