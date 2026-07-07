R"(
#version 120

uniform mat4 modelMat;
uniform mat4 viewMat;

attribute vec3 rg_Vertex;
attribute vec4 rg_Color;
attribute vec2 rg_TextureCoord;

varying vec4 color;
varying vec2 texCoord;

void main(){
    color = rg_Color;
    texCoord = rg_TextureCoord;
    gl_Position = modelMat * viewMat * vec4(rg_Vertex, 1.0);
}
)"