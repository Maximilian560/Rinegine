
#pragma once
// Аргументы строки
RG_Array<string> RG_MainArguments;
RG_Array<wstring> RG_WMainArguments;


#ifdef RG_UTF
inline wstring rg_to_string(const string str){ return RG::utf8_decode(str); }
inline wstring rg_to_string(const wstring str){ return str; }
#else
inline string rg_to_string(const string str){ return str; }
inline string rg_to_string(const wstring str){ return RG::utf8_encode(str); }
#endif

// Функция для выполнения команды в командной строке
int RG_CMD(string command, bool print = false){
#ifdef _WIN32
	if(print)rg_cout << "Command run: \"" << rg_to_string(command) << "\"\n";
	return system(command.c_str());
#endif
}
struct RG_ConfigRunProgram{
	string path = "err";
	bool assinhrone = true;
	bool InItFol = false;
	bool otherCMD = false;
};
int RG_RunProgram(RG_ConfigRunProgram conf){
	if(conf.path == "err")return 0;
	if(conf.assinhrone){
		//char* tempChar = (char*)calloc(conf.path.size(),sizeof(char));
		//LPCSTR tempChar = RG::Lock::s_new<char>(conf.path.size());
		LPCSTR tempConstChar = conf.path.c_str();
		LPSTR tempChar = RG::Lock::s_new<char>(conf.path.size());
		//RG_Debug::addl(RG_LOG_LOCK_DEBUG,"Path '"+conf.path+"' size = "+to_string(conf.path.size()));
		for(int i = 0; i < conf.path.size() && conf.path[i] != '\0';i++){
			tempChar[i] = conf.path[i];
		}
		STARTUPINFOA sti = {0};
		PROCESS_INFORMATION pi = {0};
		//CreateProcess(NULL,tempChar,NULL,NULL,false,NULL/**/,NULL,NULL/**/,NULL/**/,NULL/**/);
		RG_Debug::addl(RG_LOG_LOCK_INFO, "Create new process: '" + string(tempChar) + "' in " + (conf.otherCMD ? "other " : "same ") + "terminal");
		int out = CreateProcessA(tempConstChar, NULL, NULL, NULL, false, (conf.otherCMD ? CREATE_NEW_CONSOLE : INHERIT_PARENT_AFFINITY), NULL, NULL, &sti, &pi);//TODO
		if(!out)RG_Debug::addl(RG_LOG_LOCK_ERROR, "Error create new process");

		RG::Lock::s_delete(tempChar);
		return out;
		/*if(conf.InItFol){
			return CreateProcess(NULL,tempChar,NULL,NULL,false,(conf.otherCMD?CREATE_NEW_CONSOLE:INHERIT_PARENT_AFFINITY),NULL,NULL,&sti,&pi);
		}else{
			return CreateProcess(tempConstChar,NULL,NULL,NULL,false,(conf.otherCMD?CREATE_NEW_CONSOLE:INHERIT_PARENT_AFFINITY),NULL,NULL,&sti,&pi);//TODO
		}*/

		return 0;
	} else{
		return RG_CMD(conf.path);
	}
	return 0;
}




string RG_GetMainFolder(){
	//if(RG_MainArguments.size()<1){RG_Debug::addl(RG_LOG_LOCK_ERROR,"A non-critical error occurred during engine initialization. You probably started the engine initialization in your own main function, if you are not going to use the RG_MainFolder variable to get the path to the executable file, ignore this error, otherwise refer to the documentation or contact the developer");return "";}
	if(RG_MainArguments.size() < 1){ RG_Debug::addl(RG_LOG_LOCK_ERROR, "code: oD" + to_string(__LINE__));return ""; }
	string fol;
	int i;
	for(i = RG_MainArguments[0].size() - 1;i >= 0 && RG_MainArguments[0][i] != '\\' && RG_MainArguments[0][i] != '/';i--);
	for(int j = 0; j < i;j++){
		fol += RG_MainArguments[0][j];
	}
	return fol;
};

