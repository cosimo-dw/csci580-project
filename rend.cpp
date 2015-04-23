// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
#include "rend.h"
#include "camera.h"
#include "sky.h"
#include "ocean.h"
#include "boat.h"

void mainImage( Vec3& fragColor, Vec2 fragCoord )
{
    Vec2 camRot = Vec2(0.2,0.2);//+Vec2(-.35,4.5)*(iMouse.yx()/iResolution.yx());
    Vec3 pos = getCameraPosition();
    Vec3 ray = getRay( fragCoord );
    
    float to = TraceOcean( pos, ray );
    float tb = TraceBoat( pos, ray );
    Vec3 result;
    if ( to > 0.0 && ( to < tb || tb == 0.0 ) )
        result = ShadeOcean( pos+ray*to, ray, fragCoord );
    else if ( tb > 0.0 )
        result = ShadeBoat( pos+ray*tb, ray );
    else
        result = Sky( ray );
    
    fragColor = postProcess(result);
}

void initWorld(void)
{
    initOcean(); // initBoat should be called after initOcean
    initBoat();
    initCamera();
}