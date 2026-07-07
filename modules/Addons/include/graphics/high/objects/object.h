#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/high/object"
/*class RG_Object{
  POINT3D<double> pos;
  POINT3D<double> rot;
public:
  RG_Object(){}
  RG_Object(POINT3D<double>poss){pos = poss;}
  RG_Object(POINT3D<double>poss,POINT3D<double>rott){pos = poss; rot = rott;}
  //-----

};*/

#ifdef RG_NO_USELESS_WARNING
bool RG_EXCEED_HITBOX_WARNING = 0;
#else
bool RG_EXCEED_HITBOX_WARNING = 1;
#endif


/*
rgLoadIdentity(mat);
      rgTranslatef(pos.x, pos.y, pos.z, mat);
      rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
      rgScalef(\
        size.x * scale.x, \
        size.y * scale.y, \
        size.z * scale.z, mat);
*/
/*RG_Buffer& mesh = RawMesh::mesh;
      POINT3D<double>& pos = RawMesh::pos;
      POINT3D<double>& rotate = RawMesh::rotate;
      POINT3D<double>& size = RawMesh::size;
      POINT3D<double>& scale = RawMesh::scale;
      COLOR4D<double>& color = RawMesh::color;
      RG_Matrix<float> mat;*/
enum RG_COLLISION_TYPE {
  RG_COLLISION_NONE,
  RG_COLLISION_MOUSE,
  RG_COLLISION_FLAT,
  RG_COLLISION_BODY
};



namespace RG {
  /*RG_Array<POINT3D<double>>GenRectMesh3D(POINT3D<double>in){
    RG_Array<POINT3D<double>>out(4);
    out[0]={-in.x/2.,in.y/2.,0};
    out[1]={-in.x/2.,-in.y/2.,0};
    out[2]={in.x/2.,-in.y/2.,0};
    out[3]={in.x/2.,in.y/2.,0};
    return out;
  }*/
  enum MOUSE_ACTION {
    A_NONE,
    A_HOVER,
    A_LPRESS,
    A_RPRESS,
    A_MPRESS,
  };

  template<class type>
  RG_Array<POINT3D<type>>GenRectMesh(POINT2D<type>in) {
    RG_Array<POINT3D<type>>out(4);
    out[0] = { -in.x / 2., in.y / 2., 0 };
    out[1] = { -in.x / 2., -in.y / 2., 0 };
    out[2] = { in.x / 2., -in.y / 2., 0 };
    out[3] = { in.x / 2., in.y / 2., 0 };
    return out;
  }

  /*////////////*/
  template<class type>
  inline POINT3D<double> GlobalToGL(POINT3D<type>in) {
    POINT3D<double> out;
    out.x = (in.x - RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.) / RG_SYS_WINDOWSdow_Standart->set().resolution.x * 2.;
    out.y = -(in.y - RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.) / RG_SYS_WINDOWSdow_Standart->set().resolution.y * 2.;
    return out;
  }
  template<class type>
  inline POINT2D<double> GlobalToGL(POINT2D<type>in) {
    POINT2D<double> out;
    out.x = (in.x - RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.) / RG_SYS_WINDOWSdow_Standart->set().resolution.x * 2.;
    out.y = -(in.y - RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.) / RG_SYS_WINDOWSdow_Standart->set().resolution.y * 2.;
    return out;
  }
  /*////////////*/
  template<class type>
  inline POINT3D<double> GLToGlobal(POINT3D<type> in) {
    POINT3D<double> out;
    out.x = in.x * RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2. + RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.;
    out.y = -in.y * RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2. + RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.;
    out.z = in.z;
    return out;
  }

  template<class type>
  inline POINT2D<double> GLToGlobal(POINT2D<type> in) {
    POINT2D<double> out;
    out.x = in.x * RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2. + RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.;
    out.y = -in.y * RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2. + RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.;
    return out;
  }



  namespace Physics {
    class Engine;
  }


  namespace Graphic {
    namespace Flat {
      namespace Lock {

        POINT3D<double>Square3Dvectors[4] = {
          {-1, 1, 0},
          {-1, -1, 0},
          {1, -1, 0},
          {1, 1, 0}
        };

        struct RawMesh : protected RG_Buffer {
          POINT3D<double> pos;
          POINT3D<double> rotate;
          POINT2D<double> size = { 1, 1 };
          POINT2D<double> scale = { 1, 1 };
          COLOR4D<double> color;
        protected:
          RG_Matrix<float> mat;
        };
        struct Mesh :public RawMesh {
          friend class RG::Physics::Engine;
          LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
          RG_Array<int> textures;
          bool custom_size = false;
          bool is_gui = false;
          bool is3d = false;
          bool hitbox = false;
          bool collision = false;
          bool animate = false;
        protected:
          uint frame = 0;
          double tempFrame = 0;
          int FrPeSe = 10;
          int maxFrames = 1;
          RG_Array<vec4<double>> truePolygon;
          Mesh* _parent = nullptr;

          //RG_Array<vec4<double>*> hitbox1;
          //RG_Array<vec4<double>*> hitbox2;
        public:
          void test() {
            RG_LOG_LOCK_INFO("Mesh test");
            RG_LOG_LOCK_INFO("Public:");
            RG_LOG_LOCK_INFO("GuiType: " + std::to_string((int)GuiType));
            RG_LOG_LOCK_INFO("is_gui: " + std::to_string(is_gui));
            RG_LOG_LOCK_INFO("is3d: " + std::to_string(is3d));
            RG_LOG_LOCK_INFO("hitbox: " + std::to_string(hitbox));
            RG_LOG_LOCK_INFO("collision: " + std::to_string(collision));
            RG_LOG_LOCK_INFO("animate: " + std::to_string(animate));
            RG_LOG_LOCK_INFO("custom_size: " + std::to_string(custom_size));
            RG_LOG_LOCK_INFO("textures: " + std::to_string(textures.size()));
            string temp;
            for (int i = 0; i < textures.size(); i++) {
              temp += std::to_string(textures[i]) + " ";
            }
            if (temp.size() > 0)RG_LOG_LOCK_INFO("Textures IDs: " + temp);

            RG_LOG_LOCK_INFO("Private:");
            RG_LOG_LOCK_INFO("pos: " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z));
            RG_LOG_LOCK_INFO("rotate: " + std::to_string(rotate.x) + ", " + std::to_string(rotate.y) + ", " + std::to_string(rotate.z));
            RG_LOG_LOCK_INFO("size: " + std::to_string(size.x) + ", " + std::to_string(size.y));
            RG_LOG_LOCK_INFO("scale: " + std::to_string(scale.x) + ", " + std::to_string(scale.y));
            RG_LOG_LOCK_INFO("color: " + std::to_string(color.r) + ", " + std::to_string(color.g) + ", " + std::to_string(color.b) + ", " + std::to_string(color.a));
            RG_LOG_LOCK_INFO("Protected:");
            RG_LOG_LOCK_INFO("mat:\n" + mat.print_d());
            RG_LOG_LOCK_INFO("frame: " + std::to_string(frame));
            RG_LOG_LOCK_INFO("tempFrame: " + std::to_string(tempFrame));
            RG_LOG_LOCK_INFO("FrPeSe: " + std::to_string(FrPeSe));
            RG_LOG_LOCK_INFO("maxFrames: " + std::to_string(maxFrames));


          }
          struct Set {
            POINT3D<double> pos;
            POINT2D<double> size = { 1, 1 };
            POINT2D<double> scale = { 1, 1 };
            COLOR4D<double> color;
            POINT3D<double> rotate;
            RG_Array<int> textures;
            bool custom_size = false;
            bool is_gui = false;
            LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
            bool is3d = false;
            bool hitbox = false;
            bool collision = false;
            bool animate = false;
          };

          virtual void init(Set in) {
            pos = in.pos;
            size = in.size;
            scale = in.scale;
            color = in.color;
            rotate = in.rotate;
            textures = in.textures;
            custom_size = in.custom_size;
            is_gui = in.is_gui;
            GuiType = in.GuiType;
            is3d = in.is3d;
            hitbox = in.hitbox;
            collision = in.collision;
            animate = in.animate;
          }
          Mesh() {}
          Mesh(Set in) {
            pos = in.pos;
            size = in.size;
            scale = in.scale;
            color = in.color;
            rotate = in.rotate;
            textures = in.textures;
            custom_size = in.custom_size;
            is_gui = in.is_gui;
            GuiType = in.GuiType;
            is3d = in.is3d;
            hitbox = in.hitbox;
            collision = in.collision;
            animate = in.animate;
          }

