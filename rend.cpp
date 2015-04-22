// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
#include "rend.h"
using namespace std;

const float tau = 6.28318530717958647692;

// Gamma correction
#define GAMMA (2.2)


Vec2 iMouse(0,0);
Vec2 iResolution(512,512);
float iGlobalTime = 0;

Vec3 ToGamma( Vec3 col )
{
    // convert back into colour values, so the correct light will come out of the monitor
    return pow( col, Vec3(1.0/GAMMA,1.0/GAMMA,1.0/GAMMA) );
}

Vec3 localRay;

// Set up a camera looking at the scene.
// origin - camera is positioned relative to, and looking at, this point
// distance - how far camera is from origin
// rotation - about x & y axes, by left-hand screw rule, relative to camera looking along +z
// zoom - the relative length of the lens
void CamPolar( Vec3& pos, Vec3& ray, Vec3 origin, Vec2 rotation, float distance, float zoom, Vec2 fragCoord )
{
    // get rotation coefficients
    Vec3 c = Vec3(cos(rotation.x),cos(rotation.y),0);
    Vec3 s = Vec3(sin(rotation.x),sin(rotation.y)); // worth testing if this is faster as sin or sqrt(1.0-cos);
    //s.zw = -s.xy();
    
    // ray in view space
    Vec2 tmp = fragCoord.xy() - iResolution.xy()*.5;
    ray[0] = tmp[0];
    ray[1] = tmp[1];
    ray[2] = iResolution.y*zoom;
    ray = normalize(ray);
    localRay = ray;
    
    // rotate ray

    tmp = ray.yz()*c.xx() + ray.zy()*s.xx()*Vec2(-1,1);
    ray[1] = tmp[0];
    ray[2] = tmp[1];
    tmp = ray.xz()*c.yy() + ray.zx()*s.yy()*Vec2(1,-1);
    ray[0] = tmp[0];
    ray[2] = tmp[1];
    
    // position camera
    pos = origin - distance*Vec3(c.x*s.y,-s.x,c.x*c.y);
}


// Noise functions, distinguished by variable types

float Noise( Vec3 x )
{
    Vec3 p = floor(x);
    Vec3 f = fract(x);
    f = f*f*(3.0-2.0*f);
    //	Vec3 f2 = f*f; f = f*f2*(10.0-15.0*f+6.0*f2);
    
    Vec2 uv = (p.xy()+Vec2(37.0,17.0)*p.z) + f.xy();

    // hardware interpolation lacks precision
    Vec3 rg = mix( mix(
                       texture2D((floor(uv)+Vec2(0.5,0.5)/256.0)),
                       texture2D((floor(uv)+Vec2(1.5,0.5)/256.0)),
                       fract(uv.x) ),
                  mix(
                      texture2D((floor(uv)+Vec2(0.5,1.5)/256.0)),
                      texture2D((floor(uv)+Vec2(1.5,1.5)/256.0)),
                      fract(uv.x) ),
                  fract(uv.y) ).xyz();
    
    return mix( rg.y, rg.x, f.z );
}

Vec3 Noise( Vec2 x )
{
    return texture2D((Vec2(x.xy())+Vec2(0.5,0.5))/256.0).xyz();
}

float Waves( Vec3 pos )
{
    pos *= .2*Vec3(1,1,1);
    
    const int octaves = 6;
    float f = 0.0;
    
    // need to do the octaves from large to small, otherwise things don't line up
    // (because I rotate by 45 degrees on each octave)
    pos += iGlobalTime*Vec3(0,.1,.1);
    for ( int i=0; i < octaves; i++ )
    {
        pos = (pos.yzx() + pos.zyx()*Vec3(1,-1,1))/sqrt(2.0);
        f  = f*2.0+abs(Noise(pos)-.5)*2.0;
        pos *= 2.0;
    }
    f /= exp2(float(octaves));
    
    return (.5-f)*1.0;
}

float WavesDetail( Vec3 pos )
{
    pos *= .2*Vec3(1,1,1);
    
    const int octaves = 8;
    float f = 0.0;
    
    // need to do the octaves from large to small, otherwise things don't line up
    // (because I rotate by 45 degrees on each octave)
    pos += iGlobalTime*Vec3(0,.1,.1);
    for ( int i=0; i < octaves; i++ )
    {
        pos = (pos.yzx() + pos.zyx()*Vec3(1,-1,1))/sqrt(2.0);
        f  = f*2.0+abs(Noise(pos)-.5)*2.0;
        pos *= 2.0;
    }
    f /= exp2(float(octaves));
    
    return (.5-f)*1.0;
}

float WavesSmooth( Vec3 pos )
{
    pos *= .2*Vec3(1,1,1);
    
    const int octaves = 2;
    float f = 0.0;
    
    // need to do the octaves from large to small, otherwise things don't line up
    // (because I rotate by 45 degrees on each octave)
    pos += iGlobalTime*Vec3(0,.1,.1);
    for ( int i=0; i < octaves; i++ )
    {
        pos = (pos.yzx() + pos.zyx()*Vec3(1,-1,1))/sqrt(2.0);
        //f  = f*2.0+abs(Noise(pos).x-.5)*2.0;
        f  = f*2.0+sqrt(pow(Noise(pos)-.5,2.0)+.01)*2.0;
        pos *= 2.0;
    }
    f /= exp2(float(octaves));
    
    return (.5-f)*1.0;
}

