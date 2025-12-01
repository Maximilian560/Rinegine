#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/types/array"

template <class type>
class RG_Matrix;
#ifndef RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER
#define RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER 16
#endif
uint RG_GLOBAL_ARRAY_PUSH_RESERVE = RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER;//global variable that specifies the number of additional elements to reserve when the array overflows in the fastpush method of the RG_Array class (don't change the already created arrays)
template<class type>
class RG_Array {
protected:
  uint _size = 0, _truesize = 0, _fast_reserve_size = RG_GLOBAL_ARRAY_PUSH_RESERVE;
  type* _array = nullptr;
  type* _arrayend = nullptr;
public:
  // const uint& size = _size; 
  RG_Array() {}
  // RG_Array(to_rvalue(type) in) {
  //   init(1,in);
  // }
  // explicit 
RG_Array(RG_Array&& other) noexcept {
  clear();
  _size = other._size;
  _truesize = other._truesize;
  _fast_reserve_size = other._fast_reserve_size;
  _array = other._array;
  _arrayend = other._arrayend;

  other._size = 0;
  other._truesize = 0;
  other._fast_reserve_size = RG_GLOBAL_ARRAY_PUSH_RESERVE;
  other._array = nullptr;
  other._arrayend = nullptr;
}

  RG_Array(to_rvalue(RG_Array<type>) in) {
    init(in);
  }
  RG_Array(int size, to_rvalue(type) ar) {
    init(size, ar);
  }
  RG_Array(int size, type* ar) {
    init(size, ar);
  }
  // RG_Array(to_rvalue(uint) size, to_rrvalue(type*) ar) {
  //   init(size, ar);
  // }
  // RG_Array(to_rvalue(uint) size) {
  //   init(size);
  // }
  RG_Array(int size) {
    init(size);
  }
  RG_Array(to_rvalue(initializer_list<type>) list) {
    init(list);
  }
  template<class type2>
  RG_Array(to_rvalue(initializer_list<type2>) list) {
    init(list);
  }
  explicit RG_Array(to_rrvalue(type*)ar) {
    init(ar);
  }
  // operator type* () {
  //   return _array;
  // }
  void fastpop() {
    if (_size == 0)return;
    _size--;
    _arrayend = _array + _size;
  }
  //*FAST PUSH

  void fastpush() {
    _size++;
    if (_truesize < _size)reserve(_size + _fast_reserve_size);
    _arrayend = _array + _size;
  }

  void fastpush(to_rvalue(type) in) {
    _size++;
    if (_truesize < _size)reserve(_size + _fast_reserve_size);
    _array[_size - 1] = in;
    _arrayend = _array + _size;
  }
  void fastpush(to_rvalue(RG_Array<type>) in) {
    uint old_size = _size;
    _size += in.size();
    if (_truesize < _size)reserve(_size + _fast_reserve_size);
    for (int i = 0; i < in.size(); i++) {
      _array[i + old_size] = in[i];
    }
  }
  void fastpush(to_rvalue(initializer_list<type>) list) {
    uint old_size = _size;
    _size += list.size();
    if (_truesize < _size)reserve(_size + _fast_reserve_size);
    for (int i = 0; i < list.size(); i++) {
      _array[i + old_size] = list.begin()[i];
    }
  }
  void fastpush(to_rvalue(type*) in) {
    if (!RG::s_memtest(in))RG_LOG_LOCK_CRITICAL("RG_Array error: fastpush(type*in), 'in' is not an array of type RG\n"); //TODO переделать текст ошибки(ок)
    uint old_size = _size;
    uint in_size = RG::s_get_size(in);
    _size += in_size;
    if (_truesize < _size)reserve(_size + _fast_reserve_size);
    for (int i = 0; i < in_size; i++) {
      _array[i + old_size] = in[i];
    }
  }
  /**/
  void fastpush(type&& in) noexcept {
    _size++;
    if (_truesize < _size)reserve(_size + _fast_reserve_size);
    // _array[_size - 1] = std::move(in);
    _array[_size - 1] = std::forward<type>(in);
    _arrayend = _array + _size;
  }
  void fastpush(RG_Array<type>&& in) {
    uint old_size = _size;
    _size += in.size();
    if (_truesize < _size)reserve(_size + _fast_reserve_size);
    for (int i = 0; i < in.size(); i++) {
      _array[i + old_size] = std::move(in[i]);
    }
  }
  /**/
  template <typename... Args>
  void fastemplace(Args&&... args) noexcept {
    reserve(_size + _fast_reserve_size);
    _array[_size] = type(std::forward<Args>(args)...);
    _size++;
  }
  //!FAST PUSH
  void set_push_reserve(to_rvalue(uint)in) { _fast_reserve_size = in; }



