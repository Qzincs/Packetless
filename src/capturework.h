#pragma once
#include <QObject>
#include <QDebug>
#include "packet_sniffer.h"

/// <summary>
/// �������̵߳�ʵ��ҵ����
/// </summary>
class CaptureWork : public QObject
{
	Q_OBJECT

public:
	//����״̬�����ڽ��в���ʱΪtrue��ֹͣ����ʱΪfalse
	bool flag = true;

public slots:
	void run(Packet_Sniffer* sniffer, bool mode);

	void stop();
};