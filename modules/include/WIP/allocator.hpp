#pragma once
#include <Rinegine/Kernel>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <new>
#include <atomic>

#if defined(__linux__) || defined(__ANDROID__)
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#elif defined(_WIN32)
#include <windows.h>
#else
#error "Unsupported OS"
#endif

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
namespace Rinegine {
  namespace Kernel {
    namespace Traits {
#if defined(__clang__) && __has_builtin(__is_trivially_destructible)
#  undef __has_trivial_destructor
#  define __has_trivial_destructor(T) __is_trivially_destructible(T)
#endif
      // Тривиальный конструктор
      template<typename T, typename... Args>
      struct is_trivially_constructible {
        static constexpr bool value = __is_trivially_constructible(T, Args...);
      };
      template<typename T, typename... Args>
      inline constexpr bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;

      // Тривиальный тип (POD — memcpy безопасен)
      template<typename T>
      struct is_trivial {
        static constexpr bool value = __is_trivial(T);
      };
      template<typename T>
      inline constexpr bool is_trivial_v = is_trivial<T>::value;

      // Тривиальный деструктор (без ~T())
      template<typename T>
      struct has_trivial_destructor {
        static constexpr bool value = __has_trivial_destructor(T);
      };
      template<typename T>
      inline constexpr bool has_trivial_destructor_v = has_trivial_destructor<T>::value;
    }
    namespace Addres {//[todo] rename

      template<typename T>
      __attribute__((__always_inline__))
        inline _GLIBCXX_CONSTEXPR T*
        __addressof(T& __r) _GLIBCXX_NOEXCEPT
      {
        return __builtin_addressof(__r);
      }

      template<typename _Tp>
      [[__nodiscard__, __gnu__::__always_inline__]]
      inline _GLIBCXX17_CONSTEXPR _Tp*
        addressof(_Tp& __r) noexcept
      {
        return __addressof(__r);
      }
    }
    //Концепт для аллокатора (для добавления только подходящих аллокаторов)
    template<typename Alloc>
    concept Allocator = requires(Alloc a, std::size_t n) {
      { a.allocate(n) } -> std::same_as<void*>;
      { a.deallocate(nullptr) };// -> std::same_as<void>;
    };


    // Обёртка для маллок аллокатора для того, чтоб его можно было использовать в концепте и как универсальный аллокатор
    struct MallocAllocator {
      static void* allocate(std::size_t n) {
        void* ptr = std::malloc(n);
        if (!ptr) throw std::bad_alloc{};
        return ptr;
      }
      static void deallocate(void* ptr) noexcept {
        std::free(ptr);
      }
    };

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
    using ALLOCATOR = PoolAllocator;

    //  === Базовые типы === //
    // Нода
    template<class T>
    struct NODE {
      T data;
      NODE* next = nullptr;
      NODE* prev = nullptr;
    };

    // Список
    template <class T>
    struct LIST {
      NODE<T>* head = nullptr;
      NODE<T>* end = nullptr;
      size_t count = 0;
      //[INIT]
      LIST() {
        init();
      }
      int init() {
        head = nullptr;
        end = nullptr;
        count = 0;
        return 0;
      }
      //[DESTROY]
      ~LIST() {
        clear();
      }
      template <typename U = T>
      int clear() requires Traits::has_trivial_destructor_v<U> {
        NODE<T>* tmp = head;
        while (tmp != nullptr) {
          NODE<T>* next = tmp->next;
          tmp = next;
        }
        head = nullptr;
        end = nullptr;
        count = 0;
        ALLOCATOR::reset();//[todo] Before creating a normal allocator
        return 0;
      }
      template <typename U = T>
      int clear() requires (!Traits::has_trivial_destructor_v<U>) {
        NODE<T>* tmp = head;
        while (tmp != nullptr) {
          NODE<T>* next = tmp->next;
          tmp->data.~T();
          tmp = next;
        }
        head = nullptr;
        end = nullptr;
        count = 0;
        ALLOCATOR::reset();//[todo] Before creating a normal allocator
        return 0;
      }
      //[PUSH]
      //* Создаёт новую ноду и возвращает указатель на неё (предназначено для использования внутри класса/библиотеки)
      //* Примечание: не инициализирует data, используйте emplace после push если требуется инициализация
      NODE<T>* push() {
        NODE<T>* node = static_cast<NODE<T>*>(ALLOCATOR::allocate(sizeof(NODE<T>)));
        if (!node) return nullptr;

        node->next = nullptr;
        node->prev = end;
        if (end) end->next = node;
        else head = node; // первый элемент
        end = node;
        ++count;
        return node;
      }

      //* Создаёт ноду, копирует в data значение in и возвращает указатель на неё
      NODE<T>* push(const T& in) {
        NODE<T>* node = push();
        if (node) {
          ::new (static_cast<void*>(std::addressof(node->data))) T(in); // placement new copy
        }
        return node;
      }

      //* Создаёт ноду, перемещает значение in в data и возвращает указатель на неё
      NODE<T>* push(T&& in) {
        NODE<T>* node = push();
        if (node) {
          ::new (static_cast<void*>(std::addressof(node->data))) T(std::move(in)); // placement new move
        }
        return node;
      }

