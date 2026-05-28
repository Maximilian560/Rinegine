#pragma once


#ifndef _GLIBCXX_NOEXCEPT
#  define _GLIBCXX_NOEXCEPT noexcept
#endif
#ifndef _GLIBCXX_NOEXCEPT_PARM
#  define _GLIBCXX_NOEXCEPT_PARM
#endif
#ifndef _GLIBCXX_NOEXCEPT_QUAL
#  define _GLIBCXX_NOEXCEPT_QUAL noexcept
#endif
#ifndef _GLIBCXX_CONSTEXPR
#  define _GLIBCXX_CONSTEXPR constexpr
#endif
#ifndef _GLIBCXX17_CONSTEXPR
#  define _GLIBCXX17_CONSTEXPR constexpr
#endif
#ifndef _GLIBCXX_USE_NOEXCEPT
#  define _GLIBCXX_USE_NOEXCEPT noexcept
#endif
#if !defined(__clang__) && __has_builtin(__is_trivially_destructible)
#  define __has_trivial_destructor(T) __is_trivially_destructible(T)
#endif
namespace Rinegine {
  namespace Kernel {
    

    // Пул-аллокатор с bump pointer (O(1) аллокация, без malloc)
    // Выделяет большой блок, раздаёт ноды сдвигом указателя
    struct PoolAllocator {
      static constexpr size_t DEFAULT_BLOCK = 1 << 20; // 1MB начальный блок
      static constexpr size_t GROW_BLOCK = 1 << 21; // 2MB при росте

      struct Block {
        unsigned char* ptr;
        size_t size;
        size_t used;
      };

      static constexpr int MAX_BLOCKS = 8;
      static Block blocks[MAX_BLOCKS];
      static int block_count;
      static int current;

      static void reset() {
        for (int i = 0; i < block_count; i++)
          std::free(blocks[i].ptr);
        block_count = 0;
        current = -1;
      }

      static void* allocate(std::size_t n) {
        // Выровнять до 16 байт (для SSE/AVX)
        n = (n + 15) & ~size_t(15);

        // Ищем блок с местом
        for (int i = 0; i < block_count; i++) {
          if (blocks[i].used + n <= blocks[i].size) {
            void* ptr = blocks[i].ptr + blocks[i].used;
            blocks[i].used += n;
            return ptr;
          }
        }

        // Новый блок
        if (block_count >= MAX_BLOCKS) {
          // Fallback на malloc
          void* ptr = std::malloc(n);
          if (!ptr) throw std::bad_alloc{};
          return ptr;
        }

        size_t new_size = (block_count == 0) ? DEFAULT_BLOCK : GROW_BLOCK;
        unsigned char* mem = static_cast<unsigned char*>(std::malloc(new_size));
        if (!mem) throw std::bad_alloc{};

        current = block_count;
        blocks[block_count].ptr = mem;
        blocks[block_count].size = new_size;
        blocks[block_count].used = n;
        block_count++;
        return mem;
      }

      static void deallocate(void*) noexcept {
        // Bump allocator — deallocate no-op.
        // Память освобождается при reset() из clear()
      }
    };

    inline PoolAllocator::Block PoolAllocator::blocks[MAX_BLOCKS];
    inline int PoolAllocator::block_count = 0;
    inline int PoolAllocator::current = -1;

    // Аллокатор используемый для выделения памяти

    struct HEAD_TYPE {
      size_t flags;
      size_t size;
    };
    enum MEM_FLAG : size_t {
      FREE = 0,
      INIT = 1,
      //[todo] something else
    };
    struct MEM_HEAD : public HEAD_TYPE {//head of memory
      //[todo] maybe I'll come up with something new
    };
    //[mem_conductor_head]
    //[head]
    //[mem]
    //[head]
    //[mem]

    class MEM_CONDUCTOR_WorkName {

    };
  }
}
