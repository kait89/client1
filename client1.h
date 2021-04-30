/*
 * client1.hpp
 *
 *  Created on: 30 апр. 2021 г.
 *      Author: kait
 */

#ifndef CLIENT1_H_
#define CLIENT1_H_

#include <string>


class Client{
    enum class OPERROR;
    enum class STATUS;
    int cd;
    OPERROR operr;
    STATUS cstatus;
    int id;

    enum class STATUS{
        CONNECTED,
        DISCONNECTED
    };
public:
    enum class OPERROR{
        OK,
        CONN,
        SOCK,
        BIND,
        LSTN,
        ACPT,
        READ,
        WRITE,
        INV_ADDR,
        SOPT
    };

    Client(int id = 0);
    ~Client();
    bool connectto(const std::string& ip = "127.0.0.1", int port = 20000);
    void disconnect();
    bool makerequest();

    OPERROR operror();
};




#endif /* CLIENT1_H_ */
