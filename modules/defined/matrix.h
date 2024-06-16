#pragma once
#ifdef RG_NO_USELESS_WARNING
bool RG_EXCEED_LIMIN_MATRIX = 1;
#else
bool RG_EXCEED_LIMIN_MATRIX = 0;
#endif


template<typename type>
class RG_Matrix{
  RG_Array<type> matrix;
  uint width = 0,height = 0;
public:
  //init
  void init(initializer_list<initializer_list<type>> arr){
    fill(arr);
  }
  void init(uint x,uint y){
    resize(x,y);
  }
  void init(uint x,uint y, type*arr){
    fill(x,y,arr);
  }
  void init(uint x,uint y, type arr){
    fill(x,y,arr);
  }
  void reInit(uint x, uint y,type*mat){
		fill(x,y,mat);
  }
  void init(RG_Matrix<type>&ar){fill(ar);}

  RG_Matrix(){}
  RG_Matrix(RG_Matrix<type> &ar){init(ar);}
  RG_Matrix(initializer_list<initializer_list<type>> arr){init(arr);}
  RG_Matrix(uint x,uint y){init(x,y);}
  RG_Matrix(uint x,uint y,type*arr){init(x,y,arr);}
  RG_Matrix(uint x,uint y,type arr){init(x,y,arr);}

  void resize(uint x, uint y){
    if(y*x>0){
      matrix.resize(y*x);
      height = y;
      width = x;
    }else{
      clear();
    }
  }
  void resize(POINT2D<uint>ns){
    if(ns.y*ns.x>0){
      matrix.resize(ns.y*ns.x);
      height = ns.y;
      width = ns.x;
    }else{
      clear();
    }
  }
  //////
  //fill
  void fill(RG_Matrix<type>&ar){
    clear();
    //cout<<ar.size(0)<<" "<<ar.size(1)<<" "<<ar.size(2)<<endl;
    //matrix.resize(ar.size(2));
    resize(ar.size());
    for(int y = 0; y<ar.size(1);y++){
      for(int x = 0;x<ar.size(0);x++){
        get(x,y)=ar[y][x];
      }
    }
  }
  void fill(uint x,uint y, type*mat){
    clear();
    resize(x,y);
    for(int yy = 0; yy<y;yy++){
      for(int xx = 0; xx<x;xx++){
        matrix[yy*x+xx] = mat[yy*x+xx];
      }
    }
  }
  void fill(initializer_list<initializer_list<type>> arr){
    resize(arr.begin()->size(),arr.size());
    //cout<<width<<"||"<<height<<endl;
    for(int y = 0; y<height;y++){
      for(int x = 0; x<width;x++){
        getyx(y,x) = arr.begin()[y].begin()[x];
      }
    }
  }
  void movefill(uint x, uint y, type*mat){
    clear();
    width = x;
    height = y;
    matrix.movefill(x*y,mat);
  }
  

  void fill(type mat){
    matrix.fill(mat);
  }
  void fill(uint y,uint x, type mat){
    clear();
    matrix.fillfull(x*y,mat);
  }

  void randomBoolFill(double porog,double max = 1){
    for(int y = 0; y<height;y++){
      for(int x = 0; x<width;x++){
        matrix[y*width+x] = ((rand()/(RAND_MAX/max)>porog)?1:0);
      }
    }
  }
  void randomBoolAddFill(double porog,double max = 1){
    for(int y = 0; y<height;y++){
      for(int x = 0; x<width;x++){
        if(matrix[y*width+x]!=1)matrix[y*width+x] = ((rand()/(RAND_MAX/max)>porog)?1:0);
      }
    }
  }

  void randomAddFill(double porog,double max = 1){
    for(int y = 0; y<height;y++){
      for(int x = 0; x<width;x++){
        if(matrix[y*width+x]!=1)matrix[y*width+x] = rand()/(RAND_MAX/max);
      }
    }
  }

  void randomFill(double max = 1){
    for(int y = 0; y<height;y++){
      for(int x = 0; x<width;x++){
        matrix[y*width+x] = rand()/(RAND_MAX/max);
      }
    }
  }


