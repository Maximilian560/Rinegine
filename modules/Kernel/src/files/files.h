#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/files"
#define RG_ERROR_STRING "E6filenofound"
#define RG_ERROR_WSTRING L"E6filenofound"
namespace Rinegine::Kernel {

	// wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
#ifdef RG_SYS_WINDOWS
	std::wstring utf8_to_utf16(const std::string& str) {
		if (str.empty()) return {};
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
		std::wstring result(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), &result[0], size_needed);
		return result;
	}
	std::string utf16_to_utf8(const std::wstring& wstr) {
		if (wstr.empty()) return {};
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
		std::string result(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &result[0], size_needed, nullptr, nullptr);
		return result;
	}
#endif
	// namespace Rinegine::Kernel {

		//из файла utf8 в строку utf8

	std::wstring WFileLoad(std::string path) {
		//uint temp = 0;
		std::wstring text;

		std::ifstream file;
		if (path[0] == '"') {
			path.erase(0, 1);
			path.erase(path.size() - 1, 1);
			rg_cout << std::endl << rg_to_string(path) << std::endl;
		}
		file.open(path);

		//if(!file.is_open()) return L"File no found";
		if (!file.is_open()) return RG_ERROR_WSTRING;

		wchar_t temp = file.get();
		while (!file.eof()) {
			text += temp;
			temp = file.get();
			//	temp++;
		}
		// std::wstring endText = Rinegine::Kernel::utf8_decode(text);
		std::wstring endText = text;
		file.close();
		return endText;
	}
	//из обычного фалйа в обычные строки
	std::string AFileLoad(std::string path) {
		//uint temp = 0;

		if (path[0] == '"') {
			path.erase(0, 1);
			path.erase(path.size() - 1, 1);
			rg_cout << std::endl << rg_to_string(path) << std::endl;
		}
		std::string text;

		std::ifstream file;

		file.open(path);

		if (!file.is_open()) return RG_ERROR_STRING;
		// char temp = file.get();
		// while (!file.eof()) {
		// 	text += temp;
		// 	temp = file.get();
		// 	//temp++;
		// }
		int ch;
		while ((ch = file.get()) != EOF) {
			text += (char)(ch);
		}
		file.close();
		return text;
	}
	std::wstring WFileLoad(std::wstring path) {
		return WFileLoad(Rinegine::Kernel::utf8_encode(path));
	}
	// #ifdef RG_UTF
	// 	template <class in_string>
	// 	rg_string FileLoad(in_string path) {
	// 		return WFileLoad(rg_to_stringa(path));
	// 	}
	// #else
	// 	template <class in_string>
	// 	rg_string FileLoad(in_string path) {
	// 		return AFileLoad(rg_to_stringa(path));
	// 	}
	// #endif

		// }


	bool RG_IsFile(std::string path) {
		std::ifstream test(path);
		if (test.is_open()) { test.close(); return true; }
		else { test.close(); return false; }
	}

	// namespace Rinegine::Kernel {
	std::string GetTypePath(std::string path) {
		std::string out;
		for (long i = (long)path.size() - 1; i >= 0; i--) {
			if (path[(size_t)i] == '.') {
				for (size_t j = (size_t)i + 1; j < path.size(); j++) {
					out += path[j];
				}
				return out;
			}
		}
		return out;
	}



