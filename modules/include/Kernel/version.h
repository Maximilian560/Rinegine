#pragma once

#define RG_V_MAJOR 0
#define RG_V_MINOR 3
#define RG_V_PATCH 0
#define RG_V_WIP 1

namespace Rinegine{
  void GetVersion(int& major, int& minor,int& patch, int&wip);
  void GetVersion(int& major, int& minor,int& patch);
}