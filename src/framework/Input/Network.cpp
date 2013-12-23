#include "Network.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../MatrixManager.hpp"
#include "../Utilities.hpp"

NetworkInput::NetworkInput() : mHorizontalAngle( 4 ), mVerticalAngle( -Util::Maths::fPIo2 )
{
}
NetworkInput::~NetworkInput()
{
}

void NetworkInput::Update()
{
    double Pim1 = Util::Maths::dPIo2 * 0.99999;
    mVerticalAngle = glm::clamp( mVerticalAngle, -Pim1, Pim1 );
    glm::vec3 direction(
        cos( mVerticalAngle ) * sin( mHorizontalAngle ),
        sin( mVerticalAngle ),
        cos( mVerticalAngle ) * cos( mHorizontalAngle )
    );
    glm::vec3 pos = MatrixControl.Position();
    MatrixControl.SetPosition( pos );
    MatrixControl.SetLookAt( pos + direction );
}