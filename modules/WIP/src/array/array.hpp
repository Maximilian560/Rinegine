#pragma once

namespace Rinegine {
  namespace WIP {

    struct RawArray {
    protected:
      void* data = nullptr;
      size_t _size = 0;
    public:
      // size_t sizetype = 0;
      virtual void init(size_t nsize) {
        if (data) { RG_LOG_ERROR(std::format("RawArray error: mem already init"));return; }
        else {
          data = Kernel::Allocator::GetDefault().allocate(nsize);
          if (MEM_CELL_TEST(data)) {
            RG_LOG_CRITICAL("RawArray error: init failed");
          }
          _size = nsize;
        }
        size_t size() {
          return _size;
        }
        void resize(size_t nsize) {
          if (!data)init(nsize);
          else {
          }
          Kernel::Allocator::GetDefault().reallocate(data, nsize);
        }
      }
      inline void clear() {
        Kernel::Allocator::GetDefault().deallocate(data);
        _size = 0;
      }
      virtual ~RawArray() {
        clear();
      };
    };
    template<class type>
    class Array :public RawArray {
      type*& data = reinterpret_cast<type*&>(RawArray::data);
    public:
      Array(size_t nsize) {
        init(nsize);
      }
      void init(size_t nsize) {
        RawArray::init(nsize * sizeof(type));
      }
      type& operator[](size_t index) {
        if (index > _size) {
          RG_LOG_CRITICAL(std::format("Array operator[] error: out of range [{}>{}]", index, _size));
        }
        return data[index];
      }
    };

    void ArrayTests() {
      RG_LOG_INFO(std::format("Start Array tests"));
      RG_LOG_INFO(std::format("Create Array and try init by 40 bytes"));
      Array<char> test(40);
      RG_LOG_INFO(std::format("Try read, rewrite and read again"));
      for (int i = 0; i < 40;i++) {
        rg_cout << (long long)test[(size_t)i] << ", ";
        test[(size_t)i] = (char)i;
        if (i == 39)rg_cout << std::endl;
      }
      for (int i = 0;i < 40;i++) {
        rg_cout << (long long)test[(size_t)i] << ", ";
        if (i == 39)rg_cout << std::endl;
      }
      RG_LOG_INFO(std::format("Try init large mem and dealloc both"));
      Array<size_t> test2(1024 * 1024 * 1024);
      RG_LOG_INFO(std::format("Try init"));
      for (size_t i = 0; i < 1024 * 1024 * 1024;i++) {
        test2[i] = i;
      }
      RG_LOG_INFO(std::format("Try dealloc"));
      test.clear();
      test2.clear();
      RG_LOG_INFO(std::format("Start Array tests"));

    }
  }
}