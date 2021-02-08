#include "AsyncIO.h"
#include "functional.h"

void SendAndReceive(std::function<void()> notify_func,
                    const std::string& msg,
                    std::string* buffer,
                    const char* addr,
                    const uint16_t port) {
    auto endpoint = genUdpEndpoint(addr, port);
    auto p = std::make_shared<AsyncIO>(notify_func, buffer, endpoint);
    p->run(msg);
}

/*
void HTTPSendAndReceive(std::function<void()> notify_func,
                        const std::string& msg,
                        std::string* buffer,
                        const char* addr,
                        const uint16_t port) {
    auto endpoint = genUdpEndpoint(addr, port);
    auto p = std::make_shared<AsyncIO>(notify_func, buffer, endpoint);
    p->run(msg);
} */


// constructor for udp
AsyncIO::AsyncIO(std::function<void()> notify_func,
                 ExternalBufferType* buffer,
                 boost::asio::ip::udp::endpoint endpoint):
    socket(context),
    notify_func(notify_func),
    pBuffer(buffer),
    endpoint(endpoint) {
    // open socket and print message
    socket.open(boost::asio::ip::udp::v4());
    socket.connect(endpoint);
    std::cerr << "<AsyncIO> Constructed.\n";
}



// destructor
AsyncIO::~AsyncIO() {
    std::cerr << "<AsyncIO> Destructed.\n";
}


// handler
void AsyncIO::sendHandler(std::shared_ptr<AsyncIO> pThis,
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
    // and do nothing
}


// handler
void AsyncIO::receiveHandler(std::shared_ptr<AsyncIO> pThis,
                             const boost::system::error_code& error,
                             std::size_t bytes_transferred) {
    // call notify_func
    // and return. shared_ptr would destruct itself. Genius
    std::cerr << "<AsyncIO::receiveHandler> receive handler called.\n";
    pBuffer->resize(bytes_transferred);
    notify_func();
    return;
}


// when called this function, you can just release the top std::shared_ptr. It would dectrut automatically
void AsyncIO::run(const std::string& msg) {
    std::cerr << "<AsyncIO::run> run.\n";
    auto pThis = shared_from_this();
    socket.async_send(boost::asio::buffer(msg),
                      boost::bind(sendHandler,
                                  this,
                                  pThis,
                                  boost::asio::placeholders::error,
                                  boost::asio::placeholders::bytes_transferred));
    context.run();
    std::cerr << "<AsyncIO::run> context run.\n";
}
