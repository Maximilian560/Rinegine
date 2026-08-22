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
    NODE<T>* _end = nullptr;
    size_t count = 0;

    class Iterator {
      NODE<T>* current;
    public:
      inline explicit Iterator(NODE<T>* node) noexcept : current(node) {}

      inline Iterator& operator++() noexcept {
        current = current->next;
        return *this;
      }

      inline T& operator*() const noexcept {
        return current->data;
      }

      inline bool operator!=(const Iterator& other) const noexcept {
        return current != other.current;
      }
    };

    inline Iterator begin() noexcept {
      return Iterator(head);
    }

    inline Iterator end() noexcept {
      return Iterator(nullptr);
    }
    //[INIT]
    LIST() {
      init();
    }
    int init() {
      head = nullptr;
      _end = nullptr;
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
        Rinegine::Kernel::Allocator::GetDefault().deallocate(tmp);
      }
      Rinegine::Kernel::Allocator::GetDefault().deallocate(head);
      head = nullptr;
      _end = nullptr;
      count = 0;
      // Rinegine::Kernel::Allocator::GetDefault().clear();//[todo] Before creating a normal allocator
      return 0;
    }
    template <typename U = T>
    int clear() requires (!Util::has_trivial_destructor_v<U>) {
      NODE<T>* tmp = head;
      while (tmp != nullptr) {
        NODE<T>* next = tmp->next;
        tmp->data.~T();
        tmp = next;
        Rinegine::Kernel::Allocator::GetDefault().deallocate(tmp);
      }
      Rinegine::Kernel::Allocator::GetDefault().deallocate(head);
      head = nullptr;
      _end = nullptr;
      count = 0;
      // Rinegine::Kernel::Allocator::GetDefault().clear();//[todo] Before creating a normal allocator
      return 0;
    }
    //[PUSH]
    NODE<T>* push() {
      NODE<T>* node = reinterpret_cast<NODE<T>*>(Rinegine::Kernel::Allocator::GetDefault().allocate(sizeof(NODE<T>)));
      if (!node) return nullptr;

      node->next = nullptr;
      node->prev = _end;
      if (_end) _end->next = node;
      else head = node; // первый элемент
      _end = node;
      ++count;
      return node;
    }

    NODE<T>* push(const T& in) {
      NODE<T>* node = push();
      if (node) {
        ::new (static_cast<void*>(std::addressof(node->data))) T(in); // placement new copy
      }
      return node;
    }

    NODE<T>* push(T&& in) {
      NODE<T>* node = push();
      if (node) {
        ::new (static_cast<void*>(std::addressof(node->data))) T(std::move(in)); // placement new move
      }
      return node;
    }

    NODE<T>* push_front() {
      NODE<T>* node = reinterpret_cast<NODE<T>*>(Rinegine::Kernel::Allocator::GetDefault().allocate(sizeof(NODE<T>)));
      if (!node) return nullptr;

      node->next = head;
      node->prev = nullptr;
      if (head) head->prev = node;
      else _end = node;
      head = node;
      ++count;
      return node;
    }

    NODE<T>* push_front(const T& in) {
      NODE<T>* node = push_front();
      if (node) {
        ::new (static_cast<void*>(std::addressof(node->data))) T(in);
      }
      return node;
    }

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

    NODE<T>* insert_before(NODE<T>* pos, const T& in) {
      if (!pos) return push(in);  // nullptr = push_back
      NODE<T>* node = static_cast<NODE<T>*>(Rinegine::Kernel::Allocator::GetDefault().allocate(sizeof(NODE<T>)));
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

    NODE<T>* insert_before(NODE<T>* pos, T&& in) {
      if (!pos) return push(std::move(in));
      NODE<T>* node = reinterpret_cast<NODE<T>*>(Rinegine::Kernel::Allocator::GetDefault().allocate(sizeof(NODE<T>)));
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

    NODE<T>* erase(NODE<T>* pos) {
      if (!pos) return nullptr;
      NODE<T>* next = pos->next;
      NODE<T>* prev = pos->prev;

      // Вызываем деструктор если нужен
      if constexpr (!Util::has_trivial_destructor_v<T>) {
        pos->data.~T();
      }
      Rinegine::Kernel::Allocator::GetDefault().deallocate(pos);

      if (prev) prev->next = next;
      else head = next;
      if (next) next->prev = prev;
      else _end = prev;
      --count;
      return next;
    }

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
      return _end ? Util::addressof(_end->data) : nullptr;
    }

    // Возвращает указатель на первый элемент, либо nullptr если список пуст
    T* front() {
      return head ? Util::addressof(head->data) : nullptr;
    }

    // Для POD: просто копируем байты
    template<typename... Args>
    int emplace(Args&&... args) requires Util::is_trivially_constructible_v<T, Args...> {
      NODE<T>* new_node = static_cast<NODE<T>*>(Rinegine::Kernel::Allocator::GetDefault().allocate(sizeof(NODE<T>)));
      if (!new_node) throw - 1;

      // Обнуляем указатели
      new_node->next = nullptr;
      new_node->prev = nullptr;

      // Присваиваем данные напрямую — никаких конструкторов
      new_node->data = T(static_cast<Args&&>(args)...);

      if (_end) _end->next = new_node;
      else head = new_node;
      _end = new_node;
      ++count;
      return 0;
    }

    // Для сложных типов: placement new
    template<typename... Args>
    int emplace(Args&&... args) requires (!Util::is_trivially_constructible_v<T, Args...>) {
      NODE<T>* new_node = static_cast<NODE<T>*>(Rinegine::Kernel::Allocator::GetDefault().allocate(sizeof(NODE<T>)));
      if (!new_node) throw - 1;

      // Ручная инициализация полей NODE
      new_node->next = nullptr;
      new_node->prev = nullptr;

      // Вызов конструктора T в выделенной памяти
      T* data_ptr = &new_node->data;
      new (data_ptr) T(static_cast<Args&&>(args)...);

      if (_end) _end->next = new_node;
      else head = new_node;
      _end = new_node;
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