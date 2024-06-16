#pragma once

/*#if defined(_WIN64)
  #include "../other/GLFW/64/include/GLFW/glfw3.h"
	#include "../other/FreeType/64/include/freetype2/ft2build.h"
	#include FT_FREETYPE_H
	#include "../other/FreeType/64/include/freetype2/freetype/ftoutln.h"
	#include "../other/FreeType/64/include/freetype2/freetype/freetype.h"
#else
  #include "../other/GLFW/32/include/GLFW/glfw3.h"
	#include "../other/FreeType/32/include/freetype2/ft2build.h"
	#include FT_FREETYPE_H
	#include "../other/FreeType/32/include/freetype2/freetype/ftoutln.h"
	#include "../other/FreeType/32/include/freetype2/freetype/freetype.h"
#endif*/



#if defined(_WIN64)
  #include "../other/FreeType/64/include/freetype2/ft2build.h"
	#include FT_FREETYPE_H
	#include "../other/FreeType/64/include/freetype2/freetype/ftoutln.h"
	#include "../other/FreeType/64/include/freetype2/freetype/freetype.h"
#else
  #include "../other/FreeType/32/include/freetype2/ft2build.h"
	#include FT_FREETYPE_H
	#include "../other/FreeType/32/include/freetype2/freetype/ftoutln.h"
	#include "../other/FreeType/32/include/freetype2/freetype/freetype.h"
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
#include "../other/stb_master/stb_image.h"	

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../other/stb_master/stb_image_write.h"	

//POINT2D<uint> RG_MainWindowResolution = {1024,720};



GLFWmonitor* RG_MainMonitor;// = glfwGetPrimaryMonitor();
const GLFWvidmode* RG_MainVidmode;


double RG_Window_Size_Standart = 2000;

class RG_Window;
RG_Window *RG_Window_Standart;


FT_Face DefFace;
FT_Library library;

uint RG_SIZEFONT = 38;


double RG_Render_Distance[2] = {10,10};