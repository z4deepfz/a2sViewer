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

bool operator< (const quickQuery& a, const quickQuery& b)
{
//    if(a.name != b.name) {
//        return a.name < b.name;
//    }
//    else if(a.addr != b.addr) {
//        return a.addr < b.addr;
//    }
//    else {
//        return a.port < b.port;
//    }
    return a.name < b.name;
}
