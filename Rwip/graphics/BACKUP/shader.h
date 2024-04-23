#pragma once






float calculateTransformedZ( RG_Matrix<float>& mA,  RG_Matrix<float>& mB) {

	float transformedZ = 
	mA.get(2,0) *mA.get(2,1) * mA.get(2,2) * mA.get(2,3) + 
	mB.get(2,0) *mB.get(2,1) * mB.get(2,2) * mB.get(2,3);

 
    
    return transformedZ;
}

uint countMat = 0;
uint maxCountMat = 64;

//RG_Matrix <float>*RG_MatBuf = (RG_Matrix<float>*)calloc(maxCountMat,sizeof(RG_Matrix<float>));










//видимо было сделано для использование материалов
uint RG_STANDART_SHADER_PROG;
uint 	RG_SSP_COLOR,
		RG_SSP_TEXTURE,
		RG_SSP_TEXT;

//для шедеров (типо положение этих фигней в шейдерах)
enum RG_ATTRIB_CONST
{
	RG_VERTEX_ARRAY,
	RG_COLOR_ARRAY,
	RG_TEXTURE_COORD_ARRAY
};

uint 
ColorSet
;

uint
rg_setTexture,
rg_Texture2d
;

uint 
rg_viewMat,
rg_projMat
;

uint RG_TEXTURE_2D;

///////////////////////////

//RG_Matrix <float>*RG_MatBuf = rg_calloc(RG_Matrix<float>,maxCountMat);
RG_Array<RG_Matrix <float>> RG_MatBuf(maxCountMat);
/*
RG_Matrix <float>*PM = &RG_MatBuf[0];
RG_Matrix <float>&projMat = PM;
*/
RG_Matrix <float>*projMat;
//еденичная матрица
float IdentityMat[4*4]={
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
	};
//функция подготовки шейдера
void RG_PREPARE_SHADER()
{
	//viewMat.Init(4,4,IdentityMat);
	//projMat.Init(4,4,IdentityMat);

	RG_FOR_CYCLEi(maxCountMat)
	{
		RG_MatBuf[i].init(4,4,IdentityMat);
	}
	//rg_cout((*projMat));
	projMat = &RG_MatBuf[0];
	//rg_cout((*projMat));


/*
	RG_VERTEX_ARRAY = glGetAttribLocation(RG_STANDART_SHADER_PROG,"rg_Vertex");
	RG_COLOR_ARRAY = glGetAttribLocation(RG_STANDART_SHADER_PROG,"rg_Color");
	RG_TEXTURE_COORD_ARRAY = glGetAttribLocation(RG_STANDART_SHADER_PROG,"rg_TextureCoord");
*/
	RG_TEXTURE_2D = glGetUniformLocation(prog,"tex_2d");
	rg_viewMat = glGetUniformLocation(RG_STANDART_SHADER_PROG,"viewMat");
	rg_projMat = glGetUniformLocation(RG_STANDART_SHADER_PROG,"projMat");
	rg_setTexture = glGetUniformLocation(RG_STANDART_SHADER_PROG,"setTexture");
	rg_Texture2d = glGetUniformLocation(RG_STANDART_SHADER_PROG,"texture_2d");
	ColorSet = glGetUniformLocation(RG_STANDART_SHADER_PROG,"ColorSet");



	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());
	glUniformMatrix4fv(rg_projMat,1,0,IdentityMat);
	glUniformMatrix4fv(rg_viewMat,1,0,IdentityMat);

	//glUniformMatrix4fv(rg_viewMat,1,0,viewMat.get());

	
	glBindFragDataLocation(RG_STANDART_SHADER_PROG,0,"Frag");


	//return;
}



//функции для шедеров
void rgVertex3d(double x, double y, double z)
{
	glVertexAttrib3d(RG_VERTEX_ARRAY,x,y,z);
}
void rgVertex3f(float x, float y, float z)
{
	glVertexAttrib3f(RG_VERTEX_ARRAY,x,y,z);
}
void rgVertex2f(float x, float y)
{
	glVertexAttrib2f(RG_VERTEX_ARRAY,x,y);
}


void rgColor4d(double r, double g, double b, double a)
{
	glVertexAttrib4d(RG_COLOR_ARRAY,r,g,b,a);
}


void rgTexCoord2f(float x, float y)
{
	glVertexAttrib2f(RG_TEXTURE_COORD_ARRAY,x,y);
}









void rgVertexPointer(int size, int type, int stride, const void* pointer)
{
	glVertexAttribPointer(RG_VERTEX_ARRAY,size,type,1,stride,pointer);
	//glVertexPointer(size,type,stride,pointer);
}




