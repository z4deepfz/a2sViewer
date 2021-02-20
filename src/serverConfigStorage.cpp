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
    nlohmann::json j;
    try {
        if(j.parse(storage) == false) {
            return false;
        }
        auto&& size = j.size();
        for(decltype(size) i=0; i<size; i++) {
            data.insert(static_cast<quickQuery>(j[i]));
        }
    }
    catch(...) {
        return false;
    }
    return true;
}

std::string serverConfigStorage::storageSave() {
    if(data.size() > 0) {
        nlohmann::json j = data;
        return j;
    }
    else {
        return "";
    }
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

