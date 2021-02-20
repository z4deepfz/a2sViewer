#include "AsyncIO.h"
#include "functional.h"

// well, 仅有一处类型不同的两个函数在C++里显得很傻叉......日后把他们合并成模板函数

void SendAndReceive(std::function<void(bool)> notify_func,
                    const std::string& msg,
                    std::string* buffer,
                    const char* addr,
                    const uint16_t port) {
    auto endpoint = genUdpEndpoint(addr, port);
    auto p = std::make_shared<AsyncIO<boost::asio::ip::udp>>(notify_func, buffer, endpoint);
    p->run(msg);
//    std::cerr << "<TopFrame::queryInfo> function returns.\n";
}


void HTTPSendAndReceive(std::function<void(bool)> notify_func,
                        const std::string& msg,
                        std::string* buffer,
                        const char* addr,
                        const uint16_t port) {
    auto endpoint = genEndpoint<boost::asio::ip::tcp>(addr, port);
    auto p = std::make_shared<AsyncIO<boost::asio::ip::tcp>>(notify_func, buffer, endpoint);
    p->run(msg);
    return;
}
int global_cnt::asyncIO = 0;
