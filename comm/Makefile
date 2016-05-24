ROOT=$(shell pwd)
INCLUDE=-I$(ROOT)/../lib/include
LIB=-L$(ROOT)/../lib/lib
LDFLAGS=-ljsonlib

udp_data:json_comm.cpp udp_data.cpp
	g++ -o $@ $^ $(INCLUDE) $(LIB) $(LDFLAGS)  -D_DEBUG_ 
.PHONY:clean
clean:
	rm -rf udp_data

