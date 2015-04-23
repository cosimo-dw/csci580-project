//
//  type.cpp
//  
//
//  Created by Cosimo.DW on 2/18/15.
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
