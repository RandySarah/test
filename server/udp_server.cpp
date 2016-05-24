#include "udp_server.h"

udp_server::udp_server(const std::string &_ip,const short &_port,int pool_cap)
	:ip(_ip)
	,port(_port)
	,sock(-1)
	,pool(pool_cap)
{}

udp_server::~udp_server()
{
	if(sock > -1){
		close(sock);
	}
}

void udp_server::init_server()
{
	this->sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1){
		perror("socket");//printf log
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	if(ip == ""){
		local.sin_addr.s_addr = htonl(INADDR_ANY);
	}else{
		local.sin_addr.s_addr = inet_addr(ip.c_str());
	}
	if( bind(sock,(struct sockaddr*)&local,sizeof(local))==-1 ){
		perror("bind");
		exit(2);
	}
}

bool udp_server::recv_data(string &_out)
{
	struct sockaddr_in _remote;
	socklen_t _len = sizeof(_remote);

	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	ssize_t _size = recvfrom(this->sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&_remote,&_len);
		//cout<<"debug:recv_data size is: "<<_size<<endl;

	if(_size<0){
	}else if(_size == 0){
	}else{
		_out = buf;
		pool.put_data(_out);
		add_user(_remote);
	}
	return true;
}

bool udp_server::send_data(const std::string &_data,struct sockaddr_in *_client,socklen_t _len)
{
	ssize_t _size = sendto(this->sock,_data.c_str(),_data.size(),0,(struct sockaddr*)_client,_len);
	if(_size < 0){
		perror("sendto");
		return false;
	}else{}
	return true;
}

void udp_server::broadcast_data()
{
	std::string _data;
	pool.get_data(_data);
	//cout<<"broaddebug1: "<<_data<<endl;
	std::map<std::string,struct sockaddr_in>::iterator _iter;
	for(_iter = online_user.begin();_iter != online_user.end();_iter++){
		send_data(_data,&(_iter->second),sizeof(_iter->second));
	}
	//cout<<"broaddebug2: "<<_data<<endl;
}

bool udp_server::add_user(const struct sockaddr_in &_client)
{
	std::string _ip = inet_ntoa(_client.sin_addr);
	std::map<std::string,struct sockaddr_in>::iterator _iter = online_user.find(_ip);
	if(_iter != online_user.end()){//exist
		return false;
	}else{
		online_user.insert(std::pair<std::string,struct sockaddr_in>(_ip,_client));
	}
}

void *recv_handler(void *arg)
{
	udp_server *recv_ser = (udp_server*)arg;
	std::string _client_info;
	bool done = false;
	while(!done){
		recv_ser->recv_data(_client_info);
		//cout<<_client_info<<endl;
	}
}

void *broadcast_handler(void *arg)
{
	//cout<<"broadcast_handler"<<endl;
	udp_server *broadcast_ser = (udp_server*)arg;
	bool done = false;
	while(!done){
		broadcast_ser->broadcast_data();
	}
}


static void usage(string _proc)
{
	cout<<_proc<<"[ip] [port]"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return 1;
	}
	
	daemon(0,0);

	short _port = atoi(argv[2]);
	string _ip = argv[1];
	udp_server _ser(_ip,_port,20);
	_ser.init_server();
	

	pthread_t recv_thread;
	pthread_t broadcast_thread;
	pthread_create(&recv_thread,NULL,recv_handler,(void*)&_ser);
	pthread_create(&broadcast_thread,NULL,broadcast_handler,(void*)&_ser);

	pthread_join(recv_thread,NULL);
	pthread_join(broadcast_thread,NULL);

//	string _out;
//	bool done = true;
//	while(done){
//		_ser.recv_data(_out);
//		cout<<_out<<endl;
//	}

//	cout<<"hello world"<<endl;
}
