#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/files"
#define RG_ERROR_STRING "E6filenofound"
#define RG_ERROR_WSTRING L"E6filenofound"

// wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
#ifdef RG_WIN
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
namespace RG {

	//из файла utf8 в строку utf8

	inline wstring WFileLoad(string path) {
		//uint temp = 0;
		string text;

		ifstream file;
		if (path[0] == '"') {
			path.erase(0, 1);
			path.erase(path.size() - 1, 1);
			rg_cout << endl << rg_to_string(path) << endl;
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
		wstring endText = RG::utf8_decode(text);
		file.close();
		return endText;
	}
	//из обычного фалйа в обычные строки
	inline string AFileLoad(string path) {
		//uint temp = 0;

		if (path[0] == '"') {
			path.erase(0, 1);
			path.erase(path.size() - 1, 1);
			rg_cout << endl << rg_to_string(path) << endl;
		}
		string text;

		ifstream file;

		file.open(path);

		if (!file.is_open()) return RG_ERROR_STRING;
		char temp = file.get();
		while (!file.eof()) {
			text += temp;
			temp = file.get();
			//temp++;
		}
		//wstring endText = utf8_decode(text);
		file.close();
		return text;
	}
	inline wstring WFileLoad(wstring path) {
		return WFileLoad(RG::utf8_encode(path));
	}
#ifdef RG_UTF
	template <class in_string>
	rg_string FileLoad(in_string path) {
		return WFileLoad(rg_to_stringa(path));
	}
#else
	template <class in_string>
	rg_string FileLoad(in_string path) {
		return AFileLoad(rg_to_stringa(path));
	}
#endif
	//из файла в массив символов 
	// const char* FileLoadToChar(string path) {

	// 	ifstream file;

	// 	if (path[0] == '"') {
	// 		path.erase(0, 1);
	// 		path.erase(path.size() - 1, 1);
	// 		rg_cout << endl << path << endl;
	// 	}

	// 	char* text = nullptr;
	// 	file.open(path);
	// 	uint size = 0;


	// 	if (!file.is_open()) return RG_ERROR_STRING;
	// 	while (!file.eof()) {
	// 		size++;
	// 		text = (char*)realloc(text, size * sizeof(char));
	// 		text[size - 1] = file.get();
	// 		//temp++;
	// 	}
	// 	text[size - 1] = '\0';
	// 	//wstring endText = utf8_decode(text);
	// 	file.close();
	// 	return text;
	// }
	// const RG_Array<char> FileLoadToArray(string path) {

	// 	ifstream file;

	// 	if (path[0] == '"') {
	// 		path.erase(0, 1);
	// 		path.erase(path.size() - 1, 1);
	// 		rg_cout << endl << path << endl;
	// 	}

	// 	RG_Array<char> text;
	// 	file.open(path);
	// 	uint size = 0;


	// 	if (!file.is_open()) return RG_ERROR_STRING;
	// 	while (!file.eof()) {
	// 		size++;
	// 		// text = (char*)realloc(text, size * sizeof(char));
	// 		text.fastpush(file.get());
	// 		// text[size - 1] = ;
	// 		//temp++;
	// 	}
	// 	text[size - 1] = '\0';
	// 	//wstring endText = utf8_decode(text);
	// 	file.close();
	// 	return text;
	// }
}
// #ifdef RG_WIN
// rg_char todopath[300];
// rg_string RG_GetFilePath(/*HWND& test*/) {
// 	//#ifdef RG_DEF_WINOS
// 	OPENFILENAME ofn;
// 	ZeroMemory(&ofn, sizeof(ofn));
// 	ofn.lStructSize = sizeof(ofn); //размер структуры
// 	// ofn.hwndOwner = test; //окно
// 	ofn.lpstrFile = todopath; //путь
// 	ofn.nMaxFile = sizeof(todopath); //maxsize
// 	ofn.lpstrFilter = RG_L"*.rgset";
// 	ofn.lpstrFileTitle = NULL;
// 	ofn.nMaxFileTitle = 0;
// 	ofn.lpstrInitialDir = NULL; //start dir
// 	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
// 	if (!GetSaveFileName(&ofn))return RG_L"error";
// 	return todopath;

// 	RG_LOG_LOCK_ERROR("RG_GetFilePath cant work outside Windows");
// 	return RG_L"";
// }
// #endif


bool RG_IsFile(string path) {
	ifstream test(path);
	if (test.is_open()) { test.close(); return true; } else { test.close(); return false; }
}

namespace RG {
	string GetTypePath(string path) {
		string out;
		for (int i = path.size() - 1; i >= 0; i--) {
			if (path[i] == '.') {
				for (int j = i + 1; j < path.size(); j++) {
					out += path[j];
				}
				return out;
			}
		}
		return out;
	}



#ifdef RG_WINos
	class FileFinder {
		HANDLE hFindFile;
		WIN32_FIND_DATA findFileData; // Используем объект, а не указатель
		bool _init = false;
		bool _eof = false;