          void Build() {
            if (maxFrames <= 0)RG_LOG_LOCK_CRITICAL("maxFrames<=0");
            if (frame >= maxFrames)RG_LOG_LOCK_CRITICAL("frame>=maxFrames");
            //COLOR4D<double>coltemp[4] = { color, color, color, color };//glColor


            RG_Buffer::raw.color.init(4, color);


            RG_Buffer::raw.elements.init({ 0, 1, 2, 2, 3, 0 });
            RG_Buffer::raw.vertex.init(4, Lock::Square3Dvectors);
            if (textures.size() > 0) {

              maxFrames = textures.size();
              POINT2D<int> TexturePos;
              POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;

              RG_Buffer::raw.textures.resize(textures.size());
              int i = 0;
              for (int t : textures) {

                TexturePos = (*RG_Atlas_StandartPtr)[t].pos;

                TextureSize = (*RG_Atlas_StandartPtr)[t].size;

                POINT2D<double> TexCoordArr[4] = {
                  {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
                  {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
                  {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
                  {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
                };

                RG_Buffer::raw.textures[i].resize(4);

                RG_Buffer::raw.textures[i].fill(TexCoordArr);


                i++;
              }
            }
            MatInit();
            RG_Buffer::GL_Gen();
          }

          // RG_Material material = RG_StandartMaterial;
          // bool custom_size = false;

          void MatInit() {

            if (textures.size() > 0 && !custom_size) {
              POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;

              size.x = TextureSize.x / RG_SYS_WINDOWSdow_Virtual;
              size.y = TextureSize.y / RG_SYS_WINDOWSdow_Virtual;
              //RG_LOG_LOCK_INFO("Texture has, size = " + to_string(TextureSize.x) + ", " + to_string(TextureSize.y));
            }

            MatUpdate();

          }
          void next_frame() {
            frame++;
          }
          void set_frame(uint id) {
            frame = id;
          }
          void MatUpdate() {

            rgLoadIdentity(mat);
            if (_parent == nullptr) {
              //rgLoadIdentity(mat);
              rgTranslatef(pos.x, pos.y, pos.z, mat);
              rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
              rgScalef(\
                size.x * scale.x, \
                size.y * scale.y, \
                1, mat);
              //TruePolygonUpdate();
            } else {
              //mat = _parent->mat;
              rgTranslatef(pos.x + _parent->pos.x, pos.y + _parent->pos.y, pos.z + _parent->pos.z, mat);
              rgRotatef(rotate.x + _parent->rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y + _parent->rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z + _parent->rotate.z, 0, 0, 1, mat);
              rgScalef(\
                size.x * scale.x * _parent->scale.x, \
                size.y * scale.y * _parent->scale.y, \
                1, mat);
            }
            if (collision)
              TruePolygonUpdate();
            /*rgTranslatef(pos.x, pos.y, pos.z, mat);
            rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
            rgScalef(\
              size.x * scale.x, \
              size.y * scale.y, \
              1, mat);
            TruePolygonUpdate();*/
          }
          void paint() {
            Lock::Mesh::RG_Buffer::raw.color.fill(Lock::Mesh::color);
            Lock::Mesh::RG_Buffer::GL_Regen(GL_INIT_Color);
          }
          void paint(COLOR4D<double> col) {
            if (col != Lock::Mesh::color) {
              Lock::Mesh::color = col;
              Lock::Mesh::RG_Buffer::raw.color.fill(Lock::Mesh::color);
              Lock::Mesh::RG_Buffer::GL_Regen(GL_INIT_Color);
            }
          }
          void set_parent(Mesh& par) {
            _parent = &par;
          }
          void TruePolygonInit() {
            if (collision) {
              truePolygon.resize(RG_Buffer::raw.elements.size());
              //hitbox1.resize(RG_Buffer::raw.elements.size());
              //hitbox2.resize(RG_Buffer::raw.elements.size());
              TruePolygonUpdate();
            } else {
              RG_LOG_LOCK_ERROR("False true polygon init, collision is off");
            }
          }
          void TruePolygonUpdate() {
            if (collision) {
              if (RG_Buffer::raw.elements.size() != truePolygon.size()) {
                TruePolygonInit();
              } else {
                double scaleX = size.x * scale.x;
                double scaleY = size.y * scale.y;

                // Предварительные вычисления для поворотов
                double cosX = cos(rotate.x), sinX = sin(rotate.x);
                double cosY = cos(rotate.y), sinY = sin(rotate.y);
                double cosZ = cos(rotate.z), sinZ = sin(rotate.z);

                /*POINT2D<double>tempOtn;
                if (RG_SYS_WINDOWSdow_Standart->set().resolution.x > RG_SYS_WINDOWSdow_Standart->set().resolution.y) {
                  tempOtn.x = ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y);
                  tempOtn.y = 1;
                } else {
                  tempOtn.x = 1;
                  tempOtn.y = ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x);
                }*/
                for (int i = 0; i < truePolygon.size(); i++) {
                  truePolygon[i] = { RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].x,RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].y,RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].z,1 };
                  // Исходная вершина
                  rgScalefa(
                    size.x * scale.x,
                    size.y * scale.y,
                    1, truePolygon[i]);
                  rgRotatefa(rotate.z, 0, 0, 1, truePolygon[i]); rgRotatefa(rotate.y, 0, 1, 0, truePolygon[i]); rgRotatefa(rotate.x, 1, 0, 0, truePolygon[i]);
                  rgTranslatefa(pos.x, pos.y, pos.z, truePolygon[i]);
                  /*if (RG_Camera_StandartPtr->is3d())
                    rgFrustumfa((-tempOtn.x), (tempOtn.x), -tempOtn.y, tempOtn.y, RG_Render_Distance3D[0], RG_Render_Distance3D[1], truePolygon[i]);
                  else
                    rgOrthofa((-tempOtn.x), tempOtn.x, -tempOtn.y, tempOtn.y, -RG_Render_Distance2D[0], RG_Render_Distance2D[1], truePolygon[i]);
                  */
                  //hitbox1[i] = (&truePolygon[i]);
                  //hitbox2[i] = (&truePolygon[(i + 1) % truePolygon.size()]);
                }
              }
            } else {
              RG_LOG_LOCK_ERROR("False polygon update, collision is off");
            }
            //rg_cout << endl;
          }
          /*void TruePolygonInit() {
            truePolygon.resize(RG_Buffer::raw.elements.size());
            hitbox1.resize(RG_Buffer::raw.elements.size());
            hitbox2.resize(RG_Buffer::raw.elements.size());
            // Предварительный расчёт: масштаб и размер
            double scaleX = size.x * scale.x;
            double scaleY = size.y * scale.y;

            // Предварительные вычисления для поворотов
            double cosX = cos(rotate.x), sinX = sin(rotate.x);
            double cosY = cos(rotate.y), sinY = sin(rotate.y);
            double cosZ = cos(rotate.z), sinZ = sin(rotate.z);

            for (int i = 0; i < truePolygon.size(); i++) {
              // Исходная вершина
              POINT3D<double> vertex = RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]];
              // Масштабирование
              vertex.x *= scaleX;
              vertex.y *= scaleY;
              // Вращение по Z
              vertex.x = vertex.x * cosZ - vertex.y * sinZ;
              vertex.y = vertex.x * sinZ + vertex.y * cosZ;
              // Вращение по Y
              vertex.x = vertex.x * cosY + vertex.z * sinY;
              vertex.z = -vertex.x * sinY + vertex.z * cosY;
              // Вращение по X
              vertex.y = vertex.y * cosX - vertex.z * sinX;
              vertex.z = vertex.y * sinX + vertex.z * cosX;
              // Трансляция
              vertex.x += pos.x;
              vertex.y += pos.y;
              vertex.z += pos.z;
              // Сохраняем результат
              truePolygon[i] = vec4<double>({ vertex.x, vertex.y, vertex.z, 1 });
              hitbox1[i] = (&truePolygon[i]);
              hitbox2[i] = (&truePolygon[(i + 1) % truePolygon.size()]);
            }
          }*/
          // void TruePolygonInit(){
          //   truePolygon.resize(RG_Buffer::raw.elements.size());
          //   hitbox1.resize(RG_Buffer::raw.elements.size());
          //   hitbox2.resize(RG_Buffer::raw.elements.size());
          //   for(int i = 0; i < truePolygon.size();i++){
          //     truePolygon[i] = vec4<double>({RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].x, RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].y, RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].z, 1}) * mat;
          //     hitbox1[i] = (&truePolygon[i]);
          //     hitbox2[i] = (&truePolygon[(i + 1) % truePolygon.size()]);
          //   }
          // }



          /*void TruePolygonUpdate(){
            if(RG_Buffer::raw.elements.size() != truePolygon.size()){
              TruePolygonInit();
            } else{
              double scaleX = size.x * scale.x;
            double scaleY = size.y * scale.y;

            // Предварительные вычисления для поворотов
            double cosX = cos(rotate.x), sinX = sin(rotate.x);
            double cosY = cos(rotate.y), sinY = sin(rotate.y);
            double cosZ = cos(rotate.z), sinZ = sin(rotate.z);

            for(int i = 0; i < truePolygon.size(); i++){
              // Исходная вершина
              POINT3D<double> vertex = RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]];
              // Масштабирование
              vertex.x *= scaleX;
              vertex.y *= scaleY;
              // Вращение по Z
              vertex.x = vertex.x * cosZ - vertex.y * sinZ;
              vertex.y = vertex.x * sinZ + vertex.y * cosZ;
              // Вращение по Y
              vertex.x = vertex.x * cosY + vertex.z * sinY;
              vertex.z = -vertex.x * sinY + vertex.z * cosY;
              // Вращение по X
              vertex.y = vertex.y * cosX - vertex.z * sinX;
              vertex.z = vertex.y * sinX + vertex.z * cosX;
              // Трансляция
              vertex.x += pos.x;
              vertex.y += pos.y;
              vertex.z += pos.z;
              // Сохраняем результат
              truePolygon[i] = vec4<double>({vertex.x, vertex.y, vertex.z, 1});
              hitbox1[i] = (&truePolygon[i]);
              hitbox2[i] = (&truePolygon[(i + 1) % truePolygon.size()]);
            }
            }
            //rg_cout << endl;
          }*/


          /*void TruePolygonUpdate(){
            if(RG_Buffer::raw.elements.size() != truePolygon.size()){
              TruePolygonInit();
            } else{
              for(int i = 0; i < truePolygon.size();i++){
                truePolygon[i] = vec4<double>({RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].x, RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].y, RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].z, 1.}) * mat;
              }
            }
            //rg_cout << endl;
          }*/
          inline static int debug_int = 0;
          void draw(const RG_Camera& cam = *RG_Camera_StandartPtr) {
            if (RG_Buffer::gl.textures.size() > 0) {
              if (animate)tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

              if (tempFrame > 1) {
                frame += floor(tempFrame);
                tempFrame -= floor(tempFrame);
              }
              frame = frame % (maxFrames);//textures.size();
              RG_Mods::Texture_On();
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
              RG_Buffer::gl.textures[frame].bind();
              rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
            } else RG_Mods::Texture_Off();

            if (RG_Buffer::gl.vertex.is_init()) {
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
              RG_Buffer::gl.vertex.bind();
              rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
            } else RG_LOG_LOCK_CRITICAL("flat mesh gl vertex == -1");

            if (RG_Buffer::gl.color.is_init()) {
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
              RG_Buffer::gl.color.bind();
              rgColorPointer(4, GL_DOUBLE, 0, nullptr);
            } else RG_LOG_LOCK_CRITICAL("flat mesh gl color == -1");//TODO fix everything
            //cam.loadMatrix();


            if (is_gui) {
              rgLoadGuiMatrix(GuiType);
            } else {
              //rgLoadCamMatrix();
              cam.loadMatrix();
            }
            rgLoadMatrixf(mat);


            rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
          }
          void draw_d(const RG_Camera& cam = *RG_Camera_StandartPtr) {
            RG_LOG_LOCK_INFO("draw start");
            RG_LOG_LOCK_INFO("Textures init");
            if (RG_Buffer::gl.textures.size() > 0) {
              RG_LOG_LOCK_INFO("Texture size > 0");
              if (animate)tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

              if (tempFrame > 1) {
                RG_LOG_LOCK_INFO("Next frame");
                frame += floor(tempFrame);
                tempFrame -= floor(tempFrame);
              }
              frame = frame % (maxFrames);//textures.size();
              RG_Mods::Texture_On();
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
              RG_Buffer::gl.textures[frame].bind();
              rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
            } else RG_Mods::Texture_Off();
            RG_LOG_LOCK_INFO("Vertex init");

            if (RG_Buffer::gl.vertex.is_init()) {
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
              RG_Buffer::gl.vertex.bind();
              rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
            } else RG_LOG_LOCK_CRITICAL("flat mesh gl vertex == -1");

            RG_LOG_LOCK_INFO("Color init");
            if (RG_Buffer::gl.color.is_init()) {
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
              RG_Buffer::gl.color.bind();
              rgColorPointer(4, GL_DOUBLE, 0, nullptr);
            } else RG_LOG_LOCK_CRITICAL("flat mesh gl color == -1");//TODO fix everything
            //cam.loadMatrix();


            RG_LOG_LOCK_INFO("Matrix init");
            if (is_gui) {
              RG_LOG_LOCK_INFO("GUI matrix");
              rgLoadGuiMatrix(GuiType);
            } else {
              //rgLoadCamMatrix();
              RG_LOG_LOCK_INFO("Cam matrix");
              cam.loadMatrix();
            }
            RG_LOG_LOCK_INFO("Object matrix init");
            rgLoadMatrixf(mat);


            RG_LOG_LOCK_INFO("Draw object");
            rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
            RG_LOG_LOCK_INFO("Done");
          }
          MOUSE_ACTION Action(bool sticky = false) {
            POINT2D<double> mouse = GlobalToGL(MPos);
            //vec4<double> mouse2 = vec4<double>({mouse.x, mouse.y, 1., 1.}) * RG_Camera_StandartPtr->getMat();
            //vec4<double>mouse2;
            vec4<double> mouse2 = vec4<double>({ mouse.x, mouse.y, 0., 1. });
            if (is_gui) {
              RG_Point_To_Invert_GUI(mouse2, GuiType);
            } else {
              RG_Camera_StandartPtr->Point_To_Cam(mouse2);
              if (RG_EXCEED_HITBOX_WARNING) {
                if (RG_Camera_StandartPtr->getRotate().x != 0 && RG_Camera_StandartPtr->getRotate().y != 0) {
                  RG_LOG_LOCK_WARNING("If you rotate the camera in x and y at the same time, the collision is broken, keep in mind that Action may not work correctly!");
                  RG_EXCEED_HITBOX_WARNING = 0;
                }
              }
            }
            vec2<vec4<double>> hb;
            int intersections = 0;

            if (hitbox) {

              glColor4d(1, 0.3, 0.3, 1);
              glPointParameteri(GL_POINT_SIZE, 100);
              //glPointParameterf
              glUseProgram(0);
              rgBegin(GL_POINTS);

              rgVertex3f(mouse2.x, mouse2.y, -1);
              /*glVertex3f(mouse2.x - 0.01, mouse2.y - 0.01, 0);
              glVertex3f(mouse2.x - 0.01, mouse2.y + 0.01, 0);
              glVertex3f(mouse2.x + 0.01, mouse2.y + 0.01, 0);
              glVertex3f(mouse2.x + 0.01, mouse2.y + 0.01, 0);
              glVertex3f(mouse2.x + 0.01, mouse2.y - 0.01, 0);
              glVertex3f(mouse2.x - 0.01, mouse2.y - 0.01, 0);*/
              rgEnd();
              rgBegin(GL_LINES);
              for (int i = 0; i < truePolygon.size(); ++i) {
                //vec4<double> invec = vec4<double>{truePolygon[i].x,truePolygon[i].y,truePolygon[i].z,1}*RG_Camera_StandartPtr->getMat();
                //rgVertex3f(invec.x, invec.y, invec.z);
                hb[0] = (truePolygon[i]);//*RG_Camera_StandartPtr->getMat();
                hb[1] = (truePolygon[(i + 1) % truePolygon.size()]);//*RG_Camera_StandartPtr->getMat();
                rgVertex3f(hb[0].x, hb[0].y, hb[0].z);
                rgVertex3f(hb[1].x, hb[1].y, hb[1].z);
                // Проверка пересечения луча с отрезком
                if ((hb[0].y <= mouse2.y && hb[1].y > mouse2.y) ||
                  (hb[1].y <= mouse2.y && hb[0].y > mouse2.y)) {
                  double x_intersect = hb[0].x + (mouse2.y - hb[0].y) * (hb[1].x - hb[0].x) / (hb[1].y - hb[0].y);
                  if (x_intersect > mouse2.x) {
                    intersections++;
                  }
                }
              }
              rgEnd();
              glUseProgram(RG_STANDART_SHADER_PROG);
            } else {
              for (int i = 0; i < truePolygon.size(); ++i) {
                //vec4<double> invec = vec4<double>{truePolygon[i].x,truePolygon[i].y,truePolygon[i].z,1}*RG_Camera_StandartPtr->getMat();
                //rgVertex3f(invec.x, invec.y, invec.z);
                hb[0] = (truePolygon[i]);//*RG_Camera_StandartPtr->getMat();
                hb[1] = (truePolygon[(i + 1) % truePolygon.size()]);//*RG_Camera_StandartPtr->getMat();
                // Проверка пересечения луча с отрезком
                if ((hb[0].y <= mouse2.y && hb[1].y > mouse2.y) ||
                  (hb[1].y <= mouse2.y && hb[0].y > mouse2.y)) {
                  double x_intersect = hb[0].x + (mouse2.y - hb[0].y) * (hb[1].x - hb[0].x) / (hb[1].y - hb[0].y);
                  if (x_intersect > mouse2.x) {
                    intersections++;
                  }
                }
              }
            }

            // Нечётное количество пересечений означает, что точка внутри
            if ((intersections % 2) != 0) {
              if (RG_MOUSE[GLFW_MOUSE_BUTTON_LEFT]) {
                if (!sticky)RG_MOUSE[GLFW_MOUSE_BUTTON_LEFT] = false;
                return RG::A_LPRESS;
              }
              if (RG_MOUSE[GLFW_MOUSE_BUTTON_RIGHT]) {
                if (!sticky)RG_MOUSE[GLFW_MOUSE_BUTTON_RIGHT] = false;
                return RG::A_RPRESS;
              }
              if (RG_MOUSE[GLFW_MOUSE_BUTTON_MIDDLE]) {
                if (!sticky)RG_MOUSE[GLFW_MOUSE_BUTTON_MIDDLE] = false;
                return RG::A_MPRESS;
              }
              return RG::A_HOVER;
            }
            return RG::A_NONE;

            return A_NONE;
          }

          bool Collide(const Mesh& otherMesh, bool sticky = false, RG_Array<uint>ThisCollide = {}, RG_Array<uint> OtherCollide = {}) {
            int intersections = 0;

            // Проверка пересечения рёбер двух полигонов
            if (ThisCollide.size() == 0) {
              for (uint i = 0; i < this->truePolygon.size(); ++i) {
                vec4<double> a1 = this->truePolygon[i];
                vec4<double> a2 = this->truePolygon[(i + 1) % this->truePolygon.size()];
                if (OtherCollide.size() == 0) {
                  for (uint j = 0; j < otherMesh.truePolygon.size(); ++j) {
                    vec4<double> b1 = otherMesh.truePolygon[j];
                    vec4<double> b2 = otherMesh.truePolygon[(j + 1) % otherMesh.truePolygon.size()];

                    // Проверка пересечения рёбер (a1, a2) и (b1, b2)
                    double denom = (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
                    if (denom == 0) continue; // Параллельные линии.

                    double ua = ((b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x)) / denom;
                    double ub = ((a2.x - a1.x) * (a1.y - b1.y) - (a2.y - a1.y) * (a1.x - b1.x)) / denom;

                    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
                      return 1; // Пересечение рёбер.
                    }
                  }
                } else {
                  for (uint& j : OtherCollide) {
                    //rg_cout << "custom other index: " << j << endl;
                    if (j >= otherMesh.truePolygon.size()) { RG_LOG_LOCK_ERROR("Collide custom other collide index out of range, size == " + to_string(otherMesh.truePolygon.size()) + ", index = " + to_string(j)); continue; }
                    vec4<double> b1 = otherMesh.truePolygon[j];
                    vec4<double> b2 = otherMesh.truePolygon[(j + 1) % otherMesh.truePolygon.size()];

                    // Проверка пересечения рёбер (a1, a2) и (b1, b2)
                    double denom = (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
                    if (denom == 0) continue; // Параллельные линии.

                    double ua = ((b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x)) / denom;
                    double ub = ((a2.x - a1.x) * (a1.y - b1.y) - (a2.y - a1.y) * (a1.x - b1.x)) / denom;

                    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
                      return 1; // Пересечение рёбер.
                    }
                  }
                }
              }
            } else {
              for (uint& i : ThisCollide) {
                //rg_cout << "custom this index: " << i << endl;
                if (i >= this->truePolygon.size()) { RG_LOG_LOCK_ERROR("Collide custom this collide index out of range, size == " + to_string(this->truePolygon.size()) + ", index = " + to_string(i)); continue; }
                vec4<double> a1 = this->truePolygon[i];
                vec4<double> a2 = this->truePolygon[(i + 1) % this->truePolygon.size()];
                if (OtherCollide.size() == 0)
                  for (uint j = 0; j < otherMesh.truePolygon.size(); ++j) {
                    vec4<double> b1 = otherMesh.truePolygon[j];
                    vec4<double> b2 = otherMesh.truePolygon[(j + 1) % otherMesh.truePolygon.size()];

                    // Проверка пересечения рёбер (a1, a2) и (b1, b2)
                    double denom = (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
                    if (denom == 0) continue; // Параллельные линии.

                    double ua = ((b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x)) / denom;
                    double ub = ((a2.x - a1.x) * (a1.y - b1.y) - (a2.y - a1.y) * (a1.x - b1.x)) / denom;

                    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
                      return 1; // Пересечение рёбер.
                    }
                  } else {
                    for (uint& j : OtherCollide) {
                      //rg_cout<<truePolygon[i].x<<"|"<<truePolygon[i+1].x<<" /\\"<<otherMesh.truePolygon[j].x<<"|"<<otherMesh.truePolygon[j+1].x<<endl<<endl;
                      //rg_cout << "custom other index: " << j << endl;
                      if (j >= otherMesh.truePolygon.size()) { RG_LOG_LOCK_ERROR("Collide custom other collide index out of range, size == " + to_string(otherMesh.truePolygon.size()) + ", index = " + to_string(j)); continue; }
                      vec4<double> b1 = otherMesh.truePolygon[j];
                      vec4<double> b2 = otherMesh.truePolygon[(j + 1) % otherMesh.truePolygon.size()];
                      // Проверка пересечения рёбер (a1, a2) и (b1, b2)
                      double denom = (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
                      if (denom == 0) continue; // Параллельные линии.

                      double ua = ((b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x)) / denom;
                      double ub = ((a2.x - a1.x) * (a1.y - b1.y) - (a2.y - a1.y) * (a1.x - b1.x)) / denom;

                      if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
                        return 1; // Пересечение рёбер.
                      }
                    }
                  }
              }
            }

            // Проверка попадания вершин одного меша в другой
            auto isPointInside = [](const vec4<double>& point, const RG_Array<vec4<double>>& polygon) -> bool {
              int count = 0;
              for (uint i = 0; i < polygon.size(); ++i) {
                vec4<double> p1 = polygon[i];
                vec4<double> p2 = polygon[(i + 1) % polygon.size()];

                if ((p1.y <= point.y && p2.y > point.y) || (p2.y <= point.y && p1.y > point.y)) {
                  double x_intersect = p1.x + (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                  if (x_intersect > point.x) {
                    count++;
                  }
                }
              }
              return (count % 2) != 0; // Нечётное число пересечений — точка внутри.
            };

            // Проверка попадания вершин второго меша в первый
            for (const auto& vertex : otherMesh.truePolygon) {
              if (isPointInside(vertex, this->truePolygon)) {
                return 1;
              }
            }

            // Проверка попадания вершин первого меша во второй
            for (const auto& vertex : this->truePolygon) {
              if (isPointInside(vertex, otherMesh.truePolygon)) {
                return 1;
              }
            }

            return 0; // Пересечений и попаданий не обнаружено.
          }
          /*
                    MOUSE_ACTION Action(bool sticky = false) {

                    //TruePolygonInit();
                      int intersections = 0;
                      vec2<double>point2 = {
                        (MPos.x - RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.) / RG_SYS_WINDOWSdow_Standart->set().resolution.x * 2.,
                        (MPos.y - RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.) / RG_SYS_WINDOWSdow_Standart->set().resolution.y * 2.
                      };
                      //vec2<double> hitbox = {};
                      //rg_cout << point << endl;
                      //rgBegin(GL_TRIANGLES);
                      //vec4<double>v1;
                      //vec4<double>v2;
                      RG_Matrix<float> cam;

                      if (is_gui) {
                        RG_Set_Gui_Matrix(cam, GuiType);
                      } else {
                        cam = RG_Camera_StandartPtr->getMat();
                      }
                      //vec4<double>point = (((RG_Matrix<double>({{point2.x},{point2.y},{0},{0}})).transpose() * cam.transpose()).transpose());
                      //vec4<double>point = (((RG_Matrix<double>({{point2.x},{point2.y},{0},{0}})).transpose() * cam.transpose()));
                      //rg_cout<<point3.size(0)<<" "<<point3.size(1)<<endl;
                      vec2<double>&point = point2;
                      //rg_cout<<"mat:\n";
                      //cam.print();
                      //rg_cout<<"points:\n";
                      //\\vec4<double> point = vec4<double>({ point2.x, point2.y, 0., 0 })*cam;
                      //rg_cout<<point2<<endl<<point<<endl<<endl;
                      // rg_cout<<"Cam:\n";
                      // cam.print();
                      // rg_cout<<"\n:Cam\n";
                      vec2<vec4<double>> hb;
                      for (int i = 0; i < truePolygon.size(); ++i) {
                        //hb[0] = (vec4<double>({ RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].x,RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].y,RG_Buffer::raw.vertex[RG_Buffer::raw.elements[i]].z,1. }) * mat) * cam ;
                        //hb[1] = (vec4<double>({ RG_Buffer::raw.vertex[RG_Buffer::raw.elements[(i + 1) % RG_Buffer::raw.elements.size()]].x,RG_Buffer::raw.vertex[RG_Buffer::raw.elements[(i + 1) % RG_Buffer::raw.elements.size()]].y,RG_Buffer::raw.vertex[RG_Buffer::raw.elements[(i + 1) % RG_Buffer::raw.elements.size()]].z,1. }) * mat) * cam;
                        hb[0] = (*hitbox1[i]);// *cam);
                        hb[1] = (*hitbox2[i]);// *cam);

                        // Проверка пересечения луча с отрезком
                        if ((hb[0].y <= point.y && hb[1].y > point.y) ||
                          (hb[1].y <= point.y && hb[0].y > point.y)) {
                          double x_intersect = hb[0].x + (point.y - hb[0].y) * (hb[1].x - hb[0].x) / (hb[1].y - hb[0].y);
                          if (x_intersect > point.x) {
                            intersections++;
                          }
                        }
                      }

                      // Нечётное количество пересечений означает, что точка внутри
                      if ((intersections % 2) != 0) {
                        if (RG_MOUSE[GLFW_MOUSE_BUTTON_LEFT]) {
                          return RG::A_LPRESS;
                        }
                        return RG::A_HOVER;
                      }
                      return RG::A_NONE;
                    }*/
        };

      }

