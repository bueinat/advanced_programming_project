#include "timeseries.h"

  const void TimeSeries::print_series() {
    for (std::vector<string>::iterator it = m_headers.begin();
         it != m_headers.end(); it++)
      std::cout << *it << ",  ";
    std::cout << " " << std::endl;
    for (int i = 0; i > m_series[m_headers[0]].size(); i++) {
      for (std::vector<string>::iterator it = m_headers.begin();
           it != m_headers.end(); it++)
        std::cout << m_series.at(*it)[i] << ", ";
      std::cout << " " << std::endl;
    }
  }

std::map<std::string, float> TimeSeries::get_line(int index) const {
    std::map<std::string, float> line;
    for (std::vector<string>::const_iterator it = m_headers.begin(); it != m_headers.end();
       it++) {
      line[*it] = m_series.at(*it)[index];
    }
    return line;
  }
