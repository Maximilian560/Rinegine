#pragma once



int now_used_shader_prog = RG_STANDART_SHADER_PROG;
class RG_Material{
  int gl_shader_prog = -1;
public:
  RG_Material(int prog){
    if(prog<0&&RG_D_W_L>=2)RG_Debug::addl(RG_LOG_WARNING,"Material initialized with a negative OpenGL shader value: "+to_string(prog));
    gl_shader_prog = prog;
  }
  RG_Material(RG_Shader shd){
    gl_shader_prog = shd.get_prog();
  }
  RG_Material(){
    gl_shader_prog = RG_STANDART_SHADER_PROG;
  }
  ~RG_Material(){
    if(gl_shader_prog!=RG_STANDART_SHADER_PROG){
      if(glIsProgram(gl_shader_prog))
      if(RG_D_W_L>=4)RG_Debug::addl(RG_LOG_WARNING,"The material has been destroyed but the shader program is still initialized and is not equal to the standard shader program. Shader program handle: "+to_string(gl_shader_prog));
    }
  }

}RG_StandartMaterial;

//RG_D_W_L 0 Without debugging information
//RG_D_W_L 1 Less debugging information
//RG_D_W_L 2 Some debugging information
//RG_D_W_L 3 More debugging information
//RG_D_W_L 4 Much more debugging information