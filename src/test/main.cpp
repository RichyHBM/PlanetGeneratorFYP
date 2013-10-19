#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>

#include "UtilsTests.hpp"

int main( int argc, char *const argv[] )
{
    Catch::Session session;
    Catch::ConfigData config;
    config.showDurations = Catch::ShowDurations::DefaultForReporter;
    config.showSuccessfulTests = true;
    config.reporterName = "junit";
    config.outputFilename = "testreport.xml";
    session.useConfigData( config );
    int s = session.run();
    return s;
}