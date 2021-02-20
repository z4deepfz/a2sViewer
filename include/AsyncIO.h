#ifndef ASYNCIO_H
#define ASYNCIO_H

#include <array>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "functional.h"


void SendAndReceive(
    std::function<void(bool)> notify_func,
    const std::string& msg,
    std::string* recv_buffer,
    const char* addr,
    const uint16_t port);


void HTTPSendAndReceive(
    std::function<void(bool)> notify_func,
    const std::string& msg,
    std::string* recv_buffer,
    const char* addr,
    const uint16_t port);

namespace global_cnt {
    extern int asyncIO;
}

template<class ConT>
class AsyncIO: public std::enable_shared_from_this<AsyncIO<ConT>>
{

public:

    using ExternalBufferType = std::string;
    using Endpoint_t = typename ConT::endpoint;
    using Notifier_t = std::function<void(bool)>;
    using Socket_t = typename ConT::socket;
    using Context_t = boost::asio::io_context;
    using ddl_timer_t = boost::asio::deadline_timer;

protected:

    Context_t context;
    Socket_t socket;
    Notifier_t notify_func;
    ExternalBufferType* pBuffer;
    Endpoint_t endpoint;
    ddl_timer_t timer;

public:

    AsyncIO(Notifier_t notify_func,
            ExternalBufferType* buffer,
            Endpoint_t endpoint):
                socket(context),
                notify_func(notify_func),
                pBuffer(buffer),
                endpoint(endpoint),
                timer(context) {

        socket.open(ConT::v4());
        socket.connect(endpoint);
        std::cerr << "<AsyncIO> Constructed. Current object count: " << ++::global_cnt::asyncIO << std::endl;
    }

    ~AsyncIO() {
        std::cerr << "<AsyncIO> Destructed. Current object count: " << --::global_cnt::asyncIO << std::endl;
    }

    void run(const std::string& request) {
//        std::cerr << "<AsyncIO::run> run.\n";
        auto pThis = this->shared_from_this();
        // set socket params
        socket.async_send(boost::asio::buffer(request),
                          boost::bind(sendHandler,
                                      this,
                                      pThis,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
        // set timeout timer
        timer.expires_from_now(boost::posix_time::seconds(3));
        timer.async_wait(boost::bind(timeoutHandler, this, boost::asio::placeholders::error));
        // 一个简单粗暴的方法，把阻塞的函数放到线程中调用
        // 反正std::shared_ptr过去了，应该不会发生提早析构的问题
        // context.run()执行完后线程应该会自动析构
        std::thread t(
            [this](){
                context.run();
            }
        );
        t.detach();
    }

protected:

    void sendHandler(std::shared_ptr<AsyncIO> pThis,
                     const boost::system::error_code& error,
                     std::size_t bytes_transferred) {
//            std::cerr << "<AsyncIO::sendHandler> send handler called: ";
            // start receive
            if(!error) {
//                std::cerr << "success.\n";
                auto buffer = boost::asio::buffer(*pBuffer, pBuffer->size());
                auto handler = boost::bind(receiveHandler,
                                           this,
                                           pThis,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred);
                socket.async_receive(buffer, handler);
            }
            else {
//                std::cerr << "failed.\n";
            }
    }

    void receiveHandler(std::shared_ptr<AsyncIO> pThis,
                        const boost::system::error_code& error,
                        std::size_t bytes_transferred) {
            // call notify_func
            // and return. shared_ptr would destruct itself. Genius
//            std::cerr << "<AsyncIO::receiveHandler> receive handler called: ";
            if(!error) {
//                std::cerr << "success.\n";
                pBuffer->resize(bytes_transferred);
                notify_func(true);
                timer.cancel();
                context.stop();
            }
            else {
                notify_func(false);
//                std::cerr << "failed.\n";
            }
    }

    void timeoutHandler(const boost::system::error_code& error) {
        // if timeout, stop the context directly.
        // All actions would be stopped and handler ###wouldn't return###
        // so never forget close the socket to let all the handlers return
        // so that std::shared_ptr could destruct the object correctly
        std::cerr << "<AsyncIO::timeoutHandler> timeout handler called: ";
        if(!error) {
            std::cerr << "operation timed out!\n";
            // important: close the socket
            // because the handlers has a std::shared_ptr to this object
            socket.close();
            context.stop();
        }
        else {
            std::cerr << "normal exit\n";
        }
    }


};

#endif // ASYNCIO_H
