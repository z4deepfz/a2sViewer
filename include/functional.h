#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <boost/asio.hpp>
#include <string>

boost::asio::ip::udp::endpoint genUdpEndpoint(const char* addr, uint16_t port);

namespace functional::detail {
    bool isIP(const char* str);
}

template<typename T>
std::string convertByteToHexString(const T& byteArr) {
    std::string ans;
    char buf[16];
    for(auto i: byteArr) {
        uint8_t b = i;
        sprintf(buf, "0x%02X ", b);
        ans += buf;
    }
    return ans;
}

template<class ConT>
typename ConT::endpoint genEndpoint(const char* addr, uint16_t port)
{
    using endpoint_t = typename ConT::endpoint;
    using resolver_t = typename ConT::resolver;
    using query_t = typename resolver_t::query;
    using context_t = boost::asio::io_context;

    if(functional::detail::isIP(addr)) {
        endpoint_t endpoint(boost::asio::ip::address::from_string(addr), port);
        return endpoint;
    }
    else {
        context_t context;
        resolver_t resolver(context);
        query_t query(addr, std::to_string(port).c_str());
        auto endpoint = resolver.resolve(query)->endpoint();
        return endpoint;
    }
}

#endif // FUNCTIONAL_H
