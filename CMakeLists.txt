cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(barkeshli_s22)


#. . . . . . . . . . . . . . . . . . . .
include(GNUInstallDirs)
if(MSVC)
    add_compile_options(/W4)
    add_link_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
    # message("compiler: MSVC")
else()
    # message("compiler: NOT MSVC")
    # add_compile_options(-Wall -Wextra -pedantic -Werror -Wl,--fatal-warnings)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})



if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .

# ------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

 
enable_testing() 


# ------------------------------------




#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all cpp files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${INCLUDES_FOLDER}/*.cpp" )

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


ADD_EXECUTABLE(main
    main.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(basic_test
    _tests/_test_files/basic_test.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(testB
    _tests/_test_files/testB.cpp
    ${SOURCE_FILES}
    #- - - - - - - - - - - - - - - - 
)

TARGET_LINK_LIBRARIES(basic_test gtest)
TARGET_LINK_LIBRARIES(testB gtest)

 
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics network audio)

set(SFML_INCLUDE_DIRS "/opt/homebrew/opt/sfml/include")
set(SFML_LIBRARY_DIRS "/opt/homebrew/opt/sfml/lib")

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIRS: ${SFML_INCLUDE_DIRS}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    include_directories(${SFML_INCLUDE_DIRS})
    link_directories(${SFML_LIBRARY_DIRS})
    target_link_libraries(main sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
    target_link_libraries(basic_test sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
    target_link_libraries(testB sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
else()
    message(FATAL_ERROR "SFML not found")
endif()