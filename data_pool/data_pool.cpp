#include"data_pool.h"

data_pool::data_pool(int _size)
	:cap(_size)
	,pool(_size)
{
	consumer_step = 0;
	product_step = 0;
	sem_init(&consumer_sem,0,0);
	sem_init(&product_sem,0,_size);
}

bool data_pool::get_data(std::string &_out)
{
	//cout<<"debug:data_pool begin get data"<<endl;
	sem_wait(&consumer_sem);
	_out = pool[consumer_step];
	consumer_step++;
	consumer_step %= cap;
	sem_post(&product_sem);
	//cout<<"gat data succeed : "<<_out<<endl;
}

bool data_pool::put_data(std::string _in)
{
	//cout<<"debug: data_pool begin put data"<<endl;
	sem_wait(&product_sem);
	pool[product_step] = _in;
	product_step++;
	product_step %= cap;
	sem_post(&consumer_sem);
	//cout<<"put data succeed : "<<_in<<endl;
}

data_pool::~data_pool()
{
	sem_destroy(&consumer_sem);
	sem_destroy(&product_sem);
}

