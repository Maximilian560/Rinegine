#pragma once

namespace RG_Lock{

  template<class type>
  type* s_new(int size){
    char* newmem = (char*)malloc(size*sizeof(type)+sizeof(uint)+sizeof(char)*2);
    newmem[0] = 'R';
    newmem[1] = 'G';
    uint* ssize = (uint*)(newmem+2);
    ssize[0] = size;
    type* out = ((type*)(ssize+1));
    for(int i = 0; i<size;i++){
      out[i] = type();
    }
    return out;
  }

  //template<class type>
  inline bool s_rawmemtest(char*in){
    if(in[0]=='R' && in[1]=='G')return true;
    return false;
  }

  template<class type>
  inline bool s_memtest(type*in){
    char* rawmem = (char*)((uint*)(p)-1)-2;
    if(rawmem[0]=='R' && rawmem[1]=='G')return true;
    return false;
  }
  template<class type>
  void s_delete(type* &p){
    char* rawmem = (char*)((uint*)(p)-1)-2;
    if(s_rawmemtest(rawmem)){
      free(rawmem);
      p = nullptr;
    }else{
      RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Memory Deallocation is failed, array is not RG type");
    }
    

  }


  template<class type>
  int s_get_size(type* in){
    return(((int*)(in))-1)[0];
  }
  template<class type>
  char s_print(type* in){
    int temp_size = new_get_size(in);
    for(int i = 0; i<temp_size;i++){
      rg_cout<<in[i];
      if(i==temp_size-1)rg_cout<<endl;else rg_cout<<','<<' ';
    }
    return '\0';
  }







  template<class type>
  int s_erase(type* &p, int arrsize, int pos, int size = 1){// p - начала массива, arrsize - размер массива, pos - начала удаления, size - количество элементов для удаления
      if(size == 0)return arrsize;
      int eracesize = size;
      int eracepos = pos;
      if(pos+size>arrsize){RG_Debug::addl(RG_LOG_LOCK_ERROR,"s_erase, size+pos is greater than the size of the passed array, erase pos = '"+to_string(pos)+"', erase size = '"+to_string(size)+"', array size = '" + to_string(arrsize)+"'");}
      if(pos>arrsize){RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"s_erase, pos is greater than the size of the passed array, erase pos = '"+to_string(pos)+"',array size = '" + to_string(arrsize)+"'");}
      if(arrsize<=0)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"s_erase, array size less than or equal to 0, array size = " + to_string(arrsize)+"'");
      if(pos<0)eracepos = arrsize+pos;
      if(size<0){
          if(size+pos<=0)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"I'm tired of writing errors, but here it's supposedly position + cleanup size is less than zero, understand it as you want. And i want to sleep.\n");
      }
      if(pos+size>arrsize)eracesize = arrsize-pos;
      if(arrsize-size<=0){RG_Debug::addl(RG_LOG_LOCK_DEBUG,"s_erase, array size less than or equal to 0");s_delete(p);return 0;}
      //type* a = s_new<type>(arrsize-size);//new type[arrsize-size];
      type* a = new type[arrsize-size];
      for(int i = 0; i<arrsize-eracesize;i++){
          if(i>=pos){
              a[i] = p[i+eracesize];
          }else{
              a[i]=p[i];
          }
      }
      //s_delete(p);

      delete[] p;
      p = a;
      return arrsize-eracesize;
  }
  template<class type>
  void s_resize(type* &p, int &size, to_rvalue(int) newsize){
    if(newsize>0){
      if(p!=nullptr){
        if(size!=newsize){
          type* out = new type[newsize];
          for(int i = 0; i<rg_min(size,newsize);i++){
            out[i] = p[i];
          }
          size = newsize;
          p = out;
          return;
        }else return;
      }else {
        p = new type[newsize];
        size = newsize;
        return;
      }
    }else {delete[] p;p = nullptr;size = 0;return;};

  }




  template <class type>
  class raw_array{
    type* _array = nullptr;
    int _size = 0;
    bool _is_leaky = false;
    int find_continue = 0;
  public:
    type* array()const{return _array;}
    int size()const{return _size;}
    
    ///
    type& get(to_rvalue(int) i)const{
      if(i>=_size)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Index out of range, index = '"+to_string(i)+"', _array _size = '"+to_string(_size)+"'");
      if(i<0){
        if(_size+i<=0)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Index out of range, index = '"+to_string(i)+"', index + _size = '"+to_string(i+_size)+"', _array _size = '"+to_string(_size)+"'");
        return _array[_size+i];
      }
      return _array[i];
    }
    type& operator[](int i)const{
      return get(i);
    }
    /*
    type& find_equale_start(to_rvalue(type) in){
      find_continue = 0;
      for(; find_continue<_size;find_continue++){
        if(in==_array[i])return _array[i];
      }
    }
    type& find_equale(to_rvalue(type) in){
      for(; find_continue<_size;find_continue++){
        if(in==_array[i])return _array[i];
      }
    }*/
    int find_start(to_rvalue(type) in){
      find_continue = 0;
      for(; find_continue<_size;find_continue++){
        if(in==_array[i])return i;
      }
      find_continue = 0;
      return _size;
    }
    int find_next(to_rvalue(type) in){
      for(; find_continue<_size;find_continue++){
        if(in==_array[i])return i;
      }
      find_continue = 0;
      return _size;
    }
    int find(to_rvalue(type) in)const{
      for(int i = 0; i<_size;i++){
        if(in==_array[i])return i;
      }
      return _size;
    }
    ///
    void resize(int newsize){
      s_resize<type>(_array,_size,newsize);
    }
    void push_back(){
      resize(_size+1);
    }
    void push_back(type a){
      resize(_size+1);
      _array[_size-1] = a;
    }
    ///
    void pop(){
      resize(_size-1);
    }
    void erace(int i,int delsize = 1){
      s_erase(_array,_size,i,delsize);
    }
    void clear(){
      delete[] _array;
      int _size = 0;
    }
    void copy (to_rvalue(raw_array<type>) in){
      resize(in._size);
      for(int i = 0; i<_size;i++){
        
      }
    }
    void operator=(to_rvalue(raw_array<type>) in){
      _array = in._array;
      _size = in._size;
      _is_leaky = true;
    }
    void leaky_clear(){
      _array = nullptr;
      _size = 0;
      _is_leaky = false;
    }
    ~raw_array(){
      if(_is_leaky)
        leaky_clear();
      else 
        clear();
    }
  };



}


