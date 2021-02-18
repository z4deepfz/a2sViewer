#include "a2s_info_l4d2.h"
#include "ByteReader.h"
#include <iostream>

namespace L4D2 {

const std::array<uint8_t,25> a2s_info_Response::request = {
    0xFF, 0xFF, 0xFF, 0xFF, 0x54,
    0x53, 0x6F, 0x75, 0x72, 0x63,
    0x65, 0x20, 0x45, 0x6E, 0x67,
    0x69, 0x6E, 0x65, 0x20, 0x51,
    0x75, 0x65, 0x72, 0x79, 0x00
};

a2s_info_Response::a2s_info_Response()
{
    //ctor
}

a2s_info_Response::~a2s_info_Response()
{
    //dtor
}

void a2s_info_Response::parse(const uint8_t* raw) {
    //std::cerr << "<a2s_info_Response::_parse> Start parsing...\n";
    ByteReader r(raw);
    r.Ignore(5);
    protocol = r.Byte();
    name = r.String();
    map = r.String();
    folder = r.String();
    game = r.String();
    ID = r.Dword();
    players = r.Byte();
    max_players = r.Byte();
    bots = r.Byte();
    server_type = r.Byte();
    environment = r.Byte();
    visibility = r.Byte();
    vac = r.Byte();
    version = r.String();
    EDF = r.Byte();
    if(EDF & 0x80) {
        port = r.Dword();
    }
    if(EDF & 0x10) {
        steam_id = r.Ull();
    }
    if(EDF & 0x40) {
        stv_port = r.Dword();
        stv_name = r.String();
    }
    if(EDF & 0x20) {
        keywords = r.String();
    }
    if(EDF & 0x01) {
        game_id = r.Ull();
    }
}

}

