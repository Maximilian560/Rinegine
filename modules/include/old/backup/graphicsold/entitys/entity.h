#pragma once

namespace RG {
  namespace Lock {
    namespace Entity {
      struct Variables {
        RG::vec3<double> _pos;
        RG::vec3<double> _size;
        int _health = -1;
        int _armor = -1;
        int _type = -1; // тип сущности, в типе должны быть указаны необходимые дополнительные параметры, такие как урон или макс хп, скорость и тому подобное. Реализует сам разработчик
        // public:
        //   Variables operator=(Variables in) {
        //     _pos = in._pos;
        //     _size = in._size;
        //     _health = in._health;
        //     _armor = in._armor;
        //     _type = in._type;
        //   }
        void operator=(const Variables& in) {
          _pos = in._pos;
          _size = in._size;
          _health = in._health;
          _armor = in._armor;
          _type = in._type;
        }


      };

    }
  }
  class Entity :private Lock::Entity::Variables {

  public:
    Entity() {}
    Entity(Lock::Entity::Variables in) :Lock::Entity::Variables(in) {};
    // void init(Lock::Entity::Variables in) {
    //   _pos = in._pos;
    //   _size = in._size;
    //   _health = in._health;
    //   _armor = in._armor;
    //   _type = in._type;
    // }
    void operator=(const Entity& in) {
      *this = in;
    }
    void operator=(const Variables& in) {
      *this = in;
    }
    void init(const Variables& in) {
      *this = in;
    }
  };

}

void TEST() {
  RG::Entity test;
  
  test.init({
    ._health = 10
    });

}