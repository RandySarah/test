#pragma once 

#include<iostream>
#include"json/json.h"
#include<string>

using namespace std;

class json_comm{
	public:
		json_comm();
		~json_comm();
		
		bool set_val(const Json::Value &_val);
		bool val_to_str();
		bool get_str(std::string &_out_str);
		
		bool set_str(const std::string &_str);
		bool str_to_val();
		bool get_val(Json::Value &_out_val);

	private:
		Json::Value val;
		std::string str;
};
