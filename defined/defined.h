#pragma once

#include <cmath> 
#include <string>
#include <thread>
#include <vector>

#include <iostream>
#include <fstream>

#include <filesystem>
#include <malloc.h>	

//#include <type_traits>

#include "../other/glad/include/glad/glad.h"

#if defined(_WIN64)
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
#endif

#define STB_IMAGE_IMPLEMENTATION	
#include "../other/stb_master/stb_image.h"	

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../other/stb_master/stb_image_write.h"	


#include "../other/MyLibs/Noise.h"//Моя библиотека, не используется




#include <windows.h>




//#include "../other/FreeType/64/include/freetype2/freetype/ftoutln.h"
//#include "../other/FreeType/64/include/freetype2/freetype/freetype.h"




//////////////ОБЪЯВЛЕНИЕ ВАЖНЫХ ТИПОВ ДАННЫХ
using namespace std;


typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef __int16 int16;
typedef long int lint;
typedef long unsigned int luint;

ofstream debug;

string DebugPath = "Logs/log.txt";
void DebugAdd(string text)
{
	debug.open(DebugPath,ios::app);
	debug<<text;
	debug.close();
	return;
}

uint prog;//шейдеры?
//переменные для шейдера(их позиции(сделать всё в отдельный класс для работы как с материалами))
int SHDsetTexture;
int SHDisCube;
int SHDface;
int SHDcounter = 0;
int SHDlocation = 0;

#define RG_CATCH_ERROR 	try
#define RG_ERROR_LOG 	catch(ErrorRinegine error)\
						{\
							DebugAdd("Error: ");\
							switch(error)\
							{\
								case RG_ERROR_WINDOWS_NO_CREATED:		DebugAdd("Error code = 0. Error creating window.\n"); break;\
								case RG_ERROR_FREETYPE:					DebugAdd("Error code = 1. Font loading error.\n"); break;\
								case RG_ERROR_FREETYPE_FONTS_NOT_FOUND:	DebugAdd("Error code = 2. Font not found.\n"); break;\
								case RG_ERROR_OUT_OF_MEMORY:			DebugAdd("Error code = 3. Out of RAM memory.\n"); break;\
								case RG_ERROR_FREETYPE_CHAR_NOT_LOAD:	DebugAdd("Error code = 4. Symbol not found.\n"); break;\
								case RG_ERROR_GLFW_INIT_ERR:			DebugAdd("Error code = 5. GLFW initialization error.\n"); break;\
								case RG_ERROR_FILE_NOT_FOUND:			DebugAdd("Error code = 6. File not found.\n"); break;\
								case RG_ERROR_RGARRAY_SIZE0:			DebugAdd("Error code = 7. RG_Array access error, RG_Array size = 0.\n"); break;\
								case RG_ERROR_RGARRAY_SIZE1:			DebugAdd("Error code = 8. RG_Array access error, RG_Array size < [i].\n"); break;\
								case RG_ERROR_RGARRAY_SIZE2:			DebugAdd("Error code = 9. RG_Array access error, RG_Array size - i > size.\n"); break;\
								case RG_ERROR_LOAD_NOT4CNT_IMAGE:		DebugAdd("Error code = 10. The loaded texture has fewer color channels supported (less than 4).\n"); break;\
								case RG_ERROR_MATERIAL_MISUSE:			DebugAdd("Error code = 11. Incorrect use of the material creation function.\n"); break;\
								case RG_ERROR_RGMATRIX_SIZE0:			DebugAdd("Error code = 12. RG_Matrix access error, RG_Matrix size = 0 or width < getPoint(width).\n"); break;\
								case RG_ERROR_LOAD_TEXTURE:				DebugAdd("Error code = 13. RG_LoadTexture(string path) - the wrong path was passed to the function.\n"); break;\
								case RG_ERROR_PLANET_NOT_FOUND:			DebugAdd("Error code = 14. RG_FindPlanet(string) could not find the planet.\n"); break;\
								case RG_ERROR_BLOCK_TYPE_INCORRECT:		DebugAdd("Error code = 15. RG_GetBlockType could not find the block.\n"); break;\
								case RG_ERROR_FIND_TEXTURE:				DebugAdd("Error code = 16. RG_GetTexture could not find the texture.\n"); break;\
								default: DebugAdd("unknown\n");\
							}\
							ShellExecuteA(0, "open", "Logs\\log.txt", NULL, NULL, SW_SHOWDEFAULT);\
							return error;\
						}


#define rg_min(num1, num2) (num1<num2?num1:num2)

#define rg_max(num1, num2) (num1>num2?num1:num2)

#define RG_FOR_CYCLEi(count) for(int i = 0; i<count; i++)
#define RG_FOR_CYCLEj(count) for(int j = 0; j<count; j++)
#define RG_FOR_CYCLEk(count) for(int k = 0; k<count; k++)

#define RG_FOR_CYCLEx(count) for(int x = 0; x<count; x++)
#define RG_FOR_CYCLEy(count) for(int y = 0; y<count; y++)
#define RG_FOR_CYCLEz(count) for(int z = 0; z<count; z++)

