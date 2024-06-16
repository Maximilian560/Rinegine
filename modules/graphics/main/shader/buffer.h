#pragma once

//Buffers
struct RG_BO
{
	uint id;
	uint size = 0;
	char name[64];
};

RG_Array<RG_BO>Buffers;


template<typename Point>
uint BufferLoad(uint size,Point *buf,int type)
{
	uint BO;
	uint edit = Buffers.size() ;

	//Buffers = (RG_BO*)realloc(Buffers,CountBuffers * sizeof(RG_BO));
	Buffers.push_back();
	glGenBuffers(1,&BO);
	glBindBuffer(GL_ARRAY_BUFFER,BO);
		glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	Buffers[edit].size = size;
	Buffers[edit].id = BO;
	return BO;
}
