#ifndef ANOMALYDETECTORUTIL_H_
#define ANOMALYDETECTORUTIL_H_

/**
 * @brief returns the mean of X
 *
 * @param x a given array
 * @param size of the array
 * @return mean of X
 */
float avg(float *x, int size);

/**
 * @brief returns the variance of X
 *
 * @param x a given array
 * @param size of the array
 * @return variance of X
 */
float var(float *x, int size);

/**
 * @brief returns the covariance of X and Y, calculated: 𝐸((𝑋 − 𝐸(𝑋))(𝑌 − 𝐸(𝑌))
 *
 * @param x first array
 * @param y second array
 * @param size of both arrays
 * @return covariance
 */
float cov(float *x, float *y, int size);

/**
 * @brief returns the Pearson correlation coefficient of X and Y
 *
 * @param x first array
 * @param y second array
 * @param size of both arrays
 * @return covariance
 */
float pearson(float *x, float *y, int size);

/**
 * @brief a class which defines a line by its slope (a) and free variable (b).
 *
 */
class Line {
public:
  const float a, b;
  Line(float a, float b) : a(a), b(b) {}
  float f(float x) { return a * x + b; }
};

/**
 * @brief a class which defindes a point in 2D sapce.
 *
 */
class Point {
public:
  const float x, y;
  Point(float x, float y) : x(x), y(y) {}
};

/**
 * @brief performs a linear regression and return s the line equation
 *
 * @param points to prform the opration on
 * @param size of points array
 * @return Line which is the result of the regression.
 */
Line linear_reg(Point **points, int size);

/**
 * @brief returns the deviation between point p and the line equation of the
 * points
 *
 * @param p single point
 * @param points to calc the deviation from
 * @param size of points array
 * @return float deviation
 */
float dev(Point p, Point **points, int size);

/**
 * @brief returns the deviation between point p and the line
 *
 * @param p a single point
 * @param l line to calc the deviation from
 * @return float
 */
float dev(Point p, Line l);

#endif
