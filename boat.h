#pragma once
#include "type.h"

void initBoat( void );

float TraceBoat( Vec3 pos, Vec3 ray );

Vec3 ShadeBoat( Vec3 pos, Vec3 ray );