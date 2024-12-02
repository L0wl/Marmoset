#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#pragma once
#include <map>
#include <string>
#include <vector>

class CommandlineParser {
private:
    std::map<std::string, std::string> arguments;
    std::vector<std::string> requiredArguments;
    std::map<std::string, std::string> shortToLongArguments;
    bool parserValid = false;

public:
    void setRequiredArguments(std::vector<std::string> requiredArgs);
    void setShortArgumentConvensions(std::map<std::string, std::string> shortToLongArgs);
    void parse(int argc, char* argv[]);
    bool isValid() const;
    void validateArguments();
    std::string getArgument(const std::string& key) const;
    bool hasArgument(const std::string& key) const;
    void printAllArguments() const;
};

#endif //COMMANDLINEPARSER_H
