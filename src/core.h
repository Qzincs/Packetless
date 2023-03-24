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

//����ģ�飺�����û����棬����C++��Qt֮�������ת�������̹߳������������߼���
class Core : public QObject
{
	Q_OBJECT
public:
	Core(QApplication* app, MainWindow * window, QTranslator* tran);
	void connect();
	void addTreeData();

	//Ӧ�ó���
	QApplication* app;
	//������
	MainWindow* window;

	//��ģ�����
	Ui::GUI gui;
	Packet_Sniffer sniffer;
	Analyzer analyzer;
	Packet_Send sender;

	//�����������������л�
	QTranslator* translator;
	//��������󣬴����ı�����
	QClipboard* clipboard = QGuiApplication::clipboard();
	//��ʱ�ļ�����
	QFile tempFile;


	//�������߳�
	QThread* captureThread = new QThread;
	CaptureWork* captureWork = new CaptureWork;
	//�������߳�
	QThread* processThread = new QThread;
	ProcessWork* processWork = new ProcessWork;



	//����ģ��
	TableModel tableModel;
	ListModel listModel;
	QTreeWidget* treeWidget;
	QVector<TreeData> treeData;
	//���鿴�ı�������
	int lastViewedIndex = -1;

	//����ӿڱ��
	int captureInterfaceIndex = 0;
	//ԭʼ���ݰ�
	QVector<u_char*> packetsRaw;
	//���ݰ��ַ���
	QVector<QVector<QString>> packetsStr;
	//����ԭʼ���ݰ�
	u_char* newPacketRaw = nullptr;
	//�������ݰ�����
	int newPacketRawLength = 0;
	//���ڽ����ı��ĵ�����
	int processIndex = 0;
	//�����־
	bool isSave = true;
	//���ͱ��ĵ�����
	int sendType = 0;
	//����ͳ������
	QVector<int> stat = QVector<int>(7);

//���¸�������ע�ͼ�"core.cpp"�ļ�
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