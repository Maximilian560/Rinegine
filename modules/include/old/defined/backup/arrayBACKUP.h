#pragma once

template <class type>
class RG_Matrix;
template<class type>
class RG_Array {
  uint* __size = nullptr;
  uint _size = 0;
  type* _array = nullptr;
  type* _arrayend = nullptr;
public:
  RG_Array() {}
  RG_Array(to_rvalue(RG_Array<type>) in) {
    init(in);
  }
  RG_Array(to_rvalue(uint) size, to_rvalue(RG_Array<type>) in) {
    init(size, in);
  }
  RG_Array(to_rvalue(int) size, to_rvalue(type) ar) {
    init(size, ar);
  }
  RG_Array(to_rvalue(int) size, to_rvalue(type*) ar) {
    init(size, ar);
  }
  RG_Array(to_rvalue(uint) size, to_rvalue(type*) ar) {
    init(size, ar);
  }
  
  RG_Array(to_rvalue(int) size) {
    init(size);
  }
  RG_Array(to_rvalue(initializer_list<type>) list) {
    init(list);
  }
  RG_Array(to_rrvalue(type*)ar) {
    init(ar);
  }
  
  
  
  
  
  
  // RG_Array(to_rvalue(uint) size, to_rvalue(type*) ar) {
  //   init(size, ar);
  // }

