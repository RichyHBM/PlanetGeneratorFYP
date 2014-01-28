#include "ResourceManager.hpp"

std::map<std::string, Texture *> ResourceManager::mTextureMap;
std::map<std::string, BitmapText *> ResourceManager::mFontMap;
std::map<std::string, Shader *> ResourceManager::mShaderMap;

Texture *ResourceManager::GetTexture( const std::string &name, const std::string &textureLocation )
{
    std::map<std::string, Texture *>::iterator it = mTextureMap.find( name );

    if ( it != mTextureMap.end() ) {
        return it->second;
    }

    Texture *texture = new Texture();
    texture->LoadFromFile( textureLocation );
    mTextureMap[name] = texture;
    return mTextureMap[name];
}

BitmapText *ResourceManager::GetFont( const std::string &name, const std::string &bitmapLocation, const std::string &textLocation )
{
    std::map<std::string, BitmapText *>::iterator it = mFontMap.find( name );

    if ( it != mFontMap.end() ) {
        return it->second;
    }

    BitmapText *font = new BitmapText();
    font->LoadFile( bitmapLocation , textLocation );
    mFontMap[name] = font;
    return mFontMap[name];
}

Shader *ResourceManager::GetShader( const std::string &name, const std::string &vertexLocation, const std::string &fragmentLocation )
{
    std::map<std::string, Shader *>::iterator it = mShaderMap.find( name );

    if ( it != mShaderMap.end() ) {
        return it->second;
    }

    Shader *shader = new Shader();
    shader->LoadShaderFiles( vertexLocation , fragmentLocation );
    mShaderMap[name] = shader;
    return mShaderMap[name];
}

void ResourceManager::Destroy()
{
    for( std::map<std::string, Texture *>::iterator it = mTextureMap.begin(); it != mTextureMap.end(); ++it ) {
        delete it->second;
    }

    for( std::map<std::string, BitmapText *>::iterator it = mFontMap.begin(); it != mFontMap.end(); ++it ) {
        delete it->second;
    }

    for( std::map<std::string, Shader *>::iterator it = mShaderMap.begin(); it != mShaderMap.end(); ++it ) {
        delete it->second;
    }
}