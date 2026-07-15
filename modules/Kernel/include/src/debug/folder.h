#pragma once

namespace Rinegine {
  namespace Kernel {
    bool isDirectory(std::string path);
    bool isDirectory(std::wstring path);
    bool CreateFolder(std::string path);
    bool CreateFolder(std::wstring path);
  }
}