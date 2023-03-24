#pragma once
#include <QObject>
#include <QDebug>
#include "packet_sniffer.h"

/// <summary>
/// 捕获子线程的实际业务类
/// </summary>
class CaptureWork : public QObject
{
	Q_OBJECT

public:
	//捕获状态，正在进行捕获时为true，停止捕获时为false
	bool flag = true;

public slots:
	void run(Packet_Sniffer* sniffer, bool mode);

	void stop();
};