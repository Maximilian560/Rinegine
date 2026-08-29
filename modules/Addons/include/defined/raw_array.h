#pragma once

/*struct rg_raw_array{
  void*arr;
  int size=0;
  void   
};*/
#define to_rvalue(type)const type&

template<typename type>
class RG_Matrix;
template<typename type>
class RG_Pointers;

template<typename type>
class RG_RawArray{
  friend class RG_Pointers<type>;
  type*_array = nullptr;
  uint _size = 0;
  bool _noclear = false;
public:
  //init
  void init(to_rvalue(uint) size){
    resize(size);
  }
  void init(to_rvalue(uint) size, const type*arr){
    fill(size,arr);
  }
  void init(to_rvalue(uint) size, to_rvalue(type) arr){
    fillfull(size,arr);
  }
  void init(to_rvalue(initializer_list<type>) list){
    fill(list);
  }
  void init(to_rvalue(RG_RawArray<type>)ar){fill(ar);}

  /*operator type*()const{
    return _array;
  }
  operator int()const{
    return _size;
  }
  operator bool()const{
    return INIT;
  }*/
  operator RG_Matrix<type>()const{
    return RG_Matrix<type>(size,1,_array);
  }
  //constructor
  RG_RawArray(){}
  RG_RawArray(uint size){init(size);}
  RG_RawArray(initializer_list<type> list){init(list);}
  RG_RawArray(uint size,type*arr){init(size,arr);}
  RG_RawArray(uint size,type arr){fillfull(size,arr);}
  //RG_RawArray(RG_RawArray<type>arr){fill(arr);}
  RG_RawArray(const RG_RawArray<type>&arr){fill(arr._size,arr._array);}
  RG_RawArray(const char* in){
    for(int i = 0;;i++){
      if(in[i]=='\0'){char_fill(i,in);break;};
    }
  }
  RG_RawArray(const wchar_t* in){
    for(int i = 0;;i++){
      if(in[i]=='\0'){wchar_fill(i,in);break;};
    }
  }
  void char_fill(to_rvalue(uint)size, const char*in){
    resize(size);
    for(int i = 0; i<size;i++){
      _array[i] = in[i];
    }
  }
  void wchar_fill(to_rvalue(uint)size, const wchar_t*in){
    resize(size);
    for(int i = 0; i<size;i++){
      _array[i] = in[i];
    }
  }
  //RG_RawArray(type*arr, uint size){init(size,arr);}
  //RG_RawArray(type arr,uint size){fillfull(size,arr);}
  /*template<class type2>
  RG_RawArray(type2*arr){init(sizeof(arr),arr);}*/

  ////////
  //resize
  void resize(to_rvalue(uint) size){
    RG_Debug::addl(RG_LOG_INFO,"Raw _array resize, old size = '"+to_string(_size)+"', new size = '"+to_string(size)+"', old _array = '"+to_string((long long)_array)+"'");
    RG_Debug::addl(RG_LOG_INFO,"Raw _array type of '"+string(abi::__cxa_demangle(typeid(type).name(), NULL, NULL, NULL))+"'");
    if(size>0){
     if(_size==0){
          //_array = RG::s_new<type>(size);
          //RG_Debug::addl(RG_LOG_INFO,"Raw _array resize "+to_string(size));
          _array = RG::s_new<type>(size);
          if(_array == nullptr)throw RG_ERROR_OUT_OF_MEMORY;
      }
      else{
        if(_size!= size){
          RG::s_resize<type>(_array,_size,size); 
          if(_array == nullptr)throw RG_ERROR_OUT_OF_MEMORY;
        }
      }
    RG_Debug::addl(RG_LOG_INFO,"Raw _array resize new _array = '"+to_string((long long)_array)+"'");
      //INIT = true;
      _size = size;
    }else{

      if(!_size) return;
      clear();
    }
  }
  //////
  //fillа
  void fill(to_rvalue(uint) size, const type*arr){
    //clear();
    resize(size);
    for(int i = 0; i<size;i++){
      _array[i] = arr[i];
    }
  }
  void fill(const type*arr,to_rvalue(uint) size){
    //clear();
    resize(size);
    for(int i = 0; i<size;i++){
      _array[i] = arr[i];
    }
  }

  void fill(to_rvalue(type) arr){
    for(int i = 0; i<_size;i++){
      _array[i] = arr;
    }
  }
  void fill(to_rvalue(initializer_list<type>) list){
    resize(list.size());
    for(int i = 0; i<_size;i++){
      _array[i] = list.begin()[i];
    }
  }
  void fill(to_rvalue(RG_RawArray<type>) list){
    clear();
    resize(list.size());
    for(int i = 0; i<_size;i++){
      _array[i] = list[i];
    }
  }
  void fillfull(to_rvalue(uint) size, to_rvalue(type) ar){
    clear();
    resize(size);
    for(int i = 0; i<size;i++){
      _array[i] = ar;
    }
  }
  void movefill(to_rvalue(uint) size, type*arr){
    _size = size;
    _array = arr;
  }

