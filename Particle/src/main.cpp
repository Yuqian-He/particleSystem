#include <iostream>
#include <chrono>
#include "Emitter.h"
#include<fmt/format.h>

int main()
{
  std::cout<<"Particle System\n";
  Emitter e(1000);
  for(int i = 0; i<100;++i)
  {
    e.update();
    //e.render();
    e.writeToGeo(fmt::format("Particle.{:04d}.geo",i));
  }
  return EXIT_SUCCESS;
}