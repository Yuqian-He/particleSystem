#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Vec3.h"

struct Particle //bad idea
{
    int lifetime=0;
    Vec3 position;
    Vec3 colour;
    Vec3 direction={0.0f,1.0f,0.0f};
    float scale=0.01f;
};


#endif