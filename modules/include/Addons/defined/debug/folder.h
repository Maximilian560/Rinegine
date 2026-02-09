#pragma once

// Автор кода поиска папка (isDirectory): https://www.cyberforum.ru/win-api/thread382853.html#post9791602 (было добавлено без его согласия, если это читает автор, прошу дай знать если ты против)
/*bool isDirectory(LPCWSTR folderpath)//wchar_t*
{
    DWORD dwFileAttributes = GetFileAttributes(folderpath);
    if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY||dwFileAttributes==22)
        return true;
    return false;
}*/
#ifdef RG_WIN
bool isDirectory(LPCSTR folderpath)//char*
{
    DWORD dwFileAttributes = GetFileAttributesA(folderpath);
    if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22)
        return true;
    return false;
}
bool isDirectory(LPCWSTR folderpath)//char*
{
    DWORD dwFileAttributes = GetFileAttributesW(folderpath);
    if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22)
        return true;
    return false;
}

bool RG_CreateFolder(string path) {
    if (!isDirectory(path.c_str()))
        if (!CreateDirectoryA(path.c_str(), NULL))return false;
    return true;
}

bool RG_CreateFolder(wstring path) {
    if (!isDirectory(path.c_str()))
        if (!CreateDirectoryW(path.c_str(), NULL))return false;
    return true;
}
string RG_AMainFolder = "C:/";
wstring RG_WMainFolder = L"C:/";

#elif defined(RG_Linux)


bool isDirectory(const char* folderpath) {
    struct stat info;
    if (stat(folderpath, &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool isDirectory(const wchar_t* folderpath) {
    string narrow_path = RG::utf8_encode(wstring(folderpath));
    if (narrow_path.empty()) {
        rg_cout<<"Failed to convert wstring path";
        return false;
    }
    struct stat info;
    if (stat(narrow_path.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool RG_CreateFolder(string path) {
    if (!isDirectory(path.c_str())) {
        if (mkdir(path.c_str(), 0755) != 0) {
            rg_cout<<"Failed to create directory";
            return false;
        }
    }
    return true;
}

bool RG_CreateFolder(wstring path) {
    string narrow_path = RG::utf8_encode(path);
    if (narrow_path.empty()) {
        rg_cout<<"Failed to convert wstring path";
        return false;
    }
    if (!isDirectory(narrow_path.c_str())) {
        if (mkdir(narrow_path.c_str(), 0755) != 0) {
            rg_cout<<"Failed to create directory";
            return false;
        }
    }
    return true;
}

string RG_AMainFolder = "/";
wstring RG_WMainFolder = L"/";
#endif
#ifdef RG_UTF
wstring& RG_MainFolder = RG_WMainFolder;
#else
string&  RG_MainFolder = RG_AMainFolder;
#endif