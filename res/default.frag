#version 330 core

in vec3 fragNormal;                  // Interpolated normal from the vertex shader
in vec2 fragTexCoords;               // Interpolated texture coordinates from the vertex shader

out vec4 fragColor;                  // Output color of the fragment

uniform vec3 lightColor;             // Color of the light source
uniform vec3 objectColor;            // Color of the object
uniform sampler2D texture1;          // Texture sampler
uniform bool useTexture;             // Flag to enable/disable texturing

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDirection = normalize(vec3(1.0, 1.0, 1.0));

    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    if (useTexture) {
        vec4 texColor = texture(texture1, fragTexCoords);
        fragColor = vec4(result * texColor.rgb, texColor.a);
    } else {
        fragColor = vec4(result, 1.0);
    }
}