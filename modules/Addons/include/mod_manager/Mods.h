#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/mod_manager-mods"

typedef void(*RG_Mod_Init_Func)(RG_Array<string>&, RG_Array<wstring>&, const RG_Meta_Resources&);
typedef void(*RG_Mod_Start_Func)();
typedef void(*RG_Share_Resources_Func)(RG::Parser* resource);//TODO


class RG_Meta_Mods {
  uint _core_count = 0, _main_core = 0;
  RG_Array<RG_ModMeta> _mods;
  wstring _path = L"mods/";
  RG_Array<RG::Parser> parsers;
public:
  RG_ModMeta& operator[](uint i) {
    return _mods[i];
  }
  RG::Parser& get_pars(uint i) {
    return parsers[i];
  }
  RG_Meta_Mods() {};

  inline uint size() { return _mods.size(); }
  inline uint count() { return _mods.size(); }
  inline uint core_count() { return _core_count; }
  inline uint main_core() { return _main_core; }
  void dll_on() {
    for (int i = 0; i < _mods.size(); i++) {
      HMODULE dllmod = LoadLibraryW(wstring(_mods[i].path + L"/" + _mods[i].entry_dll).c_str());
      if (!dllmod) {
        RG_LOG_LOCK_INFO(_mods[i].name + L" mod DLL file was not found");
      } else {
        _mods[i].dllmod = dllmod;
      }
    }
  }
  void dll_off() {
    for (int i = 0; i < _mods.size(); i++) {
      if (_mods[i].dllmod) {
        FreeLibrary(_mods[i].dllmod);
        _mods[i].dllmod = nullptr;
      }
    }
  }
  void dll_on(uint i) {
#if defined(__i386__) || defined(_M_IX86) || defined(__arm__)// || defined(_WIN32)
    HMODULE dllmod = LoadLibraryW(wstring(_mods[i].path + L"/" + _mods[i].entry_dll_x32).c_str());
    if (!dllmod) {
      rg_cout << "Mods " << wstring(_mods[i].path + L"/" + _mods[i].entry_dll_x32).c_str() << " dont loaded\n";
      RG_LOG_LOCK_INFO(_mods[i].name + L" mod DLL file was not found");
    } else {
      rg_cout << "Mods " << wstring(_mods[i].path + L"/" + _mods[i].entry_dll_x32).c_str() << " loaded\n";
      _mods[i].dllmod = dllmod;
    }
#else
    HMODULE dllmod = LoadLibraryW(wstring(_mods[i].path + L"/" + _mods[i].entry_dll).c_str());
    if (!dllmod) {
      rg_cout << "Mods " << wstring(_mods[i].path + L"/" + _mods[i].entry_dll).c_str() << " dont loaded\n";
      RG_LOG_LOCK_INFO(_mods[i].name + L" mod DLL file was not found");
    } else {
      rg_cout << "Mods " << wstring(_mods[i].path + L"/" + _mods[i].entry_dll).c_str() << " loaded\n";
      _mods[i].dllmod = dllmod;
    }
#endif

  }
  void dll_off(uint i) {
    if (_mods[i].dllmod) {
      RG_LOG_LOCK_INFO(_mods[i].name + L" mod DLL will be free");
      FreeLibrary(_mods[i].dllmod);
      _mods[i].dllmod = nullptr;
    }
  }
  RG_Meta_Mods(to_rvalue(wstring) path) : _path(path) { init(); }
  void init(to_rvalue(wstring) path) { _path = path; init(); }
  void init() {
    _mods.reserve(16);
    bool isLoad = false;

    RG::FileFinderW fin;
    if (_path[_path.size() - 1] != L'/' && _path[_path.size() - 1] != L'/')_path += L'/';
    WIN32_FIND_DATAW* file = fin.init(_path + L"*");

    RG_Array<wstring> mods;

    if (file) {
      for (int i = 0; !fin.eof(); i++) {
        file = fin.next();
        if (file) {
          if (i > 0) {
            mods.push_back(file->cFileName);
          }
        }
      }
    }


    RG_Array<wstring> mods_paths, mods_paths_meta;

    fin.close();

    if (mods.size() == 0) { isLoad = 0; } else {
      for (int i = 0; i < mods.size(); i++) {
        file = fin.init(L"mods/" + mods[i] + L"/*.rgmeta");
        if (file) {
          mods_paths.fastpush(L"mods/" + mods[i]);
          mods_paths_meta.fastpush(L"mods/" + mods[i] + L"/" + file->cFileName);
          do {
            file = fin.next();
            if (file) {
              mods_paths.fastpush(L"mods/" + mods[i]);
              mods_paths_meta.fastpush(L"mods/" + mods[i] + L"/" + file->cFileName);
            }
          } while (file);
        }
        fin.close();
      }
    }

    parsers.resize(mods_paths.size());
    for (int i = 0; i < mods_paths.size(); i++) {
      // rg_cout<<"meta print:\n\n";
      parsers[i].init((RG::FileLoad(RG::utf8_encode(mods_paths_meta[i]))));
      // parsers[i]. (mods_paths_meta[i]);

      // pars.print();
      _mods.push_back();
      _mods[i].priority = parsers[i].get(L"meta/priority", 0);
      _mods[i].path = mods_paths[i];
      _mods[i].name = parsers[i].get(L"meta/mod/name", 0);
      _mods[i].description = parsers[i].get(L"meta/mod/description", 0);
      _mods[i].version = parsers[i].get(L"meta/mod/version", 0);
      _mods[i].build_number = parsers[i].get(L"meta/mod/build_number", 0);
      _mods[i].uuid = parsers[i].get(L"meta/mod/uuid", 0);
      _mods[i].entry_dll = parsers[i].get(L"meta/mod/entry_dll", 0);
      _mods[i].entry_dll_x32 = parsers[i].get(L"meta/mod/entry_dll_x32", 0);
      _mods[i].author = parsers[i].get(L"meta/mod/author", 0);
      _mods[i].license = parsers[i].get(L"meta/mod/license", 0);
      _mods[i].min_game_version = parsers[i].get(L"meta/mod/min_game_version", 0);
      _mods[i].icon = parsers[i].get(L"meta/mod/icon", 0);
      _mods[i].dependencies = parsers[i].get(L"meta/mod/dependencies");
      _mods[i].resources = parsers[i].get(L"meta/mod/resources", 0);
      _mods[i].resources_uuid = parsers[i].get(L"meta/mod/resources_uuid", 0);
    }


    if (_mods.size()) {
      for (int i = 0; i < _mods.size(); i++) {
        if (_mods[i].priority == L"Core") {
          if (!_core_count) {
            _main_core = i;
          }
          _core_count++;
        }

        // rg_cout << _mods[i] << endl;

          // Получение указателя на функцию
        //   RG_Mod_Init_Func RG_Mod_Init = (RG_Mod_Init_Func)GetProcAddress(dllmod, "RG_Mod_Init");
        //   if (!RG_Mod_Init) {
        //     RG_LOG_LOCK_ERROR(L"RG_Mod_Init function not found in " + _mods[i].name + L" mod");
        //   } else {
        //     // RG_Mod_Init(RG_AMainArguments, RG_WMainArguments);

        //   }

        // }
      }
    }
  }
};