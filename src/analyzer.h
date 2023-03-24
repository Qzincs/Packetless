#pragma once
#include<iostream>
#include<string>
using namespace std;
#include <winsock2.h>
#include <memory>
#include<vector>
#pragma comment(lib,"ws2_32.lib")
typedef struct { //TCP数据报头
	u_short SrcPort; //源端口
	u_short DstPort; //目的端口
	u_int Seq; //序号
	u_int Ack; //确认号
	u_char HeaderLen; //数据报头的长度(4 bit) + 保留(4 bit)
	u_char Flags; //标识TCP不同的控制消息
	u_short Window; //窗口大小
	u_short Checksum; //校验和
	u_short UrgentPointer;  //紧急指针
}TCP_HEADER;
typedef struct { //UDP数据报头
	u_short SrcPort; //源端口
	u_short DstPort; //目的端口
	u_short Length; //长度
	u_short Checksum; //校验和
}UDP_HEADER;
typedef struct { //ICMP数据报头
	u_char Type; //类型
	u_char Code; //代码
	u_short Checksum; //校验和
}ICMP_HEADER;
typedef struct { //IGMP数据报头
	u_char Type;//类型
	u_char Max_response_time; //最大响应时间
	u_short Checksum; //校验和
	u_char Group_Addr[4];  //组播地址
	u_char SQRV;//前四位保留,s容错,qrv重传
	u_char QQIC;//定期查询间隔
	u_short Src_Num;
}IGMP_HEADER;
typedef struct {
	u_char DesMacAddr[6];//目的地址
	u_char SrcMacAddr[6];//源地址:
	u_short LengthOrType;//数据长度或类型
}MAC_HEADER;
//MAC帧类型
const u_short MAC_TYPE_IP = 0x0800;
const u_short MAC_TYPE_ARP = 0x0806;
const u_short MAC_TYPE_RARP = 0x0835;
const u_short MAC_TYPE_IPv6 = 0x86dd;
typedef struct {
	u_short hardware_type;//16位硬件类型
	u_short proto_type;//16位协议类型
	u_char hardware_addr_len;//8位硬件地址长度
	u_char proto_addr_len;//8位协议地址长度
	u_short operation_code;//16位操作码
	u_char src_mac_addr[6];//源以太网地址
	u_char src_ip_addr[4];//源IP地址
	u_char dest_mac_addr[6];//目的以太网地址
	u_char dest_ip_addr[4]; //目的IP地址
}ARP_HEADER;
//ARP报文操作码类型
const u_short ARP_OP_REQUEST = 1;//ARP请求
const u_short ARP_OP_REPLY = 2;//ARP应答
typedef struct {
	u_short hardware_type;//16位硬件类型
	u_short proto_type;//16位协议类型
	u_char hardware_addr_len;//8位硬件地址长度
	u_char proto_addr_len;//8位协议地址长度
	u_short operation_code;//16位操作码
	u_char src_mac_addr[6];//源以太网地址
	u_char src_ip_addr[4];//源IP地址
	u_char dest_mac_addr[6];//目的以太网地址
	u_char dest_ip_addr[4]; //目的IP地址
}RARP_HEADER;
//RARP报文操作码类型
const u_short RARP_OP_REQUEST = 3;//ARP请求
const u_short RARP_OP_REPLY = 4;//ARP应答
typedef struct
{ //IP数据报头
	u_char Ver_HeaderLen;//版本+报头长度
	u_char TOS;            //服务类型
	u_short TotalLen;       //总长度
	u_short ID; //标识
	u_short Flag_Segment;   //标志+片偏移
	u_char TTL;            //生存周期
	u_char Protocol;       //协议类型
	u_short Checksum;       //头部校验和
	u_char src_ip_addr[4];//源IP地址
	u_char dest_ip_addr[4]; //目的IP地址
} IP_HEADER;
typedef struct
{ //IPv6数据报头
	u_char Ver : 4;//版本
	u_char Traffic_class_1:4 ;//流量等级
	u_char Traffic_class_2 : 4;
	u_char Flow_label_1:4;            //流标签
	u_short Flow_label_2;
	u_short TotalLen;       //总长度
	u_char Next_header; //下一报头
	u_char Hop_limit;            //跳数限制
	u_short src_ip_addr[8];//源IP地址
	u_short dest_ip_addr[8]; //目的IP地址
} IPv6_HEADER;
const u_char IP_TYPE_IPv6 = 0x0;
const u_char IP_TYPE_ICMP = 0x1;
const u_char IP_TYPE_IGMP = 0x2;
const u_char IP_TYPE_GGP = 0x3;
const u_char IP_TYPE_TCP = 0x6;
const u_char IP_TYPE_EGP = 0x8;
const u_char IP_TYPE_UDP = 0x11;
const u_char IP_TYPE_ICMPv6 = 0x3a;
template<typename ... Args>
static std::string str_format(const std::string& format, Args ... args);//格式化输出字符串的函数
u_short checksum(u_short* packet, int packlen);//计算校验和的函数
typedef struct//ipv6的伪首部
{ 
	u_short src_ip_addr[8];//源IP地址
	u_short dest_ip_addr[8]; //目的IP地址
	u_short bank_1;//留空
	u_short length;//下一层长度
	u_char bank_2[3];//留空
	u_char nexthead;//下一跳类型
} PSD_HEADERv6;
typedef struct//ip的伪首部
{
	u_char src_ip_addr[4];//源IP地址
	u_char dest_ip_addr[4]; //目的IP地址
	u_char bank;//留空
	u_char protocol;//下一层协议类型
	u_short length;//tcp/udp的长度
} PSD_HEADER;
//将解析函数和解析结果封装在一个类里,这样便于调用,且可以通过修改类成员变量的方法存储解析结果
class Analyzer {
public:
	void Analyze(int caplen, u_char* pkt);//初始函数,不用构造函数的原因是只生成一个类,后续通过不断调用初始函数来解析新的包
	int caplen;//捕获长度,从抓包处获得
	u_char* pPkt;//包的首地址,从抓包处获得
	int ip_num;//ip/ipv6里的总长度,是ip+tcp/udp...的长度
	int flag;//ip头的长度,用于区分上一层是ip还是ipv6
	char ck[1500];//校验和用到的字符数组,用于将伪首部和首部连在一起放入cheacksum函数
	PSD_HEADERv6 psd_headerv6;//创建一个ipv6的伪首部
	PSD_HEADER psd_header;//ip伪首部
	vector<string> info;//横向信息,0是时间戳,1源地址,2目的地址,3协议类型,4长度,5信息
	vector<string> tree_header;//树状结构的头节点,0:捕捉信息;1:mac;  2:ip/arp/rarp;3:tcp/udp,   4http 
	vector<vector<string>> tree;//树状结构的子节点,二维数组中,各数组的0索引仍为头节点信息
	vector<string> mac;//存储树状结构的mac节点的信息,每一行对应一个下标,下面同理,信息内容全参考wireshark
	vector<string> arp;
	vector<string> rarp;
	vector<string> ip;
	vector<string> ipv6;
	vector<string> tcp;
	vector<string> udp;
	vector<string> icmp;
	vector<string> igmp;
	vector<string> http;

	void ParseMACPacket();//解析mac头部的函数,下面同理
	void ParseARPPacket();
	void ParseTCPPacket();
	void ParseIPPacket();
	void ParseUDPPacket();
	void ParseRARPPacket();
	void ParseICMPPacket();
	void ParseIGMPPacket();
	void ParseIPv6Packet();
	void ParseICMPv6Packet();
};
