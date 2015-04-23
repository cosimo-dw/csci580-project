#pragma once
#include "type.h"

void initOcean( void );

float Waves( Vec3 pos, int octaves );

float TraceOcean( Vec3 pos, Vec3 ray );

Vec3 ShadeOcean( Vec3 pos, Vec3 ray, Vec2 fragCoord );