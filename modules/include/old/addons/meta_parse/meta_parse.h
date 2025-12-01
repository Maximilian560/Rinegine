#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/meta_parse"
/*
  class Meta_Parser {
  public:
    struct Node {
      string key, value;
      RG_Array<Node*> children;

      Node(const string& k, const string& v = "") : key(k), value(v) {}
      ~Node() { for (auto* child : children)  RG::s_delete(child); }
    };

    explicit Meta_Parser(const string& src) : source(src), pos(0) {}
    Node* parse() {
      skipWhitespace();
      if (!match('{')) return nullptr;

      Node* root = RG::s_new<Node>(1, Node(""));

      while (pos < source.size() && !match('}')) {
        skipWhitespace();
        string key = readKeyOrValue();
        skipWhitespace();

        if (match('=')) {
          string value = readKeyOrValue();
          root->children.push_back(RG::s_new<Node>(1, Node(key, value)));
        } else if (match('{')) {
          Node* child = RG::s_new<Node>(1, Node(key));
          child->children.push_back(parse());
          root->children.push_back(child);
        }
        match(','); // Optional comma
      }
      return root;
    }

  private:
    string source;
    uint pos;

    void skipWhitespace() {
      while (pos < source.size() && isspace(source[pos])) ++pos;
    }
    bool match(char c) {
      if (pos < source.size() && source[pos] == c) { ++pos; return true; }
      return false;
    }
    string readKeyOrValue() {
      skipWhitespace();
      if (match('"')) { // Quoted string
        uint start = pos;
        while (pos < source.size() && source[pos] != '"') ++pos;
        return source.substr(start, pos++ - start);
      }
      // Unquoted key or value
      uint start = pos;
      while (pos < source.size() && !isspace(source[pos]) && source[pos] != '=' && source[pos] != ',' && source[pos] != '{' && source[pos] != '}') ++pos;
      return source.substr(start, pos - start);
    }
  };*/
namespace RG {
  class Parser {
    inline static RG_Array<rg_string> Error = RG_Array<rg_string>(1, RG_L"Not_Found");
    inline static RG_Array<rg_string> No_Value = RG_Array<rg_string>(1, RG_L"No_Value");
    rg_string source;
    uint pos = 0;
  public:
    static rg_string error() {
      return Error[0];
    }

    static rg_string no_value() {
      return No_Value[0];
    }


    static bool some_wrong(rg_string in) {
      return (in == No_Value[0] || in == Error[0]);
    }

    static bool some_wrong(RG_Array<rg_string> in) {
      return (in.size() == 1 && (in[0] == No_Value[0] || in[0] == Error[0]));
    }

    // inline static bool error(RG_Array<string> in) {
    //   if (in.size() == 1)
    //     return error(rg_to_string(in[0]));
    //   return false;
    // }
    // inline static bool no_value(RG_Array<string> in) {
    //   if (in.size() == 1)
    //     return no_value(rg_to_string(in[0]));
    //   return false;
    // }
    // inline static bool some_wrong(RG_Array<string> in) {
    //   if (in.size() == 1)
    //     return some_wrong(rg_to_string(in[0]));
    //   return false;
    // }
    // inline static bool error(string in) {
    //   return error(rg_to_string(in));
    // }
    // inline static bool no_value(string in) {
    //   return no_value(rg_to_string(in));
    // }
    // inline static bool some_wrong(string in) {
    //   return some_wrong(rg_to_string(in));
    // }

    static bool error(RG_Array<rg_string> in) {
      if (in.size() == 1)
        if (in[0] == Error[0])return true;
      return false;
    }
    static bool no_value(RG_Array<rg_string> in) {
      if (in.size() == 1)
        if (in[0] == No_Value[0])return true;
      return false;
    }
    static bool error(rg_string in) {
      if (in == Error[0])return true;
      return false;
    }
    static bool no_value(rg_string in) {
      if (in == No_Value[0])return true;
      return false;
    }
    struct Node {
      rg_string key;
      RG_Array<rg_string> value;
      // Node* parent = nullptr;
      RG::Pointer<Node> parent;
      RG_Array<RG::Pointer<Node>> childrens;
      Node() {};
      Node(rg_string& k) :key(k), value(0) {}
      Node(rg_string& k, rg_string v) :key(k), value(1, v) {}
      Node(rg_string& k, RG_Array<rg_string> v) :key(k), value(v) {}

