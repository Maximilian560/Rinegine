#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/files"
namespace Rinegine::Kernel {

	// wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
#ifdef RG_SYS_WINDOWS
	std::wstring utf8_to_utf16(const std::string& str);
	std::string utf16_to_utf8(const std::wstring& wstr);
#endif
	// namespace Rinegine::Kernel {

		//из файла utf8 в строку utf8

	std::wstring WFileLoad(std::string path);
	//из обычного фалйа в обычные строки
	std::string AFileLoad(std::string path);
	std::wstring WFileLoad(std::wstring path);


	bool RG_IsFile(std::string path);

	// namespace Rinegine::Kernel {
	std::string GetTypePath(std::string path);



#ifdef RG_SYS_WINDOWS
	// class Kernel::FileFinder {
	// 	HANDLE hFindFile;
	// 	WIN32_FIND_DATA findFileData; // Используем объект, а не указатель
	// 	bool _init = false;
	// 	bool _eof = false;

	// public:
	class FileFinder {
		bool eof();
		WIN32_FIND_DATA* init(const rg_string& path);

		WIN32_FIND_DATA* next();
		void close();

		~FileFinder();
	};
	class FileFinderA {
		// HANDLE hFindFile;
	// 	WIN32_FIND_DATAA findFileData; // Используем объект, а не указатель
	// 	bool _init = false;
	// 	bool _eof = false;

	// public:
		bool eof();

		WIN32_FIND_DATAA* init(const std::string& path);
		WIN32_FIND_DATAA* next();

		void close();

		~FileFinderA();
	};

	// class Kernel::FileFinderW {
		// HANDLE hFindFile;
		// WIN32_FIND_DATAW findFileData; // Используем объект, а не указатель
		// bool _init = false;
		// bool _eof = false;
	class FileFinderW {
		// public:
		bool eof();

		WIN32_FIND_DATAW* init(const std::wstring& path);
		WIN32_FIND_DATAW* next();

		void close();

		~FileFinderW();
	};


	// };

#endif
}