//
//  mat.cpp
//  
//
//  Created by Cosimo.DW on 2/18/15.
//
//

#include "mat.h"
#include <string.h>
#include <math.h>

void zero(GzMatrix mat) {
    memset(mat,0,sizeof(GzMatrix));
}

void eye(GzMatrix mat) {
    zero(mat);
    mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1;
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
    Vec3 ret;
    ret[X] = a[X] + b[X];
    ret[Y] = a[Y] + b[Y];
    ret[Z] = a[Z] + b[Z];
    return ret;
}

void operator+=(Vec3& a, const Vec3& b) {
    a = a + b;
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    Vec3 ret;
    ret[X] = a[X] - b[X];
    ret[Y] = a[Y] - b[Y];
    ret[Z] = a[Z] - b[Z];
    return ret;
}

Vec3 operator*(const Vec3& a, const Vec3& b) {
    Vec3 ret;
    ret[X] = a[X] * b[X];
    ret[Y] = a[Y] * b[Y];
    ret[Z] = a[Z] * b[Z];
    return ret;
}

float dot(const Vec3& a, const Vec3& b){
    return a[0]*b[0] + a[1]*b[a] + a[2]*b[2];
}

Vec3 cross(const Vec3& a, const Vec3& b){
    Vec3 ret;
    ret[0] = a[1]*b[2] - a[2]*b[1];
    ret[1] = a[2]*b[0] - a[0]*b[2];
    ret[2] = a[0]*b[1] - a[1]*b[0];
    return ret;
}

float norm(const Vec3& v){
    return sqrt(dot(v,v));
}

Vec3& normalize(const Vec3& v) {
    Vec ret = v;
    float length = norm();
    ret[0] /= length;
    ret[1] /= length;
    ret[2] /= length;
    return ret;
}

Vec3 operator*(float s, const Vec3& v) {
    Vec3 ret;
    ret[X] = s * v[X];
    ret[Y] = s * v[Y];
    ret[Z] = s * v[Z];
    return ret;
}

Vec3 operator*(const Vec3& v, float s) {
    return s * v;
}

Vec3 operator/(const Vec3& v, float s) {
    return (1.0f/s) * v;
}

Vec3 operator*(const Mat& A, const Vec3& v) {
    Vec3 ret;
    float d = A[3][0]*v[0] + A[3][1]*v[1] + A[3][2]*v[2] + A[3][3];
    ret[X] = (A[0][0]*v[0] + A[0][1]*v[1] + A[0][2]*v[2] + A[0][3])/d;
    ret[Y] = (A[1][0]*v[0] + A[1][1]*v[1] + A[1][2]*v[2] + A[1][3])/d;
    ret[Z] = (A[2][0]*v[0] + A[2][1]*v[1] + A[2][2]*v[2] + A[2][3])/d;
    return ret;
}

void operator*=(GzCoord v, Mat m) {
    (m * Vec3(v)).dump(v);
}

void Mat::normalize() {
    data[0][3] = 0;
    data[1][3] = 0;
    data[2][3] = 0;
    float l = 1.0f/sqrt(data[0][0]*data[0][0] +
                        data[0][1]*data[0][1] +
                        data[0][2]*data[0][2]);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] *= l;
        }
    }
}