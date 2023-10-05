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
    float ambientStrength = 0.05f;
    vec3 Normal = normalize(normal);
    vec3 lightDir = normalize(lightPos-crntPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    float specStrength = 1.0f;
    vec3 viewDir = normalize(cameraPos - crntPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
    float specular = specAmount*specStrength;

    FragColor = vec4(color, 1.0f) * lightColor * (diff +  specular + ambientStrength);
}