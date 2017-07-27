/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "SearchBar.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionDocPage;
    QAction *actionOptions;
    QAction *actionAbout;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionShowSearch;
    QAction *actionResetZoom;
    QAction *actionZoomTextOnly;
    QAction *actionFullScreen;
    QAction *actionBack;
    QAction *actionForward;
    QAction *actionReloadStop;
    QAction *actionHelpful;
    QAction *actionNotHelpful;
    QAction *actionPersonal;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuHelp;
    QMenu *menuTab;
    QMenu *menuNavigate;
    QToolBar *toolBarMain;
    QStatusBar *statusBar;
    SearchBar *toolBarSearch;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(470, 338);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/FAQ.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionDocPage = new QAction(MainWindow);
        actionDocPage->setObjectName(QStringLiteral("actionDocPage"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/Home.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDocPage->setIcon(icon2);
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionZoomIn = new QAction(MainWindow);
        actionZoomIn->setObjectName(QStringLiteral("actionZoomIn"));
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QStringLiteral("actionZoomOut"));
        actionShowSearch = new QAction(MainWindow);
        actionShowSearch->setObjectName(QStringLiteral("actionShowSearch"));
        actionShowSearch->setCheckable(true);
        actionResetZoom = new QAction(MainWindow);
        actionResetZoom->setObjectName(QStringLiteral("actionResetZoom"));
        actionZoomTextOnly = new QAction(MainWindow);
        actionZoomTextOnly->setObjectName(QStringLiteral("actionZoomTextOnly"));
        actionZoomTextOnly->setCheckable(true);
        actionFullScreen = new QAction(MainWindow);
        actionFullScreen->setObjectName(QStringLiteral("actionFullScreen"));
        actionFullScreen->setCheckable(true);
        actionBack = new QAction(MainWindow);
        actionBack->setObjectName(QStringLiteral("actionBack"));
        actionForward = new QAction(MainWindow);
        actionForward->setObjectName(QStringLiteral("actionForward"));
        actionReloadStop = new QAction(MainWindow);
        actionReloadStop->setObjectName(QStringLiteral("actionReloadStop"));
        actionHelpful = new QAction(MainWindow);
        actionHelpful->setObjectName(QStringLiteral("actionHelpful"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/Yes.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelpful->setIcon(icon3);
        actionHelpful->setVisible(false);
        actionNotHelpful = new QAction(MainWindow);
        actionNotHelpful->setObjectName(QStringLiteral("actionNotHelpful"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Images/No.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNotHelpful->setIcon(icon4);
        actionNotHelpful->setVisible(false);
        actionPersonal = new QAction(MainWindow);
        actionPersonal->setObjectName(QStringLiteral("actionPersonal"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Images/Personal.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPersonal->setIcon(icon5);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 470, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuTab = new QMenu(menuBar);
        menuTab->setObjectName(QStringLiteral("menuTab"));
        menuNavigate = new QMenu(menuBar);
        menuNavigate->setObjectName(QStringLiteral("menuNavigate"));
        MainWindow->setMenuBar(menuBar);
        toolBarMain = new QToolBar(MainWindow);
        toolBarMain->setObjectName(QStringLiteral("toolBarMain"));
        toolBarMain->setContextMenuPolicy(Qt::PreventContextMenu);
        toolBarMain->setMovable(false);
        toolBarMain->setAllowedAreas(Qt::TopToolBarArea);
        toolBarMain->setIconSize(QSize(32, 32));
        toolBarMain->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolBarMain->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarMain);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBarSearch = new SearchBar(MainWindow);
        toolBarSearch->setObjectName(QStringLiteral("toolBarSearch"));
        toolBarSearch->setAllowedAreas(Qt::BottomToolBarArea);
        toolBarSearch->setIconSize(QSize(32, 32));
        MainWindow->addToolBar(Qt::BottomToolBarArea, toolBarSearch);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuTab->menuAction());
        menuBar->addAction(menuNavigate->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOptions);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuView->addAction(actionDocPage);
        menuView->addSeparator();
        menuView->addAction(actionZoomIn);
        menuView->addAction(actionZoomOut);
        menuView->addAction(actionResetZoom);
        menuView->addAction(actionZoomTextOnly);
        menuView->addSeparator();
        menuView->addAction(actionShowSearch);
        menuView->addAction(actionFullScreen);
        menuHelp->addAction(actionAbout);
        menuTab->addAction(actionPersonal);
        menuTab->addSeparator();
        menuNavigate->addAction(actionBack);
        menuNavigate->addAction(actionForward);
        toolBarMain->addAction(actionDocPage);
        toolBarMain->addSeparator();
        toolBarMain->addAction(actionBack);
        toolBarMain->addAction(actionForward);
        toolBarMain->addAction(actionReloadStop);
        toolBarMain->addSeparator();
        toolBarMain->addAction(actionHelpful);
        toolBarMain->addAction(actionNotHelpful);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FAQBrowser", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", Q_NULLPTR));
        actionDocPage->setText(QApplication::translate("MainWindow", "&Document", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDocPage->setToolTip(QApplication::translate("MainWindow", "Document page", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionOptions->setText(QApplication::translate("MainWindow", "&Options", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", Q_NULLPTR));
        actionZoomIn->setText(QApplication::translate("MainWindow", "Zoom In", Q_NULLPTR));
        actionZoomOut->setText(QApplication::translate("MainWindow", "Zoom Out", Q_NULLPTR));
        actionShowSearch->setText(QApplication::translate("MainWindow", "Show Search Bar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionShowSearch->setToolTip(QApplication::translate("MainWindow", "Show Search Bar", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionResetZoom->setText(QApplication::translate("MainWindow", "Reset Zoom", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionResetZoom->setShortcut(QApplication::translate("MainWindow", "Ctrl+0", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomTextOnly->setText(QApplication::translate("MainWindow", "Zoom Text Only", Q_NULLPTR));
        actionFullScreen->setText(QApplication::translate("MainWindow", "Full Screen", Q_NULLPTR));
        actionBack->setText(QApplication::translate("MainWindow", "Back", Q_NULLPTR));
        actionForward->setText(QApplication::translate("MainWindow", "Forward", Q_NULLPTR));
        actionReloadStop->setText(QApplication::translate("MainWindow", "Reload", Q_NULLPTR));
        actionHelpful->setText(QApplication::translate("MainWindow", "Helpful", Q_NULLPTR));
        actionNotHelpful->setText(QApplication::translate("MainWindow", "Not helpful", Q_NULLPTR));
        actionPersonal->setText(QApplication::translate("MainWindow", "Personal profile", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionPersonal->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", Q_NULLPTR));
        menuTab->setTitle(QApplication::translate("MainWindow", "Tab", Q_NULLPTR));
        menuNavigate->setTitle(QApplication::translate("MainWindow", "Navigate", Q_NULLPTR));
        toolBarMain->setWindowTitle(QApplication::translate("MainWindow", "Main Toolbar", Q_NULLPTR));
        toolBarSearch->setWindowTitle(QApplication::translate("MainWindow", "Search in page", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
