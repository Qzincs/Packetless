#include<iostream>
#include <memory>
using namespace std;
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<vector>
#include"analyzer.h"
template<typename ... Args>
static std::string str_format(const std::string& format, Args ... args)//格式化输出字符串的函数(网上找的)
{
	auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
	std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

	if (!buf)
		return std::string("");

	std::snprintf(buf.get(), size_buf, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size_buf - 1);
}
//计算校验和的函数
u_short checksum(u_short* addr, int count){
	long sum = 0;
	/*
	计算所有数据的16bit对之和
	*/
	while (count > 1) {
		/*  This is the inner loop */
		sum += *(addr++);
		count -= 2;
	}
	/* 如果数据长度为奇数，在该字节之后补一个字节(0),
	   然后将其转换为16bit整数，加到上面计算的校验和
	　　中。
	 */
	if (count > 0) {
		char left_over[2] = { 0 };
		left_over[0] = *addr;
		sum += *(unsigned short*)left_over;
	}
	/*  将32bit数据压缩成16bit数据，即将进位加大校验和
	　　的低字节上，直到没有进位为止。
	 */
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	/*返回校验和的反码*/
	return ~sum;
}
//初始化函数
void Analyzer::Analyze(int caplen, u_char* pkt) {
	this->caplen = caplen;
	pPkt = pkt;
	info.assign(6, "none");
	info[4] = caplen;
	tree_header.assign(5, "none");
	tree.resize(5);
	mac.assign(4, "none");
	arp.assign(10, "none");
	rarp.assign(10, "none");
	ip.assign(14, "none");
	ipv6.assign(9, "none");
	tcp.assign(12, "none");
	udp.assign(6, "none");
	icmp.assign(5, "none");
	igmp.assign(11, " ");
	http.assign(2, " ");
}
//解析mac头部
void Analyzer::ParseMACPacket() {
	MAC_HEADER* pMacHdr = (MAC_HEADER*)pPkt;
	//mac头部节点
	mac[0] = "Ethernet II, "+ str_format("Src:%02X:%02X:%02X:%02X:%02X:%02X",
		(char*)pMacHdr->SrcMacAddr[0], (char*)pMacHdr->SrcMacAddr[1],
		(char*)pMacHdr->SrcMacAddr[2], (char*)pMacHdr->SrcMacAddr[3],
		(char*)pMacHdr->SrcMacAddr[4], (char*)pMacHdr->SrcMacAddr[5])+ ","+
		str_format("Dst:%02X:%02X:%02X:%02X:%02X:%02X",
			pMacHdr->DesMacAddr[0], pMacHdr->DesMacAddr[1],
			pMacHdr->DesMacAddr[2], pMacHdr->DesMacAddr[3],
			pMacHdr->DesMacAddr[4], pMacHdr->DesMacAddr[5]);
	tree_header[1] = mac[0];
	//MAC源地址
	mac[2] = str_format("Source:%02X:%02X:%02X:%02X:%02X:%02X",
		(char*)pMacHdr->SrcMacAddr[0], (char*)pMacHdr->SrcMacAddr[1],
		(char*)pMacHdr->SrcMacAddr[2], (char*)pMacHdr->SrcMacAddr[3],
		(char*)pMacHdr->SrcMacAddr[4], (char*)pMacHdr->SrcMacAddr[5]);
	//Mac目的地址
	mac[1] = str_format("Destination:%02X:%02X:%02X:%02X:%02X:%02X",
		pMacHdr->DesMacAddr[0], pMacHdr->DesMacAddr[1],
		pMacHdr->DesMacAddr[2], pMacHdr->DesMacAddr[3],
		pMacHdr->DesMacAddr[4], pMacHdr->DesMacAddr[5]);
	//根据协议类型调用相应解析函数
	if (ntohs(pMacHdr->LengthOrType) == MAC_TYPE_IP) {//IP协议
		mac[3] = "Type:IPv4 (0x0800)";
		ParseIPPacket();
	}
	else if (ntohs(pMacHdr->LengthOrType) == MAC_TYPE_ARP) {//ARP协议
		mac[3] = "Type:ARP (0x0806)";
		ParseARPPacket();
	}
	else if (ntohs(pMacHdr->LengthOrType) == MAC_TYPE_RARP) {//帧数据中报文类型未知
		mac[3] = "Type:RARP (0x0835)";
		ParseRARPPacket();
	}
	else if (ntohs(pMacHdr->LengthOrType) == MAC_TYPE_IPv6) {
		mac[3] = "Type:IPv6 (0x86dd)";
		ParseIPv6Packet();
	}
	else {
		//ieee802.3没做解析
	}
	tree[1] = mac;
}
//解析arp头部
void Analyzer::ParseARPPacket() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER);//先位移至arp头部所在地址
	ARP_HEADER* pARPHdr = (ARP_HEADER*)pkt;
	info[3] = "ARP";
	if (ntohs(pARPHdr->hardware_type) == 0x0001) {
		arp[1] = "Hardware type: Ethernet (1)";//硬件类型
	}
	else {
		arp[1] = "Hardware type: others";
	}
	if (ntohs(pARPHdr->proto_type) == 0x0800) {
		arp[2] = str_format("Protocol type: IPv4 (%04x)", ntohs(pARPHdr->proto_type));//协议类型
	}
	else {
		arp[2] = "Protocol type: others";
	}
	arp[3] = str_format("Hardware size: %02x", pARPHdr->hardware_addr_len);
	arp[4] = str_format("Protocol size: %02x", pARPHdr->proto_addr_len);

	//操作类型(表述形式仿照wireshark)
	if (ntohs(pARPHdr->operation_code) == ARP_OP_REQUEST) {
		arp[0] = "Address Resolution Protocol (request)";
		tree_header[2] = arp[0];
		arp[5] = "Opcode: request (1)";
		info[2] = "Broadcast";
		info[5]="Who has "+ str_format("%u.%u.%u.%u", pARPHdr->dest_ip_addr[0], pARPHdr->dest_ip_addr[1],
			pARPHdr->dest_ip_addr[2], pARPHdr->dest_ip_addr[3])+"? Tell "+ str_format("%u.%u.%u.%u", pARPHdr->src_ip_addr[0], pARPHdr->src_ip_addr[1],
				pARPHdr->src_ip_addr[2], pARPHdr->src_ip_addr[3]);
	}
	else if (ntohs(pARPHdr->operation_code) == ARP_OP_REPLY) {
		arp[0] = "Address Resolution Protocol (reply)";
		arp[5] = "Opcode: reply (2)";
		info[2]= str_format("%02X:%02X:%02X:%02X:%02X:%02X",
			pARPHdr->dest_mac_addr[0], pARPHdr->dest_mac_addr[1],
			pARPHdr->dest_mac_addr[2], pARPHdr->dest_mac_addr[3],
			pARPHdr->dest_mac_addr[4], pARPHdr->dest_mac_addr[5]);
		info[5]=str_format("%u.%u.%u.%u", pARPHdr->src_ip_addr[0], pARPHdr->src_ip_addr[1],
			pARPHdr->src_ip_addr[2], pARPHdr->src_ip_addr[3])+" is at "+ str_format("%02X:%02X:%02X:%02X:%02X:%02X",
				pARPHdr->src_mac_addr[0], pARPHdr->src_mac_addr[1],
				pARPHdr->src_mac_addr[2], pARPHdr->src_mac_addr[3],
				pARPHdr->src_mac_addr[4], pARPHdr->src_mac_addr[5]);
	}
	//ARP头部子节点:源Mac地址
	arp[6] = str_format("Sender MAC address: %02X:%02X:%02X:%02X:%02X:%02X",
		pARPHdr->src_mac_addr[0], pARPHdr->src_mac_addr[1],
		pARPHdr->src_mac_addr[2], pARPHdr->src_mac_addr[3],
		pARPHdr->src_mac_addr[4], pARPHdr->src_mac_addr[5]);
	info[1] = str_format("%02X:%02X:%02X:%02X:%02X:%02X",
		pARPHdr->src_mac_addr[0], pARPHdr->src_mac_addr[1],
		pARPHdr->src_mac_addr[2], pARPHdr->src_mac_addr[3],
		pARPHdr->src_mac_addr[4], pARPHdr->src_mac_addr[5]);
	arp[7] = str_format("Sender IP address: %u.%u.%u.%u", pARPHdr->src_ip_addr[0], pARPHdr->src_ip_addr[1],
		pARPHdr->src_ip_addr[2], pARPHdr->src_ip_addr[3]);
	arp[8] = str_format("Target MAC address: %02X:%02X:%02X:%02X:%02X:%02X",
		pARPHdr->dest_mac_addr[0], pARPHdr->dest_mac_addr[1],
		pARPHdr->dest_mac_addr[2], pARPHdr->dest_mac_addr[3],
		pARPHdr->dest_mac_addr[4], pARPHdr->dest_mac_addr[5]);
	arp[9] = str_format("Target IP address: %u.%u.%u.%u", pARPHdr->dest_ip_addr[0], pARPHdr->dest_ip_addr[1],
		pARPHdr->dest_ip_addr[2], pARPHdr->dest_ip_addr[3]);
	tree[2] = arp;
	tree.pop_back();//没有第三层第四层,故删去
	tree_header.pop_back();
	tree.pop_back();
	tree_header.pop_back();
}
//解析tcp
void Analyzer::ParseTCPPacket() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER)+flag;
	TCP_HEADER* pTCPHdr = (TCP_HEADER*)pkt;
	info[3] = "TCP";
	int a = ip_num -  sizeof(IP_HEADER);//横向信息里的Len，看wireshark感觉是a
	if ((pTCPHdr->Flags&0x01)==0x01) {//FIN=1
		info[5] = str_format("%u -> %u [FIN, ACK] Seq=%u Ack=%u Win=%u Len=%u", ntohs(pTCPHdr->SrcPort), 
			ntohs(pTCPHdr->DstPort),ntohl(pTCPHdr->Seq),ntohl(pTCPHdr->Ack),ntohs(pTCPHdr->Window), a);
		tcp[7] = str_format("Flags: 0x%3x (FIN, ACK)", pTCPHdr->Flags);
	}
	else {//FIN=0
		if ((pTCPHdr->Flags&0x2)==0x2) {//SYN=1
			if ((pTCPHdr->Flags & 0x10) == 0x10) {//ACK=1
				info[5] = str_format("%u -> %u [SYN, ACK] Seq=%u Ack=%u Win=%u Len=%u", ntohs(pTCPHdr->SrcPort),
					ntohs(pTCPHdr->DstPort), ntohl(pTCPHdr->Seq), ntohl(pTCPHdr->Ack), ntohs(pTCPHdr->Window), a);
				tcp[7] = str_format("Flags: 0x%3x (SYN, ACK)", pTCPHdr->Flags);
			}
			else {//ACK=0
				info[5] = str_format("%u -> %u [SYN] Seq=%u Win=%u Len=%u", ntohs(pTCPHdr->SrcPort),
					ntohs(pTCPHdr->DstPort), ntohl(pTCPHdr->Seq), ntohs(pTCPHdr->Window), a);
				tcp[7] = str_format("Flags: 0x%3x (SYN)", pTCPHdr->Flags);
			}
		}
		else {//SYN=0
			info[5] = str_format("%u -> %u [ACK] Seq=%u Ack=%u Win=%u Len=%u", ntohs(pTCPHdr->SrcPort),
				ntohs(pTCPHdr->DstPort), ntohl(pTCPHdr->Seq), ntohl(pTCPHdr->Ack), ntohs(pTCPHdr->Window), a);
			tcp[7] = str_format("Flags: 0x%3x (ACK)", pTCPHdr->Flags);
		}
	}
	tcp[0] = "Transmission Control Protocol, " + 
		str_format("Src Port: %u, Dst Port: %u", ntohs(pTCPHdr->SrcPort), ntohs(pTCPHdr->DstPort)) +
		str_format(", Seq: %u, Ack: %u, Len: %u", ntohl(pTCPHdr->Seq), ntohl(pTCPHdr->Ack), a);
	tree_header[3] = tcp[0];
	tcp[1] = str_format("Src Port: %u", ntohs(pTCPHdr->SrcPort));
	tcp[2] = str_format("Dst Port: %u", ntohs(pTCPHdr->DstPort));
	tcp[3] = str_format("Sequence Number: %u", ntohl(pTCPHdr->Seq));
	tcp[4]= str_format("[Next Sequence Number: %u]", ntohl(pTCPHdr->Seq)+1);
	tcp[5]= str_format("Acknowledge Number: %u", ntohl(pTCPHdr->Ack));
	tcp[6] = str_format("Header Length: %u bytes", 4*(pTCPHdr->HeaderLen>>4));
	tcp[8]= str_format("Window: %u", ntohs(pTCPHdr->Window));
	tcp[9]= str_format("Checksum: 0x%4x", ntohs(pTCPHdr->Checksum));
	memcpy(ck, &psd_header, sizeof(PSD_HEADER));//将伪首部放入送检字符数组
	memcpy(ck + sizeof(PSD_HEADER), pkt, ntohs(psd_header.length));//再将tcp报文放入送检字符数组
	u_short temp = checksum((u_short*)ck, sizeof(PSD_HEADER) + ntohs(psd_header.length));//计算校验和,校验和部分不置0,直接一块算,最后结果是0x0或者0xffff即可
	if (temp == 0x0) {
		tcp[10] = "[Checksum status: Good]";
	}
	else if (temp == 0xffff) {
		tcp[10] = "[Checksum status: Good]";
	}
	else {
		tcp[10] = "[Checksum status: Bad]";
	}
	tcp[11]= str_format("Urgent Pointer: %u", (pTCPHdr->Flags & 0x200) == 0x200?ntohs(pTCPHdr->UrgentPointer):0);
	tree[3] = tcp;
	//接下来解析http,由于http报文没有固定到字节数的结构,而且全是ascii码,直接输出就行,不另外创建函数
	if (14+flag+ 4 * (pTCPHdr->HeaderLen >> 4)<caplen) {//tcp报文后面还有东西吗
		u_char* phttp = pkt + 4 * (pTCPHdr->HeaderLen >> 4);//位移找到可能的http地址
//通过首字母和第二字母判断是不是http.看过wireshark,大部分http端口号都不是80,不如直接用字母来判断
		if (*phttp == 'G'|| *phttp == 'P'|| *phttp == 'H'|| *phttp == 'D') {
			if (*(phttp+1) == 'E' || *(phttp+1) == 'O' || *(phttp+1) == 'T' || *(phttp+1) == 'U') {
				tree_header[4] = "Hypertext Transfer Protocol";
				http[0] = tree_header[4];
				info[3] = "HTTP";
				int temp_index = 1;//http树状数组的下标,在检测到0x0d0a结构就加一
				for (int i = 0; i + 14 + flag + 4 * (pTCPHdr->HeaderLen >> 4) < caplen; i++) {
					if (*(phttp + i) == 0x0d) {
						http[temp_index] += "\\r\\n";
						http.push_back("");
						temp_index++;
					}
					else if (*(phttp + i) == 0x0a) {
						if (http[temp_index-1]=="\\r\\n") {
							break;
						}
					}
					else {
						http[temp_index] += *(phttp + i);
					}

				}
				info[4] = http[1];
				tree[4] = http;
			}
			else {
				tree.pop_back();
				tree_header.pop_back();
			}		
		}
		else {
			tree.pop_back();
			tree_header.pop_back();
		}
	}
	else {
		tree.pop_back();
		tree_header.pop_back();
	}
}
//解析IP
void Analyzer::ParseIPPacket() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER);
	IP_HEADER* pIPHdr = (IP_HEADER*)pkt;
	flag = 4 * (pIPHdr->Ver_HeaderLen & 0x0f);//通过这个可以在下一层函数知道上一层是ip还是ipv6
	ip[0] = "Internet Protocol Version 4, " + str_format("Src: %u.%u.%u.%u", pIPHdr->src_ip_addr[0], pIPHdr->src_ip_addr[1],
		pIPHdr->src_ip_addr[2], pIPHdr->src_ip_addr[3])+ str_format(", Dst: %u.%u.%u.%u", pIPHdr->dest_ip_addr[0], pIPHdr->dest_ip_addr[1],
			pIPHdr->dest_ip_addr[2], pIPHdr->dest_ip_addr[3]);
	tree_header[2] = ip[0];
	ip[1] = "Version: 4";
	ip[2] = str_format("Header Length: %u bytes (%u)",flag, (pIPHdr->Ver_HeaderLen & 0x0f));
	ip[3] = str_format("Differentiated Services Field: 0x%2x", pIPHdr->TOS);
	ip[4]= str_format("Total Length: %u", ntohs(pIPHdr->TotalLen));
	ip_num = ntohs(pIPHdr->TotalLen);
	ip[5]=str_format("Identification: 0x%4x (%u)", pIPHdr->ID, pIPHdr->ID);
	int b = ntohs(pIPHdr->Flag_Segment) >> 13;
	if (b == 2) {
		ip[6] = "Flags: 0x2, Don't fragment";
	}
	else if (b == 1) {
		ip[6] = "Flags: 0x1, more fragment";
	}
	else {
		ip[6] = "Flags: 0x0, no more fragment";
	}
	int c = ntohs(pIPHdr->Flag_Segment) & 0x1fff;
	ip[7] = str_format("Fragment offset: %u", c);
	ip[8] = str_format("Time to Live: %u", pIPHdr->TTL);
	u_short temp = checksum((u_short*)pkt,flag);//ip校验和不需要伪首部
	if (temp == 0x0) {
		ip[10] = str_format("Checksum : 0x%4x [correct]", ntohs(pIPHdr->Checksum));
		ip[11] = "[Checksum status: Good]";
	}
	else if (temp == 0xffff) {
		ip[10] = str_format("Checksum : 0x%4x [correct]", ntohs(pIPHdr->Checksum));
		ip[11] = "[Checksum status: Good]";
	}
	else {
		ip[10] = str_format("Checksum : 0x%4x [incorrect]",ntohs(pIPHdr->Checksum));
		ip[11] = "[Checksum status: Bad]";
	}
	ip[12] = str_format("Source Address: %u.%u.%u.%u", pIPHdr->src_ip_addr[0], pIPHdr->src_ip_addr[1],
		pIPHdr->src_ip_addr[2], pIPHdr->src_ip_addr[3]);
	info[1] = str_format("%u.%u.%u.%u", pIPHdr->src_ip_addr[0], pIPHdr->src_ip_addr[1],
		pIPHdr->src_ip_addr[2], pIPHdr->src_ip_addr[3]);
	ip[13] = str_format("Destination Address: %u.%u.%u.%u", pIPHdr->dest_ip_addr[0], pIPHdr->dest_ip_addr[1],
		pIPHdr->dest_ip_addr[2], pIPHdr->dest_ip_addr[3]);
	info[2]= str_format("%u.%u.%u.%u", pIPHdr->dest_ip_addr[0], pIPHdr->dest_ip_addr[1],
		pIPHdr->dest_ip_addr[2], pIPHdr->dest_ip_addr[3]);
	//搭建ip伪首部
	memcpy(psd_header.src_ip_addr, pIPHdr->src_ip_addr, 4);
	memcpy(psd_header.dest_ip_addr, pIPHdr->dest_ip_addr, 4);
	short tcp_length = htons(ntohs(pIPHdr->TotalLen)-flag);
	psd_header.length = tcp_length;
	psd_header.protocol= pIPHdr->Protocol;
	psd_header.bank = 0x00;
	//通过ip协议类型调用下一层协议解析函数
	if (pIPHdr->Protocol == IP_TYPE_IPv6) {
		/////
	}
	else if (pIPHdr->Protocol == IP_TYPE_ICMP) {
		ip[9] = "Protocol: ICMP (1)";
		ParseICMPPacket();
	}
	else if (pIPHdr->Protocol == IP_TYPE_IGMP) {
		ip[9] = "Protocol: IGMP (2)";
		ParseIGMPPacket();
	}
	else if (pIPHdr->Protocol == IP_TYPE_TCP) {
		ip[9] = "Protocol: TCP (6)";
		ParseTCPPacket();
	}
	else {
		ip[9] = "Protocol: UDP (17)";
		ParseUDPPacket();
	}
	tree[2] = ip;
}
//IPv6
void Analyzer::ParseIPv6Packet() {
	flag = sizeof(IPv6_HEADER);
	u_char* pkt = pPkt + sizeof(MAC_HEADER);
	IPv6_HEADER* pIPHdr = (IPv6_HEADER*)pkt;
	ipv6[0] = "Internet Protocol Version 6, " + str_format("Src: %4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x", ntohs(pIPHdr->src_ip_addr[0]), ntohs(pIPHdr->src_ip_addr[1]),
		ntohs(pIPHdr->src_ip_addr[2]), ntohs(pIPHdr->src_ip_addr[3]), ntohs(pIPHdr->src_ip_addr[4]), ntohs(pIPHdr->src_ip_addr[5]), ntohs(pIPHdr->src_ip_addr[6]), ntohs(pIPHdr->src_ip_addr[7])) +
		str_format(", Dst: %4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x", ntohs(pIPHdr->dest_ip_addr[0]), ntohs(pIPHdr->dest_ip_addr[1]),
			ntohs(pIPHdr->dest_ip_addr[2]), ntohs(pIPHdr->dest_ip_addr[3]), ntohs(pIPHdr->dest_ip_addr[4]), ntohs(pIPHdr->dest_ip_addr[5]), ntohs(pIPHdr->dest_ip_addr[6]), ntohs(pIPHdr->dest_ip_addr[7]));
	tree_header[2] = ipv6[0];
	ipv6[1] = "Version: 6";
	ipv6[2] = str_format("Traffic Class: 0x%2x", pIPHdr->Traffic_class_1<<4+pIPHdr->Traffic_class_2);
	ipv6[3] = str_format("Flow Label: 0x%5x", ntohs(pIPHdr->Flow_label_1<<16+pIPHdr->Flow_label_2));
	ipv6[4] = str_format("Payload Length: %u", ntohs(pIPHdr->TotalLen));
	ip_num = ntohs(pIPHdr->TotalLen);
	ipv6[6] = str_format("Hop Limit: %u", pIPHdr->Hop_limit);
	ipv6[7] = str_format("Source Address: %4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x", ntohs(pIPHdr->src_ip_addr[0]), ntohs(pIPHdr->src_ip_addr[1]),
		ntohs(pIPHdr->src_ip_addr[2]), ntohs(pIPHdr->src_ip_addr[3]), ntohs(pIPHdr->src_ip_addr[4]), ntohs(pIPHdr->src_ip_addr[5]), ntohs(pIPHdr->src_ip_addr[6]), ntohs(pIPHdr->src_ip_addr[7]));
	info[1] = str_format("%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x", ntohs(pIPHdr->src_ip_addr[0]), ntohs(pIPHdr->src_ip_addr[1]),
		ntohs(pIPHdr->src_ip_addr[2]), ntohs(pIPHdr->src_ip_addr[3]), ntohs(pIPHdr->src_ip_addr[4]), ntohs(pIPHdr->src_ip_addr[5]), ntohs(pIPHdr->src_ip_addr[6]), ntohs(pIPHdr->src_ip_addr[7]));
	ipv6[8] = str_format("Destination Address: %4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x", ntohs(pIPHdr->dest_ip_addr[0]), ntohs(pIPHdr->dest_ip_addr[1]),
		ntohs(pIPHdr->dest_ip_addr[2]), ntohs(pIPHdr->dest_ip_addr[3]), ntohs(pIPHdr->dest_ip_addr[4]), ntohs(pIPHdr->dest_ip_addr[5]), ntohs(pIPHdr->dest_ip_addr[6]), ntohs(pIPHdr->dest_ip_addr[7]));
	info[2] = str_format("%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x", ntohs(pIPHdr->dest_ip_addr[0]), ntohs(pIPHdr->dest_ip_addr[1]),
		ntohs(pIPHdr->dest_ip_addr[2]), ntohs(pIPHdr->dest_ip_addr[3]), ntohs(pIPHdr->dest_ip_addr[4]), ntohs(pIPHdr->dest_ip_addr[5]), ntohs(pIPHdr->dest_ip_addr[6]), ntohs(pIPHdr->dest_ip_addr[7]));
	//搭建ipv6伪首部
	memcpy(psd_headerv6.src_ip_addr, pIPHdr->src_ip_addr, 16);
	memcpy(psd_headerv6.dest_ip_addr, pIPHdr->dest_ip_addr, 16);
	psd_headerv6.length = pIPHdr->TotalLen;
	psd_headerv6.nexthead = pIPHdr->Next_header;
	psd_headerv6.bank_1 = 0x00;
	for (int i = 0; i < 3; i++) {
		psd_headerv6.bank_2[i] = 0x00;
	}
	if (pIPHdr->Next_header == IP_TYPE_IPv6) {
		/////
	}
	else if (pIPHdr->Next_header == IP_TYPE_ICMP) {
		ipv6[5] = "Next Header: ICMP (1)";
		ParseICMPPacket();
	}
	else if (pIPHdr->Next_header== IP_TYPE_IGMP) {
		ipv6[5] = "Next Header: IGMP (2)";
		ParseIGMPPacket();
	}
	else if (pIPHdr->Next_header == IP_TYPE_TCP) {
		ipv6[5] = "Next Header: TCP (6)";
		ParseTCPPacket();
	}
	else if (pIPHdr->Next_header == IP_TYPE_ICMPv6) {
		ipv6[5] = "Next Header: ICMPv6 (58)";
		ParseICMPv6Packet();
	}
	else {
		ipv6[5] = "Next Header: UDP (17)";
		ParseUDPPacket();
	}
	tree[2] = ipv6;
}
//udp,跟tcp差不多
void Analyzer::ParseUDPPacket() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER) + flag;
	UDP_HEADER* pUDPHdr = (UDP_HEADER*)pkt;
	info[3] = "UDP";
	int a = ip_num -sizeof(IP_HEADER);
	info[5] = str_format("%u -> %u Len=%u", ntohs(pUDPHdr->SrcPort),
			ntohs(pUDPHdr->DstPort), a);	
	udp[0] = "User Datagram Protocol, " +
		str_format("Src Port: %u, Dst Port: %u", ntohs(pUDPHdr->SrcPort), ntohs(pUDPHdr->DstPort));
	tree_header[3] = udp[0];
	udp[1] = str_format("Src Port: %u", ntohs(pUDPHdr->SrcPort));
	udp[2] = str_format("Dst Port: %u", ntohs(pUDPHdr->DstPort));
	udp[3]= str_format("Length: %u", ntohs(pUDPHdr->Length));
	udp[4] = str_format("Checksum: 0x%4x", ntohs(pUDPHdr->Checksum));
	memcpy(ck, &psd_header, sizeof(PSD_HEADER));
	memcpy(ck + sizeof(PSD_HEADER), pkt, ntohs(psd_header.length));
	u_short temp = checksum((u_short*)ck, sizeof(PSD_HEADER) + ntohs(psd_header.length));
	if (temp == 0x0) {
		udp[5] = "[Checksum status: Good]";
	}
	else if (temp == 0xffff) {
		udp[5] = "[Checksum status: Good]";
	}
	else {
		udp[5] = "[Checksum status: Bad]";
	}
	tree[3] = udp;
	tree.pop_back();
	tree_header.pop_back();
}
//RARP,与ARP相似
void Analyzer::ParseRARPPacket() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER);
	RARP_HEADER* pRARPHdr = (RARP_HEADER*)pkt;
	info[3] = "RARP";
	if (ntohs(pRARPHdr->hardware_type) == 0x0001) {
		rarp[1] = "Hardware type: Ethernet (1)";//硬件类型
	}
	else {
		rarp[1] = "Hardware type: others";
	}
	if (ntohs(pRARPHdr->proto_type) == 0x0800) {
		rarp[2] = str_format("Protocol type: IPv4 (%04x)", ntohs(pRARPHdr->hardware_type));//硬件类型
	}
	else {
		rarp[2] = "Protocol type: others";
	}
	rarp[3] = str_format("Hardware size: %02x", pRARPHdr->hardware_addr_len);
	rarp[4] = str_format("Protocol size: %02x", pRARPHdr->proto_addr_len);

	//操作类型
	if (ntohs(pRARPHdr->operation_code) == RARP_OP_REQUEST) {
		rarp[0] = "Address Resolution Protocol (reverse request)";
		tree_header[2] = rarp[0];
		rarp[5] = "Opcode: reverse request (3)";
		info[5] = "Who is " + str_format("%02X:%02X:%02X:%02X:%02X:%02X",
			pRARPHdr->dest_mac_addr[0], pRARPHdr->dest_mac_addr[1],
			pRARPHdr->dest_mac_addr[2], pRARPHdr->dest_mac_addr[3],
			pRARPHdr->dest_mac_addr[4], pRARPHdr->dest_mac_addr[5]) + "? Tell " + str_format("%02X:%02X:%02X:%02X:%02X:%02X",
				pRARPHdr->src_mac_addr[0], pRARPHdr->src_mac_addr[1],
				pRARPHdr->src_mac_addr[2], pRARPHdr->src_mac_addr[3],
				pRARPHdr->src_mac_addr[4], pRARPHdr->src_mac_addr[5]);
	}
	else if (ntohs(pRARPHdr->operation_code) == RARP_OP_REPLY) {
		rarp[0] = "Address Resolution Protocol (reverse reply)";
		rarp[5] = "Opcode: reverse reply (4)";
		info[5] = str_format("%02X:%02X:%02X:%02X:%02X:%02X",
			pRARPHdr->src_mac_addr[0], pRARPHdr->src_mac_addr[1],
			pRARPHdr->src_mac_addr[2], pRARPHdr->src_mac_addr[3],
			pRARPHdr->src_mac_addr[4], pRARPHdr->src_mac_addr[5]) + " is at " + str_format("%u.%u.%u.%u", pRARPHdr->src_ip_addr[0], pRARPHdr->src_ip_addr[1],
				pRARPHdr->src_ip_addr[2], pRARPHdr->src_ip_addr[3]);
	}
	//ARP头部子节点:源Mac地址
	rarp[6] = str_format("Sender MAC address: %02X:%02X:%02X:%02X:%02X:%02X",
		pRARPHdr->src_mac_addr[0], pRARPHdr->src_mac_addr[1],
		pRARPHdr->src_mac_addr[2], pRARPHdr->src_mac_addr[3],
		pRARPHdr->src_mac_addr[4], pRARPHdr->src_mac_addr[5]);
	info[1] = str_format("%02X:%02X:%02X:%02X:%02X:%02X",
		pRARPHdr->src_mac_addr[0], pRARPHdr->src_mac_addr[1],
		pRARPHdr->src_mac_addr[2], pRARPHdr->src_mac_addr[3],
		pRARPHdr->src_mac_addr[4], pRARPHdr->src_mac_addr[5]);
	info[2] = "Broadcast";
	rarp[7] = str_format("Sender IP address: %u.%u.%u.%u", pRARPHdr->src_ip_addr[0], pRARPHdr->src_ip_addr[1],
		pRARPHdr->src_ip_addr[2], pRARPHdr->src_ip_addr[3]);
	rarp[8] = str_format("Target MAC address: %02X:%02X:%02X:%02X:%02X:%02X",
		pRARPHdr->dest_mac_addr[0], pRARPHdr->dest_mac_addr[1],
		pRARPHdr->dest_mac_addr[2], pRARPHdr->dest_mac_addr[3],
		pRARPHdr->dest_mac_addr[4], pRARPHdr->dest_mac_addr[5]);
	rarp[9] = str_format("Target IP address: %u.%u.%u.%u", pRARPHdr->dest_ip_addr[0], pRARPHdr->dest_ip_addr[1],
		pRARPHdr->dest_ip_addr[2], pRARPHdr->dest_ip_addr[3]);
	tree[2] = rarp;
	tree.pop_back();
	tree_header.pop_back();
	tree.pop_back();
	tree_header.pop_back();
}
//ICMP
void Analyzer::ParseICMPPacket() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER) + flag;
	ICMP_HEADER* pICMPHdr = (ICMP_HEADER*)pkt;
	info[3] = "ICMP";
	if (pICMPHdr->Type == 0) {
		info[5] = str_format("Echo (ping) reply");
		icmp[1] = str_format("Type: %u (Echo (ping) reply)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 3) {
		info[5] = str_format("Destination unreachable");
		icmp[1] = str_format("Type: %u (Destination unreachable)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 8) {
		info[5] = str_format("Echo (ping) request");
		icmp[1] = str_format("Type: %u (Echo (ping) request)", pICMPHdr->Type);
	}
	else {
		info[5] = str_format("others");
		icmp[1] = str_format("Type: %u (others)", pICMPHdr->Type);
	}
	icmp[0] = "Internet Control Message Protocol";
	tree_header[3] = icmp[0];
	icmp[2] = str_format("Code: %u", pICMPHdr->Code);
	icmp[3] = str_format("Checksum: 0x%4x", ntohs(pICMPHdr->Checksum));
	u_short temp = checksum((u_short*)pkt, caplen-sizeof(MAC_HEADER)-flag);
	if (temp == 0x0) {
		icmp[4] = "[Checksum status: Good]";
	}
	else if (temp == 0xffff) {
		icmp[4] = "[Checksum status: Good]";
	}
	else {
		icmp[4] = "[Checksum status: Bad]";
	}

	tree[3] = icmp;
	tree.pop_back();
	tree_header.pop_back();
}
void Analyzer::ParseIGMPPacket() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER) + flag;
	IGMP_HEADER* pIGMPHdr = (IGMP_HEADER*)pkt;
	int a = ntohs(pIGMPHdr->Src_Num);
	u_int* index = (u_int*)pIGMPHdr;
	index = index + 3;
	u_char* pt = (u_char*)index;
	u_short* src = (u_short*)(pIGMPHdr->Group_Addr + 2);
	igmp[0] = "Internet Group Management Protocol";
	tree_header[3] = igmp[0];
	switch (pIGMPHdr->Type) {
	case 0x11://查询报文,v1/v2/v3都有可能
		if (pIGMPHdr->Max_response_time == 0) {//说明是unused字段,判断为v1
			igmp[1] = "[IGMP Version: 1]";
			igmp[2] = str_format("Type: Membership Query (0x%2x)", pIGMPHdr->Type);
			igmp[3] = "Reserved: 00";
			igmp[4] = str_format("Checksum: 0x%4x", ntohs(pIGMPHdr->Checksum));
			igmp[6] = "Multicast Address: 0.0.0.0";
			info[3] = "IGMPv1";			
			info[5] = str_format("Membership Query");	
		}
		else {
			string mua = str_format("%u.%u.%u.%u", pIGMPHdr->Group_Addr[0], pIGMPHdr->Group_Addr[1],
				pIGMPHdr->Group_Addr[2], pIGMPHdr->Group_Addr[3]);
			if (mua=="0.0.0.0") {//组播地址为0,判断为v2
				igmp[1] = "[IGMP Version: 2]";
				igmp[2] = str_format("Type: Membership Query (0x%2x)", pIGMPHdr->Type);
				igmp[3] = str_format("Max Resp Time: %.1f sec (0x%2x)", pIGMPHdr->Max_response_time / 10, pIGMPHdr->Max_response_time);
				igmp[4] = str_format("Checksum: 0x%4x", ntohs(pIGMPHdr->Checksum));
				igmp[6] = "Multicast Address: 0.0.0.0";
				info[3] = "IGMPv2";
				info[5] = str_format("Membership Query, general");
			}
			else {
				igmp[1] = "[IGMP Version: 3]";
				igmp[2] = str_format("Type: Membership Query (0x%2x)", pIGMPHdr->Type);
				igmp[3] = str_format("Max Resp Time: %.1f sec (0x%2x)", pIGMPHdr->Max_response_time / 10, pIGMPHdr->Max_response_time);
				igmp[4] = str_format("Checksum: 0x%4x", ntohs(pIGMPHdr->Checksum));
				igmp[6] = str_format("Multicast Address: %s", info[2]);
				if (pIGMPHdr->SQRV >> 3 == 0) {
					igmp[7] = "S: 0 (Do not suppress router side processing)";
				}
				else {
					igmp[7] = "S: 1 (Suppress router side processing)";
				}
				igmp[8] = str_format("QRV: %u",pIGMPHdr->SQRV&0x7);
				igmp[9] = str_format("QOIC: %u", pIGMPHdr->QQIC);
				igmp[10]= str_format("Num Src: %u", ntohs(pIGMPHdr->Src_Num));
				for (int i = 0; i <  4*a; ) {
					igmp.push_back (str_format("Source Address: %u.%u.%u.%u",pt+i,pt+i+1,pt+i+2,pt+i+3));
					i = i + 4;
				}
				info[3] = "IGMPv3";
				info[5] = str_format("Membership Query, specific for group %s", info[2]);
			}
		}
		break;
	case 0x12://v1的报告
		igmp[1] = "[IGMP Version: 1]";
		igmp[2] = str_format("Type: Membership Report (0x%2x)", pIGMPHdr->Type);
		igmp[3] = "Reserved: 00";
		igmp[4] = str_format("Checksum: 0x%4x", ntohs(pIGMPHdr->Checksum));
		igmp[6] = str_format("Multicast Address: %s",info[2]);
		info[3] = "IGMPv1";
		info[5] = str_format("Membership Report");
		break;
	case 0x16://v2的报告
		igmp[1] = "[IGMP Version: 2]";
		igmp[2] = str_format("Type: Membership Report (0x%2x)", pIGMPHdr->Type);
		igmp[3] = str_format("Max Resp Time: %.1f sec (0x%2x)", pIGMPHdr->Max_response_time / 10, pIGMPHdr->Max_response_time);
		igmp[4] = str_format("Checksum: 0x%4x", ntohs(pIGMPHdr->Checksum));
		igmp[6] = str_format("Multicast Address: %s", info[2]);
		info[3] = "IGMPv2";
		info[5] = str_format("Membership Report group %s", info[2]);		
		break;
	case 0x17://v2的离开
		igmp[1] = "[IGMP Version: 2]";
		igmp[2] = str_format("Type: Leave Group (0x%2x)", pIGMPHdr->Type);
		igmp[3] = str_format("Max Resp Time: %.1f sec (0x%2x)", pIGMPHdr->Max_response_time / 10, pIGMPHdr->Max_response_time);
		igmp[4] = str_format("Checksum: 0x%4x", ntohs(pIGMPHdr->Checksum));
		igmp[6] = str_format("Multicast Address: %u.%u.%u.%u", pIGMPHdr->Group_Addr[0], pIGMPHdr->Group_Addr[1],
			pIGMPHdr->Group_Addr[2], pIGMPHdr->Group_Addr[3]);
		info[3] = "IGMPv2";
		info[5] = str_format("Leave group %u.%u.%u.%u", pIGMPHdr->Group_Addr[0], pIGMPHdr->Group_Addr[1],
			pIGMPHdr->Group_Addr[2], pIGMPHdr->Group_Addr[3]);
		break;
	case 0x22://v3的报告
		igmp[1] = "[IGMP Version: 3]";
		igmp[2] = str_format("Type: Membership Report (0x%2x)", pIGMPHdr->Type);
		igmp[3] = "Reserved: 00";
		igmp[4] = str_format("Checksum: 0x%4x", ntohs(pIGMPHdr->Checksum));
		igmp[6] = str_format("Multicast Address: %u.%u.%u.%u", pIGMPHdr->Group_Addr[0], pIGMPHdr->Group_Addr[1],
			pIGMPHdr->Group_Addr[2], pIGMPHdr->Group_Addr[3]);
		igmp[7] = "Reserved: 0000";
		igmp[8] = str_format("Num Src: %u", ntohs(*src));
		igmp.pop_back();
		igmp.pop_back();
		pt = pt + 4;
		for (int i = 0; i < 4 * a; ) {
			igmp.push_back(str_format("Source Address: %u.%u.%u.%u", pt + i, pt + i + 1, pt + i + 2, pt + i + 3));
			i = i + 4;
		}
		info[3] = "IGMPv3";
		info[5] = str_format("Membership Report");
		break;
	default:
		info[3] = "IGMP";
		info[5] = str_format("others");
		igmp[1] = str_format("Type: others (0x%2x)", pIGMPHdr->Type);
	}
	u_short temp = checksum((u_short*)pkt, caplen - sizeof(MAC_HEADER) - flag);
	if (temp == 0x0) {
		igmp[5] = "[Checksum status: Good]";
	}
	else if (temp == 0xffff) {
		igmp[5] = "[Checksum status: Good]";
	}
	else {
		igmp[5] = "[Checksum status: Bad]";
	}
	tree[3] = igmp;
	tree.pop_back();
	tree_header.pop_back();
}
//ICMPv6
void Analyzer::ParseICMPv6Packet() {
	u_char* pkt = pPkt + sizeof(MAC_HEADER) + flag;
	ICMP_HEADER* pICMPHdr = (ICMP_HEADER*)pkt;
	info[3] = "ICMPv6";
	if (pICMPHdr->Type == 1) {
		info[5] = "Destination unreachable";
		icmp[1] = str_format("Type: %u (Destination Unreachable)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 2) {
		info[5] = "Packet Too Big";
		icmp[1] = str_format("Type: %u (Packet Too Big)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 3) {
		info[5] = "Time Exceeded";
		icmp[1] = str_format("Type: %u (Time Exceeded)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 4) {
		info[5] = "Parameter Problem";
		icmp[1] = str_format("Type: %u (Parameter Problem)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 128) {
		info[5] = "Echo Request";
		icmp[1] = str_format("Type: %u (Echo Request)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 129) {
		info[5] = "Echo Reply";
		icmp[1] = str_format("Type: %u (Echo Reply)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 130) {
		info[5] = "Multicast Listener Query";
		icmp[1] = str_format("Type: %u (Multicast Listener Query)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 131) {
		info[5] = "Multicast Listener Report";
		icmp[1] = str_format("Type: %u (Multicast Listener Report)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 132) {
		info[5] = "Multicast Listener Done";
		icmp[1] = str_format("Type: %u (Multicast Listener Done)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 133) {
		info[5] = "Router Solicitation";
		icmp[1] = str_format("Type: %u (Router Solicitation)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 134) {
		info[5] = "Router Advertisement";
		icmp[1] = str_format("Type: %u (Router Advertisement)", pICMPHdr->Type);
	}
	else if (pICMPHdr->Type == 135) {
		info[5] = "Neighbor Solicitation";
		icmp[1] = str_format("Type: %u (Neighbor Solicitation)", pICMPHdr->Type);
	}
	else {
		info[5] = "Redirect Message";
		icmp[1] = str_format("Type: %u (Redirect Message)", pICMPHdr->Type);
	}
	icmp[0] = "Internet Control Message Protocol v6";
	tree_header[3] = icmp[0];
	icmp[2] = str_format("Code: %u", pICMPHdr->Code);
	icmp[3] = str_format("Checksum: 0x%4x", ntohs(pICMPHdr->Checksum));
	memcpy(ck ,&psd_headerv6 , sizeof(PSD_HEADERv6));
	memcpy(ck + sizeof(PSD_HEADERv6), pkt, ntohs(psd_headerv6.length));
	u_short temp = checksum((u_short*)ck, sizeof(PSD_HEADERv6)+ ntohs(psd_headerv6.length));
	if (temp == 0x0) {
		icmp[4] = "[Checksum status: Good]";
	}
	else if (temp == 0xffff) {
		icmp[4] = "[Checksum status: Good]";
	}
	else {
		icmp[4] = "[Checksum status: Bad]";
	}
	tree[3] = icmp;
	tree.pop_back();
	tree_header.pop_back();
}
