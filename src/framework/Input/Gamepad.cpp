#include "Gamepad.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../Managers/MatrixManager.hpp"
#include "../Utilities.hpp"
#include "../RuntimeSettings.hpp"

#define DEAD_ZONE 25

Gamepad::Gamepad() : mHorizontalAngle( 4 ), mVerticalAngle( -Util::Maths::fPIo2 )
{
}
Gamepad::~Gamepad()
{
}

bool Gamepad::IsGamepadConnected( int i )
{
    //Checks for connected gamepads
    return sf::Joystick::isConnected( i );
}

void Gamepad::Update()
{
    //Update the internal gamepad state
    sf::Joystick::update();
    float delta = RuntimeSettings::Settings.Delta;
    float lookSpeed = 0.05f;
    float movementSpeed = 50;
    float xAxis = sf::Joystick::getAxisPosition( 0, sf::Joystick::U );
    float yAxis = sf::Joystick::getAxisPosition( 0, sf::Joystick::R );
    //Compute look at angles
    if( xAxis > DEAD_ZONE || xAxis < -DEAD_ZONE ) {
        mHorizontalAngle -= lookSpeed * delta * ( xAxis );
    }

    if( yAxis > DEAD_ZONE || yAxis < -DEAD_ZONE ) {
        mVerticalAngle   -= lookSpeed * delta * ( yAxis );
    }
    //Generate direction from angles
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
    glm::vec3 up = glm::cross( right, direction );
    //Move player
    if ( sf::Joystick::getAxisPosition( 0, sf::Joystick::Y ) < -DEAD_ZONE ) {
        pos += direction * delta * movementSpeed;
    }

    if ( sf::Joystick::getAxisPosition( 0, sf::Joystick::Y ) > DEAD_ZONE ) {
        pos -= direction * delta * movementSpeed;
    }

    if ( sf::Joystick::getAxisPosition( 0, sf::Joystick::X ) > DEAD_ZONE ) {
        pos += right * delta * movementSpeed;
    }

    if ( sf::Joystick::getAxisPosition( 0, sf::Joystick::X ) < -DEAD_ZONE ) {
        pos -= right * delta * movementSpeed;
    }

    if ( sf::Joystick::getAxisPosition( 0, sf::Joystick::Z ) < -DEAD_ZONE ) {
        pos += up * delta * movementSpeed;
    }

    if ( sf::Joystick::getAxisPosition( 0, sf::Joystick::Z ) > DEAD_ZONE ) {
        pos -= up * delta * movementSpeed;
    }
    //set position and look at
    MatrixControl.SetPosition( pos );
    MatrixControl.SetLookAt( pos + direction );
}