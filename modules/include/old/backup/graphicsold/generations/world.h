#pragma once

namespace RG {
  class World {
    struct SystemChunk {
      Chunk* chunk;
      int index;
    };
    RG_Array<Chunk> _chunks_raw;
    RG_Matrix3D<SystemChunk> _chunks;
    POINT3D<uint> _chunk_size;
    uint _status = 0;
    uint _max_status = 0;
    uint _max_chunk_status = 0;
    mutex _mut;
    // wstring _status_str = L"Null"
    POINT2D<int> _draw_distance;

    POINT3D<int> _generator_pos;
    thread _gen;
    bool _gen_done = 0;
  public:

    World(int draw_dist = 3, POINT3D<uint>chunk_size = { 32,128,32 }) :_chunk_size(chunk_size), _draw_distance({ draw_dist * 2,int(ceil(draw_dist / 4.) * 2) }) {
      _chunks_raw.init(_draw_distance.x * _draw_distance.y * _draw_distance.x);
      _chunks.init(_draw_distance.x, _draw_distance.y, _draw_distance.x);
      // 
      // if (!_chunks_raw.size()) {
      //   rg_cout << "What? Raw chunk is empty, but should be is: " << _draw_distance.x << " * " << _draw_distance.y << " * " << _draw_distance.x << " = " << _draw_distance.x * _draw_distance.x * _draw_distance.y << endl;
      //   _chunks_raw.init(_draw_distance.x * _draw_distance.x * _draw_distance.y);
      // }
      // if (!_chunks.size(3)) {
      //   rg_cout << "What? Chunks is empty, but should be is: " << _draw_distance.x << " * " << _draw_distance.y << " * " << _draw_distance.x << " = " << _draw_distance.x * _draw_distance.x * _draw_distance.y << endl;
      //   _chunks.init(_draw_distance.x, _draw_distance.y, _draw_distance.x);
      // }
    }

    void status_fix() {
      if (_gen_done)
        _status = _max_status;
    }
    uint get_status() {
      return _status;
    }
    uint get_max_status() {
      return _max_status;
    }
    void join() {
      if (_gen.joinable())
        _gen.join();
    }
    void calculate_max_status() {
      Chunk::calculate_status(_max_chunk_status, _chunk_size);
      _max_status = _max_chunk_status * _draw_distance.x * _draw_distance.x * _draw_distance.y;
    }
    void init() {
      if (_gen.joinable()) {
        RG_Debug::addl(RG_LOG_ERROR, "Generation thread is busy");
        _gen.join();
      }
      _gen = std::move(thread(
        [&]() {
        RG_Array<thread> litlgen;
        litlgen.init(_chunks.size().x * _chunks.size().y * _chunks.size().z);
        // if (!litlgen.size()) {
        //   rg_cout << "What? Array of threads is empty, but should be is: " << _chunks.size().x << " * " << _chunks.size().y << " * " << _chunks.size().z << " = " << _chunks.size().x * _chunks.size().y * _chunks.size().z << endl;
        //   _chunks.init(_chunks.size().x * _chunks.size().y * _chunks.size().z);
        // }
        for (uint y = 0; y < _chunks.size().y; y++) {
          for (uint z = 0; z < _chunks.size().z; z++) {
            for (uint x = 0; x < _chunks.size().x; x++) {
              int chunk_raw_indx = y * _chunks.size().z * _chunks.size().x + z * _chunks.size().x + x;
              // rg_cout << chunk_raw_indx << endl;
              _chunks_raw[chunk_raw_indx].init(_chunk_size);
              _chunks_raw[chunk_raw_indx].set_status(_status);
              _chunks_raw[chunk_raw_indx].set_mutex(_mut);
              _chunks.get(x, y, z) = { &(_chunks_raw[chunk_raw_indx]),chunk_raw_indx };
              litlgen[chunk_raw_indx] = std::move(thread(
                [&, chunk_raw_indx, x, y, z]() {
                _chunks_raw[chunk_raw_indx].raw_gen({ x,y,z });
                // _chunks_raw[chunk_raw_indx].index_gen();
                // rg_cout << "DONE " << chunk_raw_indx << endl;
              }));
              // _chunks.get(_generator_pos.x - (_chunks.size().x / 2) + x, _generator_pos.y - (_chunks.size().y / 2) + y, _generator_pos.z - (_chunks.size().z / 2) + z) = { &_chunks_raw[chunk_raw_indx],chunk_raw_indx };
              // rg_cout << chunk_raw_indx << endl;
              // rg_cout<<z * _chunks.size().y * _chunks.size().x + y * _chunks.size().x + x<<" "<<x<<" "<<y<<" "<<z<<endl;
            }
          }
        }
        for (thread& th : litlgen) {
          if (th.joinable())
            th.join();
        }
        _gen_done = 1;
      }));
    }

    void post_init() {
      for (int y = 0; y < _chunks.size().y; y++) {
        for (int z = 0; z < _chunks.size().z; z++) {
          for (int x = 0; x < _chunks.size().x; x++) {
            _chunks.get(x, y, z).chunk->gl_gen();
          }
        }
      }
    }
    void draw() {
      for (int y = 0; y < _chunks.size().y; y++) {
        for (int z = 0; z < _chunks.size().z; z++) {
          for (int x = 0; x < _chunks.size().x; x++) {
            _chunks.get(x, y, z).chunk->draw();
          }
        }
      }
    }
  };

}
