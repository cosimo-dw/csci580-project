#include "sky.h"
#include "func.h"
#include "sky.h"
#include "func.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

const int noiseWidth = 512;
const int noiseHeight = 512;
float noise2[noiseWidth][noiseHeight];
bool noiseGenerated = 0;
int calls = 0;
void generateNoise2()
{
    for (int x = 0; x < noiseWidth; x++)
        for (int y = 0; y < noiseHeight; y++)
        {
            noise2[x][y] = (rand() % 32768) / 32768.0;
        }
}

double smoothNoise(double x, double y)
{
    //get fractional part of x and y
    double fractX = x - int(x);
    double fractY = y - int(y);
    
    //wrap around
    int x1 = (int(x) + noiseWidth) % noiseWidth;
    int y1 = (int(y) + noiseHeight) % noiseHeight;
    
    //neighbor values
    int x2 = (x1 + noiseWidth - 1) % noiseWidth;
    int y2 = (y1 + noiseHeight - 1) % noiseHeight;
    
    //smooth the noise with bilinear interpolation
    double value = 0.0;
    value += fractX       * fractY       * noise2[x1][y1];
    value += fractX       * (1 - fractY) * noise2[x1][y2];
    value += (1 - fractX) * fractY       * noise2[x2][y1];
    value += (1 - fractX) * (1 - fractY) * noise2[x2][y2];
    
    return value;
}

double turbulence(double x, double y, double size)
{
    double value = 0.0, initialSize = size;
    
    while(size >= 1)
    {
        value += smoothNoise(x / size, y / size) * size;
        size /= 2.0;
    }
    
    return(128.0 * value / initialSize);
}

float hue2rgb(float p, float q, float t){
    if(t < 0)
        t += 1;
    if(t > 1)
        t -= 1;
    if(t < 1/6.0)
        return p + (q - p) * 6 * t;
    if(t < 1/2.0)
        return q;
    if(t < 2/3.0)
        return p + (q - p) * (2/3.0 - t) * 6;
    
    return p;
}

Vec3 hslToRgb(float h, float s, float l){
    float r, g, b;
    
    if(s == 0)
    {
        r = g = b = l; // achromatic
    }
    else
    {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        r = hue2rgb(p, q, h + 1/3.0);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1/3.0);
    }
    
    return Vec3(r, g, b);
}


Vec3 Sky( Vec2 coord )
{
    if (!noiseGenerated)
    {
        generateNoise2();
        noiseGenerated = true;
    }
    
    Vec2 newCoord;
    newCoord[0] = (int)coord[0];
    newCoord[1] = (int)coord[1]+256;
    
//    cout << newCoord[0] << "\t" << newCoord[1]<< endl;
    float L = (128 + turbulence(newCoord[0], newCoord[1], 16) / 2) ;

//    cout << L << endl;
    
    Vec3 color = hslToRgb(211.0/360.0,  32.5/100.0, L / 255.0);
    
//    cout << color[0] << "\t" << color[1] << "\t" << color[2] << endl;
    
    //    cout << calls++ << endl;
    
    return color;
}

Vec3 Sky( Vec3 ray )
{
	Vec2 coord;
	coord[0] = acos(ray.x) / 3.14 * 512.0;
	coord[1] = acos(ray.y) / 3.14 * 512.0;
	return Sky( coord );
    //return Vec3(0.8,0.85,0.9);
}
