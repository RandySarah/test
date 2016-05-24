#include"window.h"

window::window()
	:header(NULL)
	,output(NULL)
	,input(NULL)
	,flist(NULL)
{
	initscr();	
	curs_set(0);
}

window::~window()
{
	delwin(this->header);
	delwin(this->output);
	delwin(this->flist);
	delwin(this->input);
	endwin();
}

void window::put_str_to_win(WINDOW *_win, int _y, int _x, std::string &_msg)
{
	mvwaddstr(_win, _y, _x, _msg.c_str());	
}

void window::get_str_to_win(WINDOW *_win,std::string &_out)
{
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	wgetnstr(_win,buf,sizeof(buf)-1);
	_out = buf;
}

void window::clear_win_line(WINDOW *_win,int begin,int lines)
{
	while(lines-- > 0)	
	{
		wmove(_win,begin++,0); 
		wclrtoeol(_win);
	}
}

void window::draw_header(int _y_msg,int _x_msg,std::string _msg)
{
	int _y = 0;
	int _x = 0;
	int _high = LINES/5;
	int _width = COLS;

	this->header = newwin(_high,_width,_y,_x);
	box(this->header,0,0);
	if(_y_msg != -1 || _x_msg != -1){
		put_str_to_win(this->header,_y_msg,_x_msg,_msg);
	}
	wrefresh(this->header);

}

void window::draw_output(int _y_msg,int _x_msg,std::string &_msg)
{

	if(_y_msg == -1 && _x_msg == -1){		
		int _x = 0;
		int _y = LINES/5;
		int _high = (LINES*3)/5;
		int _width = (COLS*3)/4;
		this->output = newwin(_high,_width,_y,_x);
		box(this->output,0,0);
	}else{
		box(this->output,0,0);
		put_str_to_win(output,_y_msg,_x_msg,_msg);
	}
	wrefresh(this->output);
}

void window::draw_input()
{
	int _x = 0;
	int _y = (4*LINES)/5;
	int _high = LINES/5;
	int _width = COLS;
	this->input = newwin(_high,_width,_y,_x);
	box(this->input,0,0);

	int _y_str = 1;
	int _x_str = 1;
	std::string _str = "Please Enter :";
	put_str_to_win(this->input,_y_str,_x_str,_str);
	wrefresh(this->input);
}
void window::draw_flist(std::vector<std::string> &_v)
{
	int _x = (COLS*4)/5;
	int _y = LINES/5;
	int _high = (LINES*3)/5;
	int _width = (COLS*1)/4;
	this->flist = newwin(_high,_width,_y,_x);
	box(this->flist,0,0);

	int i = 0;
	for(;i< _v.size();i++){
		put_str_to_win(this->flist,i+1,1,_v[i]);
	}
	wrefresh(this->flist);
}

//void *header(void *arg)
//{
//	window *_win = (window*)arg;
//	bool done = false;
//	int _y_high = 0;
//	int _x_width = 0;
//
//	std::string _msg = "Welcome To Chatroom";
//	_win->draw_header(-1,-1,_msg);
//	int _x_msg= 1;
//	int _y_msg;
//	while(!done)
//	{
//		getmaxyx(_win->header,_y_high,_x_width);
//		 _y_msg = _y_high/2;
//	
//		
//		_win->draw_header(_y_msg,_x_msg,_msg);
//		sleep(1);
//		_win->clear_win_line(_win->header,_y_msg,1);
//		_x_msg++;
//		_x_msg %= _x_width;
//	}
//}
//
//void *output(void *arg)
//{
//	window *_win = (window*)arg;
//	bool done = false;
//	while(!done){
//		_win->draw_output();
//		_win->draw_flist();
//		sleep(1);
//	}
//}
//
//void *input(void *arg)
//{
//	window* _win = (window*)arg;
//	bool done = false;
//	std::string msg;
//	while(!done){
//		_win->draw_input();
//		_win->get_str_to_win(_win->input,msg);
//		sleep(1);
//	}
//}
//
//
//#ifdef _DEBUG_
//int main()
//{
//	window _w;
//	//_w.draw_header(-1,-1,NULL);
//
//	pthread_t tid1,tid2,tid3;
//	pthread_create(&tid1,NULL,header,(void*)&_w);
//	pthread_create(&tid2,NULL,output,(void*)&_w);
//	pthread_create(&tid3,NULL,input,(void*)&_w);
//	//_w.draw_output();
//	//_w.draw_flist();
//	//_w.draw_input();
//	sleep(5);
//
//	pthread_join(tid1,NULL);
//	pthread_join(tid2,NULL);
//	pthread_join(tid3,NULL);
//	return 0;
//}
//#endif
