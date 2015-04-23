#pragma once

#include "type.h"

void initCamera( Vec3 origin = Vec3(0,0,0), float distance = 12.0, float zoom = 2.5 );

Vec3 getCameraPosition();

Vec3 getRay( Vec2 fragCoord );

Vec3 postProcess( Vec3 color );