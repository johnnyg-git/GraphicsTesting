# CMakeList.txt : CMake project for GraphicsTesting, include source and define

# Add source to this project's executable.
add_executable (GraphicsTesting "Main.cpp" "Renderer/Renderer.h" "Renderer/Window.h" "Renderer/Window.cpp"   "Renderer/Shader.h" "Renderer/Shader.cpp" "Renderer/Mesh.h" "Renderer/Mesh.cpp" "Renderer/VertexArray.h" "Renderer/VertexArray.cpp" "Renderer/VertexBuffer.h" "Renderer/VertexBuffer.cpp" "Renderer/ElementBuffer.h" "Renderer/ElementBuffer.cpp")

target_link_libraries(GraphicsTesting glfw)
target_link_libraries(GraphicsTesting glad)
target_link_libraries(GraphicsTesting glm)
target_link_libraries(GraphicsTesting assimp)

# Clean the res folder
set_property(
        TARGET GraphicsTesting
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES  $<TARGET_FILE_DIR:GraphicsTesting>/res
)

# Copy the res folder to the build directory
add_custom_command(TARGET GraphicsTesting PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:GraphicsTesting>/res)
