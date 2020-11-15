
#include "SimpleAnomalyDetector.h"
#include <vector>

SimpleAnomalyDetector::SimpleAnomalyDetector() {
  // TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
  // TODO Auto-generated destructor stub
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
  auto headers = ts.get_headers();
  // std::string time = ts.get_time_name();
  std::string highly_correlated;
  float correlation = 0;
  float max_correlation = 0;
  std::vector<float> fstcol;
  std::vector<float> seccol;

  for (std::vector<string>::iterator it = headers.begin(); it != headers.end();
       it++) {
    max_correlation = 0;
    for (std::vector<string>::iterator jt = headers.begin();
         jt != headers.end(); jt++) {
      if (it->compare(*jt) == 0)
        continue;

        // std::cout << *it << ", " << *jt << std::endl;
        // vec_to_arr(ts.get_column(*it));
        fstcol = ts.get_column(*it);
        seccol = ts.get_column(*jt);
        correlation = pearson(fstcol, seccol);
        if (fabs(correlation) > max_correlation) {
          max_correlation = fabs(correlation);
          highly_correlated = *jt;
        }
      }
      if (max_correlation > 0.9)
        add_to_cf(ts, *it, highly_correlated);
    }
  }

void SimpleAnomalyDetector::add_to_cf(const TimeSeries &ts, const std::string &f1,
               const std::string &f2) {
  correlatedFeatures *cfs = new correlatedFeatures();
  cfs->feature1 = f1;
  cfs->feature2 = f2;
  cfs->corrlation = pearson(ts.get_column(f1), ts.get_column(f2));
  std::cout << f1 << ", " << f2 << ": " << cfs->corrlation << ", ";

  // f1, f2 to points array
  std::vector <Point> points;
  for (int i = 0; i < ts.get_length(); i++) {
    points.push_back(Point(ts.get_column(f1)[i], ts.get_column(f2)[i]));
  }
  cfs->lin_reg = linear_reg(points);

  cfs->threshold = find_max_dist(ts, points, cfs->lin_reg) * 1.1;
  std::cout << cfs->threshold << std::endl;
  cf.push_back(*cfs);
}

double SimpleAnomalyDetector::find_max_dist(const TimeSeries &ts, const std::vector<Point> &points, Line line) {
  float max_dist = 0;
  float dist = 0;
  for (int i = 0; i < ts.get_length(); i++) {
    dist = dev(points[i], line);
    if (dist > max_dist)
      max_dist = dist;
  }
  return max_dist;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
  return std::vector<AnomalyReport>();
  // TODO Auto-generated destructor stub
}
