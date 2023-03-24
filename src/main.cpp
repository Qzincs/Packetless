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

    //设置程序图标
    QIcon logo;
    logo.addFile(QString::fromUtf8(":/GUI/Resources/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
    w->setWindowIcon(logo);

    //初始化程序
    Core core(&a, w, &tran);
    //显示主界面
    w->show();
    //显示设备选择对话框
    core.interfaceSelectionDialog();
    //执行程序
    return a.exec();
}
