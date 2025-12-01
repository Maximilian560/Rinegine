#pragma once

/*struct rg_raw_array{
  void*arr;
  int size=0;
  void
};*/
#define to_rvalue(type)const type&

template<typename type>
class RG_Matrix;

namespace RG {
  template<typename type>
  class Pointer {
    // inline static int __ID = 0;
    // mutable bool* _init;// = RG::Lock::s_new<bool>(1,false);
    mutable type* _pointer;// = nullptr;
    // void _init_init() {
    //   if (_init == nullptr) _init = RG::Lock::s_new<bool>(1);
    // }
  public:
    inline bool is_init() const {
      return _pointer != nullptr;
    }
    //INIT
    // Pointer() :_pointer(nullptr) {}
    // Pointer(type& in) :_pointer(RG::Lock::s_new<type>(1, in)) {}
    // Pointer(const type& in) :_pointer(RG::Lock::s_new<type>(1, in)) {}
    // Pointer(const type* in) :_pointer(RG::Lock::s_new<type>(1, *in)) {}
    // Pointer(type* in) :_pointer(in) {}
    const type* get() const { return _pointer; }
    Pointer() : _pointer(nullptr) {} // Пустой конструктор
    Pointer(type& in) : _pointer(RG::Lock::s_new<type>(1, in)) {} // Копирование из lvalue
    Pointer(const type& in) : _pointer(RG::Lock::s_new<type>(1, in)) {} // Копирование из const lvalue
    Pointer(const type* in) : _pointer(in ? RG::Lock::s_new<type>(1, *in) : nullptr) {} // Копирование из указателя
    Pointer(type*&& in)noexcept : _pointer(std::move(in)) { in = nullptr; } // Прямое присваивание указателя
    Pointer(type&& in)noexcept { *_pointer = std::move(in); }

    // Pointer(Pointer<type>&& other) noexcept : _pointer(other._pointer) { // Перемещение
    //   other._pointer = nullptr;
    // }
    // Pointer(const Pointer& in) {
    //   if (in.is_init()) {
    //     _pointer = RG::Lock::s_new<type>(1, *in._pointer);
    //   } else {
    //     _pointer = nullptr;
    //   }
    // }
    Pointer(Pointer<type>& in) {
      if (in.is_init()) {
        _pointer = in._pointer;
        in._pointer = nullptr;
      } else {
        _pointer = nullptr;
      }
    }
    Pointer(Pointer<type>&& in) noexcept {
      if (in.is_init()) {
        _pointer = std::move(in._pointer);
        in._pointer = nullptr;
      } else {
        _pointer = nullptr;
      }
    }
    // Pointer(type& in):_pointer(RG::Lock::s_new<type>(1, in)){}



    void init() {
      if (is_init())clear();
      _pointer = RG::Lock::s_new<type>(1);
    }
    void init(const type& in) {
      if (is_init())clear();
      _pointer = RG::Lock::s_new<type>(1, *in);
      // *_pointer = in;
    }
    //OPERATORS
    operator type& () {
      return *_pointer;
    }
    operator type* () {
      return _pointer;
    }

    operator type& () const {
      if (!is_init()) {
        RG_Debug::addl(RG_LOG_ERROR, "Dereferencing null pointer");
      }
      return *_pointer;
    }
    operator const type* () const {
      return _pointer;
    }

    type* operator->() {
      return _pointer;
    }
    // void operator=(const type* in) {
    //   if (is_init())clear();
    //   _pointer = in;
    // }

    // _pointer = RG::Lock::s_new<type>(1, *in._pointer);
    // void operator=(Pointer<type>& in) {
    //   if (is_init())clear();
    //   if (in.is_init()) {
    //     _pointer = in._pointer;
    //     in._pointer = nullptr;
    //   } else {
    //     _pointer = nullptr;
    //   }
    // }

    Pointer& operator=(type&& other) noexcept {
      clear();
      *_pointer = std::move(other);
      return *this;
    }
    Pointer& operator=(type*&& other) noexcept {
      // if (this != &other) {
      clear();
      _pointer = std::move(other);
      other = nullptr;
      // }
      return *this;
    }
    Pointer& operator=(Pointer<type>&& other) noexcept {
      if (this != &other) {
        clear();
        _pointer = other._pointer;
        other._pointer = nullptr;
      }
      return *this;
    }

