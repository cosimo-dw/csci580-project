//
//  mat.h
//  
//
//  Created by Cosimo.DW on 2/18/15.
//
//

#ifndef ____mat__
#define ____mat__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "gz.h"

class Vec2{
    float data[2];
public:
    Vec2(float* vec, int len = 3) {memcpy(data,vec,sizeof(float)*len);}
    Vec2(float x = 0, float y = 0) {data[0] = x; data[1] = y;}
    
};


class Vec3{
    float data[3];
public:
    Vec3(float* vec, int len = 3) {memcpy(data,vec,sizeof(float)*len);}
    Vec3(float x = 0, float y = 0, float z = 0) {data[0] = x; data[1] = y; data[2] = z;}
    
    void dump(float* ret, int len = D) {memcpy(ret,data,sizeof(float)*len);}
    
    Vec3 yyy() {
        Vec ret;
        ret[1] = data[0];
        ret[1] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 yyx() {
        Vec ret;
        ret[1] = data[0];
        ret[1] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 yyz() {
        Vec ret;
        ret[1] = data[0];
        ret[1] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 yxy() {
        Vec ret;
        ret[1] = data[0];
        ret[0] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 yxx() {
        Vec ret;
        ret[1] = data[0];
        ret[0] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 yxz() {
        Vec ret;
        ret[1] = data[0];
        ret[0] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 yzy() {
        Vec ret;
        ret[1] = data[0];
        ret[2] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 yzx() {
        Vec ret;
        ret[1] = data[0];
        ret[2] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 yzz() {
        Vec ret;
        ret[1] = data[0];
        ret[2] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 xyy() {
        Vec ret;
        ret[0] = data[0];
        ret[1] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 xyx() {
        Vec ret;
        ret[0] = data[0];
        ret[1] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 xyz() {
        Vec ret;
        ret[0] = data[0];
        ret[1] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 xxy() {
        Vec ret;
        ret[0] = data[0];
        ret[0] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 xxx() {
        Vec ret;
        ret[0] = data[0];
        ret[0] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 xxz() {
        Vec ret;
        ret[0] = data[0];
        ret[0] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 xzy() {
        Vec ret;
        ret[0] = data[0];
        ret[2] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 xzx() {
        Vec ret;
        ret[0] = data[0];
        ret[2] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 xzz() {
        Vec ret;
        ret[0] = data[0];
        ret[2] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 zyy() {
        Vec ret;
        ret[2] = data[0];
        ret[1] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 zyx() {
        Vec ret;
        ret[2] = data[0];
        ret[1] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 zyz() {
        Vec ret;
        ret[2] = data[0];
        ret[1] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 zxy() {
        Vec ret;
        ret[2] = data[0];
        ret[0] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 zxx() {
        Vec ret;
        ret[2] = data[0];
        ret[0] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 zxz() {
        Vec ret;
        ret[2] = data[0];
        ret[0] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    Vec3 zzy() {
        Vec ret;
        ret[2] = data[0];
        ret[2] = data[1];
        ret[1] = data[2];
        return ret;
    }
    
    Vec3 zzx() {
        Vec ret;
        ret[2] = data[0];
        ret[2] = data[1];
        ret[0] = data[2];
        return ret;
    }
    
    Vec3 zzz() {
        Vec ret;
        ret[2] = data[0];
        ret[2] = data[1];
        ret[2] = data[2];
        return ret;
    }
    
    
    float& operator[] (int idx) {return data[idx];}
    const float& operator[] (int idx) const {return data[idx];}
    
};

class Mat{
    GzMatrix data;
public:
    Mat() {}
    Mat(GzMatrix mat) {memcpy(data,mat,sizeof(GzMatrix));}
    
    void dump(GzMatrix ret) {memcpy(ret,data,sizeof(GzMatrix));}
    
    const float* operator[] (int idx) const {return data[idx];}
    
    void normalize();
};

float dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);
float length() const;
Vec3& normalize();

Vec3 operator+(const Vec3& a, const Vec3& b);
void operator+=(Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, const Vec3& b);

Vec3 operator*(float s, const Vec3& v);
Vec3 operator*(const Vec3& v, float s);
Vec3 operator/(const Vec3& v, float s);

Vec3 operator*(const Mat& a, const Vec3& b);

void operator*=(GzCoord v, Mat m);

void zero(GzMatrix mat);

void eye(GzMatrix mat);

#endif /* defined(____mat__) */
