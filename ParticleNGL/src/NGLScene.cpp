#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include<ngl/ShaderLib.h>
#include<ngl/Util.h>
#include <iostream>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Particle NGL");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();   //the first called, link between the opengl driver and video driver and opengl functions
  //we should never issue any command require opengl, until this code being called
  
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  m_emitter=std::make_unique<Emitter>(1000);//envoke the constructor of emitter and return a smart pointer,we don;t need to call the destructor.
  startTimer(10);//I don;t know what is it.

  //the basic color and shader
  //load and make the active shader,this shader within ngl
  ngl::ShaderLib::use(ngl::nglColourShader);
  // MVP is the model view project uniform
  //Colour 4float
  m_view=ngl::lookAt({12,12,12},{0,0,0},{0,1,0});//put the camera position {12,12,12},look at {0,0,0},and {0,1,0}is the up direction
  //ased on these arguments, the function calculates a projection transformation matrix and applies it to the current OpenGL state, 
  //so that any subsequent rendering will use this transformation to determine the shape and size of the viewing frustum
  m_project=ngl::perspective(45.0f,1.0f,0.01f,50.0f);//a field of view angle, an aspect ratio, a near clipping plane distance, and a far clipping plane distance. 
  
  ngl::ShaderLib::setUniform("MVP",m_project*m_view);
  ngl::ShaderLib::setUniform("Colour",1.0f,0.0f,0.0f,1.0f);
  glPointSize(2);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  m_emitter->update();//everytime the time trigger, we call emitter to update.
  update();

}


void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  m_emitter->render();

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
