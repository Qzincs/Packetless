/********************************************************************************
** Form generated from reading UI file 'InterfaceSelection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACESELECTION_H
#define UI_INTERFACESELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InterfaceSelection
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *deviceLabel;
    QComboBox *deviceMenu;
    QLabel *descriptionLabel;
    QLabel *deviceDescription;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *InterfaceSelectionUI)
    {
        if (InterfaceSelectionUI->objectName().isEmpty())
            InterfaceSelectionUI->setObjectName(QString::fromUtf8("InterfaceSelection"));
        InterfaceSelectionUI->resize(413, 129);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InterfaceSelectionUI->sizePolicy().hasHeightForWidth());
        InterfaceSelectionUI->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(InterfaceSelectionUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        deviceLabel = new QLabel(InterfaceSelectionUI);
        deviceLabel->setObjectName(QString::fromUtf8("deviceLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deviceLabel->sizePolicy().hasHeightForWidth());
        deviceLabel->setSizePolicy(sizePolicy1);
        deviceLabel->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, deviceLabel);

        deviceMenu = new QComboBox(InterfaceSelectionUI);
        deviceMenu->setObjectName(QString::fromUtf8("deviceMenu"));

        formLayout->setWidget(0, QFormLayout::FieldRole, deviceMenu);

        descriptionLabel = new QLabel(InterfaceSelectionUI);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(descriptionLabel->sizePolicy().hasHeightForWidth());
        descriptionLabel->setSizePolicy(sizePolicy2);

        formLayout->setWidget(1, QFormLayout::LabelRole, descriptionLabel);

        deviceDescription = new QLabel(InterfaceSelectionUI);
        deviceDescription->setObjectName(QString::fromUtf8("deviceDescription"));
        deviceDescription->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(1, QFormLayout::FieldRole, deviceDescription);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        okButton = new QPushButton(InterfaceSelectionUI);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(InterfaceSelectionUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(InterfaceSelectionUI);

        QMetaObject::connectSlotsByName(InterfaceSelectionUI);
    } // setupUi

    void retranslateUi(QDialog *InterfaceSelectionUI)
    {
        InterfaceSelectionUI->setWindowTitle(QCoreApplication::translate("InterfaceSelection", "Select capture interface", nullptr));
        deviceLabel->setText(QCoreApplication::translate("InterfaceSelection", "Interface:", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("InterfaceSelection", "Description:", nullptr));
        deviceDescription->setText(QCoreApplication::translate("InterfaceSelection", "No Description", nullptr));
        okButton->setText(QCoreApplication::translate("InterfaceSelection", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("InterfaceSelection", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceSelectionUI: public Ui_InterfaceSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACESELECTION_H