  void scale(uint a){
    RG_Matrix<type>mat2;
    mat2.init(width*a,height*a);
    for(int y = 0;y<height*a;y++){
      for(int x = 0; x<width*a;x++){
        mat2.get(x,y) = matrix[(y/a)*width+(x/a)];
      }
    }
    reInit(mat2.size(0),mat2.size(1),mat2.get_mat());
    mat2.clear();
  }
  void smoothScale(int a){
    RG_Matrix<type>mat2;
    mat2.init(width*a,height*a);
    for(int y = 0;y<height*a;y+=a){
      for(int x = 0; x<width*a;x+=a){
        mat2.get(x,y) = matrix[(y/a)*width+(x/a)];
      }
     }

    for(int g = 1; g<a;g++){
      for(int y = g;y<height*a;y+=a){
        for(int x = g; x<width*a;x+=a){
          //cout<<x<<" "<<y<<" "<<g<<endl;
          //cout<<((x-g)/a)<<" "<<((y-g)/a)<<" "<<g<<endl<<endl;

          if(((x-g)/a)-g>=0){
            mat2.get(x,y) += matrix[(((y-g)/a)+0)*width+(((x-g)/a)-g)]/(g+1.);
          }
          if(((y-g)/a)-g>=0){
            mat2.get(x,y) += matrix[(((y-g)/a)-g)*width+(((x-g)/a)-0)]/(g+1.);
          }
          if(((x-g)/a)+g<width/a){
            mat2.get(x,y) += matrix[(((y-g)/a)+0)*width+(((x-g)/a)+g)]/(g+1.);
          }
          if(((y-g)/a)+g<height/a){
            mat2.get(x,y) += matrix[(((y-g)/a)+g)*width+(((x-g)/a)-0)]/(g+1.);
          }
        }
      }
    }
    

    reInit(mat2.size(0),mat2.size(1),mat2.get_mat());
    mat2.clear();

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
  type*operator[](uint i){
    if(i>=height)RG_Debug::addl(RG_LOG_CRITICAL,"matrix height is less than "+to_string(i+1)+"(you set "+to_string(i)+") and equal to "+to_string(height));
    if(!RG_EXCEED_LIMIN_MATRIX){RG_Debug::addl(RG_LOG_WARNING, "When using [y][x] it is possible to exceed the limit, check that x is not larger than the width of the matrix. This warning will no longer appear");RG_EXCEED_LIMIN_MATRIX = 1;}
    return &matrix[i*width];
  }

  
  type&get(uint x,uint y){
    if(y>=height){
      RG_Debug::addl(RG_LOG_CRITICAL,"Matrix height less than or equal to 'y' in 'get(x,y)'\n\
      'Height' = '"+to_string(height)+"', 'y' = '"+to_string(y)+"'");
    }
    if(x>=width){
      RG_Debug::addl(RG_LOG_CRITICAL,"Matrix width less than or equal to 'x' in 'get(x,y)'\n\
      'Width' = '"+to_string(width)+"', 'x' = '"+to_string(x)+"'");
    }
    return matrix[y*width+x];
  }

  type&getyx(uint y, uint x){
    if(y>=height){
      RG_Debug::addl(RG_LOG_CRITICAL,"Matrix height less than or equal to 'y' in 'getyx(y,x)'\n\
      'Height' = '"+to_string(height)+"', 'y' = '"+to_string(y)+"'");
    }
    if(x>=width){
      RG_Debug::addl(RG_LOG_CRITICAL,"Matrix width less than or equal to 'x' in 'getyx(y,x)'\n\
      'Width' = '"+to_string(width)+"', 'x' = '"+to_string(x)+"'");
    }
    return matrix[y*width+x];
  }
  type&get(POINT2D<uint> pos){
    if(pos.x>=width){
      RG_Debug::addl(RG_LOG_CRITICAL,"Matrix width less than or equal to 'pos.x' in 'get(POINT2D<uint>pos)'\n\
      'Width' = '"+to_string(width)+"', 'pos.x' = '"+to_string(pos.x)+"'");
    }
    if(pos.y>=height){
      RG_Debug::addl(RG_LOG_CRITICAL,"Matrix height less than or equal to 'pos.y' in 'get(POINT2D<uint>pos)'\n\
      'Height' = '"+to_string(height)+"', 'pos.y' = '"+to_string(pos.y)+"'");
    }

    return matrix[pos.y*width+pos.x];
  }
  void print(){
    for(int i = 0; i<height;i++){
      for(int j = 0; j<width;j++){
        cout<<getyx(i,j)<<" ";
      }
      cout<<endl;
    }
    //matrix.print();
  }
  

  operator type*(){
    return matrix.get_arr();
  }
  type*get(){
    return matrix.get_arr();
  }
  type*get_mat(){
    return matrix.get_arr();
  }
  ///////
  //empty
  bool empty(){
    return matrix.empty();
  }
  operator bool(){
    return !matrix.empty();
  }
  //////
  //size
  uint size(uint i){
    switch(i){
      case 0: return width;
      case 1: return height;
      default: return matrix.size();
    }
    
  }
  operator uint(){
    return matrix.size();
  }
  /*POINT2D<uint> size(){
    return {uint(width),uint(height)};    
  }*/
  POINT2D<uint> size(){
    return {width,height};    
  }
  ///////
  //clear
  void clear(){
    //if(!matrix.empty()){
      //free(array);
      matrix.clear();
      width = 0;
      height = 0;
   // }
  }
  ~RG_Matrix(){
    clear();
  }
  ////////////////////////////////////
  //operators
  void operator*=(RG_Matrix<type>& mat){

    uint nsizex = width;
		uint nsizey = mat.getSize(1);

		//type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
		type* mt = s_calloc<type>(nsizex*nsizey);
    
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
  }
  void operator*=(initializer_list<initializer_list<type>> mat){
    uint nsizex = width;
		uint nsizey = mat.size();
		type* mt = s_calloc<type>(nsizex*nsizey);
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
  }
  void operator*=(type* mat){

    //cout<<"div\n";
    uint nsizex = width;
		uint nsizey = height;

		//type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //cout<<"mem\n";
		type* mt = s_calloc<type>(nsizex*nsizey);
    //cout<<"cycle\n";
    	for(uint y = 0; y<nsizey;y++)
    	{
    		for(uint x = 0; x<nsizex ;x++)
    		{
    			for(uint k = 0; k<nsizex;k++)
    			{
    				mt[x+y*nsizex]+=matrix[y*nsizex+k] * mat[x+k*nsizex];
    			}
    		}

    	}
    //cout<<"end cycle\n";
    	clear();
    //cout<<"clear\n";
    	//init(nsizex,nsizey,mt);
      movefill(nsizex,nsizey,mt);
    //cout<<"init\n";
    	//free(mt);
    //cout<<"free\n";
  }

  RG_Matrix<type>operator*(RG_Matrix<type> mat){

    uint nsizex = width;
		uint nsizey = mat.getSize(1);

		//type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
		type* mt = s_calloc<type>(nsizex*nsizey);
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
  }

  template<class tttt>
  void place(POINT2D<int> pl,RG_Matrix<tttt>&matr){
    cout<<matr.size(0)<<endl;
    cout<<matr.size(1)<<endl;
    //exit(-2);
    for(int y = pl.y; y<matr.size(1)+pl.y&&y+pl.y<height;y++){
      for(int x = pl.x; x<matr.size(0)+pl.x&&x+pl.x<width;x++){

        //type asd = get(x,y);

        //asd = matr.get(x-pl.x,y-pl.y);

        //get(x,y) = matr.get(x-pl.x,y-pl.y);
        //cout<<y<<" "<<x<<endl;
        get(x,y) = matr[y][x];//.get(x-pl.x,y-pl.y);
      }

    }
  }

  void set_stbi(){
    matrix.set_stbi();
  }
};


template<typename type>
class RG_3DMatrix{
  RG_Array<type> matrix;
  uint width = 0,height = 0,length = 0;
public:
  //init
  void init(uint x,uint y,uint z){
    resize(x,y,z);
  }
  void init(POINT3D<uint>size){
    resize(size);
  }
  void init(uint x,uint y,uint z, type*arr){
    fill(x,y,z,arr);
  }
  void init(POINT3D<uint>size, type*arr){
    fill(size,arr);
  }
  void init(uint x,uint y,uint z, type arr){
    fill(x,y,z,arr);
  }
  void init(POINT3D<uint>size, type arr){
    fill(size,arr);
  }
  void reInit(uint x, uint y,uint z,type*mat){
		if(x!=width||y!=height||z!=length)
    {
      clear();
      resize(x,y,z);
    }
    matrix.fill(x*y*z,mat);
  }
 
