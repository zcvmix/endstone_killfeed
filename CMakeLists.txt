cmake_minimum_required(VERSION 3.15)

project(killfeed CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        endstone
        GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
        GIT_TAG v0.10.18
)
FetchContent_MakeAvailable(endstone)

endstone_add_plugin(${PROJECT_NAME} src/killfeed.cpp)
