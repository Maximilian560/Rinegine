#pragma once

// #ifdef RG_WIN
// bool Kernel::isDirectory(LPCSTR folderpath) // char*
// {
//   DWORD dwFileAttributes = GetFileAttributesA(folderpath);
//   if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22)
//     return true;
//   return false;
// }
// bool Kernel::isDirectory(LPCWSTR folderpath) // char*
// {
//   DWORD dwFileAttributes = GetFileAttributesW(folderpath);
//   if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22)
//     return true;
//   return false;
// }

// bool Kernel::CreateFolder(std::string path) {
//   if (!isDirectory(path.c_str()))
//     if (!CreateDirectoryA(path.c_str(), NULL))
//       return false;
//   return true;
// }

// bool Kernel::CreateFolder(std::wstring path) {
//   if (!isDirectory(path.c_str()))
//     if (!CreateDirectoryW(path.c_str(), NULL))
//       return false;
//   return true;
// }

// #elif defined(RG_Linux)

// bool Kernel::isDirectory(const char *folderpath) {
//   struct stat info;
//   if (stat(folderpath, &info) != 0) {
//     return false;
//   }
//   return (info.st_mode & S_IFDIR) != 0;
// }

// bool Kernel::isDirectory(const wchar_t *folderpath) {
//   std::string narrow_path = Kernel::utf8_encode(std::wstring(folderpath));
//   if (narrow_path.empty()) {
//     rg_cout << "Failed to convert std::wstring path";
//     return false;
//   }
//   struct stat info;
//   if (stat(narrow_path.c_str(), &info) != 0) {
//     return false;
//   }
//   return (info.st_mode & S_IFDIR) != 0;
// }

// bool Kernel::CreateFolder(std::string path) {
//   if (!isDirectory(path.c_str())) {
//     if (mkdir(path.c_str(), 0755) != 0) {
//       rg_cout << "Failed to create directory\n";
//       return false;
//     }
//   }
//   return true;
// }

// bool Kernel::CreateFolder(std::wstring path) {
//   std::string narrow_path = Kernel::utf8_encode(path);
//   if (narrow_path.empty()) {
//     rg_cout << "Failed to convert std::wstring path";
//     return false;
//   }
//   if (!isDirectory(narrow_path.c_str())) {
//     if (mkdir(narrow_path.c_str(), 0755) != 0) {
//       rg_cout << "Failed to create directory";
//       return false;
//     }
//   }
//   return true;
// }

// #endif

namespace Rinegine {
bool Kernel::isDirectory(std::string path) {
  if (std::filesystem::is_directory(path)) {
    return true;
  }
  return false;
}
bool Kernel::isDirectory(std::wstring path) {
  if (std::filesystem::is_directory(path)) {
    return true;
  }
  return false;
}
bool Kernel::CreateFolder(std::string path) {
  if (!isDirectory(path)) {
    if(!std::filesystem::create_directory(path)){
      return false;
    };
  }
  return true;
}
bool Kernel::CreateFolder(std::wstring path) {
  if (!isDirectory(path)) {
    if(!std::filesystem::create_directory(path)){
      return false;
    };
  }
  return true;
}
}