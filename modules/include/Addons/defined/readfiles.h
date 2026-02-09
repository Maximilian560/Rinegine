#pragma once
#define RG_ERROR_STRING "E6filenofound"
#define RG_ERROR_WSTRING L"E6filenofound"

wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;


//из файла utf8 в строку utf8
wstring WFileLoad(string path) {
	//uint temp = 0;
	string text;

	ifstream file;
	if (path[0] == '"') {
		path.erase(0, 1);
		path.erase(path.size() - 1, 1);
		cout << endl << path << endl;
	}
	file.open(path);

	//if(!file.is_open()) return L"File no found";
	if (!file.is_open()) return RG_ERROR_WSTRING;

	while (!file.eof()) {
		text += file.get();
		//	temp++;
	}
	wstring endText = RG::utf8_decode(text);
	file.close();
	return endText;
}
//из обычного фалйа в обычные строки
string FileLoad(string path) {
	//uint temp = 0;

	if (path[0] == '"') {
		path.erase(0, 1);
		path.erase(path.size() - 1, 1);
		cout << endl << path << endl;
	}
	string text;

	ifstream file;

	file.open(path);

	if (!file.is_open()) return RG_ERROR_STRING;

	while (!file.eof()) {
		text += file.get();
		//temp++;
	}
	//wstring endText = utf8_decode(text);
	file.close();
	return text;
}
//из файла в массив символов 
// const char* FileLoadToChar(string path) {

// 	ifstream file;

// 	if (path[0] == '"') {
// 		path.erase(0, 1);
// 		path.erase(path.size() - 1, 1);
// 		cout << endl << path << endl;
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

char todopath[300];
string RG_GetFilePath(HWND& test) {
	//#ifdef RG_DEF_WINOS
#ifdef WIN_32
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); //размер структуры
	ofn.hwndOwner = test; //окно
	ofn.lpstrFile = todopath; //путь
	ofn.nMaxFile = sizeof(todopath); //maxsize
	ofn.lpstrFilter = "*.rgset";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL; //start dir
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (!GetSaveFileNameA(&ofn))return "error";
	return todopath;

#endif
	RG_Debug::addl(RG_LOG_ERROR, "RG_GetFilePath cant work outside Windows");
	return "";
}


bool RG_IsFile(string path) {
	ifstream test(path);
	if (test.is_open()) { test.close();return true; }
	else { test.close();return false; }
}

namespace RG {
	string GetTypePath(string path) {
		string out;
		for (int i = path.size() - 1;i >= 0;i--) {
			if (path[i] == '.') {
				for (int j = i + 1;j < path.size();j++) {
					out += path[j];
				}
				return out;
			}
		}
		return out;
	}
}