#pragma once

#include <string>

namespace constants {
    inline constexpr const char* TRUE_VAL = "true";
    inline constexpr const char* FALSE_VAL = "false";
    inline constexpr const char* DEFAULT_ALPHA = "0.3";
    inline constexpr const char* DEFAULT_TRAIN_RATIO = "0.8";
    inline constexpr const char* DEFAULT_STEPS_AHEAD = "10";
    inline constexpr const char* OUTPUT_DIR = "output/";
    inline constexpr const char* ALPHA = "alpha";
    inline constexpr const char* STEPS_AHEAD = "steps_ahead";
    inline constexpr const char* TRAIN_RATIO = "train_ratio";
    inline constexpr const char* INPUT_FILE_PATH = "input_file_path";
    inline constexpr const char* METHOD = "method";
    namespace operations {
        inline constexpr const char* FORECAST = "forecast";
        inline constexpr const char* EVALUATE = "evaluate";
    }
    namespace models {
        inline constexpr const char* MEAN = "mean";
        inline constexpr const char* EWMA = "ewma";
        inline constexpr const char* LINEAR = "linear";
    }
}