#ifdef RG_SYS_WINDOWS
	// class Kernel::FileFinder {
	// 	HANDLE hFindFile;
	// 	FileFindType findFileData; // Используем объект, а не указатель
	// 	bool _init = false;
	// 	bool _eof = false;

	// public:
	bool FileFinder::eof() { return _eof; }

	FileFindType* FileFinder::init(const rg_string& path) {
		if (!_init) {
			hFindFile = FindFirstFile(path.c_str(), &findFileData);
			if (hFindFile == INVALID_HANDLE_VALUE) {
				_eof = true;
				return nullptr;
			}
			_init = true;
		}
		else {
			RG_LOG_LOCK_ERROR("FileFinder is already initialized");
			if (!FindNextFile(hFindFile, &findFileData)) _eof = true;
		}
		return &findFileData;
	}

	FileFindType* FileFinder::next() {
		if (!_init) {
			RG_LOG_LOCK_ERROR("FileFinder is not initialized");
			return nullptr;
		}
		if (!FindNextFile(hFindFile, &findFileData)) {
			_eof = true;
			return nullptr;
		}
		return &findFileData;
	}

	void FileFinder::close() {
		if (_init) {
			FindClose(hFindFile);
			_init = false;
			_eof = false;
		}
	}

	FileFinder::~FileFinder() {
		close();
	}
	// };
	// class Kernel::FileFinderA {
	// 	HANDLE hFindFile;
	// 	FileFindTypeA findFileData; // Используем объект, а не указатель
	// 	bool _init = false;
	// 	bool _eof = false;

	// public:
	bool FileFinderA::eof() { return _eof; }

	FileFindTypeA* FileFinderA::init(const std::string& path) {
		if (!_init) {
			hFindFile = FindFirstFileA(path.c_str(), &findFileData);
			if (hFindFile == INVALID_HANDLE_VALUE) {
				_eof = true;
				return nullptr;
			}
			_init = true;
		}
		else {
			RG_LOG_LOCK_ERROR("FileFinder is already initialized");
			if (!FindNextFileA(hFindFile, &findFileData)) _eof = true;
		}
		return &findFileData;
	}

	FileFindTypeA* FileFinderA::next() {
		if (!_init) {
			RG_LOG_LOCK_ERROR("FileFinder is not initialized");
			return nullptr;
		}
		if (!FindNextFileA(hFindFile, &findFileData)) {
			_eof = true;
			return nullptr;
		}
		return &findFileData;
	}

	void FileFinderA::close() {
		if (_init) {
			FindClose(hFindFile);
			_init = false;
			_eof = false;
		}
	}

	FileFinderA::~FileFinderA() {
		close();
	}
	// };

	// class Kernel::FileFinderW {
		// HANDLE hFindFile;
		// FileFindTypeW findFileData; // Используем объект, а не указатель
		// bool _init = false;
		// bool _eof = false;

	// public:
	bool FileFinderW::eof() { return _eof; }

	FileFindTypeW* FileFinderW::init(const std::wstring& path) {
		if (!_init) {
			hFindFile = FindFirstFileW(path.c_str(), &findFileData);
			if (hFindFile == INVALID_HANDLE_VALUE) {
				_eof = true;
				return nullptr;
			}
			_init = true;
		}
		else {
			RG_LOG_LOCK_ERROR("FileFinder is already initialized");
			if (!FindNextFileW(hFindFile, &findFileData)) { _eof = true; return nullptr; }
		}
		return &findFileData;
	}

	FileFindTypeW* FileFinderW::next() {
		if (!_init) {
			RG_LOG_LOCK_ERROR("FileFinder is not initialized");
			return nullptr;
		}
		if (!FindNextFileW(hFindFile, &findFileData)) {
			_eof = true;
			return nullptr;
		}
		return &findFileData;
	}

	void FileFinderW::close() {
		if (_init) {
			FindClose(hFindFile);
			_init = false;
			_eof = false;
		}
	}

	FileFinderW::~FileFinderW() {
		close();
	}
	// };

#elif defined(RG_SYS_LINUX)

	// class Kernel::FileFinder {
	// 	DIR* dir = nullptr;
	// 	FileFindType* ent = nullptr;
	// 	bool _init = false;
	// 	bool _eof = false;
	//
	// public:
	bool FileFinder::eof() { return _eof; }

	FileFindType* FileFinder::init(const rg_string& path) {
		if (!_init) {
			dir = opendir(std::filesystem::path(path).string().c_str());
			if (!dir) {
				_eof = true;
				return nullptr;
			}
			_init = true;
			ent = static_cast<FileFindType*>(readdir(dir));
			if (!ent) {
				_eof = true;
				return nullptr;
			}
			return ent;
		}
		else {
			RG_LOG_LOCK_ERROR("FileFinder is already initialized");
			ent = static_cast<FileFindType*>(readdir(dir));
			if (!ent) _eof = true;
			return ent;
		}
	}

	FileFindType* FileFinder::next() {
		if (!_init) {
			RG_LOG_LOCK_ERROR("FileFinder is not initialized");
			return nullptr;
		}
		ent = static_cast<FileFindType*>(readdir(dir));
		if (!ent) {
			_eof = true;
			return nullptr;
		}
		return ent;
	}

	void FileFinder::close() {
		if (_init) {
			closedir(dir);
			dir = nullptr;
			ent = nullptr;
			_init = false;
			_eof = false;
		}
	}

	FileFinder::~FileFinder() {
		close();
	}
	// };

	// class Kernel::FileFinderA {
	// 	DIR* dir = nullptr;
	// 	FileFindType* ent = nullptr;
	// 	bool _init = false;
	// 	bool _eof = false;
	//
	// public:
	bool FileFinderA::eof() { return _eof; }

	FileFindType* FileFinderA::init(const std::string& path) {
		if (!_init) {
			dir = opendir(path.c_str());
			if (!dir) {
				_eof = true;
				return nullptr;
			}
			_init = true;
			ent = static_cast<FileFindType*>(readdir(dir));
			if (!ent) {
				_eof = true;
				return nullptr;
			}
			return ent;
		}
		else {
			RG_LOG_LOCK_ERROR("FileFinderA is already initialized");
			ent = static_cast<FileFindType*>(readdir(dir));
			if (!ent) _eof = true;
			return ent;
		}
	}

	FileFindType* FileFinderA::next() {
		if (!_init) {
			RG_LOG_LOCK_ERROR("FileFinderA is not initialized");
			return nullptr;
		}
		ent = static_cast<FileFindType*>(readdir(dir));
		if (!ent) {
			_eof = true;
			return nullptr;
		}
		return ent;
	}

	void FileFinderA::close() {
		if (_init) {
			closedir(dir);
			dir = nullptr;
			ent = nullptr;
			_init = false;
			_eof = false;
		}
	}

	FileFinderA::~FileFinderA() {
		close();
	}
	// };

	// class Kernel::FileFinderW {
	// 	DIR* dir = nullptr;
	// 	FileFindType* ent = nullptr;
	// 	bool _init = false;
	// 	bool _eof = false;
	//
	// public:
	bool FileFinderW::eof() { return _eof; }

	FileFindType* FileFinderW::init(const std::wstring& path) {
		if (!_init) {
			// В Linux нет прямой поддержки wchar_t в opendir, конвертируем wstring в UTF-8 string
			std::string utf8_path = std::filesystem::path(path).string();
			dir = opendir(utf8_path.c_str());
			if (!dir) {
				_eof = true;
				return nullptr;
			}
			_init = true;
			ent = static_cast<FileFindType*>(readdir(dir));
			if (!ent) {
				_eof = true;
				return nullptr;
			}
			return ent;
		}
		else {
			RG_LOG_LOCK_ERROR("FileFinderW is already initialized");
			ent = static_cast<FileFindType*>(readdir(dir));
			if (!ent) _eof = true;
			return ent;
		}
	}

	FileFindType* FileFinderW::next() {
		if (!_init) {
			RG_LOG_LOCK_ERROR("FileFinderW is not initialized");
			return nullptr;
		}
		ent = static_cast<FileFindType*>(readdir(dir));
		if (!ent) {
			_eof = true;
			return nullptr;
		}
		return ent;
	}

	void FileFinderW::close() {
		if (_init) {
			closedir(dir);
			dir = nullptr;
			ent = nullptr;
			_init = false;
			_eof = false;
		}
	}

	FileFinderW::~FileFinderW() {
		close();
	}
	// };
