#pragma once
namespace Rinegine::Kernel::Concept {
  template<typename Alloc>
  concept Allocator = requires(Alloc a, std::size_t n) {
    { a.allocate(n) } -> std::same_as<void*>;
    { a.deallocate(nullptr) };// -> std::same_as<void>;
  };
}