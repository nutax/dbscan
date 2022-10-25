#ifndef __DOORS_H__
#define __DOORS_H__

#include "core/simd.h"
#include "core/random.h"
#include <vector>

#define DOORS 100
#define PLAYERS 30

void doors_normal();
void doors_simd();

struct Player
{
    float xpos;
    float ypos;
    float zpos;
    uint32_t team;
};

struct Door
{
    float xpos;
    float ypos;
    float zpos;
    float radiusSq;
    uint32_t team;
};

STRUCT(DoorSimd, float, float, float, float, uint32_t, uint32_t)
{
    STRUCT_NO_COMPARATORS;
    STRUCT_DATA(0, DoorSimd, XPos);
    STRUCT_DATA(1, DoorSimd, YPos);
    STRUCT_DATA(2, DoorSimd, ZPos);
    STRUCT_DATA(3, DoorSimd, RadiusSq);
    STRUCT_DATA(4, DoorSimd, Team);
};

#endif