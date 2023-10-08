#version 330 core

in vec3 fragPos;                     // Position of vertex in world space
in vec3 fragNormal;                  // Interpolated normal from the vertex shader
in vec2 fragTexCoords;               // Interpolated texture coordinates from the vertex shader

out vec4 fragColor;                  // Output color of the fragment

uniform vec3 lightColor;             // Color of the light source
uniform vec3 objectColor;            // Color of the object
uniform vec3 camPos;                 // Position of the camera
uniform sampler2D texture1;          // Texture sampler
uniform bool useTexture;             // Flag to enable/disable texturing

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDirection = normalize(vec3(0.0, 0.0, 1.0));

    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDirection, norm);
    vec3 viewDir = normalize(camPos - fragPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor;


    vec3 result = (ambient + diffuse + specular) * objectColor;

    if (useTexture) {
        vec4 texColor = texture(texture1, fragTexCoords);
        fragColor = vec4(result * texColor.rgb, texColor.a);
    } else {
        fragColor = vec4(result, 1.0);
    }
}