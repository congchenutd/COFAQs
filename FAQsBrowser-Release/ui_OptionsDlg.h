/********************************************************************************
** Form generated from reading UI file 'OptionsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDLG_H
#define UI_OPTIONSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include "ImageLabel.h"

QT_BEGIN_NAMESPACE

class Ui_OptionsDlg
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leServerIP;
    QLabel *label_6;
    QLineEdit *leServerPort;
    QLabel *labelServerStatus;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *leUsername;
    ImageLabel *labelImage;
    QLineEdit *leEmail;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QRadioButton *radioGoogle;
    QRadioButton *radioBaidu;
    QPushButton *btFont;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionsDlg)
    {
        if (OptionsDlg->objectName().isEmpty())
            OptionsDlg->setObjectName(QStringLiteral("OptionsDlg"));
        OptionsDlg->resize(522, 268);
        gridLayout_3 = new QGridLayout(OptionsDlg);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox_2 = new QGroupBox(OptionsDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        leServerIP = new QLineEdit(groupBox_2);
        leServerIP->setObjectName(QStringLiteral("leServerIP"));

        horizontalLayout->addWidget(leServerIP);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        leServerPort = new QLineEdit(groupBox_2);
        leServerPort->setObjectName(QStringLiteral("leServerPort"));
        leServerPort->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(leServerPort);


        verticalLayout->addLayout(horizontalLayout);

        labelServerStatus = new QLabel(groupBox_2);
        labelServerStatus->setObjectName(QStringLiteral("labelServerStatus"));

        verticalLayout->addWidget(labelServerStatus);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(OptionsDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        leUsername = new QLineEdit(groupBox);
        leUsername->setObjectName(QStringLiteral("leUsername"));

        gridLayout->addWidget(leUsername, 0, 1, 1, 1);

        labelImage = new ImageLabel(groupBox);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelImage->sizePolicy().hasHeightForWidth());
        labelImage->setSizePolicy(sizePolicy);
        labelImage->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelImage, 2, 1, 1, 1);

        leEmail = new QLineEdit(groupBox);
        leEmail->setObjectName(QStringLiteral("leEmail"));

        gridLayout->addWidget(leEmail, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 1, 2, 1);

        groupBox_3 = new QGroupBox(OptionsDlg);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        radioGoogle = new QRadioButton(groupBox_3);
        radioGoogle->setObjectName(QStringLiteral("radioGoogle"));

        gridLayout_2->addWidget(radioGoogle, 0, 1, 1, 1);

        radioBaidu = new QRadioButton(groupBox_3);
        radioBaidu->setObjectName(QStringLiteral("radioBaidu"));

        gridLayout_2->addWidget(radioBaidu, 0, 2, 1, 1);

        btFont = new QPushButton(groupBox_3);
        btFont->setObjectName(QStringLiteral("btFont"));

        gridLayout_2->addWidget(btFont, 1, 0, 1, 3);


        gridLayout_3->addWidget(groupBox_3, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(OptionsDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 2, 1, 1, 1);

        QWidget::setTabOrder(leServerIP, leServerPort);
        QWidget::setTabOrder(leServerPort, leUsername);
        QWidget::setTabOrder(leUsername, leEmail);
        QWidget::setTabOrder(leEmail, btFont);
        QWidget::setTabOrder(btFont, buttonBox);

        retranslateUi(OptionsDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(OptionsDlg);
    } // setupUi

    void retranslateUi(QDialog *OptionsDlg)
    {
        OptionsDlg->setWindowTitle(QApplication::translate("OptionsDlg", "Options", 0));
        groupBox_2->setTitle(QApplication::translate("OptionsDlg", "Server", 0));
        label->setText(QApplication::translate("OptionsDlg", "Server IP", 0));
        label_6->setText(QApplication::translate("OptionsDlg", ":", 0));
        leServerPort->setText(QApplication::translate("OptionsDlg", "8080", 0));
        labelServerStatus->setText(QApplication::translate("OptionsDlg", "Connection status", 0));
        groupBox->setTitle(QApplication::translate("OptionsDlg", "User", 0));
        labelImage->setText(QApplication::translate("OptionsDlg", "Click me to select", 0));
        leEmail->setText(QString());
        label_3->setText(QApplication::translate("OptionsDlg", "Email", 0));
        label_2->setText(QApplication::translate("OptionsDlg", "User name", 0));
        label_4->setText(QApplication::translate("OptionsDlg", "Photo", 0));
        groupBox_3->setTitle(QApplication::translate("OptionsDlg", "Browser", 0));
        label_5->setText(QApplication::translate("OptionsDlg", "Search engine:", 0));
        radioGoogle->setText(QApplication::translate("OptionsDlg", "Google", 0));
        radioBaidu->setText(QApplication::translate("OptionsDlg", "Baidu", 0));
        btFont->setText(QApplication::translate("OptionsDlg", "Font", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsDlg: public Ui_OptionsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDLG_H
