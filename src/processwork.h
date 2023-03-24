#pragma once
#include <QObject>


/// <summary>
/// �������̵߳�ʵ��ҵ����
/// </summary>
class ProcessWork : public QObject
{
	Q_OBJECT

public:
	ProcessWork();	

signals:
	//������һ�����ݰ����ź�
	void next();

public slots:
	//׼���ý�����һ�����ݰ�
	void readyForNext()
	{
		emit next();
	}

};