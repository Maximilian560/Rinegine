#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/gen-chunk"

namespace RG {
  enum Block_Type {
    Air = -1,
    Grass,
    Dirt,
    Stone,
  };

  class Chunk : public Graphic::Body::Lock::Mesh {
    friend class World;
    static inline POINT3D<uint> _size;
    POINT3D<uint> _pos;
    RG_Matrix3D<Block_Type> _chunk;
    wstring _wstr_status;
    uint _status = 0;
    uint* _status_ptr = &_status;
    uint _max_status = 0;
    // mutex _mut;
    mutex* _mut_ptr;
    static inline double _block_size = 0.5;
    // static inline int GL_VERTEX_BUFFER_CHUNK = -1;
    // static inline int GL_COLOR_BUFFER_CHUNK = -1;
    // int GL_TEXTURE_BUFFER_CHUNK = -1;
    // int GL_INDEXES_BUFFER_CHUNK = -1;

    static inline RG::Buffer GL_VERTEX_BUFFER_CHUNK;
    static inline RG::Buffer GL_COLOR_BUFFER_CHUNK;
    RG::Buffer GL_TEXTURE_BUFFER_CHUNK;
    RG::Buffer GL_INDEXES_BUFFER_CHUNK;

    int gl_indexes_size = 0;
  public:
    void init(POINT3D<uint>in) {
      _size = in;
      _max_status = in.x * in.y * in.z * 1 + 2;
    }
    void init(uint x, uint y, uint z) {
      _size = { x,y,z };
      _max_status = x * y * z * 1 + 2;
    }
    // void get_status(const uint& status_in, const uint& max_status_in) {
    //   status_in = *_status_ptr;
    //   max_status_in = &_max_status;
    // }
    // Chunk(Chunk&& in) {
    //   clear();
    //   _size = (in._size);
    //   _pos = (in._pos);
    //   _chunk = (in._chunk);
    //   _wstr_status = (in._wstr_status);
    //   _status = (in._status);
    //   _status_ptr = (in._status_ptr);
    //   _max_status = (in._max_status);
    //   _mut = (in._mut);
    //   _mut_ptr = (in._mut_ptr);
    //   _block_size = (in._block_size);
    // }
    static void calculate_status(uint& max_stat, POINT3D<uint>in) {
      max_stat = in.x * in.y * in.z * 1 + 2;
    }
    void set_status() {
      _status_ptr = &_status;
    }
    void set_status(uint& stat) {
      _status_ptr = &stat;
    }
    // void set_mutex() {
    //   _mut_ptr = &_mut;
    // }
    void set_mutex(mutex& mut) {
      _mut_ptr = &mut;
    }

