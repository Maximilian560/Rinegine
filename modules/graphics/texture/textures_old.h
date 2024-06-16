#pragma once

struct RG_LoadsTexture{
	int texture = 0;
	string name;

};
RG_Array<RG_LoadsTexture> RG_LoadsTextures;

int RG_GetTexture(string name){
	for(RG_LoadsTexture a:RG_LoadsTextures){
		if(name == a.name)return a.texture;
	}
	/*RG_FOR_CYCLEi(RG_LoadsTextures.size()){
		if(name == RG_LoadsTextures[i].name)return RG_LoadsTextures[i].texture;
	}*/

	return -1;
}




/*struct RG_rawTexture{
  //uint8* raw;
	//RG_Array<uint8>raw;
	
};*/
//RG_Texture RG_CreateTexture(RG_rawTexture);


struct RG_Texture{
  //uint glTexture = 0;
	//RG rawTexture
	struct Raw{
		RG_Matrix<uint8>raw;
  	POINT2D<int>size;
  	int gl_type = GL_TEXTURE_2D;
  	int gl_tx_wrap_s = GL_CLAMP_TO_EDGE;
  	int gl_tx_wrap_t = GL_CLAMP_TO_EDGE;
  	int gl_tx_wrap_r = GL_CLAMP_TO_EDGE;

  	int gl_tx_min_filter = GL_NEAREST;
  	int gl_tx_mag_filter = GL_NEAREST;
  	int gl_gen_minmap = GL_TRUE;

  	int gl_color_channel = GL_RGBA;

		void clear(){
			raw.clear();
		}
	};


	struct Full{
		RG_Matrix<uint8>texture;
		Raw* raw = nullptr;
  	uint id = 0;
		int cnt = 4;
		int gl_type = GL_TEXTURE_2D;
  	POINT2D<int> pos;
  	POINT2D<int> size;
		bool cache = true;

		Full(){
		texture.set_stbi();
		}
		void operator=(Full& a){
			size = a.size;
			//raw = a.raw;
			pos = a.pos;
			cnt = a.cnt;
			id = a.id;
		}
		void operator=(Full& tx){
			switch (tx.gl_color_channel){
			case GL_RGBA:
				//RG_Debug::addl(RG_LOG_DEBUG,"RGBA");
				cnt = 4;
				break;
			case GL_RGB:
				//RG_Debug::addl(RG_LOG_DEBUG,"RGB");
				cnt = 3;
				break;
			case GL_RED:
			case GL_BLUE:
			case GL_GREEN:
			case GL_ALPHA:
				//RG_Debug::addl(RG_LOG_DEBUG,"One Channel");
				cnt = 1;
			  break;
			default:
				RG_Debug::addl(RG_LOG_CRITICAL,"Unknown Color Channel");
				break;
				raw = &tx;
				size = tx.size;
				//texture = tx.raw;
				texture.movefill(size.y,size.x,tx.raw.get());
				//texture.stbi = true;
			}
		}

		void create(Raw&);

		void clear(){
			if(raw!=nullptr)raw->clear();
			texture.clear();
		}
		void del(){
			clear();
			glDeleteTextures(1,&id);
		}
		~RG_Texture(){
			clear();
		}
	};
	

	struct Lite{
		int gl_type = GL_TEXTURE_2D;
  	uint id = 0;
  	POINT2D<int> pos;
  	POINT2D<int> size;
	};

};



