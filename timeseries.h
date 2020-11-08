

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include "StringParsingTools.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class TimeSeries {

public:
  TimeSeries(const char *CSVfileName) {
    std::string line;
    ifstream fid(CSVfileName);
    // parser_tools ps;

    if (fid.is_open()) {
      getline(fid, line);
      auto headers = parser_tools::split(line, ",");
      std::map<std::string, std::vector<double>> series;
      // std::map<int, std::string> indices;
      for (int i = 0; i < headers.size(); i++) {
        // indices.insert(std::make_pair(i, hea))
        series.insert(std::make_pair(headers[i], std::vector<double>()));
      }

      std::vector<double> splitted_line;
      while (getline(fid, line)) {
        splitted_line = parser_tools::split_to_double(line, ",");
        for (int i = 0; i < splitted_line.size(); i++)
          series.at(headers[i]).push_back(splitted_line[i]);
      }
      for (int i = 0; i < series.at(headers[0]).size(); i++) {
        std::cout << headers[0] << ": " << series.at(headers[0])[i] << ", "
                  << headers[1] << ": " << series.at(headers[1])[i]
                  << std::endl;
      }

      fid.close();
    }

    else
      cout << "Unable to open file";
  }
};

#endif /* TIMESERIES_H_ */
