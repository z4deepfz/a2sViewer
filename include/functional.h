#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <boost/asio.hpp>

boost::asio::ip::udp::endpoint genUdpEndpoint(const char* addr, uint16_t port);

#endif // FUNCTIONAL_H
