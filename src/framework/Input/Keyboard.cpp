#include "Keyboard.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../Managers/MatrixManager.hpp"
#include "../Utilities.hpp"
#include "../RuntimeSettings.hpp"

#include "Mouse.hpp"

Keyboard::Keyboard() : mHorizontalAngle( Util::Maths::fPI ), mVerticalAngle( 0 )
{
}
Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
    float delta = RuntimeSettings::Settings.Delta;
    float mouseSpeed = 0.1f;
    float keyboardSpeed = 50;
    //Get the amount of mouse movement
    glm::vec2 mPos = Mouse::GetDisplacement();
    //Compute the look at angles from the mouse movement
    mHorizontalAngle -= mouseSpeed * delta * ( mPos.x );
    mVerticalAngle   -= mouseSpeed * delta * ( mPos.y );
    //Compute the look at direction from the angles
    double Pim1 = Util::Maths::dPIo2 * 0.99999;
    mVerticalAngle = glm::clamp( mVerticalAngle, -Pim1, Pim1 );
    glm::vec3 direction(
        cos( mVerticalAngle ) * sin( mHorizontalAngle ),
        sin( mVerticalAngle ),
        cos( mVerticalAngle ) * cos( mHorizontalAngle )
    );
    glm::vec3 right = glm::vec3(
                          sin( mHorizontalAngle - Util::Maths::fPIo2 ),
                          0,
                          cos( mHorizontalAngle - Util::Maths::fPIo2 )
                      );
    glm::vec3 pos = MatrixControl.Position();

    //Move depending on user keypress
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ) {
        keyboardSpeed *= 3;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) {
        pos += direction * delta * keyboardSpeed;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) {
        pos -= direction * delta * keyboardSpeed;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) {
        pos += right * delta * keyboardSpeed;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) {
        pos -= right * delta * keyboardSpeed;
    }

    //Set the new position and look at
    MatrixControl.SetPosition( pos );
    MatrixControl.SetLookAt( pos + direction );
}