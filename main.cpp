/*
 * main.cpp
 *
 *  Created on: 30 апр. 2021 г.
 *      Author: kait
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <unistd.h>
#include <iostream>
#include "client1.h"

int main(int argc, char** argv){
	std::cout << "main" << std::endl;
    int id = 1;
    if (argc > 1){
        id = std::stoi(std::string(argv[1]));
    }
    Client client1(id);
    client1.connectto();
    sleep(1);
    //this_thread::sleep_for(chrono::seconds(2));
    client1.makerequest();
    client1.disconnect();
    return 0;
}



#endif /* MAIN_CPP_ */
