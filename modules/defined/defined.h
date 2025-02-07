#pragma once // Защита от повторного включения файла

#include <cmath> // Подключение математической библиотеки
#include <string> // Подключение библиотеки для работы со строками
#include <thread> // Подключение библиотеки для работы с потоками

#include <iostream> // Подключение библиотеки для ввода/вывода
#include <fstream> // Подключение библиотеки для работы с файлами

#include <filesystem> // Подключение библиотеки для работы с файловой системой
#include <malloc.h>	// Подключение библиотеки для работы с динамической памятью

#include "../other/MyLibs/Noise.h"// Подключение пользовательской библиотеки, не используется

#include <windows.h> // Подключение библиотеки Windows API

// ОБЪЯВЛЕНИЕ ВАЖНЫХ ТИПОВ ДАННЫХ
using namespace std; // Использование стандартного пространства имен

// Определение типов для удобства
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef __int16 int16;
typedef long int lint;
typedef long unsigned int luint;

#ifndef UNIT_MAX
#define UINT_MAX 4294967295
#endif
// Объявление переменных для работы с шейдерами
uint prog; // Идентификатор программы шейдера
// Переменные для хранения позиций в шейдере
int SHDsetTexture;
int SHDisCube;
int SHDface;
int SHDcounter = 0; // Счетчик для управления шейдерами
int SHDlocation = 0; // Позиция в шейдере


// Макросы для математических операций
#define rg_min(num1, num2) (num1<num2?num1:num2)
#define rg_max(num1, num2) (num1>num2?num1:num2)

// Макросы для циклов
#define RG_FOR_CYCLEi(count) for(int i = 0; i<count; i++)
#define RG_FOR_CYCLEj(count) for(int j = 0; j<count; j++)
#define RG_FOR_CYCLEk(count) for(int k = 0; k<count; k++)
#define RG_FOR_CYCLEx(count) for(int x = 0; x<count; x++)
#define RG_FOR_CYCLEy(count) for(int y = 0; y<count; y++)
#define RG_FOR_CYCLEz(count) for(int z = 0; z<count; z++)
#define RG_FOR_CYCLEty(type,name,count) for(type name = 0; name < count; name++)
#define RG_FOR_CYCLE(name,count) for(int name = 0; name < count; name++)
#define RG_FOR_CYCLErev(name,count) for(int name = count; name >= 0; name--)
#define RG_RevFOR_CYCLEi(count) for(int i = count; i>=0; i--)
#define RG_RevFOR_CYCLEj(count) for(int j = count; j>=0; j--)
#define RG_RevFOR_CYCLEk(count) for(int k = count; k>=0; k--)
#define RG_RevFOR_CYCLEx(count) for(int x = count; x>=0; x--)
#define RG_RevFOR_CYCLEy(count) for(int y = count; y>=0; y--)
#define RG_RevFOR_CYCLEz(count) for(int z = count; z>=0; z--)
#define RG_RevFOR_CYCLE(type,name,count) for(type name = count; name >=0; name--)

// Макросы для работы с памятью
#define rg_free(fr) free(fr); // Освобождение памяти
#define rg_realloc(resizable, type,oldsize, size)	{type* NONUSEDRGRGCALLOCNONUSEDNOTUSED = rg_calloc(type,size);						\
													RG_FOR_CYCLEi(rg_min(oldsize,size)) NONUSEDRGRGCALLOCNONUSEDNOTUSED[i]=resizable[i];\
													if(resizable!=nullptr&&oldsize>0)rg_free(resizable);								\
													resizable = NONUSEDRGRGCALLOCNONUSEDNOTUSED;}

// Макросы для вывода в консоль
#define rg_cout(a) cout<<a<<endl
#define rg_wcout(a) wcout<<a<<endl

// Макросы для отладки
uint rg_count_temp = 0;
#define rg_count cout<<rg_count_temp<<endl; rg_count_temp++;
#define rg_count_clear rg_count_temp = 0;
#define elif else if

// Шаблоны структур для работы с точками и цветом
template<typename type>
struct POINT2D
{
	type x = 0, y = 0;
	bool operator==(POINT2D<type> p){
		if(x == p.x&& y==p.y)return true;
		return false;
	}
	bool operator>=(POINT2D<type> p){
		if(x >= p.x&& y>=p.y)return true;
		return false;
	}
	bool operator<=(POINT2D<type> p){
		if(x <= p.x&& y<=p.y)return true;
		return false;
	}
	bool operator>(POINT2D<type> p){
		if(x > p.x&& y>p.y)return true;
		return false;
	}
	bool operator<(POINT2D<type> p){
		if(x < p.x&& y<p.y)return true;
		return false;
	}
};

template<typename type>
struct POINT3D
{
	type x = 0, y = 0, z = 0;
	bool operator==(POINT3D<type> p){
		if(x == p.x&& y==p.y&&z==p.z)return true;
		return false;
	}
	bool operator>=(POINT3D<type> p){
		if(x >= p.x&& y>=p.y&&z>=p.z)return true;
		return false;
	}
	bool operator<=(POINT3D<type> p){
		if(x <= p.x&& y<=p.y&&z<=p.z)return true;
		return false;
	}
	bool operator>(POINT3D<type> p){
		if(x > p.x&& y>p.y&&z>p.z)return true;
		return false;
	}
	bool operator<(POINT3D<type> p){
		if(x < p.x&& y<p.y&&z<p.z)return true;
		return false;
	}
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
};


enum RG_Mouse_State
{
	RG_MNPress,
	RG_MPress,
	RG_MRelease,
};

// Объявление массивов для хранения состояний клавиш и мыши
int RG_KEYS[350];
int RG_MOUSE[10] = {0,0,0,0,0,0,0,0,0,0};


class RG_SysTime{
	static inline SYSTEMTIME SystemTime;
public:
	static void update(){
    GetLocalTime(&SystemTime);
	}
	static string Year(){
		return to_string(SystemTime.wYear);
	}
	static string Month(){
		string temp = to_string(SystemTime.wMonth);
		return ((temp.size()==1?"0":"")+temp);
		
	}
	static string DayOfWeek(){
		return to_string(SystemTime.wDayOfWeek);
	}
	static string Day(){
		string temp = to_string(SystemTime.wDay);
		return ((temp.size()==1?"0":"")+temp);
	}
	static string Hour(){
		string temp = to_string(SystemTime.wHour);
		return ((temp.size()==1?"0":"")+temp);
	}
	static string Minute(){
		string temp = to_string(SystemTime.wMinute);
		return ((temp.size()==1?"0":"")+temp);
	}
	static string Second(){
		string temp = to_string(SystemTime.wSecond);
		return ((temp.size()==1?"0":"")+temp);
	}
	static string Milliseconds(){
		string temp = to_string(SystemTime.wMilliseconds);
		return ((temp.size()==1?"000":temp.size()==2?"00":temp.size()==3?"0":"")+temp);
	}
};

HANDLE RG_MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void RG_SetColorTCMD(WORD col){
	SetConsoleTextAttribute(RG_MainConsole, col);
}