#ifndef WINDOW_H
#define WINDOW_H

#include "ui_Window.h"
#include <QTextEdit>
#include <QSystemTrayIcon>

class Window: public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void onQuit();
    void onTrayActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::Window ui;

    QSystemTrayIcon* _tray;
};

#endif // WINDOW_H
