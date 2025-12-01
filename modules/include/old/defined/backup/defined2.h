#pragma once // Защита от повторного включения файла

#include <cmath> // Подключение математической библиотеки
#include <string> // Подключение библиотеки для работы со строками
#include <thread> // Подключение библиотеки для работы с потоками

#include <iostream> // Подключение библиотеки для ввода/вывода
#include <fstream> // Подключение библиотеки для работы с файлами
#include <mutex>
#include <filesystem> // Подключение библиотеки для работы с файловой системой
#include <malloc.h>	// Подключение библиотеки для работы с динамической памятью

#include "../other/MyLibs/Noise.h"// Подключение пользовательской библиотеки, не используется

#ifdef _WIN32
#include <windows.h> // Подключение библиотеки Windows API

#include <io.h>     // для функции _setmode
#include <fcntl.h>  // для константы _O_U8TEXT

#include <Psapi.h>
#endif

#ifdef RG_Linux
#include <iconv.h>
#include <errno.h>
#include <stdexcept>
#include <sys/stat.h>
#include <chrono>
#include <ctime>
#endif



#include <typeinfo> //	Для определения
#include <cstdlib>		//	и вывода
#include <cxxabi.h>		//	названия типов

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)// || defined(_WIN64)
#define RG_x64
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__)// || defined(_WIN32)
#define RG_x32
#endif

#ifdef _M_IX86
#define RG_x86
#endif 
// ОБЪЯВЛЕНИЕ ВАЖНЫХ ТИПОВ ДАННЫХ
using namespace std; // Использование стандартного пространства имен

// Определение типов для удобства
typedef unsigned int uint;
typedef unsigned char uchar;

typedef uint8_t uint8;

typedef uint16_t uint16;

typedef int16_t int16;
typedef long int lint;
typedef long unsigned int luint;


// typedef unsigned long long int RG_GreatestType;
//typedef __int64 unsigned __int64;


#ifndef UINT_MAX
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
//#define rg_free(fr) free(fr); // Освобождение памяти
//#define rg_realloc(resizable, type,oldsize, size)	{type* NONUSEDRGRGCALLOCNONUSEDNOTUSED = rg_calloc(type,size);						
													// RG_FOR_CYCLEi(rg_min(oldsize,size)) NONUSEDRGRGCALLOCNONUSEDNOTUSED[i]=resizable[i];\
													// if(resizable!=nullptr&&oldsize>0)rg_free(resizable);								\
													// resizable = NONUSEDRGRGCALLOCNONUSEDNOTUSED;}

// Макросы для вывода в консоль
//#define rg_cout(a) cout<<a<<endl
//#define rg_wcout(a) wcout<<a<<endl

#ifdef RG_UTF
// #define rg_cout wcout
// inline ostream& rg_cout { return wcout; }
#define rg_cout wcout

inline wostream& operator<<(wostream& out, const wstring& text) {
	out << text;
	return out;
}

#define rg_cin wcin
#define rg_string wstring
#define rg_char wchar_t
#define rg_to_string_(in) to_wstring(in)
#define RG_L L""
#else
// #define rg_cout cout
// inline void rg_cout(ostream& in) { cout << in; }
// inline ostream& rg_cout { return cout; }
#define rg_cout cout

inline ostream& operator<<(ostream& out, const string& text) {
	out << text;
	return out;
}


#define rg_cin cin
#define rg_string string
#define rg_char char
#define rg_to_string_(in) to_string(in)
#define RG_L 
#endif


// Макросы для отладки
uint rg_count_temp = 0;
#define rg_count rg_cout<<(rg_count_temp++)<<", "<<__BASE_FILE__<<":"<<__LINE__<<endl
#define rg_count_clear rg_count_temp = 0
#define elif else if

enum RG_LOGS_TYPE {
	RG_LOG_LOCK_CRITICAL,
	RG_LOG_LOCK_ERROR,
	RG_LOG_LOCK_WARNING,
	RG_LOG_LOCK_INFO,
	RG_LOG_LOCK_DEBUG,
	RG_LOG_LOCK_MEM
};