    // Копирующее присваивание
    Pointer& operator=(const Pointer<type>& other) {
      if (this != &other) {
        clear();
        _pointer = other.is_init() ? RG::Lock::s_new<type>(1, *other._pointer) : nullptr;
      }
      return *this;
    }
    // void operator=(const Pointer<type>& in) {
    //   if (is_init()) clear();
    //   if (in.is_init()) {
    //     _pointer = RG::Lock::s_new<type>(1, *in._pointer);
    //   } else {
    //     _pointer = nullptr;
    //   }
    // }
    // bool operator==(const type* in) {
    //   return _pointer==in;
    // }
    //CLEAR
    void clear() {
      if (is_init()) {
        RG::Lock::s_delete(_pointer);
        _pointer = nullptr;
      }
    }
    ~Pointer() {
      clear();
    }
  };
  /*
  template<class type>
  class Pointer {
    bool* _init;// = RG::Lock::s_new<bool>(1,false);
    type* _pointer;// = nullptr;
    // void _init_init() {
    //   if (_init == nullptr) _init = RG::Lock::s_new<bool>(1);
    // }
  public:
    //INIT
    Pointer():_init(RG::Lock::s_new<bool>(1,false)), _pointer(nullptr) {}

    void init() {
      if (_pointer != nullptr)clear();
      _pointer = RG::Lock::s_new<type>(1);
      *_init = true;
    }
    void init(const type& in) {
      if (_pointer != nullptr)clear();
      _pointer = RG::Lock::s_new<type>(1, in);
      *_init = true;
    }
    //OPERATORS
    operator type& () {
      return *_pointer;
    }
    operator type* () {
      return _pointer;
    }
    type* operator->() {
      return _pointer;
    }
    void operator=(const type* in) {
      if (_pointer != nullptr)clear();
      _pointer = in;
    }
    void operator=(Pointer& in){
      if(_pointer != nullptr)clear();
      _pointer = in._pointer;
      _init = in._init;
      if(*(in._init)){
        in._init = nullptr;
        in._pointer = nullptr;
      }
    }
    void operator=(const Pointer& in){
      if(_pointer != nullptr)clear();
      _pointer = in._pointer;
      _init = in._init;
      RG_Debug::addl(RG_LOG_WARNING,"pointer.h:"+to_string(__LINE__)+" Pointer copy constructor");
    }
    //CLEAR
    void clear() {
      if (_pointer != nullptr)RG::Lock::s_delete(_pointer);
      _pointer = nullptr;
    }
    ~Pointer() {
      clear();
    }
  };*/
}

// template<typename type>
// class RG_Pointer{
//   type*array = nullptr;
//   bool stbi = false;
//   uint SIZE = 0;
//   bool INIT = false;
//   bool noclear = false;
// public:
//   //init
//   /*void init(to_rvalue(uint) size){
//     resize(size);
//   }*/
//   /*void init(to_rvalue(uint) size, const type*arr){
//     fill(size,arr);
//   }*/
//   /*void init(to_rvalue(uint) size, to_rvalue(type) arr){
//     fillfull(size,arr);
//   }*/
//   /*void init(to_rvalue(initializer_list<type>) list){
//     fill(list);
//   }*/
//   /*void init(to_rvalue(RG_Pointer<type>)ar){fill(ar);}*/

//   operator type*()const{
//     return array;
//   }
//   operator int()const{
//     return SIZE;
//   }
//   operator bool()const{
//     return INIT;
//   }
//   operator RG_Matrix<type>()const{
//     return RG_Matrix<type>(size,0,array);
//   }
//   //constructor
//   RG_Pointer(){}
//   /*RG_Pointer(uint size){init(size);}
//   RG_Pointer(initializer_list<type> list){init(list);}
//   RG_Pointer(uint size,type*arr){init(size,arr);}
//   RG_Pointer(uint size,type arr){fillfull(size,arr);}*/
//   //RG_Pointer(RG_Pointer<type>arr){fill(arr);}
//   /*RG_Pointer(const RG_Pointer<type>&arr){fill(arr.SIZE,arr.array);}*/
//   /*RG_Pointer(const char* in){
//     for(int i = 0;;i++){
//       if(in[i]=='\0'){char_fill(i,in);break;};
//     }
//   }
//   RG_Pointer(const wchar_t* in){
//     for(int i = 0;;i++){
//       if(in[i]=='\0'){wchar_fill(i,in);break;};
//     }
//   }*/
//   /*void char_fill(to_rvalue(uint)size, const char*in){
//     resize(size);
//     for(int i = 0; i<size;i++){
//       array[i] = in[i];
//     }
//   }*/
//   /*void wchar_fill(to_rvalue(uint)size, const wchar_t*in){
//     resize(size);
//     for(int i = 0; i<size;i++){
//       array[i] = in[i];
//     }
//   }*/
//   //RG_Pointer(type*arr, uint size){init(size,arr);}
//   //RG_Pointer(type arr,uint size){fillfull(size,arr);}
//   /*template<class type2>
//   RG_Pointer(type2*arr){init(sizeof(arr),arr);}*/

