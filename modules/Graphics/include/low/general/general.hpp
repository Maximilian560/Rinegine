#pragma once

namespace Rinegine::Graphics{
  template <class type>
  struct Ray{
    Rinegine::Kernel::vec3<type> pos;
    Rinegine::Kernel::vec3<type> vector;
  };//todo
}