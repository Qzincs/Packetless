#pragma once
#include <QObject>
#include <QMainWindow>
#include <QCloseEvent>

/// <summary>
/// 主窗口
/// </summary>
class MainWindow : public QMainWindow
{
	Q_OBJECT
signals:
	//窗口关闭的信号
	void close();

public slots:
	//关闭窗口时触发的事件
	void closeEvent(QCloseEvent* e) override;
};