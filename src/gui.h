/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tablemodel.h"
#include "listmodel.h"

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QAction* actionStart;
    QAction* actionStop;
    QAction* actionRestart;
    QAction* actionSave;
    QAction* actionOpen;
    QAction* actionSend;
    QAction* actionQuit;
    QAction* actionSelectInterface;
    QAction* actionEnglish;
    QAction* actionChinese;
    QAction* actionAbout;
    QWidget* centralWidget;
    QVBoxLayout* verticalLayout;
    QHBoxLayout* FilterLayout;
    QLabel* labelFilter;
    QLineEdit* inputFilter;
    QPushButton* buttonApply;
    QPushButton* buttonClear;
    QTableView* tableView;
    QHBoxLayout* horizontalLayout_2;
    QTreeWidget* treeWidget;
    QListView* listView;
    QMenuBar* menuBar;
    QMenu* menuFile;
    QMenu* menuCapture;
    QMenu* menuHelp;
    QMenu* menuLanguage;
    QToolBar* mainToolBar;
    QStatusBar* statusBar;
    QLabel* labelStat;

    void setupUi(QMainWindow* GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName(QString::fromUtf8("GUI"));
        GUI->resize(1600, 900);
        actionStart = new QAction(GUI);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/GUI/Resources/Start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon);
        actionStop = new QAction(GUI);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionStop->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/GUI/Resources/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon1);
        actionRestart = new QAction(GUI);
        actionRestart->setObjectName(QString::fromUtf8("actionRestart"));
        actionRestart->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/GUI/Resources/restart.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRestart->setIcon(icon2);
        actionSave = new QAction(GUI);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/GUI/Resources/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionOpen = new QAction(GUI);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/GUI/Resources/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon4);
        actionSend = new QAction(GUI);
        actionSend->setObjectName(QString::fromUtf8("actionSend"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/GUI/Resources/send.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSend->setIcon(icon5);
        actionQuit = new QAction(GUI);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionSelectInterface = new QAction(GUI);
        actionSelectInterface->setObjectName(QString::fromUtf8("actionSelectInterface"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/GUI/Resources/device.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectInterface->setIcon(icon7);
        actionEnglish = new QAction(GUI);
        actionEnglish->setObjectName(QString::fromUtf8("actionEnglish"));
        actionChinese = new QAction(GUI);
        actionChinese->setObjectName(QString::fromUtf8("actionChinese"));
        actionAbout = new QAction(GUI);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(GUI);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        FilterLayout = new QHBoxLayout();
        FilterLayout->setSpacing(6);
        FilterLayout->setObjectName(QString::fromUtf8("FilterLayout"));
        labelFilter = new QLabel(centralWidget);
        labelFilter->setObjectName(QString::fromUtf8("labelFilter"));

        FilterLayout->addWidget(labelFilter);

        inputFilter = new QLineEdit(centralWidget);
        inputFilter->setObjectName(QString::fromUtf8("inputFilter"));

        FilterLayout->addWidget(inputFilter);

        buttonApply = new QPushButton(centralWidget);
        buttonApply->setObjectName(QString::fromUtf8("buttonApply"));

        FilterLayout->addWidget(buttonApply);

        buttonClear = new QPushButton(centralWidget);
        buttonClear->setObjectName(QString::fromUtf8("buttonClear"));

        FilterLayout->addWidget(buttonClear);


        verticalLayout->addLayout(FilterLayout);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSortingEnabled(true);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem* __qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setHeaderHidden(true);

        horizontalLayout_2->addWidget(treeWidget);

        listView = new QListView(centralWidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        horizontalLayout_2->addWidget(listView);


        verticalLayout->addLayout(horizontalLayout_2);

        GUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 948, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuCapture = new QMenu(menuBar);
        menuCapture->setObjectName(QString::fromUtf8("menuCapture"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuLanguage = new QMenu(menuBar);
        menuLanguage->setObjectName(QString::fromUtf8("menuLanguage"));
        GUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUI);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUI);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GUI->setStatusBar(statusBar);
        labelStat = new QLabel();
        statusBar->addWidget(labelStat);
        labelStat->setText("");
        labelStat->setAlignment(Qt::AlignLeft);
        QWidget::setTabOrder(buttonApply, inputFilter);
        QWidget::setTabOrder(inputFilter, buttonClear);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCapture->menuAction());
        menuBar->addAction(menuLanguage->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionQuit);
        menuCapture->addAction(actionStart);
        menuCapture->addAction(actionStop);
        menuCapture->addAction(actionRestart);
        menuHelp->addAction(actionAbout);
        menuLanguage->addAction(actionEnglish);
        menuLanguage->addAction(actionChinese);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSelectInterface);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionStart);
        mainToolBar->addAction(actionStop);
        mainToolBar->addAction(actionRestart);
        mainToolBar->addAction(actionSend);

        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QMainWindow* GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "Packetless", nullptr));
        actionStart->setText(QCoreApplication::translate("GUI", "&Start", nullptr));
