#include<iostream>
#include"Emitter.h"
#include <ngl/Random.h>
#include<fstream>
#include<sstream>
#include<ngl/VAOFactory.h>
#include<ngl/SimpleVAO.h>

//this function I don't know.: change the random function to Emitter
ngl::Vec3 randomVectorOnSphere(float _radius=1)
{
    float phi = ngl::Random::randomPositiveNumber(static_cast<float>(M_PI * 2.0f));
	float costheta = ngl::Random::randomNumber();
	float u =ngl::Random::randomPositiveNumber();
	float theta = acos(costheta);
	float r = _radius * std::cbrt(u);
	return ngl::Vec3(r * sin(theta) * cos(phi),
					r * sin(theta) * sin(phi),
					r * cos(theta)
					);
}

void Emitter::createParticle(Particle &io_p)
{
    ngl::Vec3 emitDir(0,10.0f,0);

    io_p.position.set(0.0f,0.0f,0.0f);
    io_p.direction=emitDir * ngl::Random::randomPositiveNumber()+ randomVectorOnSphere()*10;//video 1:12 don't understand
    io_p.direction.m_y=std::abs(io_p.direction.m_y);//I don't know why use m_y,check ngl folder
    io_p.colour=ngl::Random::getRandomColour3();
    io_p.lifetime=ngl::Random::getIntFromGeneratorName("particleLife");

}

Emitter::Emitter(size_t _numParticle)
{
    m_particles.resize(_numParticle);
    
    for(auto &p : m_particles) //auto create copy but we want to change the original one so we use &
    {
        createParticle(p);
    }

/*
    //set up opengl buffers
    //this is a state object
    glGenVertexArrays(1,&m_vao);//we want 1 vertex array, store in memory address in m_vao
    glGenBuffers(1,&m_buffer);
    std::cout<<m_vao<<' '<<m_buffer<<'\n';
*/

    m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);

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
        if(p.direction.m_y<=0.0f || --p.lifetime<=0)
        {
            createParticle(p);
        }
    }

}

void Emitter::render() const
{
/*
    //std::cout<<"render\n";
    //we need to go through and pass our particle date to opengl
    //opengl can only bind one thing at a time
    glBindVertexArray(m_vao); //opengl has the bind to add the,if we create something and we want to change it, we should bind it to active
    //memory for our particle date,and copy to opengl,do it in each frame
    //opengl use a function, glbufferdate
    //1.put it in what kind of buffer
    //2.how big the date is,how does it to malloc
    //3.where the date begins,I want the first alloment to be position
    //4.give opengl a hit, how these date be used
    glBufferData(GL_ARRAY_BUFFER,m_particles.size()*sizeof(Particle), &m_particles[0].position.m_x,GL_STATIC_DRAW);//combination of mlloce and m_copy. target
    //we should tell opengl how is date will layout
    //1.position;2.three component;3.where or not the date should be normalized
    //4.how far do we need to jump to get the next date we need
    //5.where is start in the buffer we are binding to
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Particle),0);
    //enable it,it tells OpenGL that the data for that attribute is present in the current vertex array object, and should be used when rendering geometry. 
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Particle),reinterpret_cast<float *>(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //kick off the shader
    glDrawArrays(GL_POINTS,0,m_particles.size());
    //disable
    glBindVertexArray(0);
*/
    glPointSize(4);
    m_vao->bind();
    m_vao->setData(ngl::SimpleVAO::VertexData(m_particles.size()*sizeof(Particle), m_particles[0].position.m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),3);//why this use 3

    m_vao->setNumIndices(m_particles.size());
    m_vao->draw();
    m_vao->unbind();


}