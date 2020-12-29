#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_
#include "anomaly_detection_util.h"

class Circle {
public:
    Point center;
    float radius;
    Circle(Point c, float r) : center(c), radius(r) {}
};

float distance(const Point &a, const Point &b);

bool isPointInsideCircle(const Circle &circle, const Point &point);

Circle circleFrom(const Point &a, const Point &b, const Point &c);

Circle circleFrom(const Point &a, const Point &b);

// The function checks if a circle contains the given points:
bool isCircleValid(const Circle &center, const vector<Point> &points);

Circle minCircleTrivial(vector<Point> &pointsVector);

Circle findMinCircleAux(vector<Point> &pointsVector, vector<Point> rVector,
                        int size);

vector<Point> createPointsVector(Point **points, size_t size);

// Main function:
Circle findMinCircle(Point **points, size_t size);

#endif /* MINCIRCLE_H_ */
