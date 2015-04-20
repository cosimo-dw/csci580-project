//
//  type.h
//  
//
//  Created by Cosimo.DW on 2/18/15.
//
//
#pragma once

#include "gz.h"

#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>

class Vec2{
    float data[2];
public:
    Vec2(float* vec, int len = 2) {memcpy(data,vec,sizeof(float)*len);}
    Vec2(float x = 0, float y = 0) {data[0] = x; data[1] = y;}
    
    float y() {
        return data[1];
    }

    Vec2 yy() {
        Vec2 ret;
        ret[0] = data[1];
        ret[1] = data[1];
        return ret;
    }

    Vec2 yx() {
        Vec2 ret;
        ret[0] = data[1];
        ret[1] = data[0];
        return ret;
    }

    float x() {
        return data[0];
    }

    Vec2 xy() {
        Vec2 ret;
        ret[0] = data[0];
        ret[1] = data[1];
        return ret;
    }

    Vec2 xx() {
        Vec2 ret;
        ret[0] = data[0];
        ret[1] = data[0];
        return ret;
    }

    float& operator[] (int idx) {return data[idx];}
    const float& operator[] (int idx) const {return data[idx];}
};


class Vec3{
    float data[3];
public:
    Vec3(float* vec, int len = 3) {memcpy(data,vec,sizeof(float)*len);}
    Vec3(float x = 0, float y = 0, float z = 0) {data[0] = x; data[1] = y; data[2] = z;}
    
    float y() {
        return data[1];
    }

    Vec2 yy() {
        Vec2 ret;
        ret[0] = data[1];
        ret[1] = data[1];
        return ret;
    }

    Vec3 yyy() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[1];
        ret[2] = data[1];
        return ret;
    }

    Vec3 yyx() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[1];
        ret[2] = data[0];
        return ret;
    }

    Vec3 yyz() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[1];
        ret[2] = data[2];
        return ret;
    }

    Vec2 yx() {
        Vec2 ret;
        ret[0] = data[1];
        ret[1] = data[0];
        return ret;
    }

    Vec3 yxy() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[0];
        ret[2] = data[1];
        return ret;
    }

    Vec3 yxx() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[0];
        ret[2] = data[0];
        return ret;
    }

    Vec3 yxz() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[0];
        ret[2] = data[2];
        return ret;
    }

    Vec2 yz() {
        Vec2 ret;
        ret[0] = data[1];
        ret[1] = data[2];
        return ret;
    }

    Vec3 yzy() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[2];
        ret[2] = data[1];
        return ret;
    }

    Vec3 yzx() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[2];
        ret[2] = data[0];
        return ret;
    }

    Vec3 yzz() {
        Vec3 ret;
        ret[0] = data[1];
        ret[1] = data[2];
        ret[2] = data[2];
        return ret;
    }

    float x() {
        return data[0];
    }

    Vec2 xy() {
        Vec2 ret;
        ret[0] = data[0];
        ret[1] = data[1];
        return ret;
    }

    Vec3 xyy() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[1];
        ret[2] = data[1];
        return ret;
    }

    Vec3 xyx() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[1];
        ret[2] = data[0];
        return ret;
    }

    Vec3 xyz() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[1];
        ret[2] = data[2];
        return ret;
    }

    Vec2 xx() {
        Vec2 ret;
        ret[0] = data[0];
        ret[1] = data[0];
        return ret;
    }

    Vec3 xxy() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[0];
        ret[2] = data[1];
        return ret;
    }

    Vec3 xxx() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[0];
        ret[2] = data[0];
        return ret;
    }

    Vec3 xxz() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[0];
        ret[2] = data[2];
        return ret;
    }

    Vec2 xz() {
        Vec2 ret;
        ret[0] = data[0];
        ret[1] = data[2];
        return ret;
    }

    Vec3 xzy() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[2];
        ret[2] = data[1];
        return ret;
    }

    Vec3 xzx() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[2];
        ret[2] = data[0];
        return ret;
    }

    Vec3 xzz() {
        Vec3 ret;
        ret[0] = data[0];
        ret[1] = data[2];
        ret[2] = data[2];
        return ret;
    }

    float z() {
        return data[2];
    }

    Vec2 zy() {
        Vec2 ret;
        ret[0] = data[2];
        ret[1] = data[1];
        return ret;
    }

    Vec3 zyy() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[1];
        ret[2] = data[1];
        return ret;
    }

    Vec3 zyx() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[1];
        ret[2] = data[0];
        return ret;
    }

    Vec3 zyz() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[1];
        ret[2] = data[2];
        return ret;
    }

    Vec2 zx() {
        Vec2 ret;
        ret[0] = data[2];
        ret[1] = data[0];
        return ret;
    }

    Vec3 zxy() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[0];
        ret[2] = data[1];
        return ret;
    }

    Vec3 zxx() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[0];
        ret[2] = data[0];
        return ret;
    }

    Vec3 zxz() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[0];
        ret[2] = data[2];
        return ret;
    }

    Vec2 zz() {
        Vec2 ret;
        ret[0] = data[2];
        ret[1] = data[2];
        return ret;
    }

    Vec3 zzy() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[2];
        ret[2] = data[1];
        return ret;
    }

    Vec3 zzx() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[2];
        ret[2] = data[0];
        return ret;
    }

    Vec3 zzz() {
        Vec3 ret;
        ret[0] = data[2];
        ret[1] = data[2];
        ret[2] = data[2];
        return ret;
    }

    float& operator[] (int idx) {return data[idx];}
    const float& operator[] (int idx) const {return data[idx];}
    
};

float dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);
float length(const Vec3& v);
Vec3 normalize(const Vec3& v);

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);

void operator+=(Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
void operator-=(Vec3& a, const Vec3& b);

Vec3 operator*(const Vec3& a, const Vec3& b);
void operator*=(Vec3& a, const Vec3& b);
Vec2 operator*(const Vec2& a, const Vec2& b);

Vec3 operator/(const Vec3& a, const Vec3& b);
Vec2 operator/(const Vec2& a, const Vec2& b);


Vec3 operator*(float s, const Vec3& v);
Vec3 operator*(const Vec3& v, float s);
void operator*=(Vec3& v, float s);
Vec3 operator/(const Vec3& v, float s);