  // RG_Array(to_rvalue(uint) size, to_rvalue(type*) ar) {
  //   init(size, ar);
  // }

  ///////////INIT
  void init(int size) {
    resize(size);
  }
  void init(to_rvalue(int) size, to_rvalue(type) ar) {
    resize(size);
    //int fillsize = rg_min(size, _size);
    for (int i = 0; i < size; i++) {
      _array[i] = ar;
    }
  }
  void init(to_rvalue(type*)ar) {
    if (ar == nullptr) { clear(); return; }
    if (!RG::s_memtest(ar))RG_LOG_LOCK_CRITICAL("RG_Array error: init(type*arr), type is not RG array\n");
    resize(RG::s_get_size(ar));
    for (int i = 0; i < _size; i++) {
      _array[i] = ar[i];
    }
  }
  void init(to_rvalue(uint)size, to_rrvalue(type*)ar) {
    resize(size);

    for (int i = 0; i < _size; i++) {
      _array[i] = ar[i];
    }
  }
  void init(to_rvalue(initializer_list<type>) list) {
    resize(list.size());
    for (int i = 0; i < list.size(); i++) {
      _array[i] = list.begin()[i];
    }
  }
  template<class type2>
  void init(to_rvalue(initializer_list<type2>) list) {
    resize(list.size());
    for (int i = 0; i < list.size(); i++) {
      _array[i] = list.begin()[i];
    }
  }
  void init(to_rvalue(RG_Array<type>) in) {
    resize(in.size());
    for (int i = 0; i < in.size(); i++) {
      _array[i] = in[i];
    }
  }
  /*void init(to_rvalue(uint) size, to_rvalue(RG_Array<type>) in) {
    resize(size);
    for (int i = 0; i < in.size();i++) {
      _array[i] = in[i];
    }
  }*/


  ///////////RESIZE/FILL
  void resize(int size) {
    if (_truesize >= size) {
      _size = size;
      _arrayend = _array + size;
      return;
    }
    if (size <= 0) { clear(); return; }
    if (size != _size) {
      RG::s_resize(_array, size);
      _truesize = size;
      _size = size;
      _arrayend = _array + size;
      // __size = (((uint*)(_array)) - 1);
      // _size = *__size;
    }
  }
  void fast_clear() {
    if (_truesize) {
      _size = 0;
      _arrayend = _array;
    }
  }
  void reserve(to_rvalue(int) size) {
    if (_truesize >= size) {
      _arrayend = _array + size;
      return;
    }
    if (size <= 0) { clear(); return; }
    if (size != _size) {
      RG::s_resize(_array, size);
      _truesize = size;
      _arrayend = _array + size;
    }
  }
  void reserve_fill() {
    _size = _truesize;
    _arrayend = _array + _truesize;
  }
  void reinit(to_rvalue(int) size) {
    if (size <= 0) { clear(); return; }
    if (size != _size) {
      RG::s_renew(_array, size);
      _truesize = size;
      _size = size;
      _arrayend = _array + size;
      // __size = (((uint*)(_array)) - 1);
      // _size = *__size;
    }
  }

  ////


  //void fill([](int)(*in)){
  //template<class gen>
  void fill(type(*in)()) {
    type* temp = _array;
    for (; temp != _arrayend; ++temp) {
      *temp = in();
    }
  }


  /*void fill(int(*in)()){
    type* temp = _array;
    for(;temp!=_arrayend;++temp){
      *temp = in();
    }
  }*/
  void fillfull(to_rvalue(uint) size, to_rvalue(type) in) {
    for (int i = 0; i < size; i++) {
      _array[i] = in;
    }
  }