      class Sprite :public Lock::Mesh {
      public:
        void Update() {
          MatUpdate();
        }

        void Create() {
          if (maxFrames <= 0)RG_LOG_LOCK_CRITICAL("maxFrames<=0");
          if (frame >= maxFrames)RG_LOG_LOCK_CRITICAL("frame>=maxFrames");
          //COLOR4D<double>coltemp[4] = { color, color, color, color };//glColor


          Lock::Mesh::RG_Buffer::raw.color.init(4, Lock::Mesh::color);


          Lock::Mesh::RG_Buffer::raw.elements.init({ 0, 1, 2, 2, 3, 0 });
          Lock::Mesh::RG_Buffer::raw.vertex.init(4, Lock::Square3Dvectors);
          if (textures.size() > 0) {

            maxFrames = textures.size();
            POINT2D<int> TexturePos;
            POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;

            Lock::Mesh::RG_Buffer::raw.textures.resize(textures.size());
            int i = 0;
            for (int t : textures) {

              TexturePos = (*RG_Atlas_StandartPtr)[t].pos;

              TextureSize = (*RG_Atlas_StandartPtr)[t].size;

              POINT2D<double> TexCoordArr[4] = {
                {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
                {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
                {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
                {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
              };

              Lock::Mesh::RG_Buffer::raw.textures[i].resize(4);

              Lock::Mesh::RG_Buffer::raw.textures[i].fill(TexCoordArr);


              i++;
            }



          }

          Lock::Mesh::MatInit();
          Lock::Mesh::RG_Buffer::GL_Gen();
        }



        void update() {
          Lock::Mesh::MatUpdate();
        }

        void to_rotate(POINT3D<double>rot, bool upd = 0) {
          rotate.x += rot.x;
          rotate.y += rot.y;
          rotate.z += rot.z;
          if (upd)update();
        }
        void set_rotate(POINT3D<double> rot, bool upd = 0) {
          rotate = rot;
          if (upd)update();
        }

        void set_scale(POINT2D<double> sc, bool upd = 0) {
          scale = sc;
          if (upd)update();
        }
        void set_size(POINT2D<double> sz, bool upd = 0) {
          size = sz;
          if (upd)update();
        }
        void set_pos(POINT3D<double>poss, bool upd = 0) {
          pos = poss;
          if (upd)update();
        }
        void move(POINT3D<double>move, bool upd = 0) {
          pos.x += move.x;
          pos.y += move.y;
          pos.z += move.z;
          if (upd)update();
        }

        /*void draw(RG_Camera& cam = RG_Camera_StandartPtr) {

          if (RG_Buffer::gl.textures.size() > 0) {
            tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

            if (tempFrame > 1) {
              frame += floor(tempFrame);
              tempFrame -= floor(tempFrame);
            }
            frame = frame % (maxFrames);//textures.size();
            RG_Mods::Texture_On();
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
            rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
          } else RG_Mods::Texture_Off();

          if (RG_Buffer::gl.vertex != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
            rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("background vertex == -1");
          if (RG_Buffer::gl.color != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
            rgColorPointer(4, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("background color == -1");
          //cam.loadMatrix();


          if (is_gui) {
            rgLoadGuiMatrix(GuiType);
          } else {
            //rgLoadCamMatrix();
            cam.loadMatrix();
          }
          rgLoadMatrixf(mat);


          rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
        }*/

        int action(bool sticky = false) {


          POINT2D<double>HPos;

          if (is_gui) {
            if (GuiType == RG_GUI_LINK_LEFT_TOP) { HPos.x = 0; HPos.y = 0; }
            if (GuiType == RG_GUI_LINK_LEFT_CENTER) { HPos.x = 0; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.; }
            if (GuiType == RG_GUI_LINK_LEFT_BOTTOM) { HPos.x = 0; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y; }

            if (GuiType == RG_GUI_LINK_CENTER_TOP) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = 0; }
            if (GuiType == RG_GUI_LINK_CENTER_CENTER) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.; }
            if (GuiType == RG_GUI_LINK_CENTER_BOTTOM) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y; }

            if (GuiType == RG_GUI_LINK_RIGHT_TOP) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x; HPos.y = 0; }
            if (GuiType == RG_GUI_LINK_RIGHT_CENTER) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.; }
            if (GuiType == RG_GUI_LINK_RIGHT_BOTTOM) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y; }
          } else {
            HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.;
          }