namespace RG{
  

  template <class type>
  struct Pointers{
    static RG_Lock::raw_array<RG_Lock::raw_array<type>>ptrs;

    static type* add(int size){
      ptrs.push_back();
      ptrs[size-1].resize(size);
      return ptrs[size-1].array();
    }
    static void pop(){
      ptrs.pop();
    }
    static void erace(int a,int delsize = 1){
      ptrs.erace(a,delsize);
    }
    static void find_delete(type* &p){
      ptrs.find(p);
    }

  }

  template <class type>
  inline void s_delete(type* &p){
    //delete[] p;
    Pointers<type>::find_delete(p);
    if(p!=nullptr)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Memory Deallocation is failed, array is not found");
    /*int fordel;
    if(fordel = ptrs.find(p),fordel==ptrs.size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Memory Deallocation is failed, array is not found");
    ptrs.erace(ptrs.find(p));
    p = nullptr;*/
  }
  template <class type>
  inline void s_delete_one(type* &p){
    RG_Debug::addl(RG_LOG_LOCK_WARNING,"'s_delete_one': s_delete_one/s_new_one is not safe, use s_delete/s_new instead");
    delete p;
    p = nullptr;
  }
  template <class type>
  inline type* s_new_one(){
    RG_Debug::addl(RG_LOG_LOCK_WARNING,"'s_new_one': s_delete_one/s_new_one is not safe, use s_delete/s_new instead");
    return new type;
  }

  template <class type>
  inline type* s_new(int size){
    return Pointers<type>::add(size);
    
  }
  template <class type>
  inline type* s_new(){
    return new type[1];
  }
}
