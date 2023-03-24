/********************************************************************************
** Form generated from reading UI file 'Send.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEND_H
#define UI_SEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Send
{
public:
    QGroupBox *typeBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *TypeLayout;
    QRadioButton *MAC;
    QRadioButton *IPv4;
    QRadioButton *ARP;
    QRadioButton *ICMP;
    QRadioButton *UDP;
    QRadioButton *TCP;
    QGroupBox *macBox;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *macSrc;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLineEdit *macDst;
    QGroupBox *ipBox;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QLineEdit *ipSrc;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLineEdit *ipDst;
    QGroupBox *ipFlags;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *reserved;
    QCheckBox *df;
    QCheckBox *mf;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QLineEdit *ipDscp;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_6;
    QLineEdit *ipEcn;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_8;
    QLineEdit *ipTtl;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_9;
    QLineEdit *ipOffset;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_7;
    QLineEdit *ipId;
    QGroupBox *udpBox;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_10;
    QLineEdit *udpSrcPort;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_11;
    QLineEdit *udpDstPort;
    QGroupBox *arpBox;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_16;
    QLineEdit *arpOpCode;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_13;
    QLineEdit *arpSrcMac;
    QVBoxLayout *verticalLayout_16;
    QLabel *label_12;
    QLineEdit *arpDstMac;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_15;
    QLineEdit *arpSrcIp;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_14;
    QLineEdit *arpDstIp;
    QGroupBox *icmpBox;
    QVBoxLayout *verticalLayout_26;
    QVBoxLayout *verticalLayout_22;
    QLabel *label_17;
    QLineEdit *icmpType;
    QVBoxLayout *verticalLayout_23;
    QLabel *label_18;
    QLineEdit *icmpCode;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_19;
    QLineEdit *icmpId;
    QVBoxLayout *verticalLayout_25;
    QLabel *label_20;
    QLineEdit *icmpSeq;
    QGroupBox *tcpBox;
    QVBoxLayout *verticalLayout_35;
    QVBoxLayout *verticalLayout_28;
    QLabel *label_21;
    QLineEdit *tcpSrcPort;
    QVBoxLayout *verticalLayout_29;
    QLabel *label_22;
    QLineEdit *tcpDstPort;
    QVBoxLayout *verticalLayout_27;
    QLabel *label_23;
    QLineEdit *tcpSeq;
    QVBoxLayout *verticalLayout_30;
    QLabel *label_24;
    QLineEdit *tcpAck;
    QVBoxLayout *verticalLayout_31;
    QLabel *label_25;
    QLineEdit *tcpOffset;
    QGroupBox *tcpFlags;
    QGridLayout *gridLayout;
    QCheckBox *AEC;
    QCheckBox *CWR;
    QCheckBox *ECE;
    QCheckBox *URG;
    QCheckBox *ACK;
    QCheckBox *PSH;
    QCheckBox *RST;
    QCheckBox *SYN;
    QCheckBox *FIN;
    QVBoxLayout *verticalLayout_32;
    QLabel *label_26;
    QLineEdit *tcpWindow;
    QVBoxLayout *verticalLayout_33;
    QLabel *label_27;
    QLineEdit *tcpUgPointer;
    QVBoxLayout *verticalLayout_34;
    QLabel *label_28;
    QLineEdit *tcpOptions;
    QGroupBox *dataBox;
    QVBoxLayout *verticalLayout_36;
    QPlainTextEdit *data;
    QWidget *layoutWidget_22;
    QVBoxLayout *verticalLayout_37;
    QLabel *label_29;
    QSpinBox *times;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *fileButton;
    QPushButton *sendButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Send)
    {
        if (Send->objectName().isEmpty())
            Send->setObjectName(QString::fromUtf8("Send"));
        Send->setEnabled(true);
        Send->resize(1020, 781);
        typeBox = new QGroupBox(Send);
        typeBox->setObjectName(QString::fromUtf8("typeBox"));
        typeBox->setGeometry(QRect(20, 30, 691, 60));
        verticalLayout = new QVBoxLayout(typeBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        TypeLayout = new QHBoxLayout();
        TypeLayout->setObjectName(QString::fromUtf8("TypeLayout"));
        MAC = new QRadioButton(typeBox);
        MAC->setObjectName(QString::fromUtf8("MAC"));
        MAC->setText(QString::fromUtf8("MAC"));
        MAC->setChecked(true);

        TypeLayout->addWidget(MAC);

        IPv4 = new QRadioButton(typeBox);
        IPv4->setObjectName(QString::fromUtf8("IPv4"));
        IPv4->setText(QString::fromUtf8("IPv4"));

        TypeLayout->addWidget(IPv4);

        ARP = new QRadioButton(typeBox);
        ARP->setObjectName(QString::fromUtf8("ARP"));
        ARP->setText(QString::fromUtf8("ARP"));

        TypeLayout->addWidget(ARP);

        ICMP = new QRadioButton(typeBox);
        ICMP->setObjectName(QString::fromUtf8("ICMP"));
        ICMP->setText(QString::fromUtf8("ICMP"));

        TypeLayout->addWidget(ICMP);

        UDP = new QRadioButton(typeBox);
        UDP->setObjectName(QString::fromUtf8("UDP"));
        UDP->setText(QString::fromUtf8("UDP"));

        TypeLayout->addWidget(UDP);

        TCP = new QRadioButton(typeBox);
        TCP->setObjectName(QString::fromUtf8("TCP"));
        TCP->setText(QString::fromUtf8("TCP"));

        TypeLayout->addWidget(TCP);


        verticalLayout->addLayout(TypeLayout);

        macBox = new QGroupBox(Send);
        macBox->setObjectName(QString::fromUtf8("macBox"));
        macBox->setGeometry(QRect(20, 100, 421, 87));
        horizontalLayout_3 = new QHBoxLayout(macBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(macBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        macSrc = new QLineEdit(macBox);
        macSrc->setObjectName(QString::fromUtf8("macSrc"));

        verticalLayout_2->addWidget(macSrc);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(macBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        macDst = new QLineEdit(macBox);
        macDst->setObjectName(QString::fromUtf8("macDst"));

        verticalLayout_3->addWidget(macDst);


        horizontalLayout_3->addLayout(verticalLayout_3);

        ipBox = new QGroupBox(Send);
        ipBox->setObjectName(QString::fromUtf8("ipBox"));
        ipBox->setGeometry(QRect(20, 200, 241, 484));
        verticalLayout_12 = new QVBoxLayout(ipBox);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_4 = new QLabel(ipBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_5->addWidget(label_4);

        ipSrc = new QLineEdit(ipBox);
        ipSrc->setObjectName(QString::fromUtf8("ipSrc"));

        verticalLayout_5->addWidget(ipSrc);


        verticalLayout_12->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(ipBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_4->addWidget(label_3);

        ipDst = new QLineEdit(ipBox);
        ipDst->setObjectName(QString::fromUtf8("ipDst"));

        verticalLayout_4->addWidget(ipDst);


        verticalLayout_12->addLayout(verticalLayout_4);

        ipFlags = new QGroupBox(ipBox);
        ipFlags->setObjectName(QString::fromUtf8("ipFlags"));
        verticalLayout_9 = new QVBoxLayout(ipFlags);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        reserved = new QCheckBox(ipFlags);
        reserved->setObjectName(QString::fromUtf8("reserved"));

        horizontalLayout_4->addWidget(reserved);

        df = new QCheckBox(ipFlags);
        df->setObjectName(QString::fromUtf8("df"));

        horizontalLayout_4->addWidget(df);

        mf = new QCheckBox(ipFlags);
        mf->setObjectName(QString::fromUtf8("mf"));

        horizontalLayout_4->addWidget(mf);


        verticalLayout_9->addLayout(horizontalLayout_4);


        verticalLayout_12->addWidget(ipFlags);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_5 = new QLabel(ipBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_6->addWidget(label_5);

        ipDscp = new QLineEdit(ipBox);
        ipDscp->setObjectName(QString::fromUtf8("ipDscp"));
#if QT_CONFIG(tooltip)
        ipDscp->setToolTip(QString::fromUtf8("0~63"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_6->addWidget(ipDscp);


        verticalLayout_12->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_6 = new QLabel(ipBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_7->addWidget(label_6);

        ipEcn = new QLineEdit(ipBox);
        ipEcn->setObjectName(QString::fromUtf8("ipEcn"));
#if QT_CONFIG(tooltip)
        ipEcn->setToolTip(QString::fromUtf8("0~3"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_7->addWidget(ipEcn);


        verticalLayout_12->addLayout(verticalLayout_7);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_8 = new QLabel(ipBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_10->addWidget(label_8);

        ipTtl = new QLineEdit(ipBox);
        ipTtl->setObjectName(QString::fromUtf8("ipTtl"));
#if QT_CONFIG(tooltip)
        ipTtl->setToolTip(QString::fromUtf8("0~255"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_10->addWidget(ipTtl);


        verticalLayout_12->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_9 = new QLabel(ipBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_11->addWidget(label_9);

        ipOffset = new QLineEdit(ipBox);
        ipOffset->setObjectName(QString::fromUtf8("ipOffset"));
#if QT_CONFIG(tooltip)
        ipOffset->setToolTip(QString::fromUtf8("0~8191"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_11->addWidget(ipOffset);


        verticalLayout_12->addLayout(verticalLayout_11);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_7 = new QLabel(ipBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_8->addWidget(label_7);

        ipId = new QLineEdit(ipBox);
        ipId->setObjectName(QString::fromUtf8("ipId"));
#if QT_CONFIG(tooltip)
        ipId->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_8->addWidget(ipId);


        verticalLayout_12->addLayout(verticalLayout_8);

        udpBox = new QGroupBox(Send);
        udpBox->setObjectName(QString::fromUtf8("udpBox"));
        udpBox->setGeometry(QRect(270, 540, 197, 142));
        verticalLayout_15 = new QVBoxLayout(udpBox);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        label_10 = new QLabel(udpBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_13->addWidget(label_10);

        udpSrcPort = new QLineEdit(udpBox);
        udpSrcPort->setObjectName(QString::fromUtf8("udpSrcPort"));
#if QT_CONFIG(tooltip)
        udpSrcPort->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_13->addWidget(udpSrcPort);


        verticalLayout_15->addLayout(verticalLayout_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        label_11 = new QLabel(udpBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_14->addWidget(label_11);

        udpDstPort = new QLineEdit(udpBox);
        udpDstPort->setObjectName(QString::fromUtf8("udpDstPort"));
#if QT_CONFIG(tooltip)
        udpDstPort->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_14->addWidget(udpDstPort);


        verticalLayout_15->addLayout(verticalLayout_14);

        arpBox = new QGroupBox(Send);
        arpBox->setObjectName(QString::fromUtf8("arpBox"));
        arpBox->setGeometry(QRect(270, 200, 197, 307));
        verticalLayout_21 = new QVBoxLayout(arpBox);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_16 = new QLabel(arpBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        verticalLayout_20->addWidget(label_16);

        arpOpCode = new QLineEdit(arpBox);
        arpOpCode->setObjectName(QString::fromUtf8("arpOpCode"));
#if QT_CONFIG(tooltip)
        arpOpCode->setToolTip(QString::fromUtf8("0~4"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_20->addWidget(arpOpCode);


        verticalLayout_21->addLayout(verticalLayout_20);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        label_13 = new QLabel(arpBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        verticalLayout_17->addWidget(label_13);

        arpSrcMac = new QLineEdit(arpBox);
        arpSrcMac->setObjectName(QString::fromUtf8("arpSrcMac"));

        verticalLayout_17->addWidget(arpSrcMac);


        verticalLayout_21->addLayout(verticalLayout_17);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        label_12 = new QLabel(arpBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_16->addWidget(label_12);

        arpDstMac = new QLineEdit(arpBox);
        arpDstMac->setObjectName(QString::fromUtf8("arpDstMac"));

        verticalLayout_16->addWidget(arpDstMac);


        verticalLayout_21->addLayout(verticalLayout_16);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        label_15 = new QLabel(arpBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        verticalLayout_19->addWidget(label_15);

        arpSrcIp = new QLineEdit(arpBox);
        arpSrcIp->setObjectName(QString::fromUtf8("arpSrcIp"));

        verticalLayout_19->addWidget(arpSrcIp);


        verticalLayout_21->addLayout(verticalLayout_19);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        label_14 = new QLabel(arpBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout_18->addWidget(label_14);

        arpDstIp = new QLineEdit(arpBox);
        arpDstIp->setObjectName(QString::fromUtf8("arpDstIp"));

        verticalLayout_18->addWidget(arpDstIp);


        verticalLayout_21->addLayout(verticalLayout_18);

        icmpBox = new QGroupBox(Send);
        icmpBox->setObjectName(QString::fromUtf8("icmpBox"));
        icmpBox->setGeometry(QRect(720, 110, 197, 252));
        verticalLayout_26 = new QVBoxLayout(icmpBox);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        label_17 = new QLabel(icmpBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        verticalLayout_22->addWidget(label_17);

        icmpType = new QLineEdit(icmpBox);
        icmpType->setObjectName(QString::fromUtf8("icmpType"));
#if QT_CONFIG(tooltip)
        icmpType->setToolTip(QString::fromUtf8("0~255"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_22->addWidget(icmpType);


        verticalLayout_26->addLayout(verticalLayout_22);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        label_18 = new QLabel(icmpBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        verticalLayout_23->addWidget(label_18);

        icmpCode = new QLineEdit(icmpBox);
        icmpCode->setObjectName(QString::fromUtf8("icmpCode"));
#if QT_CONFIG(tooltip)
        icmpCode->setToolTip(QString::fromUtf8("0~255"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_23->addWidget(icmpCode);


        verticalLayout_26->addLayout(verticalLayout_23);

        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        label_19 = new QLabel(icmpBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        verticalLayout_24->addWidget(label_19);

        icmpId = new QLineEdit(icmpBox);
        icmpId->setObjectName(QString::fromUtf8("icmpId"));
#if QT_CONFIG(tooltip)
        icmpId->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_24->addWidget(icmpId);


        verticalLayout_26->addLayout(verticalLayout_24);

        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        label_20 = new QLabel(icmpBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        verticalLayout_25->addWidget(label_20);

        icmpSeq = new QLineEdit(icmpBox);
        icmpSeq->setObjectName(QString::fromUtf8("icmpSeq"));
#if QT_CONFIG(tooltip)
        icmpSeq->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_25->addWidget(icmpSeq);


        verticalLayout_26->addLayout(verticalLayout_25);

        tcpBox = new QGroupBox(Send);
        tcpBox->setObjectName(QString::fromUtf8("tcpBox"));
        tcpBox->setEnabled(true);
        tcpBox->setGeometry(QRect(480, 100, 215, 589));
        verticalLayout_35 = new QVBoxLayout(tcpBox);
        verticalLayout_35->setObjectName(QString::fromUtf8("verticalLayout_35"));
        verticalLayout_28 = new QVBoxLayout();
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        label_21 = new QLabel(tcpBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        verticalLayout_28->addWidget(label_21);

        tcpSrcPort = new QLineEdit(tcpBox);
        tcpSrcPort->setObjectName(QString::fromUtf8("tcpSrcPort"));
#if QT_CONFIG(tooltip)
        tcpSrcPort->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_28->addWidget(tcpSrcPort);


        verticalLayout_35->addLayout(verticalLayout_28);

        verticalLayout_29 = new QVBoxLayout();
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        label_22 = new QLabel(tcpBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        verticalLayout_29->addWidget(label_22);

        tcpDstPort = new QLineEdit(tcpBox);
        tcpDstPort->setObjectName(QString::fromUtf8("tcpDstPort"));
#if QT_CONFIG(tooltip)
        tcpDstPort->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_29->addWidget(tcpDstPort);


        verticalLayout_35->addLayout(verticalLayout_29);

        verticalLayout_27 = new QVBoxLayout();
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        label_23 = new QLabel(tcpBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_27->addWidget(label_23);

        tcpSeq = new QLineEdit(tcpBox);
        tcpSeq->setObjectName(QString::fromUtf8("tcpSeq"));
#if QT_CONFIG(tooltip)
        tcpSeq->setToolTip(QString::fromUtf8("0~4294967295"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_27->addWidget(tcpSeq);


        verticalLayout_35->addLayout(verticalLayout_27);

        verticalLayout_30 = new QVBoxLayout();
        verticalLayout_30->setObjectName(QString::fromUtf8("verticalLayout_30"));
        label_24 = new QLabel(tcpBox);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        verticalLayout_30->addWidget(label_24);

        tcpAck = new QLineEdit(tcpBox);
        tcpAck->setObjectName(QString::fromUtf8("tcpAck"));
#if QT_CONFIG(tooltip)
        tcpAck->setToolTip(QString::fromUtf8("0~4294967295"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_30->addWidget(tcpAck);


        verticalLayout_35->addLayout(verticalLayout_30);

        verticalLayout_31 = new QVBoxLayout();
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        label_25 = new QLabel(tcpBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        verticalLayout_31->addWidget(label_25);

        tcpOffset = new QLineEdit(tcpBox);
        tcpOffset->setObjectName(QString::fromUtf8("tcpOffset"));
#if QT_CONFIG(tooltip)
        tcpOffset->setToolTip(QString::fromUtf8("5~15"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_31->addWidget(tcpOffset);


        verticalLayout_35->addLayout(verticalLayout_31);

        tcpFlags = new QGroupBox(tcpBox);
        tcpFlags->setObjectName(QString::fromUtf8("tcpFlags"));
        gridLayout = new QGridLayout(tcpFlags);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        AEC = new QCheckBox(tcpFlags);
        AEC->setObjectName(QString::fromUtf8("AEC"));
        AEC->setText(QString::fromUtf8("AEC"));

        gridLayout->addWidget(AEC, 0, 0, 1, 1);

        CWR = new QCheckBox(tcpFlags);
        CWR->setObjectName(QString::fromUtf8("CWR"));
        CWR->setText(QString::fromUtf8("CWR"));

        gridLayout->addWidget(CWR, 0, 1, 1, 1);

        ECE = new QCheckBox(tcpFlags);
        ECE->setObjectName(QString::fromUtf8("ECE"));
        ECE->setText(QString::fromUtf8("ECE"));

        gridLayout->addWidget(ECE, 0, 2, 1, 1);

        URG = new QCheckBox(tcpFlags);
        URG->setObjectName(QString::fromUtf8("URG"));
        URG->setText(QString::fromUtf8("URG"));

        gridLayout->addWidget(URG, 1, 0, 1, 1);

        ACK = new QCheckBox(tcpFlags);
        ACK->setObjectName(QString::fromUtf8("ACK"));
        ACK->setText(QString::fromUtf8("ACK"));

        gridLayout->addWidget(ACK, 1, 1, 1, 1);

        PSH = new QCheckBox(tcpFlags);
        PSH->setObjectName(QString::fromUtf8("PSH"));
        PSH->setText(QString::fromUtf8("PSH"));

        gridLayout->addWidget(PSH, 1, 2, 1, 1);

        RST = new QCheckBox(tcpFlags);
        RST->setObjectName(QString::fromUtf8("RST"));
        RST->setText(QString::fromUtf8("RST"));

        gridLayout->addWidget(RST, 2, 0, 1, 1);

        SYN = new QCheckBox(tcpFlags);
        SYN->setObjectName(QString::fromUtf8("SYN"));
        SYN->setText(QString::fromUtf8("SYN"));

        gridLayout->addWidget(SYN, 2, 1, 1, 1);

        FIN = new QCheckBox(tcpFlags);
        FIN->setObjectName(QString::fromUtf8("FIN"));
        FIN->setText(QString::fromUtf8("FIN"));

        gridLayout->addWidget(FIN, 2, 2, 1, 1);


        verticalLayout_35->addWidget(tcpFlags);

        verticalLayout_32 = new QVBoxLayout();
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        label_26 = new QLabel(tcpBox);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        verticalLayout_32->addWidget(label_26);

        tcpWindow = new QLineEdit(tcpBox);
        tcpWindow->setObjectName(QString::fromUtf8("tcpWindow"));
#if QT_CONFIG(tooltip)
        tcpWindow->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_32->addWidget(tcpWindow);


        verticalLayout_35->addLayout(verticalLayout_32);

        verticalLayout_33 = new QVBoxLayout();
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        label_27 = new QLabel(tcpBox);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        verticalLayout_33->addWidget(label_27);

        tcpUgPointer = new QLineEdit(tcpBox);
        tcpUgPointer->setObjectName(QString::fromUtf8("tcpUgPointer"));
#if QT_CONFIG(tooltip)
        tcpUgPointer->setToolTip(QString::fromUtf8("0~65535"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_33->addWidget(tcpUgPointer);


        verticalLayout_35->addLayout(verticalLayout_33);

        verticalLayout_34 = new QVBoxLayout();
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        label_28 = new QLabel(tcpBox);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        verticalLayout_34->addWidget(label_28);

        tcpOptions = new QLineEdit(tcpBox);
        tcpOptions->setObjectName(QString::fromUtf8("tcpOptions"));
        

        

        verticalLayout_34->addWidget(tcpOptions);


        verticalLayout_35->addLayout(verticalLayout_34);

        dataBox = new QGroupBox(Send);
        dataBox->setObjectName(QString::fromUtf8("dataBox"));
        dataBox->setGeometry(QRect(700, 380, 280, 321));
        verticalLayout_36 = new QVBoxLayout(dataBox);
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        data = new QPlainTextEdit(dataBox);
        data->setObjectName(QString::fromUtf8("data"));
#if QT_CONFIG(tooltip)
        data->setToolTip(QString::fromUtf8("Hexadecimal format"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_36->addWidget(data);

        layoutWidget_22 = new QWidget(Send);
        layoutWidget_22->setObjectName(QString::fromUtf8("layoutWidget_22"));
        layoutWidget_22->setGeometry(QRect(720, 40, 131, 48));
        verticalLayout_37 = new QVBoxLayout(layoutWidget_22);
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        verticalLayout_37->setContentsMargins(0, 0, 0, 0);
        label_29 = new QLabel(layoutWidget_22);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        verticalLayout_37->addWidget(label_29);

        times = new QSpinBox(layoutWidget_22);
        times->setObjectName(QString::fromUtf8("times"));
        times->setValue(1);
#if QT_CONFIG(tooltip)
        times->setToolTip(QString::fromUtf8("The times the packets will be sent"));
#endif // QT_CONFIG(tooltip)

        verticalLayout_37->addWidget(times);

        layoutWidget = new QWidget(Send);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 730, 751, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(7, 0, 0, 0);
        fileButton = new QPushButton(layoutWidget);
        fileButton->setObjectName(QString::fromUtf8("fileButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fileButton->sizePolicy().hasHeightForWidth());
        fileButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(fileButton);

        sendButton = new QPushButton(layoutWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sizePolicy.setHeightForWidth(sendButton->sizePolicy().hasHeightForWidth());
        sendButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(sendButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cancelButton);


        retranslateUi(Send);
        QObject::connect(cancelButton, SIGNAL(clicked()), Send, SLOT(reject()));

        QMetaObject::connectSlotsByName(Send);
    } // setupUi

    void retranslateUi(QDialog *Send)
    {
        Send->setWindowTitle(QCoreApplication::translate("Send", "Send packets", nullptr));
#if QT_CONFIG(tooltip)
        typeBox->setToolTip(QCoreApplication::translate("Send", "The type of the packet to send", nullptr));
#endif // QT_CONFIG(tooltip)
        typeBox->setTitle(QCoreApplication::translate("Send", "Protocol Type", nullptr));
        macBox->setTitle(QCoreApplication::translate("Send", "MAC", nullptr));
        label_2->setText(QCoreApplication::translate("Send", "Source MAC", nullptr));
#if QT_CONFIG(tooltip)
        macSrc->setToolTip(QCoreApplication::translate("Send", "Hexadecimal format, no seperators, e.g. 0016EAAE3C40", nullptr));
#endif // QT_CONFIG(tooltip)
        macSrc->setPlaceholderText(QString());
        label->setText(QCoreApplication::translate("Send", "Destination MAC", nullptr));
#if QT_CONFIG(tooltip)
        macDst->setToolTip(QCoreApplication::translate("Send", "Hexadecimal format, no seperators, e.g. 0016EAAE3C40", nullptr));
#endif // QT_CONFIG(tooltip)
        ipBox->setTitle(QCoreApplication::translate("Send", "IPv4", nullptr));
        label_4->setText(QCoreApplication::translate("Send", "Source address", nullptr));
#if QT_CONFIG(tooltip)
        ipSrc->setToolTip(QCoreApplication::translate("Send", "Dotted decimal notation, e.g. 192.0.0.1", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("Send", "Destination address", nullptr));
#if QT_CONFIG(tooltip)
        ipDst->setToolTip(QCoreApplication::translate("Send", "Dotted decimal notation, e.g. 192.0.0.1", nullptr));
#endif // QT_CONFIG(tooltip)
        ipFlags->setTitle(QCoreApplication::translate("Send", "Flags", nullptr));
        reserved->setText(QCoreApplication::translate("Send", "Reserved", nullptr));
#if QT_CONFIG(tooltip)
        df->setToolTip(QCoreApplication::translate("Send", "Don't fragment", nullptr));
#endif // QT_CONFIG(tooltip)
        df->setText(QCoreApplication::translate("Send", "DF", nullptr));
#if QT_CONFIG(tooltip)
        mf->setToolTip(QCoreApplication::translate("Send", "More Fragment", nullptr));
#endif // QT_CONFIG(tooltip)
        mf->setText(QCoreApplication::translate("Send", "MF", nullptr));
        label_5->setText(QCoreApplication::translate("Send", "DSCP", nullptr));
        label_6->setText(QCoreApplication::translate("Send", "ECN", nullptr));
        label_8->setText(QCoreApplication::translate("Send", "TTL", nullptr));
        label_9->setText(QCoreApplication::translate("Send", "Offset", nullptr));
        label_7->setText(QCoreApplication::translate("Send", "ID", nullptr));
        udpBox->setTitle(QCoreApplication::translate("Send", "UDP", nullptr));
        label_10->setText(QCoreApplication::translate("Send", "Source Port", nullptr));
        label_11->setText(QCoreApplication::translate("Send", "Destination Port", nullptr));
        arpBox->setTitle(QCoreApplication::translate("Send", "ARP", nullptr));
        label_16->setText(QCoreApplication::translate("Send", "OP code", nullptr));
        label_13->setText(QCoreApplication::translate("Send", "Source MAC", nullptr));
#if QT_CONFIG(tooltip)
        arpSrcMac->setToolTip(QCoreApplication::translate("Send", "Hexadecimal format, no seperators, e.g. 0016EAAE3C40", nullptr));
#endif // QT_CONFIG(tooltip)
        label_12->setText(QCoreApplication::translate("Send", "Destination MAC", nullptr));
#if QT_CONFIG(tooltip)
        arpDstMac->setToolTip(QCoreApplication::translate("Send", "Hexadecimal format, no seperators, e.g. 0016EAAE3C40", nullptr));
#endif // QT_CONFIG(tooltip)
        label_15->setText(QCoreApplication::translate("Send", "Source IP", nullptr));
#if QT_CONFIG(tooltip)
        arpSrcIp->setToolTip(QCoreApplication::translate("Send", "Dotted decimal notation, e.g. 192.0.0.1", nullptr));
#endif // QT_CONFIG(tooltip)
        label_14->setText(QCoreApplication::translate("Send", "Destination IP", nullptr));
#if QT_CONFIG(tooltip)
        arpDstIp->setToolTip(QCoreApplication::translate("Send", "Dotted decimal notation, e.g. 192.0.0.1", nullptr));
#endif // QT_CONFIG(tooltip)
        icmpBox->setTitle(QCoreApplication::translate("Send", "ICMP", nullptr));
        label_17->setText(QCoreApplication::translate("Send", "Type", nullptr));
        label_18->setText(QCoreApplication::translate("Send", "Code", nullptr));
        label_19->setText(QCoreApplication::translate("Send", "ID", nullptr));
        label_20->setText(QCoreApplication::translate("Send", "Sequence", nullptr));
        tcpBox->setTitle(QCoreApplication::translate("Send", "TCP", nullptr));
        label_21->setText(QCoreApplication::translate("Send", "Source Port", nullptr));
        label_22->setText(QCoreApplication::translate("Send", "Destination Port", nullptr));
        label_23->setText(QCoreApplication::translate("Send", "Sequence", nullptr));
        label_24->setText(QCoreApplication::translate("Send", "Acknowledge", nullptr));
        label_25->setText(QCoreApplication::translate("Send", "Offset", nullptr));
        tcpFlags->setTitle(QCoreApplication::translate("Send", "Flags", nullptr));
        label_26->setText(QCoreApplication::translate("Send", "Window", nullptr));
        label_27->setText(QCoreApplication::translate("Send", "UG pointer", nullptr));
        label_28->setText(QCoreApplication::translate("Send", "Options", nullptr));
        dataBox->setTitle(QCoreApplication::translate("Send", "Data", nullptr));
        label_29->setText(QCoreApplication::translate("Send", "Times", nullptr));
        fileButton->setText(QCoreApplication::translate("Send", "Send files", nullptr));
        sendButton->setText(QCoreApplication::translate("Send", "Send", nullptr));
        cancelButton->setText(QCoreApplication::translate("Send", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendUI: public Ui_Send
    {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEND_H
