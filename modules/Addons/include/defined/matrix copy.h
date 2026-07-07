#pragma once
#ifdef RG_NO_USELESS_WARNING
bool RG_EXCEED_LIMIN_MATRIX = 1;
#else
bool RG_EXCEED_LIMIN_MATRIX = 0;
#endif



template<typename type>
class RG_Matrix {
  //RG_Matrix<type>*transonir = nullptr;
  //bool transpos = false;
  RG_Array<type> matrix;
  uint width = 0, height = 0;
public:
  //init
  void init(to_rvalue(RG_Array<type>) arr) {
    fill(arr);
  }
  /*void init(initializer_list<type> arr){
    //fill(arr.size(),1,arr.begin());
    fill(arr);
  }*/
  void init(to_rvalue(initializer_list<initializer_list<type>>) arr) { fill(arr); }

  void init(to_rvalue(uint) x, to_rvalue(uint) y) {
    resize(x, y);
  }
  void init(to_rvalue(uint) x, to_rvalue(uint) y, type* arr) {
    fill(x, y, arr);
  }
  void init(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(type) arr) {
    fill(x, y, arr);
  }
  /*void reInit(to_rvalue(uint) x, to_rvalue(uint) y,const type*mat){
    fill(x,y,mat);
  }*/
  void init(to_rvalue(RG_Matrix<type>)ar) { fill(ar); }

  RG_Matrix() {}
  RG_Matrix(to_rvalue(RG_Array<type>) ar) { init(ar); }
  RG_Matrix(to_rvalue(RG_Matrix<type>) ar) { init(ar); }
  RG_Matrix(to_rvalue(initializer_list<initializer_list<type>>) arr) { init(arr); }
  //RG_Matrix(initializer_list<type> arr){init(arr);}
  RG_Matrix(to_rvalue(uint) x, to_rvalue(uint) y) { init(x, y); }
  RG_Matrix(to_rvalue(uint) x, to_rvalue(uint) y, type* arr) { init(x, y, arr); }
  RG_Matrix(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(type)arr) { init(x, y, arr); }

  //void operator=(){}
  void operator=(to_rvalue(initializer_list<initializer_list<type>>) in) {
    init(in);
  }
  void operator=(to_rvalue(RG_Array<type>)in) {
    if (matrix.size() != 0) {
      if (matrix.size() != in.matrix.size())wcout << L"ВНИМАНИЕ! РАЗМЕР МАССИВА МАТРИЦЫ БЫЛ ИЗМЕНЁН МАССИВОМ С " << matrix.size() << L" НА '" << in.matrix.size() << L"' !!!!\n";
    }
    init(in);
  }
  void operator=(to_rvalue(RG_Matrix<type>)in) {
    if (matrix.size() != 0) {
      if (matrix.size() != in.matrix.size())wcout << L"ВНИМАНИЕ! РАЗМЕР МАТРИЦЫ И ЕГО МАССИВА БЫЛ ИЗМЕНЁН С " << matrix.size() << L" НА '" << in.matrix.size() << L"' !!!!\n" << L"ШИРИНА И ВЫСОТА С " << width << L"' '" << height << L"' НА '" << in.width << L"' '" << in.height << L"'!!!!\n";
    }
    init(in);
  }
  //void operator=(initializer_list<type> arr){init(arr);}
  //oid operator=(uint x,uint y){init(x,y);}
  //oid operator=(uint x,uint y,type*arr){init(x,y,arr);}
  //oid operator=(uint x,uint y,type arr){init(x,y,arr);}


  void resize(to_rvalue(uint) x) {
    if (x > 0) {
      matrix.resize(x);
      height = 1;
      width = x;
    } else {
      clear();
    }
  }

