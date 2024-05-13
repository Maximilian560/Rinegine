#pragma once



//int* bytes = (int*)calloc(1024, sizeof(int));
enum RGE{
  RGE01,
  RGE0_1,
  RGE10,
  RGE_10
};
POINT2D<int> RG_Gradient[4] = {{0,1},{0,-1},{1,0},{-1,0}};

class RG_GradientNoise{
  RG_Matrix<double> noise;
  RG_Matrix<int> GradientNoise;
  RG_Matrix<POINT2D<double>>b;
  RG_Matrix<POINT2D<double>>a;
  /////функция интерполяции грани a = значение 1 угола, b значение другого угола, t = локальная позиция
  double Lerp(double a, double b, double t){
    return a * (t - 1) + b * t;
  }

  ////Ещё одна интерполяция
  double QunticCurve(double t){
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  //скалярное произведение векторов
  template<class t,class t2>
  float Dot(POINT2D<t> a, POINT2D<t2> b)
  {
      return a.x * b.x + a.y * b.y;
  }
  
  RGE GetPseudoRandomGradientVector(int x, int y)
    {
        //int v = rand();
        //int v = noise.get(x,y) & 3;
        int v = GradientNoise.get(x,y);
        return RGE(v);
    }
public:
  void pre_init(double size,double maxCountNoise = 1){
    noise.init(size,size);
    noise.randomFill(maxCountNoise);
    GradientNoise.init(size,size);
    GradientNoise.randomFill(4);
  }

  double get_noise(double x, double y,double size ){

    //POINT2D<double> globalCoord = {x/noise.size(0),y/noise.size(1)};
    POINT2D<double> globalCoord = {x/size,y/size};
    //cout<<"GlobalPos "<<globalCoord.x<<" "<<globalCoord.y<<endl;
    POINT2D<int> pointCoord =  {(int)floor(globalCoord.x),(int)floor(globalCoord.y)};
    //cout<<"PointCoord "<<pointCoord.x<<" "<<pointCoord.y<<endl;
    POINT2D<double> localCoord = {globalCoord.x-pointCoord.x,globalCoord.y-pointCoord.y};
    //cout<<"LocalPos "<<localCoord.x<<" "<<localCoord.y<<endl;
    
    RG_Matrix<RGE>LocGradient(2,2);
    LocGradient.get(0,0) = GetPseudoRandomGradientVector(globalCoord.x,globalCoord.y);
    LocGradient.get(1,0) = GetPseudoRandomGradientVector(globalCoord.x + 1,globalCoord.y);
    LocGradient.get(0,1) = GetPseudoRandomGradientVector(globalCoord.x,globalCoord.y + 1);
    LocGradient.get(1,1) = GetPseudoRandomGradientVector(globalCoord.x + 1,globalCoord.y + 1);

    RG_Matrix<POINT2D<double>>DistantToLocalPos(2,2);
    DistantToLocalPos.get(0,0) = {localCoord.x, localCoord.y};
    DistantToLocalPos.get(1,0) = {localCoord.x-1, localCoord.y};
    DistantToLocalPos.get(0,1) = {localCoord.x, localCoord.y-1};
    DistantToLocalPos.get(1,1) = {localCoord.x-1, localCoord.y-1};
    
    RG_Matrix<double>ScalarPoint(2,2);
    ScalarPoint.get(0,0) =  Dot(DistantToLocalPos.get(0,0),RG_Gradient[LocGradient.get(0,0)]);
    ScalarPoint.get(1,0) =  Dot(DistantToLocalPos.get(1,0),RG_Gradient[LocGradient.get(1,0)]);
    ScalarPoint.get(0,1) =  Dot(DistantToLocalPos.get(0,1),RG_Gradient[LocGradient.get(0,1)]);
    ScalarPoint.get(1,1) =  Dot(DistantToLocalPos.get(1,1),RG_Gradient[LocGradient.get(1,1)]);
    localCoord = {QunticCurve(localCoord.x),QunticCurve(localCoord.y)};

    POINT2D<double> SoftEdges = {Lerp(ScalarPoint.get(0,0), ScalarPoint.get(1,0), localCoord.x),Lerp(ScalarPoint.get(0,1), ScalarPoint.get(1,1), localCoord.x)};
    double temp = Lerp(SoftEdges.x, SoftEdges.y, localCoord.y);
    //cout<<"exit "<<temp<<endl;
    //exit(-2);
    return temp;

    /*b.init(2,2);  
    a.init(2,2);
    b.get(0,0) = {x,y};
    b.get(0,1) = {x,y-noise.size(1)};
    b.get(1,0) = {x-noise.size(0),y};
    b.get(1,1) = {x-noise.size(0),y-noise.size(1)};
    double fx = x/size;
    double fy = y/size;

    double pointInQuadX = fx - (int)floor(fx);
    double pointInQuadY = fy - (int)floor(fy);

    a.get(0,0) = {pointInQuadX,pointInQuadX};
    a.get(1,0) = {pointInQuadX - 1, pointInQuadX};
    a.get(0,1) = {pointInQuadX,pointInQuadX - 1};
    a.get(1,1) = {pointInQuadX - 1,pointInQuadX - 1};
    double fx = x / size;
    double fy = y / size;

    int left = (int)floor(fx);
    int top = (int)floor(fy);
    double pointInQuadX = fx - left;
    double pointInQuadY = fy - top;*/

  }
};


template<class type>
void RG_MovePixelsMatrix(RG_Matrix<type>& mat,double porog = 0.5){//name todo
double temp = false;
double tempPixel = 0;
  for(int y = 0; y<mat.size(1);y++){
    for(int x = 0; x<mat.size(0);x++){
      temp = rand()/(double)RAND_MAX;
      
      if(temp>porog)
        if(x!=mat.size(0)-1){
          tempPixel = mat.get(x+1,y);
          mat.get(x+1,y) = mat.get(x,y);
          mat.get(x,y) = tempPixel;
          continue;
        }
      if(temp>porog+porog/4.*1)
        if(y!=mat.size(1)-1){
          tempPixel = mat.get(x,y+1);
          mat.get(x,y+1) = mat.get(x,y);
          mat.get(x,y) = tempPixel;
          continue;
        }
      if(temp>porog+porog/4.*2)
        if(x!=0){
          tempPixel = mat.get(x-1,y);
          mat.get(x-1,y) = mat.get(x,y);
          mat.get(x,y) = tempPixel;
          continue;
        }
      if(temp>porog+porog/4.*3)
        if(y!=0){
          tempPixel = mat.get(x,y-1);
          mat.get(x,y-1) = mat.get(x,y);
          mat.get(x,y) = tempPixel;
          continue;
        }
    }
  }
}

class RG_WorldNoise{
  RG_Matrix<double>worldMap;
  RG_Matrix<double>temperMap;
public:
RG_Matrix<double>&get_worldMap(){
  return worldMap;
}
  void init(){
    //WorldMap
    worldMap.init(4,4);
    worldMap.randomFill(10);
    worldMap.smoothScale(2);
    RG_MovePixelsMatrix(worldMap,0.6);
    worldMap.smoothScale(2);
    worldMap.randomAddFill(10);
    RG_MovePixelsMatrix(worldMap,0.6);
    worldMap.smoothScale(2);
    worldMap.smoothScale(2);
    worldMap.randomAddFill(10);
    RG_MovePixelsMatrix(worldMap,0.7);
    worldMap.smoothScale(2);
    worldMap.smoothScale(2);
    worldMap.smoothScale(2);
    //RG_MovePixelsMatrix(worldMap,0.5);
    //worldMap.smoothScale(2);
    //worldMap.smoothScale(2);
    //RG_MovePixelsMatrix(worldMap,0.7);
    //worldMap.smoothScale(2);
    //worldMap.smoothScale(2);
    ////////////////
    //TemperatureMap
    /*temperMap.init(worldMap.size(0),worldMap.size(1));
    temperMap.randomFill(2);
    for(int y = 0; y<temperMap.size(1);y++){
      for(int x = 0; x<temperMap.size(0);x++){ 
        temperMap.get(x,y)+(((-y*y+temperMap.size(1)*y)/temperMap.size(1)*temperMap.size(1)/4)-0.5);
      } 
    }*/

  }
};