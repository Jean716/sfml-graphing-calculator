cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(sfml_graphing_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

option(ENABLE_COVERAGE "Build with gcov coverage instrumentation" OFF)
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES GNU)
    add_compile_options(-fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif()

# ---------------------------------------------------------------------------
# SFML 2.5+ (macOS: brew install sfml@2, Ubuntu/Debian: apt install libsfml-dev)
# Homebrew's keg-only sfml@2 is not on the default search path, so add it.
# ---------------------------------------------------------------------------
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH /opt/homebrew/opt/sfml@2 /usr/local/opt/sfml@2
                                  /opt/homebrew/opt/sfml /usr/local/opt/sfml)
endif()
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# ---------------------------------------------------------------------------
# GoogleTest
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# ---------------------------------------------------------------------------
# Core library: every .cpp under includes/
# ---------------------------------------------------------------------------
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.cpp")
add_library(calculator STATIC ${SOURCE_FILES})
target_include_directories(calculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(calculator PUBLIC sfml-graphics sfml-window sfml-system)
# Absolute path to the bundled font, so the app works from any directory
target_compile_definitions(calculator PRIVATE
    FONT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/DejaVuSans.ttf")

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calculator)

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
add_executable(expression_test _tests/_test_files/expression_test.cpp)
target_link_libraries(expression_test PRIVATE calculator gtest_main)
gtest_discover_tests(expression_test)

add_executable(coord_test _tests/_test_files/coord_test.cpp)
target_link_libraries(coord_test PRIVATE calculator gtest_main)
gtest_discover_tests(coord_test)
