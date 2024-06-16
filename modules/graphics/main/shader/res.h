#pragma once

string RG_StandartFragmentShader330 = "\
#version 330 core\n\
\n\
uniform sampler2D tex_2d;\n\
in vec4 color;\n\
\n\
in vec2 texCoord;\n\
\n\
out vec4 Frag;\n\
\n\
uniform int setTexture;\n\
uniform int ColorSet;\n\
\n\
void main()\n\
{\n\
    Frag = color;\n\
\n\
   	if(setTexture > 0)\n\
   	{\n\
   		Frag *= vec4(texture(tex_2d, texCoord));\n\
   	    \n\
   		if(ColorSet == 1)\n\
   		{\n\
            Frag.rgb = color.rgb;\n\
        }\n\
   	}\n\
}\n\
",
RG_StandartVertexShader330 = "\
#version 330 core\n\
\n\
//in vec3 RG_VERTEX_ARRAY;\n\
\n\
uniform mat4 projMat = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},viewMat = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};\n\
//{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}\n\
\n\
layout (location = 0) in vec3 rg_Vertex;\n\
layout (location = 1) in vec4 rg_Color;\n\
layout (location = 2) in vec2 rg_TextureCoord;\n\
\n\
out vec4 color;\n\
out vec2 texCoord;\n\
\n\
void main()\n\
{\n\
	color = rg_Color;\n\
	texCoord = rg_TextureCoord;\n\
	//vec4 vert = vec4(RG_VERTEX_ARRAY,1);\n\
	gl_Position = vec4(rg_Vertex,1) *projMat*viewMat;\n\
}\n\
";