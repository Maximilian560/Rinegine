#pragma once



class RG_Atlas : private RG_Texture::Atlas{
  int gl_type = GL_TEXTURE_2D;
  uint gl_id = UINT_MAX;
  RG_Array<RG_Texture::Standart> Textures;
  //RG_Array<RG_Texture::Lite> Textures;
  RG_Array<string>names;
  RG_Array<string>paths;

public:
  //

  void Init(initializer_list<string> path, initializer_list<string> name){
    //paths.fill(path.begin(),path.size());
    //names.fill(name.begin(),name.size());
    paths.fill(path);
    names.fill(name);
  }
  void Init(RG_Array <string> path, RG_Array<string> name){
    paths = path;
    names = name;
  }
  void Add(string path, string name){
    paths.push_back(path);
    names.push_back(name);
  }
  void Add(initializer_list<string> path, initializer_list<string> name){
    paths.push_back(path);
    names.push_back(name);
  }

  void Add(RG_Array <string> path, RG_Array<string> name){
    paths.push_back(path);
    names.push_back(name);
  }

  //void Add()

  void Gen(){
    //if(names.size()==0||paths.size()==0)RG_Debug::addl(RG_LOG_CRITICAL,"Error generating atlas, names or paths to textures were not found.");
    if(names.size()!=paths.size())RG_Debug::addl(RG_LOG_CRITICAL,"Atlas generation error, number of textures and their paths do not match.");
    if(names.size()==0||paths.size()==0)return;//RG_Debug::addl(RG_LOG_CRITICAL,"Error generating atlas, names or paths to textures were not found.");
    
    /*Textures.resize(1);
    Textures[0].load(paths[0]);
    raw.init(Textures[0].raw);
    size = {48,64};*/


    //raw.resize();
    
    
    
    Textures.resize(paths.size());
    POINT2D<int>max_size;
    POINT2D<int>max_one_size;
    POINT2D<int>end_size;
    for(int i = 0; i<paths.size();i++){
      Textures[i].load(paths[i]);
    }
    //Textures[0].raw.print();
    Textures.resize(paths.size());
    //raw = Textures[0].raw;
    //Textures[0].pos.x = 0;
    //Textures[0].pos.y = 0;

    for(RG_Texture::Standart& tex:Textures){
      max_size.x+=tex.size.x;
      max_size.y+=tex.size.y;
      if(tex.size.x>max_one_size.x) max_one_size.x = tex.size.x;
      if(tex.size.y>max_one_size.y) max_one_size.y = tex.size.y;
    }
    while(end_size.x<max_size.x){
    	end_size.x+=1024*4;
    }
    while(end_size.y<max_size.y){
    	end_size.y+=1024;
    }

    raw.resize(end_size.x,end_size.y);
    size.x = end_size.x/4.;
    size.y = end_size.y;
    cnt = 4;

    POINT2D<int>pen;
    POINT2D<int>max;


    //raw.place({0,0},Textures[0].raw);

    for(RG_Texture::Standart& texture:Textures){
      if(pen.x+texture.size.x>end_size.x){
    		if(pen.y+max.y+1>end_size.y){RG_Debug::addl(RG_LOG_CRITICAL,"Error gen atlas, size pen.y > end_size.y; end_size.y '"+to_string(end_size.y)+"' texture.size '"+to_string(texture.size.y)+"'");};
        pen.x = 0;
        pen.y+=max.y+1;
        max.y = 0;
      }
      raw.place({pen.x,pen.y},texture.raw);

      texture.pos.x = pen.x/4;
    	texture.pos.y = pen.y;
    	pen.x+=texture.size.x;
    	max.y = rg_max(texture.size.y,max.y);


    }

    glGenTextures(1,&gl_id);

    glBindTexture(GL_TEXTURE_2D, gl_id);

    		/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);*/

    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y,
    									0, GL_RGBA, GL_UNSIGNED_BYTE, raw.get_mat());
    //raw.print();
    stbi_write_png("atlas.png",size.x,size.y,4,raw.get_mat(),0);
    RG_Debug::addl(RG_LOG_INFO,"Atlas successfully generated");
  }

  uint get_id(){
    return gl_id;
  }

  RG_Texture::Standart& operator[](int i){
    return Textures[i];
  }
  POINT2D<int> get_size(){
    return size;
  }
  int operator[](string name){
    for(int i = 0; i<names.size();i++){
      if(names[i]==name)return i;
    }
    RG_Debug::addl(RG_LOG_ERROR,"Atlas not found texture '"+name+"'");
    return -1;
  }
  int find(string name) {
    for(int i = 0; i<names.size();i++){
      if(names[i]==name)return i;
    }
    RG_Debug::addl(RG_LOG_ERROR,"Atlas not found texture '"+name+"'");
    return -1;
  }

}RG_Atlas_Standart;

//RG_Atlas *RG_Atlas_pStandart = &RG_Atlas_Standart;



class RG_Mods{
  inline static bool textures = true;

public:
  static void Texture_On(){
    if(textures){
      //RG_Debug::addl(RG_LOG_INFO,"Atlas already on");
      return;
    };
    if(RG_Atlas_Standart.get_id()==-1){
      RG_Debug::addl(RG_LOG_CRITICAL,"Atlas not prepare");
    }
    textures = 1;
  	rgEnableClientState(RG_TEXTURE_COORD_ARRAY);
  	rgBindTexture(RG_Atlas_Standart.get_id());
  }

  static void Texture_Off(){
    if(!textures){
      //RG_Debug::addl(RG_LOG_INFO,"Atlas already off");
      return;
    }
    textures = 0;
  	rgDisableClientState(RG_TEXTURE_COORD_ARRAY);
  	glBindBuffer(GL_ARRAY_BUFFER,0);
  	rgBindTexture(0);
  }
};


