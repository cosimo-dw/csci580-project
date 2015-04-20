//
//  mat.cpp
//  
//
//  Created b1 Cosimo.DW on 2/18/15.
//
//

#include "type.h"
#include <cmath>

Vec3 operator+(const Vec3& a, const Vec3& b) {
    Vec3 ret;
    ret[0] = a[0] + b[0];
    ret[1] = a[1] + b[1];
    ret[2] = a[2] + b[2];
    return ret;
}

void operator+=(Vec3& a, const Vec3& b) {
    a = a + b;
}

void operator-=(Vec3& a, const Vec3& b) {
    a = a - b;
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    Vec3 ret;
    ret[0] = a[0] - b[0];
    ret[1] = a[1] - b[1];
    ret[2] = a[2] - b[2];
    return ret;
}

Vec2 operator-(const Vec2& a, const Vec2& b) {
    Vec2 ret;
    ret[0] = a[0] - b[0];
    ret[1] = a[1] - b[1];
    return ret;
}

Vec3 operator*(const Vec3& a, const Vec3& b) {
    Vec3 ret;
    ret[0] = a[0] * b[0];
    ret[1] = a[1] * b[1];
    ret[2] = a[2] * b[2];
    return ret;
}

void operator*=(Vec3& a, const Vec3& b) {
    a = a * b;
}

Vec3 operator/(const Vec3& a, const Vec3& b) {
    Vec3 ret;
    ret[0] = a[0] / b[0];
    ret[1] = a[1] / b[1];
    ret[2] = a[2] / b[2];
    return ret;
}

Vec2 operator+(const Vec2& a, const Vec2& b) {
    Vec2 ret;
    ret[0] = a[0] + b[0];
    ret[1] = a[1] + b[1];
    return ret;
}

Vec2 operator*(const Vec2& a, const Vec2& b) {
    Vec2 ret;
    ret[0] = a[0] * b[0];
    ret[1] = a[1] * b[1];
    return ret;
}

Vec2 operator/(const Vec2& a, const Vec2& b) {
    Vec2 ret;
    ret[0] = a[0] / b[0];
    ret[1] = a[1] / b[1];
    return ret;
}

float dot(const Vec3& a, const Vec3& b){
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

Vec3 cross(const Vec3& a, const Vec3& b){
    Vec3 ret;
    ret[0] = a[1]*b[2] - a[2]*b[1];
    ret[1] = a[2]*b[0] - a[0]*b[2];
    ret[2] = a[0]*b[1] - a[1]*b[0];
    return ret;
}

float length(const Vec3& v){
    return sqrt(dot(v,v));
}

Vec3 normalize(const Vec3& v) {
    return v / length(v);
}

Vec3 operator*(float s, const Vec3& v) {
    Vec3 ret;
    ret[0] = s * v[0];
    ret[1] = s * v[1];
    ret[2] = s * v[2];
    return ret;
}

Vec3 operator*(const Vec3& v, float s) {
    return s * v;
}

void operator*=(Vec3& v, float s) {
    v = v * s;
}

Vec3 operator/(const Vec3& v, float s) {
    return (1.0f/s) * v;
}

// Vec3 operator*(const Mat& A, const Vec3& v) {
//     Vec3 ret;
//     float d = A[3][0]*v[0] + A[3][1]*v[1] + A[3][2]*v[2] + A[3][3];
//     ret[0] = (A[0][0]*v[0] + A[0][1]*v[1] + A[0][2]*v[2] + A[0][3])/d;
//     ret[1] = (A[1][0]*v[0] + A[1][1]*v[1] + A[1][2]*v[2] + A[1][3])/d;
//     ret[2] = (A[2][0]*v[0] + A[2][1]*v[1] + A[2][2]*v[2] + A[2][3])/d;
//     return ret;
// }

// void operator*=(G2Coord v, Mat m) {
//     (m * Vec3(v)).dump(v);
// }

// void Mat::normalize() {
//     data[0][3] = 0;
//     data[1][3] = 0;
//     data[2][3] = 0;
//     float l = 1.0f/sqrt(data[0][0]*data[0][0] +
//                         data[0][1]*data[0][1] +
//                         data[0][2]*data[0][2]);
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             data[i][j] *= l;
//         }
//     }
// }