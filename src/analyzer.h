#pragma once
#include<iostream>
#include<string>
using namespace std;
#include <winsock2.h>
#include <memory>
#include<vector>
#pragma comment(lib,"ws2_32.lib")
typedef struct { //TCP���ݱ�ͷ
	u_short SrcPort; //Դ�˿�
	u_short DstPort; //Ŀ�Ķ˿�
	u_int Seq; //���
	u_int Ack; //ȷ�Ϻ�
	u_char HeaderLen; //���ݱ�ͷ�ĳ���(4 bit) + ����(4 bit)
	u_char Flags; //��ʶTCP��ͬ�Ŀ�����Ϣ
	u_short Window; //���ڴ�С
	u_short Checksum; //У���
	u_short UrgentPointer;  //����ָ��
}TCP_HEADER;
typedef struct { //UDP���ݱ�ͷ
	u_short SrcPort; //Դ�˿�
	u_short DstPort; //Ŀ�Ķ˿�
	u_short Length; //����
	u_short Checksum; //У���
}UDP_HEADER;
typedef struct { //ICMP���ݱ�ͷ
	u_char Type; //����
	u_char Code; //����
	u_short Checksum; //У���
}ICMP_HEADER;
typedef struct { //IGMP���ݱ�ͷ
	u_char Type;//����
	u_char Max_response_time; //�����Ӧʱ��
	u_short Checksum; //У���
	u_char Group_Addr[4];  //�鲥��ַ
	u_char SQRV;//ǰ��λ����,s�ݴ�,qrv�ش�
	u_char QQIC;//���ڲ�ѯ���
	u_short Src_Num;
}IGMP_HEADER;
typedef struct {
	u_char DesMacAddr[6];//Ŀ�ĵ�ַ
	u_char SrcMacAddr[6];//Դ��ַ:
	u_short LengthOrType;//���ݳ��Ȼ�����
}MAC_HEADER;
//MAC֡����
const u_short MAC_TYPE_IP = 0x0800;
const u_short MAC_TYPE_ARP = 0x0806;
const u_short MAC_TYPE_RARP = 0x0835;
const u_short MAC_TYPE_IPv6 = 0x86dd;
typedef struct {
	u_short hardware_type;//16λӲ������
	u_short proto_type;//16λЭ������
	u_char hardware_addr_len;//8λӲ����ַ����
	u_char proto_addr_len;//8λЭ���ַ����
	u_short operation_code;//16λ������
	u_char src_mac_addr[6];//Դ��̫����ַ
	u_char src_ip_addr[4];//ԴIP��ַ
	u_char dest_mac_addr[6];//Ŀ����̫����ַ
	u_char dest_ip_addr[4]; //Ŀ��IP��ַ
}ARP_HEADER;
//ARP���Ĳ���������
const u_short ARP_OP_REQUEST = 1;//ARP����
const u_short ARP_OP_REPLY = 2;//ARPӦ��
typedef struct {
	u_short hardware_type;//16λӲ������
	u_short proto_type;//16λЭ������
	u_char hardware_addr_len;//8λӲ����ַ����
	u_char proto_addr_len;//8λЭ���ַ����
	u_short operation_code;//16λ������
	u_char src_mac_addr[6];//Դ��̫����ַ
	u_char src_ip_addr[4];//ԴIP��ַ
	u_char dest_mac_addr[6];//Ŀ����̫����ַ
	u_char dest_ip_addr[4]; //Ŀ��IP��ַ
}RARP_HEADER;
//RARP���Ĳ���������
const u_short RARP_OP_REQUEST = 3;//ARP����
const u_short RARP_OP_REPLY = 4;//ARPӦ��
typedef struct
{ //IP���ݱ�ͷ
	u_char Ver_HeaderLen;//�汾+��ͷ����
	u_char TOS;            //��������
	u_short TotalLen;       //�ܳ���
	u_short ID; //��ʶ
	u_short Flag_Segment;   //��־+Ƭƫ��
	u_char TTL;            //��������
	u_char Protocol;       //Э������
	u_short Checksum;       //ͷ��У���
	u_char src_ip_addr[4];//ԴIP��ַ
	u_char dest_ip_addr[4]; //Ŀ��IP��ַ
} IP_HEADER;
typedef struct
{ //IPv6���ݱ�ͷ
	u_char Ver : 4;//�汾
	u_char Traffic_class_1:4 ;//�����ȼ�
	u_char Traffic_class_2 : 4;
	u_char Flow_label_1:4;            //����ǩ
	u_short Flow_label_2;
	u_short TotalLen;       //�ܳ���
	u_char Next_header; //��һ��ͷ
	u_char Hop_limit;            //��������
	u_short src_ip_addr[8];//ԴIP��ַ
	u_short dest_ip_addr[8]; //Ŀ��IP��ַ
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
static std::string str_format(const std::string& format, Args ... args);//��ʽ������ַ����ĺ���
u_short checksum(u_short* packet, int packlen);//����У��͵ĺ���
typedef struct//ipv6��α�ײ�
{ 
	u_short src_ip_addr[8];//ԴIP��ַ
	u_short dest_ip_addr[8]; //Ŀ��IP��ַ
	u_short bank_1;//����
	u_short length;//��һ�㳤��
	u_char bank_2[3];//����
	u_char nexthead;//��һ������
} PSD_HEADERv6;
typedef struct//ip��α�ײ�
{
	u_char src_ip_addr[4];//ԴIP��ַ
	u_char dest_ip_addr[4]; //Ŀ��IP��ַ
	u_char bank;//����
	u_char protocol;//��һ��Э������
	u_short length;//tcp/udp�ĳ���
} PSD_HEADER;
//�����������ͽ��������װ��һ������,�������ڵ���,�ҿ���ͨ���޸����Ա�����ķ����洢�������
class Analyzer {
public:
	void Analyze(int caplen, u_char* pkt);//��ʼ����,���ù��캯����ԭ����ֻ����һ����,����ͨ�����ϵ��ó�ʼ�����������µİ�
	int caplen;//���񳤶�,��ץ�������
	u_char* pPkt;//�����׵�ַ,��ץ�������
	int ip_num;//ip/ipv6����ܳ���,��ip+tcp/udp...�ĳ���
	int flag;//ipͷ�ĳ���,����������һ����ip����ipv6
	char ck[1500];//У����õ����ַ�����,���ڽ�α�ײ����ײ�����һ�����cheacksum����
	PSD_HEADERv6 psd_headerv6;//����һ��ipv6��α�ײ�
	PSD_HEADER psd_header;//ipα�ײ�
	vector<string> info;//������Ϣ,0��ʱ���,1Դ��ַ,2Ŀ�ĵ�ַ,3Э������,4����,5��Ϣ
	vector<string> tree_header;//��״�ṹ��ͷ�ڵ�,0:��׽��Ϣ;1:mac;  2:ip/arp/rarp;3:tcp/udp,   4http 
	vector<vector<string>> tree;//��״�ṹ���ӽڵ�,��ά������,�������0������Ϊͷ�ڵ���Ϣ
	vector<string> mac;//�洢��״�ṹ��mac�ڵ����Ϣ,ÿһ�ж�Ӧһ���±�,����ͬ��,��Ϣ����ȫ�ο�wireshark
	vector<string> arp;
	vector<string> rarp;
	vector<string> ip;
	vector<string> ipv6;
	vector<string> tcp;
	vector<string> udp;
	vector<string> icmp;
	vector<string> igmp;
	vector<string> http;

	void ParseMACPacket();//����macͷ���ĺ���,����ͬ��
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
