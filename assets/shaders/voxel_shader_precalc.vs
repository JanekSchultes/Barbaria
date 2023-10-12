#version 450 core

layout (location = 0) in uint blockData;
layout (location = 1) in uint blockFaceData;
layout (location = 2) in uint blockVertexData;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 vTexture;

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
   
    gl_Position = projectionMatrix * viewMatrix * vec4(final_position.x, final_position.y, final_position.z, 1.0);
    //gl_Position =  viewMatrix * vec4(final_position.x, final_position.y, final_position.z, 1.0);
}