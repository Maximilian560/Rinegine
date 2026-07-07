#pragma once

namespace RG {
  namespace Physics {
    struct Environment {
      double density = 1.2255;//Fc=m*g-m*a;
      double Attraction = 9.8;
      vec3<double>windVel;
    };
    struct Object {
      Graphic::Flat::Lock::Mesh* mesh;
      double weight = 1;
      double mass = 1;
      //vec3<double>windage = {1,1,1};
      vec3<double>acceleration;
      vec3<double>velocity;
      vec3<double>impuls;
      vec2<vec3<double>>friction;//;
      double ResCoef = 0.47;
      double area = 1;
      vec3<double>sideArea;
    };
    class Engine {



      RG_Array<Object> phys;
      Environment env;
    public:
      void init(Environment in) {
        env = in;
      }
      Engine() {}
      Engine(Environment in) :env(in) {}

      int push_back(Object in) {
        phys.push_back(in);
        return phys.size() - 1;
      }
      Object& operator[](int i) {
        return phys[i];
      }

      /*void update() {
        for (int i = 0; i < phys.size(); i++) {
          phys[i].acceleration = { 0, -env.Attraction, 0 };
          if(phys[i].mass==0)continue;
          double velocityMagnitude = sqrt(phys[i].velocity.x * phys[i].velocity.x +
            phys[i].velocity.y * phys[i].velocity.y +
            phys[i].velocity.z * phys[i].velocity.z);
          double airResistance = 0.5 * phys[i].ResCoef * env.density * phys[i].area * velocityMagnitude * velocityMagnitude;
          vec3<double> resistanceForce = phys[i].velocity * (-airResistance / phys[i].mass);

          phys[i].acceleration += resistanceForce;

          phys[i].velocity += (phys[i].acceleration) * RG_Timer_Standart.getBias();
          for(int j = 0;j<phys.size();j++){
            if(i==j)continue;
            if(phys[i].mesh->Collide(*phys[j].mesh))phys[i].velocity={0,4,0};
          }
          phys[i].mesh->pos.x += phys[i].velocity.x * RG_Timer_Standart.getBias();
          phys[i].mesh->pos.y += phys[i].velocity.y * RG_Timer_Standart.getBias();
          phys[i].mesh->MatUpdate();
        }
      }*/
      int size() {
        return phys.size();
      }
      void calculateSideAreas(Object& obj) {
        vec3<double> min = { INFINITY, INFINITY, INFINITY };
        vec3<double> max = { -INFINITY, -INFINITY, -INFINITY };

        // Найти границы меша
        for (const auto& vertex : obj.mesh->truePolygon) {
          min.x = rg_min(min.x, vertex.x);
          max.x = rg_max(max.x, vertex.x);
          min.y = rg_min(min.y, vertex.y);
          max.y = rg_max(max.y, vertex.y);
          min.z = rg_min(min.z, vertex.z);
          max.z = rg_max(max.z, vertex.z);
        }

        // Рассчитать поперечные площади
        obj.sideArea.x = (max.y - min.y) * (max.z - min.z); // Плоскость yz
        obj.sideArea.y = (max.x - min.x) * (max.z - min.z); // Плоскость xz
        obj.sideArea.z = (max.x - min.x) * (max.y - min.y); // Плоскость xy
      }

      void update() {
        for (int i = 0; i < phys.size(); i++) {
          if (phys[i].mass == 0)continue;
          auto& obj = phys[i];
          double airDensity = 1.225; // Плотность воздуха
          double dragCoeff = 1.05;  // Коэффициент сопротивления
          double sideAreaX = obj.sideArea.x; // Поперечная площадь

          // Гравитационное ускорение
          obj.acceleration = { 0, -env.Attraction, 0 };

          // Добавить сопротивление воздуха
          double speedX = obj.velocity.x;
          double dragForceX = -0.5 * env.density * dragCoeff * sideAreaX * speedX * fabs(speedX);
          obj.acceleration.x += dragForceX / obj.mass;

          // Обновить скорость
          obj.velocity += obj.acceleration * RG_Timer_Standart.getBias();

          // Обновить позицию меша
          obj.mesh->pos.x += obj.velocity.x * RG_Timer_Standart.getBias();
          obj.mesh->pos.y += obj.velocity.y * RG_Timer_Standart.getBias();
          obj.mesh->pos.z += obj.velocity.z * RG_Timer_Standart.getBias();

          obj.mesh->MatUpdate();
        }
      }


      /*void update(){
        for(int i = 0;i<phys.size();i++){
          phys[i].acceleration ={0,-Attraction,0};
          phys[i].velocity += phys[i].acceleration*RG_Timer_Standart.getBias();
          phys[i].mesh->pos.x+=phys[i].velocity.x*RG_Timer_Standart.getBias();
          phys[i].mesh->pos.y+=phys[i].velocity.y*RG_Timer_Standart.getBias();
          phys[i].mesh->MatUpdate();
        }
      }*/
    };
  }

}