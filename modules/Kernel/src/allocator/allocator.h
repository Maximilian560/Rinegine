#pragma once

namespace Rinegine::Kernel {
#ifndef CACHE_LINE_SIZE_BYTE
#define CACHE_LINE_SIZE_BYTE 64
#endif

  // Инкапсуляция макроса в типобезопасную constexpr переменную
  // const size_t SYS_PAGE_SIZE = low_level::get_page_size();
  const std::size_t low_level::CACHE_LINE_SIZE = CACHE_LINE_SIZE_BYTE;

  static_assert((low_level::CACHE_LINE_SIZE& (low_level::CACHE_LINE_SIZE - 1)) == 0, "CACHE_LINE_SIZE must be a power of 2");
  // class Allocator {

  struct Allocator::ChainNode {
    BYTE* prev = nullptr;
    BYTE* next = nullptr;
    BYTE* end = nullptr;
    size_t cell_used = 0;
  };

  BYTE* Allocator::pool = nullptr;
  BYTE* Allocator::next = nullptr;
  size_t Allocator::size_of_allocate = 1;
  // inline static BYTE* free_cells = nullptr;
  size_t Allocator::allocator_count = 0;

  Allocator::Allocator() {
    allocator_count++;
    if (!pool)init();
  }
  void Allocator::init() {
    size_of_allocate = rg_min(MAX_ALLOC_PAGE_SIZE, SYS_PAGE_SIZE * BASE_ALLOC_PAGE_COUNT * ((size_of_allocate / 2) + 1));
    pool = SYS_GET_RAW_MEM(size_of_allocate);
    ((ChainNode*)pool)->next = nullptr;
    ((ChainNode*)pool)->prev = nullptr;
    ((ChainNode*)pool)->cell_used = 0;
    ((ChainNode*)pool)->end = pool + size_of_allocate;
    next = Rinegine::Kernel::low_level::align_ptr_to_cache_line(pool + sizeof(ChainNode));
  }
  BYTE* Allocator::allocate(size_t in) {
    in = Rinegine::Kernel::low_level::align_to_cache_line(in);
    if (next + in >= ((ChainNode*)pool)->end) {
      size_of_allocate = rg_max(rg_min(MAX_ALLOC_PAGE_SIZE, SYS_PAGE_SIZE * BASE_ALLOC_PAGE_COUNT * ((size_of_allocate / 2) + 1)), Rinegine::Kernel::low_level::align_to_cache_line(in) + low_level::CACHE_LINE_SIZE);
      BYTE* next_pool = SYS_GET_RAW_MEM(size_of_allocate);
      ((ChainNode*)pool)->next = next_pool;
      ((ChainNode*)next_pool)->next = nullptr;
      ((ChainNode*)next_pool)->prev = pool;
      ((ChainNode*)next_pool)->cell_used = 0;
      ((ChainNode*)next_pool)->end = next_pool + size_of_allocate;
      pool = next_pool;
      next = Rinegine::Kernel::low_level::align_ptr_to_cache_line(pool + sizeof(ChainNode));
    }
    ((ChainNode*)pool)->cell_used++;
    BYTE* out = next;
    next += in;
    return out;
  }
  void Allocator::deallocate(void* ptr, size_t) {
    if (ptr == nullptr)return;
    BYTE* head = pool;
    while (!(ptr > head && ptr < ((ChainNode*)head)->end)) {
      head = ((ChainNode*)head)->prev;
      if (head == nullptr) [[unlikely]] {
        RG_LOG_LOCK_WARN(std::format("deallocate get a ptr, but this allocator hasn't this"));
        return;
      }
    }
    ((ChainNode*)head)->cell_used--;
    if (((ChainNode*)head)->cell_used == 0) [[unlikely]] {
      if (head != pool) [[unlikely]] {
        if (((ChainNode*)head)->prev)
          ((ChainNode*)(((ChainNode*)head)->prev))->next = ((ChainNode*)head)->next;
        if (((ChainNode*)head)->next)
          ((ChainNode*)(((ChainNode*)head)->next))->prev = ((ChainNode*)head)->prev;
        Rinegine::Kernel::SYS_DEL_RAW_MEM(head);
      }
      else {
        next = Rinegine::Kernel::low_level::align_ptr_to_cache_line(pool + sizeof(ChainNode));
      }
    }


  }
  Allocator::~Allocator() {
    allocator_count--;
    if (allocator_count == 0) [[unlikely]] {
      while (pool != nullptr) {
        BYTE* head = ((ChainNode*)pool)->prev;
        Rinegine::Kernel::SYS_DEL_RAW_MEM(pool);
        pool = head;
      }
    }
  }
  // };

}
