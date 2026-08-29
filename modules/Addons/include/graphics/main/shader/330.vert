R"(
#version 330 core

//in vec3 RG_VERTEX_ARRAY;

//uniform mat4 modelMat = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},viewMat = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
uniform mat4 modelMat,viewMat;
//{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}

layout (location = 0) in vec3 rg_Vertex;
layout (location = 1) in vec4 rg_Color;
layout (location = 2) in vec2 rg_TextureCoord;

out vec4 color;
out vec2 texCoord;

void main()
{
	color = rg_Color;
	texCoord = rg_TextureCoord;
	//vec4 vert = vec4(RG_VERTEX_ARRAY,1);
	gl_Position = vec4(rg_Vertex,1) *modelMat*viewMat;
}
)"