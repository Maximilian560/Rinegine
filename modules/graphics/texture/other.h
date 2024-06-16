#pragma once

void RG_png_to_txtfile(string intx, string outtxt){
    RG_Debug::addl(RG_LOG_DEBUG,"Convert image '"+intx+"' to txt file '"+outtxt+"'");
    POINT2D <int> size;
    int cnt;
		uint8* tximg = stbi_load(intx.c_str(),&size.x,&size.y,&cnt,0);
    
    RG_Array<uint8> tx(size.x*size.y*cnt,tximg);

    ofstream file(outtxt);
    if(!file.is_open()){
      RG_Debug::addl(RG_LOG_CRITICAL,"Cannot create file '"+outtxt+ "'");
    }
    file << size.x << " " << size.y << " " << cnt <<"\n";
    for(int i = 0; i<size.y;i++){
      for(int j = 0; j<size.x;j++){
        for(int k = 0; k<cnt;k++){
          file << to_string(tx[i*size.x*cnt+j*cnt+k]);
          if(k!=cnt-1)file<<" ";
        }
        file<<"|";
      }
      file<<endl;
    }
    file.close();
    RG_Debug::addl(RG_LOG_DEBUG,"Convert done");
}

void RG_txt_to_texture(RG_Texture::Raw &tex,string pathtxt){
  RG_Debug::addl(RG_LOG_DEBUG,"Load txt file '"+pathtxt+"' to texture");
  string t = FileLoad(pathtxt);
  string temp;
  POINT2D <int> size;
  int cnt;
  int tempwr = 0;
  int ti=0;
  for(char a:t){
    if(ti==0)cout<<a<<endl;
    if((a==' '||a=='\n'||a=='|'||a==t.back())&&temp.size()>0){
      if(a==t.back()){
        cout<<"'"<<temp<<"'"<<endl;
      }
      if(tempwr<=2){
        switch (tempwr){
          case 0:
            tempwr++;
            RG_Debug::addl(RG_LOG_DEBUG,"Size x = "+temp);
            tex.size.x = stoi(temp);
            temp.clear();
            break;
          case 1:
            tempwr++;
            RG_Debug::addl(RG_LOG_DEBUG,"Size y = "+temp);
            tex.size.y = stoi(temp);
            temp.clear();
            break;
          case 2:
            tempwr++;
            RG_Debug::addl(RG_LOG_DEBUG,"cnt = "+temp);
            tex.cnt = stoi(temp);
            tex.raw.resize(tex.size.x*tex.cnt,tex.size.y);
            temp.clear();
            break;
        }
        continue;
      }
      //RG_Debug::addl(RG_LOG_DEBUG,"i = "+to_string(ti)+" texture[ti] = "+temp);
      tex.raw[0][ti] = stoi(temp);
      ti++;
      temp.clear();
      continue;
    }
    if(a>='0' && a<='9'){
      temp+=a;
    }
  }
    RG_Debug::addl(RG_LOG_DEBUG,"Load done");
}