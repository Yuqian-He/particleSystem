#include<iostream>
#include"Emitter.h"
#include <ngl/Random.h>
#include<fstream>
#include<sstream>

//this function I don't know.: change the random function to Emitter
ngl::Vec3 randomVectorOnSphere(float _radi=1)
{
    return ngl::Vec3();
}

Emitter::Emitter(size_t _numParticle)
{
    m_particles.resize(_numParticle);
    ngl::Vec3 emitDir(0,10.0f,0);
    for(auto &p : m_particles) //auto create copy but we want to change the original one so we use &
    {
        p.direction=emitDir * ngl::Random::randomPositiveNumber()+ randomVectorOnSphere()*10;//video 1:12 don't understand
        p.direction.m_y=std::abs(p.direction.m_y);//I don't know why use m_y,check ngl folder
        p.colour=ngl::Random::getRandomColour3();
    }
}

size_t Emitter::numParticles() const
{
    return m_particles.size();
}

void Emitter::update()
{
    float _dt=0.01;
    ngl::Vec3 gravity(0,-9.81f,0);
    for(auto &p:m_particles)
    {
        //direction=velocity
        p.direction+=gravity*_dt*0.5f; //formula: dt_s=1/2*gravity*(dt_t)^2
        p.position+=p.direction*_dt;
        p.scale+=0.001f;
    }

}

void Emitter::render() const
{
    for(auto p : m_particles)
    {
        //std::cout<<"**********************"<<'\n';
        //std::cout<<p.position.x<<','<<p.position.y<<','<<p.position.z<<'\n';
        //std::cout<<p.direction.x<<' '<<p.direction.y<<' '<<p.direction.z<<'\n';
        //std::cout<<p.colour.x<<' '<<p.colour.y<<' '<<p.colour.z<<'\n';
    }
}