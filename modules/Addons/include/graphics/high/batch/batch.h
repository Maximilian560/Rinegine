#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/high/batch"

namespace RG{
  namespace Graphic{
    template<class gr_type>
    class Batch{
      // typedef RG::Graphic::Flat::Sprite gr_type;
      RG_Array<gr_type> _objects;
      gr_type _opti_object;
      public:
      void push_back(const gr_type& in){
        _objects.push_back(in);
      }
      void init(initializer_list<gr_type> in){
        _objects.init(in);
      }
      void init(initializer_list<typename gr_type::Set> in){
        _objects.clear();
        _objects.resize(in.size());
        for(int i = 0; i<in.size();i++){
          _objects[i].init(in.begin()[i]);
          _objects[i].Create();
        }
      }

      void optimize(){
        _opti_object.clear();
        _opti_object.raw.vertex.resize(_objects.size() * 4);
        _opti_object.raw.color.resize(_objects.size() * 4);
        _opti_object.raw.textures.resize(_objects.size() * 4);
        _opti_object.raw.elements.resize(_objects.size() * 6);

        for(int i = 0; i < _objects.size();i++){
          _opti_object.raw.vertex[i]+=_objects[i].raw.vertex;
          _opti_object.raw.color[i]+=_objects[i].raw.color;
          _opti_object.raw.textures[i]+=_objects[i].raw.textures;
          _opti_object.raw.elements[i]+=_objects[i].raw.elements;
        }
        _opti_object.GL_Gen();
      }
      void draw(){
        for(int i = 0; i < _objects.size();i++){
          _objects[i].draw();
        }
      }
      void draw_opti(){
        _opti_object.draw();
      }
      gr_type& operator[](int i){
        return _objects[i];
      }
    };
  }
}