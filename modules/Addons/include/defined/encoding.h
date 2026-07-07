#pragma once




//#define RG_ENCODE_SIZE 0x80
/*enum RG_ENCODE{
  RG_ENCODE_ENG = 0x000,
  RG_ENCODE_RUS = 0x400,
}*/
/*#define RG_ENCODE_ENG_BEG 0x000
#define RG_ENCODE_ENG_SIZE 0x80
#define RG_ENCODE_ENGsup_BEG 0x80
#define RG_ENCODE_ENGsup_SIZE 0x20
#define RG_ENCODE_RUS_BEG 0x400
#define RG_ENCODE_RUS_SIZE 0x100*/


template <class type>
class RG_List{
  struct sheet{
    //RG_List<type>*PREV = nullptr;
    //RG_List<type>*NEXT = nullptr;
    sheet*PREV = nullptr;
    sheet*NEXT = nullptr;

    type NUM;

    operator type(){
      return NUM;
    }
    sheet* prev(){
      return PREV;
    }
    sheet* next(){
      return NEXT;
    }
  };

  RG_Array<sheet>sheets;
public:
   operator RG_Array<type>&(){
    return sheets;
  }
  int size(){
    return sheets.size();
  }
  RG_List<type> (initializer_list<type>t){
    sheets.resize(t.size());
    for(int i = 0; i<t.size();i++){
      sheets[i].NUM = t.begin()[i];
      if(i!=0){sheets[i].PREV = &sheets[i-1];}
      if(i!=t.size()-1){sheets[i].NEXT = &sheets[i+1];}
    }
  }
  
  type operator[](int i){
    return sheets[i];
  }
};
struct RG_ENCODE_TYPE{
  wchar_t size = 0;
  string name;
  wchar_t firstLet = 0;
  wchar_t lastLet = 0;
  wchar_t specialLet = L'Ё';
};

struct RG_ENCODE_VALUE{
  int pos = 0;
  int size = 0;
};

