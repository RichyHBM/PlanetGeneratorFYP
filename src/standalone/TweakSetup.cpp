#include "TweakSetup.hpp"

#include "Program.hpp"
#include "framework/Window/Window.hpp"
#include "framework/RuntimeSettings.hpp"

void TW_CALL QuitButton( void *clientData )
{
    ( ( Window * )clientData )->Close();
}

void TW_CALL RebuildButton( void *clientData )
{
    ( ( Program * )clientData )->GetDebugInfo()->SetDrawRebuild();
    ( ( Program * )clientData )->Draw();
    ( ( Program * )clientData )->GetWindow()->Display();
    ( ( Program * )clientData )->GetRoundedCube()->RebuildNoise();
    ( ( Program * )clientData )->GetRoundedCube()->RebuildSides();
}

void TW_CALL RebuildTextureButton( void *clientData )
{
    unsigned char image[256 * 256 * 4];
    NoiseppNoise noise(
        RuntimeSettings::Settings.ImgSeed,
        RuntimeSettings::Settings.ImgOctaves,
        RuntimeSettings::Settings.ImgPersistence,
        RuntimeSettings::Settings.ImgFrequency,
        RuntimeSettings::Settings.ImgQuality,
        RuntimeSettings::Settings.ImgScale,
        RuntimeSettings::Settings.ImgLacunarity,
        RuntimeSettings::Settings.ImgDistortion
    );
    int i = 0;

    for( int y = 0; y < 256; y++ ) {
        for( int x = 0; x < 256; x++ ) {
            unsigned char val = ( unsigned char )( noise.Generate( x, y ) * 100 );
            image[0 + i * 4] = val;
            image[1 + i * 4] = val;
            image[2 + i * 4] = val;
            image[3 + i * 4] = 255;
            i++;
        }
    }

    Texture *t = ( ( Program * )clientData )->GetRoundedCube()->GetTexture();
    t->LoadData( image,256,256 );
    ( ( Program * )clientData )->GetRoundedCube()->UpdateTextures();
    ( ( Program * )clientData )->GetTextureRenderer()->SetTexture( t->GetGLUINT() );
}


void SetupTweakControls( Program *program )
{
    TwBar *myBar;
    myBar = TwNewBar( "Controls" );
    TwSetParam( myBar, NULL, "position", TW_PARAM_CSTRING, 1, "20 60" );
    TwDefine( " Controls size='200 500' " );
    TwAddVarRW( myBar, "Draw Lines", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.DrawLines, NULL );
    TwAddVarRW( myBar, "Draw Hidden", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.DrawHidden, NULL );
    TwAddVarRW( myBar, "Freeze Frustrum", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.FreezeFrustrum, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Subdivisions", TW_TYPE_UINT32, &RuntimeSettings::Settings.Subdivisions, " max=20 " );
    TwAddVarRW( myBar, "Planet Radius", TW_TYPE_UINT32, &RuntimeSettings::Settings.PlanetRadius, NULL );
    TwAddVarRW( myBar, "Rebuild Realtime", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.RealtimeRebuild, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Light Direction", TW_TYPE_DIR3F, &RuntimeSettings::Settings.LightDirection, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Noise Seed", TW_TYPE_UINT32, &RuntimeSettings::Settings.Seed, NULL );
    TwAddVarRW( myBar, "Noise Octaves", TW_TYPE_UINT32, &RuntimeSettings::Settings.Octaves, NULL );
    TwAddVarRW( myBar, "Noise Persistence", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Persistence, NULL );
    TwAddVarRW( myBar, "Noise Frequency", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Frequency, NULL );
    TwAddVarRW( myBar, "Noise Quality", TW_TYPE_UINT32, &RuntimeSettings::Settings.Quality, NULL );
    TwAddVarRW( myBar, "Noise Scale", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Scale, NULL );
    TwAddVarRW( myBar, "Noise Lacunarity", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Lacunarity, NULL );
    TwAddVarRW( myBar, "Noise Distortion", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Distortion, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddButton( myBar, "Rebuild", RebuildButton, program, NULL );
    TwAddButton( myBar, "Quit", QuitButton, program->GetWindow(), NULL );
    TwBar *myImageBar;
    myImageBar = TwNewBar( "Texture Controls" );
    TwSetParam( myImageBar, NULL, "position", TW_PARAM_CSTRING, 1, "540 250" );
    TwAddVarRW( myImageBar, "Texture Seed", TW_TYPE_UINT32, &RuntimeSettings::Settings.ImgSeed, NULL );
    TwAddVarRW( myImageBar, "Texture Octaves", TW_TYPE_UINT32, &RuntimeSettings::Settings.ImgOctaves, NULL );
    TwAddVarRW( myImageBar, "Texture Persistence", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.ImgPersistence, NULL );
    TwAddVarRW( myImageBar, "Texture Frequency", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.ImgFrequency, NULL );
    TwAddVarRW( myImageBar, "Texture Quality", TW_TYPE_UINT32, &RuntimeSettings::Settings.ImgQuality, NULL );
    TwAddVarRW( myImageBar, "Texture Scale", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.ImgScale, NULL );
    TwAddVarRW( myImageBar, "Texture Lacunarity", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.ImgLacunarity, NULL );
    TwAddVarRW( myImageBar, "Texture Distortion", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.ImgDistortion, NULL );
    TwAddSeparator( myImageBar, NULL, NULL );
    TwAddButton( myImageBar, "Rebuild Texture", RebuildTextureButton, program, NULL );
}