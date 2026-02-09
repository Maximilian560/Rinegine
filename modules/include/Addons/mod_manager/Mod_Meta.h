#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/mod_manager-mod_meta"


struct RG_ModMeta {
  wstring path,
    name,
    description,
    version,
    build_number,
    uuid,
    entry_dll,
    entry_dll_x32,
    author,
    license,
    min_game_version,
    icon,
    resources,
    resources_uuid,
    priority;
  // dependencies;
  RG_Array<wstring> dependencies;
  HMODULE dllmod = nullptr;
  ~RG_ModMeta() {
    if (dllmod) {
      FreeLibrary(dllmod);
      RG_LOG_LOCK_INFO(L"mod '" + name + L"' unloaded");
    }
  }
};

wostream& operator<<(wostream& out, RG_ModMeta& mod) {
  out << L"Mod meta\nname: " << mod.name << "\npath:"
    << mod.path << "\ndescription:"
    << mod.description << "\nversion:"
    << mod.version << "\nbuild_number:"
    << mod.build_number << "\nuuid:"
    << mod.uuid << "\nentry_dll:"
    << mod.entry_dll << "\entry_dll_x32:"
    << mod.entry_dll_x32 << "\nauthor:"
    << mod.author << "\nlicense:"
    << mod.license << "\nmin_game_version:"
    << mod.min_game_version << "\nicon:"
    << mod.icon << "\nresources:"
    << mod.resources << "\nresources_uuid:"
    << mod.resources_uuid << "\npriority:"
    << mod.priority << "\ndependencies:";
  mod.dependencies.print();
  rg_cout << endl << endl;

  return out;
}
