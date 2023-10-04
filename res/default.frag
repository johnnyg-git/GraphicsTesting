#version 330 core
out vec4 FragColor;

in vec3 color;
in vec3 normal;
in vec3 crntPos;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    vec3 normal = normalize(normal);
    vec3 lightDir = normalize(lightPos-crntPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    float specStrength = 0.5f;
    vec3 viewDir = normalize(cameraPos - crntPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 8);
    float specular = specAmount*specStrength;

    FragColor = vec4(color, 1.0f) * lightColor * (diff+specular);
}