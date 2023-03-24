/********************************************************************************
** Form generated from reading UI file 'About.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QGridLayout* gridLayout;
    QVBoxLayout* verticalLayout_3;
    QVBoxLayout* verticalLayout;
    QLabel* labelIntro;
    QSplitter* splitter;
    QLabel* labelName;
    QLabel* labelCompile;
    QVBoxLayout* verticalLayout_2;
    QLabel* labelKFC;
    QPushButton* donateButton;

    void setupUi(QDialog* AboutUI)
    {
        if (AboutUI->objectName().isEmpty())
            AboutUI->setObjectName(QString::fromUtf8("AboutUI"));
        AboutUI->resize(723, 239);
        gridLayout = new QGridLayout(AboutUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelIntro = new QLabel(AboutUI);
        labelIntro->setObjectName(QString::fromUtf8("labelIntro"));
        QFont font;
        font.setPointSize(12);
        labelIntro->setFont(font);
        labelIntro->setTextFormat(Qt::RichText);
        labelIntro->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelIntro);

        splitter = new QSplitter(AboutUI);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        labelName = new QLabel(splitter);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setFont(font);
        labelName->setAlignment(Qt::AlignCenter);
        labelName->setWordWrap(true);
        splitter->addWidget(labelName);

        verticalLayout->addWidget(splitter);

        labelCompile = new QLabel(AboutUI);
        labelCompile->setObjectName(QString::fromUtf8("labelCompile"));
        QFont font1;
        font1.setPointSize(11);
        labelCompile->setFont(font1);
        labelCompile->setAlignment(Qt::AlignCenter);
        labelCompile->setWordWrap(true);

        verticalLayout->addWidget(labelCompile);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelKFC = new QLabel(AboutUI);
        labelKFC->setObjectName(QString::fromUtf8("labelKFC"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelKFC->sizePolicy().hasHeightForWidth());
        labelKFC->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(50);
        labelKFC->setFont(font2);

        verticalLayout_2->addWidget(labelKFC, 0, Qt::AlignHCenter);

        donateButton = new QPushButton(AboutUI);
        donateButton->setObjectName(QString::fromUtf8("donateButton"));
        sizePolicy1.setHeightForWidth(donateButton->sizePolicy().hasHeightForWidth());
        donateButton->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Consolas"));
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        donateButton->setFont(font3);
        donateButton->setAutoFillBackground(false);

        verticalLayout_2->addWidget(donateButton, 0, Qt::AlignHCenter);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(AboutUI);

        QMetaObject::connectSlotsByName(AboutUI);
    } // setupUi

    void retranslateUi(QDialog* AboutUI)
    {
        AboutUI->setWindowTitle(QCoreApplication::translate("AboutUI", "About", nullptr));
        labelIntro->setText(QCoreApplication::translate("AboutUI", "Packetless: A Lightweight Protocol Analyzer", nullptr));
        labelName->setText(QCoreApplication::translate("AboutUI", "Author: Litong Deng, Jiaxin Liu, Yankai Wang, Yimin Zhao", nullptr));
        labelCompile->setText(QCoreApplication::translate("AboutUI", "Compiled using Microsoft Visual Studio 2022 with Winpcap 4.1.2 and Qt 5.14.2.", nullptr));
        labelKFC->setText(QCoreApplication::translate("AboutUI", "KFC Crazy Thursday, V US 50!!!", nullptr));
        donateButton->setText(QCoreApplication::translate("AboutUI", "Donate!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutUI: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
