#include <iostream>
#include <vector>
#include "StringParsingTools.h"


    std::vector<std::string> parser_tools::split(const std::string &s,
                                const std::string &delimiter) {
    std::vector<std::string> splitted;
    std::string scpy = s;
    int pos = 0;
    while ((pos = scpy.find(delimiter)) != std::string::npos) {
        splitted.push_back(scpy.substr(0, pos));
        scpy.erase(0, pos + delimiter.length());
    }
    return splitted;
    }

    std::vector<double> parser_tools::split_to_double(const std::string &s,
                                const std::string &delimiter) {
    std::vector<double> splitted;
    std::string scpy = s;
    int pos = 0;
    while ((pos = scpy.find(delimiter)) != std::string::npos) {
        splitted.push_back(std::stod(scpy.substr(0, pos)));
        scpy.erase(0, pos + delimiter.length());
    }
    return splitted;
    }