    static void gl_buffer_gen() {
      // rg_cout << "gl_buffer_gen\n";
      if (GL_COLOR_BUFFER_CHUNK.empty()) {
        // rg_cout << "gl_color_buffer_gen\n";
        RG_Array<COLOR4D<double>> color;
        color.init(_size.x * _size.y * _size.z * 4 * 6, { 1,1,1,1 });
        GL_COLOR_BUFFER_CHUNK.init<COLOR4D<double>>(color.size() * sizeof(COLOR4D<double>), color.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
      }
      if (GL_VERTEX_BUFFER_CHUNK.empty()) {
        // rg_cout << "gl_vertex_buffer_gen\n";
        RG_Array<POINT3D<double>> vertex;
        vertex.resize(_size.x * _size.y * _size.z * 4 * 6);
        for (int y = 0; y < _size.y; y++) {
          for (int z = 0; z < _size.z; z++) {
            for (int x = 0; x < _size.x; x++) {
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 0] = { 0. + _block_size * x, 0. + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 1] = { _block_size + _block_size * x, 0. + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 2] = { _block_size + _block_size * x, _block_size + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 3] = { 0. + _block_size * x, _block_size + _block_size * y, 0. + _block_size * z };//front

              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 0] = { _block_size + _block_size * x, 0. + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 1] = { 0. + _block_size * x, 0. + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 2] = { 0. + _block_size * x, _block_size + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 3] = { _block_size + _block_size * x, _block_size + _block_size * y, _block_size + _block_size * z };//back

              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 0] = { 0. + _block_size * x, 0. + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 1] = { 0. + _block_size * x, 0. + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 2] = { 0. + _block_size * x, _block_size + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 3] = { 0. + _block_size * x, _block_size + _block_size * y, 0. + _block_size * z };//left

              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 0] = { _block_size + _block_size * x, 0. + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 1] = { _block_size + _block_size * x, 0. + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 2] = { _block_size + _block_size * x, _block_size + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 3] = { _block_size + _block_size * x, _block_size + _block_size * y, _block_size + _block_size * z };//right

              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 0] = { 0. + _block_size * x, _block_size + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 1] = { _block_size + _block_size * x, _block_size + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 2] = { _block_size + _block_size * x, _block_size + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 3] = { 0. + _block_size * x, _block_size + _block_size * y, _block_size + _block_size * z };//top

              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 0] = { _block_size + _block_size * x, 0. + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 1] = { 0. + _block_size * x, 0. + _block_size * y, 0. + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 2] = { 0. + _block_size * x, 0. + _block_size * y, _block_size + _block_size * z };
              vertex[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 3] = { _block_size + _block_size * x, 0. + _block_size * y, _block_size + _block_size * z };//bottom
            }
          }
        }
        GL_VERTEX_BUFFER_CHUNK.init<POINT3D<double>>(vertex.size() * sizeof(POINT3D<double>), vertex.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
      }
    }
    // void set_status_ptr(uint& stat) {
    //   *_status_ptr = &stat;
    // }
    uint& get_status() {
      return *_status_ptr;
    }
    uint get_max_status() {
      return _max_status;
    }
    void gl_texture_gen() {
      if (GL_TEXTURE_BUFFER_CHUNK.empty()) {
        RG_Array<POINT2D<double>>gentextures;
        textures.push_back(RG_Atlas_Standart.find("Grass"));
        textures.push_back(RG_Atlas_Standart.find("Dirt"));
        textures.push_back(RG_Atlas_Standart.find("Stone"));
        if (textures[0] < 0)
          RG_Debug::addl(RG_LOG_LOCK_ERROR, "Texture Grass Not Found");
        if (textures[1] < 0)
          RG_Debug::addl(RG_LOG_LOCK_ERROR, "Texture Dirt Not Found");
        if (textures[2] < 0)
          RG_Debug::addl(RG_LOG_LOCK_ERROR, "Texture Stone Not Found");

        gentextures.resize(_size.x * _size.y * _size.z * 4 * 6);
        int texture_now = textures[0];
        // int index_el = 0, index_ver = 0, index_tex = 0;
        for (int y = 0; y < _size.y; y++) {
          for (int z = 0; z < _size.z; z++) {
            for (int x = 0; x < _size.x; x++) {
              if (_chunk.get(x, y, z) == Block_Type::Grass) {
                texture_now = textures[0];
              }elif(_chunk.get(x, y, z) == Block_Type::Dirt) {
                texture_now = textures[1];
              }elif(_chunk.get(x, y, z) == Block_Type::Stone) {
                texture_now = textures[2];
              }
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 0] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 1] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 0. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 2] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 0. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 0 * 4 + 3] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };//front

              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 0] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 3. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 1] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 2] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 1 * 4 + 3] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 3. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };//back

              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 0] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 1] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 2] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 2 * 4 + 3] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };//left

              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 0] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 4. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 1] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 3. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 2] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 3. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 3 * 4 + 3] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 4. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };//right

              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 0] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 1] = { ((RG_Atlas_Standart[texture_now].size.x * 2. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 2] = { ((RG_Atlas_Standart[texture_now].size.x * 3. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 4 * 4 + 3] = { ((RG_Atlas_Standart[texture_now].size.x * 3. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };//top

              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 0] = { ((RG_Atlas_Standart[texture_now].size.x * 0. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 1] = { ((RG_Atlas_Standart[texture_now].size.x * 0. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 2] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 1. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };
              gentextures[y * _size.z * _size.x * 24 + z * _size.x * 24 + x * 24 + 5 * 4 + 3] = { ((RG_Atlas_Standart[texture_now].size.x * 1. / 3.) + ((double)RG_Atlas_Standart[texture_now].pos.x)) / (double)RG_Atlas_Standart.get_size().x, (((RG_Atlas_Standart[texture_now].size.y * 2. / 4.) + (RG_Atlas_Standart[texture_now].pos.y)) / (double)RG_Atlas_Standart.get_size().y) };//bottom

            }
          }
        }
        GL_TEXTURE_BUFFER_CHUNK.init<POINT2D<double>>(gentextures.size() * sizeof(POINT2D<double>), gentextures.data(), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

      }
    }
    void raw_gen(POINT3D<uint>p) {
      if (*_status_ptr == 0) {
        if (_mut_ptr)
          _mut_ptr->lock();
        *_status_ptr++;
        if (_mut_ptr)
          _mut_ptr->unlock();
        _pos = p;
        rgLoadIdentity(mat);
        rgTranslatef(_pos.x * _size.x * _block_size, _pos.y * _size.y * _block_size, _pos.z * _size.z * _block_size, mat);
        rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
        rgScalef(\
          size.x * scale.x, \
          size.y * scale.y, \
          size.z * scale.z, mat);

        _chunk.resize(_size);


        // RG_Buffer::raw.textures.push_back();
        // RG_Buffer::raw.textures[0].resize(_size.x * _size.y * _size.z * 4 * 6);


        for (int y = 0; y < _size.y; y++) {
          for (int z = 0; z < _size.z; z++) {
            for (int x = 0; x < _size.x; x++) {
              if (y == _size.y - 1)
                _chunk.get(x, y, z) = Block_Type::Grass;
              elif(y > _size.y - 10)
                _chunk.get(x, y, z) = Block_Type::Dirt;
              else
                _chunk.get(x, y, z) = Block_Type::Stone;
              if (_mut_ptr)
                _mut_ptr->lock();
              *_status_ptr++;
              if (_mut_ptr)
                _mut_ptr->unlock();
            }
          }
        }
        if (_mut_ptr)
          _mut_ptr->lock();
        *_status_ptr++;
        if (_mut_ptr)
          _mut_ptr->unlock();


      }
      // _status = *_status_ptr;
    }
    void index_gen() {
      if (GL_INDEXES_BUFFER_CHUNK.empty()) {
        RG_Array<uint>indexes;
        indexes.fast_clear();
        indexes.reserve(_size.x * _size.y * _size.z * 6 * 6);

        // RG_Buffer::raw.elements.fast_clear();
        // RG_Buffer::raw.elements.reserve(_size.x * _size.y * _size.z * 6 * 6);
        for (int y = 0; y < _size.y; y++) {
          for (int z = 0; z < _size.z; z++) {
            for (int x = 0; x < _size.x; x++) {

              // RG_Buffer::raw.elements[index_el++] = ((0 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
              if (((z == 0) && (true)) || _chunk.get(x, y, z - 1) == Air) {
                indexes.push_back((0 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((1 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((3 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((0 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//front
              }
              if (((z == _size.z - 1) && (true)) || _chunk.get(x, y, z + 1) == Air) {
                indexes.push_back((0 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((1 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((3 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((0 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//back
              }
              if (((x == 0) && (true)) || _chunk.get(x - 1, y, z) == Air) {
                indexes.push_back((0 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((1 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((3 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((0 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//left
              }
              if (((x == _size.x - 1) && (true)) || _chunk.get(x + 1, y, z) == Air) {
                indexes.push_back((0 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((1 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((3 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((0 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//right
              }
              if (((y == _size.y - 1) && (true)) || _chunk.get(x, y + 1, z) == Air) {
                indexes.push_back((0 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((1 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((3 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((0 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//top
              }
              if (((y == 0) && (true)) || _chunk.get(x, y - 1, z) == Air) {
                indexes.push_back((0 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((1 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((2 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((3 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
                indexes.push_back((0 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//bottom            
              }
              // *_status_ptr++;
            }
          }
        }
        // rg_cout<<"INDEXES:\n"<<indexes.size()<<"\n";
        // indexes.print();
        // rg_cout<<endl;
        gl_indexes_size = indexes.size();
        GL_INDEXES_BUFFER_CHUNK.init<uint>(indexes.size() * sizeof(uint), indexes.data(), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);


      }
      // *_status_ptr++;
    }
    void gl_gen() {
      index_gen();
      gl_buffer_gen();
      gl_texture_gen();
      // GL_Gen();
    }
    void draw(RG_Camera& cam = *RG_Camera_StandartPtr) {

      // if (RG_Buffer::gl.textures.size() > 0) {
      //   tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

      //   if (tempFrame > 1) {
      //     frame += floor(tempFrame);
      //     tempFrame -= floor(tempFrame);
      //   }
      //   frame = frame % (maxFrames);//textures.size();
      //   RG_Mods::Texture_On();
      //   glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
      //   rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
      // } else RG_Mods::Texture_Off();
      if (GL_TEXTURE_BUFFER_CHUNK.is_init()) {
        RG_Mods::Texture_On();
        // glBindBuffer(GL_ARRAY_BUFFER, GL_TEXTURE_BUFFER_CHUNK);
        GL_TEXTURE_BUFFER_CHUNK.bind();
        rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
      } else RG_Mods::Texture_Off();
      if (GL_VERTEX_BUFFER_CHUNK.is_init()) {
        // glBindBuffer(GL_ARRAY_BUFFER, GL_VERTEX_BUFFER_CHUNK);
        GL_VERTEX_BUFFER_CHUNK.bind();
        rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
      } else { gl_gen(); return; }
      if (GL_COLOR_BUFFER_CHUNK.is_init()) {
        // glBindBuffer(GL_ARRAY_BUFFER, GL_COLOR_BUFFER_CHUNK);
        GL_COLOR_BUFFER_CHUNK.bind();
        rgColorPointer(4, GL_DOUBLE, 0, nullptr);
      } else { gl_gen(); return; }//TODO fix everything
      //cam.loadMatrix();


      if (is_gui) {
        rgLoadGuiMatrix(GuiType);
      } else {
        //rgLoadCamMatrix();
        cam.loadMatrix();
      }
      rgLoadMatrixf(mat);
      if (GL_INDEXES_BUFFER_CHUNK.is_init()) {
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_INDEXES_BUFFER_CHUNK);
        GL_INDEXES_BUFFER_CHUNK.bind();
        glDrawElements(GL_TRIANGLES, gl_indexes_size, GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }
    }
    inline POINT3D<uint> get_pos() {
      return _pos;
    }

    void gen(POINT3D<uint>pos) {
      raw_gen(pos);
      gl_gen();
      // GL_Gen();
    }
    /*
    for (int y = 0; y < _size.y; y++) {
      for (int z = 0; z < _size.z; z++) {
        for (int x = 0; x < _size.x; x++) {

          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 0 * 6 + 0] = ((0 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 0 * 6 + 1] = ((1 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 0 * 6 + 2] = ((2 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 0 * 6 + 3] = ((2 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 0 * 6 + 4] = ((3 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 0 * 6 + 5] = ((0 + (4 * 0)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//front

          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 1 * 6 + 0] = ((0 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 1 * 6 + 1] = ((1 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 1 * 6 + 2] = ((2 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 1 * 6 + 3] = ((2 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 1 * 6 + 4] = ((3 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 1 * 6 + 5] = ((0 + (4 * 1)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//back

          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 2 * 6 + 0] = ((0 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 2 * 6 + 1] = ((1 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 2 * 6 + 2] = ((2 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 2 * 6 + 3] = ((2 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 2 * 6 + 4] = ((3 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 2 * 6 + 5] = ((0 + (4 * 2)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//left

          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 3 * 6 + 0] = ((0 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 3 * 6 + 1] = ((1 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 3 * 6 + 2] = ((2 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 3 * 6 + 3] = ((2 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 3 * 6 + 4] = ((3 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 3 * 6 + 5] = ((0 + (4 * 3)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//right

          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 4 * 6 + 0] = ((0 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 4 * 6 + 1] = ((1 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 4 * 6 + 2] = ((2 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 4 * 6 + 3] = ((2 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 4 * 6 + 4] = ((3 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 4 * 6 + 5] = ((0 + (4 * 4)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//top

          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 5 * 6 + 0] = ((0 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 5 * 6 + 1] = ((1 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 5 * 6 + 2] = ((2 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 5 * 6 + 3] = ((2 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 5 * 6 + 4] = ((3 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));
          RG_Buffer::raw.elements[y * _size.z * _size.x * 36 + z * _size.x * 36 + x * 36 + 5 * 6 + 5] = ((0 + (4 * 5)) + (24 * (y * _size.z * _size.x + z * _size.x + x)));//bottom
        }
      }
    }
    */

    // RG_Buffer::raw.textures[0] = {
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 0 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 0 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//front
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//back
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//left
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 4 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 4 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//right
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 3 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 3 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//top
    //   {((RG_Atlas_Standart[textures[0]].size.x * 0 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 0 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//bottom
    // };
    /*RG_Buffer::raw.elements = {
      (0 + (4 * 0)),
      (1 + (4 * 0)),
      (2 + (4 * 0)),
      (2 + (4 * 0)),
      (3 + (4 * 0)),
      (0 + (4 * 0)),//front
      (0 + (4 * 1)),
      (1 + (4 * 1)),
      (2 + (4 * 1)),
      (2 + (4 * 1)),
      (3 + (4 * 1)),
      (0 + (4 * 1)),//back
      (0 + (4 * 2)),
      (1 + (4 * 2)),
      (2 + (4 * 2)),
      (2 + (4 * 2)),
      (3 + (4 * 2)),
      (0 + (4 * 2)),//left
      (0 + (4 * 3)),
      (1 + (4 * 3)),
      (2 + (4 * 3)),
      (2 + (4 * 3)),
      (3 + (4 * 3)),
      (0 + (4 * 3)),//right
      (0 + (4 * 4)),
      (1 + (4 * 4)),
      (2 + (4 * 4)),
      (2 + (4 * 4)),
      (3 + (4 * 4)),
      (0 + (4 * 4)),//top
      (0 + (4 * 5)),
      (1 + (4 * 5)),
      (2 + (4 * 5)),
      (2 + (4 * 5)),
      (3 + (4 * 5)),
      (0 + (4 * 5)) //bottom
    };*/
    // RG_Buffer::raw.vertex = ({
    //   {0,0,0},
    //   {1,0,0},
    //   {1,1,0},
    //   {0,1,0},//front
    //   {1,0,1},
    //   {0,0,1},
    //   {0,1,1},
    //   {1,1,1},//back
    //   {0,0,0},
    //   {0,0,1},
    //   {0,1,1},
    //   {0,1,0},//left
    //   {1,0,1},
    //   {1,0,0},
    //   {1,1,0},
    //   {1,1,1},//right
    //   {0,1,0},
    //   {1,1,0},
    //   {1,1,1},
    //   {0,1,1},//top
    //   {1,0,0},
    //   {0,0,0},
    //   {0,0,1},
    //   {1,0,1}//bottom
    //   });



    // RG_Buffer::raw.vertex = {
    //     {0,0,0},{1,0,0},{1,1,0},{0,1,0},//front
    //     {1,0,1},{0,0,1},{0,1,1},{1,1,1},//back

    //     {0,0,0},{0,0,1},{0,1,1},{0,1,0},//left
    //     {1,0,1},{1,0,0},{1,1,0},{1,1,1},//right

    //     {0,1,0},{1,1,0},{1,1,1},{0,1,1},//top
    //     {1,0,0},{0,0,0},{0,0,1},{1,0,1}//bottom
    // };
    // RG_Array<POINT2D<double>> texture_coord = {
    //   {(1. / 3.) * ((1 + 0)),(1. / 4.) * ((1))},	{(1. / 3.) * ((1 + 0)),(1. / 4.) * ((0))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((0))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((1))},//front
    //   {(1. / 3.) * ((1 + 0)),(1. / 4.) * ((2 + 1))},	{(1. / 3.) * ((1 + 0)),(1. / 4.) * ((2 + 0))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((2 + 0))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((2 + 1))},//back

    //   {(1. / 3.) * ((1 + 0)),(1. / 4.) * ((1 + 1))},	{(1. / 3.) * ((1 + 0)),(1. / 4.) * ((1 + 0))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((1 + 0))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((1 + 1))},//left
    //   {(1. / 3.) * ((1 + 0)),(1. / 4.) * ((4))},	{(1. / 3.) * ((1 + 0)),(1. / 4.) * ((3))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((3))},	{(1. / 3.) * ((1 + 1)),(1. / 4.) * ((4))},//right

    //   {(1. / 3.) * ((2 + 0)),(1. / 4.) * ((1 + 1))},	{(1. / 3.) * ((2 + 0)),(1. / 4.) * ((1 + 0))},	{(1. / 3.) * ((2 + 1)),(1. / 4.) * ((1 + 0))},	{(1. / 3.) * ((2 + 1)),(1. / 4.) * ((1 + 1))},//top
    //   {(1. / 3.) * ((0)),(1. / 4.) * ((1 + 1))},	{(1. / 3.) * ((0)),(1. / 4.) * ((1 + 0))},	{(1. / 3.) * ((1)),(1. / 4.) * ((1 + 0))},	{(1. / 3.) * ((1)),(1. / 4.) * ((1 + 1))},//bottom
    // };
    /**/
    // textures.push_back(RG_Standart::Atlas->find("Grass"));
    // RG_Buffer::raw.textures.resize(1);
    // RG_Buffer::raw.textures[0].resize(texture_coord.size());
    // for (int i = 0;i < texture_coord.size();i++) {
    //   // RG_Buffer::raw.textures[0][i].x = ((texture_coord[i].x * RG_Atlas_Standart[textures[0]].size.x) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x;
    //   // RG_Buffer::raw.textures[0][i].y = ((texture_coord[i].y * RG_Atlas_Standart[textures[0]].size.y) + (RG_Atlas_Standart[textures[0]].pos.y)) / RG_Atlas_Standart.get_size().y;


    // }
    // RG_Buffer::raw.textures[0] = {
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 0 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 0 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//front
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//back
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//left
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 4 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 3 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 4 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//right
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 2 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 3 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 3 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//top
    //   {((RG_Atlas_Standart[textures[0]].size.x * 0 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 0 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 1 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},
    //   {((RG_Atlas_Standart[textures[0]].size.x * 1 / 3.) + (RG_Atlas_Standart[textures[0]].pos.x)) / RG_Atlas_Standart.get_size().x, ((RG_Atlas_Standart[textures[0]].size.y * 2 / 4.) + (RG_Atlas_Standart[textures[0]].pos.y) / RG_Atlas_Standart.get_size().y)},//bottom
    // };
    /**/

  // void draw() {
  //   Mesh::draw();
  // }
  };
}