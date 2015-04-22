#include "func.h"
#include <iostream>

using namespace std;

float mix(float x, float y, float a)
{
    return x*(1-a) + y*a;
}

Vec2 mix(Vec2 x, Vec2 y, float a)
{
    Vec2 output;
    output[0] = x[0]*(1-a) + y[0]*a;
    output[1] = x[1]*(1-a) + y[1]*a;
    return output;
}

Vec3 mix(Vec3 x, Vec3 y, float a)
{
    Vec3 output;
    output[0] = x[0]*(1-a) + y[0]*a;
    output[1] = x[1]*(1-a) + y[1]*a;
    output[2] = x[2]*(1-a) + y[2]*a;
    return output;
}

Vec2 iVec2(const Vec3 &v) {
    Vec2 ret;
    ret[0] = int(v[0]);
    ret[1] = int(v[1]);
    return ret;
}

// Vec4 mix(Vec4 x, Vec4 y, float a)
// {
//     Vec4 output;
//     output[0][0] = x[0][0]*(1-a) + y[0][0]*a;
//     output[0][1] = x[1][1]*(1-a) + y[1][1]*a;
//     output[1][0] = x[1][0]*(1-a) + y[1][0]*a;
//     output[1][1] = x[1][1]*(1-a) + y[1][1]*a;
//     return output;
// }

Vec2 floor(Vec2 x)
{
    Vec2 output;
    output[0] = floor(x[0]);
    output[1] = floor(x[1]);
    
    return output;

}
Vec3 floor(Vec3 x)
{
    Vec3 output;
    output[0] = floor(x[0]);
    output[1] = floor(x[1]);
    output[1] = floor(x[2]);
    
    return output;
}

float fract(float x)
{
    return x-floor(x);
}

Vec3 fract(Vec3 x)
{
    Vec3 output;
    output[0] = x[0] - floor(x[0]);
    output[1] = x[1] - floor(x[1]);
    output[1] = x[2] - floor(x[2]);
    
    return output;
}

float clamp(float x, float minVal, float maxVal)
{
    float max = x;
    if(minVal > max)
    {
        max = minVal;
    }
    
    float min = maxVal;
    if(max < min)
    {
        min = max;
    }
    
    return min;
}

float smoothstep(float edge0, float edge1, float x)
{
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

Vec3 pow(Vec3 x, Vec3 y)
{
    Vec3 output;
    output[0] = pow(x[0], y[0]);
    output[1] = pow(x[1], y[1]);
    output[2] = pow(x[2], y[2]);
    
    return output;
}

Vec3 reflect(const Vec3& I, const Vec3& N) {
    return I - 2.0 * dot(N, I) * N;
}

GzColor *image;
int xs, ys;
int reset = 1;

#define IDX(x,y)    (x+(y*(xs)))

#define noiseWidth 256
#define noiseHeight 256

float noise[noiseWidth][noiseHeight]; //the noise array
bool noiseGenerated = false;

void generateNoise() {
    for (int x = 0; x < noiseWidth; x++) {
        for (int y = 0; y < noiseHeight; y++) {
            noise[x][y] = (rand() % 32768) / 32768.0;
        }
    }
    noiseGenerated = true;
}

float smoothNoise(float u, float v) {
    int left = floor(u);
    int right = ceil(u);
    int top = floor(v);
    int bottom = ceil(v);
    
    float A, B, C, D;
    A = noise[left][top];
    B = noise[right][top];
    C = noise[right][bottom];
    D = noise[left][bottom];
    
    float s = u - left;
    float t = v - top;
    
    return (s*t*C) + ((1-s)*t*D) + (s*(1-t)*B) + ((1-s)*(1-t)*A);
}

float turbulence(float u, float v, int size) {
    float value = 0.0, initialSize = size;
    while(size >= 1) {
        value += smoothNoise(u/size, v/size) * size;
        size /= 2;
    }
    
    return value/initialSize;
}


Vec3 texture2D(const Vec2& uv)
{
    if (noiseGenerated == false)
        generateNoise();
    
    int u = abs(floor(uv[0])), v = abs(floor(uv[1]));
    u = clamp(u, 0, noiseWidth);
    v = clamp(v, 0, noiseHeight);
    
    Vec3 color;
    color[0] = color[1] = color[2] = noise[u][v]; // Noise
    // color[0] = color[1] = color[2] = turbulence(u, v, 8); // Turbulence
    return color;

}