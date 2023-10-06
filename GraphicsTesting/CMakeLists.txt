# CMakeList.txt : CMake project for GraphicsTesting, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GraphicsTesting "Application.cpp"  "Window.h" "Window.cpp" "VertexBuffer.h" "VertexBuffer.cpp"  "ElementBuffer.cpp" "ElementBuffer.h" "Shader.h" "Shader.cpp" "VertexArray.h" "VertexArray.cpp" "Camera.h" "Camera.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphicsTesting PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(GraphicsTesting glfw)
target_link_libraries(GraphicsTesting glad)
target_link_libraries(GraphicsTesting glm)
target_link_libraries(GraphicsTesting assimp)

set_property(
        TARGET GraphicsTesting
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES  $<TARGET_FILE_DIR:GraphicsTesting>/res
)

add_custom_command(TARGET GraphicsTesting PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:GraphicsTesting>/res)
