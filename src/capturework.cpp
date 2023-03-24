#include "capturework.h"

/// <summary>
/// 开始捕获数据包
/// </summary>
/// <param name="sniffer">捕获模块对象</param>
/// <param name="mode">如果设为false，则抓包的同时将数据包存入文件</param>
void CaptureWork::run(Packet_Sniffer* sniffer, bool mode)
{
	flag = true;
	bool res = true;
	//sniffer->set_snffer_devs(index);
	while (flag)
	{
		res = (sniffer->set_pkt(mode));
		if (!res)
		{
			flag = false;
		}

	}
}

/// <summary>
/// 停止捕获数据包
/// </summary>
void CaptureWork::stop()
{
	flag = false;
}