#if QT_CONFIG(tooltip)
        actionStart->setToolTip(QCoreApplication::translate("GUI", "Start capturing packets", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionStart->setShortcut(QCoreApplication::translate("GUI", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionStop->setText(QCoreApplication::translate("GUI", "&Stop", nullptr));
#if QT_CONFIG(tooltip)
        actionStop->setToolTip(QCoreApplication::translate("GUI", "Stop capturing packets", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionStop->setShortcut(QCoreApplication::translate("GUI", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRestart->setText(QCoreApplication::translate("GUI", "&Restart", nullptr));
#if QT_CONFIG(tooltip)
        actionRestart->setToolTip(QCoreApplication::translate("GUI", "Restart current capture", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRestart->setShortcut(QCoreApplication::translate("GUI", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("GUI", "&Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("GUI", "Save this capture file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("GUI", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("GUI", "&Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("GUI", "Open a capture file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("GUI", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSend->setText(QCoreApplication::translate("GUI", "Send", nullptr));
#if QT_CONFIG(tooltip)
        actionSend->setToolTip(QCoreApplication::translate("GUI", "Send a packet", nullptr));
#endif // QT_CONFIG(tooltip)
        actionQuit->setText(QCoreApplication::translate("GUI", "&Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("GUI", "Quit the application", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("GUI", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelectInterface->setText(QCoreApplication::translate("GUI", "Select capture interface", nullptr));
        actionEnglish->setText(QCoreApplication::translate("GUI", "English", nullptr));
#if QT_CONFIG(tooltip)
        actionEnglish->setToolTip(QCoreApplication::translate("GUI", "change language to English", nullptr));
#endif // QT_CONFIG(tooltip)
        actionChinese->setText(QCoreApplication::translate("GUI", "\344\270\255\346\226\207", nullptr));
#if QT_CONFIG(tooltip)
        actionChinese->setToolTip(QCoreApplication::translate("GUI", "change language to Chinese", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAbout->setText(QCoreApplication::translate("GUI", "&About", nullptr));
        labelFilter->setText(QCoreApplication::translate("GUI", "Filter", nullptr));
        buttonApply->setText(QCoreApplication::translate("GUI", "Apply", nullptr));
        buttonClear->setText(QCoreApplication::translate("GUI", "Clear", nullptr));
        menuFile->setTitle(QCoreApplication::translate("GUI", "&File", nullptr));
        menuCapture->setTitle(QCoreApplication::translate("GUI", "&Capture", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("GUI", "&Help", nullptr));
        menuLanguage->setTitle(QCoreApplication::translate("GUI", "&Language", nullptr));
    } // retranslateUi

};


namespace Ui {
    class GUI : public Ui_GUI
    {
    public:       
        QAction* tableCopyAction;
        QAction* listCopyAction;

        /// <summary>
        /// 初始化View，将Model和View进行绑定
        /// </summary>
        /// <param name="table">概要数据模型</param>
        /// <param name="list">原始数据模型</param>
        void setupView(TableModel& table, ListModel& list)
        {
            //绑定表格和其数据模型
            tableView->setModel(&table);
            //最后一列拉伸
            tableView->horizontalHeader()->setStretchLastSection(true);
            //列可移动
            tableView->horizontalHeader()->setSectionsMovable(true);
            tableView->horizontalHeader()->setMinimumSectionSize(100);
            tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            //设置点击选择整行
            tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
            //设置一次只能选中一行
            tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            //设置上下文菜单，添加复制菜单
            tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
            tableCopyAction = new QAction(QObject::tr("Copy"), tableView);
            tableView->addAction(tableCopyAction);
            
            //绑定列表和其数据模型
            listView->setModel(&list);
            //设置上下文菜单，添加复制菜单
            listView->setContextMenuPolicy(Qt::ActionsContextMenu);
            listCopyAction = new QAction(QObject::tr("Copy"), listView);
            listView->addAction(listCopyAction);
            //设置树的列数为1
            treeWidget->setColumnCount(1);
            //点击概要信息时显示对应原始数据
            QObject::connect(tableView, &QTableView::clicked, &list, &ListModel::onTableviewClicked);
        }
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