  ///////////INIT
  void init(to_rvalue(int) size) {
    resize(size);
  }
  void init(to_rvalue(int) size, to_rvalue(type) ar) {
    resize(size);
    //int fillsize = rg_min(size, _size);
    for (int i = 0; i < size;i++) {
      _array[i] = ar;
    }
  }
  void init(to_rvalue(type*)ar) {
    if(ar == nullptr){clear();return;}
    if(!RG::s_memtest(ar))RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"RG_Array error: init(type*arr), type is not RG array\n");
    resize(RG::s_get_size(ar));
    for (int i = 0; i < _size; i++) {
      _array[i] = ar[i];
    }
  }
  void init(to_rvalue(uint)size,to_rvalue(type*)ar) {
    resize(size);
    for (int i = 0; i < _size; i++) {
      _array[i] = ar[i];
    }
  }
  void init(to_rvalue(initializer_list<type>) list) {
    resize(list.size());
    for (int i = 0; i < list.size();i++) {
      _array[i] = list.begin()[i];
    }
  }
  void init(to_rvalue(RG_Array<type>) in) {
    resize(in.size());
    for(int i = 0; i<in.size();i++){
      _array[i] = in[i];
    }
  }
  void init(to_rvalue(uint) size, to_rvalue(RG_Array<type>) in) {
    resize(size);
    for(int i = 0; i<in.size();i++){
      _array[i] = in[i];
    }
  }

  ///////////RESIZE/FILL
  void resize(to_rvalue(int) size,bool replace = true) {
    if(size<=0){clear();return;}
    if(size!=_size){
      RG::s_resize(_array, size);
      _arrayend = _array + size;
      __size = (((uint*)(_array)) - 1);
      _size = *__size;
    }
  }
  ////
  

  //void fill([](int)(*in)){
  //template<class gen>
  void fill(type(*in)()){
    type* temp = _array;
    for(;temp!=_arrayend;++temp){
      *temp = in();
    }
  }


  /*void fill(int(*in)()){
    type* temp = _array;
    for(;temp!=_arrayend;++temp){
      *temp = in();
    }
  }*/

  void fill(type in){
    type* temp = _array;
    for(;temp!=_arrayend;++temp){
      *temp = in;
    }
  }
  void push_back(){
    resize(_size+1);
  }
  void push_back(to_rvalue(type) in){
    push_back();
    _array[_size-1] = in;
  }
  void push_back(to_rvalue(RG_Array<type>) in){
    uint old_size = _size;
    resize(in.size()+_size);
    for(int i = 0; i<in.size();i++){
      _array[i+old_size] = in[i];
    }
  }
  void push_back(to_rvalue(initializer_list<type>) list){
    uint old_size = _size;
    resize(list.size()+_size);
    for(int i = 0; i<list.size();i++){
      _array[i+old_size] = list.begin()[i];
    }
  }
  void push_back(to_rvalue(type*) in){
    if(!RG::s_memtest(in))RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"RG_Array error: push_back(type*in), 'in' is not RG array\n");
    uint old_size = _size;
    uint in_size = RG::s_get_size(in);
    resize(in_size+_size);
    for(int i = 0; i<in_size;i++){
      _array[i+old_size] = in[i];
    }
  }
  //////////ORETATORS
  
  type& operator[](to_rvalue(int) index) const{
    if(_size==0)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array index out of range, index '"+to_string(index)+"', array size '"+to_string(_size)+"'");

    int true_index = index;
    if(index<0){
      true_index = _size+index;
    }
    if(true_index>=_size)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array index out of range, index '"+to_string(index)+"', array size '"+to_string(_size)+"'");
    return _array[true_index];
  }
  type& operator[](to_rvalue(uint) index) const{

    uint true_index = index;
    if(index<0){
      true_index = _size+index;
    }
    if(true_index>=_size)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array index out of range, index '"+to_string(index)+"', array size '"+to_string(_size)+"'");
    return _array[true_index];
  }

  RG_Array<type>operator*(to_rvalue(RG_Matrix<type>) mat)const{
    if(_size!=mat.size(1))RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array multiplication error (_array by matrix) _array size does not match matrix width, _array size '"+to_string(_size)+"', matrix height '"+to_string(mat.size(1))+"'");
    uint nsizex = mat.size(0);
    RG_Array<type>out(mat.size(0));
    

    for(uint x = 0; x<nsizex; x++){
    	for(uint k = 0; k<_size; k++){
        out[x]+=_array[k] * mat.get(x,k);
    	}
    }
    return out;
  }
  RG_Array<type>operator*(to_rvalue(type) in)const{
    RG_Array<type> out(_size);
    for(int i = 0;i<_size;i++){
      out[i] = _array[i]*in;
    }
    return out;
  }
  RG_Array<type>operator-(to_rvalue(RG_Array<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array subtraction error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    RG_Array<type>out(_size);
    for(int i =0; i<_size;i++){
      out[i] = _array[i]-in[i];
    }
    return out;
  }
  RG_Array<type>operator+(to_rvalue(RG_Array<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array addition error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    RG_Array<type>out(_size);
    for(int i =0; i<_size;i++){
      out[i] = _array[i]+in[i];
    }
    return out;
  }

  RG_Array<type>operator%(to_rvalue(RG_Array<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array multiplication error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    
    RG_Array<type>out(_size);
    for(int i =0; i<_size;i++){
      out[i] = _array[i]*in[i];
    }

    return out;
  }
  RG_Array<type>operator*(to_rvalue(RG_Array<type>)in)const{
    if(_size!=in.size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array multiplication error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    RG_Array<type>out(_size);
    for(int i =0; i<_size;i++){
      out = _array[i]*in[i];
    }
    return out;
  }

  template<class em>
  void operator=(to_rvalue(em)in){
   RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array operator= error, this type is not supported");
  }
  void operator=(to_rvalue(RG_Array<type>)in){
    init(in);
  }
  void operator=(to_rvalue(initializer_list<type>)list){
    init(list);
  }
  void operator=(const char* in){
    clear();
    for(int i = 0;in[i]!='\0';i++){
      _size++;
    }
    init(_size,in);
  }
  void copy(to_rvalue(RG_Array<type>)in){
    init(in);
  }
  void operator-=(to_rvalue(RG_Array<type>)in){
    if(_size!=in.size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array subtraction error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    for(int i =0; i<_size;i++){
      _array[i] -= in[i];
    }
  }
  void operator+=(to_rvalue(RG_Array<type>)in){
    if(_size!=in.size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array addition error arrays size does not match, first _array size '"+to_string(_size)+"', second _array size '"+to_string(in.size())+"'");
    for(int i =0; i<_size;i++){
      _array[i] += in[i];
    }
  }


 


  //////OTHER OPERATORS
  operator type*()const{
    return _array;
  }
  operator uint()const{
    return _size;
  }
  RG_Matrix<type> transpose()const{
    RG_Matrix<type> transpos(1,_size,_array);
    return transpos;
  }
  type* get() const{
    return _array;
  }
  type* get_array() const{
    return _array;
  }
  type* get_arr() const{
    return _array;
  }
  type& get(to_rvalue(int) index) const{

    int true_index = index;
    if(index<0){
      true_index = _size+index;
    }
    if(true_index>=_size)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array index out of range, index '"+to_string(index)+"', array size '"+to_string(_size)+"'");
    return _array[true_index];
  }
  type& get(to_rvalue(uint) index) const{

    uint true_index = index;
    if(index<0){
      true_index = _size+index;
    }
    if(true_index>=_size)RG_Debug::addl(RG_LOG_LOCK_CRITICAL,"Array index out of range, index '"+to_string(index)+"', array size '"+to_string(_size)+"'");
    return _array[true_index];
  }
  ////////SPECIAL
  type*begin()const{
    return _array;
  }
  type*end()const{
    return _arrayend;
  }

  type*back()const{
    return _arrayend-1;
  }
  //////////SIZE
  uint size() const{
    return _size;
  }
  ////////OTHER
  void print() {
    RG::s_print(_array);
  }
  type sum()const{
    type out = 0;
    for(type* temp = _array;temp!=_arrayend;++temp){
      out+=*temp;
    }
    return out;
  }
  void fill_range_random(to_rvalue(type) min, to_rvalue(type) max) {
    for(uint i = 0; i<_size;i++){
      _array[i] = (rand()/(RAND_MAX/(max-min)))+min;
    }
  }
  bool empty()const{
    return (_array==nullptr);
  }
  void movefill(to_rvalue(uint) size, type*arr){
    if(!RG::s_memtest(arr)){RG_Debug::addl(RG_LOG_LOCK_ERROR,"RG_Array movefill(uint size, type*arr) error, 'arr' is not RG type");init(size,arr);return;};
    clear();
    _size = size;
    _array = arr;
  }




  ////////CLEAR
  void clear() {
    if(_array == nullptr) return;
    if(_size == 0) return; 
    RG::s_delete(_array);
  }
  ~RG_Array() {
    clear();
  }
};
