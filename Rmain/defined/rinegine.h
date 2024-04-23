#pragma once

#define RG_V_MAJOR 0
#define RG_V_MINOR 2
#define RG_V_PATCH 0
#define RG_V_WIP 1

void RG_GetVersion(int& major, int& minor,int& patch, int&wip){
  major = RG_V_MAJOR;
  minor = RG_V_MINOR;
  patch = RG_V_PATCH;
  wip = RG_V_WIP;
}
void RG_GetVersion(int& major, int& minor,int& patch){
  major = RG_V_MAJOR;
  minor = RG_V_MINOR;
  patch = RG_V_PATCH;
}