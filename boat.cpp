#include "boat.h"
#include "func.h"
#include "ocean.h"
#include "sky.h"
//#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

extern Vec2 iResolution;

Vec3 boatRight, boatUp, boatForward;
Vec3 boatPosition;

vector<vector<Vec3> > vert;
vector<vector<Vec3> > norm;

Vec3 localNormal;

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

    char dummy[256];
    float uvList[3][2];
    int i = 0;
    FILE *infile;
    infile  = fopen( "pot.asc" , "r" );
    vert.reserve(1000);
    norm.reserve(1000);
    while( fscanf(infile, "%s", dummy) == 1) {  /* read in tri word */
        vert.push_back(vector<Vec3>(3));
        norm.push_back(vector<Vec3>(3));
        fscanf(infile, "%f %f %f %f %f %f %f %f", &(vert[i][0][0]), &(vert[i][0][1]), &(vert[i][0][2]),
        &(norm[i][0][0]), &(norm[i][0][1]), &(norm[i][0][2]), &(uvList[0][0]), &(uvList[0][1]));
        fscanf(infile, "%f %f %f %f %f %f %f %f", &(vert[i][1][0]), &(vert[i][1][1]), &(vert[i][1][2]),
        &(norm[i][1][0]), &(norm[i][1][1]), &(norm[i][1][2]), &(uvList[1][0]), &(uvList[1][1]));
        fscanf(infile, "%f %f %f %f %f %f %f %f", &(vert[i][2][0]), &(vert[i][2][1]), &(vert[i][2][2]),
        &(norm[i][2][0]), &(norm[i][2][1]), &(norm[i][2][2]), &(uvList[2][0]), &(uvList[2][1]));
        i++;
    }
    fclose(infile);
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
    pos -= boatPosition;
    pos = WorldToBoat(pos);
    ray = WorldToBoat(ray);
    float zval = 2147483647.0;
    float dist = 0.0;
    int idx = -1;
    float tmpW[3];
    for (int i = 0; i< vert.size(); i++) {
        Vec3& p0 = vert[i][0];
        Vec3& p1 = vert[i][1];
        Vec3& p2 = vert[i][2];
        Vec3 normal = cross(p1 - p0,p2 - p0);
        float t = dot(p0 - pos, normal) / dot(ray, normal);
        Vec3 x = pos + t * ray;
        float w0 = dot(cross(p2 - p1, x - p1), normal);
        float w1 = dot(cross(p0 - p2, x - p2), normal);
        float w2 = dot(cross(p1 - p0, x - p0), normal);
        if (w0 >= 0 && w1 >= 0 && w2 >= 0 && x.z < zval) {
            zval = x.z;
            dist = t * length(ray);
            idx = i;
            tmpW[0] = w0;
            tmpW[1] = w1;
            tmpW[2] = w2;
        }
    }
    if (idx >= 0) {
        localNormal = (norm[idx][0] * tmpW[0]) + (norm[idx][1] * tmpW[1]) + (norm[idx][2] * tmpW[2]);
        localNormal = normalize(localNormal);
    }
    return dist;
}


Vec3 ShadeBoat( Vec3 pos, Vec3 ray )
{
    pos -= boatPosition;
    Vec3 norm = localNormal;
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
   // albedo = mix( Vec3(.04,.04,.04), albedo, smoothstep( .05-aa*1.0, .05, abs(abs(pos.y)-.6) ) );
   // albedo = mix( Vec3(1,.8,.08), albedo, smoothstep( .05-aa*1.0, .05, abs(abs(pos.y)-.65) ) );
    
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