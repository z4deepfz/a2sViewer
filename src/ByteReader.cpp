#include <ByteReader.h>

using byte = ByteReader::byte;

byte ByteReader::Byte() {
    uint8_t res = *pNow;
    pNow++;
    return res;
}

std::string ByteReader::String() {
    std::string res(reinterpret_cast<const char*>(pNow));
    pNow += res.size() + 1;
    return res;
}

uint16_t ByteReader::Dword() {
    uint16_t res;
    byte* p = reinterpret_cast<byte*>(&res);
    p[1] = *(pNow++);
    p[0] = *(pNow++);
    return res;
}

uint64_t ByteReader::Ull() {
    uint64_t res;
    byte* p = reinterpret_cast<byte*>(&res);
    for(int i=7; i>=0; i--) {
        p[i] = *(pNow++);
    }
    return res;
}

void ByteReader::Ignore(size_t length) {
    pNow+=length;
}

void ByteReader::reset() {
    pNow = raw;
}
