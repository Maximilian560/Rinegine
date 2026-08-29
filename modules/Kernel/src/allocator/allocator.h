#pragma once

namespace Rinegine::Kernel {
#ifndef CACHE_LINE_SIZE_BYTE
#define CACHE_LINE_SIZE_BYTE 64
#endif

  // Rinegine::Kernel::Allocator Rinegine::Kernel::Allocator::GetDefault() = Rinegine::Kernel::Allocator();
  // Инкапсуляция макроса в типобезопасную constexpr переменную
  // const size_t Allocator::page_size() = low_level::get_page_size();
  const std::size_t low_level::CACHE_LINE_SIZE = CACHE_LINE_SIZE_BYTE;

  static_assert((low_level::CACHE_LINE_SIZE& (low_level::CACHE_LINE_SIZE - 1)) == 0, "CACHE_LINE_SIZE must be a power of 2");
  // class Allocator {

  struct Allocator::ChainNode {
    BYTE* prev = nullptr;
    BYTE* next = nullptr;
    BYTE* end = nullptr;
    size_t cell_used = 0;
  };

  // BYTE* Allocator::pool = nullptr;
  // BYTE* Allocator::next = nullptr;
  // size_t Allocator::size_of_allocate = 1;
  // inline static BYTE* free_cells = nullptr;
  size_t Allocator::allocator_count = 0;

  Allocator::Allocator() {
    allocator_count++;
    current_pool = nullptr;
    current_end = nullptr;
    // if (!pool)
    init();
  }
  void Allocator::init() {
    if (current_pool != nullptr)return;
    size_of_allocate = rg_min(Allocator::max_alloc_page_size, Allocator::page_size() * Allocator::base_alloc_page_count * ((size_of_allocate / 2) + 1));
    current_pool = SYS_GET_RAW_MEM(size_of_allocate);
    ((ChainNode*)current_pool)->next = nullptr;
    ((ChainNode*)current_pool)->prev = nullptr;
    ((ChainNode*)current_pool)->cell_used = 0;
    ((ChainNode*)current_pool)->end = current_pool + size_of_allocate;
    current_end = ((ChainNode*)current_pool)->end;
    next = Rinegine::Kernel::low_level::align_ptr_to_cache_line(current_pool + sizeof(ChainNode));
  }
  BYTE* Allocator::allocate(size_t in) {
    if (!current_pool) [[unlikely]]init();
    // in = Rinegine::Kernel::low_level::align_to_cache_line(in);

    if (next + in >= current_end) [[unlikely]] {
      size_of_allocate = rg_max(rg_min(Allocator::max_alloc_page_size, Allocator::page_size() * Allocator::base_alloc_page_count * ((size_of_allocate / 2) + 1)), /*Rinegine::Kernel::low_level::align_to_cache_line(in)*/ in + low_level::CACHE_LINE_SIZE);
      BYTE* next_pool = SYS_GET_RAW_MEM(size_of_allocate);
      ((ChainNode*)current_pool)->next = next_pool;
      ((ChainNode*)next_pool)->next = nullptr;
      ((ChainNode*)next_pool)->prev = current_pool;
      ((ChainNode*)next_pool)->cell_used = 0;
      ((ChainNode*)next_pool)->end = next_pool + size_of_allocate;
      current_end = ((ChainNode*)next_pool)->end;
      current_pool = next_pool;
      next = Rinegine::Kernel::low_level::align_ptr_to_cache_line(current_pool + sizeof(ChainNode));
      // next = current_pool + sizeof(ChainNode);
    }
    ((ChainNode*)current_pool)->cell_used++;
    BYTE* out = next;
    next += in;
    return out;
  }
  void Allocator::deallocate(void* ptr, size_t) {
    if (current_pool == nullptr) { RG_LOG_LOCK_ERROR("Deallocation of a memory cell from an already deallocated pool");return; }
    if (ptr == nullptr)return;
    BYTE* head = current_pool;
    while (!(ptr > head && ptr < ((ChainNode*)head)->end)) {
      head = ((ChainNode*)head)->prev;
      if (head == nullptr) [[unlikely]] {
        RG_LOG_LOCK_WARN(std::format("deallocate get a ptr, but this allocator hasn't this"));
        return;
      }
    }
    ((ChainNode*)head)->cell_used--;
    if (((ChainNode*)head)->cell_used == 0) [[unlikely]] {
      if (head != current_pool) [[unlikely]] {
        if (((ChainNode*)head)->prev)
          ((ChainNode*)(((ChainNode*)head)->prev))->next = ((ChainNode*)head)->next;
        if (((ChainNode*)head)->next)
          ((ChainNode*)(((ChainNode*)head)->next))->prev = ((ChainNode*)head)->prev;
        Rinegine::Kernel::SYS_DEL_RAW_MEM(head);
      }
      else {
        next = Rinegine::Kernel::low_level::align_ptr_to_cache_line(current_pool + sizeof(ChainNode));
      }
    }


  }
  Allocator::~Allocator() {
    allocator_count--;
    if (allocator_count == 0) [[unlikely]] {
      while (current_pool != nullptr) {
        BYTE* head = ((ChainNode*)current_pool)->prev;
        Rinegine::Kernel::SYS_DEL_RAW_MEM(current_pool);
        current_pool = head;
      }
    }
  }
  // alignas(Allocator) static char default_storage[sizeof(Allocator)];
  // Rinegine::Kernel::Allocator& Rinegine::Kernel::Allocator::GetDefault() = *new (default_storage) Allocator();
  // Rinegine::Kernel::Allocator& Rinegine::Kernel::Allocator::GetDefault() = Rinegine::Kernel::Allocator::instance();
  // };

}
