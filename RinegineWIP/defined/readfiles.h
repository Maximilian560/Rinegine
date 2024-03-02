#pragma once



wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

//декодирование из ASCII в utf8
wstring utf8_decode(const std::string &str)
{
    if( str.empty() ) return std::wstring();
    int SizeWstr = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring str_to_wstr( SizeWstr, 0 );
    MultiByteToWideChar                  (CP_UTF8, 0, &str[0], (int)str.size(), &str_to_wstr[0], SizeWstr);
    return str_to_wstr;
}

//из файла utf8 в строку utf8
wstring WFileLoad(string path)
{
	//uint temp = 0;
	string text;

	ifstream file;

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