void rgColorPointer(int size, int type, int stride, const void* pointer)
{
	glVertexAttribPointer(RG_COLOR_ARRAY,size,type,1,stride,pointer);
	//glColorPointer(size,type,stride,pointer);
}

void rgTexCoordPointer(int size, int type, int stride, const void* pointer)
{
	glVertexAttribPointer(RG_TEXTURE_COORD_ARRAY,size,type,1,stride,pointer);
	//glColorPointer(size,type,stride,pointer);
}











//////////////////////////////////////////////////////////////////////////////////////////




void rgFrustum(float left, float right, float bottom, float top, float zNear, float zFar,RG_Matrix <float>&mat = (*projMat))
{
	float FurstumMat[16]=
	{
		((2.f*zNear)/(right-left)),	0,							((right+left)/(right-left)),	0,

		0,							((2.f*zNear)/(top-bottom)),	((top+bottom)/(top-bottom)),	0,

		0,							0,							-((zFar+zNear)/(zFar-zNear)),	-((2.f*zFar*zNear)/(zFar-zNear)),

		0,							0,							-1,								0
	};
	mat*=FurstumMat;
}
void rgOrtho(float left, float right, float bottom, float top, float zNear, float zFar,RG_Matrix <float>&mat = (*projMat))
{
	float orthoMat[16]=
	{
		(2.f/(right-left)),	0,					0,						-((right+left)/(right-left)),

		0,					(2.f/(top-bottom)),	0,						-((top+bottom)/(top-bottom)),

		0,					0,					((-2.f)/(zFar-zNear)),	-((zFar+zNear)/(zFar-zNear)),

		0,					0,					0,						1
	};
	mat*=orthoMat;
}


void rgLoadIdentity(RG_Matrix<float>&mat)
{
	//projMat.Clear();
	mat.reInit(4,4,IdentityMat);
}
	/*for(int i = 0; i<16;i++)
	{
		projMat.get()[i]=0;
		if(i==0||i==5||i==10||15)projMat.get()[i]=1;
	}
	if(use)glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());
}

/*void rgLoadIdentity(bool use = false)
{
	//projMat.Clear();
	projMat->reInit(4,4,IdentityMat);
	/*for(int i = 0; i<16;i++)
	{
		projMat.get()[i]=0;
		if(i==0||i==5||i==10||15)projMat.get()[i]=1;
	}
	if(use)glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());
}
*/
/*void rgLoadMatrixf(RG_Matrix<float> m,bool use = false)
{
	*projMat = m;

	if(use)glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());
}*/


void rgLoadMatrixf(RG_Matrix<float>& m)
{
	glUniformMatrix4fv(rg_projMat,1,0,m.get());
}

void rgLoadMatrixf(RG_Matrix<float>& m,uint id)
{
	glUniformMatrix4fv(id,1,0,m.get());
}

void rgLoadMatrixf(float* m)
{
	glUniformMatrix4fv(rg_projMat,1,0,m);
}
void rgLoadIdentityMatrix()
{
	glUniformMatrix4fv(rg_projMat,1,0,IdentityMat);
}

void rgLoadMatrixf(float* m,uint id)
{
	glUniformMatrix4fv(id,1,0,m);
}

void rgReloadMatrix(RG_Matrix<float>&mat = (*projMat),bool use = false)
{
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());
}


void rgRotatef(float a, float x, float y, float z,RG_Matrix <float>&mat = (*projMat),bool use = false)
{
	float c = cos(a/180.f*M_PI);
	float s = sin(a/180.f*M_PI);
	
	float rotateMat[16]=
	{
		(x*x*(1.f-c)+c)		,(x*y*(1.f-c)-z*s)	,(x*z*(1.f-c)+y*s)	,0,
	
		(y*x*(1.f-c)+z*s)	,(y*y*(1.f-c)+c)	,(y*z*(1.f-c)-x*s)	,0,
	
		(z*x*(1.f-c)-y*s)	,(z*y*(1.f-c)+x*s)	,(z*z*(1.f-c)+c)	,0,
	
		0							,0							,0							,1
	};

	//MultyMat4(projMat,rotateMat,projMat);
	mat*=rotateMat;
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());
}


void rgScalef(float x, float y, float z,RG_Matrix <float>&mat = (*projMat),bool use = false)
{

	float scaleMat[16]=
	{
		x,0,0,0,
		0,y,0,0,
		0,0,z,0,
		0,0,0,1
	};

	//MultyMat4(projMat,scaleMat,projMat);
	mat*=scaleMat;
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());
}