namespace RG {
	namespace Lock {
		string TempError;
		void addl(RG_LOGS_TYPE type = RG_LOG_LOCK_DEBUG, string text = "empty", bool print = true) {
			TempError += char(type);
			TempError += print;
			TempError += text;
			TempError += char(3);
		}

	}
#ifdef RG_WIN
	inline wstring utf8_decode(const string& str) {
		if (str.empty()) return wstring();
		int SizeWstr = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring str_to_wstr(SizeWstr, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &str_to_wstr[0], SizeWstr);
		return str_to_wstr;
	}

	inline string utf8_encode(const wstring& wstr) {
		if (wstr.empty()) return string();
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}
	// #elif defined(RG_Linux)
#else
	wstring utf8_decode(const string& str) {
		if (str.empty()) return wstring();

		iconv_t cd = iconv_open("UTF-16LE", "UTF-8");
		if (cd == (iconv_t)-1) {
			rg_cout << L"iconv_open failed for UTF-8 to UTF-16LE";
			return wstring();
		}

		const char* in_buf = str.c_str();
		size_t in_bytes_left = str.size();
		size_t out_buf_size = str.size() * 2; // Примерный размер под UTF-16
		char* out_buf = (char*)calloc(out_buf_size + 2, sizeof(char)); // +2 для завершающего \0
		char* out_ptr = out_buf;
		size_t out_bytes_left = out_buf_size;

		if (!out_buf) {
			rg_cout << L"Memory allocation failed";
			iconv_close(cd);
			return wstring();
		}

		size_t ret = iconv(cd, const_cast<char**>(&in_buf), &in_bytes_left, &out_ptr, &out_bytes_left);

		if (ret == (size_t)-1) {
			rg_cout << L"iconv conversion failed";
			free(out_buf);
			iconv_close(cd);
			return wstring();
		}

		iconv_close(cd);

		size_t wchar_count = (out_ptr - out_buf) / sizeof(wchar_t);
		wstring result;
		result.assign((wchar_t*)out_buf, wchar_count);

		free(out_buf);

		return result;
	}

	string utf8_encode(const wstring& wstr) {
		if (wstr.empty()) return string();

		iconv_t cd = iconv_open("UTF-8", "UTF-16LE");
		if (cd == (iconv_t)-1) {
			rg_cout << L"iconv_open failed for UTF-16LE to UTF-8";
			return string();
		}

		const char* in_buf = reinterpret_cast<const char*>(wstr.c_str());
		size_t in_bytes_left = wstr.size() * sizeof(wchar_t);
		size_t out_buf_size = wstr.size() * 4; // Максимум 4 байта на один символ в UTF-8
		char* out_buf = (char*)calloc(out_buf_size + 1, sizeof(char)); // +1 для '\0'
		char* out_ptr = out_buf;
		size_t out_bytes_left = out_buf_size;

		if (!out_buf) {
			rg_cout << L"Memory allocation failed";
			iconv_close(cd);
			return string();
		}

		size_t ret = iconv(cd, const_cast<char**>(&in_buf), &in_bytes_left, &out_ptr, &out_bytes_left);

		if (ret == (size_t)-1) {
			rg_cout << L"iconv conversion failed";
			free(out_buf);
			iconv_close(cd);
			return string();
		}

		iconv_close(cd);

		size_t result_size = out_ptr - out_buf;
		string result(out_buf, result_size);

		free(out_buf);

		return result;
	}
#endif
}


#ifdef RG_UTF
inline wstring rg_to_string(const string& str) { return RG::utf8_decode(str); }
inline wstring rg_to_string(const wstring& str) { return str; }
inline wstring rg_to_stringw(const string& str) { return RG::utf8_decode(str); }
inline wstring rg_to_stringw(const wstring& str) { return str; }
inline string rg_to_stringa(const string& str) { return str;  }
inline string rg_to_stringa(const wstring& str) { return RG::utf8_encode(str); }

inline wostream& operator<<(wostream& out, const string& text) {
	out << RG::utf8_decode(text);
	return out;
}
#else
inline string rg_to_string(const string str) { return str; }
inline string rg_to_string(const wstring str) { return RG::utf8_encode(str); }
inline wstring rg_to_stringw(const string& str) { return RG::utf8_decode(str); }
inline wstring rg_to_stringw(const wstring& str) { return str; }
inline string rg_to_stringa(const string& str) { return str;  }
inline string rg_to_stringa(const wstring& str) { return RG::utf8_encode(str); }
inline ostream& operator<<(ostream& out, const wstring& text) {
	out << RG::utf8_encode(text);
	return out;
}
#endif

