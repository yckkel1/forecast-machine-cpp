#pragma once

#include <string>
#include <set>

namespace constants {
    inline constexpr const char* TRUE_VAL = "true";
    inline constexpr const char* FALSE_VAL = "false";
    inline constexpr const char* OUTPUT_DIR = "output/";
    inline constexpr const char* QUERIES_DIR = "queries/";
    inline constexpr const char* SCHEMAS_DIR = "schemas/";

    inline constexpr const char* DEFAULT_ALPHA = "0.3";
    inline constexpr const double DEFAULT_ALPHA_FLOOR = 0.0;
    inline constexpr const double DEFAULT_ALPHA_CEILING = 1.0;
    inline constexpr const char* DEFAULT_BETA = "0.3";
    inline constexpr const double DEFAULT_BETA_FLOOR = 0.0;
    inline constexpr const double DEFAULT_BETA_CEILING = 1.0;
    inline constexpr const char* DEFAULT_TRAIN_RATIO = "0.8";
    inline constexpr const double DEFAULT_TRAIN_RATIO_FLOOR = 0.0;
    inline constexpr const double DEFAULT_TRAIN_RATIO_CEILING = 1.0;
    inline constexpr const char* DEFAULT_STEPS_AHEAD = "10";
    inline constexpr const int DEFAULT_STEPS_AHEAD_FLOOR = 1;
    inline constexpr const int DEFAULT_STEPS_AHEAD_CEILING = 100;
    
    namespace params {
        inline constexpr const char* ALPHA = "alpha";
        inline constexpr const char* BETA = "beta";
        inline constexpr const char* STEPS_AHEAD = "steps_ahead";
        inline constexpr const char* TRAIN_RATIO = "train_ratio";
        inline constexpr const char* INPUT_FILE_PATH = "input_file_path";
        inline constexpr const char* METHOD = "method";
        inline const std::set<std::string> ALL_PARAMS = {
            ALPHA, BETA, STEPS_AHEAD, TRAIN_RATIO, INPUT_FILE_PATH, METHOD
        };
    }

    namespace operations {
        inline constexpr const char* FORECAST = "forecast";
        inline constexpr const char* EVALUATE = "evaluate";
        inline const std::set<std::string> ALL_OPERATIONS = {
            FORECAST, EVALUATE
        };
    }

    namespace methods {
        inline constexpr const char* MEAN = "mean";
        inline constexpr const char* EWMA = "ewma";
        inline constexpr const char* LINEAR = "linear";
        inline constexpr const char* HOLT = "holt";
        inline const std::set<std::string> ALL_METHODS = {
            MEAN, EWMA, LINEAR, HOLT
        };
    }

    namespace tickers {
        namespace index {
            inline constexpr const char* SPY = "spy";
            inline constexpr const char* NDQ = "ndq";
        }
        inline const std::unordered_map<std::string, std::string> PATHS = {
            {index::SPY, "selectSpyDataByDateRanges.sql"},
            {index::NDQ, "selectNdqDataByDateRanges.sql"}
        };
    }
}
