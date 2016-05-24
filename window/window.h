#pragma once
#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include</usr/include/ncurses.h>
#include<pthread.h>
using namespace std;

class window{
	public:
		window();
		~window();
		void draw_header(int _y_msg,int _x_msg,std::string _msg);
		void draw_input();
		void draw_output(int _y_msg,int _x_msg,std::string &_msg);
		void draw_flist(std::vector<std::string> &_v);

		void put_str_to_win(WINDOW *_win, int _y, int _x, std::string &_msg);
		void clear_win_line(WINDOW *_win,int begin,int lines);
		void get_str_to_win(WINDOW *_win,std::string &_out);

	//private:
	public:
		WINDOW *header;
		WINDOW *output;
		WINDOW *input;
		WINDOW *flist;
};
