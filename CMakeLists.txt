cmake_minimum_required(VERSION 3.0)
project(raylibPhysicsEngine)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.c")
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/include/*.h")

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add library directory
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Add raylib from lib/raylib if it’s source-based or already compiled
if (EXISTS "${CMAKE_SOURCE_DIR}/lib/raylib/CMakeLists.txt")
    # If raylib is in source form, add as subdirectory
    add_subdirectory(lib/raylib)
    set(RAYLIB_LIB raylib)
else()
    # If raylib is precompiled, find the library
    find_library(RAYLIB_LIB raylib HINTS ${CMAKE_SOURCE_DIR}/lib)
endif()

# Add your source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} lib/ds.c)

# Link raylib and any other libraries in lib folder
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB})
