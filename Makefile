
SERVER-CPP=arm-linux-gnueabi-g++
CLIENT-CPP=g++

all: server client

server: server.cpp conntest.h Makefile
	$(SERVER-CPP) -o server -ggdb -Og -Wall -static server.cpp

client: client.cpp conntest.h Makefile
	$(CLIENT-CPP) -o client -ggdb -Og -Wall -static client.cpp
