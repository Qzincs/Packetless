#pragma once
#include <QObject>


/// <summary>
/// 解析子线程的实际业务类
/// </summary>
class ProcessWork : public QObject
{
	Q_OBJECT

public:
	ProcessWork();	

signals:
	//解析下一个数据包的信号
	void next();

public slots:
	//准备好解析下一个数据包
	void readyForNext()
	{
		emit next();
	}

};