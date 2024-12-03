#include <iostream>
#include "core/cmd/CommandlineParser.h"
#include "core/archive/Archive.h"

int main(int argc, char* argv[]) {
    CommandlineParser parser;
    parser.setRequiredArguments({"archive", "output"});
    parser.setShortArgumentConvensions({{"-a", "--archive"}, {"-o", "--output"}});
    try {
        parser.parse(argc, argv);
        if (parser.isValid()) {
            const auto archive = new Archive(parser.getArgument("archive"));
           std::cout << "\n"
            << "Target file: " << parser.getArgument("archive") << "\n"
            << "Blocks encoded: " << archive->getNumFiles() << "\n";
        }
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}