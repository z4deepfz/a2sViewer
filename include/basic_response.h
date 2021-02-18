#ifndef BASIC_RESPONSE_H
#define BASIC_RESPONSE_H

#include <iostream>

// protocal parser is OOP now. may move to GP one day.
// drived class should implement:
//   1. parse(const uint8_t*)
//   2. getRequestStr() const
class basic_response
{

public:

    basic_response(); // ctor

    template<typename T>
    void load(const T* arr) { // template ctor
        loc_arr = reinterpret_cast<const uint8_t*>(arr);
    }

    virtual ~basic_response(); // dtor

    template<typename T>
    bool Parse(const T* arr) {
        // if parse from a array, load it first, then parse it
        load(arr);
        return parse(loc_arr);
        // reinterpret the array to uint8(aka byte) array
        // caller should take care of it. Guarantee it's a correct protocal response
    }

    // implement it. different protocla has different request str
    virtual std::string getRequestStr() const = 0;

protected:

    const uint8_t* loc_arr;
    // implement this function in derived class
    virtual bool parse(const uint8_t* arr) = 0;

public: // fields

    // keep fields public so that anyone can get access to them
    // can use custom typedef

};

#endif // BASIC_RESPONSE_H
