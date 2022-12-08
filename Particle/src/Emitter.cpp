#include<iostream>
#include"Emitter.h"
#include "Random.h"
#include<fstream>
#include<sstream>

Emitter::Emitter(size_t _numParticle)
{
    m_particles.resize(_numParticle);
    Vec3 emitDir(0,10.0f,0);
    for(auto &p : m_particles) //auto create copy but we want to change the original one so we use &
    {
        p.direction=emitDir * Random::randomPositiveFloat()+ Random::randomVectorOnSphere()*10;//video 1:12 don't understand
        p.direction.y=std::abs(p.direction.y);
        p.colour=Random::randomPositiveVec3();
    }
}

size_t Emitter::numParticles() const
{
    return m_particles.size();
}

void Emitter::update()
{
    float _dt=0.01;
    Vec3 gravity(0,-9.81f,0);
    for(auto &p:m_particles)
    {
        //direction=velocity
        p.direction+=gravity*_dt*0.5f; //formula: dt_s=1/2*gravity*(dt_t)^2
        p.position+=p.direction*_dt;
        p.scale+=0.001f;
    }

}

void Emitter::writeToGeo(std::string_view _fname) const
{
    std::ofstream file(_fname.data());//used for writing to files
    std::cout<<"saving "<<_fname<<'\n';

    std::stringstream geo;
    geo<<"PGEOMETRY V5\n";
    geo<<"NPoints "<<m_particles.size()<<" NPrims 1\n";
    geo<<"NPointGroups 0 NPrimGroups 0\n";
    geo<<"NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 1 NAttrib 0\n";
    geo<<"PointAttrib\n";
    geo<<"Cd 3 float 1 1 1 \n";
    geo<<"pscale 1 float 1 \n";
    for (auto p:m_particles)
    {
        geo<<p.position.x<<' '<<p.position.y<<' '<<p.position.z<<" 1 (";
        geo<<p.colour.x<<' '<<p.colour.y<<' '<<p.colour.z<<' ';
        geo<<p.scale<<" )\n";
    }
    geo<<"PrimitiveAttrib\n";
    geo<<"generator 1 index 1 papi\n";
    geo<<"Part "<<m_particles.size()<<' ';
    for(int i=0; i<m_particles.size(); ++i)
    {
        geo<<i<<' ';
    }
    geo<<"[0]\n";
    geo<<"beginExtra\n";
    geo<<"endExtra\n";

    if(file.is_open())
    {
        file<<geo.rdbuf();
        //fast reading/writing
    }
    file.close();
}

void Emitter::render() const
{
    for(auto p : m_particles)
    {
        //std::cout<<"**********************"<<'\n';
        std::cout<<p.position.x<<','<<p.position.y<<','<<p.position.z<<'\n';
        //std::cout<<p.direction.x<<' '<<p.direction.y<<' '<<p.direction.z<<'\n';
        //std::cout<<p.colour.x<<' '<<p.colour.y<<' '<<p.colour.z<<'\n';
    }
}