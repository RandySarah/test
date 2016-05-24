#pragma once 
#include"json/json.h"
#include<iostream>
#include<string>
#include"json_comm.h"
using namespace std;

class udp_data{
	public:
		udp_data(){}
		~udp_data(){}

		void set_name(const std::string &_in){name = _in;}
		void set_msg(const std::string &_in){msg = _in;}
		void set_cmd(const std::string &_in){cmd = _in;}

		void get_name(std::string &_out){_out = name;}
		void get_msg(std::string &_out){_out = msg;}
		void get_cmd(std::string &_out){_out = cmd;}

		void serialize(std::string &_out);
		void deserialize(std::string &_in);

	private:
		std::string name;
		std::string msg;
		std::string cmd;
};
