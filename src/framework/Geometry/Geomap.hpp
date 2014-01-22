#ifndef GEOMAP_HPP
#define GEOMAP_HPP

#include "./common/FlatPlane.hpp"
#include <vector>

class Geomap
{
public:
    Geomap();
    ~Geomap();

    void Update();
    void Draw();
protected:
    std::vector<FlatPlane *> mPlanes;

    glm::mat4 mModel;
    glm::mat4 mMVP;
};

#endif //GEOMAP_HPP
