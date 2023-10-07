# CMakeList.txt : Top-level CMake project file, do global configuration
cmake_minimum_required (VERSION 3.8)

# Set project name
project ("GraphicsTesting")

# Specify the C++ standard to use (C++ 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Include sub-projects.
add_subdirectory("thirdparty/glad")
add_subdirectory("thirdparty/glfw")
add_subdirectory("thirdparty/glm")
add_subdirectory("thirdparty/assimp")
add_subdirectory("GraphicsTesting")