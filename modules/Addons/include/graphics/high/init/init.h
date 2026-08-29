#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/high/init"

namespace RG{
  namespace Lock{
    namespace Graphic{
      void init(){
        Rinegine::init();
      }
    }
  }
}
#define RG_GRAPH_INIT RG::Lock::Graphic::init()