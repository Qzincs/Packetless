#include "capturework.h"

/// <summary>
/// ��ʼ�������ݰ�
/// </summary>
/// <param name="sniffer">����ģ�����</param>
/// <param name="mode">�����Ϊfalse����ץ����ͬʱ�����ݰ������ļ�</param>
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
/// ֹͣ�������ݰ�
/// </summary>
void CaptureWork::stop()
{
	flag = false;
}