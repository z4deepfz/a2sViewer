#include "QuickQuerySubscribe.h"
#include "local_res.h"

QuickQuerySubscribe::QuickQuerySubscribe() {
    //ctor
}

QuickQuerySubscribe::~QuickQuerySubscribe() {
    //dtor
}

std::vector<quickQuery> QuickQuerySubscribe::Parse(const std::string& str) {
    nlohmann::json j = nlohmann::json::parse(str);
    auto&& arr = j["list"];
    std::vector<quickQuery> ret;
    for(auto&& i: arr) {
        arr.push_back(i);
    }
    return ret;
}

std::vector<quickQuery> QuickQuerySubscribe::Parse() {
    return Parse(buffer);
}


std::string* QuickQuerySubscribe::getBufferPointer() {
    return &buffer;
}

std::string QuickQuerySubscribe::getRequestStr() const {
    return local_res::sub_req;
}
