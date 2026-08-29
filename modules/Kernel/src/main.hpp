#pragma once

namespace Rinegine {
  namespace Kernel {

    alignas(std::wstring) static char storage_WFolder[sizeof(std::wstring)];
    alignas(std::string)  static char storage_AFolder[sizeof(std::string)];
    alignas(rg_string)    static char storage_Folder[sizeof(rg_string)];
    alignas(Kernel::Array<std::string>)  static char storage_AArguments[sizeof(Kernel::Array<std::string>)];
    alignas(Kernel::Array<std::wstring>)  static char storage_WArguments[sizeof(Kernel::Array<std::wstring>)];
    static bool folders_initialized = false;

    std::wstring& Main::WFolder = *reinterpret_cast<std::wstring*>(storage_WFolder);
    std::string& Main::AFolder = *reinterpret_cast<std::string*>(storage_AFolder);
    rg_string& Main::Folder = *reinterpret_cast<rg_string*>(storage_Folder);

    Kernel::Array<std::string>& Main::AArguments = *reinterpret_cast<Kernel::Array<std::string>  *>(storage_AArguments);
    Kernel::Array<std::wstring>& Main::WArguments = *reinterpret_cast<Kernel::Array<std::wstring> *>(storage_WArguments);

    void Main::InitFolder(const std::string& exePath) {
      if (folders_initialized) return;

      new (storage_WFolder) std::wstring(rg_to_stringw(exePath));
      new (storage_AFolder) std::string(exePath);
      new (storage_Folder)  rg_string(rg_to_string(exePath));


      folders_initialized = true;
    }

  }
}