class RG_ENCODE{
  inline static RG_Array<RG_ENCODE_TYPE> encode{
    {0x080, "Basic Latin",L'A',L'Z'},
    {0x080, "Latin-1 Supplement"},
    {0x080, "Latin Extended-A"},
    {0xD0,  "Latin Extended-B"},
    {0x060, "IPA Extensions"},
    {0x050, "Spacing Modifier Letters"},
    {0x070, "Combining Diacritical Marks"},
    {0x090, "Greek and Coptic"},
    {0x100, "Cyrillic"},
    {0x30,  "Cyrillic Supplement"},
    {0x60,  "Armenian"},
    {0x70,  "Hebrew"},
    {0x100, "Arabic"},
    {0x50,  "Syriac"},
    {0x30,  "Arabic Supplement"},
    {0x40,  "Thaana"},
    {0x40,  "NKo"},
    {0x40,  "Samaritan"},
    {0x20,  "Mandaic"},
    {0x10,  "Syriac Supplement"},
    {0x30,  "Arabic Extended-B"},
    {0x60,  "Arabic Extended-A"},
    {0x80,  "Devanagari"},
    {0x80,  "Bengali"},
    {0x80,  "Gurmukhi"},
    {0x80,  "Gujarati"},
    {0x80,  "Oriya"},
    {0x80,  "Tamil"},
    {0x80,  "Telugu"},
    {0x80,  "Kannada"},
    {0x80,  "Malayalam"},
    {0x80,  "Sinhala"},
    {0x80,  "Thai"},
    {0x80,  "Lao"},
    {0x100, "Tibetan"},
    {0xA0,  "Myanmar"},
    {0x60,  "Georgian"},
    {0x100, "Hangul Jamo"},
    {0x180, "Ethiopic"},
    {0x20,  "Ethiopic Supplement"},
    {0x60,  "Cherokee"},
    {0x280, "Unified Canadian Aboriginal Syllabics"},
    {0x20,  "Ogham"},
    {0x60,  "Runic"},
    {0x20,  "Tagalog"},
    {0x20,  "Hanunoo"},
    {0x20,  "Buhid"},
    {0x20,  "Tagbanwa"},
    {0x80,  "Khmer"},
    {0xB0,  "Mongolian"},
    {0x50,  "Unified Canadian Aboriginal Syllabics Extended"},
    {0x50,  "Limbu"},
    {0x30,  "Tai Le"},
    {0x60,  "New Tai Lue"},
    {0x20,  "Khmer Symbols"},
    {0x20,  "Buginese"},
    {0x90,  "Tai Tham"},
    {0x50,  "Combining Diacritical Marks Extended"},
    {0x80,  "Balinese"},
    {0x40,  "Sundanese"},
    {0x40,  "Batak"},
    {0x50,  "Lepcha"},
    {0x30,  "Ol Chiki"},
    {0x10,  "Cyrillic Extended C"},
    {0x30,  "Georgian Extended"},
    {0x10,  "Sundanese Supplement"},
    {0x30,  "Vedic Extensions"},
    {0x80,  "Phonetic Extensions"},
    {0x40,  "Phonetic Extensions Supplement"},
    {0x40,  "Combining Diacritical Marks Supplement"},
    {0x100, "Latin Extended Additional"},
    {0x100, "Greek Extended"},
    {0x70,  "General Punctuation"},
    {0x30,  "Superscripts and Subscripts"},
    {0x30,  "Currency Symbols"},
    {0x30,  "Combining Diacritical Marks for Symbols"},
    {0x50,  "Letterlike Symbols"},
    {0x40,  "Number Forms"},
    {0x70,  "Arrows"},
    {256, "Mathematical Operators"},
    {256,"Miscellaneous Technical"},
    {64,"Control Pictures"},
    {32,"Optical Character Recognition"},
    {160,"Enclosed Alphanumerics"},
    {128,"Box Drawing"},
    {32,"Block Elements"},
    {96,"Geometric Shapes"},
    {256,"Miscellaneous Symbols"},
    {192,"Dingbats"},
    {48,"Miscellaneous Mathematical Symbols-A"},
    {16,"Supplemental Arrows-A"},
    {256,"Braille Patterns"},
    {128,"Supplemental Arrows-B"},
    {128,"Miscellaneous Mathematical Symbols-B"},
    {256,"Supplemental Mathematical Operators"},
    {256,"Miscellaneous Symbols and Arrows"},
    {96,"Glagolitic"},
    {32,"Latin Extended-C"},
    {128,"Coptic"},
    {48,"Georgian Supplement"},
    {80,"Tifinagh"},
    {96,"Ethiopic Extended"},
    {32,"Cyrillic Extended-A"},
    {128,"Supplemental Punctuation"},
    {128,"CJK Radicals Supplement"},
    {224,"Kangxi Radicals"},
    {16,"Ideographic Description Characters"},
    {64,"CJK Symbols and Punctuation"},
    {96,"Hiragana"},
    {96,"Katakana"},
    {48,"Bopomofo"},
    {96,"Hangul Compatibility Jamo"},
    {16,"Kanbun"},
    {32,"Bopomofo Extended"},
    {48,"CJK Strokes"},
    {16,"Katakana Phonetic Extensions"},
    {256,"Enclosed CJK Letters and Months"},
    {256,"CJK Compatibility"},
    {6592,"CJK Unified Ideographs Extension A"},
    {64,"Yijing Hexagram Symbols"},
    {20992,"CJK Unified Ideographs"},
    {1168,"Yi Syllables"},
    {64,"Yi Radicals"},
    {48,"Lisu"},
    {320,"Vai"},
    {96,"Cyrillic Extended-B"},
    {96,"Bamum"},
    {32,"Modifier Tone Letters"},
    {224,"Latin Extended-D"},
    {48,"Syloti Nagri"},
    {16,"Common Indic Number Forms"},
    {64,"Phags-pa"},
    {96,"Saurashtra"},
    {32,"Devanagari Extended"},
    {48,"Kayah Li"},
    {48,"Rejang"},
    {32,"Hangul Jamo Extended-A"},
    {96,"Javanese"},
    {32,"Myanmar Extended-B"},
    {96,"Cham"},
    {32,"Myanmar Extended-A"},
    {96,"Tai Viet"},
    {32,"Meetei Mayek Extensions"},
    {48,"Ethiopic Extended-A"},
    {64,"Latin Extended-E"},
    {80,"Cherokee Supplement"},
    {64,"Meetei Mayek"},
    {11184,"Hangul Syllables"},
    {80,"Hangul Jamo Extended-B"},
    {896,"High Surrogates"},
    {128,"High Private Use Surrogates"},
    {1024,"Low Surrogates"},
    {6400,"Private Use Area"},
    {512,"CJK Compatibility Ideographs"},
    {80,"Alphabetic Presentation Forms"},
    {688,"Arabic Presentation Forms-A"},
    {16,"Variation Selectors"},
    {16,"Vertical Forms"},
    {16,"Combining Half Marks"},
    {32,"CJK Compatibility Forms"},
    {32,"Small Form Variants"},
    {144,"Arabic Presentation Forms-B"},
    {240,"Halfwidth and Fullwidth Forms"},
    {16,"Specials"}
  };//https://symbl.cc/en/unicode/blocks/specials/ NEED COMPLITED
  
  /*static wchar_t operator[](string nam){
    int i = 0;
    for(;encode[i].name == nam;i++)if(i==encode.size());
    return encode[nam].size;
  }*/



  public:
  static wchar_t get_size(string nam){
    int i = 0;
    for(;encode[i].name != nam;i++)if(i==encode.size()-1)return -1;
    return encode[i].size;
  }

  static int get_id(string nam){
    int i = 0;
    for(;encode[i].name != nam;i++)if(i==encode.size()-1)return -1;
    return i;
  }

  static RG_ENCODE_VALUE get(string nam){
    wchar_t pos=0, size=0;
    int id = get_id(nam);
    if(id==-1)RG_Debug::addl(RG_LOG_CRITICAL,"encoding '"+nam+"' not found!");
    size = encode[id].size;
    //wcout<<endl<<L"name = "<<RG::utf8_decode(nam)<<endl;
    //wcout<<L"id = "<<to_wstring(id)<<endl;
    //wcout<<L"size = "<<to_wstring(size)<<endl;
    for(int i = 0; i<id;i++){
      pos+=encode[i].size;
    }
    //wcout<<L"pos = "<<to_wstring(pos)<<endl<<endl;
    return {pos,size};
  }


};
