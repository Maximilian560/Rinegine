#pragma once
// Функция для выполнения команды в командной строке
int RG_CMD(string command){
#ifdef _WIN32
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
	if(conf.path=="err")return 0;
	if(conf.assinhrone){
		//char* tempChar = (char*)calloc(conf.path.size(),sizeof(char));
		//LPCSTR tempChar = s_calloc<char>(conf.path.size());
		LPCSTR tempConstChar = conf.path.c_str();
		LPSTR tempChar = s_calloc<char>(conf.path.size());
    //RG_Debug::addl(RG_LOG_DEBUG,"Path '"+conf.path+"' size = "+to_string(conf.path.size()));
		for(int i = 0; i<conf.path.size()&&conf.path[i]!='\0';i++){
			tempChar[i] = conf.path[i];
		}
		STARTUPINFO sti = {0};
		PROCESS_INFORMATION pi = {0};
		//CreateProcess(NULL,tempChar,NULL,NULL,false,NULL/**/,NULL,NULL/**/,NULL/**/,NULL/**/);
		RG_Debug::addl(RG_LOG_INFO,"Create new process: '" + string(tempChar)+"' in "+(conf.otherCMD?"other ":"same ")+"terminal");
    int out = CreateProcess(tempConstChar,NULL,NULL,NULL,false,(conf.otherCMD?CREATE_NEW_CONSOLE:INHERIT_PARENT_AFFINITY),NULL,NULL,&sti,&pi);//TODO
    if(!out)RG_Debug::addl(RG_LOG_ERROR,"Error create new process");
		return out;
		/*if(conf.InItFol){
			return CreateProcess(NULL,tempChar,NULL,NULL,false,(conf.otherCMD?CREATE_NEW_CONSOLE:INHERIT_PARENT_AFFINITY),NULL,NULL,&sti,&pi);
		}else{
			return CreateProcess(tempConstChar,NULL,NULL,NULL,false,(conf.otherCMD?CREATE_NEW_CONSOLE:INHERIT_PARENT_AFFINITY),NULL,NULL,&sti,&pi);//TODO
		}*/

		return 0;
	}else
	{
		return RG_CMD(conf.path);
	}
	return 0;
}




string RG_GetMainFolder(){
	//if(RG_MainArguments.size()<1){RG_Debug::addl(RG_LOG_ERROR,"A non-critical error occurred during engine initialization. You probably started the engine initialization in your own main function, if you are not going to use the RG_MainFolder variable to get the path to the executable file, ignore this error, otherwise refer to the documentation or contact the developer");return "";}
	if(RG_MainArguments.size()<1){RG_Debug::addl(RG_LOG_ERROR,"code: do"+to_string(__LINE__));return "";}
    string fol;
    int i;
    for(i = RG_MainArguments[0].size()-1;i>=0&&RG_MainArguments[0][i]!='\\'&&RG_MainArguments[0][i]!='/';i--);
		for(int j = 0; j<i;j++){
			fol+=RG_MainArguments[0][j];
		}
		return fol;
};

// Комментарии сгенерированы GPT-4
