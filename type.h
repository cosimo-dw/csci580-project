//
//  type.h
//  
//
//  Created by Cosimo.DW on 2/18/15.
//
//
#pragma once

struct Vec3{
    union{
        float data[3];
        struct{
            float x;
            float y;
            float z;
        };
    };
    Vec3(float x = 0, float y = 0, float z = 0) {data[0] = x; data[1] = y; data[2] = z;}

    float& operator[] (int idx) {return data[idx];}
    const float& operator[] (int idx) const {return data[idx];}
};

struct Vec2{
    union{
        float data[2];
        struct{
            float x;
            float y;
        };
    };
    Vec2(float x = 0, float y = 0) {data[0] = x; data[1] = y;}
    Vec2(const Vec3& v) {x = v.x; y = v.y;}

    float& operator[] (int idx) {return data[idx];}
    const float& operator[] (int idx) const {return data[idx];}
};

float dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);
float length(const Vec3& v);
Vec3 normalize(const Vec3& v);

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec2 operator+(const Vec2& a, const Vec2& b);

Vec3 operator-(const Vec3& a, const Vec3& b);
Vec2 operator-(const Vec2& a, const Vec2& b);

Vec3 operator*(const Vec3& a, const Vec3& b);
Vec2 operator*(const Vec2& a, const Vec2& b);

Vec3 operator/(const Vec3& a, const Vec3& b);
Vec2 operator/(const Vec2& a, const Vec2& b);

void operator+=(Vec3& a, const Vec3& b);
void operator-=(Vec3& a, const Vec3& b);
void operator*=(Vec3& a, const Vec3& b);

Vec3 operator*(float s, const Vec3& v);
Vec3 operator*(const Vec3& v, float s);
void operator*=(Vec3& v, float s);

Vec3 operator/(const Vec3& v, float s);

