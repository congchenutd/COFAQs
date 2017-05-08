#include <QApplication>
#include "Window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Window window;
    window.resize(1000, 800);
    window.show();

    return app.exec();
}
