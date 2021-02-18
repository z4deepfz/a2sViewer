#ifndef BASIC_RESPONSE_H
#define BASIC_RESPONSE_H

#include <iostream>

// protocal parser is OOP now. may move to GP one day.

class basic_response
{

public:

    basic_response(); // ctor

    template<typename T>
    basic_response(const T* arr) { // template ctor
        Parse(arr);
    }

    virtual ~basic_response(); // dtor

    template<typename T>
    void Parse(const T* arr) {
        parse(reinterpret_cast<const uint8_t*>(arr));
        // reinterpret the array to uint8(aka byte) array
        // caller should take care of it. Guarantee it's a correct protocal response
    }

    // implement it. different protocla has different request str
    virtual std::string getRequestStr() const = 0;

protected:

    // implement this function in derived class
    virtual void parse(const uint8_t* arr) = 0;

public: // fields

    // keep fields public so that anyone can get access to them
    // can use custom typedef

};

#endif // BASIC_RESPONSE_H
