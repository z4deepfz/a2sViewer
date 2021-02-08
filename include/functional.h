#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <boost/asio.hpp>
#include <string>

boost::asio::ip::udp::endpoint genUdpEndpoint(const char* addr, uint16_t port);

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

#endif // FUNCTIONAL_H
