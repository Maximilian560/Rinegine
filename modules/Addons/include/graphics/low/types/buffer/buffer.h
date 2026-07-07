#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/low/types/buf"

namespace RG {
  class Buffer {
    uint _buf = -1;
    uint _buf_type;
  public:
    Buffer() {}
    operator uint& () {
      return _buf;
    }
    template<typename Point>
    Buffer(uint size, Point* buf, uint arr_type, uint type) {
      init(size, buf, type, arr_type);
    }
    template<typename Point>
    void init(uint size, Point* buf, uint arr_type, uint type) {
      clear();
      _buf_type = arr_type;
      glGenBuffers(1, &_buf);
      glBindBuffer(_buf_type, _buf);
      glBufferData(_buf_type, size, buf, type);
      glBindBuffer(_buf_type, 0);
    }
    template<typename Point>
    void init(const RG_Array<Point>& in, uint arr_type, uint type ) {
      clear();
      _buf_type = arr_type;
      glGenBuffers(1, &_buf);
      glBindBuffer(_buf_type, _buf);
      glBufferData(_buf_type, in.size() * sizeof(Point), in.arr(), type);
      glBindBuffer(_buf_type, 0);
    }
    void bind() {
      if (_buf != -1)
        glBindBuffer(_buf_type, _buf);
      else {
        RG_LOG_LOCK_ERROR("Buffer is not init");
        glBindBuffer(_buf_type, _buf);
      }
    }
    bool empty() {
      return (_buf == -1);
    }
    bool is_init() {
      return (_buf != -1);
    }
    void clear() {
      if (_buf != -1) {
        glDeleteBuffers(1, &_buf);
        _buf = -1;
      }
    }
    ~Buffer() {
      if (_buf != -1) {
        glDeleteBuffers(1, &_buf);
      }
    }
  };
}

namespace RG_Object {
  class Standart;
  class Sprite;
  class Background;
  class Text;
};

class RG_Buffer {
  friend class RG_Object::Standart;
  friend class RG_Object::Text;
  friend class RG_Object::Sprite;
  friend class RG_Object::Background;
  friend class RG_Atlas;

  //friend class RG_Object::Mesh;
protected:
  enum gl_init {
    GL_INIT_Vertex = 1,
    GL_INIT_Color = 2,
    GL_INIT_Texture = 4,
    GL_INIT_Normal = 8
  };
  struct GL {
    // int init = 0;
    // uint vertex = -1;
    // uint color = -1;
    // uint normal = -1;
    // RG_Array<uint> textures;
    RG::Buffer vertex;
    RG::Buffer color;
    RG::Buffer normal;
    RG_Array<RG::Buffer> textures;
    RG::Buffer elements;
  }gl;
public:
  struct Raw {
    RG_Array<POINT3D<double>> vertex;
    RG_Array<COLOR4D<double>> color;
    RG_Array<POINT3D<double>> normal;
    RG_Array<RG_Array<POINT2D<double>>> textures;
    RG_Array<uint> elements;
  }raw;
  RG::Buffer gl_vertex() {
    return gl.vertex;
  }

  RG::Buffer gl_color() {
    return gl.color;
  }

  RG_Array<RG::Buffer>& gl_textures() {
    return gl.textures;
  }

  RG::Buffer gl_normal() {
    return gl.normal;
  }

  bool gl_is_vertex() {
    return (gl.vertex.is_init());
  }

  bool gl_is_color() {
    return (gl.color.is_init());
  }

  bool gl_is_texture() {
    return (gl.textures.size());
  }

  bool gl_is_normal() {
    return (gl.normal.is_init());
  }

