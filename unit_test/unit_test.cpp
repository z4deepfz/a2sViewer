#include <cstdint>
#include <iostream>
#include "a2s_info_l4d2.h"
#include "unit_test.h"

namespace unit_test {


void test_convert_from_array()
{
    std::cout << "======== BEGIN TEST: convert struct from an array ========\n";
    L4D2::a2s_info_Response exp = detail::gen_with_example_case();
    detail::show_attributes(exp);
    std::cout << "========= END TEST: convert struct from an array =========\n";
}


}


namespace unit_test::detail {

/**
头1		\ff\ff\ff\ff
头2		I
协议		\11
服务器名	\e4\bd\a0\e5\a6\88\e6\b2\a1\e4\ba\86\00
地图名	c2m1_highway\00
文件夹	left4dead2\00
游戏名	Left 4 Dead 2\00
steamID &\02
玩家数	\00
最大玩家数	\06
机器人数量	\00
服务器类型	d
环境		l
可见性	\00
VAC		\01
游戏版本	2.2.1.1\00
EDF		\b1
端口号	%[
steamID	\06\d8:l\07@@\01
关键词	coop,empty,hidden,secure\00
GameID	&\02\00\00\00\00\00\00
*/

uint8_t a2s_info_example[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0x49,
    0x11,
    0xE4, 0xBD, 0xA0, 0xE5, 0xA6, 0x88, 0xE6, 0xB2, 0xA1, 0xE4, 0xBA, 0x86, 0x00,
    0x63, 0x32, 0x6D, 0x31, 0x5F, 0x68, 0x69, 0x67, 0x68, 0x77, 0x61, 0x79, 0x00,
    0x6C, 0x65, 0x66, 0x74, 0x34, 0x64, 0x65, 0x61, 0x64, 0x32, 0x00,
    0x4C, 0x65, 0x66, 0x74, 0x20, 0x34, 0x20, 0x44, 0x65, 0x61, 0x64, 0x20, 0x32, 0x00,
    0x26, 0x02, // ID
    0x00, // players
    0x06, // max players
    0x00, // bots
    0x64, // server_type
    0x6C, // env
    0x00, // visibility
    0x01, // vac
    0x32, 0x2E, 0x32, 0x2E, 0x31, 0x2E, 0x31, 0x00, // version
    0xB1, // EDF
    0x25, 0x5B, // port
    0x06, 0xD8, 0x3A, 0x6C, 0x07, 0x40, 0x40, 0x01, // steamID
    // keywords
    0x63, 0x6F, 0x6F, 0x70, 0x2C, 0x65, 0x6D, 0x70, 0x74, 0x79, 0x2C, 0x68, 0x69, 0x64, 0x64, 0x65, 0x6E, 0x2C, 0x73, 0x65, 0x63, 0x75, 0x72, 0x65, 0x00,
    0x26, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // game id
};

::L4D2::a2s_info_Response gen_with_example_case()
{
    ::L4D2::a2s_info_Response ans(a2s_info_example);
    return ans;
}

void show_attributes(const ::L4D2::a2s_info_Response& a)
{
    std::cout << "Protocal: " << (int)a.protocol << '\n'
          << "Server Name: " << a.name << '\n'
          << "Current Map: " << a.map << '\n'
          << "Map Folder: " << a.folder << '\n'
          << "Game: " << a.game << '\n'
          << "SteamApp ID: " << a.ID << '\n'
          << "Current Players: " << (int)a.players << '\n'
          << "Max Players: " << (int)a.max_players << '\n'
          << "Current Bots: " << (int)a.bots << '\n'
          << "Server Type: " << (char)a.server_type << '\n'
          << "Server Platform: " << (char)a.environment << '\n'
          << "Visiable: " << (a.visibility?"True":"False") << '\n'
          << "Vac: " << (a.vac?"Enable":"Disable") << '\n'
          << "Game Version: " << a.version << '\n'
          << "Port: " << a.port << '\n'
          << "Server Steam ID: " << a.steam_id << '\n'
          << "KeyWords: " << a.keywords << '\n'
          << "Game ID(long): " << a.game_id << '\n';
}




}


