#ifndef EMITTER_H_
#define EMITTER_H_
#include<cstddef>
#include<Particle.h>
#include<vector>
#include<string_view>

class Emitter
{
    public:
    Emitter(size_t _numParticle);
    size_t numParticles() const;
    void update();
    void render() const;
    void writeToGeo(std::string_view _fname) const;

    private:
    //size_t number;
    std::vector<Particle> m_particles;
};

#endif