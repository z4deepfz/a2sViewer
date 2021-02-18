#ifndef A2S_INFO_L4D2_H
#define A2S_INFO_L4D2_H

#include <cstdint>
#include <string>
#include <array>
#include "basic_response.h"

namespace L4D2 {

class a2s_info_Response: public basic_response {

public:

    using byte = uint8_t;
    using dword = uint16_t;
    using ull = uint64_t;
    static const std::array<uint8_t,25> request;

public:

    a2s_info_Response();
    ~a2s_info_Response();

    // construct class from byte array
    template<typename T> a2s_info_Response(const T* raw): basic_response(raw) { }

    /*// parse from any container
    template<typename T> void Parse(const T* raw) {
        parse(reinterpret_cast<const uint8_t*>(raw));
    }*/

    virtual std::string getRequestStr() const override {
        std::string ret;
        for(auto i: request) {
            ret.push_back(i);
        }
        return ret;
    }

#ifdef KEEP_NATIVE_FIELD_ORDER // use native a2s_info response order
    byte protocol;
    std::string name;
    std::string map;
    std::string folder;
    std::string game;
    dword ID; // Steam Application ID of game.
    byte players;
    byte max_players;
    byte bots;
    char server_type;
    char environment;
    byte visibility;
    byte vac;
    std::string version; // Version of the game installed on the server.
    byte EDF;
    dword port;
    ull steam_id;
    dword stv_port; // Spectator port number for SourceTV.
    std::string stv_name; // Name of the spectator server for SourceTV.
    std::string keywords;
    ull game_id;
#else // optimized structure to save more memory
    ull game_id;
    ull steam_id;
    dword ID; // Steam Application ID of game.
    dword port;
    dword stv_port; // Spectator port number for SourceTV.
    std::string name;
    std::string map;
    std::string folder;
    std::string game;
    std::string version; // Version of the game installed on the server.
    std::string stv_name; // Name of the spectator server for SourceTV.
    std::string keywords;
    char server_type;
    char environment;
    byte protocol;
    byte players;
    byte max_players;
    byte bots;
    byte visibility;
    byte vac;
    byte EDF;
#endif // KEEP_NATIVE_FIELD_ORDER

protected:

    virtual void parse(const uint8_t* raw) override;

};



}



#endif // A2S_INFO_L4D2_H
