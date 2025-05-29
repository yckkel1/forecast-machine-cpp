#include "forecast_runner.hpp"

int main(int argc, const char * argv[]) {
    // dynamically load csv on command line
    ForecastRunner runner;
    runner.run(argc, argv);
    
    return 0;
}

