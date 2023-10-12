#version 450 core

layout (location = 0) in uint blockData;
layout (location = 1) in uint blockFaceData;
layout (location = 2) in uint blockVertexData;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform float ambientLight;

out vec2 vTexture;
out float vAmbientStrength;

void main() {
    vec3 final_position;
    final_position.x = float((blockData & 0xF));
    final_position.y = float((blockData >> 4) & 0xFF);
    final_position.z = float((blockData >> 12) & 0xF);

    if(((blockData >> 31) & 0x1) == 1) {
        final_position.x -= float((blockData >> 16) & 0x7F) * 16.0;
    } else {
        final_position.x += float((blockData >> 16) & 0x7F) * 16.0;
    }

    if(((blockData >> 30) & 0x1) == 1) {
        final_position.z -= float((blockData >> 23) & 0x7F) * 16.0;
    } else {
        final_position.z += float((blockData >> 23) & 0x7F) * 16.0;
    }

    final_position.x += float(((blockVertexData >> 2) & 0x00000001));
    final_position.y += float(((blockVertexData >> 1) & 0x00000001));
    final_position.z += 1 - (blockVertexData & 0x00000001);

    vec2 texCoord;
    texCoord.x = float((blockFaceData & 0x000000FF) + ((blockVertexData >> 4) & 0x00000001)) * 0.25;
    texCoord.y = 1.0 - float(((blockFaceData >> 8) & 0x000000FF) + 0x1 - ((blockVertexData >> 3) & 0x00000001)) * 0.25;
   
    gl_Position = projectionMatrix * viewMatrix * vec4(final_position.x, final_position.y, final_position.z, 1.0);
    //gl_Position =  viewMatrix * vec4(final_position.x, final_position.y, final_position.z, 1.0);
    vTexture = texCoord;
    vAmbientStrength = ambientLight;
}