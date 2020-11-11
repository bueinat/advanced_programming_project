

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
  std::map<std::string, std::vector<double>> m_series;
  std::map<double, double> m_time;
  std::vector<std::string> m_headers;

public:
  TimeSeries(const char *CSVfileName) {
    std::string line;
    ifstream fid(CSVfileName);

    if (fid.is_open()) {
      getline(fid, line);

      int time_index = 0;
      m_headers = parser_tools::split(line, ",");

      for (std::vector<string>::iterator it = m_headers.begin();
           it != m_headers.end(); ++it)
        m_series.insert(std::make_pair(*it, std::vector<double>()));

      std::vector<double> splitted_line;
      while (getline(fid, line)) {
        splitted_line = parser_tools::split_to_double(line, ",");
        m_time.insert(std::make_pair(splitted_line[0], time_index));
        time_index++;
        for (int i = 0; i < splitted_line.size(); i++) {
          m_series.at(m_headers[i]).push_back(splitted_line[i]);
          // m_time[splitted_line[0]] = i;
          // std::cout << splitted_line[0] << ": " << i << std::endl;
        }
      }
      fid.close();
    }

    else
      cout << "Unable to open file";
  }

  const std::string get_time_name() { return m_headers[0]; }

  const double get_value(std::string column, double time) {
    return m_series[column][m_time[time]];
  }

  const void print_series();

};

#endif /* TIMESERIES_H_ */
