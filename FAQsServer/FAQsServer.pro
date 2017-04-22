cache()
TARGET = FAQsServer

QT += network sql
QT -= gui

CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/include

win32 {
#    debug: LIBS += -L$$PWD/lib/ -lqhttpserverd
#    else:  LIBS += -L$$PWD/lib/ -lqhttpserver
} else {
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
