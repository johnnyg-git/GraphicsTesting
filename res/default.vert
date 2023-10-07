#version 330 core
layout(location = 0) in vec3 inPosition;     // Vertex position
layout(location = 1) in vec3 inNormal;       // Vertex normal
layout(location = 2) in vec2 inTexCoords;    // Texture coordinates

out vec3 fragNormal;                         // Interpolated normal to fragment shader
out vec2 fragTexCoords;                      // Interpolated texture coordinates

uniform mat4 model;                          // Model matrix
uniform mat4 view;                           // View matrix
uniform mat4 projection;                     // Projection matrix

void main() {
    mat4 modelView = view * model;

    gl_Position = projection * modelView * vec4(inPosition, 1.0);

    fragNormal = mat3(transpose(inverse(modelView))) * inNormal;

    fragTexCoords = inTexCoords;
}