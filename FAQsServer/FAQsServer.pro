cache()
TARGET = FAQsServer

QT += gui network sql widgets

CONFIG += c++11

TEMPLATE = app

INCLUDEPATH += $$PWD/include

win32 {
    CONFIG(release, debug|release) {
        LIBS += -L$$PWD/lib/ -lqhttp
    }
    CONFIG(debug, debug|release) {
        LIBS += -L$$PWD/lib/ -lqhttpd
    }
}
else {
    LIBS += -L$$PWD/lib -lqhttp
}

SOURCES = \
    DAO.cpp \
    SimilarityComparer.cpp \
    Main.cpp \
    Template.cpp \
    SnippetCreator.cpp \
    Settings.cpp \
    ClientHandler.cpp \
    Window.cpp \
    TextEditToQIODeviceAdapter.cpp
HEADERS = \
    DAO.h \
    SimilarityComparer.h \
    Template.h \
    SnippetCreator.h \
    Settings.h \
    ClientHandler.h \
    Window.h \
    Logger.h \
    TextEditToQIODeviceAdapter.h

FORMS += \
    Window.ui

RESOURCES += \
    Resources.qrc
