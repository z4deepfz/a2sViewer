#include "util.h"

void to_json(nlohmann::json& j, const quickQuery& p) {
    j["addr"] = p.addr;
    j["name"] = p.name;
    j["port"] = p.port;
}



void from_json(const nlohmann::json& j, quickQuery& p) {
    p.addr = j["addr"];
    p.name = j["name"];
    p.port = j["port"];
}
