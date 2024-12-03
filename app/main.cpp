#include <iostream>
#include "cmd/CommandlineParser.h"
#include <Archive.h>

int main(int argc, char* argv[]) {
    CommandlineParser parser;
    parser.setRequiredArguments({"archive", "output"});
    parser.setShortArgumentConvensions({{"-a", "--archive"}, {"-o", "--output"}});
    try {
        parser.parse(argc, argv);
        if (parser.isValid()) {
            const auto archive = new Archive(parser.getArgument("archive"));
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}