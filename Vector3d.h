#pragma once
class Vector3d
{
public:
    float x, y, z;
private:

public:
    Vector3d();
    Vector3d(float x, float y, float z);
    Vector3d(const Vector2d& v);
    Vector3d perp();
    float mag();
    Vector3d normalized();
    void scale(float s);
private:
};
