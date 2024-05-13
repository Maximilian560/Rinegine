#pragma once

class RG_Window{
  GLFWwindow* window;
	RG_SettingWindow settings;
  RG_Shader sh;
  bool INIT = false;
public:
  //init

	GLFWwindow*&win(){
		return window;
	}
  void init(RG_SettingWindow& set){


  	settings = set;
  	if(!settings.INIT){
  	  settings.INIT = 1;
  	  settings.FullscreanResolution.x = RG_MainVidmode->width;
  	  settings.FullscreanResolution.y = RG_MainVidmode->height;
  	}
    	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, settings.transparent); //прозрачность окна вкл/откл(по-умол. выкл)
    	glfwWindowHint(GLFW_DECORATED, ((settings.Wtype==RG_Windowed)?1:0));
    	glfwWindowHint(GLFW_CENTER_CURSOR,settings.CenterCursor);
    	glfwWindowHint(GLFW_SAMPLES, settings.MSAA);
      switch(settings.Wtype){
        case RG_Windowed: 
          settings.resolution = settings.WindowResolution;
          window = glfwCreateWindow(
        	  settings.resolution.x, 
        	  settings.resolution.y, 
        	  settings.name.c_str(), 
        	  nullptr, 
        	  nullptr
        	  );
    	  glfwSetWindowPos(window,RG_MainVidmode->width/2.-settings.resolution.x/2. , RG_MainVidmode->height/2.-settings.resolution.y/2.);
        break;
        case RG_Fullscreen:
          settings.resolution = settings.FullscreanResolution;
          window = glfwCreateWindow(
        	  settings.resolution.x, 
        	  settings.resolution.y, 
        	  settings.name.c_str(), 
        	  glfwGetPrimaryMonitor(), 
        	  nullptr
        	  ); break;
        case RG_Borderless:
          settings.resolution.x = RG_MainVidmode->width;
          settings.resolution.y = RG_MainVidmode->height;

          window = glfwCreateWindow(
        	  settings.resolution.x, 
        	  settings.resolution.y,
        	  settings.name.c_str(), 
        	  nullptr, 
        	  nullptr
        	  ); break;
      }

    	
        


    	if (!window)
    	{
        	glfwTerminate();
        	throw(RG_ERROR_WINDOWS_NO_CREATED);
    	}