  void GL_Regen(gl_init type) {
    if (type & GL_INIT_Vertex)
      gl.vertex.init(raw.vertex.size() * sizeof(POINT3D<double>), raw.vertex.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    if (type & GL_INIT_Normal)
      gl.normal.init(raw.normal.size() * sizeof(POINT3D<double>), raw.normal.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    if (type & GL_INIT_Color)
      gl.color.init(raw.color.size() * sizeof(COLOR4D<double>), raw.color.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    if (type & GL_INIT_Texture) {
      gl.textures.resize(raw.textures.size());
      for (int i = 0; i < raw.textures.size(); i++) {
        gl.textures[i].init(raw.textures[i].size() * sizeof(POINT2D<double>), raw.textures[i].data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
      }
    }


    // if (type & GL_INIT_Vertex) {
    //   if (gl.init & GL_INIT_Vertex) {
    //     glDeleteBuffers(1, &gl.vertex);
    //     gl.init &= ~GL_INIT_Vertex;
    //   }
    //   if (raw.vertex.size()) {
    //     gl.vertex = BufferLoad<POINT3D<double>>(raw.vertex.size() * sizeof(POINT3D<double>), raw.vertex.data(), GL_STATIC_DRAW);
    //     gl.init |= GL_INIT_Vertex;
    //   }
    // }

    // if (type & GL_INIT_Normal) {
    //   if (gl.init & GL_INIT_Normal) {
    //     glDeleteBuffers(1, &gl.normal);
    //     gl.init &= ~GL_INIT_Normal;
    //   }
    //   if (raw.normal.size()) {
    //     gl.normal = BufferLoad<POINT3D<double>>(raw.normal.size() * sizeof(POINT3D<double>), raw.normal.data(), GL_STATIC_DRAW);
    //     gl.init |= GL_INIT_Normal;
    //   }
    // }

    // if (type & GL_INIT_Color) {
    //   if (gl.init & GL_INIT_Color) {
    //     glDeleteBuffers(1, &gl.color);
    //     gl.init &= ~GL_INIT_Color;
    //   }
    //   if (raw.color.size()) {
    //     gl.color = BufferLoad<COLOR4D<double>>(raw.color.size() * sizeof(COLOR4D<double>), raw.color.data(), GL_STATIC_DRAW);
    //     gl.init |= GL_INIT_Color;
    //   }
    // }

    // if (type & GL_INIT_Texture) {
    //   if (gl.init & GL_INIT_Texture) {
    //     glDeleteBuffers(gl.textures.size(), gl.textures.data());
    //     gl.init &= ~GL_INIT_Texture;
    //   }
    //   if (raw.textures.size()) {
    //     gl.textures.resize(raw.textures.size());
    //     for (int i = 0; i < raw.textures.size(); i++) {
    //       gl.textures[i] = BufferLoad<POINT2D<double>>(raw.textures[i].size() * sizeof(POINT2D<double>), raw.textures[i].data(), GL_STATIC_DRAW);
    //     }
    //     gl.init |= GL_INIT_Texture;
    //   }
    // }
    // switch (type) {
    //   case GL_INIT_Vertex:
    //     if (gl.init & GL_INIT_Vertex) {
    //       glDeleteBuffers(1, &gl.vertex);
    //       gl.init &= ~GL_INIT_Vertex;
    //     }
    //     if (raw.vertex.size()) {
    //       gl.vertex = BufferLoad<POINT3D<double>>(raw.vertex.size() * sizeof(POINT3D<double>), raw.vertex.data(), GL_STATIC_DRAW);
    //       gl.init |= GL_INIT_Vertex;
    //     }
    //     break;

    //   case GL_INIT_Normal:
    //     if (gl.init & GL_INIT_Normal) {
    //       glDeleteBuffers(1, &gl.normal);
    //       gl.init &= ~GL_INIT_Normal;
    //     }
    //     if (raw.normal.size()) {
    //       gl.normal = BufferLoad<POINT3D<double>>(raw.normal.size() * sizeof(POINT3D<double>), raw.normal.data(), GL_STATIC_DRAW);
    //       gl.init |= GL_INIT_Normal;
    //     }
    //     break;

    //   case GL_INIT_Color:
    //     if (gl.init & GL_INIT_Color) {
    //       glDeleteBuffers(1, &gl.color);
    //       gl.init &= ~GL_INIT_Color;
    //     }
    //     if (raw.color.size()) {
    //       gl.color = BufferLoad<COLOR4D<double>>(raw.color.size() * sizeof(COLOR4D<double>), raw.color.data(), GL_STATIC_DRAW);
    //       gl.init |= GL_INIT_Color;
    //     }
    //     break;

    //   case GL_INIT_Texture:
    //     if (gl.init & GL_INIT_Texture) {
    //       glDeleteBuffers(gl.textures.size(), gl.textures.data());
    //       gl.init &= ~GL_INIT_Texture;
    //     }
    //     if (raw.textures.size()) {
    //       gl.textures.resize(raw.textures.size());
    //       for (int i = 0; i < raw.textures.size();i++) {
    //         gl.textures[i] = BufferLoad<POINT2D<double>>(raw.textures[i].size() * sizeof(POINT2D<double>), raw.textures[i].data(), GL_STATIC_DRAW);
    //       }
    //       gl.init |= GL_INIT_Texture;
    //     }
    //     break;
    // }
  }
  void GL_Gen() {
    if (raw.vertex.size())
      gl.vertex.init(raw.vertex.size() * sizeof(POINT3D<double>), raw.vertex.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    if (raw.normal.size())
      gl.normal.init(raw.normal.size() * sizeof(POINT3D<double>), raw.normal.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    if (raw.color.size())
      gl.color.init(raw.color.size() * sizeof(COLOR4D<double>), raw.color.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    if (raw.textures.size()) {
      gl.textures.resize(raw.textures.size());
      for (int i = 0; i < raw.textures.size(); i++) {
        gl.textures[i].init(raw.textures[i].size() * sizeof(POINT2D<double>), raw.textures[i].data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
      }
    }
    /*if (gl.init & GL_INIT_Vertex) {
      glDeleteBuffers(1, &gl.vertex);
      gl.init &= ~GL_INIT_Vertex;
    }
    if(gl.init&GL_INIT_Normal){
      glDeleteBuffers(1, &gl.normal);
      gl.init &= ~GL_INIT_Normal;
    }
    if (gl.init & GL_INIT_Color) {
      glDeleteBuffers(1, &gl.color);
      gl.init &= ~GL_INIT_Color;
    }
    if (gl.init & GL_INIT_Texture) {
      glDeleteBuffers(gl.textures.size(), gl.textures.data());
      gl.init &= ~GL_INIT_Texture;
    }*/
    // clear();

    // if (raw.vertex.size()) {
    //   gl.vertex = BufferLoad<POINT3D<double>>(raw.vertex.size() * sizeof(POINT3D<double>), raw.vertex.data(), GL_STATIC_DRAW);
    //   gl.init |= GL_INIT_Vertex;
    // }
    // if (raw.normal.size()) {
    //   gl.normal = BufferLoad<POINT3D<double>>(raw.normal.size() * sizeof(POINT3D<double>), raw.normal.data(), GL_STATIC_DRAW);
    //   gl.init |= GL_INIT_Normal;
    // }
    // if (raw.color.size()) {
    //   gl.color = BufferLoad<COLOR4D<double>>(raw.color.size() * sizeof(COLOR4D<double>), raw.color.data(), GL_STATIC_DRAW);
    //   gl.init |= GL_INIT_Color;
    // }
    // if (raw.textures.size()) {
    //   gl.textures.resize(raw.textures.size());
    //   for (int i = 0; i < raw.textures.size(); i++) {
    //     gl.textures[i] = BufferLoad<POINT2D<double>>(raw.textures[i].size() * sizeof(POINT2D<double>), raw.textures[i].data(), GL_STATIC_DRAW);
    //   }
    //   gl.init |= GL_INIT_Texture;
    // }
  }
  void clear() {
    gl.vertex.clear();
    gl.color.clear();
    gl.normal.clear();
    gl.textures.clear();
    // if (gl.init & GL_INIT_Vertex) {
    //   glDeleteBuffers(1, &gl.vertex);
    //   gl.init &= ~GL_INIT_Vertex;
    // }
    // if (gl.init & GL_INIT_Normal) {
    //   glDeleteBuffers(1, &gl.normal);
    //   gl.init &= ~GL_INIT_Normal;
    // }
    // if (gl.init & GL_INIT_Color) {
    //   glDeleteBuffers(1, &gl.color);
    //   gl.init &= ~GL_INIT_Color;
    // }
    // if (gl.init & GL_INIT_Texture) {
    //   glDeleteBuffers(gl.textures.size(), gl.textures.data());
    //   gl.init &= ~GL_INIT_Texture;
    // }
    // if (gl.init)RG_LOG_LOCK_CRITICAL(L"Что то тут не так...");
  }
  ~RG_Buffer() {
    gl.vertex.clear();
    gl.color.clear();
    gl.normal.clear();
    gl.textures.clear();
  }
};