#endif
	// }


	// namespace Rinegine::Kernel {
	// 	namespace File {
			/**
			* Reads the contents of a file character by character and applies a provided lambda function
			* to each character. This is useful for processing large files without loading the entire
			* file into memory.
			*
			* The lambda function should take a `char&` as its parameter, allowing you to modify the
			* character if necessary.
			*
			* The file is automatically closed after reading.
			*
			* Use lamda like [&file_out](char& file_char_in){file_out += file_char_in;}
			*
			* @template lamda
			* @param {std::string} path - The path to the file to be read.
			* @param {function(char&): void} func - A lambda function that processes each character in the file. The character is passed by reference, so it can be modified.
			*
			* @example
			* // Example usage:
			* // Collect all characters from a file into a std::string:
			* std::string result;
			* Read("example.txt", [&result](char& file_char_in) {
			*     result += file_char_in;
			* });
			*/
	template<typename lamda>
	void Read(std::string path, lamda func) {
		std::ifstream file(path);
		char temp = (char)file.get();
		while (!file.eof()) {
			func(temp);
			temp = (char)file.get();
		}

		file.close();
	}

	void Write(std::string path, const std::string& in) {
		std::ofstream file(path);

		file << in;

		file.close();
	}
	/**
	 * Reads the contents of a file character by character and applies a provided lambda function
	 * to each character. This is useful for processing large files without loading the entire
	 * file into memory.
	 *
	 * The lambda function should take a `char&` as its parameter, allowing you to modify the
	 * character if necessary.
	 *
	 * The file is automatically closed after reading.
	 *
	 * Use lamda like [&file_out](wchar_t& file_char_in){file_out += file_char_in;}
	 *
	 * @example
	 *
	 * // Example usage:
	 * // Collect all characters from a file into a std::string:
	 * std::string result;
	 * Read(L"example.txt", [&result](wchar_t& file_char_in) {
	 *     result += file_char_in;
	 * });
	 *
	 * @param {std::wstring} path - The path to the file to be read.
	 * @param {function(wchar_t&): void} func - A lambda function that processes each character in the file. The character is passed by reference, so it can be modified.
	 */
	template<typename lamdaw>
	void ReadW(const wchar_t* path, lamdaw func) {
		std::wifstream file(rg_to_stringa(std::wstring(path)));
		wchar_t temp = (wchar_t)file.get();
		while (!file.eof()) {
			func(temp);
			temp = (wchar_t)file.get();
		}
		file.close();
	}

	void WriteW(const char* path, const std::wstring& in) {
		std::wofstream file(path, std::ios::out);

		file << in;

		file.close();
	}
	// 	}
	// }
}