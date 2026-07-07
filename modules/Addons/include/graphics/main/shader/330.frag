R"(
  #version 330 core
  
  uniform sampler2D tex_2d;
  in vec4 color;
  
  in vec2 texCoord;
  
  out vec4 Frag;
  
  uniform int setTexture;
  uniform int ColorSet;
  
  void main()
  {
    Frag = color;
  
    if(setTexture > 0)
    {
       Frag *= texture(tex_2d, texCoord);
           
         /*if(ColorSet == 1)
         {
              Frag.rgb = color.rgb;
          }*/
    }
  }
)"
