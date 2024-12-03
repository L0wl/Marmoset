#ifndef ARCHIVE_H
#define ARCHIVE_H

#pragma once

#include <memory>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

struct ArchiveFile {
    std::string name;
    std::string type;
    uint32_t compressedSize;
    uint32_t decompressedSize;
    bool isCompressed;
    std::vector<uint8_t> data;
};

class Archive {
public:
    explicit Archive(const std::string& filepath);
    std::shared_ptr<ArchiveFile> getFile(const std::string& name) const;
    int getNumFiles() const;

private:
    bool loadFromFile(const std::string& filepath);
    std::unordered_map<std::string, std::shared_ptr<ArchiveFile>> files;
};

#endif //ARCHIVE_H
