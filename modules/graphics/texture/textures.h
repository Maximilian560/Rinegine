#pragma once

//class RG_Texture{
//
//public:
namespace RG_Texture{
  struct Raw{
		RG_Matrix<uint8>raw;
  	POINT2D<int>size;
    int cnt = 4;

    void del(){
      raw.clear();
    }
    ~Raw(){
      del();
    }
    Raw(){};
    Raw(string path){load(path);}
    void load(string path){
      uint8* temp = stbi_load(path.c_str(),&size.x,&size.y,&cnt,0);
      raw.movefill(size.x*4,size.y,temp);
    }

  };


  
  struct GL_Settings{
    int gl_type = GL_TEXTURE_2D;
  	int gl_tx_wrap_s = GL_CLAMP_TO_EDGE;
  	int gl_tx_wrap_t = GL_CLAMP_TO_EDGE;
  	int gl_tx_wrap_r = GL_CLAMP_TO_EDGE;

  	int gl_tx_min_filter = GL_NEAREST;
  	int gl_tx_mag_filter = GL_NEAREST;
  	int gl_gen_minmap = GL_TRUE;

  	int gl_color_channel = GL_RGBA;
  };

  struct GL_Raw :public GL_Settings, public Raw{};
  
  struct Lite{
    POINT2D<int> pos;
    POINT2D<int> size;
  };

  struct Standart: public Raw{
    POINT2D<int> pos;
    uint gl_id = -1;
    int gl_type = GL_TEXTURE_2D;
		int cnt = 4;
    Standart(string path):Raw(path){};
    Standart(){};

  };

  struct Atlas: public Raw{
    uint gl_id = -1;
    int gl_type = GL_TEXTURE_2D;
		int cnt = 4;
  };
 
  struct Full : public Standart, public GL_Settings{
    int gl_type = Standart::gl_type;
    Full(string path):Standart(path){};
    Full(){};
    void Create(){
      glGenTextures(1,&gl_id);
      glBindTexture(gl_type, gl_id);

		    glTexParameteri(gl_type,GL_TEXTURE_WRAP_S,gl_tx_wrap_s);
		    glTexParameteri(gl_type,GL_TEXTURE_WRAP_T,gl_tx_wrap_t);
		    glTexParameteri(gl_type,GL_TEXTURE_WRAP_R,gl_tx_wrap_r);

		    glTexParameteri(gl_type,GL_TEXTURE_MIN_FILTER,gl_tx_min_filter);
		    glTexParameteri(gl_type,GL_TEXTURE_MAG_FILTER,gl_tx_mag_filter);
		    glTexParameteri(gl_type,GL_GENERATE_MIPMAP, gl_gen_minmap);

				glTexImage2D(gl_type, 0, gl_color_channel, size.x, size.y,
										0,gl_color_channel,GL_UNSIGNED_BYTE,raw.get());

    }
    void del(){
      Raw::del();
      glDeleteTextures(1,&gl_id);
    }

    ~Full(){
      del();
    }
  };



};