          POINT2D <double>SIZE;

          SIZE.x = size.x * RG_SYS_WINDOWSdow_Standart->set().resolution.x * scale.x * ((float)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x);
          SIZE.y = size.y * RG_SYS_WINDOWSdow_Standart->set().resolution.y * scale.y;
          //SIZE.z = size.z * scale.z;



          POINT2D<double> LeftTop = {
            (HPos.x + (pos.x / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.x) * ((float)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x) - (SIZE.x / 2)),
            (HPos.y + (-pos.y / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.y)) - (SIZE.y / 2.)
          };

          POINT2D<double> RightBottom
          {
            (HPos.x + ((pos.x / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.x)) * ((float)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x)) + (SIZE.x / 2.),
            (HPos.y + (-pos.y / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.y)) + (SIZE.y / 2.)
          };

          if (MPos.x > LeftTop.x && MPos.x < RightBottom.x) {
            if (MPos.y > LeftTop.y && MPos.y < RightBottom.y) {
              if (RG_MOUSE[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS) { if (!sticky)RG_MOUSE[GLFW_MOUSE_BUTTON_1] = GLFW_RELEASE; return 2; } else return 1;
            }
          }


          return 0;
        }
      };//SPRITE

      class Background :public Lock::Mesh {
      public:
        enum Types {
          None,
          GradientHorizontal,
          GradientVertical,
          TextureScale,
          TextureStretch,
        };
        Types type;
        RG::vec2<COLOR4D<double>> color;