  void fill(type in) {
    type* temp = _array;
    for (; temp != _arrayend; ++temp) {
      *temp = in;
    }
  }
  template<class type2>
  void fill(type2 in) {
    type* temp = _array;
    for (; temp != _arrayend; ++temp) {
      *temp = in;
    }
  }

  void fill(type* in) {
    type* temp = _array;
    for (int i = 0; temp != _arrayend; ++temp) {
      *temp = in[i];
      i++;
    }
  }
  void push_back() {
    resize(_size + 1);
  }
  void push_back(to_rvalue(type) in) {
    push_back();
    _array[_size - 1] = in;
  }
  void push_back(to_rvalue(RG_Array<type>) in) {
    uint old_size = _size;
    resize(in.size() + _size);
    for (int i = 0; i < in.size(); i++) {
      _array[i + old_size] = in[i];
    }
  }
  void push_back(to_rvalue(initializer_list<type>) list) {
    uint old_size = _size;
    resize(list.size() + _size);
    for (int i = 0; i < list.size(); i++) {
      _array[i + old_size] = list.begin()[i];
    }
  }
  void push_back(to_rvalue(type*) in) {
    if (!RG::s_memtest(in))RG_LOG_LOCK_CRITICAL("RG_Array error: push_back(type*in), 'in' is not an array of type RG\n"); //TODO переделать текст ошибки(ок)
    uint old_size = _size;
    uint in_size = RG::s_get_size(in);
    resize(in_size + _size);
    for (int i = 0; i < in_size; i++) {
      _array[i + old_size] = in[i];
    }
  }
  template <typename... Args>
  void emplace_back(Args&&... args) {

    resize(_size + 1);
    _array[_size - 1] = type(std::forward<Args>(args)...);
  }
  //////////ORETATORS

  type& operator[](to_rvalue(int) index) const {
    if (_size == 0)RG_LOG_LOCK_CRITICAL("Array index out of range, index '" + to_string(index) + "', array size '" + to_string(_size) + "'");

    int true_index = index;
    if (index < 0) {
      true_index = _size + index;
    }
    if (true_index >= _size)RG_LOG_LOCK_CRITICAL("Array index out of range, index '" + to_string(index) + "', array size '" + to_string(_size) + "'");
    return _array[true_index];
  }
  type& operator[](to_rvalue(uint) index) const {

    uint true_index = index;
    if (index < 0) {
      true_index = _size + index;
    }
    if (true_index >= _size)RG_LOG_LOCK_CRITICAL("Array index out of range, index '" + to_string(index) + "', array size '" + to_string(_size) + "'");
    return _array[true_index];
  }

  RG_Array<type>operator*(to_rvalue(RG_Matrix<type>) mat)const {
    if (_size != mat.size(1))RG_LOG_LOCK_CRITICAL("Array multiplication error (_array by matrix) _array size does not match matrix width, _array size '" + to_string(_size) + "', matrix height '" + to_string(mat.size(1)) + "'");
    uint nsizex = mat.size(0);
    RG_Array<type>out(mat.size(0));


    for (uint x = 0; x < nsizex; x++) {
      for (uint k = 0; k < _size; k++) {
        out[x] += _array[k] * mat.get(x, k);
      }
    }
    return out;
  }
  RG_Array<type>operator*(to_rvalue(type) in)const {
    RG_Array<type> out(_size);
    for (int i = 0; i < _size; i++) {
      out[i] = _array[i] * in;
    }
    return out;
  }
  RG_Array<type>operator-(to_rvalue(RG_Array<type>)in)const {
    if (_size != in.size())RG_LOG_LOCK_CRITICAL("Array subtraction error arrays size does not match, first _array size '" + to_string(_size) + "', second _array size '" + to_string(in.size()) + "'");
    RG_Array<type>out(_size);
    for (int i = 0; i < _size; i++) {
      out[i] = _array[i] - in[i];
    }
    return out;
  }
  RG_Array<type>operator+(to_rvalue(RG_Array<type>)in)const {
    if (_size != in.size())RG_LOG_LOCK_CRITICAL("Array addition error arrays size does not match, first _array size '" + to_string(_size) + "', second _array size '" + to_string(in.size()) + "'");
    RG_Array<type>out(_size);
    for (int i = 0; i < _size; i++) {
      out[i] = _array[i] + in[i];
    }
    return out;
  }

