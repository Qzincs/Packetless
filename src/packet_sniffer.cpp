#include "packet_sniffer.h"
using namespace std;

/*获取网络适配器列表*/
int Packet_Sniffer::set_devs()
{
	pcap_if_t* d;
	int i = 0;

	/*查找设备出错*/
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		return -1;
	}

	/* Print the list */
	for (d = alldevs; d; d = d->next)
	{
		devs_name.push_back((d->name));
		/*printf("%d. %s\n    ", ++i, d->name);*/

		devs_ip_address.push_back(d->addresses->addr->sa_data);

		if (d->description)
			//printf(" (%s)\n", d->description);
			devs_description.push_back(d->description);
		/*else
			printf(" (No description available)\n");*/
	}
	/* Free the device list */
	//pcap_freealldevs(alldevs);
	return 1;
}

/*设置捕获的设备*/
void Packet_Sniffer::set_sniffer_devs(int dev_num)
{
	int i = 0;
	/* Jump to the selected adapter */
	for (dev_s = alldevs, i = 0; i < dev_num; dev_s = dev_s->next, i++);
	/* Open the adapter */
	if ((fp = pcap_open_live(dev_s->name,	// name of the device
		65536,							// portion of the packet to capture. 
		// 65536 grants that the whole packet will be captured on all the MACs.
		1,								// promiscuous mode (nonzero means promiscuous)
		1000,								// read timeout
		errbuf							// error buffer
	)) == NULL)
	{
		pkt_data.push_back((nullptr));
		caplen.push_back(0);
	}
}

/*设置过滤规则*/
int Packet_Sniffer::set_filter(string packet_filter)
{
	bpf_u_int32 NetMask;
	struct bpf_program fcode;
	const char* filter = packet_filter.c_str();

	if (filter != NULL)
	{
		if (dev_s->addresses != NULL)
			/* 获取接口第一个地址的掩码 */
			NetMask = ((struct sockaddr_in*)(dev_s->addresses->netmask))->sin_addr.S_un.S_addr;
		else
			/* 如果这个接口没有地址，那么我们假设这个接口在C类网络中 */
			NetMask = 0xffffff;
		// We should loop through the adapters returned by the pcap_findalldevs_ex()
		// in order to locate the correct one.
		//
		// Let's do things simpler: we suppose to be in a C class network ;-)
		//NetMask = 0xffffff;

		//compile the filter
		if (pcap_compile(fp, &fcode, filter, 1, NetMask) < 0)
		{
			/*fprintf(stderr, "\nError compiling filter: wrong syntax.\n");*/

			//pcap_close(fp);
			return -1;
		}

		//set the filter
		if (pcap_setfilter(fp, &fcode) < 0)
		{
			/*fprintf(stderr, "\nError setting the filter\n");*/

			//pcap_close(fp);
			return -2;
		}
		return 1;
	}
}

/*不采用回调函数抓取一次数据包并添加到列表中*/
bool Packet_Sniffer::set_pkt(bool mode)
{
	int res;
	const u_char* pkt_data_new;
	res = pcap_next_ex(fp, &header, &pkt_data_new);
	if (!mode)
	{
		pcap_dump((u_char*)dumpfile, header, pkt_data_new);
	}
	
	if (res == 0) 
	{
		/* Timeout elapsed */
		return true;
	}
	else if (res < 0)
	{
		return false;
	}
	else if (res > 0)
	{
		/* print pkt timestamp and pkt len */
		caplen.push_back(header->caplen);
		time_stamp.push_back(header->ts);
		
		u_char* data = (u_char*)malloc(header->caplen * sizeof(u_char));;
		memcpy(data, pkt_data_new, header->caplen);
		pkt_data.push_back(data);
	}
	return true;
}

/*打开临时文件*/
int Packet_Sniffer::set_openfile()
{
	const char* filename = data(file);
	dumpfile = pcap_dump_open(fp, filename);
	if (dumpfile == NULL) return -1;
	return 0;
}

/*关闭临时文件*/
void Packet_Sniffer::close_file()
{
	pcap_dump_close(dumpfile);
}

/*打开存储文件*/
bool Packet_Sniffer::open_file(const char* file_name)
{
	char source[PCAP_BUF_SIZE];
	const u_char* pkt_data_new;
	int res;

	if (pcap_createsrcstr(source,         // 源字符串
		PCAP_SRC_FILE,  // 我们要打开的文件
		NULL,           // 远程主机
		NULL,           // 远程主机端口
		file_name,        // 我们要打开的文件名
		errbuf          // 错误缓冲区
	) != 0)
	{
		fprintf(stderr, "\nError creating a source string\n");
		return false;
	}

	/* 打开捕获文件 */
	if ((fp = pcap_open(source,         // 设备名
						65536,          // 要捕捉的数据包的部分，65535保证能捕获到不同数据链路层上的每个数据包的全部内容
						PCAP_OPENFLAG_PROMISCUOUS,     // 混杂模式
						1000,              // 读取超时时间
						NULL,              // 远程机器验证
						errbuf         // 错误缓冲池
					)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the file %s.\n", source);
		return false;
	}
	return true;
}