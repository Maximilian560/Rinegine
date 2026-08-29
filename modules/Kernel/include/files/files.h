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
	// typedef WIN32_FIND_DATA FileFindType;
	// typedef WIN32_FIND_DATAA FileFindTypeA;
	// typedef WIN32_FIND_DATAW FileFindTypeW;
	struct FileFindType : public WIN32_FIND_DATA {
		rg_string get_name() {
			return this->cFileName;
		}
	};
	struct FileFindTypeA : public WIN32_FIND_DATAA {
		std::string get_name() {
			return this->cFileName;
		}
	};
	struct FileFindTypeW : public WIN32_FIND_DATAW {
		std::wstring get_name() {
			return this->cFileName;
		}
	};
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
	// 	FileFindType findFileData; // Используем объект, а не указатель
	// 	bool _init = false;
	// 	bool _eof = false;

	// public:
		bool eof();

		FileFindType* init(const std::string& path);
		FileFindType* next();

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

#elif defined(RG_SYS_LINUX)
	struct FileFindType : public dirent {
		std::string get_name() {
			return this->d_name;
		}
	};
	// typedef dirent FileFindType;

	class FileFinder {
		DIR* dir;
		// FileFindType entsat;
		FileFindType* ent;
		bool _init;
		bool _eof;
	public:
		FileFinder() : dir(nullptr), _init(false), _eof(false) {}
		bool eof();
		FileFindType* init(const rg_string& path);
		FileFindType* next();
		void close();
		~FileFinder();
	};

	class FileFinderA {
		DIR* dir = nullptr;
		FileFindType* ent = nullptr;
		bool _init = false;
		bool _eof = false;

	public:
		bool eof();
		FileFindType* init(const std::string& path);
		FileFindType* next();
		void close();
		~FileFinderA();
	};

	class FileFinderW {
		DIR* dir = nullptr;
		FileFindType* ent = nullptr;
		bool _init = false;
		bool _eof = false;
	public:
		bool eof();
		FileFindType* init(const std::wstring& path);
		FileFindType* next();
		void close();
		~FileFinderW();
	};
#endif
}