#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/med/texture-atlas"

//#include <io.h>
//#include <fcntl.h>

struct RG_Letter {
  wchar_t let;
  POINT2D<int> pos;
  POINT2D <double>size;//	ширина и высота глифа в пикселях, доступ по face->glyph->bitmap.width и face->glyph->bitmap.rows
  POINT2D <double>bias;//	горизонтальное и вертикальное смещение верхней левой точки глифа по отношению к origin, доступ по face->glyph->bitmap_left и  face->glyph->bitmap_top
  double advance;//	горизонтальное смещение начала следующего глифа в 1/64 пикселях по отношению к origin, доступ по face->glyph->advance.x
};

class RG_Atlas : private RG_Texture::Atlas {
  friend class RG_Object::Standart;
  friend class RG_Object::Text;
  friend class RG_Object::Sprite;
  friend class RG_Object::Background;
  //friend class RG_Object::Mesh;
  RG_Array<RG_Texture::Standart> Textures;
  RG_Array<string>names;
  RG_Array<string>paths;
  struct Font_Atlas {
    RG_Texture::Raw font;
    POINT2D<int> pos;
    POINT2D<int> size;
    RG_Array<RG_ENCODE_VALUE> letter_index;
    RG_Array<RG_Letter>letters;

    bool init = false;
  }Font_Atl;
  int gl_type = GL_TEXTURE_2D;
  uint gl_id = UINT_MAX;
  bool _INIT = false;
  //RG_Array<RG_Texture::Lite> Textures;
public:
  void clear() {
    // rg_cout<<L"Clear atlas\n";
    del();
    // rg_cout<<L"Del success\n";
    FT_Done_Face(DefFace);   // Завершение работы с шрифтом face
    // rg_cout<<L"Face Done success\n";
    FT_Done_FreeType(library); // Завершение работы FreeType
    // rg_cout<<L"FreeType Done success\n";
    if (gl_id != UINT_MAX) {
      // rg_cout<<gl_id<<endl;
      glDeleteTextures(1, &gl_id);
      gl_id = UINT_MAX;
      // rg_cout<<gl_id<<L" deleted"<<endl;
    }
    for (int i = 0; i < Textures.size(); i++)Textures[i].del();
    // rg_cout<<L"gl texture delete success\n";
    Font_Atl.font.del();
    // rg_cout<<L"font texture delete success\n";
  }
  ~RG_Atlas() {
    clear();
  }
  //
  POINT2D<int> Font_Get_Pos(to_rvalue(wchar_t) in)const {
    //return Font_Get_Letter(in).pos;
    //return {0,0};
    /*for(int i = 0; i< Font_Atl.letter_index.size();i++){
      if(Font_Atl.letter_index[i].pos>=in&&Font_Atl.letter_index[i].size+Font_Atl.letter_index[i].pos<=in)return Font_Atl.letters[i].pos;
    }*/
    return Font_Get_Letter(in).pos;
  }
  RG_Letter& Font_Get_Letter(to_rvalue(wchar_t) in)const {
    int id = 0;
    for (int i = 0; i < Font_Atl.letter_index.size(); i++) {
      if ((Font_Atl.letter_index[i].pos <= in) && ((Font_Atl.letter_index[i].size + Font_Atl.letter_index[i].pos) >= in)) {
        //return Font_Atl.letters[(id + (Font_Atl.letter_index[i].pos + Font_Atl.letter_index[i].size) - in)];
        //int out = (id + (Font_Atl.letter_index[i].pos + Font_Atl.letter_index[i].size)-in);
        int out = (id + (in - Font_Atl.letter_index[i].pos));
        return Font_Atl.letters[out];
      } else {
        id += Font_Atl.letter_index[i].size;
      }
    }
    return Font_Atl.letters[0];

    //return Font_Atl.letters[in];
    /*for(int i = 0; i< Font_Atl.letter_index.size();i++){
      if((Font_Atl.letter_index[i].pos>=in)&&((Font_Atl.letter_index[i].size+Font_Atl.letter_index[i].pos)<=in))return Font_Atl.letters[i];
    }*/
  }

  void Init(initializer_list<string> path, initializer_list<string> name) {
    //paths.fill(path.begin(),path.size());
    //names.fill(name.begin(),name.size());
    paths.init(path);
    names.init(name);
  }
  void Init(RG_Array <string> path, RG_Array<string> name) {
    paths = path;
    names = name;
  }
  void fastpush(string path, string name) {
    paths.fastpush(path);
    names.fastpush(name);
  }
  void fastpush(initializer_list<string> path, initializer_list<string> name) {
    paths.fastpush(path);
    names.fastpush(name);
  }