        void Create() {


          RG_Array<COLOR4D<double>> temp;

          is_gui = true;

          switch (type) {
            case Types::GradientHorizontal:
            temp = { color[0], color[0], color[1], color[1] };
            break;
            case Types::GradientVertical:
            temp = { color[0], color[1], color[1], color[0] };
            break;
            default:
            temp = { color[0], color[0], color[0], color[0] };
            break;
          }


          //mat.fill(4, 4, IdentityMat);
          rgLoadIdentity(mat);

          rgTranslatef(0, 0, 1, mat);



          if (textures.size() > 0) {

            maxFrames = textures.size();
            POINT2D<int> TexturePos = (*RG_Atlas_StandartPtr)[textures[0]].pos;
            POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;

            Lock::Mesh::RG_Buffer::raw.textures.resize(1);

            POINT2D<double> TexCoordArr[4] = {
              {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
              {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
              {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
              {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
            };

            Lock::Mesh::RG_Buffer::raw.textures[0].resize(4);


            Lock::Mesh::RG_Buffer::raw.textures[0].fill(TexCoordArr);
            if (type == TextureStretch)
              // RG_Buffer::raw.vertex = RG::GenRectMesh(RG::GlobalToGL((*RG_Atlas_StandartPtr)[textures[0]].size));
              RG_Buffer::raw.vertex.init(RG::GenRectMesh(RG::GlobalToGL((*RG_Atlas_StandartPtr)[textures[0]].size)));
            else
              //RG_Buffer::raw.vertex = { {-1,1,0},{-1,-1,0},{1,-1,0},{1,1,0} };
              RG_Buffer::raw.vertex.init({ {-1, 1, 0}, {-1, -1, 0}, {1, -1, 0}, {1, 1, 0} });
          } else {
            //RG_Buffer::raw.vertex = { {-1,1,0},{-1,-1,0},{1,-1,0},{1,1,0} };
            RG_Buffer::raw.vertex.init({ {-1, 1, 0}, {-1, -1, 0}, {1, -1, 0}, {1, 1, 0} });
          }

          //RG_Buffer::raw.color = temp;
          RG_Buffer::raw.color.init(temp);
          //RG_Buffer::raw.elements = { 0, 1, 2, 2, 3, 0 };
          Lock::Mesh::RG_Buffer::raw.elements.init({ 0, 1, 2, 2, 3, 0 });

          RG_Buffer::GL_Gen();

        }



        /*void draw(RG_Camera& cam = RG_Camera_StandartPtr) {
          if (RG_Buffer::gl.textures.size() > 0) {
            tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

            if (tempFrame > 1) {
              frame += floor(tempFrame);
              tempFrame -= floor(tempFrame);
            }
            frame = frame % (maxFrames);//textures.size();
            RG_Mods::Texture_On();
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
            rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
          }
          else RG_Mods::Texture_Off();

          if (RG_Buffer::gl.vertex != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
            rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
          }
          else RG_LOG_LOCK_CRITICAL("background vertex == -1");
          if (RG_Buffer::gl.color != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
            rgColorPointer(4, GL_DOUBLE, 0, nullptr);
          }
          else RG_LOG_LOCK_CRITICAL("background color == -1");
          //cam.loadMatrix();


          if (is_gui) {
            rgLoadGuiMatrix(GuiType);
          }
          else {
            //rgLoadCamMatrix();
            cam.loadMatrix();
          }
          rgLoadMatrixf(mat);


          rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
        }*/

        /*void draw(RG_Camera& cam = RG_Camera_StandartPtr) {

          if (RG_Buffer::gl.textures.size() > 0) {
            tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

            if (tempFrame > 1) {
              frame += floor(tempFrame);
              tempFrame -= floor(tempFrame);
            }
            frame = frame % (maxFrames);//textures.size();
            RG_Mods::Texture_On();
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
            rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
          } else RG_Mods::Texture_Off();

          if (RG_Buffer::gl.vertex != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
            rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("background vertex == -1");
          if (RG_Buffer::gl.color != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
            rgColorPointer(4, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("background color == -1");
          //cam.loadMatrix();


          if (is_gui) {
            rgLoadGuiMatrix(GuiType);
          } else {
            //rgLoadCamMatrix();
            cam.loadMatrix();
          }
          rgLoadMatrixf(mat);


          rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
        }*/
      };//BACKGROUND
      class Text :public Lock::Mesh {
        wstring _text;
        int _true_size_text = 0;
        double _offset = 0.1;
        vec2<double> _wordsize;
      public:
        wstring text;
        void set_offset(double offset) {
          _offset = offset;
        }
        struct Set {
          POINT3D<double> pos;
          POINT2D<double> size = { 1, 1 };
          POINT2D<double> scale = { 1, 1 };
          COLOR4D<double> color;
          POINT3D<double> rotate;
          RG_Array<int> textures;
          bool custom_size = false;
          bool is_gui = false;
          LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
          bool is3d = false;
          bool hitbox = false;
          bool collision = false;
          bool animate = false;
          wstring text;
        };
        Text() {}
        void init(Set in) {
          pos = in.pos;
          size = in.size;
          scale = in.scale;
          color = in.color;
          rotate = in.rotate;
          textures = in.textures;
          custom_size = in.custom_size;
          is_gui = in.is_gui;
          GuiType = in.GuiType;
          is3d = in.is3d;
          hitbox = in.hitbox;
          collision = in.collision;
          animate = in.animate;
          // _text = in.text;
          Set_Text(in.text);
        }

        // void to_center() {
        //   pos = { pos.x - (RG_Buffer::raw.vertex[-1].x * scale.x / 2.),pos.y + (RG_Buffer::raw.vertex[-2].y * scale.y * 1.5),pos.z };
        // }
        // void to_center(RG::vec3<double> in) {
        //   pos = { in.x - (RG_Buffer::raw.vertex[-1].x * scale.x / 2.),in.y + (RG_Buffer::raw.vertex[-2].y * scale.y * 1.5) ,in.z };
        // }
        // void to_center(const Mesh& in) {
        //   pos = { in.pos.x - (RG_Buffer::raw.vertex[-1].x * scale.x / 2.),in.pos.y + (RG_Buffer::raw.vertex[-2].y * scale.y * 1.5),in.pos.z };
        // }
        void to_center() {
          pos = { pos.x - (_wordsize.x * scale.x / 2.),pos.y - (_wordsize.y * scale.y / 2.),pos.z };
        }
        void to_center(int i) {
          if (i) {
            pos.y = pos.y + (RG_Buffer::raw.vertex[-1].y * scale.x / 2.);
          } else {
            pos.x = pos.x - (RG_Buffer::raw.vertex[-1].x * scale.x / 2.);
          }
        }
        void to_center(RG::vec3<double> in) {
          pos = { in.x - (_wordsize.x * scale.x / 2.), in.y - (_wordsize.y * scale.y / 2.),in.z };
        }
        void to_center(const Mesh& in) {
          pos = { in.pos.x - (RG_Buffer::raw.vertex[-1].x * scale.x / 2.),in.pos.y - (RG_Buffer::raw.vertex[-2].y * scale.y / 2.),in.pos.z };
        }
        // * Text create
        void Create() {
          Mesh::MatInit();
          Set_Text(text);
        }

        void Set_Text(to_rvalue(wstring) text) {
          this->text = text;
          Set_Text();
        }

        vec2<double> get_word_size() {
          //return _wordsize;
          return _wordsize * scale;
        }
        void Set_Text() {
          //RG_Buffers out;
          if (text.size() > 0 && _text != text) {
            //// <POINT2D<int>> TexturesPos(set.text.size());
            //RG_Array<RG_Letter> letters(set.text.size());
            RG_Buffer::raw.textures.resize(1);
            POINT2D<double> space;
            RG_Buffer::raw.textures[0].reinit(text.size() * 4);
            RG_Buffer::raw.vertex.reinit(text.size() * 4);
            RG_Buffer::raw.color.reinit(text.size() * 4);
            RG_Buffer::raw.elements.reinit(text.size() * 6);
            /*for(int i = 0; i < set.text.size();i++){
              TexturesPos[i] = RG_Atlas_StandartPtr->Font_GetPos(set.text[i]);
            }*/
            // !rgTranslatef(pos.x+((posTemp.x*scale))/RG_MainSizeWindow, pos.y+(((-posTemp.y*scale*2)+(-characters[temp].bias.y +characters[temp].bias.y)) - (RG_SIZEFONT*scale))/RG_MainSizeWindow, (pos.z)*guiSize,matrixs[i]);
            int index = -1;
            // int index = 0;
            for (int i = 0; i < text.size(); i++) {
              if (text[i] == ' ') { space.x += RG_FONT_SIZE / RG_SYS_WINDOWSdow_Virtual / 2.; continue; }
              if (text[i] == '\n') { space.x = 0; space.y += RG_FONT_SIZE / RG_SYS_WINDOWSdow_Virtual; continue; }
              index++;
              const RG_Letter& letter = RG_Atlas_StandartPtr->Font_Get_Letter(text[i]);

              RG_Buffer::raw.vertex[index * 4 + 0] = {
                space.x,
                -space.y - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual,
                0 };

              RG_Buffer::raw.vertex[index * 4 + 1] = {
                space.x,
                -space.y - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual,
                0 };

              RG_Buffer::raw.vertex[index * 4 + 2] = {
                (letter.size.x) / RG_SYS_WINDOWSdow_Virtual + space.x,
                -space.y - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual,
                0 };

              RG_Buffer::raw.vertex[index * 4 + 3] = {
                (letter.size.x) / RG_SYS_WINDOWSdow_Virtual + space.x,
                -space.y - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual,
                0 };

              RG_Buffer::raw.textures[0][index * 4 + 0] = {
                letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x,
                letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y };
              RG_Buffer::raw.textures[0][index * 4 + 1] = {
                letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x,
                letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y + letter.size.y / (double)RG_Atlas_StandartPtr->get_size().y };
              RG_Buffer::raw.textures[0][index * 4 + 2] = {
                letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x + letter.size.x / (double)RG_Atlas_StandartPtr->get_size().x,
                letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y + letter.size.y / (double)RG_Atlas_StandartPtr->get_size().y };
              RG_Buffer::raw.textures[0][index * 4 + 3] = {
                letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x + letter.size.x / (double)RG_Atlas_StandartPtr->get_size().x,
                letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y };

              RG_Buffer::raw.color[index * 4 + 0] = color;
              RG_Buffer::raw.color[index * 4 + 1] = color;
              RG_Buffer::raw.color[index * 4 + 2] = color;
              RG_Buffer::raw.color[index * 4 + 3] = color;
              //space.x += (letter.advance / 64. - letter.bias.x + letter.size.x) / RG_SYS_WINDOWSdow_Virtual;
              space.x += (letter.size.x + letter.bias.x + (RG_FONT_SIZE * _offset)) / RG_SYS_WINDOWSdow_Virtual;
              //space.x+=RG_FONT_SIZE*2;
              RG_Buffer::raw.elements[index * 6 + 0] = index * 4 + 0;
              RG_Buffer::raw.elements[index * 6 + 1] = index * 4 + 1;
              RG_Buffer::raw.elements[index * 6 + 2] = index * 4 + 2;
              RG_Buffer::raw.elements[index * 6 + 3] = index * 4 + 2;
              RG_Buffer::raw.elements[index * 6 + 4] = index * 4 + 3;
              RG_Buffer::raw.elements[index * 6 + 5] = index * 4 + 0;

            }
            index++;
            RG_Buffer::raw.textures[0].resize(index * 4);
            RG_Buffer::raw.vertex.resize(index * 4);
            RG_Buffer::raw.color.resize(index * 4);
            RG_Buffer::raw.elements.resize(index * 6);
            _true_size_text = index;
            _wordsize = { space.x,space.y };
            _text = text;
            RG_Buffer::GL_Gen();
          } else {
            for (int i = 0; i < _true_size_text; i++) {
              RG_Buffer::raw.color[i * 4 + 0] = color;
              RG_Buffer::raw.color[i * 4 + 1] = color;
              RG_Buffer::raw.color[i * 4 + 2] = color;
              RG_Buffer::raw.color[i * 4 + 3] = color;
            }
            RG_Buffer::GL_Regen(GL_INIT_Color);
          }

        }


        /*void draw(RG_Camera& cam = RG_Camera_StandartPtr) {

          if (RG_Buffer::gl.textures.size() > 0) {
            tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

            if (tempFrame > 1) {
              frame += floor(tempFrame);
              tempFrame -= floor(tempFrame);
            }
            frame = frame % (maxFrames);//textures.size();
            RG_Mods::Texture_On();
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
            rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
          } else RG_Mods::Texture_Off();

          if (RG_Buffer::gl.vertex != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
            rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("flat mesh gl vertex == -1");

          if (RG_Buffer::gl.color != -1) {
            glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
            rgColorPointer(4, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("flat mesh gl color == -1");//TODO fix everything
          //cam.loadMatrix();


          //if (_parent == nullptr ? is_gui : _parent->is_gui) {
          if (is_gui) {
            rgLoadGuiMatrix(GuiType);
          } else {
            //rgLoadCamMatrix();
            cam.loadMatrix();
          }
          rgLoadMatrixf(mat);


          rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
        }*/

      };
    }
    namespace Body {
      namespace Lock {
        POINT3D<double>Square3Dvectors[4] = {
          {-1, 1, 0},
          {-1, -1, 0},
          {1, -1, 0},
          {1, 1, 0}
        };

        struct RawMesh : protected RG_Buffer {
          POINT3D<double> pos;
          POINT3D<double> rotate;
          POINT3D<double> size = { 1, 1, 1 };
          POINT3D<double> scale = { 1, 1, 1 };
          COLOR4D<double> color;
        protected:
          RG_Matrix<float> mat;
        };
        struct Mesh :public RawMesh {

          LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;

          RG_Array<int> textures;
          bool is_gui = false;
          bool is3d = false;
        protected:
          uint frame = 0;
          double tempFrame = 0;
          int FrPeSe = 10;
          int maxFrames = 1;
        public:

          // RG_Material material = RG_StandartMaterial;
          bool custom_size = false;
          virtual void MatInit() {
            rgLoadIdentity(mat);
            rgTranslatef(pos.x, pos.y, pos.z, mat);
            rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
            if (textures.size() > 0 && !custom_size) {
              POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;

              size.x = TextureSize.x / RG_SYS_WINDOWSdow_Virtual;
              size.y = TextureSize.y / RG_SYS_WINDOWSdow_Virtual;
              //RG_LOG_LOCK_INFO("Texture has, size = " + to_string(TextureSize.x) + ", " + to_string(TextureSize.y));
            }


            rgScalef(\
              size.x * scale.x, \
              size.y * scale.y, \
              size.z * scale.z, mat);

          }
          void MatUpdate() {
            rgLoadIdentity(mat);
            rgTranslatef(pos.x, pos.y, pos.z, mat);
            rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
            rgScalef(\
              size.x * scale.x, \
              size.y * scale.y, \
              size.z * scale.z, mat);
          }
          virtual void draw(RG_Camera& cam = *RG_Camera_StandartPtr) {

            if (RG_Buffer::gl.textures.size() > 0) {
              tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

              if (tempFrame > 1) {
                frame += floor(tempFrame);
                tempFrame -= floor(tempFrame);
              }
              frame = frame % (maxFrames);//textures.size();
              RG_Mods::Texture_On();
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
              RG_Buffer::gl.textures[frame].bind();
              rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
            } else RG_Mods::Texture_Off();

            if (RG_Buffer::gl.vertex.is_init()) {
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
              RG_Buffer::gl.vertex.bind();
              rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
            } else RG_LOG_LOCK_CRITICAL("3d mesh vertex == -1");
            if (RG_Buffer::gl.color.is_init()) {
              // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
              RG_Buffer::gl.color.bind();
              rgColorPointer(4, GL_DOUBLE, 0, nullptr);
            } else RG_LOG_LOCK_CRITICAL("3d mesh color == -1");//TODO fix everything
            //cam.loadMatrix();


            if (is_gui) {
              rgLoadGuiMatrix(GuiType);
            } else {
              //rgLoadCamMatrix();
              cam.loadMatrix();
            }
            rgLoadMatrixf(mat);


            rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
          }
        };
      }
      class Object :public Lock::Mesh {
        /*enum Mode {
          MNone,
          MVector,
          MVectorFill,
          MTexture,
          MTextureFill,
          MColor,
          MColorFill,
          MElement,
          MElementFill,
          MNormal,
          MNormalFill,
          MPolygon,
          MPolygonFill
        };*/
        enum Mode {
          MNone,
          MVector,
          MTexture,
          MElement,
          MElementFill,
          MNormal,
          MNormalFill,
          MPolygon,
          MPolygonFill
        };

      public:


        void Load(string path) {

        }

        /* void Load(string path) {
           string typefile = RG::GetTypePath(path);
           string  file = RG::FileLoad(path), temp;
           if (typefile == "obj") {

             int vectorSize = 0, normalSize = 0, textureSize = 0, polygonSize = 0;

             for (int i = 0; i < file.size();i++) {
               char in = file[i];
               if (in > 32) {
                 temp += in;
               } else {
                 if (temp.size() > 0) {
                   if (temp == "v") {
                     vectorSize++;
                   }elif(temp == "vn") {
                     normalSize++;
                   }elif(temp == "vt") {
                     textureSize++;
                   }elif(temp == "f") {
                     polygonSize++;
                   }
                   temp.clear();
                 }
               }
             }

             RG_Buffer::raw.vertex.resize(polygonSize);
             RG_Buffer::raw.textures.resize(1); RG_Buffer::raw.textures[0].resize(polygonSize);
             RG_Buffer::raw.normal.resize(polygonSize);
             RG_Array<POINT3D<double>>vertex(vectorSize * 3);
             RG_Array<POINT3D<double>>normal(normalSize * 3);
             RG_Array<POINT2D<double>>textures(textureSize * 2);
             RG_Array<POINT3D<POINT3D<uint>>>polygon(polygonSize * 3 * 3);
             uint veci = 0, texi = 0, nori = 0, poli = 0;

             Mode mode = MNone;

             for (int i = 0; i < file.size();i++) {
               char in = file[i];
               if (in != '\n' || i != file.size() - 1) {
                 temp += in;
               } else {

                 if (temp[0] == 'v') {
                   if (temp[1] == 'n')mode = MNormal;
                   elif(temp[1] == 't')mode = MTexture;
                   else mode = MVector;
                 }elif(temp[0] == 'f')mode = MPolygon;

                 string temp2;
                 for (int j = 1; j < temp.size();j++) {
                   if (temp[j] > 32) {
                     temp2 += temp[j];
                   } else {
                     if (temp2.size() > 0) {
                       if (mode == MVector) {
                         vertex[veci].x = stod(temp2);
                         veci++;
                       }elif(mode == MNormal) {
                         normal[nori].x = stod(temp2);
                         nori++;
                       }elif(mode == MTexture) {
                         textures[texi].x = stod(temp2);
                         texi++;
                       }elif(mode == MPolygon) {
                         polygon[poli].x.x = stod(temp2);
                         poli++;
                       }
                     }
                   }
                 }
               }
             }




           }elif(typefile == "rgobj") {
             RG_LOG_LOCK_CRITICAL("rgobj is not supported yet");
           } else {
             RG_LOG_LOCK_CRITICAL(typefile + " is not supported, send me feedback if this type is worth adding https://t.me/T_Rinemest");
           }
         }*/
         /*void Load(string path) {
           string typefile;
           if ((typefile = RG::GetTypePath(path)) == "obj") {

             string  file = FileLoad(path),
               temp;

             Mode mode = MNone;
             int vectorSize = 0, normalSize = 0, textureSize = 0, polygonSize = 0;
             for (int i = 0; i < file.size();i++) {
               char in = file[i];
               if (in > 32 && in != '/') {
                 temp += in;
               }
               else {
                 if (temp == "v") {
                   vectorSize++;
                 }elif(temp == "vn") {
                   normalSize++;
                 }elif(temp == "vt") {
                   textureSize++;
                 }elif(temp == "f") {
                   polygonSize++;
                 }

                 temp.clear();
               }
             }
             //RG_Buffer::raw.color.resize(polygonSize);

             RG_Buffer::raw.vertex.resize(polygonSize);
             RG_Buffer::raw.textures.resize(1);
             RG_Buffer::raw.textures[0].resize(polygonSize);
             RG_Buffer::raw.normal.resize(polygonSize);
             uint veci = 0, texi = 0, nori = 0, poli = 0;
             RG_Array<double>vertex(vectorSize * 3);
             RG_Array<double>normal(normalSize * 3);
             RG_Array<double>textures(textureSize * 2);
             RG_Array<uint>polygon(polygonSize * 3 * 3);
             for (int i = 0; i < file.size();i++) {
               char in = file[i];
               if (in > 32) {
                 temp += in;
               }
               else {
                 // logica text type
                 if (mode == MNone) {
                   if (temp == "v") {
                     mode = MVector;
                   }elif(temp == "vn") {
                     mode = MNormal;
                   }elif(temp == "vt") {
                     mode = MTexture;
                   }elif(temp == "f") {
                     mode = MPolygon;
                   }
                 }
                 else {
                   switch (mode) {
                   case MVector:
                   vertex[veci] = stod(temp);
                   veci++;
                   break;
                   case MNormal:
                   normal[nori] = stod(temp);
                   nori++;
                   break;
                   case MTexture:
                   textures[texi] = stod(temp);
                   texi++;
                   break;
                   case MPolygon:
                   polygon[poli] = stoi(temp);
                   poli++;
                   break;
                   default:
                   RG_LOG_LOCK_ERROR("Error mode by load model, mode error is " + to_string(mode));
                   }
                   temp.clear();
                   if (in == '\n') {
                     // update case
                     continue;
                   }
                 }
               }
             }
             for (int i = 0;i < polygonSize;i++) {
               RG_Buffer::raw.vertex[i].x = vertex[polygon[i] * 3];//i = 1/2/3, 3+0 = 1/... ,
               RG_Buffer::raw.vertex[i].y = vertex[polygon[i] * 3];
               RG_Buffer::raw.vertex[i].z = vertex[polygon[i] * 3];

               RG_Buffer::raw.textures[0][i].x =textures[polygon[i * 3 + 0 * 3 + 1]*2];
               RG_Buffer::raw.textures[0][i].y =textures[polygon[i * 3 + 1 * 3 + 1]*2];

               RG_Buffer::raw.normal[i].x = normal[polygon[i * 3 + 0 * 3 + 2]*3];
               RG_Buffer::raw.normal[i].y = normal[polygon[i * 3 + 1 * 3 + 2]*3];
               RG_Buffer::raw.normal[i].z = normal[polygon[i * 3 + 2 * 3 + 2]*3];

             }
           }elif(typefile == "rgobj") {
             RG_LOG_LOCK_CRITICAL("rgobj is not supported yet");
           }
           else {
             RG_LOG_LOCK_CRITICAL(typefile + " is not supported, send me feedback if this type is worth adding https://t.me/T_Rinemest");
           }
         }*/


        void Create() {
          if (!RG_Buffer::raw.elements.size())RG_LOG_LOCK_CRITICAL("Body::Object not loaded");
          Mesh::MatInit();
          GL_Gen();
        }
        void draw(RG_Camera& cam = *RG_Camera_StandartPtr) {
          if (RG_Buffer::gl.textures.size() > 0) {
            tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

            if (tempFrame > 1) {
              frame += floor(tempFrame);
              tempFrame -= floor(tempFrame);
            }
            frame = frame % (maxFrames);//textures.size();
            RG_Mods::Texture_On();
            // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.textures[frame]);
            RG_Buffer::gl.textures[frame].bind();
            rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
          } else RG_Mods::Texture_Off();

          if (RG_Buffer::gl.vertex.is_init()) {
            // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.vertex);
            RG_Buffer::gl.vertex.bind();
            rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("background vertex == -1");
          if (RG_Buffer::gl.color.is_init()) {
            // glBindBuffer(GL_ARRAY_BUFFER, RG_Buffer::gl.color);
            RG_Buffer::gl.color.bind();
            rgColorPointer(4, GL_DOUBLE, 0, nullptr);
          } else RG_LOG_LOCK_CRITICAL("background color == -1");//TODO fix everything
          //cam.loadMatrix();


          rgLoadMatrixf(mat);
          if (is_gui) {
            rgLoadGuiMatrix(GuiType);
          } else {
            //rgLoadCamMatrix();
            cam.loadMatrix();
          }


          rgDrawElements(GL_TRIANGLES, RG_Buffer::raw.elements.size(), GL_UNSIGNED_INT, RG_Buffer::raw.elements.get_arr());
        }

      };
      class Mesh :public Lock::Mesh {
      public:
        void set_pos(POINT3D<double>pos_in, bool upd = false) {
          pos = pos_in;
          if (upd)MatUpdate();
        }
        void set_rotate(POINT3D<double>rotate_in, bool upd = false) {
          rotate = rotate_in;
          if (upd)MatUpdate();
        }
        void set_size(POINT3D<double>size_in, bool upd = false) {
          size = size_in;
          if (upd)MatUpdate();
        }
        void set_scale(POINT3D<double>scale_in, bool upd = false) {
          scale = scale_in;
          if (upd)MatUpdate();
        }
        void Update() {
          MatUpdate();
        }
        struct Set {
          POINT3D<double> pos;
          POINT3D<double> size = { 1, 1 };
          POINT3D<double> scale = { 1, 1 };
          COLOR4D<double> color;
          POINT3D<double> rotate;
          RG_Array<int> textures;
          bool custom_size = false;
          bool is_gui = false;
          LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
          bool is3d = false;
          bool hitbox = false;
          bool collision = false;
          bool animate = false;
          RG_Array<POINT3D<double>> mesh;
          RG_Array<COLOR4D<double>> color_mesh;
          RG_Array<RG_Array<POINT2D<double>>>texture_coord;
          RG_Array<uint> elements;
        };

        void init(Set in) {
          pos = in.pos;
          size = in.size;
          scale = in.scale;
          color = in.color;
          rotate = in.rotate;
          textures = in.textures;
          custom_size = in.custom_size;
          is_gui = in.is_gui;
          GuiType = in.GuiType;
          is3d = in.is3d;
          // hitbox = in.hitbox;
          // collision = in.collision;
          // animate = in.animate;
          if (in.mesh.size() > 0) {
            RG_Buffer::raw.vertex = in.mesh;
          }
          if (in.elements.size())RG_Buffer::raw.elements = in.elements;
          if (in.texture_coord.size()) {
            RG_Buffer::raw.textures.resize(in.texture_coord.size());
            for (int i = 0; i < in.texture_coord.size(); i++) {
              RG_Buffer::raw.textures[i].resize(in.texture_coord[i].size());
              for (int j = 0; j < in.texture_coord[i].size(); j++) {
                RG_Buffer::raw.textures[i][j].x = ((in.texture_coord[i][j].x * RG_Atlas_Standart[textures[i]].size.x) + (RG_Atlas_Standart[textures[i]].pos.x)) / RG_Atlas_Standart.get_size().x;
                RG_Buffer::raw.textures[i][j].y = ((in.texture_coord[i][j].y * RG_Atlas_Standart[textures[i]].size.y) + (RG_Atlas_Standart[textures[i]].pos.y)) / RG_Atlas_Standart.get_size().y;
              }
            }
            // if (in.texture_coord.size()){
            //   RG_Buffer::raw.textures.push_back(in.texture_coord);
            // }

          }
          if (in.color_mesh.size())RG_Buffer::raw.color = in.color_mesh;
        }
        void paint() {
          Lock::Mesh::RG_Buffer::raw.color.fill(Lock::Mesh::color);
          Lock::Mesh::RG_Buffer::GL_Regen(GL_INIT_Color);
        }
        void paint(COLOR4D<double> col) {
          if (col != Lock::Mesh::color) {
            Lock::Mesh::color = col;
            Lock::Mesh::RG_Buffer::raw.color.fill(Lock::Mesh::color);
            Lock::Mesh::RG_Buffer::GL_Regen(GL_INIT_Color);
          }
        }
        // void MatInit() {
        //   rgLoadIdentity(mat);
        //   rgTranslatef(pos.x, pos.y, pos.z, mat);
        //   rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
        //   // if (textures.size() > 0 && !custom_size) {
        //   //   POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;

        //   //   size.x = TextureSize.x / RG_SYS_WINDOWSdow_Virtual;
        //   //   size.y = TextureSize.y / RG_SYS_WINDOWSdow_Virtual;
        //   //   //RG_LOG_LOCK_INFO("Texture has, size = " + to_string(TextureSize.x) + ", " + to_string(TextureSize.y));
        //   // }


        //   rgScalef(\
        //     size.x * scale.x, \
        //     size.y * scale.y, \
        //     size.z * scale.z, mat);

        // }
        void Create() {
          /*--------------*/
          //COLOR4D<double>coltemp[4] = { color, color, color, color };//glColor

          if (maxFrames <= 0)RG_LOG_LOCK_CRITICAL("maxFrames<=0");
          if (frame >= maxFrames)RG_LOG_LOCK_CRITICAL("frame>=maxFrames");
          // Lock::Mesh::RG_Buffer::raw.color.init(4, Lock::Mesh::color);
          if (Lock::Mesh::RG_Buffer::raw.vertex.size()) {
            if (!Lock::Mesh::RG_Buffer::raw.elements.size()) {
              Lock::Mesh::RG_Buffer::raw.elements.resize(Lock::Mesh::RG_Buffer::raw.vertex.size());
              if (!Lock::Mesh::RG_Buffer::raw.color.size()) {
                Lock::Mesh::RG_Buffer::raw.color.init(Lock::Mesh::RG_Buffer::raw.elements.size(), color);

                for (int i = 0; i < Lock::Mesh::RG_Buffer::raw.elements.size(); i++) {
                  Lock::Mesh::RG_Buffer::raw.elements[i] = i;
                }
              } else {
                for (int i = 0; i < Lock::Mesh::RG_Buffer::raw.elements.size(); i++) {
                  Lock::Mesh::RG_Buffer::raw.elements[i] = i;
                }
              }
            } else {
              if (!Lock::Mesh::RG_Buffer::raw.color.size()) {
                Lock::Mesh::RG_Buffer::raw.color.init(Lock::Mesh::RG_Buffer::raw.elements.size(), color);

              }

            }
          } else {
            Lock::Mesh::RG_Buffer::raw.elements.init({ 0, 1, 2, 2, 3, 0 });
            Lock::Mesh::RG_Buffer::raw.vertex.init(4, Lock::Square3Dvectors);
            if (!Lock::Mesh::RG_Buffer::raw.color.size()) {
              Lock::Mesh::RG_Buffer::raw.color.init(Lock::Mesh::RG_Buffer::raw.elements.size(), color);
            }
          }
          if (!Lock::Mesh::RG_Buffer::raw.vertex.size()) {
            RG_LOG_LOCK_ERROR("raw buffer vertex has empty");
          } if (!Lock::Mesh::RG_Buffer::raw.color.size()) {
            RG_LOG_LOCK_ERROR("raw buffer color has empty");
          } if (!Lock::Mesh::RG_Buffer::raw.elements.size()) {
            RG_LOG_LOCK_ERROR("raw buffer elements has empty");
          }
          MatInit();
          Lock::Mesh::RG_Buffer::GL_Gen();
          // if (textures.size() > 0) {

          //   maxFrames = textures.size();
          //   POINT2D<int> TexturePos;
          //   POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;
          //   if (Lock::Mesh::RG_Buffer::raw.textures.size() != textures.size()) {
          //     Lock::Mesh::RG_Buffer::raw.textures.resize(textures.size());
          //     // }
          //     int i = 0;
          //     for (int t : textures) {

          //       TexturePos = (*RG_Atlas_StandartPtr)[t].pos;

          //       TextureSize = (*RG_Atlas_StandartPtr)[t].size;

          //       POINT2D<double> TexCoordArr[4] = {
          //         {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
          //         {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
          //         {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
          //         {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
          //       };

          //       Lock::Mesh::RG_Buffer::raw.textures[i].resize(4);

          //       Lock::Mesh::RG_Buffer::raw.textures[i].fill(TexCoordArr);


          //       i++;
          //     }

          //   }


          // }


          /*---------------*/
          // if (!RG_Buffer::raw.elements.size())RG_LOG_LOCK_CRITICAL("Body::Object not loaded");
          // Lock::Mesh::MatInit();
          // Lock::Mesh::RG_Buffer::GL_Gen();
        }
      };
    };
  }
}



//class RG_Object{
// namespace RG_Object {
//   struct PRaw {
//     RG_Array<POINT3D<double>> vertex;
//     RG_Array<COLOR4D<double>> color;
//     RG_Array<POINT2D<double>> texture;
//     RG_Array<uint> elements;
//   };
//   struct Raw {
//     RG_Array<double> vertex;
//     RG_Array<double> color;
//     RG_Array<double> texture;
//     RG_Array<uint> elements;
//   };
//   POINT3D<double>Square3Dvectors[4] = {
//     {-1, 1, 0},
//     {-1, -1, 0},
//     {1, -1, 0},
//     {1, 1, 0}
//   };
//   /*uint SquareElemets[6]={
//     0,1,2,
//     2,3,0
//   };*/
//   RG_Array<uint> SquareElemets{ 0, 1, 2, 2, 3, 0 };

//   class Standart {
//   public:
//     POINT3D<double> pos;
//     POINT3D<double> rotate;
//     POINT3D<double> size = { 1, 1, 1 };
//     POINT3D<double> scale = { 1, 1, 1 };
//     LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
//     COLOR4D<double> color;
//     //RG_Texture tex;
//     RG_Array<int> textures;
//     RG_Matrix<float> mat;
//     bool is_gui = false;
//     bool is3d = false;
//     uint frame = 0;
//     double tempFrame = 0;
//     int FrPeSe = 10;
//     int maxFrames = 1;

//     /*struct RG_Buffers{
//       //int gl_tx_id = -1;
//       RG_Array<RG_Array<POINT2D<double>>>textures;
//       RG_Array<POINT3D<double>> vertex;
//       RG_Array<COLOR4D<double>> color;
//       RG_Array<uint> elements;
//     }buffers.raw;*/
//     RG_Buffer buffers;


//     /*struct RG_GLBuffers{
//       RG_Array<uint>textures;
//       uint vertex = INT32_MAX, color = INT32_MAX;
//     }buffers.gl;*/

//     RG_Material material = RG_StandartMaterial;
//     bool INIT = false;

//     struct Settings {
//       POINT3D<double> pos;
//       POINT3D<double> size = { 1, 1, 1 };
//       POINT3D<double> rotate;
//       POINT3D<double> scale = { 1, 1, 1 };
//       COLOR4D<double> color;
//       RG_Array<int> textures;
//       bool custom_size = false;
//       bool gui = false;
//       LINK_GUI_TYPE gui_type = RG_GUI_LINK_NONE;
//       bool is3d = false;
//     };
//     void init(to_rvalue(Settings) sett) {
//       pos = sett.pos;
//       size = sett.size;
//       rotate = sett.rotate;
//       scale = sett.scale;
//       color = sett.color;
//       textures = sett.textures;
//       // custom_size = sett.custom_size;
//       is_gui = sett.gui;
//       GuiType = sett.gui_type;
//       is3d = sett.is3d;
//       INIT = 1;
//     }
//   };

//   class Sprite :private Standart {
//   public:

//     Settings set;

//     void Create() {
//       Create(set);
//     }
//     void Create(to_rvalue(Settings) sett) {
//       init(sett);
//       COLOR4D<double>coltemp[4] = { color, color, color, color };//glColor
//       rgLoadIdentity(mat);
//       rgTranslatef(pos.x, pos.y, pos.z, mat);
//       rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
//       if (textures.size() > 0) {
//         maxFrames = textures.size();
//         POINT2D<int> TexturePos;// = RG_Atlas_StandartPtr->tx()[t].pos;
//         //rg_cout<<RG_Atlas_StandartPtr->get_textures().size()<<endl;

//         POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;// = RG_Atlas_StandartPtr->tx()[t].size;

//         buffers.gl.textures.resize(textures.size());
//         size.x = TextureSize.x / RG_SYS_WINDOWSdow_Size_Standart;
//         size.y = TextureSize.y / RG_SYS_WINDOWSdow_Size_Standart;
//         rgScalef(
//           size.x * scale.x,
//           size.y * scale.y,
//           size.z * scale.z, mat);

//         //rg_cout<<size.x * scale.x<<" "<<size.y * scale.y<<endl;
//         int i = 0;
//         for (int t : textures) {
//           rg_cout << t << endl;
//           TexturePos = (*RG_Atlas_StandartPtr)[t].pos;
//           TextureSize = (*RG_Atlas_StandartPtr)[t].size;

//           POINT2D<double> TexCoordArr[6] = {
//             {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
//             {(TexturePos.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
//             {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y + TextureSize.y) / (double)RG_Atlas_StandartPtr->get_size().y},
//             {(TexturePos.x + TextureSize.x) / (double)RG_Atlas_StandartPtr->get_size().x, (TexturePos.y) / (double)RG_Atlas_StandartPtr->get_size().y},
//           };
//           buffers.gl.textures[i] = BufferLoad<POINT2D<double>>(sizeof(TexCoordArr), TexCoordArr, GL_STATIC_DRAW);

//           i++;
//         }


//       } else {

//         rgScalef(\
//           size.x * scale.x, \
//           size.y * scale.y, \
//           size.z * scale.z, mat);
//       }


//       buffers.gl.vertex = BufferLoad<POINT3D<double>>(sizeof(Square3Dvectors), Square3Dvectors, GL_STATIC_DRAW);
//       buffers.gl.color = BufferLoad<COLOR4D<double>>(sizeof(coltemp), coltemp, GL_STATIC_DRAW);
//       buffers.raw.elements.init(SquareElemets);

//       if (maxFrames <= 0)RG_LOG_LOCK_CRITICAL("maxFrames<=0");
//       if (frame >= maxFrames)RG_LOG_LOCK_CRITICAL("frame>=maxFrames");
//     }


//     void update() {
//       rgLoadIdentity(mat);
//       rgTranslatef(pos.x, pos.y, pos.z, mat);
//       rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);

//       if (textures.size() > 0) {

//         POINT2D<int> TextureSize = (*RG_Atlas_StandartPtr)[textures[0]].size;

//         size.x = TextureSize.x / RG_SYS_WINDOWSdow_Size_Standart;
//         size.y = TextureSize.y / RG_SYS_WINDOWSdow_Size_Standart;

//       }
//       rgScalef(
//         size.x * scale.x,
//         size.y * scale.y,
//         size.z * scale.z, mat);
//     }

//     void to_rotate(POINT3D<double>rot, bool upd = 0) {
//       rotate.x += rot.x;
//       rotate.y += rot.y;
//       rotate.z += rot.z;
//       if (upd)update();
//     }
//     void set_rotate(POINT3D<double> rot, bool upd = 0) {
//       rotate = rot;
//       if (upd)update();
//     }

//     void set_scale(POINT3D<double> sc, bool upd = 0) {
//       scale = sc;
//       if (upd)update();
//     }
//     void set_pos(POINT3D<double>poss, bool upd = 0) {
//       pos = poss;
//       if (upd)update();
//     }
//     void move(POINT3D<double>move, bool upd = 0) {
//       pos.x += move.x;
//       pos.y += move.y;
//       pos.z += move.z;
//       if (upd)update();
//     }

//     void draw(RG_Camera& cam = *RG_Camera_StandartPtr) {

//       if (buffers.gl.textures.size() > 0) {
//         tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

//         if (tempFrame > 1) {
//           frame += floor(tempFrame);
//           tempFrame -= floor(tempFrame);
//         }
//         frame = frame % (maxFrames);//textures.size();
//         RG_Mods::Texture_On();
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.textures[frame]);
//         rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
//       } else RG_Mods::Texture_Off();

//       if (buffers.gl.vertex != -1) {
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.vertex);
//         rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
//       } else RG_LOG_LOCK_CRITICAL("background vertex == -1");
//       if (buffers.gl.color != -1) {
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.color);
//         rgColorPointer(4, GL_DOUBLE, 0, nullptr);
//       } else RG_LOG_LOCK_CRITICAL("background color == -1");
//       //cam.loadMatrix();


//       if (is_gui) {
//         rgLoadGuiMatrix(GuiType);
//       } else {
//         //rgLoadCamMatrix();
//         cam.loadMatrix();
//       }
//       rgLoadMatrixf(mat);


//       rgDrawElements(GL_TRIANGLES, buffers.raw.elements.size(), GL_UNSIGNED_INT, buffers.raw.elements.get_arr());
//     }

//     int action(bool sticky = false) {


//       POINT2D<double>HPos;

//       if (is_gui) {
//         if (GuiType == RG_GUI_LINK_LEFT_TOP) { HPos.x = 0; HPos.y = 0; }
//         if (GuiType == RG_GUI_LINK_LEFT_CENTER) { HPos.x = 0; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.; }
//         if (GuiType == RG_GUI_LINK_LEFT_BOTTOM) { HPos.x = 0; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y; }

//         if (GuiType == RG_GUI_LINK_CENTER_TOP) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = 0; }
//         if (GuiType == RG_GUI_LINK_CENTER_CENTER) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.; }
//         if (GuiType == RG_GUI_LINK_CENTER_BOTTOM) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y; }

//         if (GuiType == RG_GUI_LINK_RIGHT_TOP) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x; HPos.y = 0; }
//         if (GuiType == RG_GUI_LINK_RIGHT_CENTER) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.; }
//         if (GuiType == RG_GUI_LINK_RIGHT_BOTTOM) { HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y; }
//       } else {
//         HPos.x = RG_SYS_WINDOWSdow_Standart->set().resolution.x / 2.; HPos.y = RG_SYS_WINDOWSdow_Standart->set().resolution.y / 2.;
//       }

//       POINT3D <double>SIZE;

//       SIZE.x = size.x * RG_SYS_WINDOWSdow_Standart->set().resolution.x * scale.x * ((float)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x);
//       SIZE.y = size.y * RG_SYS_WINDOWSdow_Standart->set().resolution.y * scale.y;
//       SIZE.z = size.z * scale.z;



//       POINT2D<double> LeftTop = {
//         (HPos.x + (pos.x / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.x) * ((float)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x) - (SIZE.x / 2)),
//         (HPos.y + (-pos.y / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.y)) - (SIZE.y / 2.)
//       };

//       POINT2D<double> RightBottom
//       {
//         (HPos.x + ((pos.x / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.x)) * ((float)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x)) + (SIZE.x / 2.),
//         (HPos.y + (-pos.y / 2. * RG_SYS_WINDOWSdow_Standart->set().resolution.y)) + (SIZE.y / 2.)
//       };

//       if (MPos.x > LeftTop.x && MPos.x < RightBottom.x) {
//         if (MPos.y > LeftTop.y && MPos.y < RightBottom.y) {
//           if (RG_MOUSE[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS) { if (!sticky)RG_MOUSE[GLFW_MOUSE_BUTTON_1] = GLFW_RELEASE;return 2; } else return 1;
//         }
//       }


//       return 0;
//     }
//   };


//   //public:
//   class Background : private Standart {

//   public:
//     enum Types {
//       None,
//       GradientHorizontal,
//       GradientVertical,
//     };
//     struct Settings :public Standart::Settings {
//       Types type;
//       COLOR4D<double>color1;
//       COLOR4D<double>color2;
//     };
//     Settings set;

//     void Create() {
//       Types type = set.type;
//       COLOR4D<double>color1 = set.color1;
//       COLOR4D<double>color2 = set.color2;

//       INIT = true;
//       RG_Array<COLOR4D<double>> temp;

//       is_gui = true;
//       switch (type) {
//         case GradientHorizontal:
//           temp = { color1, color1, color2, color2 };
//           break;

//         case GradientVertical:
//           temp = { color1, color2, color2, color1 };
//           break;
//         default:
//           temp = { color1, color1, color1, color1 };
//           break;
//       }
//       mat.fill(4, 4, IdentityMat);
//       rgTranslatef(0, 0, 1, mat);
//       buffers.gl.vertex = BufferLoad<POINT3D<double>>(sizeof(Square3Dvectors), Square3Dvectors, GL_STATIC_DRAW);
//       buffers.gl.color = BufferLoad<COLOR4D<double>>(temp.size() * sizeof(COLOR4D<double>), temp.get_arr(), GL_STATIC_DRAW);
//       buffers.raw.elements.init(SquareElemets);
//     }
//     void Create(to_rvalue(Settings) sett) {
//       init(sett);
//       Create();
//     }


//     void draw(RG_Camera& cam = *RG_Camera_StandartPtr) {
//       if (buffers.gl.textures.size() > 0) {
//         RG_Mods::Texture_On();
//         //glBindBuffer(GL_ARRAY_BUFFER,buffers.gl.texture[buffers.gl.animNum()]);
//         rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
//       } else RG_Mods::Texture_Off();

//       if (buffers.gl.vertex != -1) {
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.vertex);
//         rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
//       } else RG_LOG_LOCK_CRITICAL("background vertex == -1");
//       if (buffers.gl.color != -1) {
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.color);
//         rgColorPointer(4, GL_DOUBLE, 0, nullptr);
//       } else RG_LOG_LOCK_CRITICAL("background color == -1");
//       //cam.loadMatrix();


