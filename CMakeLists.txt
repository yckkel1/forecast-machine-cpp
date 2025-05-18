cmake_minimum_required(VERSION 3.14)
project(ForecastEngine)


# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Debug and Release configs
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include headers from /include
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all .cpp and .hpp files
file(GLOB_RECURSE SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} ${PROJECT_SOURCE_DIR}/main.cpp)
file(GLOB_RECURSE HEADERS "include/*.hpp")
file(GLOB_RECURSE SCRIPTS "scripts/*.sh")

# Group files for Xcode UI organization
source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})
source_group("Bash Scripts" FILES ${SCRIPTS})

# Build the executable
add_executable(forecast_engine ${SOURCES} ${HEADERS} ${SCRIPTS})