void RG_CreateTexture(RG_Texture::Full& txt, RG_Texture::Raw& tx){
	RG_Debug::addl(RG_LOG_INFO,"Try to Create Texture without out(void)");
	RG_TestGLError();
	RG_Debug::addl(RG_LOG_DEBUG,"Texture id before: "+to_string(txt.id));
  glGenTextures(1,&txt.id);
	//tx.raw.print();
	RG_Debug::addl(RG_LOG_DEBUG,"Texture id after: "+to_string(txt.id));
	glBindTexture(tx.gl_type, txt.id);

	//txt.size = tx.size;
	//txt.texture = tx.raw;
	//txt.gl_type = tx.gl_type;
	txt = tx;


	RG_Debug::addl(RG_LOG_DEBUG,"Texture has binded");
			glTexParameteri(tx.gl_type,GL_TEXTURE_WRAP_S,tx.gl_tx_wrap_s);
			glTexParameteri(tx.gl_type,GL_TEXTURE_WRAP_T,tx.gl_tx_wrap_t);
			glTexParameteri(tx.gl_type,GL_TEXTURE_WRAP_R,tx.gl_tx_wrap_r);

			glTexParameteri(tx.gl_type,GL_TEXTURE_MAG_FILTER,tx.gl_tx_mag_filter);
			glTexParameteri(tx.gl_type,GL_TEXTURE_MIN_FILTER,tx.gl_tx_min_filter);
			//glTexParameteri(tx.gl_type, GL_GENERATE_MIPMAP, tx.gl_gen_minmap);
			RG_Debug::addl(RG_LOG_DEBUG,"Texture has setted");
			RG_TestGLError();
			glTexImage2D(tx.gl_type, 0, tx.gl_color_channel, tx.size.x/4, tx.size.y,
										0,tx.gl_color_channel,GL_UNSIGNED_BYTE,tx.raw.get());
	RG_Debug::addl(RG_LOG_DEBUG,"Texture has created");

	

	RG_Debug::addl(RG_LOG_INFO,"Texture Created, id = "+to_string(txt.id));
}


RG_Texture::Lite RG_CreateTexture(RG_Texture::Raw& tx){
	RG_Debug::addl(RG_LOG_WARNING,"There are bugs in this function! Will be fixed soon.");//#FIXME
	RG_Debug::addl(RG_LOG_INFO,"Try to Create Texture with out(RG_Texture)");
	//uint id;
	RG_Texture::Lite txt;
	RG_Debug::addl(RG_LOG_DEBUG,to_string(txt.id));
  glGenTextures(1,&txt.id);
	RG_Debug::addl(RG_LOG_DEBUG,to_string(txt.id));
	glBindTexture(tx.gl_type, txt.id);

			/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);*/

			glTexParameteri(tx.gl_type,GL_TEXTURE_WRAP_S,tx.gl_tx_wrap_s);
			glTexParameteri(tx.gl_type,GL_TEXTURE_WRAP_T,tx.gl_tx_wrap_t);
			glTexParameteri(tx.gl_type,GL_TEXTURE_WRAP_R,tx.gl_tx_wrap_r);

			glTexParameteri(tx.gl_type,GL_TEXTURE_MIN_FILTER,tx.gl_tx_min_filter);
			glTexParameteri(tx.gl_type,GL_TEXTURE_MAG_FILTER,tx.gl_tx_mag_filter);
			glTexParameteri(tx.gl_type, GL_GENERATE_MIPMAP, tx.gl_gen_minmap);

			/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempsize.x, tempsize.y,
										0,GL_RGBA,GL_UNSIGNED_INT,RG_TempStartLogo);*/
				glTexImage2D(tx.gl_type, 0, tx.gl_color_channel, tx.size.x, tx.size.y,
										0,tx.gl_color_channel,GL_UNSIGNED_BYTE,tx.raw.get());

	//txt = tx;
	RG_Debug::addl(RG_LOG_INFO,"Texture Created, id = "+to_string(txt.id));
	return txt;
}


inline void RG_Texture::Lite::create(RG_Texture::Raw& tx){
		RG_CreateTexture(*this,tx);
}

inline void RG_Texture::Full::create(RG_Texture::Raw& tx){
		RG_CreateTexture(*this,tx);
}

/*void RG_stbi_load(RG_Matrix<auto>m,string path){
	m.get()=stbi_load(path,&m.size.x,&m.size.y,0,4);
}*/

void RG_stbi_load(RG_Texture::Raw& m,string path){
	uint8* temp= stbi_load(path.c_str(),&m.size.x,&m.size.y,0,4);
	m.raw.movefill(m.size.x,m.size.y,temp);
}