//       if (is_gui) {
//         rgLoadGuiMatrix(GuiType);
//       } else {
//         //rgLoadCamMatrix();
//         cam.loadMatrix();
//       }
//       rgLoadMatrixf(mat);


//       rgDrawElements(GL_TRIANGLES, buffers.raw.elements.size(), GL_UNSIGNED_INT, buffers.raw.elements.get_arr());
//     }

//   };

//   class Text : private Standart {
//   public:
//     // * Text settings
//     struct Settings :public Standart::Settings {
//       wstring text = L"Empty";
//     };
//     Settings set;
//     // * Text create
//     void Create() {
//       if (!INIT)init();
//       //COLOR4D<double>coltemp[4] = {color, color, color, color};//glColor
//       rgLoadIdentity(mat);
//       rgTranslatef(pos.x, pos.y, pos.z, mat);
//       rgRotatef(rotate.x, 1, 0, 0, mat); rgRotatef(rotate.y, 0, 1, 0, mat); rgRotatef(rotate.z, 0, 0, 1, mat);
//       rgScalef(\
//         size.x * scale.x, \
//         size.y * scale.y, \
//         size.z * scale.z, mat);
//       //buffers.raw = Set_Text(set.text);
//       Set_Text(set.text);

//     }
//     void Create(to_rvalue(Settings) sett) {
//       init(sett);
//       Create();
//     }
//     // * init
//     //void init(Settings sett) : public Standart::init(sett){

