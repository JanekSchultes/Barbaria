#version 450 core

out vec4 fragmentColor;

layout(binding = 0) uniform sampler2D gameTexture;

in vec2 vTexture;
in float vAmbientStrength;  

void main() {
    vec4 light = vec4(vAmbientStrength * vec3(1.0, 1.0, 1.0), 1.0);
    //vec4 light = vec4(vAmbientStrength * vec3(0.1, 0.4, 0.8), 1.0);
    fragmentColor = texture(gameTexture, vTexture);
}