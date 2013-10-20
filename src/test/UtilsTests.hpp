#include "framework/Utilities.hpp"
#include "catch.hpp"

TEST_CASE( "Testing Utilities ToString" )
{
    REQUIRE( "5" == Util::ToString( 5 ) );
    REQUIRE( "24323432423141" == Util::ToString( 24323432423141 ) );
    REQUIRE( "Hello" == Util::ToString( "Hello" ) );
    REQUIRE( "0" == Util::ToString( false ) );
    REQUIRE( "0.432" == Util::ToString( 0.432 ) );
    REQUIRE( "0.432" == Util::ToString( 0.432f ) );
}

TEST_CASE( "Testing Utilities ToString with precision" )
{
    REQUIRE( "5.00" == Util::ToString( 5.0f, 2 ) );
    REQUIRE( "24323.43" == Util::ToString( 24323.432423141f, 2 ) );
    REQUIRE( "0" == Util::ToString( 0, 0 ) );
    REQUIRE( "0.432" == Util::ToString( 0.432f, 3 ) );
    REQUIRE( "0.4" == Util::ToString( 0.4322123123f, 1 ) );
}

TEST_CASE( "Testing Utilities MaxValue" )
{
    REQUIRE( 23 == Util::MaxValue( 5, 23 ) );
    REQUIRE( 23 == Util::MaxValue( 23, 5 ) );
    REQUIRE( 142.0 == Util::MaxValue( 142.0, 0.52 ) );
    REQUIRE( 0.8f == Util::MaxValue( 0.5f, 0.8f ) );
    REQUIRE( 0.00011 == Util::MaxValue( 0.0001, 0.00011 ) );
    REQUIRE( 5 == Util::MaxValue( 5, 5 ) );
}

TEST_CASE( "Testing Utilities MinValue" )
{
    REQUIRE( 5 == Util::MinValue( 5, 23 ) );
    REQUIRE( 5 == Util::MinValue( 23, 5 ) );
    REQUIRE( 0.52 == Util::MinValue( 142.0, 0.52 ) );
    REQUIRE( 0.5f == Util::MinValue( 0.5f, 0.8f ) );
    REQUIRE( 0.0001 == Util::MinValue( 0.0001, 0.00011 ) );
    REQUIRE( 5 == Util::MinValue( 5, 5 ) );
}

TEST_CASE( "Testing Utilities Clamp" )
{
    REQUIRE( 5 == Util::Clamp( 3, 5, 23 ) );
    REQUIRE( 23 == Util::Clamp( 25, 5, 23 ) );
    REQUIRE( 0.52 == Util::Clamp( 0.52, 0.5, 0.8 ) );
    REQUIRE( 0.8f == Util::Clamp( 0.5f, 0.8f, 0.9f ) );
    REQUIRE( 0.0001 == Util::Clamp( 0.0001, 0.00001, 0.0002 ) );
    REQUIRE( 5 == Util::Clamp( 5, 5, 5 ) );
}