      void clear() {
        parent.clear();
        value.clear();
        childrens.clear();
      }
      ~Node() {
        parent.clear();
        value.clear();
        childrens.clear();
      }
    };
    RG::Pointer<Node> root;

    void init() {
      if (source.size() == 0)return;
      if (root.is_init()) { clear(); }
      root = parse();
      root->key = RG_L"main";
    }
    // void init(rg_string in) {
    //   source = (in);
    //   init();
    // }
    // void init(string in) {
    //   source = (rg_to_string(in));
    //   init();
    // }
    template<class in_string>
    void init(in_string in){
      source = rg_to_string(in);
      init();
    }
    // Parser(rg_string in) :source(in) {
    //   init();
    // }
    // Parser(string in) :source(rg_to_string(in)) {
    //   init();
    // }
    template<class in_string>
    Parser(in_string in):source(rg_to_string(in)){
      init();
    }
    void init_debug() {
      if (source.size() == 0)return;
      if (root.is_init()) { clear(); }
      root = parse_debug();
      root->key = RG_L"main";
    }
    void init_debug(rg_string in) {
      source = (in);
      init_debug();
    }

    // void init_debug(string in) {
    //   source = (rg_to_string(in));
    //   init_debug();
    // }
    void loadinit(const rg_string& path) {
      source = (RG::FileLoad(path));
    }
    // void loadinit(const string& path) {
    //   source = (RG::FileLoad(path));
    // }
    Parser() {};
  private:
    RG::Pointer<Node> parse() {
      // Node* node = RG::s_new<Node>(1);
      RG::Pointer<Node> node;
      node.init();
      // Node* node;
      // node = s_new
      // node.init();
      rg_string temp, tempKey;
      RG_Array<rg_string>ttemp;
      // RG_Array tempKey(1);
      bool quotes = false;
      bool array = false;
      for (; pos < source.size(); pos++) {
        // Sleep(60);
        if (source[pos] == '[' && pos == 0 || source[pos] == '[' && source[pos - 1] != '\\') {
          ttemp.fast_clear();
          array = 1;
          pos++;
        } else
          if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') {
            quotes = 1;
            pos++;
          }

        if (quotes) {
          for (; pos < source.size() && quotes; pos++) {
            // Sleep(60);
            if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') { quotes = 0; pos++; break; }
            temp += source[pos];
          }
        }
        if (array) {
          for (; pos < source.size() && array; pos++) {
            // Sleep(60);
            if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') {
              quotes = 1;
              pos++;
            }
            if (quotes) {
              for (; pos < source.size() && quotes; pos++) {
                // Sleep(60);
                if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') { quotes = 0; pos++; break; }
                temp += source[pos];
              }
              ttemp.fastpush(temp);
              temp.clear();
            }
            if (source[pos] == ']' && pos == 0 || source[pos] == ']' && source[pos - 1] != '\\') { array = 0; pos++; break; }
          }
        }

