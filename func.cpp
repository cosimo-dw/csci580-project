#include "func.h"

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