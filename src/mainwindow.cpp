#include "mainwindow.h"
/// <summary>
/// 更改关闭窗口时的事件
/// </summary>
/// <param name="e">关闭事件</param>
void MainWindow::closeEvent(QCloseEvent* e)
{
	//发送关闭信号
	emit close();
	//忽略原有的关闭事件
	e->ignore();
}