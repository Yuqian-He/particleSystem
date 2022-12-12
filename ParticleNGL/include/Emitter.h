#ifndef EMITTER_H_
#define EMITTER_H_
#include<cstddef>
#include<Particle.h>
#include<vector>
#include<string_view>
#include<memory>
#include<ngl/AbstractVAO.h>
//devolve mamengement of drawing apart from camera set up to the emitter class
//vertex of array of the object.store all the information of the vertex
//vertex buffer object to store the date you render
//raw opengl command

class Emitter
{
    public:
    Emitter(size_t _numParticle);
    size_t numParticles() const;
    void update();
    void render() const;

    private:
    void createParticle(Particle &io_p);
    //size_t number;
    std::vector<Particle> m_particles;
    
    GLuint m_vao;//is the opengl unsigned integer,vao is the vertex array object,container hold multiple buffers
    //this container members where they are, how they are.
    GLuint m_buffer;//buffer to store all of the date to render,those buffer will be placed on GPU

    //try to generate a buffer data
    //very simple render pipline
    

   //std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif