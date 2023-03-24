#include "packet_send.h"
using namespace std;

//send packet, make packet error: return 1, send error: retrn -1, else: return 0
int packet_send::senduser(int times) {
	int ret;
	//根据packetype选择生成数据包类型
	switch (packetype) {
		case 0:
			ret = makemac();
			break;
		case 1:
			ret = makeip4();
			break;
		case 2:
			ret = makearp();
			break;
		case 3:
			ret = makeicp();
			break;
		case 4:
			ret = makeudp();
			break;
		case 5:
			ret = maketcp();
			break;
		default:
			ret = 1;
	}
	if (ret) return 1;
	//循环发包，若出现错误则停止
	for (int i = 0; i < times; i++) {
		if ((ret = pcap_sendpacket(fp, datapack, len)) != 0)
			return -1;
	}
	return 0;
}

//send file, send error: return -1, partially sent: return 1, else: return 0
int packet_send::sendfile(int sync) {
	const char* filename = data(file);
	pcap_t* indesc;
	int res;
	struct pcap_pkthdr mpkthder;
	struct pcap_pkthdr* pktheader = &mpkthder;
	const u_char* pktdata;
	char source[PCAP_BUF_SIZE];
	char errbuf[PCAP_ERRBUF_SIZE];
	//使用C库函数算出数据包文件中数据包总长
	FILE* capfile;
	res = fopen_s(&capfile, filename, "rb");
	if (res) return -1;
	fseek(capfile, 0, SEEK_END);
	unsigned int caplen = ftell(capfile) - sizeof(struct pcap_file_header);
	fclose(capfile);
	//打开文件接口
	if (pcap_createsrcstr(source, PCAP_SRC_FILE, NULL, NULL, filename, errbuf))
		return -1;

	if ((indesc = pcap_open(source, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errbuf)) == NULL)
		return -1;
	//开辟数据包队列
	pcap_send_queue* squeue = pcap_sendqueue_alloc(caplen);
	//将文件中的数据包逐个加入队列
	while ((res = pcap_next_ex(indesc, &pktheader, &pktdata)) == 1) {
		if (pcap_sendqueue_queue(squeue, pktheader, pktdata) == -1)
			break;
	}
	//加入失败返回-1
	if (res == -1) {
		pcap_sendqueue_destroy(squeue);
		return -1;
	}
	//发送数据包队列
	res = pcap_sendqueue_transmit(fp, squeue, sync);
	//若发送的数据包数量小于队列中数据包数量，返回1
	if (res < squeue->len) {
		pcap_sendqueue_destroy(squeue);
		pcap_close(indesc);
		return 1;
	}
	//无论是否发送完，均清除队列，关闭文件接口
	pcap_sendqueue_destroy(squeue);
	pcap_close(indesc);
	return 0;
}

//make a mac packet, wrong len: return -1, make error: return 1, else: return 0
int packet_send::makemac() {
	if (len < 15) return -1;
	datapack = (unsigned char*)malloc(len);
	if (!datapack) return 1;
	//mac header
	for (int i = 0; i < 6; i++) datapack[i] = mac.dstmac[i];
	for (int i = 6; i < 12; i++) datapack[i] = mac.hostmac[i - 6];
	datapack[12] = mac.type[0];
	datapack[13] = mac.type[1];
	//data
	for (int i = 14; i < len; i++) datapack[i] = userpack[i - 14];
	return 0;
}

//make a ipv4 packet, wrong len: return -1, make error: return 1, else: return 0
int packet_send::makeip4() {
	if (len < 35) return -1;
	datapack = (unsigned char*)malloc(len);
	if (!datapack) return 1;
	//mac header
	for (int i = 0; i < 6; i++) datapack[i] = mac.dstmac[i];
	for (int i = 6; i < 12; i++) datapack[i] = mac.hostmac[i - 6];
	datapack[12] = 8;
	datapack[13] = 0;
	//if (ip4.optlen) datapack[14] = 64 + ip4.optlen;
	//else datapack[14] = 0x45;
	//ipv4 header
	datapack[14] = 0x45;
	datapack[15] = (ip4.dscp << 2) + ip4.ecn;
	datapack[16] = (len - 14) >> 8;
	datapack[17] = (len - 14);
	datapack[18] = ip4.id >> 8;
	datapack[19] = ip4.id;
	datapack[20] = (ip4.depart << 5) + (ip4.offset >> 8);
	datapack[21] = ip4.offset;
	datapack[22] = ip4.ttl;
	datapack[23] = ip4.ptc;
	datapack[24] = 0;
	datapack[25] = 0;
	for (int i = 26; i < 30; i++) datapack[i] = ip4.hostip[i - 26];
	for (int i = 30; i < 34; i++) datapack[i] = ip4.dstip[i - 30];
	//for (i = 26; i < ip4.optlen + 26; i++) datapack[i] = ip4.opt[i - 26];
	//ip check
	unsigned int check = 0;
	for (int i = 14; i < 34 ; i += 2) check += datapack[i] * 256 + datapack[i + 1];
	while (check > 0xffff) check = (check & 0xffff) + (check >> 16);
	check = ~check;
	datapack[24] = check >> 8;
	datapack[25] = check;
	check = 0;
	//data
	for (int i = 34; i < len; i++) datapack[i] = userpack[i - 34];
	return 0;
}

