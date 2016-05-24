#pragma once 
#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"../comm/udp_data.h"
#include"../window/window.h"
using namespace std;

class udp_client{
	public:
		udp_client(std::string &_ip,const short &_port);
		~udp_client();

		void init_client();
		bool recv_data(std::string &_out);
		bool send_data(const std::string &_data);
	private:
		std::string remote_ip;
		short remote_port;
		int sock;
};