// Макрос для упрощённой конвертации типа из lvalue в rvalue
#define to_rvalue(type)const type&
#define to_rrvalue(type)const type
// Шаблоны структур для работы с точками и цветом

template <class type>
struct POINT2D {
	type x = 0, y = 0;
	bool operator==(POINT2D<type> p) {
		if (x == p.x && y == p.y)return true;
		return false;
	}
	bool operator>=(POINT2D<type> p) {
		if (x >= p.x && y >= p.y)return true;
		return false;
	}
	bool operator<=(POINT2D<type> p) {
		if (x <= p.x && y <= p.y)return true;
		return false;
	}
	bool operator>(POINT2D<type> p) {
		if (x > p.x && y > p.y)return true;
		return false;
	}
	bool operator<(POINT2D<type> p) {
		if (x < p.x && y < p.y)return true;
		return false;
	}
};

template <class type>
struct POINT3D {
	type x = type(), y = type(), z = type();
	bool operator==(POINT3D<type> p) {
		if (x == p.x && y == p.y && z == p.z)return true;
		return false;
	}
	bool operator>=(POINT3D<type> p) {
		if (x >= p.x && y >= p.y && z >= p.z)return true;
		return false;
	}
	bool operator<=(POINT3D<type> p) {
		if (x <= p.x && y <= p.y && z <= p.z)return true;
		return false;
	}
	bool operator>(POINT3D<type> p) {
		if (x > p.x && y > p.y && z > p.z)return true;
		return false;
	}
	bool operator<(POINT3D<type> p) {
		if (x < p.x && y < p.y && z < p.z)return true;
		return false;
	}
	void operator=(POINT2D<type> p) {
		x = p.x;
		y = p.y;
	}
	type& operator[](uint i) {
		return (&x)[i % 3];
	}
};

template<typename type>
struct COLOR3D {
	type
		r = 1,
		g = 1,
		b = 1;
};

template<typename type>
struct COLOR4D {
	type
		r = 1,
		g = 1,
		b = 1,
		a = 1;

	bool operator==(const COLOR4D<type>& c) {
		if (r == c.r && g == c.g && b == c.b && a == c.a)
			return true;
		else
			return false;
	}
	bool operator!=(const COLOR4D<type>& c) {
		if (r != c.r || g != c.g || b != c.b || a != c.a)
			return true;
		else
			return false;
	}
};

enum RG_Mouse_State {
	RG_MNPress,
	RG_MPress,
	RG_MRelease,
};

// Объявление массивов для хранения состояний клавиш и мыши
int RG_KEYS[350];
int RG_MOUSE[10] = { 0,0,0,0,0,0,0,0,0,0 };

inline int RG_KeyIs(int in, bool sticky = 1) {
	int out = RG_KEYS[in];
	if (sticky)RG_KEYS[in] = false;
	return out;
}
inline int RG_KeyIsPress(int in, bool sticky = 1) {
	int out = (RG_KEYS[in] == 1);
	if (sticky)RG_KEYS[in] = false;

	return out;
}