wstring RG_WGetMainFolder(){
	if(RG_WMainArguments.size() < 1){ RG_Debug::addl(RG_LOG_LOCK_ERROR, "code: oD" + to_string(__LINE__));return L""; }
	wstring fol;
	int i;
	for(i = RG_WMainArguments[0].size() - 1;i >= 0 && RG_WMainArguments[0][i] != L'\\' && RG_WMainArguments[0][i] != L'/';i--);
	for(int j = 0; j < i;j++){
		fol += RG_WMainArguments[0][j];
	}
	return fol;
}

namespace RG{
	template<class type>
	struct vec2{
		type x = type(), y = type();
		type& r = x;
		type& g = y;
		type& s = x;
		type& t = y;

		void operator=(vec2<type> in){
			x = in.x;
			y = in.y;
		}

		type& operator[](int i){
			return (&x)[i % 2];
		}
	};

	template<class type>
	struct vec3: public vec2<type>{
		// Теперь переменные vec2 будут расположены раньше
		type z = type();
		type& b = z;
		type& p = z;

		void operator=(vec3<type> in){
			this->x = in.x;
			this->y = in.y;
			this->z = in.z;
		}

		type& operator[](int i) const{
			return (&this->x)[i % 3];
		}
	};

	template<class type>
	struct vec4: public vec3<type>{
		// Теперь переменные vec3 будут расположены раньше
		type w = type();
		type& a = w;
		type& q = w;

		// Переопределение оператора присваивания
		void operator=(vec4<type> in){
			this->x = in.x;
			this->y = in.y;
			this->z = in.z;
			this->w = in.w;
		}

		type& operator[](int i) const{
			return (&this->x)[i % 4];
		}

		// Операция умножения на матрицу
		template<class type2>
		vec4<type> operator*(const RG_Matrix<type2>& in){
			vec4<type> out;
			out.x = this->x * in.get(0, 0) + this->y * in.get(0, 1) + this->z * in.get(0, 2) + this->w * in.get(0, 3);
			out.y = this->x * in.get(1, 0) + this->y * in.get(1, 1) + this->z * in.get(1, 2) + this->w * in.get(1, 3);
			out.z = this->x * in.get(2, 0) + this->y * in.get(2, 1) + this->z * in.get(2, 2) + this->w * in.get(2, 3);
			out.w = this->x * in.get(3, 0) + this->y * in.get(3, 1) + this->z * in.get(3, 2) + this->w * in.get(3, 3);
			return out;
		}
	};
}

template<class type>
ostream& operator<<(ostream& st, RG::vec2<type>& in){
	st << in.x << " " << in.y;
	return st;
}

template<class type>
ostream& operator<<(ostream& st, RG::vec3<type>& in){
	st << in.x << " " << in.y << " " << in.z;
	return st;
}

template<class type>
ostream& operator<<(ostream& st, RG::vec4<type>& in){
	st << in.x << " " << in.y << " " << in.z << " " << in.w;
	return st;
}

template<class type>
wostream& operator<<(wostream& st, RG::vec2<type>& in){
	st << in.x << " " << in.y;
	return st;
}

template<class type>
wostream& operator<<(wostream& st, RG::vec3<type>& in){
	st << in.x << " " << in.y << " " << in.z;
	return st;
}

template<class type>
wostream& operator<<(wostream& st, RG::vec4<type>& in){
	st << in.x << " " << in.y << " " << in.z << " " << in.w;
	return st;
}

/*inline char* rg_stringToChar(to_rvalue(string)in){
	//char* c = RG::Lock::s_new<char>(in.size());
	char c[in.size()];
	for(int i = 0; i<in.size()-1;i++){
		c[i] = in[i];
	}
	return c;
}*/



// Комментарии сгенерированы GPT-4
