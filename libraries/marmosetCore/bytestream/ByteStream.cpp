#include "ByteStream.h"
#include <stdexcept>

ByteStream::ByteStream(const std::vector<uint8_t>& data): data(data), position(0) {}

bool ByteStream::isEmpty() const {
    return position >= data.size();
}

std::string ByteStream::readCString() {
    size_t start = position;
    std::string result = "";
    while (position < data.size() && data[position] != '\0') {
        result += data[position];
        position++;
    }
    position++;
    return result;
}

uint32_t ByteStream::readUint32() {
    if (position + 4 > data.size()) {
        throw std::runtime_error("ByteStream: Not enough data to read uint32");
    }
    uint32_t value;
    memcpy(&value, &data[position], sizeof(value));
    position += 4;
    return value;
}

float ByteStream::readFloat32() {
    if (position + 4 > data.size()) {
        throw std::out_of_range("ByteStream: Not enough data to read float32");
    }
    float value;
    memcpy(&value, &data[position], sizeof(float));
    position += 4;
    return value;
}

void ByteStream::readBytes(std::vector<uint8_t>& buffer, size_t size) {
    if (position + size > data.size()) {
        throw std::runtime_error("ByteStream: Not enough data to read bytes");
    }
    buffer.resize(size);
    memcpy(buffer.data(), &data[position], size);
    position += size;
}

void ByteStream::skip(size_t bytes) {
    if (position + bytes > data.size()) {
        throw std::runtime_error("ByteStream: Not enough data to skip");
    }
    position += bytes;
}
