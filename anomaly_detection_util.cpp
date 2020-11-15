/*
 * animaly_detection_util.cpp
 *
 * Author: Einat Buznach 314905860
 */

#include "anomaly_detection_util.h"
#include <math.h>
#include <vector>

float avg(float *x, int size) {
  float mu = 0;
  for (int i = 0; i < size; i++)
    mu += x[i];

  return mu / size;
}

float avg(const std::vector<float> &x) {
  float mu = 0;
  for (int i = 0; i < x.size(); i++)
    mu += x[i];

  return mu / x.size();
}

float var(float *x, int size) {
  float mu = avg(x, size);
  float sqsum = 0;
  for (int i = 0; i < size; i++)
    sqsum += x[i] * x[i];
  float var = sqsum / size - mu * mu;
  return var;
}

float var(const std::vector<float> &x) {
  float mu = avg(x);
  float sqsum = 0;
  for (int i = 0; i < x.size(); i++)
    sqsum += x[i] * x[i];
  float var = sqsum / x.size() - mu * mu;
  return var;
}

float cov(float *x, float *y, int size) {
  float mu_x = avg(x, size);
  float mu_y = avg(y, size);
  float covarr[size] = {};
  for (int i = 0; i < size; i++)
    covarr[i] = (x[i] - mu_x) * (y[i] - mu_y);
  return avg(covarr, size);
}

float cov(const std::vector<float> &x, const std::vector<float> &y) {
  float mu_x = avg(x);
  float mu_y = avg(y);
  std::vector<float> covarr;
  for (int i = 0; i < x.size(); i++)
    covarr.push_back((x.at(i) - mu_x) * (y.at(i) - mu_y));
  return avg(covarr);
}

float pearson(float *x, float *y, int size) {
  float cov_xy = cov(x, y, size);
  float std_x = sqrt(var(x, size));
  float std_y = sqrt(var(y, size));
  return cov_xy / std_x / std_y;
}

float pearson(const std::vector<float> &x, const std::vector<float> &y) {
  float cov_xy = cov(x, y);
  float std_x = sqrt(var(x));
  float std_y = sqrt(var(y));
  return cov_xy / std_x / std_y;
}

Line linear_reg(Point **points, int size) {
  float x[size] = {};
  float y[size] = {};
  for (int i = 0; i < size; i++) {
    x[i] = points[i]->x;
    y[i] = points[i]->y;
  }

  float a = cov(x, y, size) / var(x, size);
  float b = avg(y, size) - a * avg(x, size);
  return *(new Line(a, b));
}

Line linear_reg(const std::vector<Point> &points) {
  std::vector<float> x;
  std::vector<float> y;
  for (int i = 0; i < points.size(); i++) {
    x.push_back(points[i].x);
    y.push_back(points[i].y);
  }

  float a = cov(x, y) / var(x);
  float b = avg(y) - a * avg(x);
  return *(new Line(a, b));
}

float dev(Point p, const std::vector<Point> &points) {
  return dev(p, linear_reg(points));
}

float dev(Point p, Line l) { return fabs(l.f(p.x) - p.y); }

std::vector<std::string> parsing_tools::split(const std::string &s,
                                              const std::string &delimiter) {
  std::vector<std::string> splitted;
  std::string scpy = s;
  int pos = 0;
  while ((pos = scpy.find(delimiter)) != std::string::npos) {
    splitted.push_back(scpy.substr(0, pos));
    scpy.erase(0, pos + delimiter.length());
  }
  splitted.push_back(scpy);
  return splitted;
}

std::vector<float> parsing_tools::split_to_float(const std::string &s,
                                                 const std::string &delimiter) {
  std::vector<float> splitted;
  std::string scpy = s;
  int pos = 0;
  while ((pos = scpy.find(delimiter)) != std::string::npos) {
    splitted.push_back(std::stod(scpy.substr(0, pos)));
    scpy.erase(0, pos + delimiter.length());
  }
  splitted.push_back(std::stod(scpy));
  return splitted;
}
