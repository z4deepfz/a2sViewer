#include <cstring>
#include <windows.h>
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
    //return ntohs(readType<uint16_t>());
}

uint64_t ByteReader::Ull() {
    uint64_t res;
    byte* p = reinterpret_cast<byte*>(&res);
    for(int i=7; i>=0; i--) {
        p[i] = *(pNow++);
    }
    pNow += 8;
    return res;
}

// TODO (Ryan#1#): don't know it's big endian or little endian
float ByteReader::Float() {
//    float res = *reinterpret_cast<const float*>(pNow);
//    pNow += 4;
//    return res;
    return readType<float>();
}

uint32_t ByteReader::Uint() {
    return readType<uint32_t>();
}

void ByteReader::Ignore(size_t length) {
    pNow += length;
}

void ByteReader::reset() {
    pNow = raw;
}

bool ByteReader::Ignore(const char* arr) {
    auto&& len = strlen(arr);
    const uint8_t* p = reinterpret_cast<const uint8_t*>(arr);
    decltype(pNow) tmp = pNow;
    for(size_t i=0; i<len; i++,pNow++) {
        if(*pNow != p[i]) {
            pNow = tmp;
            return false;
        }
    }
    //pNow++; // move pointer to next byte
    return true;
}
