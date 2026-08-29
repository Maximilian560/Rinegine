#pragma once
namespace Rinegine::Kernel {

  template<typename type>
  class Matrix {
    Array<type> matrix;
    size_t width = 0, height = 0;
  public:
    //init
    void init(size_t x, size_t y) {
      resize(x, y);
    }
    void init(size_t x, size_t y, type* arr) {
      fill(x, y, arr);
    }
    void init(size_t x, size_t y, type arr) {
      fill(x, y, arr);
    }
    void reInit(size_t x, size_t y, type* mat) {
      fill(x, y, mat);
    }

    Matrix() {}
    Matrix(size_t x, size_t y) { init(x, y); }
    Matrix(size_t x, size_t y, type* arr) { init(x, y, arr); }
    Matrix(size_t x, size_t y, type arr) { init(x, y, arr); }
    ////////
    //resize
    /*void resize(size_t x, size_t y){
      if(x*y!=0){
        type* arr = s_calloc<type>(x*y);

        for(int Y = 0; Y<height;Y++){
          for(int X = 0; X<width;X++){
            arr[Y*x+X] = get(X,Y);
          }
        }
        matrix.clear();
        matrix.fill(x*y,arr);
        //matrix.resize(x*y);
        width = x;
        height = y;
      }else{
        if(!matrix.empty()) clear();
      }
    }*/
    void resize(size_t x, size_t y) {
      if (x * y > 0) {
        matrix.resize(x * y);
        width = x;
        height = y;
      }
      else {
        clear();
      }
    }
    void resize(Rinegine::Kernel::vec2<size_t> in) {
      if (in.x * in.y > 0) {
        matrix.resize(in.x * in.y);
        width = in.x;
        height = in.y;
      }
      else {
        clear();
      }
    }
    //////
    //fill
    void fill(size_t x, size_t y, type* mat) {
      clear();
      resize(x, y);
      for (size_t yy = 0; yy < y;yy++) {
        for (size_t xx = 0; xx < x;xx++) {
          matrix[yy * x + xx] = mat[yy * x + xx];
        }
      }
    }

    void fill(type mat) {
      matrix.fill(mat);
    }
    void fill(size_t x, size_t y, type mat) {
      clear();
      matrix.fillfull(x * y, mat);
    }

    void randomBoolFill(double porog, double max = 1) {
      for (int y = 0; y < height;y++) {
        for (int x = 0; x < width;x++) {
          matrix[y * width + x] = ((rand() / (RAND_MAX / max) > porog) ? 1 : 0);
        }
      }
    }
    void randomBoolAddFill(double porog, double max = 1) {
      for (int y = 0; y < height;y++) {
        for (int x = 0; x < width;x++) {
          if (matrix[y * width + x] != 1)matrix[y * width + x] = ((rand() / (RAND_MAX / max) > porog) ? 1 : 0);
        }
      }
    }

