R"(
#version 120

uniform sampler2D tex_2d;
varying vec4 color;

varying vec2 texCoord;

uniform int setTexture;
uniform int ColorSet;

void main()
{
    gl_FragColor = color;

    if(setTexture > 0)
    {
        gl_FragColor *= texture2D(tex_2d, texCoord);
        
        if(ColorSet == 1)
        {
            gl_FragColor.rgb = color.rgb;
        }
    }
}
)"