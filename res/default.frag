#version 330 core
out vec4 FragColor;

in vec3 color;
in vec3 normal;
in vec3 crntPos;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 normal = normalize(normal);
    vec3 lightDir = normalize(lightPos-crntPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    FragColor = vec4(color, 1.0f) * lightColor * diff;
}