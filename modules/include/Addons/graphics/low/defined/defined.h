#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/low/def"

#if defined(_WIN64)
  #include "../../../other/FreeType/64/include/freetype2/ft2build.h"
	#include FT_FREETYPE_H
	#include "../../../other/FreeType/64/include/freetype2/freetype/ftoutln.h"
	#include "../../../other/FreeType/64/include/freetype2/freetype/freetype.h"
#else
  #include "../../../other/FreeType/32/include/freetype2/ft2build.h"
	#include FT_FREETYPE_H
	#include "../../../other/FreeType/32/include/freetype2/freetype/ftoutln.h"
	#include "../../../other/FreeType/32/include/freetype2/freetype/freetype.h"
#endif


#include <glad/glad.h>
#include <GLFW/glfw3.h>



#if defined(GLFW_EXPOSE_NATIVE_WIN32)
		#include <GLFW/glfw3native.h>
#endif
#define RG_DEF_WINOS
//#include <freetype2/ft2build.h>
//#include FT_FREETYPE_H
//#include <freetype2/freetype/ftoutln.h>
//#include <freetype2/freetype/freetype.h>

#define STB_IMAGE_IMPLEMENTATION	
#include "../../../other/stb_master/stb_image.h"	

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../other/stb_master/stb_image_write.h"	

#include "../../../other/stb_master/stb_vorbis.c"	
//POINT2D<uint> RG_MainWindowResolution = {1024,720};



GLFWmonitor* RG_MainMonitor;// = glfwGetPrimaryMonitor();
const GLFWvidmode* RG_MainVidmode;


double RG_Window_Virtual = 2000;
double RG_Window_Size_Standart = RG_Window_Virtual;//!\\ DO NOT USING //!\\

namespace RG_Events{

	POINT2D<uint> WinPos = {0,0};
}
class RG_Window;

RG_Window *RG_Window_Standart;


FT_Face DefFace;
FT_Library library;

uint RG_FONT_SIZE = 38;


double RG_Render_Distance2D[2] = {100000,100000};
double RG_Render_Distance3D[2] = {1,100000};

int RG_OpenGLVersion = 200;
string RG_OpenGLVersionSTR = "2.0.0";