        if (source[pos] == '/' && pos < source.size() - 1 && source[pos + 1] == '/') {
          for (; pos < source.size() && source[pos] != '\n'; pos++) {}; continue;
        }
        if (source[pos] == '=') {
          tempKey = temp;
          temp.clear();
          continue;
        }
        if (source[pos] == '{') {
          pos++;
          // node = parse();
          // RG::Pointer<Node> cld = parse();
          // cld->key = temp;
          node->childrens.fastpush(parse());
          node->childrens[-1]->key = temp;
          temp.clear();
          tempKey.clear();
          //node->childrens.push_back(parse());
          continue;
        }
        if (source[pos] == ',') {
          if (tempKey.size()) {
            if (ttemp.size()) {
              node->childrens.fastpush((RG::s_new<Node>(1, Node(tempKey, ttemp))));//RG::s_new<Node>(1, Node(tempKey, ttemp)));
              ttemp.fast_clear();
            } else {
              node->childrens.fastpush((RG::s_new<Node>(1, Node(tempKey, temp))));
            }
            tempKey.clear();
            temp.clear();
          }elif(temp.size()) {
            node->childrens.fastpush((RG::s_new<Node>(1, Node(temp))));
            temp.clear();
          }
          continue;
        }
        if (source[pos] == '}') {
          if (tempKey.size()) {
            node->childrens.fastpush((RG::s_new<Node>(1, Node(tempKey, temp))));
            tempKey.clear();
            temp.clear();
          }elif(temp.size()) {
            node->childrens.fastpush((RG::s_new<Node>(1, Node(temp))));
            temp.clear();
          }
          break;
        }
        if (source[pos] > ' ' && !quotes) {
          temp += source[pos];
        }
      }
      return node;
    }

    RG::Pointer<Node> parse_debug() {
      // Node* node = RG::s_new<Node>(1);
      RG_LOG_INFO("parse start");
      RG::Pointer<Node> node;
      node.init();
      RG_LOG_INFO("node init");
      // Node* node;
      // node = s_new
      // node.init();
      rg_string temp, tempKey;
      RG_Array<rg_string>ttemp;
      // RG_Array tempKey(1);
      bool quotes = false;
      bool array = false;
      RG_LOG_INFO("cycle start");
      for (; pos < source.size(); pos++) {
        // Sleep(60);
        if (source[pos] == '[' && pos == 0 || source[pos] == '[' && source[pos - 1] != '\\') {
          RG_LOG_INFO("get [");
          ttemp.fast_clear();
          array = 1;
          pos++;
        } else
          if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') {
            RG_LOG_INFO("get \"");
            quotes = 1;
            pos++;
          }

        if (quotes) {
          for (; pos < source.size() && quotes; pos++) {
            // Sleep(60);
            if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') {
              RG_LOG_INFO("get \", quotes set 0");
              quotes = 0; pos++; break;
            }
            temp += source[pos];
          }
        }
        if (array) {
          for (; pos < source.size() && array; pos++) {
            // Sleep(60);
            if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') {
              RG_LOG_INFO("get \" in array");
              quotes = 1;
              pos++;
            }
            if (quotes) {
              for (; pos < source.size() && quotes; pos++) {
                // Sleep(60);
                if (source[pos] == '"' && pos == 0 || source[pos] == '"' && source[pos - 1] != '\\') {
                  RG_LOG_INFO("get \" in array, quotes set 0");
                  quotes = 0; pos++; break;
                }
                temp += source[pos];
              }
              ttemp.fastpush(temp);
              temp.clear();
            }
            if (source[pos] == ']' && pos == 0 || source[pos] == ']' && source[pos - 1] != '\\') {
              RG_LOG_INFO("get ], array set 0");
              array = 0; pos++; break;
            }
          }
        }

        if (source[pos] == '/' && pos < source.size() - 1 && source[pos + 1] == '/') {
          int skip_int = 0;
          RG_LOG_INFO("comment, skip...");

          for (; pos < source.size() && source[pos] != '\n'; pos++) { skip_int++; };
          RG_LOG_INFO("skiped " + to_string(skip_int) + " chars");
          continue;
        }
        if (source[pos] == '=') {
          RG_LOG_INFO("get =, temp key set: '" + temp + "'");
          tempKey = temp;
          temp.clear();
          continue;
        }
        if (source[pos] == '{') {
          RG_LOG_INFO("get {, children create. Parent name:'" + temp + "', key was:'" + tempKey + "'");
          pos++;
          // node = parse_debug();
          // RG::Pointer<Node> cld = parse_debug();
          // cld->key = temp;
          node->childrens.fastpush(parse_debug());
          node->childrens[-1]->key = temp;
          temp.clear();
          tempKey.clear();
          //node->childrens.push_back(parse_debug());
          continue;
        }
        if (source[pos] == ',') {
          RG_LOG_INFO("get ,...");
          if (tempKey.size()) {
            RG_LOG_INFO("temp key more then 0...");
            if (ttemp.size()) {
              RG_LOG_INFO(RG_L"ttemp more zero too, new key/par:'" + tempKey + RG_L"'=='" + ttemp.get_string() + RG_L"'");
              node->childrens.fastpush((RG::s_new<Node>(1, Node(tempKey, ttemp))));//RG::s_new<Node>(1, Node(tempKey, ttemp)));
              ttemp.fast_clear();
            } else {
              RG_LOG_INFO("ttemp equals zero, new key/par:'" + tempKey + "'=='" + temp + "'");
              node->childrens.fastpush((RG::s_new<Node>(1, Node(tempKey, temp))));
            }
            tempKey.clear();
            temp.clear();
          }elif(temp.size()) {
            RG_LOG_INFO("temp key equals 0, new par :'"+temp+"'");
            node->childrens.fastpush((RG::s_new<Node>(1, Node(temp))));
            temp.clear();
          }
          continue;
        }
        if (source[pos] == '}') {
            RG_LOG_INFO("get }...");
          if (tempKey.size()) {
            RG_LOG_INFO("temp key more then 0, new par:'" + tempKey + "'=='" + temp + "'");
            node->childrens.fastpush((RG::s_new<Node>(1, Node(tempKey, temp))));
            tempKey.clear();
            temp.clear();
          }elif(temp.size()) {
            RG_LOG_INFO("temp key more zero, new par :'"+temp+"'");
            node->childrens.fastpush((RG::s_new<Node>(1, Node(temp))));
            temp.clear();
          }
          break;
        }
        if (source[pos] > ' ' && !quotes) {
          temp += source[pos];
        }
      }
      RG_LOG_INFO("parse done:");
      print();
      return node;
    }

    // rg_string operator[](rg_string key){
    //   Node* node = root;
    //   rg_string temp;
    //   for(int i = 0; i <= key.size();i++){
    //     if(key[i] == '\\' || key[i] == '/' || i == key.size()){
    //       for(int j = 0; j < node->childrens.size();j++){
    //         if(node->childrens[j]->key == temp){
    //           node = node->childrens[j];
    //           break;
    //         }
    //       }
    //       temp.clear();
    //       continue;
    //     } else
    //       temp += key[i];
    //   }
    //   if(node == root){
    //     return (key + L" not found");
    //   } else
    //     return node->value[0];
    // }
  public:
    RG_Array<rg_string>& operator[](rg_string key) {
      Node* node = root;
      rg_string temp;
      for (int i = 0; i <= key.size(); i++) {
        if (key[i] == '\\' || key[i] == '/' || i == key.size()) {
          for (int j = 0; j < node->childrens.size(); j++) {
            if (node->childrens[j]->key == temp) {
              node = node->childrens[j];
              break;
            }
          }
          temp.clear();
          continue;
        } else
          temp += key[i];
      }
      if (node == root) {
        // return (key + L" not found");
        return Error;
      } else
        return node->value;
    }
    // inline RG_Array<rg_string>& operator[](string key) {
    //   return operator[](rg_to_string(key));
    // }
    // inline RG_Array<rg_string> get(string key) {
    //   return get(rg_to_string(key));
    // }
    // inline rg_string get(string key, int index) {
    //   return get(rg_to_string(key), index);
    // }
    RG_Array<rg_string> get(rg_string key) {
      Node* node = root;
      rg_string temp, test;
      for (int i = 0; i <= key.size(); i++) {
        if (key[i] == '\\' || key[i] == '/' || i == key.size()) {
          for (int j = 0; j < node->childrens.size(); j++) {
            if (node->childrens[j]->key == temp) {
              node = node->childrens[j];
              break;
            }
          }
          temp.clear();
          continue;
        } else
          temp += key[i];
      }
      if (node == root) {
        // return (key + L" not found");
        return Error;
      } else
        return node->value;
    }
    rg_string get(rg_string key, int index) {
      Node* node = root;
      rg_string temp;
      bool found = false;
      for (int i = 0; i <= key.size(); i++) {
        if (key[i] == '\\' || key[i] == '/' || i == key.size()) {
          for (int j = 0; j < node->childrens.size(); j++) {
            if (node->childrens[j]->key == temp) {
              node = node->childrens[j];
              found = true;
              break;
            } else {
              found = false;
            }
          }
          temp.clear();
          continue;
        } else
          temp += key[i];
      }
      if (node == root) {
        // return (key + L" not found");
        return Error[0];
      } else {
        if (node->value.size() > index) {
          return node->value[index];
        } else {
          if (found)return No_Value[0];
          else
            return Error[0];
        }

      }
    }


    void clear() {
      // if(root)RG::s_delete(root);
      root.clear();
    }
    ~Parser() {
      clear();
    }

    void print() {
      print(root);
    }
    int step = 0;
    void print(RG::Pointer<Node>& in) {
      // if(in == root)
      rg_cout << "\n";
      for (int i = 0; i < step; i++)rg_cout << "  ";
      rg_cout << RG_L"Key: " << rg_to_string(in->key) << endl;
      if (in->value.size()) {
        for (int i = 0; i < step; i++)rg_cout << "  ";
        rg_cout << RG_L"Value: "; in->value.print();
        // rg_cout << endl;
      }
      if (in->childrens.size()) {
        for (int i = 0; i < step; i++)rg_cout << "  ";
        rg_cout << RG_L"Childrens: {";
        step++;
        for (int i = 0; i < in->childrens.size(); i++) {
          print(in->childrens[i]);
        }
        step--;
        for (int i = 0; i < step; i++)rg_cout << "  ";
        rg_cout << RG_L"}\n";
      }
    }
  };
}