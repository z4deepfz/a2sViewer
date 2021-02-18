#ifndef UTIL_H
#define UTIL_H

#include <nlohmann/json.hpp>
// This head file includes some public struct or other resources

struct quickQuery {
    std::string name;
    std::string addr;
    uint16_t port;
};

void to_json(nlohmann::json& j, const quickQuery& p);
void from_json(const nlohmann::json& j, quickQuery& p);



#endif // UTIL_H