 		glfwMakeContextCurrent(window);   
		
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);	
  	const GLubyte* TEMPCHAR = glGetString(GL_VERSION);
		int countss = 1;
		RG_OpenGLVersion = 0;
		RG_OpenGLVersionSTR.clear();
		for(int i = 0; i<6;i++){
		RG_OpenGLVersionSTR+=TEMPCHAR[i];
			if(TEMPCHAR[i]>='0'&&TEMPCHAR[i]<='9'){
				RG_OpenGLVersion = RG_OpenGLVersion * 10 + TEMPCHAR[i]-'0';//ТУТ ИЗ СТРОКИ glGetStrung(GL_VERSION) СТОРОКОВОЙ НОМЕР ВЕРСИИ ПРЕОБРАЗОВЫВАЕТСЯ В ЦИФРОВОЙ ВИД, ДОДЕЛАТЬ!! /#NOTE#
			}
		}
		//glEnable(GL_TEXTURE_2D); 	//Разрешить использование текстур
		glEnable(GL_DEPTH_TEST);  	//Проверка глубины
		glEnable(GL_ALPHA_TEST); 	//Разрешить прозрачность 
		glEnable(GL_BLEND); 		//Разрешить смешивание
		glEnable(GL_CULL_FACE); 	//Разрешить обрезание нивидимых обьектов(треугольников)
		glCullFace(GL_BACK);		//Отрезание задних треугольнико
		glFrontFace(GL_CCW);		//Указание на лицевую сторону (против/по часовой стрелки (CW/CCW))
		glDepthFunc(GL_LEQUAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		if(settings.MSAAon)glEnable(GL_MULTISAMPLE);//Сглаживание
		else glDisable(GL_MULTISAMPLE);

		settings.winedit.quotx=settings.resolution.x / RG_MainSizeWindow;
		settings.winedit.quoty=settings.resolution.y / RG_MainSizeWindow;
		
		settings.winedit.difx=settings.resolution.x - RG_MainSizeWindow;
		settings.winedit.dify=settings.resolution.y - RG_MainSizeWindow;
	

		settings.monedit.quotx=RG_MainVidmode->width / RG_MainSizeWindow;
		settings.monedit.quoty=RG_MainVidmode->height / RG_MainSizeWindow;
		
		settings.monedit.difx=RG_MainVidmode->width - RG_MainSizeWindow;
		settings.monedit.dify=RG_MainVidmode->height - RG_MainSizeWindow;
		


	//#ifdef RG_FONT

		//RG_SIZEFONT*=winedit.quotx;

		

	//#endif
		
    GLFWimage icon;
		if(settings.PathToIcon.size()>=1)
    	{
    		icon.pixels = stbi_load(settings.PathToIcon.c_str(), &icon.width, &icon.height, 0, 4);
    	  	glfwSetWindowIcon(window, 1, &icon);
    	  	stbi_image_free(icon.pixels);
    	}

    	glfwSwapInterval(settings.Vsyn); 
    	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);


    //sh.init("data/shaders/Shader.fragrg","data/shaders/Shader.vertrg");

		string sfrag = FileLoad("data/shaders/Shader.fragrg");
		string svert = FileLoad("data/shaders/Shader.vertrg");
		/*if(sfrag == "E6filenofound"||svert=="E6filenofound"){

		}*/
		char* frag ;//= FileLoadToChar("data/shaders/Shader.fragrg");
		char* vert ;//= FileLoadToChar("data/shaders/Shader.vertrg");

		if(sfrag=="E6filenofound"||svert=="E6filenofound"){
//////////////////////////////////////////////////////////
		sfrag.clear();
		svert.clear();
			if(RG_OpenGLVersion>=330){
		sfrag = "\
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
";
//////////////////////////////////////////////////////////////
		svert = "\
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
			}else{
				cout<<"Error, opengl 3.3.0 not support";
			}
			
		}

		RG_StringToChar(frag,sfrag);
		RG_StringToChar(vert,svert);

    sh.init(frag,vert);
		sh.used();
		RG_PREPARE_SHADER();

		/*if(fixPosObj) 
    {
    	rgOrtho(-((double)WindowSize.x/WindowSize.y),((double)WindowSize.x/WindowSize.y),-1,1, -2,2);
    }*/
    //rgOrtho(-((double)settings.resolution.x/settings.resolution.y),((double)settings.resolution.x/settings.resolution.y),-1,1, -2,2);
    //
		//if(settings.resolution.x>settings.resolution.y)rgOrtho(-((double)settings.resolution.x/settings.resolution.y),((double)settings.resolution.x/settings.resolution.y),-1,1, -2,2);
		//else if(settings.resolution.x<settings.resolution.y)rgOrtho(-((double)settings.resolution.y/settings.resolution.x),((double)settings.resolution.y/settings.resolution.x),-1,1, -2,2);
		//else
		rgOrtho(-1,1,-1,1, -2,2);
		
		//////////////////////////////////

		////////////////////OTHER
		rgEnableClientState(RG_VERTEX_ARRAY);
		rgEnableClientState(RG_COLOR_ARRAY);

    	/*if(fixPosObj) rgFrustum
    				((double)-ScaledResolution.x/ScaledResolution.y,(double)ScaledResolution.x/ScaledResolution.y, 
    				(double)-ScaledResolution.y/ScaledResolution.y,(double)ScaledResolution.y/ScaledResolution.y, 1,1024);
*/	



    /*/////////CALLBAKCS
    glfwSetFramebufferSizeCallback(window,RG_Event_Change_ViewPort);RGLogo
		glfwSetMouseButtonCallback(window, RG_MouseEvent);
		glfwSetScrollCallback(window, RG_ScrollEvent);
		//////////////////////////////

		debug.open(DebugPath);

		debug.close();
		glfwSetWindowSizeLimits (window,  320,    240,    GLFW_DONT_CARE,    GLFW_DONT_CARE);




		//SHADER

		char* fshader = FileLoadToChar("Resource/shaders/Shader.fragrg");
		char* vshader = FileLoadToChar("Resource/shaders/Shader.vertrg");

		RG_STANDART_SHADER_PROG = glCreateProgram();
		

		ShaderCompiller(fshader,vshader,RG_STANDART_SHADER_PROG);

		glUseProgram(RG_STANDART_SHADER_PROG);


		free(fshader);
		free(vshader);
		RG_PREPARE_SHADER();
		if(fixPosObj) 
    	{
    	   rgOrtho(-((double)WindowSize.x/WindowSize.y),((double)WindowSize.x/WindowSize.y),-1,1, -2,2);
    	}
    	
		
		//////////////////////////////////

		////////////////////OTHER

		rgEnableClientState(RG_VERTEX_ARRAY);
		rgEnableClientState(RG_COLOR_ARRAY);*/


		RG_StartAnimation();

	}

	void Active_Fullscreen()
	{

		if(settings.Wtype != RG_Windowed)
		{
			settings.Wtype = RG_Windowed;
      settings.resolution.x = settings.WindowResolution.x;
      settings.resolution.y = settings.WindowResolution.y;
			glfwSetWindowAttrib (window, GLFW_DECORATED  , 1);
			glfwSetWindowMonitor (window, nullptr, 0, 0 , (settings.WindowResolution.x)  , (settings.WindowResolution.y)  , GLFW_DONT_CARE );
			//cout<<"Windowed: "<<settings.resolution.x<<" "<<settings.resolution.y<<endl;
			glfwSetWindowPos(window,RG_MainVidmode->width/2.-settings.WindowResolution.x/2. , RG_MainVidmode->height/2.-settings.WindowResolution.y/2.);
		}
		else
		{
			settings.Wtype = RG_Fullscreen;
			settings.resolution.x = settings.FullscreanResolution.x;
      settings.resolution.y = settings.FullscreanResolution.y;

      //settings.resolution = settings.FullscreanResolution;
      //settings.resolution.x = RG_MainVidmode->width;
      //settings.resolution.y = RG_MainVidmode->height;
			glfwSetWindowAttrib (window, GLFW_DECORATED  , 0 );
			//glfwSetWindowMonitor (window, nullptr, 0, 0, RG_MainVidmode->width , RG_MainVidmode->height  , GLFW_DONT_CARE);
			//cout<<"FullScreen res: "<<settings.resolution.x<<" "<<settings.resolution.y<<endl;
			//cout<<"FullScreen full: "<<settings.FullscreanResolution.x<<" "<<settings.FullscreanResolution.y<<endl;
			glfwSetWindowMonitor (window, RG_MainMonitor, 0, 0, settings.FullscreanResolution.x , settings.FullscreanResolution.y  , 60);

		}
	}
	RG_SettingWindow& set(){
		return settings;
	}

	void Using()
	{
		//RG_MainWindowResolution = settings.resolution;
		RG_MainWindow = this;
	}
  ~RG_Window(){
    glfwDestroyWindow(window);
  }
	/*~RG_Window()
	{
	  FT_Done_Face(DefFace);   // Завершение работы с шрифтом face
    FT_Done_FreeType(library); // Завершение работы FreeType
    
    glfwTerminate();
    ///LogError.close();
	}*//**/
	void setVsyn(uint mode)
	{
    	glfwSwapInterval(mode); 
	}


	void RG_StartAnimation();

/////////////////////////
};



void RG_ClearContext(){glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}//TO SHADER /#NOTE#