  void fastpush(RG_Array <string> path, RG_Array<string> name) {
    paths.fastpush(path);
    names.fastpush(name);
  }

  void push_back(string path, string name) {
    paths.push_back(path);
    names.push_back(name);
  }
  void push_back(initializer_list<string> path, initializer_list<string> name) {
    paths.push_back(path);
    names.push_back(name);
  }

  void push_back(RG_Array <string> path, RG_Array<string> name) {
    paths.push_back(path);
    names.push_back(name);
  }

  void Font(
    #ifdef RG_SYS_WINDOWS
    wstring path, 
    #elif defined(RG_SYS_LINUX)
    wstring path,
    #else
    wstring path,
    #endif
    int sizefont = 50, RG_Array<wstring> lang = {}) {
    RG_Array<string>slang(lang.size());
    int ii = 0;
    for (string& i : slang) {
      i = RG::utf8_encode(lang[ii]);
      ii++;
    }
    Font(RG::utf8_encode(path), sizefont, slang);
  }
  void Font(
    #ifdef RG_SYS_WINDOWS
    string path = "/Windows/Fonts/segoeui.ttf", 
    #elif defined(RG_SYS_LINUX)
    string path = "/usr/share/fonts/cyr-sun16",
    #else
    string path,
    #endif
    int sizefont = 50, RG_Array<string>lang = {}) {

    RG_FONT_SIZE = sizefont;
    bool Latin = 1;
    for (int i = 0; i < lang.size(); i++) {
      if (lang[i] == "Basic Latin")Latin = 0;
    }
    if (FT_Init_FreeType(&library))
      throw(RG_ERROR_FREETYPE);

    if (FT_New_Face(library, path.c_str(), 0, &DefFace)) {
      RG_LOG_LOCK_ERROR("Font "+path+" not found");
      throw(RG_ERROR_FREETYPE_FONTS_NOT_FOUND);
    }
    FT_Set_Pixel_Sizes(DefFace, 0, sizefont);
    RG_Array<RG_ENCODE_VALUE> temp_enc(lang.size() + Latin);
    uint count_let = 0;
    POINT2D<int> size_mat;
    if (Latin)temp_enc[0] = RG_ENCODE::get("Basic Latin");
    count_let += temp_enc[0].size;
    for (int i = 0; i<int(lang.size()); i++) {
      temp_enc[i + Latin] = RG_ENCODE::get(lang[i]);
      count_let += temp_enc[i + Latin].size;
    }
    size_mat.x = ceil(sqrt(count_let));
    size_mat.y = count_let / size_mat.x;


    while ((size_mat.y) * size_mat.x >= count_let) { size_mat.y--; }
    while ((size_mat.y) * size_mat.x <= count_let) { size_mat.y++; }

    Font_Atl.font.raw.resize(size_mat.x * sizefont * 4, size_mat.y * sizefont);
    Font_Atl.font.cnt = 4;
    Font_Atl.font.size = { size_mat.x * sizefont, size_mat.y * sizefont };

    //rg_cout << to_wstring(count_let) << endl;
    //rg_cout << to_wstring(size_mat.x) << L" " << to_wstring(size_mat.y) << L" " << to_wstring(size_mat.x * (size_mat.y - 1)) << endl;
    POINT2D<int> pen;
    int ti = 0;

    Font_Atl.letters.resize(count_let);


    // Font_Atl.buf.gl.textures.resize(1);

    // Font_Atl.buf.raw.vertex.resize(count_let * 4);
    // Font_Atl.buf.raw.color.resize(count_let * 4);
    // Font_Atl.buf.raw.textures.resize(1);
    // Font_Atl.buf.raw.textures[0].resize(count_let * 4);

    //Font_Atl.letter_index.resize(count_let);
    Font_Atl.letter_index.resize(temp_enc.size());
    for (int i = 0; i < temp_enc.size(); i++) {
      Font_Atl.letter_index[i] = { temp_enc[i].pos, temp_enc[i].size };
      for (int j = 0; j < temp_enc[i].size; j++) {
        RG_Letter& letter = Font_Atl.letters[ti];
        letter.let = temp_enc[i].pos + j;
        if (pen.x >= size_mat.x) { pen.x = 0; pen.y++; }
        if (pen.y >= size_mat.y) { RG_LOG_LOCK_CRITICAL("HOW!?"); }

        if (FT_Load_Char(DefFace, letter.let, FT_LOAD_RENDER)) throw(RG_ERROR_FREETYPE_CHAR_NOT_LOAD);

        letter.size.x = DefFace->glyph->bitmap.width;
        letter.size.y = DefFace->glyph->bitmap.rows;

        letter.bias.x = DefFace->glyph->bitmap_left;
        letter.bias.y = DefFace->glyph->bitmap_top;

        letter.advance = DefFace->glyph->advance.x;

        letter.pos.x = pen.x * sizefont;
        letter.pos.y = pen.y * sizefont;
        //rg_cout<<letter.size.x<<" "<<DefFace->glyph->bitmap.width<<endl;
        for (int y = 0; y < letter.size.y; y++) {
          for (int x = 0; x < letter.size.x; x++) {
            uint tx = pen.x * sizefont + x;
            uint ty = pen.y * sizefont + y;
            //rg_cout<<ty<<" "<<tx<<endl;
            //Font_Atl.font.raw[ty][tx * 4 + 0] = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
            //Font_Atl.font.raw[ty][tx * 4 + 1] = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
            //Font_Atl.font.raw[ty][tx * 4 + 2] = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
            //Font_Atl.font.raw[ty][tx * 4 + 3] = 255;
            Font_Atl.font.raw.getyx(ty, tx * 4 + 0) = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
            Font_Atl.font.raw.getyx(ty, tx * 4 + 1) = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
            Font_Atl.font.raw.getyx(ty, tx * 4 + 2) = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
            Font_Atl.font.raw.getyx(ty, tx * 4 + 3) = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
          }
        }


        //rg_cout<<to_wstring(pen.x)<<"|"<<to_wstring(pen.y)<<L" ";
        pen.x++;
        ti++;
      }
    }
    /*for(int y = 0; y < Font_Atl.font.size.y;y++){
      for(int x = 0; x < Font_Atl.font.size.x;x++){
        Font_Atl.font.raw[y][x * 4 + 3] = 255;
      }
    }*/
    Font_Atl.size.x = Font_Atl.font.size.x;
    Font_Atl.size.y = Font_Atl.font.size.y;
    //rg_cout<<endl;
        //rg_cout<<wchar_t(temp_enc[i].pos+j  )<<L" = "<<to_wstring(temp_enc[i].pos+j)<<endl;
    //stbi_write_png("atlas_font.png",Font_Atl.font.size.x,Font_Atl.font.size.y,4,Font_Atl.font.raw.get_mat(),0);
    //RG_LOG_LOCK_CRITICAL("DEBUG");
    Font_Atl.init = true;
    //if(_INIT)Font_Buf_Gen();
  }
  /*||||||||* /
            //const RG_Letter& letter = RG_Atlas_StandartPtr->Font_Get_Letter(set.text[i]);

            Font_Atl.buf.raw.vertex[i * 4 + 0] = {
              space.x,
              -space.y - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual, 0};
            Font_Atl.buf.raw.vertex[i * 4 + 1] = {
              space.x,
              -space.y - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual, 0};
            Font_Atl.buf.raw.vertex[i * 4 + 2] = {
              (letter.size.x) / RG_SYS_WINDOWSdow_Virtual + space.x,
              -space.y - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual, 0};
            Font_Atl.buf.raw.vertex[i * 4 + 3] = {
              (letter.size.x) / RG_SYS_WINDOWSdow_Virtual + space.x,
              -space.y - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual, 0};

            Font_Atl.buf.raw.textures[0][i * 4 + 0] = {letter.pos.x / (double)size.x, letter.pos.y / (double)size.y};
            Font_Atl.buf.raw.textures[0][i * 4 + 1] = {letter.pos.x / (double)size.x, letter.pos.y / (double)size.y + letter.size.y / (double)size.y};
            Font_Atl.buf.raw.textures[0][i * 4 + 2] = {letter.pos.x / (double)size.x + letter.size.x / (double)size.x, letter.pos.y / (double)size.y + letter.size.y / (double)size.y};
            Font_Atl.buf.raw.textures[0][i * 4 + 3] = {letter.pos.x / (double)size.x + letter.size.x / (double)size.x, letter.pos.y / (double)size.y};


            space.x += (letter.size.x) / RG_SYS_WINDOWSdow_Virtual;
            / *|||||||||* /
            / *void Font_Buf_Gen(){

              int i = 0;
              for(RG_Letter& letter : Font_Atl.letters){

                Font_Atl.buf.raw.vertex[i * 4 + 0] = {
                  0,
                  - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual, 0};
                Font_Atl.buf.raw.vertex[i * 4 + 1] = {
                  0,
                  - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual, 0};
                Font_Atl.buf.raw.vertex[i * 4 + 2] = {
                  (letter.size.x) / RG_SYS_WINDOWSdow_Virtual,
                  - (RG_FONT_SIZE - letter.bias.y + letter.size.y) / RG_SYS_WINDOWSdow_Virtual, 0};
                Font_Atl.buf.raw.vertex[i * 4 + 3] = {
                  (letter.size.x) / RG_SYS_WINDOWSdow_Virtual + 0,
                  - (RG_FONT_SIZE - letter.bias.y) / RG_SYS_WINDOWSdow_Virtual, 0};

                Font_Atl.buf.raw.textures[0][i * 4 + 0] = {letter.pos.x / (double)size.x, letter.pos.y / (double)size.y};
                Font_Atl.buf.raw.textures[0][i * 4 + 1] = {letter.pos.x / (double)size.x, letter.pos.y / (double)size.y + letter.size.y / (double)size.y};
                Font_Atl.buf.raw.textures[0][i * 4 + 2] = {letter.pos.x / (double)size.x + letter.size.x / (double)size.x, letter.pos.y / (double)size.y + letter.size.y / (double)size.y};
                Font_Atl.buf.raw.textures[0][i * 4 + 3] = {letter.pos.x / (double)size.x + letter.size.x / (double)size.x, letter.pos.y / (double)size.y};
                i++;
              }
              Font_Atl.buf.GL_Gen();
            }
          */



