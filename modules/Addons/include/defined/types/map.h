#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/types/map"
template<class type1, class type2>
struct RG_MapData {
  type1 key;
  type2 value;
};

template<class type>
class RG_Map {
  typedef RG_MapData<string, type> Map;
  RG_Array<Map>map;
public:

  RG_Map() {}
  RG_Map(uint size) { init(size); }
  RG_Map(string key, type val) { init(key, val); }
  RG_Map(RG_MapData<string, type>keyval) { init(keyval); }
  RG_Map(RG_Array<RG_MapData<string, type>> keysvals) { init(keysvals); }
  RG_Map(initializer_list<RG_MapData<string, type>> keysvals) { init(keysvals); }
  //RG_Map(to_rvalue(RG_Map<type>)in) { init(in); }

  void init(uint size) {
    fill(size);
  }
  void init(string key, type val) {
    fill(key, val);
  }
  void init(RG_MapData<string, type>keyval) {
    fill(keyval);
  }
  void init(RG_Array<RG_MapData<string, type>>keysvals) {
    fill(keysvals);
  }
  void init(initializer_list<RG_MapData<string, type>>keysvals) {
    fill(keysvals);
  }
  // void init(to_rvalue(RG_Map<type>)in) {
  //   fill(in);
  // }


  // void fill(to_rvalue(RG_Map<type>)in) {
  //   map.init(in.get_rgarr());
  // }
  void fill(string key, type val) {
    map.push_back({ key,val });
    //values.push_back(val);
  }
  void fill(RG_MapData<string, type>keyval) {
    /*keys.push_back(keyval.one);
    values.push_back(keyval.two);*/
    map.push_back({ keyval.key,keyval.value });
  }
  void fill(uint size) {
    /*keys.init(size);
    values.init(size); */
    map.init(size);
  }
  void fill(RG_Array<RG_MapData<string, type>>keysvals) {
    //map.init(keysvals.size());
    map.init(keysvals);
    /*keys.init(keysvals.size());
    values.init(keysvals.size());*/
    //for(int i = 0; i<keysvals.size();i++){
      /*keys[i] = keysvals[i].one;
      values[i] = keysvals[i].two;*/
      //map[i] = keysvals[i];
    //}
  }
  void fill(initializer_list<RG_MapData<string, type>>keysvals) {
    map.init(keysvals);
    /*keys.init(keysvals.size());
    values.init(keysvals.size());*/
    //for(int i = 0; i<keysvals.size();i++){
      /*keys[i] = keysvals.begin()[i].one;
      values[i] = keysvals.begin()[i].two;*/
      //}
  }
  int findpos(string ii) {
    for (int i = 0; i < map.size();i++) {
      if (map[i].key == ii)return i;
    }
    return -1;
  }
  type find(string ii) {
    for (int i = 0; i < map.size();i++) {
      if (map[i].key == ii)return map[i].value;
    }
    RG_LOG_LOCK_CRITICAL("RG_Map error, '" + ii + "' not found");
    return map[0].value;

  }
  type find(int ii) {
    if (ii < 0)RG_LOG_LOCK_CRITICAL("RG_Map error, '" + to_string(ii) + "' less than zero");
    if (ii > map.size())RG_LOG_LOCK_CRITICAL("RG_Map error, '" + to_string(ii) + "' is greater than RG_Map size");
    return map[ii].value;

  }

  type operator[](string i) {
    return find(i);
  }
  /*type operator[](int i){
    return find(i);
  }*/
  void sort() {//todo
    Map tmp;
    bool noSwap;

    for (int i = map.size() - 1; i >= 0; i--) {
      noSwap = 1;
      for (int j = 0; j < i; j++) {
        if (map[j].value > map[j + 1].value) {
          tmp = map[j];
          map[j] = map[j + 1];
          map[j + 1] = tmp;
          noSwap = 0;
        }
      }
      if (noSwap == 1)
        break;
    }
  }
  RG_MapData<string, type>& operator[](uint i) {
    return map[i];
  }

  void push_back(RG_MapData<string, type> keyval) {
    map.push_back(keyval);
  }
  /*void pop(){
    map.
  }*/
  void resize(uint size) {
    map.resize(size);
  }

  int size() {
    return map.size();
  }
  RG_MapData<string, type>* get_arr() {
    return map.get_arr();
  }

  RG_Array<type>& get_rgarr() {
    return map;
  }
  void clear() {
    map.clear();
    //values.clear();
  }
  ~RG_Map() {
    clear();
  }
};

template<class type>
class RG_WMap {
  typedef RG_MapData<wstring, type> Map;
  RG_Array<Map>map;
public:

  RG_WMap() {}
  RG_WMap(uint size) { init(size); }
  RG_WMap(wstring key, type val) { init(key, val); }
  RG_WMap(RG_MapData<wstring, type>keyval) { init(keyval); }
  RG_WMap(RG_Array<RG_MapData<wstring, type>> keysvals) { init(keysvals); }
  RG_WMap(initializer_list<RG_MapData<wstring, type>> keysvals) { init(keysvals); }
  //RG_WMap(to_rvalue(RG_WMap<type>)in) { init(in); }

