#ifndef TEXTEDITIODEVICE_H
#define TEXTEDITIODEVICE_H

#include <QIODevice>
#include <QTextEdit>
#include <QTextStream>

/**
 * Adapter that converts a QTextEdit to QIODevice
 * for redirecting QDebug() output
 */
class TextEditToQIODeviceAdapter : public QIODevice
{
    Q_OBJECT

public:
    TextEditToQIODeviceAdapter(QTextEdit* textEdit, const QString& filePath, QObject* parent);

protected:
    qint64 readData(char* data, qint64 maxSize);
    qint64 writeData(const char* data, qint64 maxSize);

private:
    QTextEdit*  _textEdit;
    QTextStream _os;        // save the log to a file
};

#endif // TEXTEDITIODEVICE_H
