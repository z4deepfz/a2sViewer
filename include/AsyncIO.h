#ifndef ASYNCIO_H
#define ASYNCIO_H

#include <array>
#include <iostream>
#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "functional.h"


void SendAndReceive(
    std::function<void()> notify_func,
    const std::string& msg,
    std::string* recv_buffer,
    const char* addr,
    const uint16_t port);

class AsyncIO: public std::enable_shared_from_this<AsyncIO>
{

public:

    using ExternalBufferType = std::string;

public:

    AsyncIO(std::function<void()> notify_func,
            ExternalBufferType* buffer,
            boost::asio::ip::udp::endpoint endpoint);
    ~AsyncIO();

    void run(const std::string& request);

protected:

    void sendHandler(std::shared_ptr<AsyncIO>pThis,
                     const boost::system::error_code& error,
                     std::size_t bytes_transferred);

    void receiveHandler(std::shared_ptr<AsyncIO> pThis,
                        const boost::system::error_code& error,
                        std::size_t bytes_transferred);

protected:

    boost::asio::io_context context;
    boost::asio::ip::udp::socket socket;
    std::function<void()> notify_func;
    ExternalBufferType* pBuffer;
    boost::asio::ip::udp::endpoint endpoint;

private:



};

#endif // ASYNCIO_H
