#include <iostream>

#include "cmd/CommandlineParser.h"
#include "core/Archive.h"

int main(int argc, char* argv[]) {
    CommandlineParser parser;
    parser.setRequiredArguments({"archive", "output"});
    parser.setShortArgumentConvensions({{"-a", "--archive"}, {"-o", "--output"}});
    try {
        parser.parse(argc, argv);
        std::string filepath = parser.getArgument("archive");
        std::string outpath = parser.getArgument("output");

        // Archive* Object = new Archive(filepath, logging);
        // return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}