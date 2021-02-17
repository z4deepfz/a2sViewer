#include "QuickQuerySubscribe.h"
#include "local_res.h"
#include <iostream>


QuickQuerySubscribe::QuickQuerySubscribe() {
    //ctor
    buffer.resize(1024);
}

QuickQuerySubscribe::~QuickQuerySubscribe() {
    //dtor
}

std::vector<quickQuery> QuickQuerySubscribe::Parse(const std::string& str) {
    nlohmann::json j = nlohmann::json::parse(str);
    std::vector<quickQuery> ret;
    auto&& size = j.size();
    for(size_t i=0; i<size; i++) {
        ret.push_back(j[i]);
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
