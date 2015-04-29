#include "ocean.h"
#include "func.h"
#include "boat.h"
#include "sky.h"
#include <cstdlib>
using namespace std;

extern float iGlobalTime;

int xs, ys;

#define noiseWidth 256
#define noiseHeight 256

float noise[noiseWidth][noiseHeight]; //the noise array

void generateNoise() {
    for (int x = 0; x < noiseWidth; x++) {
        for (int y = 0; y < noiseHeight; y++) {
            noise[x][y] = (rand() % 32768) / 32768.0;
        }
    }
}

void initOcean( void ) {
    generateNoise();
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
    int u = abs(floor(uv[0])), v = abs(floor(uv[1]));
    u = clamp(u, 0, noiseWidth);
    v = clamp(v, 0, noiseHeight);
    
    Vec3 color;
    color[0] = color[1] = color[2] = noise[u][v]; // Noise
    // color[0] = color[1] = color[2] = turbulence(u, v, 8); // Turbulence
    return color;
    
}

// Noise functions, distinguished by variable types

float Noise( Vec3 x )
{
    Vec3 p = floor(x);
    Vec3 f = fract(x);
    f = f*f*3.0-f*f*f*2.0;
    //	Vec3 f2 = f*f; f = f*f2*(10.0-15.0*f+6.0*f2);
    
    //Vec2 uv = Vec2(p.x,p.y)+Vec2(37.0,17.0)*p.z;
    Vec2 uv = Vec2(p.x+f.x,p.y+f.y);
    
    // hardware interpolation lacks precision
    Vec3 rg = mix( mix(
                       texture2D(floor(uv)+Vec2(0.5,0.5)),
                       texture2D(floor(uv)+Vec2(1.5,0.5)),
                       fract(f.x) ),
                  mix(
                      texture2D(floor(uv)+Vec2(0.5,1.5)),
                      texture2D(floor(uv)+Vec2(1.5,1.5)),
                      fract(f.x) ),
                  fract(f.y) );
    
    return mix( rg.y, rg.x, f.z );
}

float Waves( Vec3 pos, int octaves )
{
    pos *= .2*Vec3(1,1,1);
    
    float f = 0.0;
    
    // need to do the octaves from large to small, otherwise things don't line up
    // (because I rotate by 45 degrees on each octave)
    pos += iGlobalTime*Vec3(0,.1,.1);
    for ( int i=0; i < octaves; i++ )
    {
        Vec3 tmp = pos;
        pos.x = (tmp.y + tmp.z)/sqrt(2.0);
        pos.y = (tmp.z - tmp.y)/sqrt(2.0);
        pos.z = tmp.x * sqrt(2.0);
        
        f  = f*2.0+abs(Noise(pos)-.5)*2.0;
        pos *= 2.0;
    }
    f /= exp2(float(octaves));
    
    return (.5-f)*1.0;
}

float OceanDistanceField( Vec3 pos )
{
    return pos.y - Waves(pos, 6);
}

float OceanDistanceFieldDetail( Vec3 pos )
{
    return pos.y - Waves(pos, 8);
}

Vec3 OceanNormal( Vec3 pos )
{
    Vec3 norm;
    Vec3 dX = Vec3(.01*length(pos),0,0);
    Vec3 dY = Vec3(0,.01*length(pos),0);
    Vec3 dZ = Vec3(0,0,.01*length(pos));
    
    // normal is the negative gradient of surface
    norm[0] = OceanDistanceFieldDetail( pos+dX )-OceanDistanceFieldDetail( pos-dX );
    norm[1] = OceanDistanceFieldDetail( pos+dY )-OceanDistanceFieldDetail( pos-dY );
    norm[2] = OceanDistanceFieldDetail( pos+dZ )-OceanDistanceFieldDetail( pos-dZ );
    
    return normalize(norm);
}

float TraceOcean( Vec3 pos, Vec3 ray )
{
    float h = 1.0;
    float t = 0.0;
    for ( int i=0; i < 150; i++ )
    {
        if ( h < .01 || t > 100.0 )
            break;
        h = OceanDistanceField( pos+t*ray );
        t += h;
    }
    
    if ( h > .1 )
        return 0.0;
    
    return t;
}


Vec3 ShadeOcean( Vec3 pos, Vec3 ray, Vec2 fragCoord )
{
    Vec3 norm = OceanNormal(pos);
    float ndotr = dot(ray,norm);
    
    float fresnel = pow(1.0-abs(ndotr),5.0);
    
    Vec3 reflectedRay = ray-2.0*norm*ndotr;
    Vec3 refractedRay = ray+(-cos(1.33*acos(-ndotr))-ndotr)*norm;
    refractedRay = normalize(refractedRay);
    
    const float crackFudge = .0;
    
    // reflection
    Vec3 reflection = Sky(reflectedRay);
    float t=TraceBoat( pos-crackFudge*reflectedRay, reflectedRay );
    
    if ( t > 0.0 )
    {
        reflection = ShadeBoat( pos+(t-crackFudge)*reflectedRay, reflectedRay );
    }
    
    // refraction
    t=TraceBoat( pos-crackFudge*refractedRay, refractedRay );
    
    Vec3 col = Vec3(0.1,0.3,0.7); // under-sea colour
    if ( t > 0.0 )
    {
        col = mix( col, ShadeBoat( pos+(t-crackFudge)*refractedRay, refractedRay ), exp(-t) );
    }
    
    col = mix( col, reflection, fresnel );
    
    return col;
}