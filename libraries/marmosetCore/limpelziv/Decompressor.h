#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#pragma once

#include <vector>
#include <cstdint>
#include <string>

class Decompressor {
public:
    static std::vector<uint8_t> decompress(const std::vector<uint8_t>& input, size_t outputSize);
};

#endif //DECOMPRESSOR_H
