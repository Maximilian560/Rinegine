#pragma once
bool RG_DEFINIT = false;
void RG_DefInit() {
  if(RG_DEFINIT)return;
  RG_DEFINIT=1;
  srand(time(0));
  RG::GlobalSeed = rand();
  RG_MainFolder = RG_GetMainFolder();
#ifdef RG_UTF
  RG_WMainFolder = RG_WGetMainFolder();
#endif
  if (RG::Lock::TempError.size() > 0) {
    RG_Debug::addl(RG_LOG_INFO, "Error before init:");
    string temp;
    bool print = true;
    RG_LOGS_TYPE mode;
    for (int i = 0; i < RG::Lock::TempError.size(); i++) {
      if (RG::Lock::TempError[i] != char(3)) {
        temp += RG::Lock::TempError[i];
      } else {
        mode = RG_LOGS_TYPE(temp[0]);
        print = temp[1] == '1';
        RG_Debug::addl(mode, temp.substr(2), print);
      }
    }
    RG_Debug::addl(RG_LOG_INFO, "Continue");
  }
}

#define RG_DEF_INIT RG_DefInit()