//make a arp/rarp packet, fixed len, make error: return 1, return 0;
int packet_send::makearp() {
	len = 42;
	datapack = (unsigned char*)malloc(len);
	if (!datapack) return 1;
	//mac header
	for (int i = 0; i < 6; i++) datapack[i] = mac.dstmac[i];
	for (int i = 6; i < 12; i++) datapack[i] = mac.hostmac[i - 6];
	datapack[12] = 8;
	datapack[13] = 6;
	//arp/rarp header
	datapack[14] = 0;
	datapack[15] = 1;
	datapack[16] = 8;
	datapack[17] = 0;
	datapack[18] = 6;
	datapack[19] = 4;
	datapack[20] = 0;
	datapack[21] = arp.op;
	//data
	for (int i = 22; i < 28; i++) datapack[i] = arp.hostmac[i - 22];
	for (int i = 28; i < 32; i++) datapack[i] = arp.hostip[i - 28];
	for (int i = 32; i < 38; i++) datapack[i] = arp.dstmac[i - 32];
	for (int i = 38; i < 42; i++) datapack[i] = arp.dstip[i - 38];
	return 0;
}

//make a icmp packet, wrong len: return -1, make error: return 1, else: return 0
int packet_send::makeicp() {
	if (len < 43) return -1;
	datapack = (unsigned char*)malloc(len);
	if (!datapack) return 1;
	//mac header
	for (int i = 0; i < 6; i++) datapack[i] = mac.dstmac[i];
	for (int i = 6; i < 12; i++) datapack[i] = mac.hostmac[i - 6];
	datapack[12] = 8;
	datapack[13] = 0;
	//ipv4 header
	datapack[14] = 0x45;
	datapack[15] = (ip4.dscp << 2) + ip4.ecn;
	datapack[16] = (len - 14) >> 8;
	datapack[17] = (len - 14);
	datapack[18] = ip4.id >> 8;
	datapack[19] = ip4.id;
	datapack[20] = (ip4.depart << 5) + (ip4.offset >> 8);
	datapack[21] = ip4.offset;
	datapack[22] = ip4.ttl;
	datapack[23] = 1;
	datapack[24] = 0;
	datapack[25] = 0;
	for (int i = 26; i < 30; i++) datapack[i] = ip4.hostip[i - 26];
	for (int i = 30; i < 34; i++) datapack[i] = ip4.dstip[i - 30];
	unsigned int check = 0;
	for (int i = 14; i < 34; i += 2) check += datapack[i] * 256 + datapack[i + 1];
	while (check > 0xffff) check = (check & 0xffff) + (check >> 16);
	check = ~check;
	datapack[24] = check >> 8;
	datapack[25] = check;
	check = 0;
	//icmp header
	datapack[34] = icp.type;
	datapack[35] = icp.code;
	datapack[36] = 0;
	datapack[37] = 0;
	datapack[38] = icp.id >> 8;
	datapack[39] = icp.id;
	datapack[40] = icp.seq >> 8;
	datapack[41] = icp.seq;
	//data
	for (int i = 42; i < len; i++) datapack[i] = userpack[i - 42];
	//icmp check
	for (int i = 34; i < len - 1; i += 2) check += datapack[i] * 256 + datapack[i + 1];
	if (len % 2) check += datapack[len - 1] * 256;
	while (check > 0xffff) check = (check & 0xffff) + (check >> 16);
	check = ~check;
	datapack[36] = check >> 8;
	datapack[37] = check;
	check = 0;
	return 0;
}

