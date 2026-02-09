#pragma once

string /*RG_EXPStandartFragmentShader330 = "\
#version 330 core\n\
\n\
in vec4 fragColor;\n\
in vec2 texCoord;\n\
in vec3 normal;\n\
in vec3 lightDirFrag;\n\
\n\
uniform sampler2D tex_2d;\n\
uniform vec3 lightColor;\n\
uniform vec3 ambientColor;\n\
uniform float ambientStrength;\n\
uniform int setTexture;\n\
uniform int rg_ColorSet;\n\
\n\
out vec4 Frag;\n\
\n\
void main()\n\
{\n\
    vec3 norm = normalize(normal);\n\
    vec3 lightDir = normalize(-lightDirFrag); // Направление света (инвертируем)\n\
\n\
    // Диффузное освещение\n\
    float diff = max(dot(norm, lightDir), 0.0);\n\
    vec3 diffuse = diff * lightColor;\n\
\n\
    // Амбиентное освещение\n\
    vec3 ambient = ambientStrength * ambientColor;\n\
\n\
    // Общий цвет\n\
    vec4 textureColor = texture(tex_2d, texCoord);\n\
    vec3 finalColor = (ambient + diffuse) * fragColor.rgb;\n\
\n\
    if (setTexture > 0) {\n\
        finalColor *= textureColor.rgb;\n\
        if (rg_ColorSet == 1) {\n\
            finalColor = fragColor.rgb;\n\
        }\n\
    }\n\
    Frag = vec4(finalColor, fragColor.a * textureColor.a);\n\
}\n\
",
RG_EXPStandartVertexShader330 = "\
#version 330 core\n\
\n\
layout (location = 0) in vec3 rg_Vertex;\n\
layout (location = 1) in vec4 rg_Color;\n\
layout (location = 2) in vec2 rg_TextureCoord;\n\
layout (location = 3) in vec3 rg_Normal;\n\
\n\
uniform mat4 projMat = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}, viewMat = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};\n\
uniform mat4 modelMat;\n\
uniform vec3 lightDir;\n\
\n\
out vec4 fragColor;\n\
out vec2 texCoord;\n\
out vec3 normal;\n\
out vec3 lightDirFrag;\n\
\n\
void main()\n\
{\n\
    fragColor = rg_Color;\n\
    texCoord = rg_TextureCoord;\n\
    normal = mat3(transpose(inverse(modelMat))) * rg_Normal;  // Трансформируем нормаль\n\
    lightDirFrag = lightDir;\n\
    gl_Position = projMat * viewMat * modelMat * vec4(rg_Vertex, 1.0);\n\
}\n\
",*/


RG_StandartFragmentShader330 = 
#include "330.frag"
,
RG_StandartVertexShader330 = 
#include "330.vert"
,

RG_StandartFragmentShader220 = 
#include "220.frag"
,
RG_StandartVertexShader220 = 
#include "220.vert"
,
RG_StandartPostProcessShader330 =
#include "post330.frag"
;
