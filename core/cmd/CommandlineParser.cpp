#include "CommandlineParser.h"
#include <stdexcept>
#include <iostream>

void CommandlineParser::setRequiredArguments(std::vector<std::string> requiredArgs) {
    requiredArguments = requiredArgs;
}

void CommandlineParser::setShortArgumentConvensions(std::map<std::string, std::string> shortToLongArgs) {
    shortToLongArguments = shortToLongArgs;
}

void CommandlineParser::parse(int argc, char* argv[]) {
    parserValid = (argc == requiredArguments.size());
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        std::string param = (i + 1 < argc) ? argv[i + 1] : "";

        if (shortToLongArguments.find(arg) != shortToLongArguments.end()) {
            arg = shortToLongArguments[arg];
        }

        if (arg.substr(0, 2) == "--" && !param.empty() && param[0] != '-') {
            arguments[arg.substr(2)] = param;
            i++;
        }
    }

    validateArguments();
}

bool CommandlineParser::isValid() const {
    return parserValid;
}

void CommandlineParser::validateArguments() {
    for (const auto& requiredArg : requiredArguments) {
        if (arguments.find(requiredArg) == arguments.end()) {
            parserValid = false;
            return;
        }
    }
    parserValid = true;
}

std::string CommandlineParser::getArgument(const std::string& key) const {
    if (parserValid) {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        throw std::runtime_error("Unknown argument passed: " + key);
    }
    return {};
}

bool CommandlineParser::hasArgument(const std::string& key) const {
    return arguments.find(key) != arguments.end();
}

void CommandlineParser::printAllArguments() const {
    std::cout << "Parsed Arguments: " << std::endl;
    for (const auto& arg : arguments) {
        std::cout << arg.first << ": " << arg.second << std::endl;
    }
}
