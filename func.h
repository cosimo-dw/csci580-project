#pragma once
#include "type.h"

float mix(float x, float y, float a);
Vec2 mix(Vec2 x, Vec2 y, float a);
Vec3 mix(Vec3 x, Vec3 y, float a);

Vec2 iVec2(const Vec3 &v);

// Vec4 mix(Vec4 x, Vec4 y, float a);

Vec2 floor(Vec2 x);
Vec3 floor(Vec3 x);

float fract(float x);
Vec3 fract(Vec3 x);

float clamp(float x, float minVal, float maxVal);

float smoothstep(float edge0, float edge1, float x);

Vec3 pow(Vec3 x, Vec3 y);

Vec3 reflect(const Vec3& I, const Vec3& N);

Vec3 texture2D(const Vec2& uv);

void generateNoise();
float smoothNoise(float u, float v);
float turbulence(float u, float v, int size);