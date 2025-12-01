#pragma once

struct RG_Collisions{
  double
  Colx = -1000,
  Colmx = -1000,
  Coly = -1000,
  Colmy = -1000,
  Colz = -1000,
  Colmz = -1000;
};

enum RG_EntityType{
  RG_ENT_None,
  RG_ENT_Player,
};
struct RG_Entity{
  POINT3D<double>pos;
  POINT3D<double>rortate;
  POINT3D<double>size;
  uint idEntity;
  RG_EntityType EnTy;
  RG_Collisions cols;
};
