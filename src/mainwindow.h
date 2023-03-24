#pragma once
#include <QObject>
#include <QMainWindow>
#include <QCloseEvent>

/// <summary>
/// ������
/// </summary>
class MainWindow : public QMainWindow
{
	Q_OBJECT
signals:
	//���ڹرյ��ź�
	void close();

public slots:
	//�رմ���ʱ�������¼�
	void closeEvent(QCloseEvent* e) override;
};