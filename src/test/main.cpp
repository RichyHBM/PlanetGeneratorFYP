#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>

#include "UtilsTests.hpp"

int main( int argc, char *const argv[] )
{
    Catch::Session session;
	Catch::ConfigData config;
    config.showDurations = Catch::ShowDurations::DefaultForReporter;
#ifndef WIN32
    config.showSuccessfulTests = true;
    config.reporterName = "junit";
    config.outputFilename = "testreport.xml";
#endif
	session.useConfigData( config );
    int s = session.run();
#ifdef	WIN32
	std::cin.get();
#endif
    return s;
}