float WaveCrests( Vec3 ipos, Vec3 fragCoord )
{
    Vec3 pos = ipos;
    pos *= .2*Vec3(1,1,1);
    
    const int octaves1 = 6;
    const int octaves2 = 16;
    float f = 0.0;
    
    // need to do the octaves from large to small, otherwise things don't line up
    // (because I rotate by 45 degrees on each octave)
    pos += iGlobalTime*Vec3(0,.1,.1);
    Vec3 pos2 = pos;
    for ( int i=0; i < octaves1; i++ )
    {
        pos = (pos.yzx() + pos.zyx()*Vec3(1,-1,1))/sqrt(2.0);
        f  = f*1.5+abs(Noise(pos)-.5)*2.0;
        pos *= 2.0;
    }
    pos = pos2 * exp2(float(octaves1));
    pos[1] = -.05*iGlobalTime;
    for ( int i=octaves1; i < octaves2; i++ )
    {
        pos = (pos.yzx() + pos.zyx()*Vec3(1,-1,1))/sqrt(2.0);
        f  = f*1.5+pow(abs(Noise(pos)-.5)*2.0,1.0);
        pos *= 2.0;
    }
    f /= 1500.0;
    
    f -= Noise(iVec2(fragCoord)).x*.01;
    
    return pow(smoothstep(.4,-.1,f),6.0);
}


Vec3 Sky( Vec3 ray )
{
    return Vec3(.4,.45,.5);
}


Vec3 boatRight, boatUp, boatForward;
Vec3 boatPosition;

void ComputeBoatTransform( void )
{
    Vec3 samples[5];
    
    samples[0] = Vec3(0,0, 0);
    samples[1] = Vec3(0,0, .5);
    samples[2] = Vec3(0,0,-.5);
    samples[3] = Vec3( .5,0,0);
    samples[4] = Vec3(-.5,0,0);
    
    samples[0][1] = WavesSmooth(samples[0]);
    samples[1][1] = WavesSmooth(samples[1]);
    samples[2][1] = WavesSmooth(samples[2]);
    samples[3][1] = WavesSmooth(samples[3]);
    samples[4][1] = WavesSmooth(samples[4]);
    
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
    return dir.x*boatRight+dir.x*boatUp+dir.x*boatForward;
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


float OceanDistanceField( Vec3 pos )
{
    return pos.y - Waves(pos);
}

float OceanDistanceFieldDetail( Vec3 pos )
{
    return pos.y - WavesDetail(pos);
}

Vec3 OceanNormal( Vec3 pos )
{
    Vec3 norm;
    Vec3 d = Vec3(.01*length(pos),0,0);
    
    norm[0] = OceanDistanceFieldDetail( pos+d.xyy() )-OceanDistanceFieldDetail( pos-d.xyy() );
    norm[1] = OceanDistanceFieldDetail( pos+d.yxy() )-OceanDistanceFieldDetail( pos-d.yxy() );
    norm[2] = OceanDistanceFieldDetail( pos+d.yyx() )-OceanDistanceFieldDetail( pos-d.yyx() );
    
    return normalize(norm);
}

float TraceOcean( Vec3 pos, Vec3 ray )
{
    float h = 1.0;
    float t = 0.0;
    for ( int i=0; i < 100; i++ )
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
    
    Vec3 col = Vec3(0,.04,.04); // under-sea colour
    if ( t > 0.0 )
    {
        col = mix( col, ShadeBoat( pos+(t-crackFudge)*refractedRay, refractedRay ), exp(-t) );
    }
    
    col = mix( col, reflection, fresnel );
    
    // foam
    col = mix( col, Vec3(1,1,1), WaveCrests(pos,Vec3(fragCoord[0],fragCoord[1],0)) );
    
    return col;
}

void mainImage(Vec3& fragColor, Vec2 fragCoord)
{
    ComputeBoatTransform();
    Vec2 camRot = Vec2(.5,.5);//+Vec2(-.35,4.5)*(iMouse.yx()/iResolution.yx());
    Vec3 pos, ray;
    CamPolar( pos, ray, Vec3(0,0), camRot, 3.0, 1.0, fragCoord );
    
    float to = TraceOcean( pos, ray );
    float tb = TraceBoat( pos, ray );
    Vec3 result;
    if ( to > 0.0 && ( to < tb || tb == 0.0 ) )
        result = ShadeOcean( pos+ray*to, ray, fragCoord );
    else if ( tb > 0.0 )
        result = ShadeBoat( pos+ray*tb, ray );
    else
        result = Sky( ray );
    
    // vignette effect
    result *= 1.1*smoothstep( .35, 1.0, localRay.z );
    
    fragColor = ToGamma(result);
}