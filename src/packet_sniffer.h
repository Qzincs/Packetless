#pragma once
#include <pcap.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
using namespace std;

class Packet_Sniffer
{
public:
	char errbuf[PCAP_ERRBUF_SIZE];
	//Packet_Sniffer();		
	//∑Ω∑®
	int set_devs();
	void set_sniffer_devs(int dev_num);
	int set_filter(string packet_filter);
	bool set_pkt(bool mode);
	int set_openfile();
	void close_file();
	bool open_file(const char* file_name);
	// Ù–‘
	pcap_if_t* alldevs;
	pcap_if_t* dev_s;
	pcap_t* fp = NULL;
	vector<bpf_u_int32> caplen;
	vector<u_char*> pkt_data;
	vector<struct timeval> time_stamp;
	vector<string> devs_name;
	vector<string> devs_description;
	vector<string> devs_ip_address;
	struct pcap_pkthdr* header;
	string file;
	pcap_dumper_t* dumpfile;
	
};