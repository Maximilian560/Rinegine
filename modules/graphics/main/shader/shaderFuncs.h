#pragma once


//функции для шедеров
//VERTEX
void rgVertex3d(double x, double y, double z)
{
	glVertexAttrib3d(RG_VERTEX_ARRAY_POS,x,y,z);
}
void rgVertex3f(float x, float y, float z)
{
	glVertexAttrib3f(RG_VERTEX_ARRAY_POS,x,y,z);
}
void rgVertex2f(float x, float y)
{
	glVertexAttrib2f(RG_VERTEX_ARRAY_POS,x,y);
}

//COLOR
void rgColorSet(bool type)
{
	glUniform1i(ColorSet,type);
}

void rgColor4d(double r, double g, double b, double a)
{
	glVertexAttrib4d(RG_COLOR_ARRAY_POS,r,g,b,a);
}


void rgTexCoord2f(float x, float y)
{
	glVertexAttrib2f(RG_TEXTURE_COORD_ARRAY_POS,x,y);
}








//POINTERS
void rgVertexPointer(int size, int type, int stride, const void* pointer)
{
	glVertexAttribPointer(RG_VERTEX_ARRAY_POS,size,type,1,stride,pointer);
	//glVertexPointer(size,type,stride,pointer);
}


void rgColorPointer(int size, int type, int stride, const void* pointer)
{
	glVertexAttribPointer(RG_COLOR_ARRAY_POS,size,type,1,stride,pointer);
	//glColorPointer(size,type,stride,pointer);
}

void rgTexCoordPointer(int size, int type, int stride, const void* pointer)
{
	glVertexAttribPointer(RG_TEXTURE_COORD_ARRAY_POS,size,type,1,stride,pointer);
	//glColorPointer(size,type,stride,pointer);
}











//////////////////////////////////////////////////////////////////////////////////////////



//PERSPECT
void rgFrustum(float left, float right, float bottom, float top, float zNear, float zFar,RG_Matrix <float>&mat = (*projMat),bool use = false)
{
	float FurstumMat[16]=
	{
		((2.f*zNear)/(right-left)),	0,							((right+left)/(right-left)),	0,

		0,							((2.f*zNear)/(top-bottom)),	((top+bottom)/(top-bottom)),	0,

		0,							0,							-((zFar+zNear)/(zFar-zNear)),	-((2.f*zFar*zNear)/(zFar-zNear)),

		0,							0,							-1,								0
	};
	mat*=FurstumMat;
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());
}
void rgOrtho(float left, float right, float bottom, float top, float zNear, float zFar,RG_Matrix <float>&mat = (*projMat),bool use = false)
{
	float orthoMat[16]=
	{
		(2.f/(right-left)),	0,					0,						-((right+left)/(right-left)),

		0,					(2.f/(top-bottom)),	0,						-((top+bottom)/(top-bottom)),

		0,					0,					((-2.f)/(zFar-zNear)),	-((zFar+zNear)/(zFar-zNear)),

		0,					0,					0,						1
	};
	mat*=orthoMat;
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());
}


void rgLoadIdentity(RG_Matrix<float>&mat)
{
	mat.reInit(4,4,IdentityMat);	
}

//MATRIX
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
void rgLoadIdentityMatrix(uint id)
{
	glUniformMatrix4fv(id,1,0,IdentityMat);
}

void rgLoadMatrixf(float* m,uint id)
{
	glUniformMatrix4fv(id,1,0,m);
}

void rgReloadMatrix(RG_Matrix<float>&mat = (*projMat),bool use = false)
{
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());
}

//ROTATEf
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

//SCALEF
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


//TRANSFORM
void rgTranslatef(float x, float y, float z,RG_Matrix <float>&mat = (*projMat),bool use = false) {

	float TranslMat[16]=
	{
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1
	};

	mat*=TranslMat;
	if(use)glUniformMatrix4fv(rg_projMat,1,0,mat.get());    
}

//DRAW ARRAY,ELEMENTS
inline void rgDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices){
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   

	glDrawElements(mode,count,type,indices);
}

inline void rgDrawArrays(	GLenum mode,GLint first,GLsizei count)
{
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   

	glDrawArrays(mode,first,count);
}
//BEGIN END
inline void rgBegin(GLenum mode)
{
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   
	glBegin(mode);
}

inline void rgEnd()
{
	glEnd();
}


//CLIENT STATE
inline void rgEnableClientState(RG_ATTRIB_CONST type)
{
	glEnableVertexAttribArray(type);

}
inline void rgDisableClientState(RG_ATTRIB_CONST type)
{
	glDisableVertexAttribArray(type);
}
//TEXTURE
inline void rgBindTexture(int id,int type = GL_TEXTURE_2D)
{
	glUniform1i(rg_setTexture,id);	
}




