#pragma once

#define RG_V_MAJOR 0
#define RG_V_MINOR 1
#define RG_V_PATCH 1

void RG_GetVersion(int& major, int& minor,int& patch){
  major = RG_V_MAJOR;
  minor = RG_V_MINOR;
  patch = RG_V_PATCH;
}