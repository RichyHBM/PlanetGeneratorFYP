#include "Keyboard.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../MatrixManager.hpp"
#include "../Utilities.hpp"

#include "Mouse.hpp"

Keyboard::Keyboard() : mHorizontalAngle(4), mVerticalAngle(-Util::Maths::fPIo2)
{

}
Keyboard::~Keyboard()
{

}

void Keyboard::Update()
{
	float delta = 1.0f/60.0f ;
	float mouseSpeed = 0.1f;
    float keyboardSpeed = 50;

	glm::vec2 mPos = Mouse::GetDisplacement();
	mHorizontalAngle -= mouseSpeed * delta * ( mPos.x );
    mVerticalAngle   -= mouseSpeed * delta * ( mPos.y );

    double Pim1 = Util::Maths::dPIo2 * 0.99999;
    mVerticalAngle = glm::clamp(mVerticalAngle, -Pim1, Pim1);

    glm::vec3 direction(
        cos(mVerticalAngle) * sin(mHorizontalAngle),
        sin(mVerticalAngle),
        cos(mVerticalAngle) * cos(mHorizontalAngle)
    );
	
	glm::vec3 right = glm::vec3(
		sin(mHorizontalAngle - Util::Maths::fPIo2),
		0,
		cos(mHorizontalAngle - Util::Maths::fPIo2)
	);

	glm::vec3 pos = MatrixControl.Position();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pos += direction * delta * keyboardSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        pos -= direction * delta * keyboardSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        pos += right * delta * keyboardSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        pos -= right * delta * keyboardSpeed;
    }
	
	MatrixControl.SetPosition(pos);
	MatrixControl.SetLookAt(pos + direction);
}