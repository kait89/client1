//============================================================================
// Name        : client1.cpp
// Author      : kait
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "client1.h"

#include <iostream>
//#include <string>
#include <chrono>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

Client::Client(int _id){
    cd = -1;
    operr = OPERROR::OK;
    cstatus = STATUS::DISCONNECTED;
    id = _id;
    std::cout << "client started id=" << id << std::endl;
}

Client::~Client(){
    if (cstatus == STATUS::CONNECTED)
        disconnect();
}

bool Client::connectto(const std::string& ip, int port){
    if ((cd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        operr = OPERROR::SOCK;
        return false;
    }

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = inet_addr(/*INADDR_LOOPBACK*/"127.0.0.1");

    if (connect(cd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1){
        operr = OPERROR::CONN;
        disconnect();
        std::cout << strerror(errno) << std::endl;
        return false;
    }

    cstatus = STATUS::CONNECTED;
    return true;
}

void Client::disconnect(){
    cstatus = STATUS::DISCONNECTED;
    close(cd);
}

bool Client::makerequest(){
    if (cstatus == STATUS::DISCONNECTED){
        return false;
    }

    std::string str = "hello" + std::to_string(id);
    const char* buffer = str.c_str();
    if (write(cd, buffer, str.size()) <= 0){
        operr = OPERROR::WRITE;
        disconnect();
        return false;
    }
    std::cout << "id " << id << ", reqv: " << buffer << std::endl;

    char ans[10];
    int len;
    while ((len = read(cd, &ans, sizeof(ans)/sizeof(char))) > 0){
    	std::cout << "id " << id << ", ans: " << ans << std::endl;
    }
    std::cout << "len " << len << std::endl;
    if (len == -1){
        std::cout << strerror(errno) << std::endl;
        operr = OPERROR::WRITE;
        disconnect();
        return false;
    }

    return true;
}

Client::OPERROR Client::operror(){
    OPERROR err = operr;
    operr = OPERROR::OK;
    return err;
}



