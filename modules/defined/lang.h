#pragma once



enum RG_LANG
{
	RG_RUS,
	RG_ENG
};



uint languageWindows;

class RG_lang
{
	string path = "data/lang";
	string type = ".rg";
	string BASELang[2]=
	{
		"ru",
		"en"
	};

	uint lang = RG_RUS;

	wstring *words = nullptr;
	wstring *names = nullptr;


	int size = 0;

	bool isLoad=false;


public:
		uint getLang()
		{
			return lang;
		}
		RG_lang(){}

		RG_lang(string pat)
		{
			init(pat);
		}

		RG_lang(int a)
		{
			if(a==0)return;
			load();
		}

		void init()
		{
			load();
		}
		void init(string pat)
		{
			path = pat;
			load();
		}
		void load()
		{
			if(isLoad){return;}

     		languageWindows = GetSystemDefaultLangID();

    		switch (languageWindows)
    		{
    			case 1049: lang = RG_RUS; break;
    			default: lang = RG_ENG;

    		}




			
			wstring file = WFileLoad(path+"/"+BASELang[lang]+type);
	

			for(int i = 0;i<(int)file.size();i++)
			{
				if(file[i]==L';')size++;
			}
			
			words = new wstring[size];
			names = new wstring[size];

			bool temp1 = false,temp2=false;
            int temp3 = -1;
        
			for(int i = 0;i<size;i++)
			{
				

				for(int j = 0;file[temp3+1]!=L';';j++)
				{
				   
				   temp3++;
					if(file[temp3]==L'{'){temp1=true;continue;}
					if(file[temp3]==L'}'){temp1=false;temp2 = true;continue;}
					//if(file[temp3]==L':'&&!temp1&&temp3){temp2=true;continue;temp3 = false;}

					if(temp1)
						{names[i]+=file[temp3];}
					if(temp2)
						{words[i]+=file[temp3];}
					
				}	
				//cout<<names[i]<<endl;
				wcout<<words[i]<<endl;
				wcout<<names[i]<<endl;


				temp1=false;
				temp2=false;
				temp3++;
				

			}

	
		}

		wstring getWstring(wstring name)
		{
        wstring wreturn = name;
			for(int i = 0;i<size;i++)
			{	
				if(names[i] == name){wreturn = words[i];break;}				
			}
		
			return wreturn;
		}

}RG_StandartLang;
