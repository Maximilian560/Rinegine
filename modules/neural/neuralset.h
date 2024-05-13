#pragma once

struct RG_SettingNeural{
  //кол во нейронов в 1 слое, 2-м слое, и т.д.
  RG_Array<uint> countNeurons;
  string pathWeight = false;
};