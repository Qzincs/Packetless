#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QTranslator>
#include "core.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator tran;
    MainWindow* w = new MainWindow;

    //���ó���ͼ��
    QIcon logo;
    logo.addFile(QString::fromUtf8(":/GUI/Resources/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
    w->setWindowIcon(logo);

    //��ʼ������
    Core core(&a, w, &tran);
    //��ʾ������
    w->show();
    //��ʾ�豸ѡ��Ի���
    core.interfaceSelectionDialog();
    //ִ�г���
    return a.exec();
}
