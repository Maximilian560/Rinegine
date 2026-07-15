#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/define"

#ifndef UINT_MAX
#define UINT_MAX 4294967295
#endif

#define rg_min(num1, num2) (num1 < num2 ? num1 : num2)
#define rg_max(num1, num2) (num1 > num2 ? num1 : num2)

#define RG_FOR_CYCLEi(count) for (int i = 0; i < count; i++)
#define RG_FOR_CYCLEj(count) for (int j = 0; j < count; j++)
#define RG_FOR_CYCLEk(count) for (int k = 0; k < count; k++)
#define RG_FOR_CYCLEx(count) for (int x = 0; x < count; x++)
#define RG_FOR_CYCLEy(count) for (int y = 0; y < count; y++)
#define RG_FOR_CYCLEz(count) for (int z = 0; z < count; z++)
#define RG_FOR_CYCLEty(type, name, count)                                      \
  for (type name = 0; name < count; name++)
#define RG_FOR_CYCLE(name, count) for (int name = 0; name < count; name++)
#define RG_FOR_CYCLErev(name, count) for (int name = count; name >= 0; name--)
#define RG_RevFOR_CYCLEi(count) for (int i = count; i >= 0; i--)
#define RG_RevFOR_CYCLEj(count) for (int j = count; j >= 0; j--)
#define RG_RevFOR_CYCLEk(count) for (int k = count; k >= 0; k--)
#define RG_RevFOR_CYCLEx(count) for (int x = count; x >= 0; x--)
#define RG_RevFOR_CYCLEy(count) for (int y = count; y >= 0; y--)
#define RG_RevFOR_CYCLEz(count) for (int z = count; z >= 0; z--)
#define RG_RevFOR_CYCLE(type, name, count)                                     \
  for (type name = count; name >= 0; name--)

#ifdef RG_UTF

#define rg_cout std::wcout
#define rg_ostrem std::wostream

#define rg_cin std::wcin
#define rg_string std::wstring
#define rg_char wchar_t
#define rg_to_string_(in) to_wstring(in)
#define RG_L L""
#else

#define rg_cout std::cout
#define rg_ostrem std::ostream

#define rg_cin std::cin
#define rg_string std::string
#define rg_char char
#define rg_to_string_(in) to_string(in)
#define RG_L
#endif

static uint rg_count_temp = 0; // todo

// #define rg_count                                                               \
//   rg_cout << (rg_count_temp++) << ", " << __FILE__ << ":" << __LINE__ << endl

// #define rg_count_clear rg_count_temp = 0

// static int rg_count_temp_deb = 0; // todo
// #define rg_count_deb                                                           \
//   RG_LOG_LOCK_DEBUG(to_string(rg_count_temp_deb++) +                           \
//                     ", line: " + to_string(__LINE__))

// #define rg_count_deb_clear rg_count_temp_deb = 0

#define elif else if

#define to_rvalue(type) const type & //todo 
#define to_rrvalue(type) const type //todo 