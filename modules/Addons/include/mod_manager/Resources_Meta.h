#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/mod_manager-res_meta"


struct RG_ResourceMeta{

  wstring path,
    name,
    description,
    version,
    build_number,
    uuid,
    author,
    license,
    min_game_version,
    icon,
    nspace,
    priority;
  // dependencies;
  RG_Array<wstring>dependencies;
  // ~RR_ModMeta(){ if(dllmod){ FreeLibrary(dllmod);rg_cout << L"mod " << name << L" unloaded"; } else{ rg_cout << L"mod " << name << L" not unloaded"; } }
};

wostream& operator<<(wostream& out, RG_ResourceMeta& mod){
  out << L"Resouce meta\nname: " 
    << mod.name << "\npath:"
    << mod.path << "\ndescription:"
    << mod.description << "\nversion:"
    << mod.version << "\nbuild_number:"
    << mod.build_number << "\nuuid:"
    << mod.uuid <<  "\nauthor:"
    << mod.author << "\nlicense:"
    << mod.license << "\nmin_game_version:"
    << mod.min_game_version << "\nicon:"
    << mod.icon << "\npriority:"
    << mod.priority << "\ndependencies:";
  mod.dependencies.print();
  rg_cout << endl << endl;

  return out;
}