#ifdef RG_WIN
class RG_SysTime {
	static inline SYSTEMTIME SystemTime;
public:
	static void update() {
		GetLocalTime(&SystemTime);
	}
	static rg_string Year() {
		return rg_to_string_(SystemTime.wYear);
	}
	static rg_string Month() {
		rg_string temp = rg_to_string_(SystemTime.wMonth);
		return ((temp.size() == 1 ? RG_L"0" : RG_L"") + temp);

	}
	static rg_string DayOfWeek() {
		return rg_to_string_(SystemTime.wDayOfWeek);
	}
	static rg_string Day() {
		rg_string temp = rg_to_string_(SystemTime.wDay);
		return ((temp.size() == 1 ? RG_L"0" : RG_L"") + temp);
	}
	static rg_string Hour() {
		rg_string temp = rg_to_string_(SystemTime.wHour);
		return ((temp.size() == 1 ? RG_L"0" : RG_L"") + temp);
	}
	static rg_string Minute() {
		rg_string temp = rg_to_string_(SystemTime.wMinute);
		return ((temp.size() == 1 ? RG_L"0" : RG_L"") + temp);
	}
	static rg_string Second() {
		rg_string temp = rg_to_string_(SystemTime.wSecond);
		return ((temp.size() == 1 ? RG_L"0" : RG_L"") + temp);
	}
	static rg_string Milliseconds() {
		rg_string temp = rg_to_string_(SystemTime.wMilliseconds);
		return ((temp.size() == 1 ? RG_L"000" : temp.size() == 2 ? RG_L"00" : temp.size() == 3 ? RG_L"0" : RG_L"") + temp);
	}
	//W
	static wstring YearW() {
		return to_wstring(SystemTime.wYear);
	}
	static wstring MonthW() {
		wstring temp = to_wstring(SystemTime.wMonth);
		return ((temp.size() == 1 ? L"0" : L"") + temp);

	}
	static wstring DayOfWeekW() {
		return to_wstring(SystemTime.wDayOfWeek);
	}
	static wstring DayW() {
		wstring temp = to_wstring(SystemTime.wDay);
		return ((temp.size() == 1 ? L"0" : L"") + temp);
	}
	static wstring HourW() {
		wstring temp = to_wstring(SystemTime.wHour);
		return ((temp.size() == 1 ? L"0" : L"") + temp);
	}
	static wstring MinuteW() {
		wstring temp = to_wstring(SystemTime.wMinute);
		return ((temp.size() == 1 ? L"0" : L"") + temp);
	}
	static wstring SecondW() {
		wstring temp = to_wstring(SystemTime.wSecond);
		return ((temp.size() == 1 ? L"0" : L"") + temp);
	}
	static wstring MillisecondsW() {
		wstring temp = to_wstring(SystemTime.wMilliseconds);
		return ((temp.size() == 1 ? L"000" : temp.size() == 2 ? L"00" : temp.size() == 3 ? L"0" : L"") + temp);
	}
	//A
	static string YearA() {
		return to_string(SystemTime.wYear);
	}
	static string MonthA() {
		string temp = to_string(SystemTime.wMonth);
		return ((temp.size() == 1 ? "0" : "") + temp);

	}
	static string DayOfWeekA() {
		return to_string(SystemTime.wDayOfWeek);
	}
	static string DayA() {
		string temp = to_string(SystemTime.wDay);
		return ((temp.size() == 1 ? "0" : "") + temp);
	}
	static string HourA() {
		string temp = to_string(SystemTime.wHour);
		return ((temp.size() == 1 ? "0" : "") + temp);
	}
	static string MinuteA() {
		string temp = to_string(SystemTime.wMinute);
		return ((temp.size() == 1 ? "0" : "") + temp);
	}
	static string SecondA() {
		string temp = to_string(SystemTime.wSecond);
		return ((temp.size() == 1 ? "0" : "") + temp);
	}
	static string MillisecondsA() {
		string temp = to_string(SystemTime.wMilliseconds);
		return ((temp.size() == 1 ? "000" : temp.size() == 2 ? "00" : temp.size() == 3 ? "0" : "") + temp);
	}
};

HANDLE RG_MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void RG_SetColorTCMD(WORD col) {
	SetConsoleTextAttribute(RG_MainConsole, col);
}

bool RG_isSubstringAt(const char& a, const std::string& b) {
	for (size_t i = 0; i < b.size(); ++i) {
		if ((&a)[i] != b[i] || (&a)[i] == '\0') {
			return false;
		}
	}
	return true;
}

bool RG_isSubstringAt(const wchar_t& a, const std::wstring& b) {
	for (size_t i = 0; i < b.size(); ++i) {
		if ((&a)[i] != b[i] || (&a)[i] == '\0') {
			return false;
		}
	}
	return true;
}
bool RG_isSubstringAt(const string& a, const std::string& b) {
	for (size_t i = 0; i < b.size(); ++i) {
		if ((a)[i] != b[i] || (a)[i] == '\0') {
			return false;
		}
	}
	return true;
}

bool RG_isSubstringAt(const string& a, const std::wstring& b) {
	for (size_t i = 0; i < b.size(); ++i) {
		if ((a)[i] != b[i] || (a)[i] == '\0') {
			return false;
		}
	}
	return true;
}



