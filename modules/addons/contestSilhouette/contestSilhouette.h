#pragma once



void RG_SL_OnGrid(RG_Object &obj, RG_Matrix<RG_Object>&grid){

  for(int y = 0; y <grid.size(1);y++){
    for(int x = 0; x<grid.size(0);x++){
      RG_Object&gr = grid.get(x,y);


      gr.texture = obj.texture;
  
      gr.is_gui = obj.is_gui;
      gr.gui_type = obj.gui_type;
      //COLOR4D<double>temp[4] = {1,1,1,1};
      //gr.pos = obj.pos;

      gr.scale = obj.scale;
      gr.rotate = obj.rotate;
      POINT2D<int> TexturePos = RG_AtlasArrayTextures[gr.texture].pos;
	    POINT2D<int> TextureSize = RG_AtlasArrayTextures[gr.texture].size;
      rgLoadIdentity(gr.mat);

      rgTranslatef(gr.pos.x,gr.pos.y,gr.pos.z);
      rgScalef
	      (
	      ((double)TextureSize.x/RG_Window_Size_Standart * gr.scale)/((double)grid.size(0)/2.) , 
	      ((double)TextureSize.y/RG_Window_Size_Standart * gr.scale)/((double)grid.size(1)/2.) , 
	      1, gr.mat); 

	    //rgTranslatef( gr.pos.x+((((double)TextureSize.x/(double)grid.size(0)/RG_Window_Size_Standart * gr.scale)*x)-0.5), gr.pos.y+((((double)TextureSize.y/(double)grid.size(1)/RG_Window_Size_Standart * gr.scale)*y)-0.5), gr.pos.z,gr.mat);

      rgTranslatef(x-floor(grid.size(0)/2.),y-floor(grid.size(1)/2.),0,gr.mat);

      rgScalef
	      (
	      ((double)TextureSize.x/RG_Window_Size_Standart * gr.scale)/(double)grid.size(0) , 
	      ((double)TextureSize.y/RG_Window_Size_Standart * gr.scale)/(double)grid.size(1) , 
	      1, gr.mat); 
      rgScalef(1.5,1.5,1,gr.mat);

      gr.size.x = ((((double)TextureSize.x/RG_Window_Size_Standart)/(double)grid.size(0)));
      gr.size.y = ((((double)TextureSize.y/RG_Window_Size_Standart)/(double)grid.size(1)));
    
      gr.pos.x = obj.pos.x+((gr.size.x*2)*(x-floor(grid.size(0)/2.)));
      gr.pos.y = obj.pos.y+((gr.size.y*2)*(y-floor(grid.size(1)/2.)));
      gr.pos.z = obj.pos.z;
      POINT2D<double> TexCoordArr[6] = 
	    {
	    	{(TexturePos.x+(TextureSize.x*1./grid.size(0)*x))		  /(double)RG_Atlas_Standart.size.x,	(TexturePos.y+(TextureSize.y*1./grid.size(1)*(( grid.size(1)-y-1))))						/(double)RG_Atlas_Standart.size.y},
	    	{(TexturePos.x+(TextureSize.x*1./grid.size(0)*x))		  /(double)RG_Atlas_Standart.size.x,	(TexturePos.y+(TextureSize.y*1./grid.size(1)*(((  grid.size(1)-y)))))	/(double)RG_Atlas_Standart.size.y},
	    	{(TexturePos.x+(TextureSize.x*1./grid.size(0)*(x+1)))	/(double)RG_Atlas_Standart.size.x,	(TexturePos.y+(TextureSize.y*1./grid.size(1)*(((  grid.size(1)-y)))))	/(double)RG_Atlas_Standart.size.y},
	    	{(TexturePos.x+(TextureSize.x*1./grid.size(0)*(x+1)))	/(double)RG_Atlas_Standart.size.x,	(TexturePos.y+(TextureSize.y*1./grid.size(1)*(( grid.size(1)-y-1))))  /(double)RG_Atlas_Standart.size.y},
	    };
      gr.BOs.tbo().resize(1);
	    gr.BOs.tbo()[0] = BufferLoad<POINT2D<double>>(sizeof(TexCoordArr),TexCoordArr,GL_STATIC_DRAW);

      
	    rgRotatef(gr.rotate.x,1,0,0,gr.mat); rgRotatef(gr.rotate.y,0,1,0,gr.mat); rgRotatef(gr.rotate.z,0,0,1,gr.mat);
    
      gr.BOs.vbo() = BufferLoad<POINT3D<double>>(sizeof(RG_Square3Dvectors),RG_Square3Dvectors,GL_STATIC_DRAW);
	    //gr.BOs.cbo() = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
      gr.BOs.cbo() = obj.BOs.cbo();
	    gr.BOs.ebo().fill(6,RG_SquareElemets);
    }
  }
}