  RG_3DMatrix(){}
  RG_3DMatrix(uint x,uint y,uint z){init(x,y,z);}
  RG_3DMatrix(uint x,uint y,uint z,type*arr){init(x,y,z,arr);}
  ////////
  //resize
  void resize(uint x, uint y,uint z){
    if(x*y*z!=0){
      matrix.resize(x*y*z);
      width = x;
      height = y;
      length = z;
    }else{
      if(matrix.empty()) return;
      clear();
    }
  }
  void resize(POINT3D<uint>size){
    if(size.x*size.y*size.z!=0){
      matrix.resize(size.x*size.y*size.z);
      width = size.x;
      height = size.y;
      length = size.z;
    }else{
      if(matrix.empty()) return;
      clear();
    }
  }
  //////
  //fill
  void fill(uint x,uint y,uint z, type*mat){
    clear();
    resize(x,y,z);
    for(int yy = 0; yy<y;yy++){
      for(int xx = 0; xx<x;xx++){
        for(int zz = 0; zz<z; zz++){
          matrix[zz*y+yy*x+xx] = mat[zz*y+yy*x+xx];

        }
      }
    }
  }
  void fill(POINT3D<uint>size, type*mat){
    clear();
    resize(size.x,size.y,size.z);
    for(int yy = 0; yy<size.y;yy++){
      for(int xx = 0; xx<size.x;xx++){
        for(int zz = 0; zz<size.z; zz++){
          matrix[zz*size.y+yy*size.x+xx] = mat[zz*size.y+yy*size.x+xx];

        }
      }
    }
  }