  void Gen() {


    //if(names.size()==0||paths.size()==0)RG_LOG_LOCK_CRITICAL("Error generating atlas, names or paths to textures were not found.");
    if (names.size() != paths.size())RG_LOG_LOCK_CRITICAL("Atlas generation error, number of textures and their paths do not match.");
    if (names.size() == 0 || paths.size() == 0) {
      if (Font_Atl.size.x > 0) {
        raw = Font_Atl.font.raw;
      } else
        return;
    }//RG_LOG_LOCK_CRITICAL("Error generating atlas, names or paths to textures were not found.");


    /*Textures.resize(1);
    Textures[0].load(paths[0]);
    raw.init(Textures[0].raw);
    size = {48,64};*/


    //raw.resize();


    //rg_cout << "Paths size" << paths.size() << endl;
    Textures.resize(paths.size());
    //rg_cout << "Textures size" << Textures.size() << endl;
    POINT2D<int>max_size;
    POINT2D<int>max_one_size;
    POINT2D<int>end_size;
    for (int i = 0; i < paths.size(); i++) {
      Textures[i].load(paths[i]);
    }
    //if(Font_Atl.init)

    //  Textures.resize(paths.size()+1);
    //else
    //  Textures.resize(paths.size());
    /*if(Font_Atl.init){
      max_size.x+=Font_Atl.font.size.x*4;
      max_size.y+=Font_Atl.font.size.y;
      if(Font_Atl.font.size.x>max_one_size.x) max_one_size.x = Font_Atl.font.size.x;
      if(Font_Atl.font.size.y>max_one_size.y) max_one_size.y = Font_Atl.font.size.y;

      Textures[0].size.x = Font_Atl.font.size.x*4;
      Textures[0].size.y = Font_Atl.font.size.y;
      Textures[0].raw.movefill(Textures[0].size.x*4,Textures[0].size.y,Font_Atl.font.raw);
    }*/



    for (RG_Texture::Standart& tex : Textures) {
      max_size.x += tex.size.x;
      max_size.y += tex.size.y;
      if (tex.size.x > max_one_size.x) max_one_size.x = tex.size.x;
      if (tex.size.y > max_one_size.y) max_one_size.y = tex.size.y;
    }


    if (Font_Atl.init) {
      max_size.x += Font_Atl.font.size.x * 4;
      max_size.y += Font_Atl.font.size.y;
      if (Font_Atl.font.size.x > max_one_size.x) max_one_size.x = Font_Atl.font.size.x;
      if (Font_Atl.font.size.y > max_one_size.y) max_one_size.y = Font_Atl.font.size.y;
    }
    while (end_size.x < max_size.x) {
      end_size.x += 1024 * 4;
    }
    while (end_size.y < max_size.y) {
      end_size.y += 1024;
    }
    raw.resize(end_size.x, end_size.y);
    size.x = end_size.x / 4.;
    size.y = end_size.y;
    cnt = 4;

    POINT2D<int>pen;
    POINT2D<int>max;


    if (Font_Atl.init) {
      if (pen.x + Font_Atl.size.x > end_size.x) {
        if (pen.y + max.y >= end_size.y) { RG_LOG_LOCK_CRITICAL("Error gen atlas, size pen.y > end_size.y; end_size.y '" + to_string(end_size.y) + "' font.size '" + to_string(Font_Atl.size.y) + "'"); };
        pen.x = 0;
        pen.y += max.y + 1;
        max.y = 0;
      }

      raw.place({ pen.x * cnt, pen.y }, Font_Atl.font.raw);

      Font_Atl.pos.x = pen.x;
      Font_Atl.pos.y = pen.y;
      pen.x += Font_Atl.size.x;//*cnt;
      max.y = rg_max(Font_Atl.size.y, max.y);
    }

    //raw.place({0,0},Textures[0].raw);


    for (RG_Texture::Standart& texture : Textures) {
      if (pen.x + texture.size.x > end_size.x) {
        if (pen.y + max.y >= end_size.y) { RG_LOG_LOCK_CRITICAL("Error gen atlas, size pen.y > end_size.y; end_size.y '" + to_string(end_size.y) + "' texture.size '" + to_string(texture.size.y) + "'"); };
        pen.x = 0;
        pen.y += max.y + 1;
        max.y = 0;
      }
      raw.place({ pen.x * 4, pen.y }, texture.raw);

      texture.pos.x = pen.x;
      texture.pos.y = pen.y;
      pen.x += texture.size.x;
      max.y = rg_max(texture.size.y, max.y);


    }


    if (gl_id == UINT_MAX)
      glGenTextures(1, &gl_id);


    glBindTexture(GL_TEXTURE_2D, gl_id);


    /*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y,
      0, GL_RGBA, GL_UNSIGNED_BYTE, raw.get_mat());

    //raw.print();
#ifdef RG_ATLAS_GEN
    stbi_write_png("atlas.png", size.x, size.y, 4, raw.get_mat(), 0);
#endif
    //ShellExecuteA(0, "open", "atlas.png", NULL, NULL, SW_SHOWDEFAULT);
    //GetLastError();
    //RG_LOG_LOCK_INFO("Atlas successfully generated");
    //RG_Debug::stop();
    _INIT = true;
    //if(Font_Atl.init)Font_Buf_Gen();

  }

  uint get_id() {
    return gl_id;
  }

  RG_Texture::Standart& operator[](int i) {
    return Textures[i];
  }
  POINT2D<int> get_size() {
    return size;
  }
  int operator[](string name) {
    for (int i = 0; i < names.size(); i++) {
      if (names[i] == name)return i;
    }
    RG_LOG_LOCK_CRITICAL("Atlas not found texture '" + name + "'");
    return -1;
  }
  int find(string name) {
    for (int i = 0; i < names.size(); i++) {
      if (names[i] == name)return i;
    }
    RG_LOG_LOCK_CRITICAL("Atlas not found texture '" + name + "'");
    return -1;
  }

}RG_Atlas_Standart;

RG_Atlas* RG_Atlas_StandartPtr = &RG_Atlas_Standart;
//RG_Atlas *RG_Atlas_pStandart = &RG_Atlas_StandartPtr;


class RG_Mods {
  inline static bool textures = 0;
  inline static bool _init = 0;
public:
  static void Texture_On() {
    if (textures) {
      //RG_LOG_LOCK_INFO("Atlas already on");
      return;
    };
    if (RG_Atlas_StandartPtr->get_id() == -1) {
      RG_LOG_LOCK_CRITICAL("Atlas not prepare");
    }
    textures = 1;
    rgEnableClientState(RG_TEXTURE_COORD_ARRAY);
    rgBindTexture(RG_Atlas_StandartPtr->get_id());
  }

  static void Texture_Off() {
    if (!textures) {
      //RG_LOG_LOCK_INFO("Atlas already off");
      return;
    }
    textures = 0;
    rgDisableClientState(RG_TEXTURE_COORD_ARRAY);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    rgBindTexture(0);
  }
  static void Texture_Init() {
    if (_init)return;
    _init = 1;
    if (RG_Atlas_StandartPtr->get_id() == -1) {
      RG_LOG_LOCK_CRITICAL("Atlas not prepare");
    }
    textures = 1;
    rgEnableClientState(RG_TEXTURE_COORD_ARRAY);
    rgBindTexture(RG_Atlas_StandartPtr->get_id());
  }
};

