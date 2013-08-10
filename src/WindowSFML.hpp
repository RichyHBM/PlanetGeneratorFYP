#ifndef WINDOWSFML_HPP
#define WINDOWSFML_HPP

#ifdef SFML
#include "Includes.hpp"
#include "Window.hpp"

class WindowSFML : public Window
{
public:
    WindowSFML();
    ~WindowSFML();

    bool IsFocused();
    bool IsOpen();
    void SetCursor( CursorState pState );
    void Display();
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