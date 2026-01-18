cmake_minimum_required(VERSION 3.15)

project(cpp_example CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        endstone
        GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
        GIT_TAG v0.10 # TODO: CHANGE ME to the actual version you are using
)
FetchContent_MakeAvailable(endstone)

endstone_add_plugin(${PROJECT_NAME} src/example_plugin.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
