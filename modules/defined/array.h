#pragma once




template<typename type>
class RG_Array
{
  type*array = nullptr;
  uint SIZE = 0;
  bool INIT = false;
public:
  //init
  void init(uint size){
    resize(size);
  }
  void init(uint size, type*arr){
    fill(size,arr);
  }
  void init(uint size, type arr){
    fillfull(size,arr);
  }
 
  RG_Array(){}
  RG_Array(uint size){init(size);}
  RG_Array(uint size,type*arr){init(size,arr);}
  RG_Array(uint size,type arr){fillfull(size,arr);}
  //RG_Array(type*arr, uint size){init(size,arr);}
  //RG_Array(type arr,uint size){fillfull(size,arr);}
  /*template<class type2>
  RG_Array(type2*arr){init(sizeof(arr),arr);}*/

  ////////
  //resize
  void resize(uint size){
    if(size>0){
     if(SIZE==0){
          array = s_calloc<type>(size);
          if(array == nullptr)throw RG_ERROR_OUT_OF_MEMORY;
      }
      else{
        if(SIZE!= size){
          s_replace_raw<type>(array,SIZE,size); 
          if(array == nullptr)throw RG_ERROR_OUT_OF_MEMORY;
        }
      }
      INIT = true;
      SIZE = size;
    }else{

      if(!INIT) return;
      clear();
    }
  }
  //////
  //fillа
  void fill(uint size, type*arr){
    //clear();
    resize(size);
    for(int i = 0; i<size;i++){
      array[i] = arr[i];
    }
  }
  void fillfull(uint size, type ar){
    clear();
    resize(size);
    for(int i = 0; i<size;i++){
      array[i] = ar;
    }
  }
  ////////
  //indexs
  type&operator[](uint i){
    if(i>=0){
      if(i<=SIZE){
        return array[i];
      }
      else {
        //cout<<"ERROR! Size array loss then 'i' in operator[](uint i)\n"; 
        //cout<<"Size = "<<SIZE<<" | i = "<<i<<endl; 
        //RG_DEBUG_TEXT("ERROR! Size array loss then 'i' in operator[](uint i)");
        //RG_DEBUG_TEXT("Size = "<<SIZE<<" | i = "<<i);
        throw RG_ERROR_RGARRAY_SIZE1;}
    }
    else{
      if(SIZE+i<SIZE){
        return array[SIZE+i];
      }
      else{
        //cout<<"ERROR! Size array loss then 'size + i' in operator[](uint i)\n";
        //cout<<"Size = "<<SIZE<<" i = "<<i<<endl;
        //RG_DEBUG_TEXT("ERROR! Size array loss then 'size + i' in operator[](uint i)");
        //RG_DEBUG_TEXT("Size = "<<SIZE<<" i = "<<i);
        throw RG_ERROR_RGARRAY_SIZE2;
      }
    }
    //return array[i];
  }
  void operator=(RG_Array<type>ar){
    //resize(ar.size());
    fill(ar.size(),ar.get_arr());
  }
  type*get_arr(){
    return array;
  }
  ////////
  //append
  void append(type a){
    resize(SIZE+1);
    array[SIZE-1] = a;
  }
  void append(){
    resize(SIZE+1);
  }
  ///////
  //empty
  bool empty(){
    return !INIT;
  }
  //////
  //size
  uint size(){
    return SIZE;
  }
  ///////
  //clear
  void clear(){
    /*if(SIZE!=0||INIT!=false){
      s_free(array);
      SIZE = 0;
      INIT = 0;
    }*/
    if(SIZE>0){
      s_free(array);
      SIZE = 0;
      INIT = 0;
    }
  }
  ~RG_Array(){
    clear();
  }

  ////////////
  //print
  void print(){
    for(int i = 0; i<SIZE;i++){
      cout<<array[i]<<" ";
    }
    cout<<endl;
  }
  //////////
  //delete
  void erase(uint id){
    for(int i = id+1;i<SIZE;i++){
      array[i-1] = array[i];
    }
    resize(SIZE-1);
  }
  //std stl style
  type*begin(){
    return &array[0];
  }
  type*end(){
    return &array[SIZE];
  }
};

template<class C>
ostream& operator<<(ostream &os, RG_Array<C>& arr) {
    string temp;
    for(int i = 0; i < arr.size();i++){
      temp+=arr[i];
    }
    return os<<temp;
}