  RG_Array<type>operator%(to_rvalue(RG_Array<type>)in)const {
    if (_size != in.size())RG_LOG_LOCK_CRITICAL("Array multiplication error arrays size does not match, first _array size '" + to_string(_size) + "', second _array size '" + to_string(in.size()) + "'");

    RG_Array<type>out(_size);
    for (int i = 0; i < _size; i++) {
      out[i] = _array[i] * in[i];
    }

    return out;
  }
  RG_Array<type>operator*(to_rvalue(RG_Array<type>)in)const {
    if (_size != in.size())RG_LOG_LOCK_CRITICAL("Array multiplication error arrays size does not match, first _array size '" + to_string(_size) + "', second _array size '" + to_string(in.size()) + "'");
    RG_Array<type>out(_size);
    for (int i = 0; i < _size; i++) {
      out = _array[i] * in[i];
    }
    return out;
  }



  template<class em>
  void operator=(to_rvalue(em)in) {
    RG_LOG_LOCK_CRITICAL("Array operator= error, this type is not supported");
  }

  void operator=(to_rvalue(type) in) {
    if (_size != 0) { RG_LOG_LOCK_WARNING("RG_Array operator=, array is not empty and will be cleared!"); }
    resize(1);
    _array[0] = in;
  }
  void operator=(to_rvalue(RG_Array<type>)in) {
    init(in);
  }
  void operator=(const initializer_list<type>* list) {
    init(list);
  }
  void operator=(const char* in) {
    clear();
    for (int i = 0; in[i] != '\0'; i++) {
      _size++;
    }
    init(_size, in);
  }
  void copy(to_rvalue(RG_Array<type>)in) {
    init(in);
  }
  void operator-=(to_rvalue(RG_Array<type>)in) {
    if (_size != in.size())RG_LOG_LOCK_CRITICAL("Array subtraction error arrays size does not match, first _array size '" + to_string(_size) + "', second _array size '" + to_string(in.size()) + "'");
    for (int i = 0; i < _size; i++) {
      _array[i] -= in[i];
    }
  }
  void operator+=(to_rvalue(RG_Array<type>)in) {
    if (_size != in.size())RG_LOG_LOCK_CRITICAL("Array addition error arrays size does not match, first _array size '" + to_string(_size) + "', second _array size '" + to_string(in.size()) + "'");
    for (int i = 0; i < _size; i++) {
      _array[i] += in[i];
    }
  }





  //////OTHER OPERATORS
  // operator type* ()const {
  //   return _array;
  // }
  // operator uint()const {
  //   return _size;
  // }
  // operator type& ()const {
  //   return _array[0];
  // }
  RG_Matrix<type> transpose()const {
    RG_Matrix<type> transpos(1, _size, _array);
    return transpos;
  }
  type* get() const {
    return _array;
  }
  type* data()const {
    return _array;
  }
  type* get_array() const {
    return _array;
  }
  type* get_arr() const {
    return _array;
  }
  type& get(to_rvalue(int) index) const {

    int true_index = index;
    if (index < 0) {
      true_index = _size + index;
    }
    if (true_index >= _size)RG_LOG_LOCK_CRITICAL("Array index out of range, index '" + to_string(index) + "', array size '" + to_string(_size) + "'");
    return _array[true_index];
  }
  type& get(to_rvalue(uint) index) const {

    uint true_index = index;
    if (index < 0) {
      true_index = _size + index;
    }
    if (true_index >= _size)RG_LOG_LOCK_CRITICAL("Array index out of range, index '" + to_string(index) + "', array size '" + to_string(_size) + "'");
    return _array[true_index];
  }
  ////////SPECIAL
  type* begin()const {
    return _array;
  }
  type* end()const {
    return _arrayend;
  }