  void init(uint size) {
    fill(size);
  }
  void init(wstring key, type val) {
    fill(key, val);
  }
  void init(RG_MapData<wstring, type>keyval) {
    fill(keyval);
  }
  void init(RG_Array<RG_MapData<wstring, type>>keysvals) {
    fill(keysvals);
  }
  void init(initializer_list<RG_MapData<wstring, type>>keysvals) {
    fill(keysvals);
  }
  // void init(to_rvalue(RG_WMap<type>)in) {
  //   fill(in);
  // }


  // void fill(to_rvalue(RG_WMap<type>)in) {
  //   map.init(in.get_rgarr());
  // }
  void fill(wstring key, type val) {
    map.push_back({ key,val });
    //values.push_back(val);
  }
  void fill(RG_MapData<wstring, type>keyval) {
    /*keys.push_back(keyval.one);
    values.push_back(keyval.two);*/
    map.push_back({ keyval.key,keyval.value });
  }
  void fill(uint size) {
    /*keys.init(size);
    values.init(size); */
    map.init(size);
  }
  void fill(RG_Array<RG_MapData<wstring, type>>keysvals) {
    //map.init(keysvals.size());
    map.init(keysvals);
    /*keys.init(keysvals.size());
    values.init(keysvals.size());*/
    //for(int i = 0; i<keysvals.size();i++){
      /*keys[i] = keysvals[i].one;
      values[i] = keysvals[i].two;*/
      //map[i] = keysvals[i];
    //}
  }
  void fill(initializer_list<RG_MapData<wstring, type>>keysvals) {
    map.init(keysvals);
    /*keys.init(keysvals.size());
    values.init(keysvals.size());*/
    //for(int i = 0; i<keysvals.size();i++){
      /*keys[i] = keysvals.begin()[i].one;
      values[i] = keysvals.begin()[i].two;*/
      //}
  }
  int findpos(wstring ii) {
    for (int i = 0; i < map.size();i++) {
      if (map[i].key == ii)return i;
    }
    return -1;
  }
  type& find(wstring ii) {
    for (int i = 0; i < map.size();i++) {
      if (map[i].key == ii)return map[i].value;
    }
    RG_LOG_LOCK_CRITICAL(L"RG_WMap find wstring error, '" + ii + L"' not found");
    return map[0].value;

  }
  type& find(int ii) {
    if (ii < 0)RG_LOG_LOCK_CRITICAL("RG_WMap find int error, '" + to_string(ii) + "' less than zero");
    if (ii > map.size())RG_LOG_LOCK_CRITICAL("RG_WMap find int error, '" + to_string(ii) + "' is greater than RG_WMap size");
    return map[ii].value;
  }
  RG_MapData<wstring, type>& findstring(wstring ii) {
    for (int i = 0; i < map.size();i++) {
      if (map[i].key == ii)return map[i].value;
    }
    RG_LOG_LOCK_CRITICAL(L"RG_WMap find wstring error, '" + ii + L"' not found");
    return map[0].value;

  }

  type& operator[](wstring i) {
    return find(i);
  }
  RG_MapData<wstring, type>& findchar(wchar_t in) {
    wstring ii = L"0";
    ii[0] = in;
    for (int i = 0; i < map.size();i++) {
      if (map[i].key == ii)return map[i];
    }
    RG_LOG_LOCK_CRITICAL(L"RG_WMap find wchar error, '" + ii + L"' not found");
    return map[0];
  }
  /*type operator[](int i){
    return find(i);
  }*/
  void revsort() {
    Map tmp;
    bool noSwap;

    for (int i = map.size() - 1; i >= 0; i--) {
      noSwap = 1;
      for (int j = i - 1; j >= 0; j--) {
        if (map[j].value < map[j + 1].value) {
          tmp = map[j];
          map[j] = map[j + 1];
          map[j + 1] = tmp;
          noSwap = 0;
        }
      }
      if (noSwap == 1)
        break;
    }
  }
  void sort() {//todo
    Map tmp;
    bool noSwap;

    for (int i = map.size() - 1; i >= 0; i--) {
      noSwap = 1;
      for (int j = 0; j < i; j++) {
        if (map[j].value > map[j + 1].value) {
          tmp = map[j];
          map[j] = map[j + 1];
          map[j + 1] = tmp;
          noSwap = 0;
        }
      }
      if (noSwap == 1)
        break;
    }
  }
  RG_MapData<wstring, type>& operator[](uint i) {
    return map[i];
  }

  void push_back(RG_MapData<wstring, type> keyval) {
    map.push_back(keyval);
  }
  /*void pop(){
    map.
  }*/
  void resize(uint size) {
    map.resize(size);
  }

  int size() {
    return map.size();
  }
  RG_MapData<wstring, type>* get_arr() {
    return map.get_arr();
  }

  RG_Array<type>& get_rgarr() {
    return map;
  }
  void clear() {
    map.clear();
    //values.clear();
  }
  ~RG_WMap() {
    clear();
  }
};