  void fill(uint x,uint y,uint z, type a){
    clear();
    resize(x,y,z);
    for(int yy = 0; yy<y;yy++){
      for(int xx = 0; xx<x;xx++){
        for(int zz = 0; zz<z; zz++){
          matrix[zz*y+yy*x+xx] = a;

        }
      }
    }
  }
  void fill(POINT3D<uint>size, type a){
    clear();
    resize(size.x,size.y,size.z);
    for(int yy = 0; yy<size.y;yy++){
      for(int xx = 0; xx<size.x;xx++){
        for(int zz = 0; zz<size.z; zz++){
          matrix[zz*size.y+yy*size.x+xx] = a;

        }
      }
    }
  }
  ////////
  //indexs
  type&operator[](uint i){
    if(i>=0){
      if(i<matrix.size()){
        return matrix[i];
      }
      else {
        cout<<"ERROR! Size 3D matrix loss then 'i' in operator[](uint i)\n"; 
        cout<<"Size = "<<matrix.size()<<" | i = "<<i<<endl; 
        exit(-1);}
    }
    else{
      if(matrix.size()+i<matrix.size()){
        return matrix[matrix.size()+i];
      }
      else{
        cout<<"ERROR! Size 3D matrix loss then 'size + i' in operator[](uint i)\n";
        cout<<"Size = "<<matrix.size()<<" i = "<<i<<endl;
        exit(-1);
      }
    }
      
  }
  type&get(uint x,uint y,uint z){
    if(x>=width){
      cout<<"ERROR! Width matrix loss then 'x' in get(x,y,z)\n";
      cout<<"Width = "<<width<<" x = "<<x<<endl;
      exit(-1);
    }
    if(y>=height){
      cout<<"ERROR! Height matrix loss then 'y' in get(x,y,z)\n";
      cout<<"Height = "<<height<<" y = "<<y<<endl;
      exit(-1);
    }
    if(z>=length){
      cout<<"ERROR! Length matrix loss then 'z' in get(x,y,z)\n";
      cout<<"Length = "<<length<<" z = "<<x<<endl;
      exit(-1);
    }
    return matrix[z*height*width+y*width+x];
  }
  type&get(POINT3D<uint>pos){
    if(pos.x>=width){
      cout<<"ERROR! Width matrix loss then 'pos.x' in get(POINT3D<uint> pos)\n";
      cout<<"Width = "<<width<<" pos.x = "<<pos.x<<endl;
      exit(-1);
    }
    if(pos.y>=height){
      cout<<"ERROR! Height matrix loss then 'pos.y' in get(POINT3D<uint> pos)\n";
      cout<<"Height = "<<height<<" pos.y = "<<pos.y<<endl;
      exit(-1);
    }
    if(pos.z>=length){
      cout<<"ERROR! Length matrix loss then 'pos.z' in get(POINT3D<uint> pos)\n";
      cout<<"Length = "<<length<<" pos.z = "<<pos.x<<endl;
      exit(-1);
    }
    return matrix[pos.z*height*width+pos.y*width+pos.x];
  }
  type*get(){
    return matrix.get_arr();
  }
   type*get_mat(){
    return matrix.get_arr();
  }
  ///////
  //empty
  bool empty(){
    return matrix.empty();
  }
  //////
  //size
  uint size(uint i){
    switch(i){
      case 0: return width;
      case 1: return height;
      case 2: return length;
      default: return matrix.size();
    }
    
  }
  ///////
  //clear
  void clear(){
    if(!matrix.empty()){
      matrix.clear();
      width = 0;
      height = 0;
      length = 0;
    }
  }
  ~RG_3DMatrix(){
    clear();
  }
  ////////////////////////////////////
  //operators
  /*void operator*=(RG_3DMatrix<type>& mat){

    uint nsizex = width;
		uint nsizey = mat.getSize(1);

		//type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
		type* mt = s_calloc<type>(nsizex*nsizey);
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
    	init(nsizex,nsizey,mt);
    	free(mt);
  }*/
  /*void operator*=(type* mat){

    //cout<<"div\n";
    uint nsizex = width;
		uint nsizey = height;

		//type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
    //cout<<"mem\n";
		type* mt = s_calloc<type>(nsizex*nsizey);
    //cout<<"cycle\n";
    	for(uint y = 0; y<nsizey;y++)
    	{
    		for(uint x = 0; x<nsizex ;x++)
    		{
    			for(uint k = 0; k<nsizex;k++)
    			{
    				mt[x+y*nsizey]+=matrix[y*nsizey+k] * mat[x+k*nsizex];
    			}
    		}

    	}
    //cout<<"end cycle\n";
    	clear();
    //cout<<"clear\n";
    	init(nsizex,nsizey,mt);
    //cout<<"init\n";
    	free(mt);
    //cout<<"free\n";
  }*/

  /*RG_3DMatrix<type>operator*(RG_3DMatrix<type> mat){

    uint nsizex = width;
		uint nsizey = mat.getSize(1);

		//type* mt = (type*)calloc(nsizex*nsizey,sizeof(type));
		type* mt = s_calloc<type>(nsizex*nsizey);
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
    
    return RG_3DMatrix(nsizex,nsizey,mt);
  }*/
};






template<class type,class type2>
type SpecialMatMulti(RG_Matrix<type>&mat1,RG_Matrix<type2>&mat2,int pos1, int pos2){
  type out = 0;
  for(int i = 0; i<mat1.size(0);i++){
    out+=mat1.get(i,pos1)*mat2.get(pos2,i);   
  }
  return out;
}

//Удалить
template<class type,class type2>
bool CountMatMinus(RG_Matrix<type>&mat1,RG_Matrix<type2>&mat2,int pos1, int pos2){
  bool out = false;
  for(int i = 0; i<mat1.size(0);i++){
    if(mat1.get(i,pos1)<0)out = !out;
    if(mat2.get(pos2,i)<0)out = !out;
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