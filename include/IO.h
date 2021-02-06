#ifndef IO_H
#define IO_H

#include <cstdint>
#include <iostream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "AsyncIO.h"

// functions decl
boost::asio::ip::udp::endpoint genUdpEndpoint(
    const char* addr,
    uint16_t port
);

// global vars decl
//extern AsyncIO<1024> io;

template<typename T>
bool SimpleUdpIO(T* Protocal, const char* addr, uint16_t port)
{
    using boost::asio::ip::udp;
    char response[1024];
    try {
        boost::asio::io_context context;
        auto request = Protocal->request;
        auto endpoint = genUdpEndpoint(addr, port);
        decltype(endpoint) loc_endpoint;

        udp::socket socket(context);
        socket.open(udp::v4());
        socket.send_to(boost::asio::buffer(request, request.size()), endpoint);

        //set_timeout(2, &socket);
        socket.receive_from(boost::asio::buffer(response, 1024), loc_endpoint);
    }
    catch(...) {
        //cancel_timeout();
        return false;
    }
    //cancel_timeout();
    Protocal->Parse(response);
    return true;
}

/*
template<typename _Proto>
void FillProtocal(_Proto* protocal)
{
    protocal->Parse(io.getBufferRef().data()); // get raw data from IO, then call parse
}

template<typename _Proto>
void CallbakFunc(std::function<void()> notify_func, _Proto* protocal,
                 const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    std::cerr << "Call back function called.\n";
    io.stop();
    FillProtocal(protocal);
    notify_func();
}

// 传递协议、通知函数、地址和端口，该函数将发起一次查询请求，并在查询成功后调用一次通知函数（会自动调用协议的Parse方法进行填充）
template<typename _Proto>
void AsyncUdpIO(std::function<void()> notify_func , _Proto* Protocal, const char* addr, uint16_t port)
{
    //using boost::asio::ip::udp;
    io.async_receive(addr, port,
                     boost::bind(CallbakFunc<_Proto>, notify_func, Protocal,
                                 boost::asio::placeholders::error,
                                 boost::asio::placeholders::bytes_transferred)
    );
    io.sync_send(Protocal->request, addr, port);
}
*/

#endif // IO_H