  type* back()const {
    return _arrayend - 1;
  }
  //////////SIZE
  uint size() const {
    return _size;
  }
  uint true_size() const {
    return _truesize;
  }
  ////////OTHER
  void print() const {
    RG::s_print(_array);
  }
  rg_string get_string(){
    rg_string out;
    for(int i = 0; i<_size;i++){
      out+=rg_to_string(_array[i]);
      if(i!=i-1)out+=RG_L", ";
    }
    return out;
  }
  type sum()const {
    type out = 0;
    for (type* temp = _array; temp != _arrayend; ++temp) {
      out += *temp;
    }
    return out;
  }
  void fill_range_random(to_rvalue(type) min, to_rvalue(type) max) {
    for (uint i = 0; i < _size; i++) {
      _array[i] = (rand() / (RAND_MAX / (max - min))) + min;
    }
  }
  bool empty()const {
    return (_array == nullptr);
  }
  void movefill(to_rvalue(uint) size, type* arr) {
    if (!RG::s_memtest(arr)) { RG_LOG_LOCK_ERROR("RG_Array movefill(uint size, type*arr) error, 'arr' is not RG type"); init(size, arr); return; };
    clear();
    _size = size;
    _array = arr;
  }




  ////////CLEAR
  // void clear() {
  //   if (size == 4 * 4)
  //     RG_LOG_LOCK_WARNING("IT IS... MATRIX ARRAY!!!");
  //   if (_array == nullptr) return;
  //   if (size == 4 * 4)
  //     RG_LOG_LOCK_WARNING("array not nullptr");
  //   if (_truesize == 0) return;
  //   if (size == 4 * 4)
  //     RG_LOG_LOCK_WARNING("_truesize not nullptr!");
  //   _truesize = 0;
  //   _size = 0;
  //   _arrayend = 0;
  //   _array = 0;
  //   if (size == 4 * 4)
  //     RG_LOG_LOCK_WARNING("AND NOW!!! S_DELETE (answer the leak has AROUND)");
  //   RG::s_delete(_array);
  // }
  void clear() {
    if (_array == nullptr) return;
    // if (_truesize == 0) return;
    RG::s_delete(_array);
    _truesize = 0;
    _size = 0;
    _array = 0;
    _arrayend = 0;
  }
  void fastclear() {
    if (_array == nullptr) return;
    // if (_truesize == 0) return;
    _arrayend = _array;
    _size = 0;
  }
  ~RG_Array() {
    if (_array == nullptr) return;
    // if (_truesize == 0) return;
    RG::s_delete(_array);
    _truesize = 0;
    _size = 0;
    _array = nullptr;
    _arrayend = 0;
  }
};



// wofstream& operator<<(wofstream& out, to_rvalue(RG_Array<wchar_t>) arr) {
//   for (int i = 0; i < arr.size();i++) {
//     out << (wchar_t(arr[i]));
//   }
//   return out;
// }
wofstream& operator<<(wofstream& out, to_rvalue(RG_Array<wstring>) arr) {
  for (int i = 0; i < arr.size(); i++)out << arr[i] << L", ";
  return out;
}

/*
template<class type>
wofstream& operator<<(wofstream& out, to_rvalue(RG_Array<type>) arr) {
  out<<L'[';
  for(type& i:arr){
    out<<i;
    if(&i!=&arr[-1])out<<L", ";
  }
  out<<L']';
  return out;
}

template<class type>
ofstream& operator<<(ofstream& out, to_rvalue(RG_Array<type>) arr) {
  out<<'[';
  for(type& i:arr){
    out<<i;
    if(&i!=&arr[-1])out<<", ";
  }
  out<<']';
  return out;
}*/
void rg_stringToChar(RG_Array<char>& c, string s) {
  c.resize(s.size());
  for (int i = 0; i < s.size() - 1; i++) {
    c[i] = s[i];
  }
}

RG_Array<char> rg_stringToChar(string s) {
  RG_Array<char> c(s.size());
  for (int i = 0; i < s.size() - 1; i++) {
    c[i] = s[i];
  }
  return c;
}