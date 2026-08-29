#pragma once

// namespace Rinegine::Tokenize {
//   class Tokenizer {
//     Rinegine::Kernel::Array<uchar> lexes;// for different lexeme types: operators, data types, etc.
//     size_t pos = 0;
//     size_t _main_size_of_chunk = 8192; // 8 KiB default buffer size for preallocated memory blocks
//     std::string buffer;// buffer    
//     Rinegine::Kernel::Array<Rinegine::Kernel::RG_Map<int>> tokens;//tokens itself
//   public:
//     void init(){//do not place into constructor
//       tokens.resize(_main_size_of_chunk);
//     }
//     void set_size_chunk(size_t size) {
//       if (pos == 0)
//         _main_size_of_chunk = size;
//       else
//         RG_LOG_LOCK_ERROR("Cannot change chunk size after starting parsing");
//     }
//   };
// }