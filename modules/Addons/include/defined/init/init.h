#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/init"

// #ifndef int32
// #define int32 __int32
// #endif
// typedef __int32 int32;
void RG_DefInit() {
  if (RG_DEFINIT)return;
  RG_DEFINIT = 1;
  srand(time(0));
  RG::GlobalSeed = rand();
  RG_AMainFolder = RG_AGetMainFolder();
#ifdef RG_UTF
  RG_WMainFolder = RG_WGetMainFolder();
#endif
  if (RG::Lock::TempError.size() > 0) {
    // RG_LOG_LOCK_INFO("Logs before init (time doesn't match):");
    // RG::Debug::addl(RG::Log::INFO, RG_L"Logs before init (time doesn't match):", true, __FILE__, __LINE__);
    RG_LOG_LOCK_INFO("Logs before init (time doesn't match):");
    string temp;
    string file;
    int32 line;
    bool print = true, next = false;
    RG::Log::Types mode;
    uint errors = 0;
    for (int i = 0; i < RG::Lock::TempError.size(); i++) {
      if (RG::Lock::TempError[i] != char(3) && !next) {
        temp += RG::Lock::TempError[i];
      }elif(RG::Lock::TempError[i] != char(4)) {
        next = 1;
        file += RG::Lock::TempError[i];
      } else {
        mode = RG::Log::Types(temp[0]);
        print = bool(temp[1]);
        line = 0;
        line |= static_cast<int32>(static_cast<unsigned char>(temp[2])) << 0;
        line |= static_cast<int32>(static_cast<unsigned char>(temp[3])) << 8;
        line |= static_cast<int32>(static_cast<unsigned char>(temp[4])) << 16;
        line |= static_cast<int32>(static_cast<unsigned char>(temp[5])) << 24;
        size_t header_size = sizeof(char) + sizeof(int32) + sizeof(bool); // 6
        if (temp.size() < header_size) {
          RG_LOG_LOCK_ERROR("Invalid log header size in TempError: " + temp);
          errors++;
          continue;
        }
        string text = temp.substr(header_size, temp.size() - header_size - 1);
        RG::Debug::addl(mode, text, print, file, line);
        file.clear();
        text.clear();
        temp.clear();
        next = false;
      }

    }
    // for (int i = 0; i < RG::Lock::TempError.size(); i++) {
    //   if (RG::Lock::TempError[i] != char(3) && !next) {
    //     temp += RG::Lock::TempError[i];
    //   } elif(RG::Lock::TempError[i] != char(4)) {
    //     next = 1;
    //     file += RG::Lock::TempError[i];
    //   } else {
    //     mode = RG::Log::Types(temp[0]);
    //     print = temp[1] == '1';
    //     line = 0;
    //     line |= static_cast<int32>(static_cast<unsigned char>(temp[2])) << 0;
    //     line |= static_cast<int32>(static_cast<unsigned char>(temp[3])) << 8;
    //     line |= static_cast<int32>(static_cast<unsigned char>(temp[4])) << 16;
    //     line |= static_cast<int32>(static_cast<unsigned char>(temp[5])) << 24;
    //     size_t header_size = sizeof(char) + sizeof(int32) + sizeof(bool); // 6
    //     if (temp.size() < header_size) {
    //       RG_LOG_LOCK_ERROR("Invalid log header size in TempError: "+temp);
    //       errors++;
    //       continue;
    //     }
    //     RG::Debug::addl(mode, temp.substr(sizeof(char) + sizeof(int32) + sizeof(bool)), print, file, line);
    //     temp.clear();
    //     file.clear();
    //   }
    // }
    if (RG::Lock::_logs - 1 <= errors) {
      RG_LOG_LOCK_ERROR("Log before init was lost!");
      RG_LOG_LOCK_INFO("Corrupted log:\n" + RG::Lock::TempError);
      string debug = "\n";
      for (int i = 0; i < RG::Lock::TempError.size(); i++) {
        debug += to_string(int(RG::Lock::TempError[i])) += ' ';
        if (RG::Lock::TempError[i] == '\n')debug += '\n';
      }
      RG_LOG_LOCK_DEBUG(debug);
    }
    RG_LOG_LOCK_INFO("Continue");
  }
}

#define RG_DEF_INIT RG_DefInit()