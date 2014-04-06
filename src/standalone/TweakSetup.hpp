#ifndef TWEAKSETUP_HPP
#define TWEAKSETUP_HPP

#include <AntTweakBar.h>

//forward declaration
class Program;

//Callbacks for the GUI controls
void TW_CALL QuitButton( void *clientData );
void TW_CALL RebuildButton( void *clientData );
void SetupTweakControls( Program *program );

#endif //TWEAKSETUP_HPP