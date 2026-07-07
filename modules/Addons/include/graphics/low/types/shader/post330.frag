R"(
  #version 330 core
  
  // Входные данные
  uniform sampler2D tex_2d; // Текстура
  in vec4 color;            // Цвет
  in vec2 texCoord;         // Текстурные координаты
  out vec4 Frag;            // Выходной цвет
  
  // Управление текстурой и цветом
  uniform int setTexture;   // Флаг использования текстуры (1 - есть текстура, 0 - нет)
  uniform int ColorSet;     // Флаг фиксации цвета (1 - игнорировать текстуру)
  
  // Параметры эффекта
  // uniform float curvature;  // Степень изгиба (например, 1.0 - нет искажения, >1.0 - сильнее)
  // uniform float strength;   // Сила эффекта (0.0 - отключено, 1.0 - полная сила)
  
  void main()
  {
      float curvature = 2;
      float strength = 1;
      // Frag.rgb = color.rgb;
      // Центр экрана (в текстурных координатах это (0.5, 0.5))
      vec2 center = vec2(0.5, 0.5);
  
      // Смещение относительно центра
      vec2 offset = texCoord - center;
  
      // Расстояние от текущей точки до центра
      float dist = length(offset);
  
      // Применяем радиальную деформацию (инвертированное направление)
      float distortion = mix(1.0, 1.0 / (curvature * (dist + 0.1)), dist); // Инверсия через деление
      vec2 distortedCoords = center + offset * mix(1.0, distortion, strength);
  
      // Основной цвет
      Frag = color;
  
      // Если текстура используется
      if (setTexture > 0)
      {
          // Применяем текстуру с искаженными координатами
          Frag *= texture(tex_2d, distortedCoords);
      }
  
      // Если нужно зафиксировать цвет (игнорировать текстуру)
      // if (ColorSet == 1)
      // {
      //     Frag.rgb = color.rgb;
      // }
  }
  )"