#include "a2s_player.h"
#include "ByteReader.h"

a2s_player::a2s_player() {
    //ctor
}

a2s_player::~a2s_player() {
    //dtor
}

std::string a2s_player::getRequestStr() const {
    if(challenage.size() == 0) { // if no challenage request a specific string
        return "\xff\xff\xff\xff\x55\xff\xff\xff\xff";
    }
    else { // else, append challenage
        return "\xff\xff\xff\xff\x55" + challenage;
    }
}

bool a2s_player::parse(const uint8_t* arr) {
    name.clear();
    score.clear();
    time.clear();

    ByteReader read(arr);
    if(read.Ignore("\xff\xff\xff\xff\x44") == false) { // 'D' means it's a legal a2s_player response
        return false; // do nothing, or throw an exception
    }
    player_count = read.Byte();
    // read data accroding to player count
    for(uint8_t i=0; i<player_count; i++) {
        if(read.Byte() != 0) { // first byte of each player block should be 0x00
            return false;
        }
        name.push_back(read.String());
        score.push_back(read.Uint());
        time.push_back(read.Float());
    }
    return true;
}

bool a2s_player::needResponse(const std::string& str) {
    ByteReader read(reinterpret_cast<const uint8_t*>(str.c_str())); // load response to byte reader
    for(int i: str) {
        std::cerr << i << ' ';
    }
    std::cerr << std::endl;
    // if first byte == 'A'(0x41), client should replys a challenage
    if(read.Ignore("\xff\xff\xff\xff\x41")) {
        for(int i=0; i<4; i++) {
            challenage.push_back(static_cast<char>(read.Byte()));
        }
        //challenage.reverse();
        return true;
    }
    else {
        return false;
    }
}

bool a2s_player::needResponse() {
    if(pbuffer == nullptr) {
        return false;
    }
    else {
        return needResponse(*pbuffer);
    }
}