//   ////////
//   //resize
//   /*void resize(to_rvalue(uint) size){
//     if(size>0){
//      if(SIZE==0){
//           array = RG::Lock::s_new<type>(size);
//           if(array == nullptr)throw RG_ERROR_OUT_OF_MEMORY;
//       }
//       else{
//         if(SIZE!= size){
//           RG::Lock::s_resize<type>(array,SIZE,size); 
//           if(array == nullptr)throw RG_ERROR_OUT_OF_MEMORY;
//         }
//       }
//       INIT = true;
//       SIZE = size;
//     }else{

//       if(!INIT) return;
//       clear();
//     }
//   }*/
//   //////
//   //fillа
//   /*void fill(to_rvalue(uint) size, const type*arr){
//     //clear();
//     resize(size);
//     for(int i = 0; i<size;i++){
//       array[i] = arr[i];
//     }
//   }*/
//   /*void fill(const type*arr,to_rvalue(uint) size){
//     //clear();
//     resize(size);
//     for(int i = 0; i<size;i++){
//       array[i] = arr[i];
//     }
//   }*/

//   void fill(to_rvalue(type) arr){
//     for(int i = 0; i<SIZE;i++){
//       array[i] = arr;
//     }
//   }
//   /*void fill(to_rvalue(initializer_list<type>) list){
//     resize(list.size());
//     for(int i = 0; i<SIZE;i++){
//       array[i] = list.begin()[i];
//     }
//   }*/
//   /*void fill(to_rvalue(RG_Pointer<type>) list){
//     clear();
//     resize(list.size());
//     for(int i = 0; i<SIZE;i++){
//       array[i] = list[i];
//     }
//   }*/
//   /*void fillfull(to_rvalue(uint) size, to_rvalue(type) ar){
//     clear();
//     resize(size);
//     for(int i = 0; i<size;i++){
//       array[i] = ar;
//     }
//   }*/
//   void movefill(to_rvalue(uint) size, type*arr){
//     SIZE = size;
//     array = arr;
//   }

