#pragma once

void  RG_FillWeights(RG_Array<RG_Array<double>>& Weight,string& file){
	string temp;
	uint layer,posx,posy;
	uint tempxf = 0;
	bool skip = false;
  setlocale(LC_ALL,"Eng");
	enum TempW
	{
		TempNone,
		TempBias,
		TempWeight
	}TempWrite;
	for(int i = 0; i<file.size();i++)
	{
		if((file[i]=='\n'&&temp.size()>0)||file.size()-1==i)
		{
			skip = false;
			tempxf = 0;
			if(temp == "WEIGHT")
			{
				TempWrite = TempWeight;
				temp.clear();
				continue;
			}
			
			//cout<<layer<<" "<<posx<<" "<<posy<<" = ";
			switch(TempWrite)
			{
				case TempWeight: Weight[layer].get(posx,posy) = stod(temp); break;
				//case TempBias: Layers[layer].Bias.get(posx,posy) = stod(temp); break;
			}
			temp.clear();
			continue;
		}
		if(file[i]=='#'){skip = true;continue;}
		if(file[i]==' '&&!skip&&temp.size()>0)
		{
			//cout<<"tempxf = "<<tempxf<<endl;
			if(tempxf==0)
			{
				tempxf++;
				layer = stoi(temp);	
				//cout<<"layer = "<<layer<<endl;
			}else
			if(tempxf==1)
			{
				tempxf++;
				posx = stoi(temp);
				//cout<<"posx = "<<posx<<endl;
			}else
			if(tempxf>=2)
			{
				tempxf=0;
				posy = stoi(temp);
				//cout<<"posy = "<<posy<<endl<<endl;
			}
			temp.clear();
			//continue;
		}
		if((file[i]>='0'&&file[i]<='9')||file[i]=='.'||file[i]=='-'||(file[i]>='A'&&file[i]<='Z')||(file[i]>='a'&&file[i]<='z'))
		{
			temp+=file[i];
		}
	}
  setlocale(LC_ALL,"Rus");
}

void RG_SaveWeights(RG_Array<RG_Array<double>>& Weight)
{
  ofstream weightFile("weight.val");
	
	weightFile<< "WEIGHT"<<endl;
	for(int i = 0; i<Weight.getSize();i++)
	{
		for(int j = 0; j<Weight[i].getSize();j++)
		{
			//weightFile<<i<<' '<<j<<' '<<Weight[i][j]<<"#"<<"Layer "<<i<<" connect "<<"Weight[i].getSize()/j"<<" to "<<"Weight[i].getSize()%j"<<endl;
			weightFile<<i<<' '<<int(j%Weight[i].getSize(0))<<' '<<int(j/Weight[i].getSize(0))<<' '<<Weight[i].get(int(j%Weight[i].getSize(0)),int(j/Weight[i].getSize(0)))<<endl;
		}	
	}
	/*weightFile<< "BIAS"<<endl;
	for(int i = 0; i<Layers.getSize();i++)
	{
		for(int j = 0; j<Layers[i].Bias.getSize();j++)
		{
			weightFile<<i<<' '<<int(j%Layers[i].Bias.getSize(0))<<' '<<int(j/Layers[i].Bias.getSize(0))<<' '<<Layers[i].Bias.get(int(j%Layers[i].Bias.getSize(0)),int(j/Layers[i].Bias.getSize(0)))<<endl;
		}
	}*/
	weightFile.close();
}