  /*void movefill(const RG_RawArray<type>&arr){
    //clear();
    _size = arr._size;
    //_array = arr._array;
    _array = RG::s_new<type>(_size);
    //print();
    //arr._noclear = true;
    //arr.clear();
  }*/
  ////////
  //indexs
  type&operator[](to_rvalue(int) i)const{
    if(_size==0)RG_Debug::addl(RG_LOG_CRITICAL,"Size _array = 0");
    if(i>=0){
      if(i<=_size){
        return _array[i];
      }
      else {
        RG_Debug::addl(RG_LOG_CRITICAL,"i > 0. Size _array loss then 'i' in operator[](uint i), i = '"+to_string(i)+"', size = '"+to_string(_size)+"'");
      }
    }
    else{
      if(int(_size)+i<_size){
        return _array[int(_size)+i];
      }
      else{
        RG_Debug::addl(RG_LOG_CRITICAL,"i < 0. i + _array size is greater than the _array size, _array size = '"+to_string(_size)+"', i = '"+to_string(i)+"', i + _array size'"+to_string(int(_size)+i)+"'");
      }
    }
    RG_Debug::addl(RG_LOG_CRITICAL,"Array unknow error");
    return _array[0];
  }
  /*void operator=(to_rvalue(RG_RawArray<type>)ar){
    //resize(ar.size());
    //wcout<<"WTF "<<ar.size()<<endl;
    if(_size!=0){
      if(_size!=ar._size)wcout<<L"ВНИМАНИЕ! РАЗМЕР МАССИВА БЫЛ ИЗМЕНЁН С "<<_size<<L" НА '"<<ar._size<<L"' !!!!\n";
    }
    fill(ar.size(),ar.get_arr());
  }
  void operator=(const char* in){
    clear();
    for(int i = 0;in[i]!='\0';i++){
      _size++;
    }
    fill(_size,in);
  }*/
  /*void operator=(to_rvalue(RG_RawArray<type>)in){
    clear();
    _size = in._size;
    _array = in._array;
    stbi = in.stbi;
    INIT = in.INIT;
    _noclear = in._noclear;
    RG_Debug::addl(RG_LOG_WARNING,"A copy of the _array has been created, which points to the same _array that is associated with the original, thus, when the original is deleted, crashes due to access to unallocated memory or garbage return are possible.");
  }*/
  /*void operator=(to_rvalue(type) ar){
    clear();
    resize(1);
    _array[0] = ar;
  }
  void operator=(to_rvalue(initializer_list<type>)list){
    fill(list);
  }*/
 void operator=(to_rvalue(RG_RawArray<type>)in){
   _array = in._array;
   _size = in._size;
 }
  void operator-=(to_rvalue(RG_RawArray<type>)in){
    if(_size!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array subtraction error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    for(int i =0; i<_size;i++){
      _array[i] -= in[i];
    }
  }
  void operator+=(to_rvalue(RG_RawArray<type>)in){
    if(_size!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array addition error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    for(int i =0; i<_size;i++){
      _array[i] += in[i];
    }
  }
 

  type*get_arr()const{
    return _array;
  }
  type*get()const{
    return _array;
  }
  ////////
  //push_back
  void push_back(to_rvalue(type) a){
    resize(_size+1);
    _array[_size-1] = a;
  }
  void push_back(){
    resize(_size+1);
  }
  void push_back(const type*arr,to_rvalue(uint) size){
    resize(_size+size);
    for(int i = 0; i<size;i++){
      _array[_size+i] = arr[i];
    }
  }
  void push_back(to_rvalue(initializer_list<type>)list){
    resize(_size+list.size());
    for(int i = 0; i<list.size();i++){
      _array[_size+i] = list.begin()[i];
    }
  }
  void push_back(to_rvalue(RG_RawArray<type>)arr){
    resize(_size+arr.size());
    for(int i = 0; i<arr.size();i++){
      _array[_size+i] = arr[i];
    }
  }
  RG_RawArray<type>operator*(to_rvalue(RG_Matrix<type>) mat)const{
    if(_size!=mat.size(1))RG_Debug::addl(RG_LOG_CRITICAL,"Array multiplication error (_array by matrix) _array size does not match matrix width, _array size '"+to_string(_size)+"', matrix height '"+to_string(mat.size(1))+"'");
    uint nsizex = mat.size(0);
    RG_RawArray<type>out(mat.size(0));
    

    for(uint x = 0; x<nsizex; x++){
    	for(uint k = 0; k<_size; k++){
        out[x]+=_array[k] * mat.get(x,k);
    	}
    }
    return out;
  }
  RG_RawArray<type>operator*(to_rvalue(type) in)const{
    RG_RawArray<type> out(_size);
    for(int i = 0;i<_size;i++){
      out[i] = _array[i]*in;
    }
    return out;
  }
  RG_RawArray<type>operator-(to_rvalue(RG_RawArray<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array subtraction error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    RG_RawArray<type>out(_size);
    for(int i =0; i<_size;i++){
      out[i] = _array[i]-in[i];
    }
    return out;
  }
  RG_RawArray<type>operator+(to_rvalue(RG_RawArray<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array addition error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    RG_RawArray<type>out(_size);
    for(int i =0; i<_size;i++){
      out[i] = _array[i]+in[i];
    }
    return out;
  }

  RG_RawArray<type>operator%(to_rvalue(RG_RawArray<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array multiplication error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    
    RG_RawArray<type>out(_size);
    for(int i =0; i<_size;i++){
      out[i] = _array[i]*in[i];
    }

    return out;
  }
  RG_RawArray<type>operator*(to_rvalue(RG_RawArray<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_CRITICAL,"Array multiplication error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    RG_RawArray<type>out(_size);
    for(int i =0; i<_size;i++){
      out = _array[i]*in[i];
    }
    return out;
  }

  const RG_Matrix<type> transpose()const{
    RG_Matrix<type> transpos(1,_size,_array);
    return transpos;
  }

  ///////
  //empty
  bool empty()const{
    return !_size;
  }
  //////
  //size
  uint size()const{
    return _size;
  }
  ///////
  //clear
  void clear(){
    /*if(_size!=0||INIT!=false){
      s_free(_array);
      _size = 0;
      INIT = 0;
    }*/
      RG_Debug::addl(RG_LOG_INFO,"Raw_array should be delete: '"+to_string((long long)_array)+"' _size '"+to_string(_size)+"'");
    if(_size>0&&_array!=nullptr&&!_noclear){
      //rg_cout<<"RG_RAW_ARRAY CLEAR, _size "<<_size<<", SIZEOF "<<sizeof(type)<<endl;
      /*if(!stbi)
        s_free(_array);
      else
        free(_array);*/
        //RG_Debug::addl(RG_LOG_INFO,"Raw _array delete "+to_string((long long)_array));
      //rg_cout<<"delete "<<_array<<endl;
      RG_Debug::addl(RG_LOG_INFO,"RAW ARRAY CLEAR _array '"+to_string((long long)_array)+"' _size '"+to_string(_size)+"'");
      RG::s_delete(_array);
        

      _size = 0;
    }
  }
  /*void * operator new[] (size_t){
      RG_Debug::addl(RG_LOG_INFO,"RAW ARRAY NEW _array '"+to_string((long long)_array)+"' _size '"+to_string(_size)+"'");
      
      return 0;
   }*/
   /*void   operator delete[] (void*){
      RG_Debug::addl(RG_LOG_INFO,"RAW ARRAY DELETE _array '"+to_string((long long)_array)+"' _size '"+to_string(_size)+"'");
   }*/
  ~RG_RawArray(){
    clear();
  }

  ////////////
  //print
  void print()const{
    for(int i = 0; i<_size;i++){
      rg_cout<<_array[i]<<" ";
    }
    rg_cout<<endl;
  }
  //////////
  //delete
  void erase(to_rvalue(uint) id){
    _size = RG::s_erase(_array,_size,id,1);
  }
  void erase(to_rvalue(uint) id,to_rvalue(uint) count){
    _size = RG::s_erase(_array,_size,id,count);
  }
  //std stl style
  type*begin()const{
    return &_array[0];
  }
  type*end()const{
    return &_array[_size];
  }
  type*back()const{
    return &_array[_size-1];
  }

  type sum()const{
    type a = 0;
    for(int i = 0; i<_size;i++){
      a+=_array[i];
    }
    return a;
  }

  void fill_range_random(to_rvalue(type) a, to_rvalue(type) b){
    for(int i = 0; i<_size;i++){
      _array[i] = (rand()/(RAND_MAX/(b-a)))+a;
    }
  }


  /*void set_stbi(){
    stbi = true;
  }
  void unset_stbi(){
    stbi = false;
  }*/
};

ostream& operator<<(ostream &os, RG_RawArray<char>& arr){
    for(int i = 0; i < arr.size();i++){
      os<<arr[i];
    }
    return os;
}
ostream& operator<<(ostream &os, RG_RawArray<wchar_t>& arr){
    for(int i = 0; i < arr.size();i++){
      os<<arr[i];
    }
    return os;
}

template<class C>
ostream& operator<<(ostream &os, RG_RawArray<C>& arr){
    for(int i = 0; i < arr.size();i++){
      os<<arr[i];
      if(i!=arr.size()-1)os<<", ";
    }
    return os;
}


wostream& operator<<(wostream &os, RG_RawArray<char>& arr){
    for(int i = 0; i < arr.size();i++){
      os<<arr[i];
    }
    return os;
}
wostream& operator<<(wostream &os, RG_RawArray<wchar_t>& arr){
    for(int i = 0; i < arr.size();i++){
      os<<arr[i];
    }
    return os;
}

template<class C>
wostream& operator<<(wostream &os, RG_RawArray<C>& arr){
    for(int i = 0; i < arr.size();i++){
      os<<arr[i];
      if(i!=arr.size()-1)os<<", ";
    }
    return os;
}

