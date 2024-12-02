#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#pragma once

#include <cstdint>
#include <vector>
#include <string>

class ByteStream {
public:
    explicit ByteStream(const std::vector<uint8_t>& data);
    bool isEmpty() const;
    std::string readCString();
    uint32_t readUint32();
    float readFloat32();
    void readBytes(std::vector<uint8_t>& buffer, size_t size);
    void skip(size_t bytes);


private:
    std::vector<uint8_t> data;
    size_t position;
};

#endif //BYTESTREAM_H
