#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/types/pointers"

template <class type>
class RG_Array;
template <class type>
struct RG_LinkType{
  RG_Array<type>* link;
  int arrayid = 0;
};
template <class type>
class RG_Pointers{
  inline static RG_RawArray<RG_RawArray<type>> pointers;
  inline static RG_RawArray<RG_LinkType<type>> links;
  inline static int _size = 0;
public:

  static int add(RG_Array<type>* link, int a){
    RG_LOG_LOCK_INFO("RG_Pointer type of '"+string(abi::__cxa_demangle(typeid(type).name(), NULL, NULL, NULL))+"' has created, size = '"+to_string(a)+"'");
    RG_LOG_LOCK_INFO("RG_Pointer pointers pointer = '"+to_string((long long)pointers.get()));
    pointers.resize(_size+1);
    pointers[_size].resize(a);
    RG_LOG_LOCK_INFO("RG_Pointer pointers pointers pointer = '"+to_string((long long)pointers[_size].get()));
    pointers[_size]._noclear = true;
    RG_LOG_LOCK_INFO("RG_Pointer new pointers pointer = '"+to_string((long long)pointers.get()));

    RG_Pointers<type>::link(link, _size);
    //rg_cout<<"POINTERS ADD, ID "<<_size<<", _size "<<a<<" SIZEOF "<<sizeof(type)<<endl;
    //links.push_back({link,_size});//_size - текущий размер массива, после добовления элемента новый элемент будет находится на месте текущего _size из-за этого _size считается как arrayid
    //rg_cout<<"ADD\n id "<<links[links.size()-1]._arrayid<<endl;
    //rg_cout<<"link "<<links[links.size()-1].link<<endl;
    //rg_cout<<"real link "<<link<<endl;
    return _size++;
  }
  static type* get(int a){
    return pointers[a].get();
  }
  static void update(int id){
    for(int i = 0; i<links.size();i++){
      if(links[i].arrayid == id){links[i].link->_array = pointers[id].get();links[i].link->_size = pointers[id].size();};
    }
  }
  static void resize(int id, int nsize){
    pointers[id].resize(nsize);
    update(id);
  }
  static int size(){
    return _size;
  }
  static int size(int in){
    return pointers[in].size();
  }
  static void pop(){
    pointers[--_size].clear();
  }
  static void clear(){
    for(int i = 0; i<_size;i++){
      pointers[i].clear();
      links[i].clear();
    }
    _size = 0;
  }
  static void unlink(RG_Array<type>* link){
    for(int i = 0; i<links.size();i++){
      if(links[i].link == link){check_link_and_free(links[i].arrayid);links.erase(i);}
    }
  }
  static void link(RG_Array<type>* link, int id){
    RG_LOG_LOCK_INFO("RG_Pointer link old pointer = '"+to_string((long long)links.get())+"'");
    RG_LOG_LOCK_INFO("This old pointers: ");
    for(int i = 0; i<_size;i++){
      RG_LOG_LOCK_INFO(to_string((long long)links[i].link)+" "+to_string(links[i].arrayid));
    }
    links.push_back({link,id});
    RG_LOG_LOCK_INFO("This new pointers: ");
    for(int i = 0; i<_size;i++){
      RG_LOG_LOCK_INFO(to_string((long long)links[i].link)+" "+to_string(links[i].arrayid));
    }
    RG_LOG_LOCK_INFO("RG_Pointer link new pointer = '"+to_string((long long)links.get())+"'");
    link->_array = pointers[id].get();
    RG_LOG_LOCK_INFO("RG_Pointer link link pointer = '"+to_string((long long)link)+"'");
    link->_size = pointers[id].size();
    link->_arrayid = id;
  }
  static void check_link_and_free(int id){
    char temp = 0;
    for(int i = 0; i<links.size();i++){
      if(links[i].arrayid == id){if(++temp==2)break;}//links[i].link->_array = nullptr};
    }
    if(temp!=2){
      pointers[id]._noclear = false;
      RG_LOG_LOCK_INFO("Pointers pointer is '"+to_string((long long)pointers.get_arr())+"'");
      pointers.erase(id);
      _size--;
    }
    //rg_cout<<"POINTERS ERASE, ID "<<id<< ", SIZEOF "<<sizeof(type)<<endl;
  }
  //static void erace(int a, int b){}TODO 
  ~RG_Pointers(){
    clear();
  }
  
};

