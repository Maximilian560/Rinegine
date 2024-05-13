#pragma once



wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

//декодирование из ASCII в utf8
wstring utf8_decode(const string &str)
{
    if( str.empty() ) return wstring();
    int SizeWstr = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring str_to_wstr( SizeWstr, 0 );
    MultiByteToWideChar                  (CP_UTF8, 0, &str[0], (int)str.size(), &str_to_wstr[0], SizeWstr);
    return str_to_wstr;
}

string utf8_encode(const wstring &wstr)
{
    if( wstr.empty() ) return string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    string strTo( size_needed, 0 );
    WideCharToMultiByte                  (CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

//из файла utf8 в строку utf8
wstring WFileLoad(string path)
{
	//uint temp = 0;
	string text;

	ifstream file;
	if(path[0]=='"'){
		path.erase(0,1);
		path.erase(path.size()-1,1);
		cout<<endl<<path<<endl;
	}
	file.open(path);

	//if(!file.is_open()) return L"File no found";
	if(!file.is_open()) return L"E6filenofound";

	while (!file.eof())
	{
		text+=file.get();
	//	temp++;
	} 
	wstring endText = utf8_decode(text);
	file.close();
	return endText;
}
//из обычного фалйа в обычные строки
string FileLoad(string path)
{
	//uint temp = 0;

	if(path[0]=='"'){
		path.erase(0,1);
		path.erase(path.size()-1,1);
		cout<<endl<<path<<endl;
	}
	string text;

	ifstream file;

	file.open(path);

	if(!file.is_open()) return "E6filenofound";

	while (!file.eof())
	{
		text+=file.get();
		//temp++;
	} 
	//wstring endText = utf8_decode(text);
	file.close();
	return text;
}
//из файла в массив символов 
char* FileLoadToChar(string path)
{

	ifstream file;

	if(path[0]=='"'){
		path.erase(0,1);
		path.erase(path.size()-1,1);
		cout<<endl<<path<<endl;
	}

	char* text = nullptr;
	file.open(path);
	uint size = 0;
	

	if(!file.is_open()) return "E6filenofound";
	while (!file.eof())
	{
		size++;
		text=(char*)realloc(text,size*sizeof(char));	
		text[size-1]=file.get();
		//temp++;
	} 
	text[size-1]='\0';
	//wstring endText = utf8_decode(text);
	file.close();
	return text;
}

char todopath[300];
string RG_GetFilePath(HWND& test){
	#ifdef RG_DEF_WINOS
  //HWND test = glfwGetWin32Window (RG_MainWindow->win());
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); //размер структуры
	ofn.hwndOwner = test; //окно
	ofn.lpstrFile = todopath; //путь
	ofn.nMaxFile = sizeof(todopath); //maxsize
	ofn.lpstrFilter = "*.rgset";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL; //start dir
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	if(!GetSaveFileNameA(&ofn))return "error";
	return todopath;

	#endif

}


bool RG_IsFile(string path){
	ifstream test(path);
	if(test.is_open()){test.close();return true;}
	else {test.close();return false;}
}