#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/high/phys"

namespace RG {
  namespace Physics {
    struct Environment {
      double density = 1.2255; // Плотность воздуха (\( \rho \)) в кг/м³
      double Attraction = 9.8; // Ускорение свободного падения (\( g \)) в м/с²
      vec3<double> windVel = { 0,0,0 };    // Скорость ветра векторами (м/с)
    };

    struct Object {
      Graphic::Flat::Lock::Mesh* mesh;
      vec3<double> acceleration; // Ускорение объекта
      vec3<double> velocity;     // Скорость объекта
      vec3<double> impuls;       // Импульс объекта
      vec2<vec3<double>> friction; // Сопротивление трения
      vec3<double> sideArea = { 1,1,1 };     // Площади сторон объекта
      double weight = 1;         // Вес объекта
      double mass = 1;           // Масса объекта
      double ResCoef = 0.47;     // Коэффициент сопротивления (\( C_d \))
      double ResFactor = 0.5;    // DragFactor
      double area = 1;           // Площадь поперечного сечения (м²)
      bool useGlobalPhysicsFunction = true;
      void(*update)(Environment&, Object&) = nullptr;
    };

    class Engine {
      RG_Array<Object> phys; // Список объектов
      Environment env;       // Среда
      uint _size = 0;
    public:
      void init(Environment in) {
        env = in;
      }

      Engine() {}
      Engine(Environment in) : env(in) {}

      int push_back(Object in) {
        if (_size == phys.size()) {
          phys.push_back(in);
          calculateDragFactor(in);
        } else {
          phys[_size] = std::move(in);
        }
        return _size++;
      }
      void pop() {
        // rg_cout << "pop, size==" << _size << endl;
        _size--;
      }
      Object& operator[](int i) {
        return phys[i];
      }

      int size() {
        return _size;
      }

      /*double calculateDragFactor(double density, double dragCoeff, double area) {
        // Коэффициент сопротивления воздуха
        return -0.5 * density * dragCoeff * area;
      }*/
      void calculateDragFactor(Object& in) {
        // Коэффициент сопротивления воздуха
        in.ResFactor = -0.5 * env.density * in.ResCoef * in.area;
      }

      // Вычисление площадей сторон объекта
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
        obj.sideArea.x = (max.y - min.y) * (max.z - min.z); // yz плоскость
        obj.sideArea.y = (max.x - min.x) * (max.z - min.z); // xz плоскость
        obj.sideArea.z = (max.x - min.x) * (max.y - min.y); // xy плоскость
      }

      // Основной метод обновления
      /*void update() {
        for (int i = 0; i < phys.size(); i++) {
          if (phys[i].mass == 0) continue;

          Object& obj = phys[i];


          // Рассчитать результирующую скорость с учётом ветра
          vec3<double> relVelocity = obj.velocity - env.windVel;

          // Обновить ускорение (гравитация)
          obj.acceleration = { 0, 0, 0 };
          //obj.acceleration = { 0, -env.Attraction, 0 };

          // Добавить сопротивление воздуха
          obj.acceleration.x += -(obj.ResFactor * env.density *obj.ResCoef * obj.sideArea.x * relVelocity.x * fabs(relVelocity.x)) / obj.mass;
          obj.acceleration.y += -(obj.ResFactor * env.density *obj.ResCoef * obj.sideArea.y * relVelocity.y * fabs(relVelocity.y)) / obj.mass;
          obj.acceleration.z += -(obj.ResFactor * env.density *obj.ResCoef * obj.sideArea.z * relVelocity.z * fabs(relVelocity.z)) / obj.mass;

          // Обновить скорость
          obj.velocity += obj.acceleration * RG_Timer_StandartPtr->getBias();

          // Обновить позицию меша
          obj.mesh->pos.x += obj.velocity.x * RG_Timer_StandartPtr->getBias();
          obj.mesh->pos.y += obj.velocity.y * RG_Timer_StandartPtr->getBias();
          obj.mesh->pos.z += obj.velocity.z * RG_Timer_StandartPtr->getBias();

          // Обновить матрицу трансформации меша
          obj.mesh->MatUpdate();
        }
      }*/

      void update() {
        for (int i = 0; i < phys.size(); i++) {
          Object& obj = phys[i];
          if (obj.useGlobalPhysicsFunction) {

            if (obj.mass == 0) continue;


            // Рассчитать результирующую скорость с учётом ветра
            vec3<double> relVelocity = obj.velocity - env.windVel;

            // Вычисление сопротивления воздуха для каждой оси
            double dragForceX = -(obj.ResFactor * env.density * obj.ResCoef * obj.sideArea.x * relVelocity.x * fabs(relVelocity.x)) / obj.mass;
            double dragForceY = -(obj.ResFactor * env.density * obj.ResCoef * obj.sideArea.y * relVelocity.y * fabs(relVelocity.y)) / obj.mass;
            double dragForceZ = -(obj.ResFactor * env.density * obj.ResCoef * obj.sideArea.z * relVelocity.z * fabs(relVelocity.z)) / obj.mass;

            // Вычисление ускорения
            obj.acceleration = { dragForceX, -env.Attraction + dragForceY, dragForceZ };

            // Обновить скорость с учетом ускорения
            obj.velocity += obj.acceleration * RG_Timer_StandartPtr->getBias();

          }
          if(obj.update!=nullptr)
            obj.update(env, obj);
          // Обновить позицию меша 
          obj.mesh->pos.x += obj.velocity.x * RG_Timer_StandartPtr->getBias();
          obj.mesh->pos.y += obj.velocity.y * RG_Timer_StandartPtr->getBias();
          obj.mesh->pos.z += obj.velocity.z * RG_Timer_StandartPtr->getBias();

          // Обновить матрицу трансформации меша
          obj.mesh->MatUpdate();
        }
      }
    };
  }
}