	public:
		bool eof() { return _eof; }

		WIN32_FIND_DATA* init(const rg_string& path) {
			if (!_init) {
				hFindFile = FindFirstFile(path.c_str(), &findFileData);
				if (hFindFile == INVALID_HANDLE_VALUE) {
					_eof = true;
					return nullptr;
				}
				_init = true;
			} else {
				RG_LOG_LOCK_ERROR("FileFinder is already initialized");
				if (!FindNextFile(hFindFile, &findFileData)) _eof = true;
			}
			return &findFileData;
		}

		WIN32_FIND_DATA* next() {
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

		void close() {
			if (_init) {
				FindClose(hFindFile);
				_init = false;
				_eof = false;
			}
		}

		~FileFinder() {
			close();
		}
	};
	class FileFinderA {
		HANDLE hFindFile;
		WIN32_FIND_DATAA findFileData; // Используем объект, а не указатель
		bool _init = false;
		bool _eof = false;

	public:
		bool eof() { return _eof; }

		WIN32_FIND_DATAA* init(const string& path) {
			if (!_init) {
				hFindFile = FindFirstFileA(path.c_str(), &findFileData);
				if (hFindFile == INVALID_HANDLE_VALUE) {
					_eof = true;
					return nullptr;
				}
				_init = true;
			} else {
				RG_LOG_LOCK_ERROR("FileFinder is already initialized");
				if (!FindNextFileA(hFindFile, &findFileData)) _eof = true;
			}
			return &findFileData;
		}

		WIN32_FIND_DATAA* next() {
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

		void close() {
			if (_init) {
				FindClose(hFindFile);
				_init = false;
				_eof = false;
			}
		}

		~FileFinderA() {
			close();
		}
	};

	class FileFinderW {
		HANDLE hFindFile;
		WIN32_FIND_DATAW findFileData; // Используем объект, а не указатель
		bool _init = false;
		bool _eof = false;

	public:
		bool eof() { return _eof; }

		WIN32_FIND_DATAW* init(const wstring& path) {
			if (!_init) {
				hFindFile = FindFirstFileW(path.c_str(), &findFileData);
				if (hFindFile == INVALID_HANDLE_VALUE) {
					_eof = true;
					return nullptr;
				}
				_init = true;
			} else {
				RG_LOG_LOCK_ERROR("FileFinder is already initialized");
				if (!FindNextFileW(hFindFile, &findFileData)) { _eof = true; return nullptr; }
			}
			return &findFileData;
		}

		WIN32_FIND_DATAW* next() {
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

		void close() {
			if (_init) {
				FindClose(hFindFile);
				_init = false;
				_eof = false;
			}
		}

		~FileFinderW() {
			close();
		}
	};

#endif
}


namespace RG {
	namespace File {
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
		* // Collect all characters from a file into a string:
		* std::string result;
		* Read("example.txt", [&result](char& file_char_in) {
		*     result += file_char_in;
		* });
		*/
		template<typename lamda>
		void Read(string path, lamda func) {
			ifstream file(path);
			char temp = file.get();
			while (!file.eof()) {
				func(temp);
				temp = file.get();
			}

			file.close();
		}

		void Write(string path, const string& in) {
			ofstream file(path);

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
		 * // Collect all characters from a file into a string:
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
			wifstream file(rg_to_stringa(wstring(path)));
			wchar_t temp = file.get();
			while (!file.eof()) {
				func(temp);
				temp = file.get();
			}

			file.close();
		}

		void WriteW(const char* path, const wstring& in) {
			std::wofstream file(path, std::ios::out);

			file << in;

			file.close();
		}


	}
}