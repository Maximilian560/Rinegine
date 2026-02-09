#pragma once

#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/lang"

namespace RG {
	namespace Lang{
		enum Type {
			Non = -1,
			Rus,
			Eng,
		};
	}
}

uint languageWindows;

class RG_Lang {
	string path = "data/lang";
	string type = ".rglg";
	bool _init = false;
	string BASELang[2] =
	{
		"ru",
		"en"
	};
	uint lang = RG::Lang::Type::Non;

	// wstring* words = nullptr;
	// wstring* names = nullptr;
	RG_Array<wstring>words, names;

	int size = 0;

	bool isLoad = false;


public:
	bool is_init() {
		return _init;
	}
	uint getLang() {
		return lang;
	}
	RG_Lang() {}
	void set_lang(RG::Lang::Type lng) {
		lang = lng;
	}
	RG_Lang(string pat) {
		init(pat);
	}

	RG_Lang(int a) {
		if (a == 0)return;
		load();
	}

	void init() {
		if (_init)return;
		_init = 1;
		load();
	}
	void init(string pat) {
		if (_init)return;
		_init = 1;
		path = pat;
		load();
	}
	void load() {
		if (isLoad) { return; }
		// if(lang == RG::Type::Non)lang = RG::Type::Eng;
		if (RG::Lang::Type::Non == lang) {

			languageWindows = GetSystemDefaultLangID();

			switch (languageWindows) {
			case 1049: lang = RG::Lang::Type::Rus; break;
			default: lang = RG::Lang::Type::Eng;
			}
		}

		wstring file = RG::WFileLoad(path + "/" + BASELang[lang] + type);
		if (file == RG_ERROR_WSTRING) {
			RG_LOG_LOCK_ERROR("Translation file not found: " + path + "/" + BASELang[lang] + type);
		}

		for (int i = 0; i < (int)file.size(); i++) {
			if (file[i] == L';')size++;
		}

		// words = new wstring[size];
		// names = new wstring[size];
		words.resize(size);
		names.resize(size);

		bool temp1 = false, temp2 = false;
		int temp3 = -1;

		for (int i = 0; i < size; i++) {
			for (int j = 0; file[temp3 + 1] != L';'; j++) {

				temp3++;
				if (file[temp3] == L'{') { temp1 = true; continue; }
				if (file[temp3] == L'}') { temp1 = false; temp2 = true; continue; }
				//if(file[temp3]==L':'&&!temp1&&temp3){temp2=true;continue;temp3 = false;}

				if (temp1) {
					names[i] += file[temp3];
				}
				if (temp2) {
					words[i] += file[temp3];
				}
			}
			//rg_cout<<names[i]<<endl;
			//rg_cout << words[i] << endl;
			//rg_cout << names[i] << endl;


			temp1 = false;
			temp2 = false;
			temp3++;


		}


	}

	wstring getWstring(wstring name) {
		wstring wreturn = name;
		bool found = false;
		for (int i = 0; i < size; i++) {
			if (names[i] == name) { wreturn = words[i]; found = 1; break; }
		}
		if (!found) {
			RG_LOG_LOCK_WARNING(L"Translation to \"" + name + L"\" not found");
		}
		return wreturn;
	}

}RG_StandartLang;
