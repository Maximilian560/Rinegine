#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/types/matrix3D"


template<typename type>
class RG_Matrix3D {
  //RG_Matrix3D<type>*transonir = nullptr;
  //bool transpos = false;
  RG_Array<type> matrix;
  uint width = 0, height = 0, depth = 0;
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

  void init(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z) {
    resize(x, y, z);
  }
  void init(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z, type* arr) {
    fill(x, y, z, arr);
  }
  void init(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z, to_rvalue(type) arr) {
    fill(x, y, z, arr);
  }
  /*void reInit(to_rvalue(uint) x, to_rvalue(uint) y,const type*mat){
    fill(x,y,mat);
  }*/
  void init(to_rvalue(RG_Matrix3D<type>)ar) { fill(ar); }

  RG_Matrix3D() {}
  RG_Matrix3D(to_rvalue(RG_Array<type>) ar) { init(ar); }
  RG_Matrix3D(to_rvalue(RG_Matrix3D<type>) ar) { init(ar); }
  RG_Matrix3D(to_rvalue(initializer_list<initializer_list<type>>) arr) { init(arr); }
  //RG_Matrix3D(initializer_list<type> arr){init(arr);}
  RG_Matrix3D(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z) { init(x, y, z); }
  RG_Matrix3D(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z, type* arr) { init(x, y, z, arr); }
  RG_Matrix3D(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z, to_rvalue(type)arr) { init(x, y, z, arr); }

  //void operator=(){}
  void operator=(to_rvalue(initializer_list<initializer_list<type>>) in) {
    init(in);
  }
  void operator=(to_rvalue(RG_Array<type>)in) {
    if (matrix.size() != 0) {
      if (matrix.size() != in.matrix.size())rg_cout << RG_L"ВНИМАНИЕ! РАЗМЕР МАССИВА МАТРИЦЫ БЫЛ ИЗМЕНЁН МАССИВОМ С " << matrix.size() << RG_L" НА '" << in.matrix.size() << RG_L"' !!!!\n";
    }
    init(in);
  }
  void operator=(to_rvalue(RG_Matrix3D<type>)in) {
    if (matrix.size() != 0) {
      if (matrix.size() != in.matrix.size())rg_cout << RG_L"ВНИМАНИЕ! РАЗМЕР МАТРИЦЫ И ЕГО МАССИВА БЫЛ ИЗМЕНЁН С " << matrix.size() << RG_L" НА '" << in.matrix.size() << RG_L"' !!!!\n" << RG_L"ШИРИНА И ВЫСОТА С " << width << RG_L"' '" << height << RG_L"' НА '" << in.width << RG_L"' '" << in.height << RG_L"'!!!!\n";
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
      width = x;
      height = 1;
      depth = 1;
    } else {
      clear();
    }
  }

