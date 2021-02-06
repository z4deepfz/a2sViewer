#include <boost/asio.hpp>

#include "query.h"
#include "a2s_info_l4d2.h"
#include "IO.h"
#include "unit_test.h"

std::tuple<
    std::string,// server name
    std::string,// map name
    uint8_t,    // players
    uint8_t,    // max_players
    bool,       // vac
    std::string,// keywords
    bool
> getNeededAttributesFromA2sResponse(const L4D2::a2s_info_Response& response)
{
    return std::make_tuple(
        response.name,
        response.map,
        response.players,
        response.max_players,
        response.vac==1,
        response.keywords,
        true
    );
}

std::tuple<
    std::string,// server name
    std::string,// map name
    uint8_t,    // players
    uint8_t,    // max_players
    bool,       // vac
    std::string,// keywords
    bool
> query(const char* IP, const uint16_t port)
{
    L4D2::a2s_info_Response response;
    SimpleUdpIO(&response, IP, port);
    return getNeededAttributesFromA2sResponse(response);
}

