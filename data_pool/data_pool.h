#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<semaphore.h>
using namespace std;



class data_pool{
	public:
		data_pool(int _size);
		~data_pool();
		bool get_data(std::string &_out);
		bool put_data(std::string _in);

	private:
		std::vector<std::string> pool;
		int cap;//capacity
		int consumer_step;
		int product_step;

		sem_t consumer_sem;
		sem_t product_sem;
};
