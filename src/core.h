#pragma once
#include <String>
#include <QMainWindow>
#include <QObject>
#include <QVector>
#include <QDialog>
#include <QDebug>
#include <QThread>
#include <QTreeWidget>
#include <QTranslator>
#include <QSettings>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipBoard>
#include <QDir>
#include <QFile>
#include <QRegEXp>
#include <QValidator>
#include "mainwindow.h"
#include "packet_sniffer.h"
#include "analyzer.h"
#include "packet_send.h"
#include "gui.h"
#include "interfaceui.h"
#include "sendui.h"
#include "aboutui.h"
#include "tablemodel.h"
#include "listmodel.h"
#include "treedata.h"
#include "capturework.h"
#include "processwork.h"

//核心模块：绘制用户界面，处理C++与Qt之间的数据转换，多线程管理及程序整体逻辑。
class Core : public QObject
{
	Q_OBJECT
public:
	Core(QApplication* app, MainWindow * window, QTranslator* tran);
	void connect();
	void addTreeData();

	//应用程序
	QApplication* app;
	//主窗口
	MainWindow* window;

	//各模块对象
	Ui::GUI gui;
	Packet_Sniffer sniffer;
	Analyzer analyzer;
	Packet_Send sender;

	//翻译器，处理语言切换
	QTranslator* translator;
	//剪贴板对象，处理文本复制
	QClipboard* clipboard = QGuiApplication::clipboard();
	//临时文件对象
	QFile tempFile;


	//捕获子线程
	QThread* captureThread = new QThread;
	CaptureWork* captureWork = new CaptureWork;
	//解析子线程
	QThread* processThread = new QThread;
	ProcessWork* processWork = new ProcessWork;



	//数据模型
	TableModel tableModel;
	ListModel listModel;
	QTreeWidget* treeWidget;
	QVector<TreeData> treeData;
	//最后查看的报文索引
	int lastViewedIndex = -1;

	//捕获接口编号
	int captureInterfaceIndex = 0;
	//原始数据包
	QVector<u_char*> packetsRaw;
	//数据包字符串
	QVector<QVector<QString>> packetsStr;
	//最新原始数据包
	u_char* newPacketRaw = nullptr;
	//最新数据包长度
	int newPacketRawLength = 0;
	//正在解析的报文的索引
	int processIndex = 0;
	//保存标志
	bool isSave = true;
	//发送报文的类型
	int sendType = 0;
	//报文统计数据
	QVector<int> stat = QVector<int>(7);

//以下各函数的注释见"core.cpp"文件
signals:
	void captureStarted(Packet_Sniffer* sniffer, bool mode);
	void processFinished();
	

public slots:	
	void onTableviewClicked(const QModelIndex& index);
	void startCapture();
	void stopCapture();
	void restartCapture();
	void openFile();
	bool saveFile();
	void onPacketCaptured();
	void quit();
	void interfaceSelectionDialog();
	void sendDialog();
	void changeToChinese();
	void changeToEnglish();
	void aboutDialog();
	void applyFilter();
	void clearFilter();
	void tableDataCopy();
	void listDataCopy();
};