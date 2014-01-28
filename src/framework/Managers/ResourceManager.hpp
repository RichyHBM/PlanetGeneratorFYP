#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include "../GLHelp/GLHelp.hpp"

class ResourceManager
{
public:
    //Return the corresponding asset from the required location
    static Texture *GetTexture( const std::string &name, const std::string &textureLocation );
    static BitmapText *GetFont( const std::string &name, const std::string &bitmapLocation, const std::string &textLocation );
    static Shader *GetShader( const std::string &name, const std::string &vertexLocation, const std::string &fragmentLocation );
    static void Destroy();
protected:
    static std::map<std::string, Texture *> mTextureMap;
    static std::map<std::string, BitmapText *> mFontMap;
    static std::map<std::string, Shader *> mShaderMap;
};

#endif //RESOURCE_MANAGER_HPP