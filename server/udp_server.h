#pragma once 

#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<data_pool.h>
#include<map>


using namespace std;

class udp_server{
	public:
		udp_server(const std::string &_ip,const short &_port,int pool_cap);
		~udp_server();
		void init_server();
		void run();
		bool recv_data(string &_out);
		void broadcast_data();

	private:
		std::string ip;
		short port;
		int sock;

		std::map<std::string,struct sockaddr_in> online_user;
		data_pool pool;
		
		bool send_data(const std::string &_data,struct sockaddr_in *_client,socklen_t _len);
		bool add_user(const struct sockaddr_in &_client);
		bool del_user(const std::string &_ip);
};
