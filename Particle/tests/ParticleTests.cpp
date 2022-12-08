#include <gtest/gtest.h>
#include "Particle.h"
#include "Emitter.h"

TEST(Particle,ctor)
{
  Particle p;
  EXPECT_FLOAT_EQ(p.position.x, 0.0f);
  EXPECT_FLOAT_EQ(p.position.y, 0.0f);
  EXPECT_FLOAT_EQ(p.position.z, 0.0f);

  EXPECT_FLOAT_EQ(p.colour.x, 0.0f);
  EXPECT_FLOAT_EQ(p.colour.y, 0.0f);
  EXPECT_FLOAT_EQ(p.colour.z, 0.0f);

  EXPECT_FLOAT_EQ(p.direction.x, 0.0f);
  EXPECT_FLOAT_EQ(p.direction.y, 1.0f);
  EXPECT_FLOAT_EQ(p.direction.z, 0.0f);
}

TEST(Emitter,ctor)
{
  Emitter e(100);
  EXPECT_EQ(e.numParticles(),100);
}

//I don't understand
TEST(Vec3,operatorMultScalar)
{
  Vec3 a(1,2,3);
  Vec3 b=a*2;
  EXPECT_FLOAT_EQ(b.x,2);
  EXPECT_FLOAT_EQ(b.y,4);
  EXPECT_FLOAT_EQ(b.z,6);
}

TEST(Vec3,operatorAddScalar)
{
  Vec3 a(1,2,3);
  Vec3 b(5,6,7);
  Vec3 c = a+b;
  EXPECT_FLOAT_EQ(c.x,6);
  EXPECT_FLOAT_EQ(c.y,8);
  EXPECT_FLOAT_EQ(c.z,10);
}

TEST(Vec3,plusEqual)
{
  Vec3 a(1,2,3);
  Vec3 b(5,6,7);
  a+=b;
  EXPECT_FLOAT_EQ(a.x,6);
  EXPECT_FLOAT_EQ(a.y,8);
  EXPECT_FLOAT_EQ(a.z,10);
}