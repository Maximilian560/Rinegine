#pragma once
// Аргументы строки
RG_Array<string> RG_MainArguments;
RG_Array<wstring> RG_WMainArguments;

wchar_t** rg_to_warg(RG_Array<wstring> str) { //TODO WARNING!!
	wchar_t** out = RG::s_new<wchar_t*>(str.size());
	for (int i = 0; i < str.size(); i++) {
		// out[i] = str[i].c_str();
		out[i] = RG::s_new<wchar_t>(str[i].size());
		for (int j = 0; j < str[i].size(); j++) {
			out[i][j] = str[i][j];
		}
	}
	return out;
}
#ifdef RG_UTF
inline wstring rg_to_string(const string str) { return RG::utf8_decode(str); }
inline wstring rg_to_string(const wstring str) { return str; }

#else
inline string rg_to_string(const string str) { return str; }
inline string rg_to_string(const wstring str) { return RG::utf8_encode(str); }

#endif


// Функция для выполнения команды в командной строке
int RG_CMD(string command, bool print = true) {
#ifdef _WIN32
	if (print)rg_cout << "Command run: \"" << rg_to_string(command) << "\"\n\n\n";
	return system(command.c_str());
#endif
}
struct RG_ConfigRunProgram {
	string path = "err";
	bool assinhrone = true;
	bool InItFol = false;
	bool otherCMD = false;
};
int RG_RunProgram(RG_ConfigRunProgram conf) {
	if (conf.path == "err")return 0;
	if (conf.assinhrone) {
		//char* tempChar = (char*)calloc(conf.path.size(),sizeof(char));
		//LPCSTR tempChar = RG::s_new<char>(conf.path.size());
		LPCSTR tempConstChar = conf.path.c_str();
		LPSTR tempChar = RG::s_new<char>(conf.path.size());
		//RG_Debug::addl(RG_LOG_DEBUG,"Path '"+conf.path+"' size = "+to_string(conf.path.size()));
		for (int i = 0; i < conf.path.size() && conf.path[i] != '\0';i++) {
			tempChar[i] = conf.path[i];
		}
		STARTUPINFOA sti = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		//CreateProcess(NULL,tempChar,NULL,NULL,false,NULL/**/,NULL,NULL/**/,NULL/**/,NULL/**/);
		RG_Debug::addl(RG_LOG_INFO, "Create new process: '" + string(tempChar) + "' in " + (conf.otherCMD ? "other " : "same ") + "terminal");
		int out = CreateProcessA(tempConstChar, NULL, NULL, NULL, false, (conf.otherCMD ? CREATE_NEW_CONSOLE : INHERIT_PARENT_AFFINITY), NULL, NULL, &sti, &pi);//TODO
		if (!out)RG_Debug::addl(RG_LOG_ERROR, "Error create new process");

		RG::s_delete(tempChar);
		return out;
		/*if(conf.InItFol){
			return CreateProcess(NULL,tempChar,NULL,NULL,false,(conf.otherCMD?CREATE_NEW_CONSOLE:INHERIT_PARENT_AFFINITY),NULL,NULL,&sti,&pi);
		}else{
			return CreateProcess(tempConstChar,NULL,NULL,NULL,false,(conf.otherCMD?CREATE_NEW_CONSOLE:INHERIT_PARENT_AFFINITY),NULL,NULL,&sti,&pi);//TODO
		}*/

		return 0;
	} else {
		return RG_CMD(conf.path);
	}
	return 0;
}




string RG_GetMainFolder() {
	//if(RG_MainArguments.size()<1){RG_Debug::addl(RG_LOG_ERROR,"A non-critical error occurred during engine initialization. You probably started the engine initialization in your own main function, if you are not going to use the RG_MainFolder variable to get the path to the executable file, ignore this error, otherwise refer to the documentation or contact the developer");return "";}
	if (RG_MainArguments.size() < 1) { RG_Debug::addl(RG_LOG_ERROR, "code: oD" + to_string(__LINE__));return ""; }
	string fol;
	int i;
	for (i = RG_MainArguments[0].size() - 1;i >= 0 && RG_MainArguments[0][i] != '\\' && RG_MainArguments[0][i] != '/';i--);
	for (int j = 0; j < i;j++) {
		fol += RG_MainArguments[0][j];
	}
	return fol;
};

wstring RG_WGetMainFolder() {
	if (RG_WMainArguments.size() < 1) { RG_Debug::addl(RG_LOG_ERROR, "code: oD" + to_string(__LINE__));return L""; }
	wstring fol;
	int i;
	for (i = RG_WMainArguments[0].size() - 1;i >= 0 && RG_WMainArguments[0][i] != L'\\' && RG_WMainArguments[0][i] != L'/';i--);
	for (int j = 0; j < i;j++) {
		fol += RG_WMainArguments[0][j];
	}
	return fol;
}

namespace RG {
	template<class type>
	struct vec2 {
		type x = type(), y = type();
		type& r = x;
		type& g = y;
		type& s = x;
		type& t = y;
		void operator=(vec2<type> in) {
			x = in.x;
			y = in.y;
		}