  void resize(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z) {
    if (y * x * z > 0) {
      matrix.resize(y * x * z);
      width = x;
      height = y;
      depth = z;
    } else {
      clear();
    }
  }
  void resize(to_rvalue(POINT3D<uint>)ns) {
    if (ns.y * ns.x * ns.z > 0) {
      matrix.resize(ns.y * ns.x * ns.z);
      width = ns.x;
      height = ns.y;
      depth = ns.z;
    } else {
      clear();
    }
  }
  void resize(to_rvalue(POINT3D<int>)ns) {
    if (ns.y * ns.x * ns.z > 0) {
      matrix.resize(ns.y * ns.x * ns.z);
      width = ns.x;
      height = ns.y;
      depth = ns.z;
    } else {
      clear();
    }
  }
  //////
  //fill
  void fill(to_rvalue(RG_Matrix3D<type>)ar) {
    //rg_cout<<ar.size(0)<<" "<<ar.size(1)<<" "<<ar.size(2)<<endl;
    //matrix.resize(ar.size(2));
    //transpos = ar.transpos;
    resize(ar.size());
    for (int z = 0; z < ar.size(2); z++) {
      for (int y = 0; y < ar.size(1); y++) {
        for (int x = 0; x < ar.size(0); x++) {
          get(x, y, z) = ar.get(x, y, z);
        }
      }
    }
  }
  void fill(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z, type* mat) {
    resize(x, y, z);
    for (int zz = 0; zz < z; zz++) {
      for (int yy = 0; yy < y; yy++) {
        for (int xx = 0; xx < x; xx++) {
          matrix[zz * y * x + yy * x + xx] = mat[yy * x + xx];
        }
      }
    }
  }
  void fill(to_rvalue(RG_Array<type>) arr) {

    resize(arr.size());
    matrix = arr;
  }
  void fill(to_rvalue(initializer_list<initializer_list<initializer_list<type>>>) arr) {
    resize(arr.begin()->size(), arr.size());
    //rg_cout<<width<<"||"<<height<<endl;
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          getzyx(z, y, x) = arr.begin()[z].begin()[y].begin()[x];
        }
      }
    }
  }
  template<class type2>
  void fill(to_rvalue(initializer_list<initializer_list<initializer_list<type2>>>) arr) {
    resize(arr.begin()->size(), arr.size());
    //rg_cout<<width<<"||"<<height<<endl;
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          getzyx(z, y, x) = arr.begin()[z].begin()[y].begin()[x];
        }
      }
    }
  }
  /*void fill(initializer_list<type>arr){
    resize(arr.size());
    for(int i = 0; i<arr.size();i++){
      matrix[i] = arr.begin()[i];
    }
  }*/
  void movefill(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z, type* mat) {
    clear();
    matrix.movefill(x * y * z, mat);
    width = x;
    height = y;
    depth = z;
  }

  /*void fillfull(to_rvalue(uint) size, to_rvalue(type) mat) {
    for(int i = 0;i<size;i++){
      matrix[i] = mat;
    }
  }*/
  void fill(to_rvalue(type) mat) {
    matrix.fill(mat);
  }
  void fill(to_rvalue(uint) x, to_rvalue(uint) y, to_rvalue(uint) z, to_rvalue(type) mat) {
    resize(x, y, z);
    matrix.fillfull(x * y * z, mat);
  }

  void randomBoolFill(to_rvalue(double) porog, to_rvalue(double) max = 1) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          matrix[z * height * width + y * width + x] = ((rand() / (RAND_MAX / max) > porog) ? 1 : 0);
        }
      }
    }
  }
  void randomBoolAddFill(to_rvalue(double) porog, to_rvalue(double) max = 1) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          if (get(x, y, z) != 1)get(x, y, z) = ((rand() / (RAND_MAX / max) > porog) ? 1 : 0);
        }
      }
    }
  }

  void randomAddFill(to_rvalue(double) porog, to_rvalue(double) max = 1) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          if (get(z, y, x) != 1)get(z, y, x) = rand() / (RAND_MAX / max);
        }
      }
    }
  }

  void random_fill(to_rvalue(double) max = 1) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          get(z, y, x) = rand() / (RAND_MAX / max);
        }
      }
    }
  }

  void noise_fill(to_rvalue(int) seed = 0) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          get(z, y, x) = rand();
        }
      }
    }
  }
  void noise_dbool_fill(to_rvalue(int) seed = 0) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          get(z, y, x) = 1. * rand() / RAND_MAX;
        }
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
    //RG_Matrix3D<type>mat2;
    type mat2[width * a * height * a * depth * a];
    //mat2.init(width*a,height*a);
    for (int z = 0; z < depth * a; z++) {
      for (int y = 0; y < height * a; y++) {
        for (int x = 0; x < width * a; x++) {
          mat2.get(x, y, z) = get(z / a, y / a, x / a);
        }
      }
    }
    fill(mat2.size(0), mat2.size(1), mat2.size(2), mat2);
    mat2.clear();
  }
  /*
  void smoothScale(to_rvalue(int) a) {
    RG_Matrix3D<type>mat2;
    mat2.init(width * a, height * a);
    for (int z = 0;z < depth * a;z++) {
      for (int y = 0;y < height * a;y += a) {
        for (int x = 0; x < width * a;x += a) {
          mat2.get(x, y) = matrix[(y / a) * width + (x / a)];
        }
      }
    }

    for (int g = 1; g < a;g++) {
      for (int z = g;z < depth * a;z += a) {
        for (int y = g;y < height * a;y += a) {
          for (int x = g; x < width * a;x += a) {
            //rg_cout<<x<<" "<<y<<" "<<g<<endl;
          //rg_cout<<((x-g)/a)<<" "<<((y-g)/a)<<" "<<g<<endl<<endl;

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
    }


    fill(mat2.size(0), mat2.size(1), mat2.get_mat());
    mat2.clear();

  }*/
  /*
    RG_Matrix3D<type> transpose() {
      //RG_Matrix3D<type>* tr = new RG_Matrix3D<type>();
      RG_Matrix3D<type> trans(height, width, depth);
      for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
          trans[j][i] = get(j, i);
        }
      }
      return trans;
    }*/
    ////////
    //indexs
    /*type&operator[](uint i){
      if(i>=0){
        if(i<matrix.size()){
          return matrix[i];
        }
        else {
          rg_cout<<"ERROR! Size 2D matrix loss then 'i' in operator[](uint i)\n";
          rg_cout<<"Size = "<<matrix.size()<<" | i = "<<i<<endl;
          exit(-1);}
      }
      else{
        if(matrix.size()+i<matrix.size()){
          return matrix[matrix.size()+i];
        }
        else{
          rg_cout<<"ERROR! Size 2D matrix loss then 'size + i' in operator[](uint i)\n";
          rg_cout<<"Size = "<<matrix.size()<<" i = "<<i<<endl;
          exit(-1);
        }
      }

    }*/
    /*
     type* operator[](const uint& i)const {
       if (i >= height)RG_LOG_LOCK_CRITICAL("matrix height is less than " + to_string(i + 1) + "(you set " + to_string(i) + ") and equal to " + to_string(height));
       if (!RG_EXCEED_LIMIN_MATRIX) { RG_LOG_LOCK_WARNING("When using [y][x] it is possible to exceed the limit, check that x is not larger than the width of the matrix. This warning will no longer appear");RG_EXCEED_LIMIN_MATRIX = 1; }
       return &matrix[i * width];
     }*/


     // type& get(const uint& x, const uint& y, const uint& z)const {
     //   if (y >= height) {
     //     RG_LOG_LOCK_CRITICAL("Matrix height less than or equal to 'y' in 'get(x,y)'\n\
     //     'Height' = '" + to_string(height) + "', 'y' = '" + to_string(y) + "'");
     //   }
     //   if (x >= width) {
     //     RG_LOG_LOCK_CRITICAL("Matrix width less than or equal to 'x' in 'get(x,y)'\n\
     //     'Width' = '" + to_string(width) + "', 'x' = '" + to_string(x) + "'");
     //   }
     //   return matrix[y * width + x];
     // }
  type& get(const uint& x, const uint& y, const uint& z)const {
    if (x >= width || y >= height || z >= depth) {
      int types = 0;
      string error;
      if (x >= width)error += "'x'";
      if (y >= height) { if (error.size())error += ", "; error += "'y'"; }
      if (z >= depth) { if (error.size())error += ", "; error += "'z'"; }
      string output_err = "Matrix size less or equal than " + error + " in 'get(x,y,z)'\n width == " + to_string(width) + ", height == " + to_string(height) + ", depth == " + to_string(depth) + "; x == " + to_string(x) + ", y == " + to_string(y) + ", z == " + to_string(z);
      RG_LOG_LOCK_CRITICAL(output_err);
    }
    if (z * height * width + y * width + x >= matrix.size()) {
      RG_LOG_LOCK_CRITICAL("Size matrix grateful then array size in 'get(x,y,z)':\nsize  array == " + to_string(matrix.size()) + "size matrix: width == " + to_string(width) + ", height == " + to_string(height) + ", depth == " + to_string(depth));
    }
    // if (z >= depth) {
    //   RG_LOG_LOCK_CRITICAL("Matrix depth less than or equal to 'z' in 'get(x,y,z)'\n\
    //   'Depth' = '" + to_string(depth) + "', 'z' = '" + to_string(z) + "'");
    // }
    // if (y >= height) {
    //   RG_LOG_LOCK_CRITICAL("Matrix height less than or equal to 'y' in 'get(x,y,z)'\n\
    //   'Height' = '" + to_string(height) + "', 'y' = '" + to_string(y) + "'");
    // }
    // if (x >= width) {
    //   RG_LOG_LOCK_CRITICAL("Matrix width less than or equal to 'x' in 'get(x,y,z)'\n\
    //   'Width' = '" + to_string(width) + "', 'x' = '" + to_string(x) + "'");
    // }
    return matrix[z * height * width + y * width + x];
  }
  type& getzyx(to_rvalue(uint) z, to_rvalue(uint) y, to_rvalue(uint) x)const {
    if (z >= depth || y >= height || x >= width) {
      int types = 0;
      string error;
      if (y >= depth) { error += "'z'"; }
      if (y >= height) { if (error.size())error += ", "; error += "'y'"; }
      if (x >= width) { if (error.size())error += ", "; error += "'x'"; }
      string output_err = "Matrix size less than or equal to " + error + " in 'getzyx(z,y,x)'\n width == " + to_string(width) + ", height == " + to_string(height) + ", depth == " + to_string(depth) + "; x == " + to_string(x) + ", y == " + to_string(y) + ", z == " + to_string(z);
      RG_LOG_LOCK_CRITICAL(output_err);
    }
    if (z * height * width + y * width + x >= matrix.size()) {
      RG_LOG_LOCK_CRITICAL("Size matrix grateful then array size in 'getzyx(z,y,x)':\nsize  array == " + to_string(matrix.size()) + "size matrix: width == " + to_string(width) + ", height == " + to_string(height) + ", depth == " + to_string(depth));
    }
    // RG_LOG_LOCK_CRITICAL( "'z' in 'getzyx(z,y,x)'\n\
      // 'Depth' = '" + to_string(depth) + "', 'z' = '" + to_string(z) + "'");
    // if (y >= height) {
    //   RG_LOG_LOCK_CRITICAL("Matrix height less than or equal to 'y' in 'getzyx(z,y,x)'\n\
    //   'Height' = '" + to_string(height) + "', 'y' = '" + to_string(y) + "'");
    // }
    // if (x >= width) {
    //   RG_LOG_LOCK_CRITICAL("Matrix width less than or equal to 'x' in 'getzyx(z,y,x)'\n\
    //   'Width' = '" + to_string(width) + "', 'x' = '" + to_string(x) + "'");
    // }
    return matrix[z * height * width + y * width + x];
  }
  type& get(to_rvalue(POINT3D<uint>)pos)const {
    if (pos.x >= width) {
      RG_LOG_LOCK_CRITICAL("Matrix width less than or equal to 'pos.x' in 'get(POINT3D<uint>pos)'\n\
      'Width' = '" + to_string(width) + "', 'pos.x' = '" + to_string(pos.x) + "'");
    }
    if (pos.y >= height) {
      RG_LOG_LOCK_CRITICAL("Matrix height less than or equal to 'pos.y' in 'get(POINT3D<uint>pos)'\n\
      'Height' = '" + to_string(height) + "', 'pos.y' = '" + to_string(pos.y) + "'");
    }
    if (pos.z >= depth) {
      RG_LOG_LOCK_CRITICAL("Matrix depth less than or equal to 'pos.z' in 'get(POINT3D<uint>pos)'\n\
      'Depth' = '" + to_string(depth) + "', 'pos.z' = '" + to_string(pos.z) + "'");
    }

    return matrix[pos.z * height * width + pos.y * width + pos.x];
  }
  type& get(to_rvalue(POINT3D<int>)pos)const {
    if (pos.z >= depth) {
      RG_LOG_LOCK_CRITICAL("Matrix depth less than or equal to 'pos.z' in 'get(POINT3D<int>pos)'\n\
      'Depth' = '" + to_string(depth) + "', 'pos.z' = '" + to_string(pos.z) + "'");
    }
    if (pos.x >= width) {
      RG_LOG_LOCK_CRITICAL("Matrix width less than or equal to 'pos.x' in 'get(POINT3D<int>pos)'\n\
      'Width' = '" + to_string(width) + "', 'pos.x' = '" + to_string(pos.x) + "'");
    }
    if (pos.y >= height) {
      RG_LOG_LOCK_CRITICAL("Matrix height less than or equal to 'pos.y' in 'get(POINT3D<int>pos)'\n\
      'Height' = '" + to_string(height) + "', 'pos.y' = '" + to_string(pos.y) + "'");
    }

    return matrix[pos.z * height * width + pos.y * width + pos.x];
  }
  void print()const {
    for (int i = 0; i < depth; i++) {
      for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
          rg_cout << getzyx(i, j, k) << " ";
        }
        rg_cout << endl;
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
      case 2: return depth;
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
  POINT3D<uint> size() const {
    return { width,height ,depth };
  }
  ///////
  //clear
  void clear() {
    //if(!matrix.empty()){
      //free(array);
    matrix.clear();
    width = 0;
    height = 0;
    depth = 0;
    //if(transonir!=nullptr)
    //  delete transonir;
 // }
  }
  ~RG_Matrix3D() {
    matrix.~RG_Array();
    width = 0;
    height = 0;
    depth = 0;
  }
  ////////////////////////////////////
 /* void operator*=(type* mat) {

    //rg_cout<<"div\n";
    uint nsizex = width;
    uint nsizey = height;
    uint nsizez = depth;

    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //rg_cout<<"mem\n";
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    type mt[nsizex * nsizey];
    //rg_cout<<"cycle\n";
    for (uint y = 0; y < nsizey;y++) {
      for (uint x = 0; x < nsizex;x++) {
        mt[y * nsizey + x] = 0;
        for (uint k = 0; k < nsizex;k++) {
          mt[x + y * nsizex] += matrix[y * nsizex + k] * mat[x + k * nsizex];
        }
      }

    }
    //rg_cout<<"end cycle\n";
    //rg_cout<<"clear\n";
      //init(nsizex,nsizey,mt);
    if (nsizex != width || nsizey != height) {
      init(nsizex, nsizey, mt);
    } else {
      for (int i = 0; i < nsizex * nsizey;i++) {
        matrix[i] = mt[i];
      }
    }
    //rg_cout<<"init\n";
      //free(mt);
    //rg_cout<<"free\n";
  }
  template<class type2>
  void operator *=(to_rvalue(initializer_list<initializer_list<type2>>) mat) {
    if (width != mat.size())RG_LOG_LOCK_CRITICAL("Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '" + to_string(width) + "', height of the second matrix '" + to_string(mat.size()) + "'");
    uint nsizex = mat.begin()->size();
    uint nsizey = height;
    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    //RG_Matrix3D<type> out(nsizex,nsizey);
    //type* out = RG::s_new<type>(nsizex*nsizey);
    type out[nsizex * nsizey];

    for (uint y = 0; y < nsizey;y++) {
      for (uint x = 0; x < nsizex;x++) {
        out[y * nsizey + x] = 0;
        for (uint k = 0; k < width;k++) {
          out[y * nsizey + x] += get(k, y) * mat.begin()[k].begin()[x];//[x+k*nsizex];
        }
      }
    }
    //clear();
    if (nsizex != width || nsizey != height) {
      init(nsizex, nsizey, out);
    } else {
      for (int i = 0; i < nsizex * nsizey;i++) {
        matrix[i] = out[i];
      }
    }
    //init(nsizex,nsizey,out);
  }

  void operator *=(const RG_Matrix3D<type>& mat) {
    if (width != mat.size(1))RG_LOG_LOCK_CRITICAL("Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '" + to_string(width) + "', height of the second matrix '" + to_string(mat.size(1)) + "'");
    uint nsizex = mat.size(0);
    uint nsizey = height;
    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    //RG_Matrix3D<type> out(nsizex,nsizey);
    //type* out = RG::s_new<type>(nsizex*nsizey);
    type out[nsizex * nsizey];

    for (uint y = 0; y < nsizey;y++) {
      for (uint x = 0; x < nsizex;x++) {
        out[y * nsizey + x] = 0;
        for (uint k = 0; k < width;k++) {
          out[y * nsizey + x] += get(k, y) * mat.get(x, k);//[x+k*nsizex];
        }
      }
    }
    //clear();
    if (nsizex != width || nsizey != height) {
      init(nsizex, nsizey, out);
    } else {
      for (int i = 0; i < nsizex * nsizey;i++) {
        matrix[i] = out[i];
      }
    }
    //init(nsizex,nsizey,out);
  }

  / *RG_Matrix3D<type>operator*(RG_Matrix3D<type> mat){

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

    return RG_Matrix3D(nsizex,nsizey,mt);
  }*/
  template<class type2>
  RG_Matrix3D<type>operator*(const type2& in)const {
    //RG_Matrix3D<type> out(width,height,matrix);
    RG_Matrix3D<type> out(*this);

    for (uint z = 0; z < depth; z++) {
      for (uint y = 0; y < height; y++) {
        for (uint x = 0; x < width; x++) {
          out.get(x, y, z) *= in;
        }
      }
    }
    return out;
  }

  template<class type2>
  RG_Matrix3D<type>operator%(to_rvalue(RG_Matrix3D<type2>)in)const {
    if (width != in.width || height != in.height)RG_LOG_LOCK_CRITICAL("Matrix % error, matrix sizes do not match");

    RG_Matrix3D<type>out(width, height);
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          out = get(x, y, z) * in.get(x, y, z);
        }
      }
    }
    return out;
  }
  /*
  RG_Matrix3D<type>operator*(const RG_Matrix3D<type>& mat) {

    if (width != mat.size(1))RG_LOG_LOCK_CRITICAL("Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '" + to_string(width) + "', height of the second matrix '" + to_string(mat.size(1)) + "'");
    uint nsizex = mat.size(0);
    uint nsizey = height;
    //rg_cout<<"wtf\n";
    //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //type* mt = RG::s_new<type>(nsizex*nsizey);
    RG_Matrix3D<type> out(nsizex, nsizey);

    for (uint y = 0; y < nsizey;y++) {
      for (uint x = 0; x < nsizex;x++) {
        for (uint k = 0; k < width;k++) {
          out[y][x] += get(k, y) * mat.get(x, k);//[x+k*nsizex];
        }
      }
    }

    return out;
  }*/
  /*RG_Matrix3D<type>operator*(const RG_Array<type>& mat)const {

    //if(width!=1)RG_LOG_LOCK_CRITICAL("Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '"+to_string(width)+"', height of the second matrix '"+to_string(mat.size(1))+"'");
    if (width != 1)RG_LOG_LOCK_CRITICAL("Matrix multiplication error (matrix by array) width of the matrix does not match array height (1), width of the matrix '" + to_string(width) + "', array height '1'");
    //rg_cout<<"DEBUG, DELETE, "<<__LINE__<<" MATRIX!\n"<<"width/height of the matrix '"<<width<<"'/'"<<height<<"', array width '"<<mat.size()<<"'"<<endl;
    uint nsizex = mat.size();
    uint nsizey = height;
    RG_Matrix3D<type> out(nsizex, nsizey);

    / *for(uint y = 0; y<nsizey;y++){
      for(uint x = 0; x<nsizex ;x++){
        out[y][x]+=get(1,y) * mat[x];
      }
    }* /
    / *rg_cout<<"\ntest1\n";
    this->print();
    rg_cout<<"test1\n";
    rg_cout<<"\ntest2\n";
    mat.print();
    rg_cout<<"test2\n";* /
  for (uint y = 0; y < nsizey;y++) {
    for (uint x = 0; x < nsizex;x++) {
      for (uint k = 0; k < width;k++) {
        out[y][x] += get(k, y) * mat[x];//[x+k*nsizex];
      }
    }
  }
  / *rg_cout<<"\ntest3\n";
  out.print();
  rg_cout<<"test3\n";* /
  return out;
}*/

  void operator+=(const RG_Matrix3D<type>& mat) {
    if (width != mat.width || height != mat.height)RG_LOG_LOCK_CRITICAL("Matrix += error, matrix sizes do not match");

    for (int i = 0; i < depth; i++) {
      for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
          get(k, j, i) += mat.get(k, j, i);
        }
      }
    }
  }
  void operator-=(const RG_Matrix3D<type>& mat) {
    //rg_cout<<"\nTEST\n";
    if (width != mat.width || height != mat.height)RG_LOG_LOCK_CRITICAL("Matrix -= error, matrix sizes do not match, this mat width/height = '" + to_string(width) + "'/'" + to_string(height) + "', right mat width/height = '" + to_string(mat.size(0)) + "'/'" + to_string(mat.size(1)) + "'");
    for (int i = 0; i < depth; i++) {
      for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
          get(k, j, i) -= mat.get(k, j, i);
        }
      }
    }
  }




  /*const RG_Matrix3D<type>& operator*(const RG_Array<type>& mat){

    //if(width!=1)RG_LOG_LOCK_CRITICAL("Matrix multiplication error, the width of the first matrix does not match the height of the second matrix, width of the first '"+to_string(width)+"', height of the second matrix '"+to_string(mat.size(1))+"'");
    if(width!=1)RG_LOG_LOCK_CRITICAL("Matrix multiplication error (matrix by array) width of the matrix does not match array height (1), width of the matrix '"+to_string(width)+"', array height '1'");
    uint nsizex = mat.size();
    uint nsizey = height;
    RG_Matrix3D<type> out(nsizex,nsizey);

    for(uint y = 0; y<nsizey;y++){
      for(uint x = 0; x<nsizex ;x++){
        out[y][x]+=get(1,y) * mat[x];
      }
    }
    const RG_Matrix3D<type> &outt = out;
    return outt;
  }*/

  /*RG_Matrix3D<type>operator*(const type& a){
    RG_Matrix3D<type>out(width,height);
    for(int i = 0; i<height;i++){
      for(int j = 0; j<width;j++){
        out[i][j]=get(j,i)*a;
      }
    }
    return out;
  }*/

  template<class tttt>
  void place(POINT3D<int> pl, RG_Matrix3D<tttt>& matr) {
    //rg_cout<<matr.size(0)<<endl;
    //rg_cout<<matr.size(1)<<endl;
    //exit(-2);
    for (int z = pl.z; z < matr.size(2) + pl.z && z + pl.z < depth; z++) {
      for (int y = pl.y; y < matr.size(1) + pl.y; y++) {
        for (int x = pl.x; x < matr.size(0) + pl.x; x++) {
          get(x, y, z) = matr.getyx(y - pl.y, x - pl.x, z - pl.z);
        }
      }
    }
    /*for(int y = pl.y; y<matr.size(1)+pl.y&&y+pl.y<height;y++){
      for(int x = pl.x; x<matr.size(0)+pl.x&&x+pl.x<width;x++){

        //type asd = get(x,y);

        //asd = matr.get(x-pl.x,y-pl.y);

        //get(x,y) = matr.get(x-pl.x,y-pl.y);
        //rg_cout<<y<<" "<<x<<endl;
        get(x,y) = matr[y-pl.y][x-pl.x];//.get(x-pl.x,y-pl.y);
      }
    }*/
  }

  /*void set_stbi(){
    matrix.set_stbi();
  }*/
};