//     void init(to_rvalue(Settings) sett) {
//       Standart::init(sett);
//       set.text = sett.text;
//     }

//     void init() {
//       init(set);
//     }
//     // * for text
//     /*PRaw Set_Text(to_rvalue(wstring) text){
//       set.text = text;
//       return Set_Text();
//     }*/
//     void Set_Text(to_rvalue(wstring) text) {
//       set.text = text;
//       Set_Text();
//     }
//     /*void Set_Text(){
//       if(set.text.size() > 0){
//         POINT3D<double> space;
//         buffers.raw.elements.reinit(set.text.size() * 6);
//         buffers.raw.color.reinit(set.text.size() * 4);
//         buffers.raw.offset.reinit(set.text.size() * 4);
//         for(int i = 0; i < set.text.size();i++){
//           if(set.text[i] == ' '){ space.x += RG_FONT_SIZE / RG_SYS_WINDOWSdow_Virtual / 2.;continue; }
//           if(set.text[i] == '\n'){ space.x = 0;space.y += RG_FONT_SIZE / RG_SYS_WINDOWSdow_Virtual;continue; }

//           RG_Letter& letter = RG_Atlas_StandartPtr->Font_Get_Letter(set.text[i]);
//           buffers.raw.elements[i * 6 + 0] = (letter.let / 4) + 0;
//           buffers.raw.elements[i * 6 + 1] = (letter.let / 4) + 1;
//           buffers.raw.elements[i * 6 + 2] = (letter.let / 4) + 2;
//           buffers.raw.elements[i * 6 + 3] = (letter.let / 4) + 2;
//           buffers.raw.elements[i * 6 + 4] = (letter.let / 4) + 3;
//           buffers.raw.elements[i * 6 + 5] = (letter.let / 4) + 0;

