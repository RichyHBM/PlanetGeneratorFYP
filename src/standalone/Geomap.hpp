#ifndef GEOMAP_HPP
#define GEOMAP_HPP

#include "Plane.hpp"
#include <vector>

class Geomap
{
public:
    Geomap();
    ~Geomap();

    void Update();
    void Draw();
protected:
    std::vector<Plane *> mPlanes;

    glm::mat4 mMVP;
};

#endif //GEOMAP_HPP