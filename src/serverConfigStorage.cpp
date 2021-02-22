#include <nlohmann/json.hpp>
#include "serverConfigStorage.h"

serverConfigStorage::serverConfigStorage() {
    //ctor
}

serverConfigStorage::~serverConfigStorage() {
    //dtor
}


bool serverConfigStorage::storageLoad(const std::string& storage) {
    // use json to save data
//    std::cerr << "<serverConfigStorage::storageLoad> Loading...\n";
    if(storage.size() > 0) {
        try {
            auto&& j = nlohmann::json::parse(storage);
            auto&& size = j.size();
            for(decltype(size) i=0; i<size; i++) {
                data.insert(static_cast<quickQuery>(j[i]));
            }
        }
        catch(...) {
            std::cerr << "<serverConfigStorage::storageLoad> Unknown exception.\n";
            return false;
        }
    }
//    std::cerr << "<serverConfigStorage::storageLoad> successful\n";
    return true;
}

std::string serverConfigStorage::storageSave() {
//    std::cerr << "<serverConfigStorage::storageSave> data size: " << data.size() << std::endl;
    nlohmann::json j = data;
    return j.dump();
}


std::string serverConfigStorage::Identifier() const {
    return "local_storage_config";
}

std::set<quickQuery> serverConfigStorage::getLoadedRecord() const {
    return data;
}

void serverConfigStorage::addItem(const quickQuery& a) {
    data.insert(a);
}

void serverConfigStorage::delItem(const quickQuery& a) {
    data.erase(a);
}


std::set<quickQuery>& serverConfigStorage::getDataRef() {
    return data;
}
