#ifndef VEC3_H_
#define VEC3_H_

class Vec3
{
    public:
    Vec3()=default;
    Vec3(float _x, float _y, float _z):x{_x},y{_y},z{_z}{}
    Vec3 operator*(float _rhs) const; //the const means the function will not modify the object on which it is called
    Vec3 operator+(const Vec3 &_rhs) const; //Using a reference as the operand allows the function to directly access and modify the original Vec3 object,
    void operator+=(const Vec3 &_rhs);
    float x=0.0f;
    float y=0.0f;
    float z=0.0f;
};

#endif