#include "Archive.h"
#include <fstream>
#include "../bytestream/ByteStream.h"
#include "../limpelziv/Decompressor.h"

Archive::Archive(const std::string& filepath) {
    if (!filepath.empty()) {
        loadFromFile(filepath);
    } else {
        delete this;
    }
}

std::shared_ptr<ArchiveFile> Archive::getFile(const std::string& name) const {
    auto it = files.find(name);
    if (it == files.end()) {
        return it->second;
    }
    return nullptr;
}

int Archive::getNumFiles() const {
    return files.size();
}

bool Archive::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    ByteStream stream(buffer);

    file.close();

    while (!stream.isEmpty()) {
        auto archiveFile = std::make_shared<ArchiveFile>();
        archiveFile->name = stream.readCString();
        archiveFile->type = stream.readCString();
        archiveFile->isCompressed = (bool)(stream.readUint32() & 1);
        archiveFile->compressedSize = stream.readUint32();
        archiveFile->decompressedSize = stream.readUint32();
        std::vector<uint8_t> compressedData;
        stream.readBytes(compressedData, archiveFile->compressedSize);
        if (archiveFile->isCompressed) {
            archiveFile->data = Decompressor::decompress(compressedData, archiveFile->decompressedSize);
        } else {
            archiveFile->data = std::move(compressedData);
        }
        files[archiveFile->name] = archiveFile;
    }
    return true;
}
