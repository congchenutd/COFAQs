#ifndef TEXTEDITIODEVICE_H
#define TEXTEDITIODEVICE_H

#include <QIODevice>
#include <QTextEdit>

/**
 * Adapter that converts a QTextEdit to QIODevice
 * for redirecting QDebug() output
 */
class TextEditToQIODeviceAdapter : public QIODevice
{
    Q_OBJECT

public:
    TextEditToQIODeviceAdapter(QTextEdit* textEdit, QObject* parent);

protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);

private:
    QTextEdit* _textEdit;
};

#endif // TEXTEDITIODEVICE_H