#define RG_FOR_CYCLE(type,name,count) for(type name = 0; name < count; name++)

#define RG_RevFOR_CYCLEi(count) for(int i = count; i>=0; i++)
#define RG_RevFOR_CYCLEj(count) for(int j = count; j>=0; j++)
#define RG_RevFOR_CYCLEk(count) for(int k = count; k>=0; k++)

#define RG_RevFOR_CYCLEx(count) for(int x = count; x>=0; x++)
#define RG_RevFOR_CYCLEy(count) for(int y = count; y>=0; y++)
#define RG_RevFOR_CYCLEz(count) for(int z = count; z>=0; z++)

#define RG_RevFOR_CYCLE(type,name,count) for(type name = count; name >=0; name++)


#define rg_calloc(type, size) (type*)calloc(size,sizeof(type))

#define rg_malloc(type, size) (type*)malloc(size*sizeof(type))

#define rg_free(fr) free(fr);

#define rg_realloc(resizable, type,oldsize, size)	{type* NONUSEDRGRGCALLOCNONUSEDNOTUSED = rg_calloc(type,size);						\
													RG_FOR_CYCLEi(rg_min(oldsize,size)) NONUSEDRGRGCALLOCNONUSEDNOTUSED[i]=resizable[i];\
													if(resizable!=nullptr&&oldsize>0)rg_free(resizable);								\
													resizable = NONUSEDRGRGCALLOCNONUSEDNOTUSED;}




/////////////ADD

template<class type>
type* s_realloc( type*& ar,uint size){
    return (type*)realloc(ar,sizeof(type)*size);
}
template<class type>
type* s_calloc(uint size){
    return (type*)calloc(size,sizeof(type));
}

template<class type>
type* s_malloc(uint size){
    return (type*)malloc(size*sizeof(type));
}

template<class type>
void s_replace( type*& ar, uint size){
    type* PLZNOTUSEIT = (type*)realloc(ar,sizeof(type)*size);
    free(ar);
    ar = PLZNOTUSEIT;
}

template<class type>
void s_replace_raw( type*& ar, uint OldSize, uint size){
    type* temparr = (type*)calloc(size,sizeof(type));
    for(int i = 0; i<min(OldSize,size);i++)
    {
        temparr[i] = ar[i];
    }
    free(ar);
    ar = temparr;
}

////////////////

#define rg_cout(a) cout<<a<<endl

#define rg_wcout(a) wcout<<a<<endl

uint rg_count_temp = 0;
#define rg_count cout<<rg_count_temp<<endl; rg_count_temp++;

template<typename type>
struct POINT2D
{
	type x = 0, y = 0;
};

template<typename type>
struct POINT3D
{
	type x = 0, y = 0, z = 0;/*
	type y = 0;
	type z = 0;*/
};

template<typename type>
struct COLOR3D
{
	type 
	r = 1,
	g = 1,
	b = 1;
};

template<typename type>
struct COLOR4D
{
	type 
	r = 1,
	g = 1,
	b = 1,
	a = 1;

	/*void operator=(COLOR4D<type>col){
		r = col.r;
		g = col.g;
		b = col.b;
		a = col.a;
	}*/
	//COLOR4D(){}
	/*template<class type2>
	COLOR4D(type2* col){
		r = col[0];
		g = col[1];
		b = col[2];
		a = col[3];
	}*/
};

enum ErrorRinegine
{
	RG_ERROR_WINDOWS_NO_CREATED, 				//0
	RG_ERROR_FREETYPE,									//1
	RG_ERROR_FREETYPE_FONTS_NOT_FOUND,	//2
	RG_ERROR_OUT_OF_MEMORY,							//3
	RG_ERROR_FREETYPE_CHAR_NOT_LOAD,		//4
	RG_ERROR_GLFW_INIT_ERR,							//5
	RG_ERROR_FILE_NOT_FOUND,						//6
	RG_ERROR_RGARRAY_SIZE0,							//7
	RG_ERROR_RGARRAY_SIZE1,							//8
	RG_ERROR_RGARRAY_SIZE2,							//9
	RG_ERROR_LOAD_NOT4CNT_IMAGE,				//10
	RG_ERROR_MATERIAL_MISUSE,						//11
	RG_ERROR_RGMATRIX_SIZE0,						//12
	RG_ERROR_LOAD_TEXTURE,							//13
	RG_ERROR_PLANET_NOT_FOUND,					//14
	RG_ERROR_BLOCK_TYPE_INCORRECT,			//15
	RG_ERROR_FIND_TEXTURE,			//16
};

enum RG_Mouse_State
{
	RG_MNPress,
	RG_MPress,
	RG_MRelease,
};


int RG_KEYS[350];
int RG_MOUSE[10] = {0,0,0,0,0,0,0,0,0,0};





GLFWmonitor* RG_MainMonitor;// = glfwGetPrimaryMonitor();
const GLFWvidmode* RG_MainVidmode;