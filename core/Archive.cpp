#include "Archive.h"
#include <iostream>
#include <fstream>
#include "ByteStream.h"
#include "Decompressor.h"

Archive::Archive(const std::string& filepath, bool enableLogging) : loggingEnabled(enableLogging) {
    if (!filepath.empty()) {
        std::cout << "Opening file " << filepath << "\n";
        loadFromFile(filepath);
    } else {
        std::cout << "Path cannot be empty!\n";
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

bool Archive::loadFromFile(const std::string& filepath) {
    std::cout << "Loading file " << filepath << std::endl;
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << "\n";
        return false;
    }

    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    ByteStream stream(buffer);

    while (!stream.isEmpty()) {
        auto archiveFile = std::make_shared<ArchiveFile>();
        archiveFile->name = stream.readCString();
        archiveFile->type = stream.readCString();
        archiveFile->isCompressed = (bool)(stream.readUint32() & 1);
        archiveFile->compressedSize = stream.readUint32();
        archiveFile->decompressedSize = stream.readUint32();

        std::cout << "\n\t\t\tArchive\t\t\t\n"
        << "name: " << archiveFile->name << "\n"
        << "type: " << archiveFile->type << "\n"
        << "cf: " << (bool)(archiveFile->isCompressed) << "\n"
        << "cs: " << archiveFile->compressedSize << "\n"
        << "ds: " << archiveFile->decompressedSize << "\n"
        << "\n";

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