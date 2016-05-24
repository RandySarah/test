#include"udp_client.h"



udp_client::udp_client(std::string &_ip,const short &_port)
	:remote_ip(_ip)
	,remote_port(_port)
	,sock(-1)
{}

udp_client::~udp_client()
{
	if(sock>-1){
		close(sock);
	}
}

void udp_client::init_client()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0){
		perror("socket");
		exit(1);
	}
}

bool udp_client::send_data(const std::string &_data)
{
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(remote_port);
	remote.sin_addr.s_addr = inet_addr(remote_ip.c_str());
	socklen_t _len = sizeof(remote);

	ssize_t _size = sendto(sock,_data.c_str(),_data.size(),0,(struct sockaddr*)&remote,_len);

	if(_size<0){
	}else{
	}

	return true;
}

bool udp_client::recv_data(std::string &_out)
{
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	ssize_t _size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);

	if(_size > 0){
		buf[_size] ='\0';
		_out = buf;
	}else if(_size == 0){
	}else{
		
	}
	return true;
}


static void usage(string _proc)
{
	cout<<_proc<<"[ip] [port]"<<endl;
}
//int main(int argc,char *argv[])
//{
//	if(argc != 3){
//		usage(argv[0]);
//		return 0;
//	}
//	short _port = atoi(argv[2]);
//	string _ip = argv[1];
//	udp_client _cli(_ip,_port);
//	_cli.init_client();
//	std::string _out;
//	char _msg[1024];
//	
//	std::string name;
//	cout<<"please enter name: ";
//	fflush(stdout);
//	cin>>name;
//	
//	std::string msg;
//	std::string cmd = "none";
//	std::string _send_json;
//	udp_data _data;
//	while(1){
//		memset(_msg,'\0',sizeof(_msg));
//		cout<<"please enter :";
//		fflush(stdout);
//		//gets(_msg);
//		cin>>_msg;
//		msg = _msg;
//		
//		_data.set_name(name);
//		_data.set_msg(msg);
//		_data.set_cmd(cmd);
//		_data.serialize(_send_json);
//
//		_cli.send_data(_send_json);
//		_cli.recv_data(_out);
//		
//		cout<<"server broadcast: "<<_out<<endl;
//		//string _msg = "hello world";
//		//_cli.send_data(_msg);
//		//sleep(1);
//	}
//
////	cout<<"hello client"<<endl;
//}
//


std::string g_name;
//udp_client _cli;
udp_client *_clip = NULL;

void *header(void *arg)
{
	window *_win = (window*)arg;
	bool done = false;
	int _y_high = 0;
	int _x_width = 0;

	std::string _msg = "Welcome To Chatroom";
	_win->draw_header(-1,-1,_msg);
	int _x_msg= 1;
	int _y_msg;
	while(!done)
	{
		getmaxyx(_win->header,_y_high,_x_width);
		 _y_msg = _y_high/2;
	
		
		_win->draw_header(_y_msg,_x_msg,_msg);
		sleep(1);
		_win->clear_win_line(_win->header,_y_msg,1);
		_x_msg++;
		_x_msg %= _x_width;
	}
}

void *output(void *arg)
{
	window *_win = (window*)arg;
	udp_data data;
	std::string _name;
	std::string _msg;
	std::string _cmd;

	std::string _output;
	std::string _flist;
	bool done = false;
	int _y_max;
	int _x_max;
	int _y = 1;
	int _x = 1;

	std::vector<std::string> _flist_v;
	_win->draw_flist(_flist_v);
	_win->draw_output(-1,-1,_msg);

	while(!done){
		_clip->recv_data(_msg);
		data.deserialize(_msg);

		data.get_name(_name);
		data.get_msg(_msg);
		data.get_cmd(_cmd);

		_flist = _name;

		std::vector<std::string>::iterator _iter = _flist_v.begin();
		for(;_iter != _flist_v.end();_iter++){
			if(*_iter == _flist){
				break;
			}
		}
		if(_iter == _flist_v.end()){
			_flist_v.push_back(_flist);
		}
		_output = _flist;
		_output += ": ";
		_output += _msg;

		getmaxyx(_win->output,_y_max,_x_max);
		_win->draw_flist(_flist_v);
		_win->draw_output(_y,_x,_output);

		//_win->put_str_to_win(_win->output,_y,1,_msg);
		_y++;
		if(_y >= _y_max-1){
			_win->clear_win_line(_win->output,1,_y_max-1);
			_y = 1;
		}

		getmaxyx(_win->flist,_y_max,_x_max);
		int _y_flist = 1;
		int _x_flist = 1;
		//_win->put_str_to_win(_win->flist,_y_flist,_x_flist,_flist);

		//_win->draw_output(_y,_x,_msg);
		_win->draw_flist(_flist_v);

		usleep(1000);
	}
}

void *input(void *arg)
{
	window* _win = (window*)arg;
	bool done = false;

	std::string msg;
	std::string cmd = "none";
	std::string _send_json;

	udp_data _data;
	_data.set_name(g_name);

	while(!done){
		_win->draw_input();
		_win->get_str_to_win(_win->input,msg);

		_data.set_msg(msg);
		_data.set_cmd(cmd);
		_data.serialize(_send_json);
		_clip->send_data(_send_json);

		_win->draw_input();
		sleep(1);
	}
}


int main(int argc,char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return 0;
	}
	short _port = atoi(argv[2]);
	string _ip = argv[1];
	udp_client _cli(_ip,_port);
	//_cli(_ip,_port);
	_cli.init_client();
	_clip = &_cli;
	//char _msg[1024];
	
	cout<<"please enter name: ";
	fflush(stdout);
	cin>>g_name;

	//std::string _out;
	//std::string msg;
	
	window _w;
	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,header,(void*)&_w);
	pthread_create(&tid2,NULL,output,(void*)&_w);
	pthread_create(&tid3,NULL,input,(void*)&_w);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	//while(1){
	//	memset(_msg,'\0',sizeof(_msg));
	//	cout<<"please enter :";
	//	fflush(stdout);
	//	//gets(_msg);
	//	cin>>_msg;
	//	msg = _msg;
	//	
	//	_cli.recv_data(_out);
	//	
	//	cout<<"server broadcast: "<<_out<<endl;
	//	//string _msg = "hello world";
	//	//_cli.send_data(_msg);
	//	//sleep(1);
	//}

//	cout<<"hello client"<<endl;
}