//make a udp packet, wrong len: return -1, make error: return 1, else: return 0
int packet_send::makeudp() {
	if (len < 43) return -1;
	datapack = (unsigned char*)malloc(len);
	if (!datapack) return 1;
	//mac header
	for (int i = 0; i < 6; i++) datapack[i] = mac.dstmac[i];
	for (int i = 6; i < 12; i++) datapack[i] = mac.hostmac[i - 6];
	datapack[12] = 8;
	datapack[13] = 0;
	//ipv4 header
	datapack[14] = 0x45;
	datapack[15] = (ip4.dscp << 2) + ip4.ecn;
	datapack[16] = (len - 14) >> 8;
	datapack[17] = (len - 14);
	datapack[18] = ip4.id >> 8;
	datapack[19] = ip4.id;
	datapack[20] = (ip4.depart << 5) + (ip4.offset >> 8);
	datapack[21] = ip4.offset;
	datapack[22] = ip4.ttl;
	datapack[23] = 17;
	datapack[24] = 0;
	datapack[25] = 0;
	for (int i = 26; i < 30; i++) datapack[i] = ip4.hostip[i - 26];
	for (int i = 30; i < 34; i++) datapack[i] = ip4.dstip[i - 30];
	//ip check
	unsigned int check = 0;
	for (int i = 14; i < 34; i += 2) check += datapack[i] * 256 + datapack[i + 1];
	while (check > 0xffff) check = (check & 0xffff) + (check >> 16);
	check = ~check;
	datapack[24] = check >> 8;
	datapack[25] = check;
	check = 0;
	//udp header
	datapack[34] = udp.hostport >> 8;
	datapack[35] = udp.hostport;
	datapack[36] = udp.dstport >> 8;
	datapack[37] = udp.dstport;
	datapack[38] = (len - 34) >> 8;
	datapack[39] = (len - 34);
	datapack[40] = 0;
	datapack[41] = 0;
	//data
	for (int i = 42; i < len; i++) datapack[i] = userpack[i - 42];
	//udp check
	for (int i = 26; i < len - 1; i += 2) check += datapack[i] * 256 + datapack[i + 1];
	if (len % 2) check += datapack[len - 1] * 256;
	check += len - 17;
	while (check > 0xffff) check = (check & 0xffff) + (check >> 16);
	check = ~check;
	datapack[40] = check >> 8;
	datapack[41] = check;
	return 0;
}

//make a tcp packet, wrong len: return -1, make error: return 1, wrong offset: return 2, else return 0
int packet_send::maketcp() {
	unsigned int minlen = 34 + tcp.offset * 4;
	if (len < minlen) return -1;
	if (tcp.offset < 5) return 2;
	datapack = (unsigned char*)malloc(len);
	if (!datapack) return 1;
	//mac header
	for (int i = 0; i < 6; i++) datapack[i] = mac.dstmac[i];
	for (int i = 6; i < 12; i++) datapack[i] = mac.hostmac[i - 6];
	datapack[12] = 8;
	datapack[13] = 0;
	//ipv4 header
	datapack[14] = 0x45;
	datapack[15] = (ip4.dscp << 2) + ip4.ecn;
	datapack[16] = (len - 14) >> 8;
	datapack[17] = (len - 14);
	datapack[18] = ip4.id >> 8;
	datapack[19] = ip4.id;
	datapack[20] = (ip4.depart << 5) + (ip4.offset >> 8);
	datapack[21] = ip4.offset;
	datapack[22] = ip4.ttl;
	datapack[23] = 6;
	datapack[24] = 0;
	datapack[25] = 0;
	for (int i = 26; i < 30; i++) datapack[i] = ip4.hostip[i - 26];
	for (int i = 30; i < 34; i++) datapack[i] = ip4.dstip[i - 30];
	//ip check
	unsigned int check = 0;
	for (int i = 14; i < 34; i += 2) check += datapack[i] * 256 + datapack[i + 1];
	while (check > 0xffff) check = (check & 0xffff) + (check >> 16);
	check = ~check;
	datapack[24] = check >> 8;
	datapack[25] = check;
	check = 0;
	//udp header
	datapack[34] = tcp.hostport >> 8;
	datapack[35] = tcp.hostport;
	datapack[36] = tcp.dstport >> 8;
	datapack[37] = tcp.dstport;
	datapack[38] = tcp.seq >> 24;
	datapack[39] = tcp.seq >> 16;
	datapack[40] = tcp.seq >> 8;
	datapack[41] = tcp.seq;
	datapack[42] = tcp.conf >> 24;
	datapack[43] = tcp.conf >> 16;
	datapack[44] = tcp.conf >> 8;
	datapack[45] = tcp.conf;
	datapack[46] = (tcp.offset << 4) + tcp.aec;
	datapack[47] = (tcp.cwr << 7) + (tcp.ece << 6) + (tcp.urg << 5) + (tcp.ack << 4)
		+ (tcp.psh << 3) + (tcp.rst << 2) + (tcp.syn << 1) + tcp.fin;
	datapack[48] = tcp.win >> 8;
	datapack[49] = tcp.win;
	datapack[50] = 0;
	datapack[51] = 0;
	if (tcp.urg) {
		datapack[52] = tcp.up >> 8;
		datapack[53] = tcp.up;
	}
	else {
		datapack[52] = 0;
		datapack[53] = 0;
	}
	if (tcp.offset > 5) for (int i = 54; i < minlen; i++) datapack[i] = tcp.op[i - 54];
	//data
	for (int i = minlen; i < len; i++) datapack[i] = userpack[i - minlen];
	//tcp check
	for (int i = 26; i < len - 1; i += 2) check += datapack[i] * 256 + datapack[i + 1];
	if (len % 2) check += datapack[len - 1] * 256;
	check += len - 28;
	while (check > 0xffff) check = (check & 0xffff) + (check >> 16);
	check = ~check;
	datapack[50] = check >> 8;
	datapack[51] = check;
	return 0;
}