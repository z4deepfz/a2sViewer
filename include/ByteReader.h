#include <string>
#include <cstdint>

#ifndef BYTEREADER_H
#define BYTEREADER_H

class ByteReader {

public:
    using byte = uint8_t;

public:
    template<typename T>
    ByteReader(const T* input): raw(reinterpret_cast<const byte*>(input)) {
        pNow = raw;
    }
    uint8_t Byte();
    std::string String();
    uint16_t Dword();
    uint32_t Uint();
    uint64_t Ull();
    float Float();


    void Ignore(size_t length);
    bool Ignore(const char* spec_arr);
    void reset();

protected:
    const byte* const raw;
    const byte* pNow;

protected:
    template<typename T>
    T readType() {
        const T* p = reinterpret_cast<const T*>(pNow);
        T val = *p;
        p++;
        pNow = reinterpret_cast<decltype(pNow)>(pNow);
        return val;
    }

};

#endif // BYTEREADER_H
