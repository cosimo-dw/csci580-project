#include "boat.h"
#include "func.h"
#include "ocean.h"
#include "sky.h"
using namespace std;

extern Vec2 iResolution;

Vec3 boatRight, boatUp, boatForward;
Vec3 boatPosition;

void initBoat( void )
{
    Vec3 samples[5];
    
    samples[0] = Vec3(0,0, 0);
    samples[1] = Vec3(0,0, .5);
    samples[2] = Vec3(0,0,-.5);
    samples[3] = Vec3( .5,0,0);
    samples[4] = Vec3(-.5,0,0);
    
    samples[0][1] = Waves(samples[0], 2);
    samples[1][1] = Waves(samples[1], 2);
    samples[2][1] = Waves(samples[2], 2);
    samples[3][1] = Waves(samples[3], 2);
    samples[4][1] = Waves(samples[4], 2);
    
    boatPosition = (samples[0]+samples[1]+samples[2]+samples[3]+samples[4])/5.0;
    
    boatRight = samples[3]-samples[4];
    boatForward = samples[1]-samples[2];
    boatUp = normalize(cross(boatForward,boatRight));
    boatRight = normalize(cross(boatUp,boatForward));
    boatForward = normalize(boatForward);
    
    boatPosition += .0*boatUp;
}

Vec3 BoatToWorld( Vec3 dir )
{
    return dir.x*boatRight+dir.y*boatUp+dir.z*boatForward;
}

Vec3 WorldToBoat( Vec3 dir )
{
    return Vec3( dot(dir,boatRight), dot(dir,boatUp), dot(dir,boatForward) );
}

float TraceBoat( Vec3 pos, Vec3 ray )
{
    Vec3 c = boatPosition;
    float r = 1.0;
    
    c -= pos;
    
    float t = dot(c,ray);
    
    float p = length(c-t*ray);
    if ( p > r )
        return 0.0;
    
    return t-sqrt(r*r-p*p);
}


Vec3 ShadeBoat( Vec3 pos, Vec3 ray )
{
    pos -= boatPosition;
    Vec3 norm = normalize(pos);
    pos = WorldToBoat(pos);
    
    Vec3 lightDir = normalize(Vec3(-2,3,1));
    float ndotl = dot(norm,lightDir);
    
    // allow some light bleed, as if it's subsurface scattering through plastic
    Vec3 light = smoothstep(-.1,1.0,ndotl)*Vec3(1.0,.9,.8)+Vec3(.06,.1,.1);
    
    // anti-alias the albedo
    float aa = 4.0/iResolution.x;
    
    //Vec3 albedo = ((fract(pos.x)-.5)*(fract(pos.y)-.5)*(fract(pos.z)-.5) < 0.0) ? Vec3(0) : Vec3(1);
    Vec3 albedo = Vec3(1,.01,0);
    albedo = mix( Vec3(.04,.04,.04), albedo, smoothstep( .25-aa, .25, abs(pos.y) ) );
    albedo = mix( mix( Vec3(1,1,1), Vec3(.04,.04,.04), smoothstep(-aa*4.0,aa*4.0,cos(atan(pos.x/pos.z)*6.0)) ), albedo, smoothstep( .2-aa*1.5, .2, abs(pos.y) ) );
    albedo = mix( Vec3(.04,.04,.04), albedo, smoothstep( .05-aa*1.0, .05, abs(abs(pos.y)-.6) ) );
    albedo = mix( Vec3(1,.8,.08), albedo, smoothstep( .05-aa*1.0, .05, abs(abs(pos.y)-.65) ) );
    
    Vec3 col = albedo*light;
    
    // specular
    Vec3 h = normalize(lightDir-ray);
    float s = pow(max(0.0f,dot(norm,h)),100.0)*100.0/32.0;
    
    Vec3 specular = s*Vec3(1,1,1);
    
    Vec3 rr = reflect(ray,norm);
    specular += mix( Vec3(0,.04,.04), Sky(rr), smoothstep( -.1, .1, rr.y ) );
    
    float ndotr = dot(norm,ray);
    float fresnel = pow(1.0-abs(ndotr),5.0);
    fresnel = mix( .001, 1.0, fresnel );
    
    col = mix( col, specular, fresnel );
    
    return col;
}