//   /*void movefill(const RG_Pointer<type>&arr){
//     //clear();
//     SIZE = arr.SIZE;
//     //array = arr.array;
//     array = RG::Lock::s_new<type>(SIZE);
//     //print();
//     //arr.noclear = true;
//     //arr.clear();
//   }*/
//   ////////
//   //indexs
//   type&operator[](to_rvalue(int) i)const{
//     if(SIZE==0)RG_Debug::addl(RG_LOG_CRITICAL,"Size array = 0");
//     if(i>=0){
//       if(i<=SIZE){
//         return array[i];
//       }
//       else {
//         RG_Debug::addl(RG_LOG_CRITICAL,"i > 0. Size array loss then 'i' in operator[](uint i), i = '"+to_string(i)+"', size = '"+to_string(SIZE)+"'");
//       }
//     }
//     else{
//       if(int(SIZE)+i<SIZE){
//         return array[int(SIZE)+i];
//       }
//       else{
//         RG_Debug::addl(RG_LOG_CRITICAL,"i < 0. i + array size is greater than the array size, array size = '"+to_string(SIZE)+"', i = '"+to_string(i)+"', i + array size'"+to_string(int(SIZE)+i)+"'");
//       }
//     }
//     RG_Debug::addl(RG_LOG_CRITICAL,"Array unknow error");
//     return array[0];
//   }
//   /*void operator=(to_rvalue(RG_Pointer<type>)ar){
//     //resize(ar.size());
//     //wcout<<"WTF "<<ar.size()<<endl;
//     if(SIZE!=0){
//       if(SIZE!=ar.SIZE)wcout<<L"ВНИМАНИЕ! РАЗМЕР МАССИВА БЫЛ ИЗМЕНЁН С "<<SIZE<<L" НА '"<<ar.SIZE<<L"' !!!!\n";
//     }
//     fill(ar.size(),ar.get_arr());
//   }*/
//   /*void operator=(const char* in){
//     clear();
//     for(int i = 0;in[i]!='\0';i++){
//       SIZE++;
//     }
//     fill(SIZE,in);
//   }*/
//   /*void operator=(to_rvalue(RG_Pointer<type>)in){
//     clear();
//     SIZE = in.SIZE;
//     array = in.array;
//     stbi = in.stbi;
//     INIT = in.INIT;
//     noclear = in.noclear;
//     RG_Debug::addl(RG_LOG_WARNING,"A copy of the array has been created, which points to the same array that is associated with the original, thus, when the original is deleted, crashes due to access to unallocated memory or garbage return are possible.");
//   }*/
//   /*void operator=(to_rvalue(type) ar){
//     clear();
//     resize(1);
//     array[0] = ar;
//   }*/
//   void operator=(to_rvalue(initializer_list<type>)list){
//     fill(list);
//   }
//   void operator-=(to_rvalue(RG_Pointer<type>)in){
//     if(SIZE!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array subtraction error arrays size does not match, first array size '"+to_string(SIZE)+"', second array size '"+to_string(in.size())+"'");
//     for(int i =0; i<SIZE;i++){
//       array[i] -= in[i];
//     }
//   }
//   void operator+=(to_rvalue(RG_Pointer<type>)in){
//     if(SIZE!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array addition error arrays size does not match, first array size '"+to_string(SIZE)+"', second array size '"+to_string(in.size())+"'");
//     for(int i =0; i<SIZE;i++){
//       array[i] += in[i];
//     }
//   }


//   type*get_arr()const{
//     return array;
//   }
//   type*get()const{
//     return array;
//   }
//   ////////
//   //push_back
//   /*void push_back(to_rvalue(type) a){
//     resize(SIZE+1);
//     array[SIZE-1] = a;
//   }*/
//   /*void push_back(){
//     resize(SIZE+1);
//   }*/
//   /*void push_back(const type*arr,to_rvalue(uint) size){
//     resize(SIZE+size);
//     for(int i = 0; i<size;i++){
//       array[SIZE+i] = arr[i];
//     }
//   }*/
//   /*void push_back(to_rvalue(initializer_list<type>)list){
//     resize(SIZE+list.size());
//     for(int i = 0; i<list.size();i++){
//       array[SIZE+i] = list.begin()[i];
//     }
//   }
//   void push_back(to_rvalue(RG_Pointer<type>)arr){
//     resize(SIZE+arr.size());
//     for(int i = 0; i<arr.size();i++){
//       array[SIZE+i] = arr[i];
//     }
//   }*/
//   RG_Pointer<type>operator*(to_rvalue(RG_Matrix<type>) mat)const{
//     if(SIZE!=mat.size(1))RG_Debug::addl(RG_LOG_CRITICAL,"Array multiplication error (array by matrix) array size does not match matrix width, array size '"+to_string(SIZE)+"', matrix height '"+to_string(mat.size(1))+"'");
//     uint nsizex = mat.size(0);
//     RG_Pointer<type>out(mat.size(0));


//     for(uint x = 0; x<nsizex; x++){
//     	for(uint k = 0; k<SIZE; k++){
//         out[x]+=array[k] * mat.get(x,k);
//     	}
//     }
//     return out;
//   }
//   RG_Pointer<type>operator*(to_rvalue(type) in)const{
//     RG_Pointer<type> out(SIZE);
//     for(int i = 0;i<SIZE;i++){
//       out[i] = array[i]*in;
//     }
//     return out;
//   }
//   RG_Pointer<type>operator-(to_rvalue(RG_Pointer<type>)in)const{
//     if(SIZE!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array subtraction error arrays size does not match, first array size '"+to_string(SIZE)+"', second array size '"+to_string(in.size())+"'");
//     RG_Pointer<type>out(SIZE);
//     for(int i =0; i<SIZE;i++){
//       out[i] = array[i]-in[i];
//     }
//     return out;
//   }
//   RG_Pointer<type>operator+(to_rvalue(RG_Pointer<type>)in)const{
//     if(SIZE!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array addition error arrays size does not match, first array size '"+to_string(SIZE)+"', second array size '"+to_string(in.size())+"'");
//     RG_Pointer<type>out(SIZE);
//     for(int i =0; i<SIZE;i++){
//       out[i] = array[i]+in[i];
//     }
//     return out;
//   }

