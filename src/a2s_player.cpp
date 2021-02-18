#include "a2s_player.h"
#include "ByteReader.h"

a2s_player::a2s_player() {
    //ctor
}

a2s_player::~a2s_player() {
    //dtor
}

std::string a2s_player::getRequestStr() const {
    return "\xff\xff\xff\xff\x55\xff\xff\xff\xff";
}

bool a2s_player::parse(const uint8_t* arr) {
    ByteReader read(arr);
    read.Ignore("\xff\xff\xff\xff");
    if(read.Ignore("D") == false) { // 'D' means it's a legal a2s_player response
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


