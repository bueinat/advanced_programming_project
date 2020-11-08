#ifndef PARSING_H_
#define PARSING_H_
#include <iostream>
#include <vector>

namespace parser_tools {

    std::vector<std::string> split(const std::string &s,
                                const std::string &delimiter);

    std::vector<double> split_to_double(const std::string &s,
                                const std::string &delimiter);
    };

#endif /* PARSING_H_ */
