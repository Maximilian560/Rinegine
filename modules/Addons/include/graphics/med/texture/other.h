#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/med/texture-other"

void RG_png_to_txtfile(string intx, string outtxt){
    RG_LOG_LOCK_DEBUG("Convert image '"+intx+"' to txt file '"+outtxt+"'");
    POINT2D <int> size;
    int cnt;
		uint8* tximg = stbi_load(intx.c_str(),&size.x,&size.y,&cnt,0);
    
    RG_Array<uint8> tx(size.x*size.y*cnt,tximg);

    ofstream file(outtxt);
    if(!file.is_open()){
      RG_LOG_LOCK_CRITICAL("Cannot create file '"+outtxt+ "'");
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
    RG_LOG_LOCK_DEBUG("Convert done");
}

void RG_txt_to_texture(RG_Texture::Raw &tex,string pathtxt){
  RG_LOG_LOCK_DEBUG("Load txt file '"+pathtxt+"' to texture");
  string t = RG::FileLoad(pathtxt);
  string temp;
  POINT2D <int> size;
  int cnt;
  int tempwr = 0;
  int ti=0;
  for(char a:t){
    if(ti==0)rg_cout<<a<<endl;
    if((a==' '||a=='\n'||a=='|'||a==t.back())&&temp.size()>0){
      if(a==t.back()){
        rg_cout<<"'"<<rg_to_string(temp)<<"'"<<endl;
      }
      if(tempwr<=2){
        switch (tempwr){
          case 0:
            tempwr++;
            RG_LOG_LOCK_DEBUG("Size x = "+temp);
            tex.size.x = stoi(temp);
            temp.clear();
            break;
          case 1:
            tempwr++;
            RG_LOG_LOCK_DEBUG("Size y = "+temp);
            tex.size.y = stoi(temp);
            temp.clear();
            break;
          case 2:
            tempwr++;
            RG_LOG_LOCK_DEBUG("cnt = "+temp);
            tex.cnt = stoi(temp);
            tex.raw.resize(tex.size.x*tex.cnt,tex.size.y);
            temp.clear();
            break;
        }
        continue;
      }
      //RG_LOG_LOCK_DEBUG("i = "+to_string(ti)+" texture[ti] = "+temp);
      tex.raw.get(ti,0) = uint8(stoi(temp));
      ti++;
      temp.clear();
      continue;
    }
    if(a>='0' && a<='9'){
      temp+=a;
    }
  }
    RG_LOG_LOCK_DEBUG("Load done");
}