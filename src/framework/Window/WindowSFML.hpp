#ifndef WINDOWSFML_HPP
#define WINDOWSFML_HPP

#ifdef SFML
#include "../Includes.hpp"
#include "Window.hpp"

class WindowSFML : public Window
{
public:
    WindowSFML();
    ~WindowSFML();

    bool IsFocused();
    bool IsOpen();
    //Sets the cursor to be hidden or visible
    void SetCursor( CursorState pState );
    //Swaps teh context buffer to show what has been drawn
    void Display();
    //Process sfml events
    void DoEvents();
    bool IsWindowCreated();
    void MakeContextCurrent();
    void ResetDelta();
    void Close();
protected:
    sf::Window mWindow;
    bool mIsFocused;
    sf::Clock mDeltaClock;
};

#endif //SFML
#endif //WINDOWSFML_HPP