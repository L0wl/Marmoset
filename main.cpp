#include <iostream>
#include "core/Archive.h"

int main(int argc, char* argv[]) {
    std::string filepath = argv[1];
    std::string output = argv[2];
    bool logging = argv[3];
    Archive* Object = new Archive(filepath, logging);
    return 0;
}