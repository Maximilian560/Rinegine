#pragma once

#pragma once
namespace Rinegine::Kernel {

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
    int clear() requires Util::has_trivial_destructor_v<U> {
      NODE<T>* tmp = head;
      while (tmp != nullptr) {
        NODE<T>* next = tmp->next;
        tmp = next;
        Rinegine::Kernel::GlobalAllocator.deallocate(tmp);
      }
      Rinegine::Kernel::GlobalAllocator.deallocate(head);
      head = nullptr;
      end = nullptr;
      count = 0;
      // Rinegine::Kernel::GlobalAllocator.clear();//[todo] Before creating a normal allocator
      return 0;
    }
    template <typename U = T>
    int clear() requires (!Util::has_trivial_destructor_v<U>) {
      NODE<T>* tmp = head;
      while (tmp != nullptr) {
        NODE<T>* next = tmp->next;
        tmp->data.~T();
        tmp = next;
        Rinegine::Kernel::GlobalAllocator.deallocate(tmp);
      }
      Rinegine::Kernel::GlobalAllocator.deallocate(head);
      head = nullptr;
      end = nullptr;
      count = 0;
      // Rinegine::Kernel::GlobalAllocator.clear();//[todo] Before creating a normal allocator
      return 0;
    }
    //[PUSH]
    //* Создаёт новую ноду и возвращает указатель на неё (предназначено для использования внутри класса/библиотеки)
    //* Примечание: не инициализирует data, используйте emplace после push если требуется инициализация
    NODE<T>* push() {
      NODE<T>* node = reinterpret_cast<NODE<T>*>(Rinegine::Kernel::GlobalAllocator.allocate(sizeof(NODE<T>)));
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
      NODE<T>* node = reinterpret_cast<NODE<T>*>(Rinegine::Kernel::GlobalAllocator.allocate(sizeof(NODE<T>)));
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
      NODE<T>* node = static_cast<NODE<T>*>(Rinegine::Kernel::GlobalAllocator.allocate(sizeof(NODE<T>)));
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
      NODE<T>* node = reinterpret_cast<NODE<T>*>(Rinegine::Kernel::GlobalAllocator.allocate(sizeof(NODE<T>)));
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
      if constexpr (!Util::has_trivial_destructor_v<T>) {
        pos->data.~T();
      }
      Rinegine::Kernel::GlobalAllocator.deallocate(pos);

      if (prev) prev->next = next;
      else head = next;
      if (next) next->prev = prev;
      else end = prev;
      --count;
      return next;
    }

    //* Вариант push для POD типов (без вызова конструкторов)
    template <typename U>
      requires Util::is_trivially_constructible_v<U, const U&>
    NODE<T>* push_trivial(const U& in) {
      NODE<T>* node = push();
      if (node) {
        node->data = in;
      }
      return node;
    }

    // Вариант push для POD типов с перемещением
    template <typename U>
      requires Util::is_trivially_constructible_v<U, U&&>
    NODE<T>* push_trivial(U&& in) {
      NODE<T>* node = push();
      if (node) {
        node->data = std::move(in);
      }
      return node;
    }

    // Возвращает указатель на последний элемент, либо nullptr если список пуст
    T* back() {
      return end ? Util::addressof(end->data) : nullptr;
    }

    // Возвращает указатель на первый элемент, либо nullptr если список пуст
    T* front() {
      return head ? Util::addressof(head->data) : nullptr;
    }

    // Для POD: просто копируем байты
    template<typename... Args>
    int emplace(Args&&... args) requires Util::is_trivially_constructible_v<T, Args...> {
      NODE<T>* new_node = static_cast<NODE<T>*>(Rinegine::Kernel::GlobalAllocator.allocate(sizeof(NODE<T>)));
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
    int emplace(Args&&... args) requires (!Util::is_trivially_constructible_v<T, Args...>) {
      NODE<T>* new_node = static_cast<NODE<T>*>(Rinegine::Kernel::GlobalAllocator.allocate(sizeof(NODE<T>)));
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

}