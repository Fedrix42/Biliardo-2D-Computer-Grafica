cmake_minimum_required(VERSION 4.0)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "Minimum policy version for all subprojects")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(common INTERFACE)
target_compile_features(common INTERFACE cxx_std_17)
target_compile_options(common INTERFACE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

file(GLOB_RECURSE SRC_TAPPA01 CONFIGURE_DEPENDS Tappa01/*.cpp)
add_executable(Tappa01 ${SRC_TAPPA01})
target_link_libraries(Tappa01 PRIVATE SFML::Graphics common)


file(GLOB_RECURSE SRC_TAPPA02 CONFIGURE_DEPENDS Tappa02/*.cpp)
add_executable(Tappa02 ${SRC_TAPPA02})
target_link_libraries(Tappa02 PRIVATE SFML::Graphics common)

file(GLOB_RECURSE SRC_TAPPA03 CONFIGURE_DEPENDS Tappa03/*.cpp)
add_executable(Tappa03 ${SRC_TAPPA03})
target_link_libraries(Tappa03 PRIVATE SFML::Graphics common)

file(GLOB_RECURSE SRC_TAPPA04 CONFIGURE_DEPENDS Tappa04/*.cpp)
add_executable(Tappa04 ${SRC_TAPPA04})
target_link_libraries(Tappa04 PRIVATE SFML::Graphics common)

