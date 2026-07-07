#pragma once

namespace Rinegine{
  void GetVersion(int& major, int& minor,int& patch, int&wip){
    major = RG_V_MAJOR;
    minor = RG_V_MINOR;
    patch = RG_V_PATCH;
    wip = RG_V_WIP;
  }
  void GetVersion(int& major, int& minor,int& patch){
    major = RG_V_MAJOR;
    minor = RG_V_MINOR;
    patch = RG_V_PATCH;
  }
}