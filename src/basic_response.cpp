#include "basic_response.h"

basic_response::basic_response()
{
    //ctor
}

basic_response::~basic_response()
{
    //dtor
}

std::string* basic_response::getBufferPtr() {
    if(pbuffer == nullptr) {
        pbuffer = std::make_shared<std::string>();
    }
    pbuffer->resize(1024);
    return pbuffer.get();
}

bool basic_response::Parse() {
    if(pbuffer == nullptr) { // if internal buffer was nullptr, stop and return false
        return false;
    }
    else {
        return parse(reinterpret_cast<const uint8_t*>(pbuffer->c_str()));
    }
}