void rgTranslatef(float x, float y, float z,RG_Matrix <float>&mat = (*projMat),bool use = false) {

	float TranslMat[16]=
	{
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1
	};


	//MultyMat4(projMat,TranslMat,projMat);
	mat*=TranslMat;
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());    
}


void rgDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices)
{
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   

	glDrawElements(mode,count,type,indices);
}

void rgDrawArrays(	GLenum mode,GLint first,GLsizei count)
{
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   

	glDrawArrays(mode,first,count);
}

void rgBegin(GLenum mode)
{
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   
	glBegin(mode);
}

void rgEnd()
{
	glEnd();
}



void rgEnableClientState(RG_ATTRIB_CONST type)
{
	glEnableVertexAttribArray(type);

}
void rgDisableClientState(RG_ATTRIB_CONST type)
{
	glDisableVertexAttribArray(type);
}

void rgBindTexture(int id,int type = GL_TEXTURE_2D)
{
	glUniform1i(rg_setTexture,id);	
}




void rgColorSet(bool type)
{
	glUniform1i(ColorSet,type);
}


////////////////////////////////////////////////////////////////////////////

///////////////////////////

void ShaderCompiller(char* frag, char* vert,uint prog)
{
	uint vshader = glCreateShader(GL_VERTEX_SHADER);
	uint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vshader,1,&vert,NULL);
	glShaderSource(fshader,1,&frag,NULL);
	glCompileShader(vshader);
	glCompileShader(fshader);
	
	char temp[2048];
	string log;
	ofstream shaderlog("Logs/Shaders.log");

	/*int status;
	glGetShaderiv(fshader,GL_COMPILE_STATUS,&status);
	if(!status)
	{*/

    	
    	glGetShaderInfoLog(fshader,2048,nullptr,temp);
    	//temp2 = ;
    	log += "Fragment shaders error:\n"; 
    	log += temp;

    	
    	glGetShaderInfoLog(vshader,2048,nullptr,temp);
    	log += "Vertex shaders error:\n";
    	log += temp;

    	glGetProgramInfoLog(fshader,2048,nullptr,temp);
    	//temp2 = ;
    	log += "Fragment program error:\n"; 
    	log += temp;

    	
    	glGetProgramInfoLog(vshader,2048,nullptr,temp);
    	log += "Vertex program error:\n";
    	log += temp;
    	
    	
		shaderlog<<"Shader Error:\n"<<log<<"END\n";
	
    
	//}
	shaderlog.close();
	glAttachShader(prog,vshader);
	glAttachShader(prog,fshader);
	//free(temp);
	glLinkProgram(prog);
}

class RG_Shader{
  uint shader_prog;
  bool INIT = false;
public:
  void init(string pathfrag, string pathvert){
    INIT = true;
    //cout<<"init\n";
    shader_prog = glCreateProgram();
    //cout<<"create\n";
    char*frag = FileLoadToChar(pathfrag);
    //cout<<"load 1\n";
    char*vert = FileLoadToChar(pathvert);
    //cout<<"load 2\n";
		ShaderCompiller(frag,vert,shader_prog);
    //cout<<"compiller\n";
		glUseProgram(shader_prog);
    //cout<<"used\n";

  }
	void used(){
		RG_STANDART_SHADER_PROG = shader_prog;
	}

};





/*
struct RG_Texture
{
	//int width = 0, height = 0, cnt = 0;
	uint8 cnt = 0;
	POINT2D<uint> size;
	POINT2D<uint> TexturePos;
};
RG_Array<RG_Texture> RG_Textures;*/
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
	Buffers.append();
	glGenBuffers(1,&BO);
	glBindBuffer(GL_ARRAY_BUFFER,BO);
		glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	Buffers[edit].size = size;
	Buffers[edit].id = BO;
	return BO;
}





enum RG_TYPE_DRAW_SHADER
{
	RG_TDS_COLOR,
	RG_TDS_TEXTURE,
	RG_TDS_TEXT,
};
/*
void RG_DrawType(RG_TYPE_DRAW_SHADER type)
{
	switch(type)
	{
	case RG_TDS_COLOR:RG_STANDART_SHADER_PROG=RG_SSP_COLOR;	break;
	case RG_TDS_TEXTURE:RG_STANDART_SHADER_PROG=RG_SSP_TEXTURE;	break;
	case RG_TDS_TEXT:RG_STANDART_SHADER_PROG=RG_SSP_TEXT;	break;
	default:throw(RG_ERROR_UNKNOWN_SHADER_TYPE);
	}
	glUseProgram(RG_STANDART_SHADER_PROG);
}*/