all:
	g++ -std=c++11 -I ../ send.cpp ../order.cpp -lnanomsg -ljsoncpp -o send
	
	g++ -std=c++11 receive.cpp -lnanomsg -lpthread -lglog -o receive