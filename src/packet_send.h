#pragma once
#include <iostream>
#include "pcap.h"
#include <pcap-stdinc.h>
#include <Win32-Extensions.h>
#include <string.h>
using namespace std;

class Packet_Send {
public:
	int* userpack;
	int len;
	char packetype;
	unsigned char* datapack;
	pcap_t* fp;
	string file;

	typedef struct macpack {
		u_int8_t dstmac[6];
		u_int8_t hostmac[6];
		u_int8_t type[2];
	}macpack;

	//��ipv4ͷ��������δ�����ѡ��
	typedef struct ipv4pack {
		u_int8_t dscp;//�����������п��ܱ�·��������Ӫ�̸���
		u_int8_t ecn;//0: null, 1/2: enable, 3: ӵ��ת��
		//u_int16_t tlen;
		u_int16_t id;
		u_int8_t depart;//0: ������Ϊ���һ��, 1: ������Ϊ���һ��, 2: ��ֹ��Ƭ
		u_int16_t offset;
		u_int8_t ttl;
		u_int8_t ptc;//1: ICMP, 2: IGMP, 4: ipv4 in ipv4, 6: TCP, 17: UDP, 89: OSPF
		u_int8_t hostip[4];
		u_int8_t dstip[4];
		//u_int8_t optlen;//0: null, else: enable
		//u_int8_t* opt;
	}ipv4pack;

	typedef struct arppack {
		u_int8_t op;//1: arp rquest, 2: arp answer, 3: rarp request, 4: rarp answer
		u_int8_t hostmac[6];
		u_int8_t hostip[4];
		u_int8_t dstmac[6];
		u_int8_t dstip[4];
	}arppack;

	typedef struct icmppack {
		u_int8_t type;
		u_int8_t code;
		//����������е�typeΪ0��8��codeΪ0ʱ��Ϊ��
		u_int16_t id;
		u_int16_t seq;
	}icmppack;

	typedef struct udppack {
		u_int16_t hostport;
		u_int16_t dstport;
	}udppack;

	typedef struct tcppack {
		u_int16_t hostport;
		u_int16_t dstport;
		u_int32_t seq;
		u_int32_t conf;
		u_int8_t offset;
		u_int8_t aec;
		u_int8_t cwr;
		u_int8_t ece;
		u_int8_t urg;
		u_int8_t ack;
		u_int8_t psh;
		u_int8_t rst;
		u_int8_t syn;
		u_int8_t fin;
		u_int16_t win;
		u_int16_t up;
		u_int8_t* op;//��ѡ��ɱ䳤
	}tcppack;

	macpack mac;
	ipv4pack ip4;
	arppack arp;
	icmppack icp;
	udppack udp;
	tcppack tcp;

	int senduser(int times);
	int sendfile(int sync);
	int makemac();
	int makeip4();
	int makearp();
	int makeicp();
	int makeudp();
	int maketcp();
};