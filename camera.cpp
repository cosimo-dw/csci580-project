#include "camera.h"
#include "func.h"

//extern Vec2 iMouse;
extern Vec2 iResolution;
extern Vec2 camRot;

Vec3 camRight, camUp, camForward;
Vec3 camPosition;

float RAY_Z;

void initCamera( Vec3 origin, float distance, float zoom )
{
    // get rotation coefficients
    Vec2 c = Vec2(cos(camRot.x),cos(camRot.y));
    Vec2 s = Vec2(sin(camRot.x),sin(camRot.y)); 
    
    camRight = Vec3(c.y,0,-s.y);
    camUp = Vec3(s.x*s.y,c.x,s.x*c.y);
    camForward = Vec3(c.x*s.y,-s.x,c.x*c.y);
    // position camera
    camPosition = origin - distance * camForward;
    RAY_Z = iResolution.y*zoom;
}

Vec3 CamRayToWorld( Vec3 ray )
{
    return ray.x*camRight+ray.y*camUp+ray.z*camForward;
}

Vec3 localRay;

Vec3 getCameraPosition()
{
    return camPosition;
}

// Set up a camera looking at the scene.
// origin - camera is positioned relative to, and looking at, this point
// distance - how far camera is from origin
// rotation - about x & y axes, by left-hand screw rule, relative to camera looking along +z
// zoom - the relative length of the lens
Vec3 getRay( Vec2 fragCoord )
{
    // ray in view space
    Vec3 ray;
    Vec2 tmp = fragCoord - iResolution*.5;
    ray[0] = tmp[0];
    ray[1] = tmp[1];
    ray[2] = RAY_Z;
    ray = normalize(ray);
    localRay = ray;
    
    ray = CamRayToWorld(ray);
    
    return ray;
}

// Gamma correction
const float GAMMA = 2.2;

Vec3 ToGamma( Vec3 col )
{
    // convert back into colour values, so the correct light will come out of the monitor
    return pow( col, Vec3(1.0/GAMMA,1.0/GAMMA,1.0/GAMMA) );
}

Vec3 postProcess( Vec3 color )
{
    // vignette effect
    color *= 1.1*smoothstep( .35, 1.0, localRay.z );
    
    return ToGamma(color);
}