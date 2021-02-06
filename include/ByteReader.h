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
    uint64_t Ull();
    void Ignore(size_t length);
    void reset();

protected:
    const byte* const raw;
    const byte* pNow;

};

#endif // BYTEREADER_H