    void randomAddFill(double porog, double max = 1) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          if (matrix[y * width + x] != 1) {
            double val = (double)rand() / (RAND_MAX / max);
            if (val > porog) {
              matrix[y * width + x] = val;
            }
          }
        }
      }
    }


    void randomFill(double max = 1) {
      for (int y = 0; y < height;y++) {
        for (int x = 0; x < width;x++) {
          matrix[y * width + x] = rand() / (RAND_MAX / max);
        }
      }
    }


    void scale(size_t a) {
      Matrix<type>mat2;
      mat2.init(width * a, height * a);
      for (int y = 0;y < height * a;y++) {
        for (int x = 0; x < width * a;x++) {
          mat2.get(x, y) = matrix[(y / a) * width + (x / a)];
        }
      }
      reInit(mat2.size(0), mat2.size(1), mat2.get_mat());
      mat2.clear();
    }
    void smoothScale(int a) {
      Matrix<type>mat2;
      mat2.init(width * a, height * a);
      for (int y = 0;y < height * a;y += a) {
        for (int x = 0; x < width * a;x += a) {
          mat2.get(x, y) = matrix[(y / a) * width + (x / a)];
        }
      }

      for (int g = 1; g < a;g++) {
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


      reInit(mat2.size(0), mat2.size(1), mat2.get_mat());
      mat2.clear();

    }
    ////////
    //indexs
    /*type&operator[](size_t i){
      if(i>=0){
        if(i<matrix.size()){
          return matrix[i];
        }
        else {
          rg_cout<<"ERROR! Size 2D matrix loss then 'i' in operator[](size_t i)\n";
          rg_cout<<"Size = "<<matrix.size()<<" | i = "<<i<<endl;
          exit(-1);}
      }
      else{
        if(matrix.size()+i<matrix.size()){
          return matrix[matrix.size()+i];
        }
        else{
          rg_cout<<"ERROR! Size 2D matrix loss then 'size + i' in operator[](size_t i)\n";
          rg_cout<<"Size = "<<matrix.size()<<" i = "<<i<<endl;
          exit(-1);
        }
      }

    }*/
    type* operator[](size_t i) {
      if (i >= height)RG_LOG_CRITICAL("matrix height is less than " + std::to_string(i + 1) + "(you set " + std::to_string(i) + ") and equal to " + std::to_string(height));
      return &matrix[i * width];
    }
    type& operator[](Kernel::vec2<size_t> pos) {
      if (pos.x >= width) {
        rg_cout << "ERROR! Width matrix loss then 'pos.x' in get(Kernel::vec2<size_t>pos)\n";
        rg_cout << "Width = " << width << " pos.x = " << pos.x << std::endl;
        exit(-1);
      }
      if (pos.y >= height) {
        rg_cout << "ERROR! Height matrix loss then 'pos.y' in get(Kernel::vec2<size_t>pos)\n";
        rg_cout << "Height = " << height << " pos.y = " << pos.y << std::endl;
        exit(-1);
      }

      return matrix[pos.y * width + pos.x];
    }

    type& get(size_t x, size_t y) {
      if (x >= width) {
        rg_cout << "ERROR! Width matrix loss then 'x' in get(x,y)\n";
        rg_cout << "Width = " << width << " x = " << x << std::endl;
        exit(-1);
      }
      if (y >= height) {
        rg_cout << "ERROR! Height matrix loss then 'y' in get(x,y)\n";
        rg_cout << "Height = " << height << " y = " << y << std::endl;
        exit(-1);
      }
      return matrix[y * width + x];
    }
    type& get(Kernel::vec2<size_t> pos) {
      if (pos.x >= width) {
        rg_cout << "ERROR! Width matrix loss then 'pos.x' in get(Kernel::vec2<size_t>pos)\n";
        rg_cout << "Width = " << width << " pos.x = " << pos.x << std::endl;
        exit(-1);
      }
      if (pos.y >= height) {
        rg_cout << "ERROR! Height matrix loss then 'pos.y' in get(Kernel::vec2<size_t>pos)\n";
        rg_cout << "Height = " << height << " pos.y = " << pos.y << std::endl;
        exit(-1);
      }

      return matrix[pos.y * width + pos.x];
    }
    type& operator()(size_t x, size_t y) {
      if (x >= width) {
        rg_cout << "ERROR! Width matrix loss then 'x' in get(x,y)\n";
        rg_cout << "Width = " << width << " x = " << x << std::endl;
        exit(-1);
      }
      if (y >= height) {
        rg_cout << "ERROR! Height matrix loss then 'y' in get(x,y)\n";
        rg_cout << "Height = " << height << " y = " << y << std::endl;
        exit(-1);
      }
      return matrix[y * width + x];
    }
    type& operator()(Kernel::vec2<size_t> pos) {
      if (pos.x >= width) {
        rg_cout << "ERROR! Width matrix loss then 'pos.x' in get(Kernel::vec2<size_t>pos)\n";
        rg_cout << "Width = " << width << " pos.x = " << pos.x << std::endl;
        exit(-1);
      }
      if (pos.y >= height) {
        rg_cout << "ERROR! Height matrix loss then 'pos.y' in get(Kernel::vec2<size_t>pos)\n";
        rg_cout << "Height = " << height << " pos.y = " << pos.y << std::endl;
        exit(-1);
      }

      return matrix[pos.y * width + pos.x];
    }
    void print() {
      for (int i = 0; i < height;i++) {
        for (int j = 0; j < width;j++) {
          rg_cout << get(j, i) << " ";
        }
        rg_cout << std::endl;
      }
      //matrix.print();
    }
    type* get() {
      return matrix.data();
    }
    type* get_mat() {
      return matrix.data();
    }
    ///////
    //empty
    bool empty() {
      return matrix.empty();
    }
    //////
    //size
    size_t size(size_t i) {
      switch (i) {
      case 0: return width;
      case 1: return height;
      default: return matrix.size();
      }

    }
    /*Kernel::vec2<size_t> size(){
      return {size_t(width),size_t(height)};
    }*/
    Kernel::vec2<int> size() {
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
      // }
    }
    ~Matrix() {
      clear();
    }
    ////////////////////////////////////
    //operators
    void operator*=(Matrix<type>& mat) {

      size_t nsizex = width;
      size_t nsizey = mat.size(1);

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      type* mt = s_calloc<type>(nsizex * nsizey);

      for (size_t y = 0; y < nsizey;y++) {
        for (size_t x = 0; x < nsizex;x++) {
          for (size_t k = 0; k < nsizex;k++) {
            mt[x + y * nsizey] += matrix[y * nsizey + k] * mat.get_mat()[x + k * nsizex];
          }
        }

      }
      clear();
      init(nsizex, nsizey, mt);
      free(mt);
    }
    void operator*=(type* mat) {

      //rg_cout<<"div\n";
      size_t nsizex = width;
      size_t nsizey = height;

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      //rg_cout<<"mem\n";
      type* mt = (type*)Kernel::Allocator::GetDefault().allocate(nsizex * nsizey * sizeof(type));
      //rg_cout<<"cycle\n";
      for (size_t y = 0; y < nsizey;y++) {
        for (size_t x = 0; x < nsizex;x++) {
          for (size_t k = 0; k < nsizex;k++) {
            mt[x + y * nsizey] += matrix[y * nsizey + k] * mat[x + k * nsizex];
          }
        }

      }
      //rg_cout<<"end cycle\n";
      clear();
      //rg_cout<<"clear\n";
      init(nsizex, nsizey, mt);
      //rg_cout<<"init\n";
      Kernel::Allocator::GetDefault().deallocate(mt);
      //rg_cout<<"free\n";
    }

    Matrix<type>operator*(Matrix<type> mat) {

      size_t nsizex = width;
      size_t nsizey = mat.size(1);

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      type* mt = s_calloc<type>(nsizex * nsizey);
      for (size_t y = 0; y < nsizey;y++) {
        for (size_t x = 0; x < nsizex;x++) {
          for (size_t k = 0; k < nsizex;k++) {
            mt[x + y * nsizey] += matrix[y * nsizey + k] * mat.get_mat()[x + k * nsizex];
          }
        }

      }

      return Matrix(nsizex, nsizey, mt);
    }

    template<class tttt>
    void place(Kernel::vec2<int> pl, Matrix<tttt>matr) {


      for (int y = pl.y; y < matr.size(1) + pl.y;y++) {
        for (int x = pl.x; x < matr.size(0) + pl.x;x++) {

          type asd = get(x, y);

          asd = matr.get(x - pl.x, y - pl.y);

          get(x, y) = matr.get(x - pl.x, y - pl.y);
        }

      }
    }
  };

  /*
  template<typename type>
  class RG_BetaMatrix{
    Array<type> matrix;
    Array<size_t> sides;//0 = x, 1 = y, 2 = z...
    size_t size;
    //size_t width = 0,height = 0;
  public:
    //init
    void init(size_t countSides){
      sides.resize(countSides);
    }
    void init(size_t countSides, type*arr){
      sides.init(countSides,arr);
    }
     void init(size_t countSides, type*arr, type*mat){
      sides.init(countSides,arr);
      size = 1;
      RG_FOR_CYCLEi(countSides){
        size*=sides[i];
      }
      matrix.fill(size,mat);

    }
    void reInit(size_t countSides, type*arr, type*mat){
      sides.clear();
      matrix.clear();
      init(size_t countSides, type*arr, type*mat);
    }

    Matrix(){}
    Matrix(size_t countSides, type*arr){init(countSides,arr);}
    Matrix(size_t countSides, type*arr, type*mat){init(countSides,arr,mat);}
    ////////
    //resize
    void resize(size_t countSides, type*arr){
      if(countSides>0){
        if(countSides!=sides.size()){
          / *countSides.clear();
          countSides.resize(countSides);/ *
          sides.fill(countSides,arr);
        }else{
          for(int i = 0; i<countSides;i++){
            sides[i]=arr[i];
          }
        }
        size = 1;
        RG_FOR_CYCLEi(countSides){
        size*=sides[i];
        }
        matrix.resize(size);
      }
      else
      {
        if(!sides.empty)sides.clear();
        if(!matrix.empty())clear();
      }
    }
    //////
    //fill
    void fill(size_t countSides, type*arr, type*mat){
      clear();
      sides.fill(countSides,arr);
      size = 1;
      RG_FOR_CYCLEi(countSides){
        size*=sides[i];
      }
      matrix.resize(size);
      matrix.fill(size,mat);
    }
    ////////
    //indexs
    type&operator[](size_t i){
      if(i>0){
        if(i<matrix.size()){
          return matrix[i];
        }
        else {
          rg_cout<<"ERROR! Size matrix loss then 'i' in operator[](size_t i)\n";
          rg_cout<<"Size = "<<matrix.size()<<" | i = "<<i<<endl;
          exit(-1);}
      }
      else{
        if(matrix.size()+i<matrix.size()){
          return matrix[matrix.size()+i];
        }
        else{
          rg_cout<<"ERROR! Size matrix loss then 'size + i' in operator[](size_t i)\n";
          rg_cout<<"Size = "<<matrix.size()<<" i = "<<i<<endl;
          exit(-1);
        }
      }

    }
    type&get(size_t x,size_t y){
      return matrix[y*width+x];
    }
    type*get(){
      return matrix.data();
    }
    ///////
    //empty
    bool empty(){
      return matrix.empty();
    }
    //////
    //size
    size_t size(size_t i){
      switch(i){
        case 0: return width;
        case 1: return height;
        default: return matrix.size();
      }

    }
    ///////
    //clear
    void clear(){
      if(!sides.empty()){
        sides.clear();
      }
      if(!matrix.empty()){
        matrix.clear();
      }
    }
    ~Matrix(){
      clear();
    }
    ////////////////////////////////////
    //operators
    void operator*=(Matrix<type>& mat){

      size_t nsizex = width;
      size_t nsizey = mat.getSize(1);

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      type* mt = s_calloc<type>(nsizex*nsizey);
        for(size_t y = 0; y<nsizey;y++)
        {
          for(size_t x = 0; x<nsizex ;x++)
          {
            for(size_t k = 0; k<nsizex;k++)
            {
              mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat.get_mat()[x+k*nsizex];
            }
          }

        }
        clear();
        init(nsizex,nsizey,mt);
        free(mt);
    }
    void operator*=(type* mat){

      //rg_cout<<"div\n";
      size_t nsizex = width;
      size_t nsizey = height;

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      //rg_cout<<"mem\n";
      type* mt = s_calloc<type>(nsizex*nsizey);
      //rg_cout<<"cycle\n";
        for(size_t y = 0; y<nsizey;y++)
        {
          for(size_t x = 0; x<nsizex ;x++)
          {
            for(size_t k = 0; k<nsizex;k++)
            {
              mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat[x+k*nsizex];
            }
          }

        }
      //rg_cout<<"end cycle\n";
        clear();
      //rg_cout<<"clear\n";
        init(nsizex,nsizey,mt);
      //rg_cout<<"init\n";
        free(mt);
      //rg_cout<<"free\n";
    }

    Matrix<type>operator*(Matrix<type> mat){

      size_t nsizex = width;
      size_t nsizey = mat.getSize(1);

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      type* mt = s_calloc<type>(nsizex*nsizey);
        for(size_t y = 0; y<nsizey;y++)
        {
          for(size_t x = 0; x<nsizex ;x++)
          {
            for(size_t k = 0; k<nsizex;k++)
            {
              mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat.get_mat()[x+k*nsizex];
            }
          }

        }

      return Matrix(nsizex,nsizey,mt);
    }
  };*/




  template<typename type>
  class RG_3DMatrix {
    Array<type> matrix;
    size_t width = 0, height = 0, length = 0;
  public:
    //init
    void init(size_t x, size_t y, size_t z) {
      resize(x, y, z);
    }
    void init(Kernel::vec3<size_t>size) {
      resize(size);
    }
    void init(size_t x, size_t y, size_t z, type* arr) {
      fill(x, y, z, arr);
    }
    void init(Kernel::vec3<size_t>size, type* arr) {
      fill(size, arr);
    }
    void init(size_t x, size_t y, size_t z, type arr) {
      fill(x, y, z, arr);
    }
    void init(Kernel::vec3<size_t>size, type arr) {
      fill(size, arr);
    }
    void reInit(size_t x, size_t y, size_t z, type* mat) {
      if (x != width || y != height || z != length) {
        clear();
        resize(x, y, z);
      }
      matrix.fill(x * y * z, mat);
    }

    RG_3DMatrix() {}
    RG_3DMatrix(size_t x, size_t y, size_t z) { init(x, y, z); }
    RG_3DMatrix(size_t x, size_t y, size_t z, type* arr) { init(x, y, z, arr); }
    ////////
    //resize
    void resize(size_t x, size_t y, size_t z) {
      if (x * y * z != 0) {
        matrix.resize(x * y * z);
        width = x;
        height = y;
        length = z;
      }
      else {
        if (matrix.empty()) return;
        clear();
      }
    }
    void resize(Kernel::vec3<size_t>size) {
      if (size.x * size.y * size.z != 0) {
        matrix.resize(size.x * size.y * size.z);
        width = size.x;
        height = size.y;
        length = size.z;
      }
      else {
        if (matrix.empty()) return;
        clear();
      }
    }
    //////
    //fill
    void fill(size_t x, size_t y, size_t z, type* mat) {
      clear();
      resize(x, y, z);
      for (int yy = 0; yy < y;yy++) {
        for (int xx = 0; xx < x;xx++) {
          for (int zz = 0; zz < z; zz++) {
            matrix[zz * y + yy * x + xx] = mat[zz * y + yy * x + xx];

          }
        }
      }
    }
    void fill(Kernel::vec3<size_t>size, type* mat) {
      clear();
      resize(size.x, size.y, size.z);
      for (int yy = 0; yy < size.y;yy++) {
        for (int xx = 0; xx < size.x;xx++) {
          for (int zz = 0; zz < size.z; zz++) {
            matrix[zz * size.y + yy * size.x + xx] = mat[zz * size.y + yy * size.x + xx];

          }
        }
      }
    }

    void fill(size_t x, size_t y, size_t z, type a) {
      clear();
      resize(x, y, z);
      for (int yy = 0; yy < y;yy++) {
        for (int xx = 0; xx < x;xx++) {
          for (int zz = 0; zz < z; zz++) {
            matrix[zz * y + yy * x + xx] = a;

          }
        }
      }
    }
    void fill(Kernel::vec3<size_t>size, type a) {
      clear();
      resize(size.x, size.y, size.z);
      for (int yy = 0; yy < size.y;yy++) {
        for (int xx = 0; xx < size.x;xx++) {
          for (int zz = 0; zz < size.z; zz++) {
            matrix[zz * size.y + yy * size.x + xx] = a;

          }
        }
      }
    }
    ////////
    //indexs
    type& operator[](size_t i) {
      if (i >= 0) {
        if (i < matrix.size()) {
          return matrix[i];
        }
        else {
          rg_cout << "ERROR! Size 3D matrix loss then 'i' in operator[](size_t i)\n";
          rg_cout << "Size = " << matrix.size() << " | i = " << i << std::endl;
          exit(-1);
        }
      }
      else {
        if (matrix.size() + i < matrix.size()) {
          return matrix[matrix.size() + i];
        }
        else {
          rg_cout << "ERROR! Size 3D matrix loss then 'size + i' in operator[](size_t i)\n";
          rg_cout << "Size = " << matrix.size() << " i = " << i << std::endl;
          exit(-1);
        }
      }

    }
    type& get(size_t x, size_t y, size_t z) {
      if (x >= width) {
        rg_cout << "ERROR! Width matrix loss then 'x' in get(x,y,z)\n";
        rg_cout << "Width = " << width << " x = " << x << std::endl;
        exit(-1);
      }
      if (y >= height) {
        rg_cout << "ERROR! Height matrix loss then 'y' in get(x,y,z)\n";
        rg_cout << "Height = " << height << " y = " << y << std::endl;
        exit(-1);
      }
      if (z >= length) {
        rg_cout << "ERROR! Length matrix loss then 'z' in get(x,y,z)\n";
        rg_cout << "Length = " << length << " z = " << x << std::endl;
        exit(-1);
      }
      return matrix[z * height * width + y * width + x];
    }
    type& get(Kernel::vec3<size_t>pos) {
      if (pos.x >= width) {
        rg_cout << "ERROR! Width matrix loss then 'pos.x' in get(Kernel::vec3<size_t> pos)\n";
        rg_cout << "Width = " << width << " pos.x = " << pos.x << std::endl;
        exit(-1);
      }
      if (pos.y >= height) {
        rg_cout << "ERROR! Height matrix loss then 'pos.y' in get(Kernel::vec3<size_t> pos)\n";
        rg_cout << "Height = " << height << " pos.y = " << pos.y << std::endl;
        exit(-1);
      }
      if (pos.z >= length) {
        rg_cout << "ERROR! Length matrix loss then 'pos.z' in get(Kernel::vec3<size_t> pos)\n";
        rg_cout << "Length = " << length << " pos.z = " << pos.x << std::endl;
        exit(-1);
      }
      return matrix[pos.z * height * width + pos.y * width + pos.x];
    }
    type* get() {
      return matrix.data();
    }
    type* get_mat() {
      return matrix.data();
    }
    ///////
    //empty
    bool empty() {
      return matrix.empty();
    }
    //////
    //size
    size_t size(size_t i) {
      switch (i) {
      case 0: return width;
      case 1: return height;
      case 2: return length;
      default: return matrix.size();
      }

    }
    ///////
    //clear
    void clear() {
      if (!matrix.empty()) {
        matrix.clear();
        width = 0;
        height = 0;
        length = 0;
      }
    }
    ~RG_3DMatrix() {
      clear();
    }
    ////////////////////////////////////
    //operators
    /*void operator*=(RG_3DMatrix<type>& mat){

      size_t nsizex = width;
      size_t nsizey = mat.getSize(1);

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      type* mt = s_calloc<type>(nsizex*nsizey);
        for(size_t y = 0; y<nsizey;y++)
        {
          for(size_t x = 0; x<nsizex ;x++)
          {
            for(size_t k = 0; k<nsizex;k++)
            {
              mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat.get_mat()[x+k*nsizex];
            }
          }

        }
        clear();
        init(nsizex,nsizey,mt);
        free(mt);
    }*/
    /*void operator*=(type* mat){

      //rg_cout<<"div\n";
      size_t nsizex = width;
      size_t nsizey = height;

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      //rg_cout<<"mem\n";
      type* mt = s_calloc<type>(nsizex*nsizey);
      //rg_cout<<"cycle\n";
        for(size_t y = 0; y<nsizey;y++)
        {
          for(size_t x = 0; x<nsizex ;x++)
          {
            for(size_t k = 0; k<nsizex;k++)
            {
              mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat[x+k*nsizex];
            }
          }

        }
      //rg_cout<<"end cycle\n";
        clear();
      //rg_cout<<"clear\n";
        init(nsizex,nsizey,mt);
      //rg_cout<<"init\n";
        free(mt);
      //rg_cout<<"free\n";
    }*/

    /*RG_3DMatrix<type>operator*(RG_3DMatrix<type> mat){

      size_t nsizex = width;
      size_t nsizey = mat.getSize(1);

      //type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
      type* mt = s_calloc<type>(nsizex*nsizey);
        for(size_t y = 0; y<nsizey;y++)
        {
          for(size_t x = 0; x<nsizex ;x++)
          {
            for(size_t k = 0; k<nsizex;k++)
            {
              mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat.get_mat()[x+k*nsizex];
            }
          }

        }

      return RG_3DMatrix(nsizex,nsizey,mt);
    }*/
  };






  template<class type, class type2>
  type SpecialMatMulti(Matrix<type>& mat1, Matrix<type2>& mat2, int pos1, int pos2) {
    type out = 0;
    for (int i = 0; i < mat1.size(0);i++) {
      out += mat1.get(i, pos1) * mat2.get(pos2, i);
    }
    return out;
  }

  //Удалить
  template<class type, class type2>
  bool CountMatMinus(Matrix<type>& mat1, Matrix<type2>& mat2, int pos1, int pos2) {
    bool out = false;
    for (int i = 0; i < mat1.size(0);i++) {
      if (mat1.get(i, pos1) < 0)out = !out;
      if (mat2.get(pos2, i) < 0)out = !out;
    }
    return out;
  }
  /*type SpecialMatMulti(Matrix<type>&mat1,Matrix<type2>&mat2,int pos1){
    type out = 0;
    for(int i = 0; i<mat1.size(0);i++){
      out+=mat1.get(i,pos1)*mat2.get(i,pos2);
    }
    return out;
  }*/
}