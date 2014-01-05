#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "framework/DrawDebugInfo.hpp"
#include "framework/Window.hpp"

#include "framework/GLHelp/GLHelp.hpp"

class Program
{
public:


    ///
    ///Default constructor
    ///
    Program( Window *pWindow );

    ///
    ///Default destructor
    ///
    ~Program();

    ///
    ///Do certain input stuff here
    ///
    void HandleEvents();
    ///
    ///Handle game logic
    ///
    void Update();
    ///
    ///Draw stuff
    ///
    void Draw();

    ///
    ///Run method, does input handling, update and draw
    ///
    void Run();

    ///
    ///Get the delta amount in seconds, for 60fps this would be around 0.016
    ///
    const double GetDelta();


protected:
    Window *mWindow;
    DrawDebugInfo mDebugInfo;

    VBO mVertexBuffer;
    std::vector<glm::vec3> mVertexList;

    VBO mNormalBuffer;
    std::vector<glm::vec2> mNormalList;

    VBO mIndexBuffer;
    std::vector<unsigned int> mIndexList;

    VBO mHeightBuffer;
    std::vector<float> mHeightList;

    Texture mTerrainTexture;

    Shader mShader;
    glm::mat4 mMVP;
private:
};

#endif // PROGRAM_HPP
