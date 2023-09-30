# CMakeList.txt : CMake project for GraphicsTesting, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GraphicsTesting "GraphicsTesting.cpp" "GraphicsTesting.h"   "Window.h" "Window.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphicsTesting PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_include_directories(GraphicsTesting PRIVATE "include")
target_link_libraries(GraphicsTesting glfw)
target_link_libraries(GraphicsTesting glad)
target_link_libraries(GraphicsTesting glm)