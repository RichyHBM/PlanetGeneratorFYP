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
    TwAddVarRW( myBar, "Subdivisions", TW_TYPE_UINT32, &RuntimeSettings::Settings.Subdivisions, " max=9 " );
    TwAddVarRW( myBar, "Planet Radius", TW_TYPE_UINT32, &RuntimeSettings::Settings.PlanetRadius, NULL );
    TwAddVarRW( myBar, "Water Radius", TW_TYPE_UINT32, &RuntimeSettings::Settings.WaterRadius, NULL );
    //TwAddVarRW( myBar, "Rebuild Realtime", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.RealtimeRebuild, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Grass Height", TW_TYPE_FLOAT, &RuntimeSettings::Settings.GrassHeight, NULL );
    TwAddVarRW( myBar, "Dirt Height", TW_TYPE_FLOAT, &RuntimeSettings::Settings.DirtHeight, NULL );
    TwAddVarRW( myBar, "Snow Height", TW_TYPE_FLOAT, &RuntimeSettings::Settings.SnowHeight, NULL );
    TwAddVarRW( myBar, "Wave Size", TW_TYPE_FLOAT, &RuntimeSettings::Settings.WaveSize, NULL );
    TwAddVarRW( myBar, "Sin Amount", TW_TYPE_FLOAT, &RuntimeSettings::Settings.SinAmount, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Light Direction", TW_TYPE_DIR3F, &RuntimeSettings::Settings.LightDirection, NULL );
    TwAddVarRW( myBar, "Water Color", TW_TYPE_COLOR4F, &RuntimeSettings::Settings.WaterColor, NULL );
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
}