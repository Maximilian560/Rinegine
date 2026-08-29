#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/mod_manager-res"

class RG_Meta_Resources {
  RG_Array<RG_ResourceMeta> _resources;
  wstring _path = L"resources/";
  RG_Array<RG::Parser> parsers;
  uint _count;
public:
  RG_ResourceMeta& operator[](uint i) const{
    return _resources[i];
  }
  RG::Parser& get_pars(uint i)const{
    return parsers[i];
  }
  uint count() const{
    return _count;
  }
  uint size() const{
    return _count;
  }
  void init(to_rvalue(wstring) path) { _path = path; init(); }
  void init() {
    // bool isLoad = false;


    RG::FileFinderW fin;

    if (_path[_path.size() - 1] != L'/' && _path[_path.size() - 1] != L'\\')_path += L'/';
    WIN32_FIND_DATAW* file = fin.init(_path + L"*");
    // WIN32_FIND_DATAW* file = fin.init(L"resources/*");


    RG_Array<wstring> resources;


    if (file) {

      for (int i = 0; !fin.eof();i++) {
        file = fin.next();
        if (file) {
          if (i > 0) {
            resources.push_back(file->cFileName);
          }
        }
      }

    }



    RG_Array<wstring> resources_paths, resources_paths_meta;


    fin.close();


    if (resources.size() != 0) {

      for (int i = 0; i < resources.size();i++) {
        file = fin.init(L"resources/" + resources[i] + L"/*.rgmeta");
        if (file) {
          resources_paths.push_back(L"resources/" + resources[i]);
          resources_paths_meta.push_back(L"resources/" + resources[i] + L"/" + file->cFileName);
          do {
            file = fin.next();
            if (file) {
              resources_paths.push_back(L"resources/" + resources[i]);
              resources_paths_meta.push_back(L"resources/" + resources[i] + L"/" + file->cFileName);
            }
          } while (file);
        }
        fin.close();
      }

    }


    _count=resources_paths.size();
    parsers.resize(resources_paths.size());
    for (int i = 0; i < resources_paths.size();i++) {
      // rg_cout<<"meta print:\n\n";

      parsers[i].init((RG::FileLoad(RG::utf8_encode(resources_paths_meta[i]))));
      // pars.print();
      _resources.push_back();
      _resources[i].path = resources_paths[i];
      _resources[i].priority = parsers[i].get(L"meta\\priority", 0);
      _resources[i].name = parsers[i].get(L"meta\\resources\\name", 0);
      _resources[i].description = parsers[i].get(L"meta\\resources\\description", 0);
      _resources[i].version = parsers[i].get(L"meta\\resources\\version", 0);
      _resources[i].build_number = parsers[i].get(L"meta\\resources\\build_number", 0);
      _resources[i].uuid = parsers[i].get(L"meta\\resources\\uuid", 0);
      _resources[i].author = parsers[i].get(L"meta\\resources\\author", 0);
      _resources[i].license = parsers[i].get(L"meta\\resources\\license", 0);
      _resources[i].min_game_version = parsers[i].get(L"meta\\resources\\min_game_version", 0);
      _resources[i].icon = parsers[i].get(L"meta\\resources\\icon", 0);
      _resources[i].dependencies = parsers[i].get(L"meta\\resources\\dependencies");
      _resources[i].nspace = parsers[i].get(L"meta\\resources\\namespace", 0);
      // _resources.print();
      // rg_cout<<"resources name: "<<_resources[i].name<<endl;

      // pars.print();
    }



    // if(_resources.size()){
    //   for(int i = 0; i < _resources.size();i++){
    //     // rg_cout << mods_meta[i] << endl;
    //     HMODULE dllmod = LoadLibrary(wstring(mods_meta[i].path + L"\\" + mods_meta[i].entry_dll).c_str());
    //     if(!dllmod){
    //       RG_LOG_LOCK_ERROR(mods_meta[i].name + L" mod DLL file was not found");
    //     } else{
    //       mods_meta[i].dllmod = dllmod;
    //       // Получение указателя на функцию
    //       RG_Mod_Init_Func RG_Mod_Init = (RG_Mod_Init_Func)GetProcAddress(dllmod, "RG_Mod_Init");
    //       if(!RG_Mod_Init){
    //         RG_LOG_LOCK_ERROR(L"RG_Mod_Init function not found in " + mods_meta[i].name + L" mod");
    //       } else{
    //         RG_Mod_Init(RG_AMainArguments, RG_WMainArguments);
    //         if(mods_meta[i].priority == L"Core"){
    //           CORE_COUNT++;
    //         }
    //       }

    //     }
    //   }
    // } else{
    //   isLoad = 0;
    // }

    // return isLoad;
  }
};