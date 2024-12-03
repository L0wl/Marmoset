#include <iostream>
#include "cmd/CommandlineParser.h"
#include "core/Archive.h"

int main(int argc, char* argv[]) {

    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    std::cout << std::endl;

    CommandlineParser parser;
    parser.setRequiredArguments({"archive", "output"});
    parser.setShortArgumentConvensions({{"-a", "--archive"}, {"-o", "--output"}});
    try {
        parser.parse(argc, argv);
        if (!parser.isValid()) {
            std::cout << "Usage: " << argv[0] << " <args_here>" << "\n"
            << "\n\t\tList of arguments\t\t\n"
            << " -a --archive <path/to/archive> - Declare target file\n"
            << " -o --output <path/to/folder> - Declare output folder\n"
            << "\nExample:\n\t" << argv[0] << " -a c:/file.bin -o c:/file/mesh" << "\n";
        } else {
            std::cout << "\nAll arguments passed!\n";
            parser.printAllArguments();
            Archive* archive = new Archive(parser.getArgument("archive"));
            return 0;
            /// TODO: serialize to output
            std::string outpath = parser.getArgument("output");
            return 0;
        }
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}