#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "GLFW\glfw3.h"

class Program
{
public:
    ///
    ///Default constructor
    ///
    Program(GLFWwindow* window);
    
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

    ///
    ///Eit the run method, and close the game
    ///
    void Close();
protected:
	double mDelta;
	GLFWwindow* mWindow;
private:
};

#endif // PROGRAM_HPP
