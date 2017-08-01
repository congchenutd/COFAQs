/********************************************************************************
** Form generated from reading UI file 'SearchDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDLG_H
#define UI_SEARCHDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_SearchDlg
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *leAPI;
    QLabel *label;
    QLineEdit *leQuestion;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SearchDlg)
    {
        if (SearchDlg->objectName().isEmpty())
            SearchDlg->setObjectName(QStringLiteral("SearchDlg"));
        SearchDlg->resize(480, 116);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Search.png"), QSize(), QIcon::Normal, QIcon::Off);
        SearchDlg->setWindowIcon(icon);
        gridLayout = new QGridLayout(SearchDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(SearchDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        leAPI = new QLineEdit(SearchDlg);
        leAPI->setObjectName(QStringLiteral("leAPI"));

        gridLayout->addWidget(leAPI, 0, 1, 1, 1);

        label = new QLabel(SearchDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        leQuestion = new QLineEdit(SearchDlg);
        leQuestion->setObjectName(QStringLiteral("leQuestion"));

        gridLayout->addWidget(leQuestion, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(SearchDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(SearchDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), SearchDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SearchDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(SearchDlg);
    } // setupUi

    void retranslateUi(QDialog *SearchDlg)
    {
        SearchDlg->setWindowTitle(QApplication::translate("SearchDlg", "Search for help", 0));
        label_2->setText(QApplication::translate("SearchDlg", "API", 0));
        label->setText(QApplication::translate("SearchDlg", "Question", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchDlg: public Ui_SearchDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDLG_H
