#pragma once




void RG_EX_ReplaceTexture(Atlas &atl = RG_Atlas_Standart){
  uint tempTexture;
  uint oldTexture;
	glGenTextures(1,&tempTexture);


	glBindTexture(GL_TEXTURE_2D, tempTexture);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atl.size.x, atl.size.y,
										0, GL_RGBA, GL_UNSIGNED_BYTE, atl.textureRaw.get_mat());
  oldTexture = atl.texture;
  atl.texture = tempTexture;
  glDeleteTextures(1,&oldTexture);
}


void RG_EX_ReloadAtlas(Atlas &atl = RG_Atlas_Standart, RG_Array<AtlasTexture> &texs = RG_AtlasArrayTextures){
  //calcule size
	POINT2D<int>max_size;
	POINT2D<int>max_one_size;

	for(int i = 0; i<texs.size();i++){
		max_size.x+=texs[i].texture.size(0);
		max_size.y+=texs[i].texture.size(1);
		if(texs[i].texture.size(0)>max_one_size.x) max_one_size.x = texs[i].texture.size(0);
		if(texs[i].texture.size(1)>max_one_size.y) max_one_size.y = texs[i].texture.size(1);
	}
	POINT2D<int>end_size;
	while(end_size.x<max_size.x){
		end_size.x+=1024;
	}
		//end_size.x-=1024;

	while(end_size.y<max_size.y){
		end_size.y+=1024;
	}
	//end_size.y-=1024;

	//RG_Matrix<int>end_texture(end_size.x,end_size.y);
	atl.size.x = end_size.x/4.;
	//atl.size.y = end_size.y;
	atl.size.y = max_size.y;

	uint8 cnt = 4;
	//end_texture.place({0,0},texs[0].texture);
	POINT2D<int>pen;
	POINT2D<int>max;
	
	//stbi_write_png("atlas.png", end_size.x/cnt, end_size.y, cnt, atl.textureRaw.get_mat(), end_size.x);
  //cout<<atl.textureRaw.size(0)<<" "<<atl.textureRaw.size(1)<<" "<<atl.textureRaw.get_mat()<<endl;
	atl.textureRaw.resize(end_size.x,max_size.y);
  //cout<<atl.textureRaw.size(0)<<" "<<atl.textureRaw.size(1)<<" "<<atl.textureRaw.get_mat()<<endl;

  //cout<<"test\n";
  //cout<<texs[0].texture.get(0,0)<<endl;
  //cout<<"cycle";
	for(int i = 0; i<texs.size();i++){AtlasTexture &texture = texs[i];
    //cout<<i<<endl;
		while(pen.x+texture.texture.size(0)>end_size.x){
			if(pen.y>max_size.y){cout<<max_size.y<<" "<<texture.texture.size(1)<<endl;exit(-902397812);};
			pen.x = 0;
			pen.y += max.y+1;
			max.y = 0;
		}
    //cout<<i<<"place\n";
		//cout<<i<<endl;
		atl.textureRaw.place({pen.x,pen.y},texs[i].texture);
    //cout<<i<<endl;

		texture.pos.x = pen.x/4;
		texture.pos.y = pen.y;
    //cout<<i<<endl;
		pen.x+=texs[i].texture.size(0);
		max.y = rg_max(texs[i].texture.size(1),max.y);
    //cout<<i<<endl;
		
		

	}
	//stbi_write_png("atlas2.png", end_size.x/cnt, end_size.y, cnt, atl.textureRaw.get_mat(), end_size.x);



}

