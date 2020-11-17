
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
  std::string highly_correlated;
  float correlation = 0;
  float max_correlation = 0;

  for (std::vector<string>::iterator it = headers.begin(); it != headers.end();
       it++) {
    max_correlation = 0;
    for (std::vector<string>::iterator jt = headers.begin();
         jt != headers.end(); jt++) {
      if (it->compare(*jt) == 0)
        continue;

      correlation = pearson(ts.get_column(*it), ts.get_column(*jt));
      if (fabs(correlation) > max_correlation) {
        max_correlation = fabs(correlation);
        highly_correlated = *jt;
      }
    }
    if (max_correlation > 0.9)
      add_to_cf(ts, *it, highly_correlated);
  }
}

void SimpleAnomalyDetector::add_to_cf(const TimeSeries &ts,
                                      const std::string &f1,
                                      const std::string &f2) {
  string keyname;
  correlatedFeatures *cfs = new correlatedFeatures();
  cfs->feature1 = f1;
  cfs->feature2 = f2;
  cfs->corrlation = pearson(ts.get_column(f1), ts.get_column(f2));
  // std::cout << f1 << ", " << f2 << ": " << cfs->corrlation << ", " << std::endl;

  // f1, f2 to points array
  std::vector<Point> points;
  for (int i = 0; i < ts.get_length(); i++) {
    points.push_back(Point(ts.get_column(f1)[i], ts.get_column(f2)[i]));
  }
  cfs->lin_reg = linear_reg(points);
  // std::cout << cfs->feature1 + "-" + cfs->feature2 << ": " << cfs->lin_reg.a
  //           << ", " << cfs->lin_reg.b << std::endl;

  cfs->threshold = find_max_dist(ts, points, cfs->lin_reg) * 1.1;
  // std::cout << "threshold: " << cfs->threshold << std::endl;
  keyname = cfs->feature2 + "-" + cfs->feature1;
  if (cfmap.count(keyname) == 0) {
    cf.push_back(*cfs);
    keyname = cfs->feature1 + "-" + cfs->feature2;
    cfmap.insert(std::make_pair(keyname, &cf.back()));
  }
  delete cfs;
}

double SimpleAnomalyDetector::find_max_dist(const TimeSeries &ts,
                                            const std::vector<Point> &points,
                                            Line line) {
  float max_dev = 0;
  float cdev = 0;
  for (int i = 0; i < ts.get_length(); i++) {
    cdev = dev(points[i], line);
    if (cdev > max_dev)
      max_dev = cdev;
  }
  return max_dev;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
  auto headers = ts.get_headers();
  std::map<std::string, float> ts_line;
  Line l;
  float pointdev = 0;
  correlatedFeatures *itercf;
  std::vector<AnomalyReport> ar;
  std::string description;
  // Point *p;

  for (int i = 0; i < ts.get_length(); i++) {
    ts_line = ts.get_line(i);
    for (std::vector<correlatedFeatures>::iterator itercf = cf.begin();
         itercf != cf.end(); itercf++) {
      // if (cfmap.count(*it) > 0) {
      // itercf = cfmap.at(*it);
      l = itercf->lin_reg;
      // p = &l.fpoint(ts_line.at(itercf->feature1));
      pointdev = dev(ts_line.at(itercf->feature1), ts_line.at(itercf->feature2), l);
      // std::cout << pointdev <<std::endl;
      if (pointdev > itercf->threshold) {
        description = itercf->feature1 + "-" + itercf->feature2;
        ar.push_back(AnomalyReport(description, i + 1));
        // std::cout << (i + 1) << ": " << description << std::endl;
      }
      // }
    }
  }

  return ar;
}
