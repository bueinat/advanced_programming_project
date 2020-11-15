#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include <algorithm>
#include <math.h>
#include <string.h>
#include <vector>

struct correlatedFeatures {
  string feature1, feature2; // names of the correlated features
  float corrlation;
  Line lin_reg;
  float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
  vector<correlatedFeatures> cf;

public:
  SimpleAnomalyDetector();
  virtual ~SimpleAnomalyDetector();

  virtual void learnNormal(const TimeSeries &ts);
  virtual vector<AnomalyReport> detect(const TimeSeries &ts);
  void add_to_cf(const TimeSeries &ts, const std::string &f1,
                 const std::string &f2);
  double find_max_dist(const TimeSeries &ts, const std::vector<Point> &points,
                       Line line);

  vector<correlatedFeatures> getNormalModel() { return cf; }
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
