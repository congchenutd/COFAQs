cache()
TARGET = FAQsServer

QT += network sql
QT -= gui

CONFIG += console c++11
CONFIG -= app_bundle

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
    ClientHandler.cpp
HEADERS = \
    DAO.h \
    SimilarityComparer.h \
    Template.h \
    SnippetCreator.h \
    Settings.h \
    ClientHandler.h
