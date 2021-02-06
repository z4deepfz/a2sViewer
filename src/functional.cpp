#include <memory>
#include <boost/xpressive/xpressive.hpp>
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include "AsyncIO.h"

#define REGEXIFY_pub(new, origin)\
    const boost::xpressive::cregex new = \
    boost::xpressive::bos >> origin >> boost::xpressive::eos

#define REGEXIFY(new, origin) static REGEXIFY_pub(new, origin)

//#define USE_STATIC_REGEX

using boost::asio::ip::udp;


namespace IPregex {

#ifdef USE_STATIC_REGEX
using namespace boost::xpressive;

static const auto ipve_cell =
    (_d) |
    (range('1','9') >> _d) |
    ('1' >> _d >> _d) |
    ('2' >> ( (range('0','4')>>_d) | ('5' >> range('0','5')) ) );

static const auto ipv4_format =
    ipve_cell >> '.' >> ipve_cell >> '.' >> ipve_cell >> '.' >> ipve_cell;

//const boost::xpressive::cregex IPv4_regex = bos >> ipv4_format >> eos;

static const auto port_format =
    (range('1','9') >> repeat<1,3>(_d)) |
    (range('1','5') >> repeat<4>(_d)) |
    ("6"   >> range('0','4') >> repeat<3>(_d)) |
    ("65"  >> range('0','4') >> repeat<2>(_d)) |
    ("655" >> range('0','2') >> _d) |
    ("6553">> range('0','5'));

static const auto IPv4_withPort_format = ipv4_format >> ':' >> port_format;

REGEXIFY(IPv4_regex, ipv4_format);
REGEXIFY(Port_regex, port_format);
REGEXIFY(IPv4_withPort_regex, IPv4_withPort_format);

#else

namespace dynamic {

static const char* IPv4_regex_str = "^(((\\d{1,2})|(1\\d{2})|(2[0-4]\\d)|(25[0-5]))\\.){3}((\\d{1,2})|(1\\d{2})|(2[0-4]\\d)|(25[0-5]))$";
static boost::regex IPv4_regex(IPv4_regex_str);

}

#endif


}


static bool isIP(const char* str)
{
#ifdef USE_STATIC_REGEX
    return boost::xpressive::regex_match(str, IPregex::IPv4_regex);
#else
    return boost::regex_match(str, IPregex::dynamic::IPv4_regex);
#endif // USE_STATIC_REGEX
}

udp::endpoint genUdpEndpoint(const char* addr, uint16_t port)
{
    using boost::asio::ip::udp;
    if(isIP(addr)) {
        udp::endpoint endpoint(boost::asio::ip::address::from_string(addr), port);
        return endpoint;
    }
    else {
        boost::asio::io_context context;
        udp::resolver resolver(context);
        udp::resolver::query query(addr, std::to_string(port).c_str());
        auto endpoint = resolver.resolve(query)->endpoint();
        return endpoint;
    }
}