  void resize(to_rvalue(uint) x, to_rvalue(uint) y) {
    if (y * x > 0) {
      matrix.resize(y * x);
      height = y;
      width = x;
    } else {
      clear();
    }
  }
  void resize(to_rvalue(POINT2D<uint>)ns) {
    if (ns.y * ns.x > 0) {
      matrix.resize(ns.y * ns.x);
      height = ns.y;
      width = ns.x;
    } else {
      clear();
    }
  }
  //////
  //fill
  void fill(to_rvalue(RG_Matrix<type>)ar) {
    //cout<<ar.size(0)<<" "<<ar.size(1)<<" "<<ar.size(2)<<endl;
    //matrix.resize(ar.size(2));
    //transpos = ar.transpos;
    resize(ar.size());
    for (int y = 0; y < ar.size(1); y++) {
      for (int x = 0; x < ar.size(0); x++) {
        get(x, y) = ar[y][x];
      }
    }
  }
  void fill(to_rvalue(uint) x, to_rvalue(uint) y, type* mat) {
    resize(x, y);
    for (int yy = 0; yy < y; yy++) {
      for (int xx = 0; xx < x; xx++) {
        matrix[yy * x + xx] = mat[yy * x + xx];
      }
    }
  }
  void fill(to_rvalue(RG_Array<type>) arr) {

    resize(arr.size());
    matrix = arr;
  }
  void fill(to_rvalue(initializer_list<initializer_list<type>>) arr) {
    resize(arr.begin()->size(), arr.size());
    //wcout<<width<<"||"<<height<<endl;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        getyx(y, x) = arr.begin()[y].begin()[x];
      }
    }
  }
  template<class type2>
  void fill(to_rvalue(initializer_list<initializer_list<type2>>) arr) {
    resize(arr.begin()->size(), arr.size());
    //wcout<<width<<"||"<<height<<endl;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        getyx(y, x) = arr.begin()[y].begin()[x];
      }
    }
  }
  /*void fill(initializer_list<type>arr){
    resize(arr.size());
    for(int i = 0; i<arr.size();i++){
      matrix[i] = arr.begin()[i];
    }
  }*/
  void movefill(to_rvalue(uint) x, to_rvalue(uint) y, type* mat) {
    clear();
    matrix.movefill(x * y, mat);
    width = x;
    height = y;
  }

  /*void fillfull(to_rvalue(uint) size, to_rvalue(type) mat) {
    for(int i = 0;i<size;i++){
      matrix[i] = mat;
    }
  }*/
  void fill(to_rvalue(type) mat) {
    matrix.fill(mat);
  }
  void fill(to_rvalue(uint) y, to_rvalue(uint) x, to_rvalue(type) mat) {
    resize(x, y);
    matrix.fillfull(x * y, mat);
  }

  void randomBoolFill(to_rvalue(double) porog, to_rvalue(double) max = 1) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        matrix[y * width + x] = ((rand() / (RAND_MAX / max) > porog) ? 1 : 0);
      }
    }
  }
  void randomBoolAddFill(to_rvalue(double) porog, to_rvalue(double) max = 1) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        if (matrix[y * width + x] != 1)matrix[y * width + x] = ((rand() / (RAND_MAX / max) > porog) ? 1 : 0);
      }
    }
  }

  void randomAddFill(to_rvalue(double) porog, to_rvalue(double) max = 1) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        if (matrix[y * width + x] != 1)matrix[y * width + x] = rand() / (RAND_MAX / max);
      }
    }
  }

  void random_fill(to_rvalue(double) max = 1) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        matrix[y * width + x] = rand() / (RAND_MAX / max);
      }
    }
  }

  void noise_fill(to_rvalue(int) seed = 0) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        matrix[y * width + x] = rand();
      }
    }
  }
  void noise_dbool_fill(to_rvalue(int) seed = 0) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        matrix[y * width + x] = 1. * rand() / RAND_MAX;
      }
    }
  }

  void fill_range_random(to_rvalue(type) a, to_rvalue(type) b) {
    matrix.fill_range_random(a, b);
    /*for(int y = 0; y<height;y++){
      for(int x = 0; x<width;x++){
        matrix[y*width+x] = (rand()/(RAND_MAX/(b-a)))+a;
      }
    }*/
  }

  void scale(to_rvalue(uint) a) {
    //RG_Matrix<type>mat2;
    type mat2[width * a * height * a];
    //mat2.init(width*a,height*a);
    for (int y = 0; y < height * a; y++) {
      for (int x = 0; x < width * a; x++) {
        mat2[y * width * a + x] = matrix[(y / a) * width + (x / a)];
      }
    }
    fill(mat2.size(0), mat2.size(1), mat2.get_mat());
    mat2.clear();
  }
  void smoothScale(to_rvalue(int) a) {
    RG_Matrix<type>mat2;
    mat2.init(width * a, height * a);
    for (int y = 0; y < height * a; y += a) {
      for (int x = 0; x < width * a; x += a) {
        mat2.get(x, y) = matrix[(y / a) * width + (x / a)];
      }
    }

    for (int g = 1; g < a; g++) {
      for (int y = g; y < height * a; y += a) {
        for (int x = g; x < width * a; x += a) {
          //cout<<x<<" "<<y<<" "<<g<<endl;
          //cout<<((x-g)/a)<<" "<<((y-g)/a)<<" "<<g<<endl<<endl;

          if (((x - g) / a) - g >= 0) {
            mat2.get(x, y) += matrix[(((y - g) / a) + 0) * width + (((x - g) / a) - g)] / (g + 1.);
          }
          if (((y - g) / a) - g >= 0) {
            mat2.get(x, y) += matrix[(((y - g) / a) - g) * width + (((x - g) / a) - 0)] / (g + 1.);
          }
          if (((x - g) / a) + g < width / a) {
            mat2.get(x, y) += matrix[(((y - g) / a) + 0) * width + (((x - g) / a) + g)] / (g + 1.);
          }
          if (((y - g) / a) + g < height / a) {
            mat2.get(x, y) += matrix[(((y - g) / a) + g) * width + (((x - g) / a) - 0)] / (g + 1.);
          }
        }
      }
    }


    fill(mat2.size(0), mat2.size(1), mat2.get_mat());
    mat2.clear();

  }

  RG_Matrix<type> transpose() {
    //RG_Matrix<type>* tr = new RG_Matrix<type>();
    RG_Matrix<type> trans(height, width);
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        trans[j][i] = get(j, i);
      }
    }
    return trans;
  }
  ////////
  //indexs
  /*type&operator[](uint i){
    if(i>=0){
      if(i<matrix.size()){
        return matrix[i];
      }
      else {
        cout<<"ERROR! Size 2D matrix loss then 'i' in operator[](uint i)\n";
        cout<<"Size = "<<matrix.size()<<" | i = "<<i<<endl;
        exit(-1);}
    }
    else{
      if(matrix.size()+i<matrix.size()){
        return matrix[matrix.size()+i];
      }
      else{
        cout<<"ERROR! Size 2D matrix loss then 'size + i' in operator[](uint i)\n";
        cout<<"Size = "<<matrix.size()<<" i = "<<i<<endl;
        exit(-1);
      }
    }

  }*/
  type* operator[](const uint& i)const {
    if (i >= height)RG_Debug::addl(RG_LOG_CRITICAL, "matrix height is less than " + to_string(i + 1) + "(you set " + to_string(i) + ") and equal to " + to_string(height));
    if (!RG_EXCEED_LIMIN_MATRIX) { RG_Debug::addl(RG_LOG_WARNING, "When using [y][x] it is possible to exceed the limit, check that x is not larger than the width of the matrix. This warning will no longer appear"); RG_EXCEED_LIMIN_MATRIX = 1; }
    return &matrix[i * width];
  }


  type& get(const uint& x, const uint& y)const {
    if (y >= height) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix height less than or equal to 'y' in 'get(x,y)'\n\
      'Height' = '" + to_string(height) + "', 'y' = '" + to_string(y) + "'");
    }
    if (x >= width) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix width less than or equal to 'x' in 'get(x,y)'\n\
      'Width' = '" + to_string(width) + "', 'x' = '" + to_string(x) + "'");
    }
    return matrix[y * width + x];
  }

  type& getyx(to_rvalue(uint) y, to_rvalue(uint) x)const {
    if (y >= height) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix height less than or equal to 'y' in 'getyx(y,x)'\n\
      'Height' = '" + to_string(height) + "', 'y' = '" + to_string(y) + "'");
    }
    if (x >= width) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix width less than or equal to 'x' in 'getyx(y,x)'\n\
      'Width' = '" + to_string(width) + "', 'x' = '" + to_string(x) + "'");
    }
    return matrix[y * width + x];
  }
  type& get(to_rvalue(POINT2D<uint>)pos)const {
    if (pos.x >= width) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix width less than or equal to 'pos.x' in 'get(POINT2D<uint>pos)'\n\
      'Width' = '" + to_string(width) + "', 'pos.x' = '" + to_string(pos.x) + "'");
    }
    if (pos.y >= height) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix height less than or equal to 'pos.y' in 'get(POINT2D<uint>pos)'\n\
      'Height' = '" + to_string(height) + "', 'pos.y' = '" + to_string(pos.y) + "'");
    }

    return matrix[pos.y * width + pos.x];
  }
  type& get(to_rvalue(POINT2D<int>)pos)const {
    if (pos.x >= width) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix width less than or equal to 'pos.x' in 'get(POINT2D<uint>pos)'\n\
      'Width' = '" + to_string(width) + "', 'pos.x' = '" + to_string(pos.x) + "'");
    }
    if (pos.y >= height) {
      RG_Debug::addl(RG_LOG_CRITICAL, "Matrix height less than or equal to 'pos.y' in 'get(POINT2D<uint>pos)'\n\
      'Height' = '" + to_string(height) + "', 'pos.y' = '" + to_string(pos.y) + "'");
    }

    return matrix[pos.y * width + pos.x];
  }
  void print()const {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        rg_cout << getyx(i, j) << " ";
      }
      rg_cout << endl;
    }
    //matrix.print();
  }


  operator type* () {
    return matrix.get_arr();
  }
  type* get()const {
    return matrix.get_arr();
  }
  type* get_mat()const {
    return matrix.get_arr();
  }
  /*RG_Array<type>&get_arr()const{
    return matrix;
  }*/
  operator RG_Array<type>& ()const {
    return matrix;
  }
  ///////
  //empty
  bool empty()const {
    return matrix.empty();
  }
  operator bool() {
    return !matrix.empty();
  }
  //////
  //size
  uint size(to_rvalue(uint) i)const {
    switch (i) {
      case 0: return width;
      case 1: return height;
      default: return matrix.size();
    }

  }
  operator RG_Array<type>()const {
    return matrix;
  }

  operator uint()const {
    return matrix.size();
  }
  /*POINT2D<uint> size(){
    return {uint(width),uint(height)};
  }*/
  POINT2D<uint> size() const {
    return { width,height };
  }
  ///////
  //clear
  void clear() {
    //if(!matrix.empty()){
      //free(array);
    matrix.clear();
    width = 0;
    height = 0;
    //if(transonir!=nullptr)
    //  delete transonir;
 // }
  }
  ~RG_Matrix() {
    clear();
  }
  ////////////////////////////////////
  //operators
  /*void operator*=(RG_Matrix<type>& mat){

    uint nsizex = width;
    uint nsizey = mat.getSize(1);

    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    type* mt = RG::s_new<type>(nsizex*nsizey);

    for(uint y = 0; y<nsizey;y++)
    {
      for(uint x = 0; x<nsizex ;x++)
      {
        for(uint k = 0; k<nsizex;k++)
        {
          mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat.get_mat()[x+k*nsizex];
        }
      }

    }
    clear();
    //init(nsizex,nsizey,mt);
    movefill(nsizex,nsizey,mt);
    //free(mt);
  }*/
  /*void operator*=(initializer_list<initializer_list<type>> mat){
    uint nsizex = width;
    uint nsizey = mat.size();
    type* mt = RG::s_new<type>(nsizex*nsizey);
    for(uint y = 0; y<nsizey;y++){
      for(uint x = 0; x<nsizex ;x++){
        for(uint k = 0; k<nsizex;k++){
          mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat.begin()[k].begin()[x];//[x+k*nsizex];
        }
      }

    }
    clear();
    //init(nsizex,nsizey,mt);
    movefill(nsizex,nsizey,mt);
    //free(mt);
  }*/
  /*
   void operator*=(const initializer_list<initializer_list<type>>& mat) {
     if (width != mat.begin()->size())RG_Debug::addl(RG_LOG_CRITICAL, "Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '" + to_string(width) + "', height of the second matrix '" + to_string(mat.size()) + "'");
     uint nsizex = mat.begin()->size();
     uint nsizey = height;
     //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
     //type* mt = RG::s_new<type>(nsizex*nsizey);

     //type* out = RG::s_new<type>(nsizex*nsizey);
     type out[nsizex * nsizey];

     for (uint y = 0; y < nsizey;y++) {
       for (uint x = 0; x < nsizex;x++) {
         out[y * nsizey + x] = 0;
         for (uint k = 0; k < width;k++) {
           out[y * nsizey + x] += get(k, y) * mat[k][x];//[x+k*nsizex];
         }
       }
     }

     if (nsizex != width || nsizey != height) {
       init(nsizex, nsizey, out);
     } else {
       for (int i = 0; i < nsizex * nsizey;i++) {
         matrix[i] = out[i];
       }
     }
   }*/
  void operator*=(const type* mat) {

    //cout<<"div\n";
    uint nsizex = width;
    uint nsizey = height;

    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //cout<<"mem\n";
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    type mt[nsizex * nsizey];
    //cout<<"cycle\n";
    for (uint y = 0; y < nsizey; y++) {
      for (uint x = 0; x < nsizex; x++) {
        mt[y * nsizey + x] = 0;
        for (uint k = 0; k < nsizex; k++) {
          mt[x + y * nsizex] += matrix[y * nsizex + k] * mat[x + k * nsizex];
        }
      }

    }
    //cout<<"end cycle\n";
    //cout<<"clear\n";
      //init(nsizex,nsizey,mt);
    if (nsizex != width || nsizey != height) {
      init(nsizex, nsizey, mt);
    } else {
      for (int i = 0; i < nsizex * nsizey; i++) {
        matrix[i] = mt[i];
      }
    }
    //cout<<"init\n";
      //free(mt);
    //cout<<"free\n";
  }
  template<class type2>
  void operator *=(to_rvalue(initializer_list<initializer_list<type2>>) mat) {
    if (width != mat.size())RG_Debug::addl(RG_LOG_CRITICAL, "Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '" + to_string(width) + "', height of the second matrix '" + to_string(mat.size()) + "'");
    uint nsizex = mat.begin()->size();
    uint nsizey = height;
    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    //RG_Matrix<type> out(nsizex,nsizey);
    //type* out = RG::s_new<type>(nsizex*nsizey);
    type out[nsizex * nsizey];

    for (uint y = 0; y < nsizey; y++) {
      for (uint x = 0; x < nsizex; x++) {
        out[y * nsizey + x] = 0;
        for (uint k = 0; k < width; k++) {
          out[y * nsizey + x] += get(k, y) * mat.begin()[k].begin()[x];//[x+k*nsizex];
        }
      }
    }
    //clear();
    if (nsizex != width || nsizey != height) {
      init(nsizex, nsizey, out);
    } else {
      for (int i = 0; i < nsizex * nsizey; i++) {
        matrix[i] = out[i];
      }
    }
    //init(nsizex,nsizey,out);
  }

  void operator *=(const RG_Matrix<type>& mat) {
    if (width != mat.size(1))RG_Debug::addl(RG_LOG_CRITICAL, "Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '" + to_string(width) + "', height of the second matrix '" + to_string(mat.size(1)) + "'");
    uint nsizex = mat.size(0);
    uint nsizey = height;
    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    //RG_Matrix<type> out(nsizex,nsizey);
    //type* out = RG::s_new<type>(nsizex*nsizey);
    type out[nsizex * nsizey];

    for (uint y = 0; y < nsizey; y++) {
      for (uint x = 0; x < nsizex; x++) {
        out[y * nsizey + x] = 0;
        for (uint k = 0; k < width; k++) {
          out[y * nsizey + x] += get(k, y) * mat.get(x, k);//[x+k*nsizex];
        }
      }
    }
    //clear();
    if (nsizex != width || nsizey != height) {
      init(nsizex, nsizey, out);
    } else {
      for (int i = 0; i < nsizex * nsizey; i++) {
        matrix[i] = out[i];
      }
    }
    //init(nsizex,nsizey,out);
  }

  /*RG_Matrix<type>operator*(RG_Matrix<type> mat){

    uint nsizex = width;
    uint nsizey = mat.getSize(1);

    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    type* mt = RG::s_new<type>(nsizex*nsizey);
      for(uint y = 0; y<nsizey;y++)
      {
        for(uint x = 0; x<nsizex ;x++)
        {
          for(uint k = 0; k<nsizex;k++)
          {
            mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat.get_mat()[x+k*nsizex];
          }
        }

      }

    return RG_Matrix(nsizex,nsizey,mt);
  }*/
  template<class type2>
  RG_Matrix<type>operator*(const type2& in)const {
    //RG_Matrix<type> out(width,height,matrix);
    RG_Matrix<type> out(*this);

    for (uint y = 0; y < height; y++) {
      for (uint x = 0; x < width; x++) {
        out[y][x] *= in;
      }
    }

    return out;
  }

  template<class type2>
  RG_Matrix<type>operator%(to_rvalue(RG_Matrix<type2>)in)const {
    if (width != in.width || height != in.height)RG_Debug::addl(RG_LOG_CRITICAL, "Matrix % error, matrix sizes do not match");

    RG_Matrix<type>out(width, height);
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        out = get(j, i) * in[i][j];
      }
    }
    return out;
  }
  RG_Matrix<type>operator*(const RG_Matrix<type>& mat) {

    if (width != mat.size(1))RG_Debug::addl(RG_LOG_CRITICAL, "Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '" + to_string(width) + "', height of the second matrix '" + to_string(mat.size(1)) + "'");
    uint nsizex = mat.size(0);
    uint nsizey = height;
    //wcout<<"wtf\n";
    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    RG_Matrix<type> out(nsizex, nsizey);

    for (uint y = 0; y < nsizey; y++) {
      for (uint x = 0; x < nsizex; x++) {
        for (uint k = 0; k < width; k++) {
          out[y][x] += get(k, y) * mat.get(x, k);//[x+k*nsizex];
        }
      }
    }

    return out;
  }
  RG_Matrix<type>operator*(const RG_Array<type>& mat)const {

    //if(width!=1)RG_Debug::addl(RG_LOG_CRITICAL,"Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '"+to_string(width)+"', height of the second matrix '"+to_string(mat.size(1))+"'");
    if (width != 1)RG_Debug::addl(RG_LOG_CRITICAL, "Matrix multiplication error (matrix by array) width of the matrix does not match array height (1), width of the matrix '" + to_string(width) + "', array height '1'");
    //wcout<<"DEBUG, DELETE, "<<__LINE__<<" MATRIX!\n"<<"width/height of the matrix '"<<width<<"'/'"<<height<<"', array width '"<<mat.size()<<"'"<<endl;
    uint nsizex = mat.size();
    uint nsizey = height;
    RG_Matrix<type> out(nsizex, nsizey);

    /*for(uint y = 0; y<nsizey;y++){
      for(uint x = 0; x<nsizex ;x++){
        out[y][x]+=get(1,y) * mat[x];
      }
    }*/
    /*wcout<<"\ntest1\n";
    this->print();
    wcout<<"test1\n";
    wcout<<"\ntest2\n";
    mat.print();
    wcout<<"test2\n";*/
    for (uint y = 0; y < nsizey; y++) {
      for (uint x = 0; x < nsizex; x++) {
        for (uint k = 0; k < width; k++) {
          out[y][x] += get(k, y) * mat[x];//[x+k*nsizex];
        }
      }
    }
    /*wcout<<"\ntest3\n";
    out.print();
    wcout<<"test3\n";*/
    return out;
  }

  void operator+=(const RG_Matrix<type>& mat) {
    if (width != mat.width || height != mat.height)RG_Debug::addl(RG_LOG_CRITICAL, "Matrix += error, matrix sizes do not match");
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        get(j, i) += mat.get(j, i);
      }
    }
  }
  void operator-=(const RG_Matrix<type>& mat) {
    //wcout<<"\nTEST\n";
    if (width != mat.width || height != mat.height)RG_Debug::addl(RG_LOG_CRITICAL, "Matrix -= error, matrix sizes do not match, this mat width/height = '" + to_string(width) + "'/'" + to_string(height) + "', right mat width/height = '" + to_string(mat.size(0)) + "'/'" + to_string(mat.size(1)) + "'");
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        get(j, i) -= mat.get(j, i);
      }
    }
  }




  /*const RG_Matrix<type>& operator*(const RG_Array<type>& mat){

    //if(width!=1)RG_Debug::addl(RG_LOG_CRITICAL,"Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '"+to_string(width)+"', height of the second matrix '"+to_string(mat.size(1))+"'");
    if(width!=1)RG_Debug::addl(RG_LOG_CRITICAL,"Matrix multiplication error (matrix by array) width of the matrix does not match array height (1), width of the matrix '"+to_string(width)+"', array height '1'");
    uint nsizex = mat.size();
    uint nsizey = height;
    RG_Matrix<type> out(nsizex,nsizey);

    for(uint y = 0; y<nsizey;y++){
      for(uint x = 0; x<nsizex ;x++){
        out[y][x]+=get(1,y) * mat[x];
      }
    }
    const RG_Matrix<type> &outt = out;
    return outt;
  }*/

  /*RG_Matrix<type>operator*(const type& a){
    RG_Matrix<type>out(width,height);
    for(int i = 0; i<height;i++){
      for(int j = 0; j<width;j++){
        out[i][j]=get(j,i)*a;
      }
    }
    return out;
  }*/

  template<class tttt>
  void place(POINT2D<int> pl, RG_Matrix<tttt>& matr) {
    //cout<<matr.size(0)<<endl;
    //cout<<matr.size(1)<<endl;
    //exit(-2);
    for (int y = pl.y; y < matr.size(1) + pl.y; y++) {
      for (int x = pl.x; x < matr.size(0) + pl.x; x++) {
        get(x, y) = matr.getyx(y - pl.y, x - pl.x);
      }
    }

    /*for(int y = pl.y; y<matr.size(1)+pl.y&&y+pl.y<height;y++){
      for(int x = pl.x; x<matr.size(0)+pl.x&&x+pl.x<width;x++){

        //type asd = get(x,y);

        //asd = matr.get(x-pl.x,y-pl.y);

        //get(x,y) = matr.get(x-pl.x,y-pl.y);
        //cout<<y<<" "<<x<<endl;
        get(x,y) = matr[y-pl.y][x-pl.x];//.get(x-pl.x,y-pl.y);
      }
    }*/
  }

  /*void set_stbi(){
    matrix.set_stbi();
  }*/
};



template<class type, class type2>
type SpecialMatMulti(RG_Matrix<type>& mat1, RG_Matrix<type2>& mat2, int pos1, int pos2) {
  type out = 0;
  for (int i = 0; i < mat1.size(0); i++) {
    out += mat1.get(i, pos1) * mat2.get(pos2, i);
  }
  return out;
}

//Удалить
template<class type, class type2>
bool CountMatMinus(RG_Matrix<type>& mat1, RG_Matrix<type2>& mat2, int pos1, int pos2) {
  bool out = false;
  for (int i = 0; i < mat1.size(0); i++) {
    if (mat1.get(i, pos1) < 0)out = !out;
    if (mat2.get(pos2, i) < 0)out = !out;
  }
  return out;
}
/*type SpecialMatMulti(RG_Matrix<type>&mat1,RG_Matrix<type2>&mat2,int pos1){
  type out = 0;
  for(int i = 0; i<mat1.size(0);i++){
    out+=mat1.get(i,pos1)*mat2.get(i,pos2);
  }
  return out;
}*/