#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>

#include "UtilitiesTests.hpp"

int main( int argc, char* const argv[] )
{
	Catch::Session session;
	Catch::ConfigData config;

	config.reporterName = "junit";

	session.useConfigData(config);
	int s = session.run();

	return s;
}