//           buffers.raw.color[i * 4 + 0] = set.color;
//           buffers.raw.color[i * 4 + 1] = set.color;
//           buffers.raw.color[i * 4 + 2] = set.color;
//           buffers.raw.color[i * 4 + 3] = set.color;

//           buffers.raw.offset[i * 4 + 0] = space;
//           buffers.raw.offset[i * 4 + 1] = space;
//           buffers.raw.offset[i * 4 + 2] = space;
//           buffers.raw.offset[i * 4 + 3] = space;

//           space.x += (letter.size.x) / RG_SYS_WINDOWSdow_Virtual;
//         }
//         buffers.GL_Gen();
//       }
//     }*/

//     void Set_Text() {
//       //RG_Buffers out;
//       if (set.text.size() > 0) {
//         //// <POINT2D<int>> TexturesPos(set.text.size());
//         //RG_Array<RG_Letter> letters(set.text.size());
//         buffers.raw.textures.resize(1);
//         POINT2D<double> space;
//         buffers.raw.textures[0].resize(set.text.size() * 4);
//         buffers.raw.vertex.resize(set.text.size() * 4);
//         buffers.raw.color.resize(set.text.size() * 4);
//         buffers.raw.elements.resize(set.text.size() * 6);
//         /*for(int i = 0; i < set.text.size();i++){
//           TexturesPos[i] = RG_Atlas_StandartPtr->Font_GetPos(set.text[i]);
//         }*/
//         // !rgTranslatef(pos.x+((posTemp.x*scale))/RG_MainSizeWindow, pos.y+(((-posTemp.y*scale*2)+(-characters[temp].bias.y +characters[temp].bias.y)) - (RG_SIZEFONT*scale))/RG_MainSizeWindow, (pos.z)*guiSize,matrixs[i]);
//         for (int i = 0; i < set.text.size();i++) {
//           if (set.text[i] == ' ') { space.x += RG_FONT_SIZE / RG_SYS_WINDOWSdow_Virtual / 2.;continue; }
//           if (set.text[i] == '\n') { space.x = 0;space.y += RG_FONT_SIZE / RG_SYS_WINDOWSdow_Virtual;continue; }
//           const RG_Letter& letter = RG_Atlas_StandartPtr->Font_Get_Letter(set.text[i]);

//           buffers.raw.vertex[i * 4 + 0] = {
//             space.x,
//             -space.y - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual, 0 };
//           buffers.raw.vertex[i * 4 + 1] = {
//             space.x,
//             -space.y - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual, 0 };
//           buffers.raw.vertex[i * 4 + 2] = {
//             (letter.size.x) / RG_SYS_WINDOWSdow_Virtual + space.x,
//             -space.y - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual, 0 };
//           buffers.raw.vertex[i * 4 + 3] = {
//             (letter.size.x) / RG_SYS_WINDOWSdow_Virtual + space.x,
//             -space.y - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual, 0 };

//           buffers.raw.textures[0][i * 4 + 0] = { letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x, letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y };
//           buffers.raw.textures[0][i * 4 + 1] = { letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x, letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y + letter.size.y / (double)RG_Atlas_StandartPtr->get_size().y };
//           buffers.raw.textures[0][i * 4 + 2] = { letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x + letter.size.x / (double)RG_Atlas_StandartPtr->get_size().x, letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y + letter.size.y / (double)RG_Atlas_StandartPtr->get_size().y };
//           buffers.raw.textures[0][i * 4 + 3] = { letter.pos.x / (double)RG_Atlas_StandartPtr->get_size().x + letter.size.x / (double)RG_Atlas_StandartPtr->get_size().x, letter.pos.y / (double)RG_Atlas_StandartPtr->get_size().y };

//           buffers.raw.color[i * 4 + 0] = set.color;
//           buffers.raw.color[i * 4 + 1] = set.color;
//           buffers.raw.color[i * 4 + 2] = set.color;
//           buffers.raw.color[i * 4 + 3] = set.color;
//           //space.x += (letter.advance / 64. - letter.bias.x + letter.size.x) / RG_SYS_WINDOWSdow_Virtual;
//           space.x += (letter.size.x) / RG_SYS_WINDOWSdow_Virtual;
//           //space.x+=RG_FONT_SIZE*2;

//         }
//         for (int i = 0; i < set.text.size();i++) {
//           buffers.raw.elements[i * 6 + 0] = i * 4 + 0;
//           buffers.raw.elements[i * 6 + 1] = i * 4 + 1;
//           buffers.raw.elements[i * 6 + 2] = i * 4 + 2;
//           buffers.raw.elements[i * 6 + 3] = i * 4 + 2;
//           buffers.raw.elements[i * 6 + 4] = i * 4 + 3;
//           buffers.raw.elements[i * 6 + 5] = i * 4 + 0;
//         }
//       }
//       //return buffers.raw;

//       //GLGen();
//       buffers.GL_Gen();
//     }
//     /*
//         void draw(RG_Camera& cam = RG_Camera_StandartPtr){

//           if(RG_Atlas_StandartPtr->Font_Atl.buf.gl_is_texture()){
//             if(RG_Atlas_StandartPtr->Font_Atl.buf.gl.textures.size() == 0)RG_LOG_LOCK_CRITICAL(L"Что то тут не то...");
//             tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

//             /*if(tempFrame > 1){
//               frame += floor(tempFrame);
//               tempFrame -= floor(tempFrame);
//             }
//             frame = frame % (maxFrames);//textures.size();*!/
//             RG_Mods::Texture_On();
//             glBindBuffer(GL_ARRAY_BUFFER, RG_Atlas_StandartPtr->Font_Atl.buf.gl.textures[frame]);
//             rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
//           }
//           else RG_Mods::Texture_Off();

//           if(RG_Atlas_StandartPtr->Font_Atl.buf.gl_is_vertex()){
//             glBindBuffer(GL_ARRAY_BUFFER, RG_Atlas_StandartPtr->Font_Atl.buf.gl.vertex);
//             rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
//           }
//           else RG_LOG_LOCK_CRITICAL("text vertex == -1");

//           if(RG_Atlas_StandartPtr->Font_Atl.buf.gl_is_offset()){
//             glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.offset);
//             rgOffsetPointer(3, GL_DOUBLE, 0, nullptr);
//           }else rgOffset3d(0, 0, 0);

//           if(buffers.gl_is_color()){
//             glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.color);
//             rgColorPointer(4, GL_DOUBLE, 0, nullptr);
//           }else RG_LOG_LOCK_CRITICAL("text color == -1");
//           //cam.loadMatrix();


//           if(is_gui){
//             rgLoadGuiMatrix(GuiType);
//           }
//           else{
//             //rgLoadCamMatrix();
//             cam.loadMatrix();
//           }
//           rgLoadMatrixf(mat);


//           rgDrawElements(GL_TRIANGLES, buffers.raw.elements.size(), GL_UNSIGNED_INT, buffers.raw.elements.get_arr());
//         }*/

//     void draw(RG_Camera& cam = *RG_Camera_StandartPtr) {

//       if (buffers.gl.textures.size() > 0) {
//         tempFrame += RG_Timer_StandartPtr->getBias() * FrPeSe;

//         if (tempFrame > 1) {
//           frame += floor(tempFrame);
//           tempFrame -= floor(tempFrame);
//         }
//         frame = frame % (maxFrames);//textures.size();
//         RG_Mods::Texture_On();
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.textures[frame]);
//         rgTexCoordPointer(2, GL_DOUBLE, 0, nullptr);
//       } else RG_Mods::Texture_Off();

//       if (buffers.gl.vertex != -1) {
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.vertex);
//         rgVertexPointer(3, GL_DOUBLE, 0, nullptr);
//       } else RG_LOG_LOCK_CRITICAL("background vertex == -1");
//       if (buffers.gl.color != -1) {
//         glBindBuffer(GL_ARRAY_BUFFER, buffers.gl.color);
//         rgColorPointer(4, GL_DOUBLE, 0, nullptr);
//       } else RG_LOG_LOCK_CRITICAL("background color == -1");
//       //cam.loadMatrix();


//       if (is_gui) {
//         rgLoadGuiMatrix(GuiType);
//       } else {
//         //rgLoadCamMatrix();
//         cam.loadMatrix();
//       }
//       rgLoadMatrixf(mat);


//       rgDrawElements(GL_TRIANGLES, buffers.raw.elements.size(), GL_UNSIGNED_INT, buffers.raw.elements.get_arr());
//     }

//   };
//   /*
//     class Mesh:public Standart{
//     public:
//       struct Settings:public Standart::Settings{
//         Standart::RG_Buffers mesh;
//       };
//       void init(to_rvalue(Settings) sett){
//         Standart::init(sett);
//         buffers.raw = sett.buf;
//       }
//       Settings set;


//       void Create(to_rvalue(Settings) sett){
//         init(sett);
//         Create();
//       }
//       void Create(){
//         if(!INIT)init();

//       }

//       void init(){
//         init(set);
//       }


//     };*/
// };



// template <class type>
// void RG_InitBuffer(int& buf, int size, type* data) {
//   buf = BufferLoad<double>(size * sizeof(type), data, GL_STATIC_DRAW);
// }


