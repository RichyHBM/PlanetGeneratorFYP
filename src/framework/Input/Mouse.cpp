#include "Mouse.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../WindowSettings.hpp"

void Mouse::Set( float x, float y )
{
    sf::Mouse::setPosition( sf::Vector2i( x, y ) );
}

glm::vec2 Mouse::GetDisplacement()
{
    sf::Vector2f center( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f );
    sf::Vector2i mouse = sf::Mouse::getPosition();
    return glm::vec2( mouse.x - center.x, mouse.y - center.y );
}
