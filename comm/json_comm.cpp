#include"json_comm.h"

json_comm::json_comm()
{}
json_comm::~json_comm()
{}

bool json_comm::set_val(const Json::Value &_val)
{
	this->val = _val;	
}

bool json_comm::val_to_str()
{
	//Json::FastWriter _writer;
	Json::StyledWriter _writer;

	this->str = _writer.write(this->val);
	return true;
}

bool json_comm::get_str(std::string &_out_str)
{
	_out_str = this->str;
}

bool json_comm::set_str(const std::string &_str)
{
	this->str = _str;
}

bool json_comm::str_to_val()
{
	Json::Reader _read;
	if(_read.parse(this->str,this->val,false)){
		return true;
	}else{
		return false;
	}
}

bool json_comm::get_val(Json::Value &_out_val)
{
	_out_val = this->val;
}


//
//int main()
//{
//	json_comm _json;
//	std::string _out_str;
//	Json::Value root;
//	root["name"] = "fly";
//	root["msg"] = "nihao";
//	root["cmd"] = "none";
//
//	_json.set_val(root);
//	_json.val_to_str();
//	_json.get_str(_out_str);
//	cout<<_out_str<<endl;
//	return 0;
//}
//
