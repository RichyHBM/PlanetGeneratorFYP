#include "Gamepad.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../MatrixManager.hpp"
#include "../Utilities.hpp"


#define DEAD_ZONE 25

Gamepad::Gamepad() : mHorizontalAngle( 4 ), mVerticalAngle( -Util::Maths::fPIo2 )
{
}
Gamepad::~Gamepad()
{
}

bool Gamepad::IsGamepadConnected(int i)
{
    return sf::Joystick::isConnected( i );
}

void Gamepad::Update()
{
    sf::Joystick::update();
    float delta = 1.0f/60.0f ;
    float lookSpeed = 0.05f;
    float movementSpeed = 50;
    float xAxis = sf::Joystick::getAxisPosition( 0, sf::Joystick::U );
    float yAxis = sf::Joystick::getAxisPosition( 0, sf::Joystick::R );

    if( xAxis > DEAD_ZONE || xAxis < -DEAD_ZONE ) {
        mHorizontalAngle -= lookSpeed * delta * ( xAxis );
    }

    if( yAxis > DEAD_ZONE || yAxis < -DEAD_ZONE ) {
        mVerticalAngle   -= lookSpeed * delta * ( yAxis );
    }

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

    MatrixControl.SetPosition( pos );
    MatrixControl.SetLookAt( pos + direction );
}