void RG_Open(string path) {
	ShellExecuteA(0, "open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

void RG_Open(wstring path) {
	ShellExecuteW(0, L"open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

#elif defined(RG_Linux)
/*
class RG_SysTime {
	static inline std::chrono::system_clock::time_point SystemTime;
public:
	static void update() {
		SystemTime = std::chrono::system_clock::now();
	}

	static string Year() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_string(1900 + now_tm->tm_year);
	}

	static string Month() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(1 + now_tm->tm_mon);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string DayOfWeek() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_string(now_tm->tm_wday);
	}

	static string Day() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_mday);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Hour() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_hour);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Minute() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_min);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Second() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_sec);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Milliseconds() {
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(SystemTime.time_since_epoch()) % 1000;
		string temp = to_string(ms.count());
		return string(3 - temp.size(), '0') + temp;
	}
};

void RG_SetColorTCMD(int col) {
	// Поскольку на Linux нет аналогичного метода, можно оставить пустым или использовать ANSI escape codes
	rg_cout << "\033[" << col << "m";  // Например, для установки цвета текста
}

bool RG_isSubstringAt(const char& a, const std::string& b) {
	return (b.size() > 0 && a == b[0]);
}

bool RG_isSubstringAt(const wchar_t& a, const std::wstring& b) {
	return (b.size() > 0 && a == b[0]);
}

bool RG_isSubstringAt(const string& a, const std::string& b) {
	return (b.size() >= a.size() && b.compare(0, a.size(), a) == 0);
}

bool RG_isSubstringAt(const string& a, const std::wstring& b) {
	return (b.size() >= a.size() && std::wstring(b.begin(), b.begin() + a.size()) == std::wstring(a.begin(), a.end()));
}

void RG_Open(string path) {
	std::filesystem::path fs_path(path);
	if (std::filesystem::exists(fs_path)) {
		std::system(("xdg-open " + path).c_str());
	}
}

void RG_Open(wstring path) {
	std::filesystem::path fs_path(path);
	if (std::filesystem::exists(fs_path)) {
		std::system(("xdg-open " + std::string(path.begin(), path.end())).c_str());
	}
}*/

class RG_SysTime {
	static inline chrono::system_clock::time_point SystemTime;
public:
	static void update() {
		SystemTime = chrono::system_clock::now();
	}

	static string Year() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_string(1900 + now_tm->tm_year);
	}

	static string Month() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(1 + now_tm->tm_mon);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string DayOfWeek() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_string(now_tm->tm_wday);
	}

	static string Day() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_mday);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Hour() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_hour);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Minute() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_min);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Second() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_sec);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string Milliseconds() {
		auto ms = chrono::duration_cast<chrono::milliseconds>(SystemTime.time_since_epoch()) % 1000;
		string temp = to_string(ms.count());
		return string(3 - temp.size(), '0') + temp;
	}

	// W-версии для согласованности с Windows
	static wstring YearW() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_wstring(1900 + now_tm->tm_year);
	}

	static wstring MonthW() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		wstring temp = to_wstring(1 + now_tm->tm_mon);
		return (temp.size() == 1 ? L"0" : L"") + temp;
	}

	static wstring DayOfWeekW() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_wstring(now_tm->tm_wday);
	}

	static wstring DayW() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		wstring temp = to_wstring(now_tm->tm_mday);
		return (temp.size() == 1 ? L"0" : L"") + temp;
	}

	static wstring HourW() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		wstring temp = to_wstring(now_tm->tm_hour);
		return (temp.size() == 1 ? L"0" : L"") + temp;
	}

	static wstring MinuteW() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		wstring temp = to_wstring(now_tm->tm_min);
		return (temp.size() == 1 ? L"0" : L"") + temp;
	}

	static wstring SecondW() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		wstring temp = to_wstring(now_tm->tm_sec);
		return (temp.size() == 1 ? L"0" : L"") + temp;
	}

	static wstring MillisecondsW() {
		auto ms = chrono::duration_cast<chrono::milliseconds>(SystemTime.time_since_epoch()) % 1000;
		wstring temp = to_wstring(ms.count());
		return wstring(3 - temp.size(), L'0') + temp;
	}

	// A-версии для согласованности с Windows
	static string YearA() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_string(1900 + now_tm->tm_year);
	}

	static string MonthA() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(1 + now_tm->tm_mon);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string DayOfWeekA() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return to_string(now_tm->tm_wday);
	}

	static string DayA() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_mday);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string HourA() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_hour);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string MinuteA() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_min);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string SecondA() {
		time_t now_c = chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		string temp = to_string(now_tm->tm_sec);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static string MillisecondsA() {
		auto ms = chrono::duration_cast<chrono::milliseconds>(SystemTime.time_since_epoch()) % 1000;
		string temp = to_string(ms.count());
		return string(3 - temp.size(), '0') + temp;
	}
};

