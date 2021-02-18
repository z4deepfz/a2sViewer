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


void HTTPSendAndReceive(
    std::function<void()> notify_func,
    const std::string& msg,
    std::string* recv_buffer,
    const char* addr,
    const uint16_t port);


template<class ConT>
class AsyncIO: public std::enable_shared_from_this<AsyncIO<ConT>>
{

public:

    using ExternalBufferType = std::string;
    using Endpoint_t = typename ConT::endpoint;
    using Notifier_t = std::function<void()>;
    using Socket_t = typename ConT::socket;
    using Context_t = boost::asio::io_context;

protected:

    Context_t context;
    Socket_t socket;
    Notifier_t notify_func;
    ExternalBufferType* pBuffer;
    Endpoint_t endpoint;

public:

    AsyncIO(Notifier_t notify_func,
            ExternalBufferType* buffer,
            Endpoint_t endpoint):
                socket(context),
                notify_func(notify_func),
                pBuffer(buffer),
                endpoint(endpoint) {

        socket.open(ConT::v4());
        socket.connect(endpoint);
        std::cerr << "<AsyncIO> Constructed.\n";
    }

    ~AsyncIO() {
        std::cerr << "<AsyncIO> Destructed.\n";
    }

    void run(const std::string& request) {
        std::cerr << "<AsyncIO::run> run.\n";
        auto pThis = this->shared_from_this();
        socket.async_send(boost::asio::buffer(request),
                          boost::bind(sendHandler,
                                      this,
                                      pThis,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
        std::cerr << "<AsyncIO::run> context run...";
// TODO (z4deepfz#1#): io_context本身没有多线程机制，为它分配一个线程

        context.run();
        std::cerr << "successfully\n";
    }

protected:

    void sendHandler(std::shared_ptr<AsyncIO> pThis,
                     const boost::system::error_code& error,
                     std::size_t bytes_transferred) {
            std::cerr << "<AsyncIO::sendHandler> send handler called.\n";
            // start receive
            auto buffer = boost::asio::buffer(*pBuffer, pBuffer->size());
            auto handler = boost::bind(receiveHandler,
                                       this,
                                       pThis,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred);
            socket.async_receive(buffer, handler);
            std::cerr << "<AsyncIO::sendHandler> leaving send handler.\n";
            // and do nothing
            return;
    }

    void receiveHandler(std::shared_ptr<AsyncIO> pThis,
                        const boost::system::error_code& error,
                        std::size_t bytes_transferred) {
            // call notify_func
            // and return. shared_ptr would destruct itself. Genius
            std::cerr << "<AsyncIO::receiveHandler> receive handler called.\n";
            pBuffer->resize(bytes_transferred);
            notify_func();
            return;
    }

private:



};

#endif // ASYNCIO_H