      //* Вставляет ноду в начало списка (push_front)
      NODE<T>* push_front() {
        NODE<T>* node = static_cast<NODE<T>*>(ALLOCATOR::allocate(sizeof(NODE<T>)));
        if (!node) return nullptr;

        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        else end = node;
        head = node;
        ++count;
        return node;
      }

      //* push_front с копированием
      NODE<T>* push_front(const T& in) {
        NODE<T>* node = push_front();
        if (node) {
          ::new (static_cast<void*>(std::addressof(node->data))) T(in);
        }
        return node;
      }

      //* push_front с перемещением
      NODE<T>* push_front(T&& in) {
        NODE<T>* node = push_front();
        if (node) {
          ::new (static_cast<void*>(std::addressof(node->data))) T(std::move(in));
        }
        return node;
      }

      // ═══════════════════════════════════════════
      //  Insert / Erase
      // ═══════════════════════════════════════════

      //* Вставляет ноду перед pos, инициализирует копированием
      NODE<T>* insert_before(NODE<T>* pos, const T& in) {
        if (!pos) return push(in);  // nullptr = push_back
        NODE<T>* node = static_cast<NODE<T>*>(ALLOCATOR::allocate(sizeof(NODE<T>)));
        if (!node) return nullptr;
        ::new (static_cast<void*>(std::addressof(node->data))) T(in);

        node->prev = pos->prev;
        node->next = pos;
        if (pos->prev) pos->prev->next = node;
        else head = node;
        pos->prev = node;
        ++count;
        return node;
      }

      //* Вставляет ноду перед pos, инициализирует перемещением
      NODE<T>* insert_before(NODE<T>* pos, T&& in) {
        if (!pos) return push(std::move(in));
        NODE<T>* node = static_cast<NODE<T>*>(ALLOCATOR::allocate(sizeof(NODE<T>)));
        if (!node) return nullptr;
        ::new (static_cast<void*>(std::addressof(node->data))) T(std::move(in));

        node->prev = pos->prev;
        node->next = pos;
        if (pos->prev) pos->prev->next = node;
        else head = node;
        pos->prev = node;
        ++count;
        return node;
      }

      //* Удаляет ноду pos, возвращает следующую (или nullptr)
      NODE<T>* erase(NODE<T>* pos) {
        if (!pos) return nullptr;
        NODE<T>* next = pos->next;
        NODE<T>* prev = pos->prev;

        // Вызываем деструктор если нужен
        if constexpr (!Traits::has_trivial_destructor_v<T>) {
          pos->data.~T();
        }
        ALLOCATOR::deallocate(pos);

        if (prev) prev->next = next;
        else head = next;
        if (next) next->prev = prev;
        else end = prev;
        --count;
        return next;
      }

      //* Вариант push для POD типов (без вызова конструкторов)
      template <typename U>
        requires Traits::is_trivially_constructible_v<U, const U&>
      NODE<T>* push_trivial(const U& in) {
        NODE<T>* node = push();
        if (node) {
          node->data = in;
        }
        return node;
      }

      // Вариант push для POD типов с перемещением
      template <typename U>
        requires Traits::is_trivially_constructible_v<U, U&&>
      NODE<T>* push_trivial(U&& in) {
        NODE<T>* node = push();
        if (node) {
          node->data = std::move(in);
        }
        return node;
      }

      // Возвращает указатель на последний элемент, либо nullptr если список пуст
      T* back() {
        return end ? Addres::addressof(end->data) : nullptr;
      }

      // Возвращает указатель на первый элемент, либо nullptr если список пуст
      T* front() {
        return head ? Addres::addressof(head->data) : nullptr;
      }

      // Для POD: просто копируем байты
      template<typename... Args>
      int emplace(Args&&... args) requires Traits::is_trivially_constructible_v<T, Args...> {
        NODE<T>* new_node = static_cast<NODE<T>*>(ALLOCATOR::allocate(sizeof(NODE<T>)));
        if (!new_node) throw - 1;

        // Обнуляем указатели
        new_node->next = nullptr;
        new_node->prev = nullptr;

        // Присваиваем данные напрямую — никаких конструкторов
        new_node->data = T(static_cast<Args&&>(args)...);

        if (end) end->next = new_node;
        else head = new_node;
        end = new_node;
        ++count;
        return 0;
      }

      // Для сложных типов: placement new
      template<typename... Args>
      int emplace(Args&&... args) requires (!Traits::is_trivially_constructible_v<T, Args...>) {
        NODE<T>* new_node = static_cast<NODE<T>*>(ALLOCATOR::allocate(sizeof(NODE<T>)));
        if (!new_node) throw - 1;

        // Ручная инициализация полей NODE
        new_node->next = nullptr;
        new_node->prev = nullptr;

        // Вызов конструктора T в выделенной памяти
        T* data_ptr = &new_node->data;
        new (data_ptr) T(static_cast<Args&&>(args)...);

        if (end) end->next = new_node;
        else head = new_node;
        end = new_node;
        ++count;
        return 0;
      }

      // int push(T&& in) {
      //   emplace(static_cast<T&&>(in));
      //   return 0;
      // }
      //[POP]

    };

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
