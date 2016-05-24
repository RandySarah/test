#include"udp_data.h"

void udp_data::serialize(std::string &_out)
{
	Json::Value _val;
	_val["name"] = this->name;
	_val["msg"] = this->msg;
	_val["cmd"] = this->cmd;

	json_comm _json;
	_json.set_val(_val);
	_json.val_to_str();
	_json.get_str(_out);
}

void udp_data::deserialize(std::string &_in)
{
	Json::Value _val;
	json_comm _json;
	_json.set_str(_in);
	_json.str_to_val();
	_json.get_val(_val);

	this->name = _val["name"].asString();
	this->msg = _val["msg"].asString();
	this->cmd = _val["cmd"].asString();
}

#ifdef _DEBUG_
int main()
{
	std::string _out;
	udp_data _data;
	_data.set_name("pig");
	_data.set_msg("happy");
	_data.set_cmd("none");

	_data.serialize(_out);
	cout<<_out<<endl;
}
#endif
