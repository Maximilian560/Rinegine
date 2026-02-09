// #pragma once

// namespace Rinegine::Kernel {
//   void RawMap::set_type_size(size_t a, size_t b) {
//     if (key == nullptr && value == nullptr) {
//       key = (char*)(s_raw_new(a));
//       value = (char*)(s_raw_new(b));
//       count = 1;
//     }
//     else {
//       RG_LOG_LOCK_CRITICAL("RawMap: key or value is not nullptr");
//     }
//   }
//   void RawMap::resize(size_t size) {
//     rg_cout << "DEBUG-1: key is " << (long)key << " value is " << (long)value << std::endl;
//     s_raw_resize(((DATA_OUT*&)key), size * (sizeof(key) / count));
//     s_raw_resize(((DATA_OUT*&)value), size * (sizeof(value) / count));
//     count = size;
//     rg_cout << "DEBUG-2: key is " << (long)key << " value is " << (long)value << std::endl;
//   }
//   void RawMap::init(size_t keyin, size_t valuein, size_t size) {
//     rg_cout << "DEBUG-1: key is " << (long)key << " value is " << (long)value << std::endl;
//     if (key == nullptr) {

//       key = (char*)(s_raw_new(keyin * size));
//     }
//     else {
//       s_raw_resize(((DATA_OUT*&)key), keyin * size);
//     }
//     if (value == nullptr) {
//       value = (char*)(s_raw_new(valuein * size));
//     }
//     else {
//       s_raw_resize(((DATA_OUT*&)value), valuein * size);
//     }
//     rg_cout << "DEBUG-2: key is " << (long)key << " value is " << (long)value << std::endl;
//   }

//   RawMap::~RawMap() {
//     s_raw_delete(((DATA_OUT*)key));
//     s_raw_delete(((DATA_OUT*)value));
//   }
// }

// namespace Rinegine::Kernel{
//   template <class Key, class Value>
//   class Map{
//     Key key;
//     Value value;
//   public:
//     Map(): key(), value(){}
    
//   };
// }