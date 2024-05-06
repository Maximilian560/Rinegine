#pragma once

// Автор кода поиска папка (isDirectory): https://www.cyberforum.ru/win-api/thread382853.html#post9791602 (было добавлено без его согласия, если это читает автор, прошу дай знать если ты против)
/*bool isDirectory(LPCWSTR folderpath)//wchar_t*
{
    DWORD dwFileAttributes = GetFileAttributes(folderpath);
    if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY||dwFileAttributes==22)
        return true;
    return false;
}*/
bool isDirectory(LPCSTR folderpath)//char*
{
    DWORD dwFileAttributes = GetFileAttributesA(folderpath);
    if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22)
        return true;
    return false;
}

bool RG_CreateFolder(string path){
  if(!isDirectory(path.c_str()))
      if(!CreateDirectory(path.c_str(),NULL))return false;
  return true;
}