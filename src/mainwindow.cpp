#include "mainwindow.h"
/// <summary>
/// ���Ĺرմ���ʱ���¼�
/// </summary>
/// <param name="e">�ر��¼�</param>
void MainWindow::closeEvent(QCloseEvent* e)
{
	//���͹ر��ź�
	emit close();
	//����ԭ�еĹر��¼�
	e->ignore();
}