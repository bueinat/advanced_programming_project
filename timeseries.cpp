#include "timeseries.h"

  const void TimeSeries::print_series() {
    for (std::vector<string>::iterator it = m_headers.begin();
         it != m_headers.end(); ++it)
      std::cout << *it << ",  ";
    std::cout << " " << std::endl;
    for (std::map<double, double>::iterator it = m_time.begin();
         it != m_time.end(); ++it) {
      std::cout << it->second << ": ";
      for (std::vector<string>::iterator itt = m_headers.begin();
           itt != m_headers.end(); ++itt)
        std::cout << m_series.at(*itt)[it->second] << ", ";
      std::cout << " " << std::endl;
    }
  }