void RG_SetColorTCMD(int col) {
	rg_cout << "\033[" << col << "m";
}

bool RG_isSubstringAt(const char& a, const string& b) {
	return (b.size() > 0 && a == b[0]);
}

bool RG_isSubstringAt(const wchar_t& a, const wstring& b) {
	return (b.size() > 0 && a == b[0]);
}

bool RG_isSubstringAt(const string& a, const string& b) {
	return (b.size() >= a.size() && b.compare(0, a.size(), a) == 0);
}

bool RG_isSubstringAt(const string& a, const wstring& b) {
	return (b.size() >= a.size() && wstring(b.begin(), b.begin() + a.size()) == wstring(a.begin(), a.end()));
}

void RG_Open(string path) {
	filesystem::path fs_path(path);
	if (filesystem::exists(fs_path)) {
		system(("xdg-open " + path).c_str());
	}
}

void RG_Open(wstring path) {
	filesystem::path fs_path(path);
	if (filesystem::exists(fs_path)) {
		system(("xdg-open " + string(path.begin(), path.end())).c_str());
	}
}

#else
// SysTime
class RG_SysTime {
	static inline std::chrono::system_clock::time_point SystemTime;
public:
	static void update() {
		SystemTime = std::chrono::system_clock::now();
	}

	static rg_string Year() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return rg_to_string_(1900 + now_tm->tm_year);
	}

	static rg_string Month() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		rg_string temp = rg_to_string_(1 + now_tm->tm_mon);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static rg_string DayOfWeek() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		return rg_to_string_(now_tm->tm_wday);
	}

	static rg_string Day() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		rg_string temp = rg_to_string_(now_tm->tm_mday);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static rg_string Hour() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		rg_string temp = rg_to_string_(now_tm->tm_hour);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static rg_string Minute() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		rg_string temp = rg_to_string_(now_tm->tm_min);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static rg_string Second() {
		time_t now_c = std::chrono::system_clock::to_time_t(SystemTime);
		tm* now_tm = localtime(&now_c);
		rg_string temp = rg_to_string_(now_tm->tm_sec);
		return (temp.size() == 1 ? "0" : "") + temp;
	}

	static rg_string Milliseconds() {
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(SystemTime.time_since_epoch()) % 1000;
		rg_string temp = rg_to_string_(ms.count());
		return rg_string(3 - temp.size(), '0') + temp;
	}
};

void RG_SetColorTCMD(int col) {
	rg_cout << "\033[" << col << "m";
}

bool RG_isSubstringAt(const char& a, const std::string& b) {
	return (b.size() > 0 && a == b[0]);
}

bool RG_isSubstringAt(const wchar_t& a, const std::wstring& b) {
	return (b.size() > 0 && a == b[0]);
}

bool RG_isSubstringAt(const string& a, const std::string& b) {
	return (b.size() >= a.size() && b.compare(0, a.size(), a) == 0);
}

bool RG_isSubstringAt(const string& a, const std::wstring& b) {
	return (b.size() >= a.size() && std::wstring(b.begin(), b.begin() + a.size()) == std::wstring(a.begin(), a.end()));
}

void RG_Open(string path) {
	std::filesystem::path fs_path(path);
	if (std::filesystem::exists(fs_path)) {
		std::system(("xdg-open " + path).c_str());
	}
}

void RG_Open(wstring path) {
	std::filesystem::path fs_path(path);
	if (std::filesystem::exists(fs_path)) {
		std::system(("xdg-open " + std::string(path.begin(), path.end())).c_str());
	}
}
#endif


namespace RG {
	int GlobalSeed = 0;
};

bool RG_Prog_Work = 0;

int rg_count_temp_deb = 0;
#define rg_count_deb RG_Debug::addl(RG_LOG_LOCK_DEBUG, to_string(rg_count_temp_deb++)+", line: "+ to_string(__LINE__))
#define rg_count_deb_clear rg_count_temp_deb = 0