		type& operator[](int i) {
			return (&x)[i % 2];
		}
		vec2 operator*(const vec2& in) {
			return { x * in.x,y * in.y };
		}
		vec2 operator*(const POINT2D<type>& in) {
			return { x * in.x,y * in.y };
		}
	};
	template<class type>
	struct vec3 {
		type x = type(), y = type(), z = type();
		type& r = x;
		type& g = y;
		type& b = z;
		type& s = x;
		type& t = y;
		type& p = z;
		void operator=(vec3<type> in) {
			x = in.x;
			y = in.y;
			z = in.z;
		}
		void operator=(vec2<type> in) {
			x = in.x;
			y = in.y;
		}
		vec3<type>& operator=(std::initializer_list<type> list) {
			auto it = list.begin();
			if (it != list.end()) x = *it++;
			if (it != list.end()) y = *it++;
			if (it != list.end()) z = *it++;
			return *this;
		}
		vec3<type> operator*(const vec3<type>& in) {
			return { x * in.x,y * in.y,z * in.z };
		}
		vec3<type> operator*(const type& in) {
			return { x * in,y * in,z * in };
		}
		vec3<type> operator+(const vec3<type>& in) {
			return { x + in.x,y + in.y,z + in.z };
		}
		vec3<type> operator+(const type& in) {
			return { x + in,y + in,z + in };
		}
		vec3<type> operator-(const vec3<type>& in) {
			return { x - in.x,y - in.y,z - in.z };
		}
		vec3<type> operator-(const type& in) {
			return { x - in,y - in,z - in };
		}

		void operator+=(const vec3<type>& in) {
			x += in.x;
			y += in.y;
			z += in.z;
		}
		type& operator[](int i)const {
			return (&x)[i % 3];
		}
	};
	template<class type>
	struct vec4 {
		type x = type(), y = type(), z = type(), w = type();
		type& r = x;
		type& g = y;
		type& b = z;
		type& a = w;
		type& s = x;
		type& t = y;
		type& p = z;
		type& q = w;
		template<class type2>
		void operator=(RG_Matrix<type2>in) {
			if (in.size(0) >= 4) {
				&x[0] = in.get(0, 0);
				&x[1] = in.get(1, 0);
				&x[2] = in.get(2, 0);
				&x[3] = in.get(3, 0);
			}elif(in.size(1) >= 4) {
				&x[0] = in.getyx(0, 0);
				&x[1] = in.getyx(1, 0);
				&x[2] = in.getyx(2, 0);
				&x[3] = in.getyx(3, 0);
			}elif(in.size(0) != 0 || in.size(1) != 0) {
				RG_Debug::addl(RG_LOG_CRITICAL, "vec4 = matrix, size less 4 bun != 0, not support yet");
			} else {
				RG_Debug::addl(RG_LOG_CRITICAL, "vec4 = matrix, size == 0");
			}
		}



		template<class type2>
		void operator=(RG_Array<type2>in) {
			&x[0] = in[0];
			&x[1] = in[1];
			&x[2] = in[2];
			&x[3] = in[3];
		}
		void operator=(vec4<type> in) {
			x = in.x;
			y = in.y;
			z = in.z;
			w = in.w;
		}
		void operator=(vec3<type> in) {
			x = in.x;
			y = in.y;
			z = in.z;
		}
		void operator=(vec2<type> in) {
			x = in.x;
			y = in.y;
		}
		type& operator[](int i)const {
			return (&x)[i % 4];
		}
		template<class type2>
		vec4<type> operator*(const RG_Matrix<type2>& in) {
			vec4<type> out;
			out.x = x * in.get(0, 0) + y * in.get(0, 1) + z * in.get(0, 2) + w * in.get(0, 3);
			out.y = x * in.get(1, 0) + y * in.get(1, 1) + z * in.get(1, 2) + w * in.get(1, 3);
			out.z = x * in.get(2, 0) + y * in.get(2, 1) + z * in.get(2, 2) + w * in.get(2, 3);
			out.w = x * in.get(3, 0) + y * in.get(3, 1) + z * in.get(3, 2) + w * in.get(3, 3);
			return out;
		}

		// vec4<type> operator*(RG_Matrix<type> in) {
		// 	vec4<type> out;
		// 	out.x = x * in[0][0] + y * in[1][0] + z * in[2][0] + w * in[3][0];
		// 	out.y = x * in[0][1] + y * in[1][1] + z * in[2][1] + w * in[3][1];
		// 	out.z = x * in[0][2] + y * in[1][2] + z * in[2][2] + w * in[3][2];
		// 	out.w = x * in[0][3] + y * in[1][3] + z * in[2][3] + w * in[3][3];
		// 	return out;
		// }
	};
}
/*
template<class type>
wostream& operator<<(wostream& out, RG::vec4<type>& in) {
	out << "["<<in.x << L" " << in.y << L" " << in.z << L" " << in.w<<"]";
	return out;
}*/

template<class type>
ostream& operator<<(ostream& st, RG::vec2<type>& in) {
	st << in.x << " " << in.y;
	return st;
}

template<class type>
ostream& operator<<(ostream& st, RG::vec3<type>& in) {
	st << in.x << " " << in.y << " " << in.z;
	return st;
}

template<class type>
ostream& operator<<(ostream& st, RG::vec4<type>& in) {
	st << in.x << " " << in.y << " " << in.z << " " << in.w;
	return st;
}

template<class type>
wostream& operator<<(wostream& st, RG::vec2<type>& in) {
	st << in.x << " " << in.y;
	return st;
}

template<class type>
wostream& operator<<(wostream& st, RG::vec3<type>& in) {
	st << in.x << " " << in.y << " " << in.z;
	return st;
}

template<class type>
wostream& operator<<(wostream& st, RG::vec4<type>& in) {
	st << in.x << " " << in.y << " " << in.z << " " << in.w;
	return st;
}

/*inline char* rg_stringToChar(to_rvalue(string)in){
	//char* c = RG::s_new<char>(in.size());
	char c[in.size()];
	for(int i = 0; i<in.size()-1;i++){
		c[i] = in[i];
	}
	return c;
}*/




// Комментарии сгенерированы GPT-4
