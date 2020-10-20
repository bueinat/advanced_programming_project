/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
    float mu = 0;
    for (int i = 0; i < size; i++)
        mu += x[i];
    
	return mu;
}

float var(float* x, int size){
    float mu = avg(x, size);
    float sqsum = 0;
    for (int i = 0; i < size; i++)
        sqsum += x[i] * x[i];
    float var = sqsum / size - mu * mu;
	return var;
}

float cov(float* x, float* y, int size){
    float mu_x = avg(x, size);
    float mu_y = avg(y, size);
    float covarr[size] = {};
    for (int i = 0; i < size; i++)
        covarr[i] = (x[i] - mu_x) * (y[i] - mu_y);
	return avg(covarr, size);
}

float pearson(float* x, float* y, int size){
    float cov_xy = cov(x, y, size);
    float std_x = sqrt(var(x, size));
    float std_y = sqrt(var(y, size));
	return cov_xy / std_x / std_y;
}

Line linear_reg(Point** points, int size){

	return Line(0,0);
}

float dev(Point p,Point** points, int size){
	return 0;
}

float dev(Point p,Line l){
	return 0;
}




