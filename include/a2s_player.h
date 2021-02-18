#ifndef A2S_PLAYER_H
#define A2S_PLAYER_H

#include <iostream>
#include <vector>
#include "basic_response.h"


class a2s_player : public basic_response
{

public:

    a2s_player();
    virtual ~a2s_player();

    virtual std::string getRequestStr() const override;

public:

    uint8_t player_count;
    std::vector<std::string> name;
    std::vector<int> score;
    std::vector<float> time;

protected:

    virtual bool parse(const uint8_t* arr) override;

};

#endif // A2S_PLAYER_H
