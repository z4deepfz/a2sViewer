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
    //auto&& json_str = str.substr(str.find('['));
    //std::cerr << "<QuickQuerySubscribe::Parse> json: " << json_str << std::endl;
    nlohmann::json j = nlohmann::json::parse(str);
    //auto&& arr = j["list"];
    //std::cerr << "<QuickQuerySubscribe::Parse> json size: " << j.size() << std::endl;
    std::vector<quickQuery> ret;
    //for(auto&& i: j) {
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
