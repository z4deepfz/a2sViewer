#ifndef QUERY_H
#define QUERY_H

/* For sync IO only */

#include <tuple>
#include <string>
#include "a2s_info_l4d2.h"

std::tuple<
    std::string,// server name
    std::string,// map name
    uint8_t,    // players
    uint8_t,    // max_players
    bool,       // vac
    std::string,// keywords
    bool
> query(const char* IP, const uint16_t port);

std::tuple<
    std::string,// server name
    std::string,// map name
    uint8_t,    // players
    uint8_t,    // max_players
    bool,       // vac
    std::string,// keywords
    bool
> getNeededAttributesFromA2sResponse(const L4D2::a2s_info_Response& response);

#endif // QUERY_H