//   /*RG_Pointer<type>operator%(to_rvalue(RG_Pointer<type>)in)const{
//     if(SIZE!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array multiplication error arrays size does not match, first array size '"+to_string(SIZE)+"', second array size '"+to_string(in.size())+"'");

//     RG_Pointer<type>out(SIZE);
//     for(int i =0; i<SIZE;i++){
//       out[i] = array[i]*in[i];
//     }

//     return out;
//   }*/
//   /*RG_Pointer<type>operator*(to_rvalue(RG_Pointer<type>)in)const{
//     if(SIZE!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array multiplication error arrays size does not match, first array size '"+to_string(SIZE)+"', second array size '"+to_string(in.size())+"'");
//     RG_Pointer<type>out(SIZE);
//     for(int i =0; i<SIZE;i++){
//       out = array[i]*in[i];
//     }
//     return out;
//   }*/

//   /*const RG_Matrix<type> transpose()const{
//     RG_Matrix<type> transpos(1,SIZE,array);
//     return transpos;
//   }*/

//   ///////
//   //empty
//   bool empty()const{
//     return !INIT;
//   }
//   //////
//   //size
//   uint size()const{
//     return SIZE;
//   }
//   ///////
//   //clear
//   void clear(){
//     /*if(SIZE!=0||INIT!=false){
//       s_free(array);
//       SIZE = 0;
//       INIT = 0;
//     }*/
//     if(SIZE>0){
//       /*if(!stbi)
//         s_free(array);
//       else
//         free(array);*/
//       if(!noclear)
//         RG::Lock::s_delete(array);
//       SIZE = 0;
//     }
//   }
//   ~RG_Pointer(){
//     clear();
//   }

//   ////////////
//   //print
//   void print()const{
//     for(int i = 0; i<SIZE;i++){
//       rg_cout<<array[i]<<" ";
//     }
//     rg_cout<<endl;
//   }
//   //////////
//   //delete
//   /*void erase(to_rvalue(uint) id){
//     for(int i = id+1;i<SIZE;i++){
//       array[i-1] = array[i];
//     }
//     resize(SIZE-1);
//   }*/
//   //std stl style
//   type*begin()const{
//     return &array[0];
//   }
//   type*end()const{
//     return &array[SIZE];
//   }
//   type*back()const{
//     return &array[SIZE-1];
//   }

//   type sum()const{
//     type a = 0;
//     for(int i = 0; i<SIZE;i++){
//       a+=array[i];
//     }
//     return a;
//   }

//   void fill_range_random(to_rvalue(type) a, to_rvalue(type) b){
//     for(int i = 0; i<SIZE;i++){
//       array[i] = (rand()/(RAND_MAX/(b-a)))+a;
//     }
//   }


//   /*void set_stbi(){
//     stbi = true;
//   }
//   void unset_stbi(){
//     stbi = false;
//   }*/
// };

// ostream& operator<<(ostream &os, RG_Pointer<char>& arr){
//     for(int i = 0; i < arr.size();i++){
//       os<<arr[i];
//     }
//     return os;
// }
// ostream& operator<<(ostream &os, RG_Pointer<wchar_t>& arr){
//     for(int i = 0; i < arr.size();i++){
//       os<<arr[i];
//     }
//     return os;
// }

// template<class C>
// ostream& operator<<(ostream &os, RG_Pointer<C>& arr){
//     for(int i = 0; i < arr.size();i++){
//       os<<arr[i];
//       if(i!=arr.size()-1)os<<", ";
//     }
//     return os;
// }


// wostream& operator<<(wostream &os, RG_Pointer<char>& arr){
//     for(int i = 0; i < arr.size();i++){
//       os<<arr[i];
//     }
//     return os;
// }
// wostream& operator<<(wostream &os, RG_Pointer<wchar_t>& arr){
//     for(int i = 0; i < arr.size();i++){
//       os<<arr[i];
//     }
//     return os;
// }

// template<class C>
// wostream& operator<<(wostream &os, RG_Pointer<C>& arr){
//     for(int i = 0; i < arr.size();i++){
//       os<<arr[i];
//       if(i!=arr.size()-1)os<<", ";
//     }
//     return os;
// }
