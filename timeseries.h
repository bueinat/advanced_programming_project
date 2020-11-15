

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
// #include "StringParsingTools.h"
#include "anomaly_detection_util.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class TimeSeries {
  std::map<std::string, std::vector<float>> m_series;
  // std::map<float, float> m_time;
  std::vector<std::string> m_headers;

public:
  TimeSeries(const char *CSVfileName) {
    std::string line;
    ifstream fid(CSVfileName);

    if (fid.is_open()) {
      getline(fid, line);

      // int time_index = 0;
      m_headers = parsing_tools::split(line, ",");

      for (std::vector<string>::iterator it = m_headers.begin();
           it != m_headers.end(); ++it)
        m_series.insert(std::make_pair(*it, std::vector<float>()));

      std::vector<float> splitted_line;
      while (getline(fid, line)) {
        splitted_line = parsing_tools::split_to_float(line, ",");
        // m_time.insert(std::make_pair(splitted_line[0], time_index));
        // time_index++;
        for (int i = 0; i < splitted_line.size(); i++) {
          m_series.at(m_headers[i]).push_back(splitted_line[i]);
        }
      }
      fid.close();
    }

    else
      cout << "Unable to open file";
  }

  // std::string get_time_name() const { return m_headers[0]; }

  std::vector<std::string> get_headers() const { return m_headers; }

  int get_length() const { return m_series.at(m_headers[0]).size(); }

  std::vector<float> get_column(std::string column) const {
    return m_series.at(column);
    // return m_series[column].;
  }

  // std::vector<std::string> get_column() 

  const float get_value(std::string column, int index) {
    return m_series[column][index];
  }

  const void print_series();
};

#endif /* TIMESERIES_H_ */
