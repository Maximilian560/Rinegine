#pragma once


//функции для шедеров
//VERTEX
void rgVertex3d(double x, double y, double z) {
	glVertexAttrib3d(RG_VERTEX_ARRAY_POS, x, y, z);
}
void rgVertex3f(float x, float y, float z) {
	glVertexAttrib3f(RG_VERTEX_ARRAY_POS, x, y, z);
}
void rgVertex2f(float x, float y) {
	glVertexAttrib2f(RG_VERTEX_ARRAY_POS, x, y);
}

//COLOR
void rgColorSet(bool type) {
	glUniform1i(rg_ColorSet, type);
}

void rgColor4d(double r, double g, double b, double a) {
	glVertexAttrib4d(RG_COLOR_ARRAY_POS, r, g, b, a);
}


void rgTexCoord2f(float x, float y) {
	glVertexAttrib2f(RG_TEXTURE_COORD_ARRAY_POS, x, y);
}
/*
void rgOffset3d(double x, double y, double z){
	glVertexAttrib3d(RG_OFFSET_ARRAY_POS, x, y, z);
}*/







//POINTERS
void rgVertexPointer(int size, int type, int stride, const void* pointer) {
	glVertexAttribPointer(RG_VERTEX_ARRAY_POS, size, type, 1, stride, pointer);
}


void rgColorPointer(int size, int type, int stride, const void* pointer) {
	glVertexAttribPointer(RG_COLOR_ARRAY_POS, size, type, 1, stride, pointer);
}

void rgTexCoordPointer(int size, int type, int stride, const void* pointer) {
	glVertexAttribPointer(RG_TEXTURE_COORD_ARRAY_POS, size, type, 1, stride, pointer);
}
/*
void rgOffsetPointer(int size, int type, int stride, const void* pointer){
	glVertexAttribPointer(RG_OFFSET_ARRAY_POS, size, type, 1, stride, pointer);
}*/











//////////////////////////////////////////////////////////////////////////////////////////



//PERSPECT
void rgFrustum(float left, float right, float bottom, float top, float zNear, float zFar, RG_Matrix <float>& mat = (*projMat), bool use = false) {
	mat *= {
		{((2.f * zNear) / (right - left)), 0, ((right + left) / (right - left)), 0},
		{ 0, 				((2.f * zNear) / (top - bottom)), ((top + bottom) / (top - bottom)), 					0 },
		{ 0, 										0, 										-((zFar + zNear) / (zFar - zNear)), 				-((2.f * zFar * zNear) / (zFar - zNear)) },
		{ 0, 										0, 										-1, 																				0 }
	};
	if (use)glUniformMatrix4fv(rg_projMat, 1, 0, mat.get());
}
// RG_Matrix<float> RG_ORTHO_MAIN
void rgOrtho(float left, float right, float bottom, float top, float zNear, float zFar, RG_Matrix <float>& mat = (*projMat), bool use = false) {
	mat *= {
		{(2.f / (right - left)), 0, 0, -((right + left) / (right - left))	},
		{ 0, 					(2.f / (top - bottom)), 	0, 													-((top + bottom) / (top - bottom)) },
		{ 0, 											0, 						((-2.f) / (zFar - zNear)), 	-((zFar + zNear) / (zFar - zNear)) },
		{ 0, 											0, 						0, 													1 }
	};
	if (use)glUniformMatrix4fv(rg_projMat, 1, 0, mat.get());
}


void rgLoadIdentity(RG_Matrix<float>& mat) {
	mat.fill(4, 4, IdentityMat);
}

//MATRIX
void rgLoadMatrixf(const RG_Matrix<float>& m) {
	glUniformMatrix4fv(rg_projMat, 1, 0, m.get());
}

void rgLoadMatrixf(const RG_Matrix<float>& m,  uint id) {
	glUniformMatrix4fv(id, 1, 0, m.get());
}
/*
void rgLoadMatrixf(float* m, uint mattype = rg_projMat) {
	glUniformMatrix4fv(mattype, 1, 0, m);
}*/

void rgLoadIdentityMatrix() {
	glUniformMatrix4fv(rg_projMat, 1, 0, IdentityMat);
}
void rgLoadIdentityMatrix(uint id) {
	glUniformMatrix4fv(id, 1, 0, IdentityMat);
}

void rgLoadMatrixf(const float* m,  uint id) {
	glUniformMatrix4fv(id, 1, 0, m);
}

void rgReloadMatrix(RG_Matrix<float>& mat = (*projMat), bool use = false) {
	if (use)glUniformMatrix4fv(rg_projMat, 1, 0, mat.get());
}

//ROTATEf
void rgRotatef(float a, float x, float y, float z, RG_Matrix <float>& mat = (*projMat), bool use = false) {
	float c = cos(a / 180.f * M_PI);
	float s = sin(a / 180.f * M_PI);

	float rotateMat[16] =
	{
		(x * x * (1.f - c) + c), (x * y * (1.f - c) - z * s), (x * z * (1.f - c) + y * s), 0,

		(y * x * (1.f - c) + z * s), (y * y * (1.f - c) + c), (y * z * (1.f - c) - x * s), 0,

		(z * x * (1.f - c) - y * s), (z * y * (1.f - c) + x * s), (z * z * (1.f - c) + c), 0,

		0, 0, 0, 1
	};

	//MultyMat4(projMat,rotateMat,projMat);
	mat *= rotateMat;
	if (use)glUniformMatrix4fv(rg_projMat, 1, 0, mat.get());
}

//SCALEF
void rgScalef(float x, float y, float z, RG_Matrix <float>& mat = (*projMat), bool use = false) {

	float scaleMat[16] =
	{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};

	//MultyMat4(projMat,scaleMat,projMat);
	mat *= scaleMat;
	if (use)glUniformMatrix4fv(rg_projMat, 1, 0, mat.get());
}


//TRANSFORM
void rgTranslatef(float x, float y, float z, RG_Matrix <float>& mat = (*projMat), bool use = false) {

	float TranslMat[16] =
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};

	mat *= TranslMat;
	if (use)glUniformMatrix4fv(rg_projMat, 1, 0, mat.get());
}

//DRAW ARRAY,ELEMENTS
inline void rgDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   

	glDrawElements(mode, count, type, indices);
}

inline void rgDrawArrays(GLenum mode, GLint first, GLsizei count) {
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   

	glDrawArrays(mode, first, count);
}
//BEGIN END
inline void rgBegin(GLenum mode) {
	//glUniformMatrix4fv(rg_projMat,1,0,projMat->mat());   
	//glUseProgram(0);
	glBegin(mode);
}

inline void rgEnd() {
	glEnd();
	//glUseProgram(RG_STANDART_SHADER_PROG);
}


//CLIENT STATE
inline void rgEnableClientState(RG_ATTRIB_CONST type) {
	glEnableVertexAttribArray(type);

}
inline void rgDisableClientState(RG_ATTRIB_CONST type) {
	glDisableVertexAttribArray(type);
}
//TEXTURE
inline void rgBindTexture(int id, int type = GL_TEXTURE_2D) {
	glUniform1i(rg_setTexture, id);
}

template<class type>
RG::vec4<double> rgFrustumfa(
	float left, float right,
	float bottom, float top,
	float zNear, float zFar,
	RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x * (2.0 * zNear / (right - left)) + in.w * ((right + left) / (right - left));
	out.y = in.y * (2.0 * zNear / (top - bottom)) + in.w * ((top + bottom) / (top - bottom));
	out.z = in.z * (-1.0 * (zFar + zNear) / (zFar - zNear)) + in.w * (-2.0 * zFar * zNear / (zFar - zNear));
	out.w = in.z * -1.0;
	in = out;
	return in;

}


template<class type>
RG::vec4<double> rgOrthofa(
	float left, float right,
	float bottom, float top,
	float zNear, float zFar,
	RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x * (2.0 / (right - left)) + in.w * (-(right + left) / (right - left));
	out.y = in.y * (2.0 / (top - bottom)) + in.w * (-(top + bottom) / (top - bottom));
	out.z = in.z * (-2.0 / (zFar - zNear)) + in.w * (-(zFar + zNear) / (zFar - zNear));
	out.w = in.w;
	in = out;
	return in;
}

template<class type>
RG::vec4<double> rgScalefa(double x, double y, double z, RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x * x;
	out.y = in.y * y;
	out.z = in.z * z;
	out.w = in.w;
	in = out;
	return in;
}

template<class type>
RG::vec4<double> rgRotatefa(double a, double x, double y, double z, RG::vec4<type>& in) {
	double c = cos(a * M_PI / 180.0);
	double s = sin(a * M_PI / 180.0);
	double oneMinusC = 1.0 - c;

	RG::vec4<type> out;
	out.x = in.x * (x * x * oneMinusC + c) + in.y * (x * y * oneMinusC - z * s) + in.z * (x * z * oneMinusC + y * s);
	out.y = in.x * (y * x * oneMinusC + z * s) + in.y * (y * y * oneMinusC + c) + in.z * (y * z * oneMinusC - x * s);
	out.z = in.x * (z * x * oneMinusC - y * s) + in.y * (z * y * oneMinusC + x * s) + in.z * (z * z * oneMinusC + c);
	out.w = in.w;
	in = out;
	return in;



}

template<class type>
RG::vec4<double> rgTranslatefa(double x, double y, double z, RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x + in.w * x;
	out.y = in.y + in.w * y;
	out.z = z + in.w * z;
	out.w = in.w;
	in = out;
	return in;
}



template<class type>
RG::vec4<double> rgFrustumfat(
	float left, float right,
	float bottom, float top,
	float zNear, float zFar,
	RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x * (2.0 * zNear / (right - left)) + in.y * ((right + left) / (right - left));
	out.y = in.x * (2.0 * zNear / (top - bottom)) + in.y * ((top + bottom) / (top - bottom));
	out.z = in.z * (-1.0 * (zFar + zNear) / (zFar - zNear)) + in.w * (-2.0 * zFar * zNear / (zFar - zNear));
	out.w = in.w * -1.0;
	in = out;
	return in;
}

template<class type>
RG::vec4<double> rgOrthofat(
	float left, float right,
	float bottom, float top,
	float zNear, float zFar,
	RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x * (2.0 / (right - left)) + in.y * (-(right + left) / (right - left));
	out.y = in.x * (2.0 / (top - bottom)) + in.y * (-(top + bottom) / (top - bottom));
	out.z = in.z * (-2.0 / (zFar - zNear)) + in.y * (-(zFar + zNear) / (zFar - zNear));
	out.w = in.w;
	in = out;
	return in;
}

template<class type>
RG::vec4<double> rgScalefat(double x, double y, double z, RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x * x;
	out.y = in.y * y;
	out.z = in.z * z;
	out.w = in.w;
	in = out;
	return in;
}

template<class type>
RG::vec4<double> rgRotatefat(double a, double x, double y, double z, RG::vec4<type>& in) {
	double c = cos(a * M_PI / 180.0);
	double s = sin(a * M_PI / 180.0);
	double oneMinusC = 1.0 - c;

	RG::vec4<type> out;
	out.x = in.x * (x * x * oneMinusC + c) + in.y * (x * y * oneMinusC + z * s) + in.z * (x * z * oneMinusC - y * s);
	out.y = in.x * (y * x * oneMinusC - z * s) + in.y * (y * y * oneMinusC + c) + in.z * (y * z * oneMinusC + x * s);
	out.z = in.x * (z * x * oneMinusC + y * s) + in.y * (z * y * oneMinusC - x * s) + in.z * (z * z * oneMinusC + c);
	out.w = in.w;
	in = out;
	return in;
}

/*
template<class type>
RG::vec4<double> rgRotatefiat(double a, double x, double y, double z, RG::vec4<type>& in) {
	double c = cos((a)*M_PI / 180.0);
	double s = sin((a)*M_PI / 180.0);
	double oneMinusC = 1.0 - c;
	double oneMinusS = 1.0 - s;

	RG::vec4<type> out;
	//RG::vec3<double> temp{ in.x *((x * x * oneMinusC + (y==1?(1./c):c))),in.y * (x * y * oneMinusC + z * s),in.z * (x * z * oneMinusC - y * c) };
	//rg_cout << in.x << endl;
	//out.x = temp.x + temp.y + temp.z;
	//rg_cout << "x: "<<temp.x << " y: " << temp.y << " z: " << temp.z << endl << endl;

	// out.x = in.x * (x * x *oneMinusC + (y==1?(1./c):c)) + in.y * (x * y * oneMinusC + z * s) + in.z * (x * z * oneMinusC - y * s);
	// out.y = in.x * (y * x * oneMinusC - z * s) + in.y * (y * y * oneMinusC + (x==1?(1./c):c)) + in.z * (y * z * oneMinusC + x * s);
	// out.z = in.x * (z * x * oneMinusC + y * s) + in.y * (z * y * oneMinusC - x * s) + in.z * (z * z * oneMinusC + c);
	//rg_cout<<x<<" "<<y<<" "<<z<<endl;
	//rg_cout<<in.y<<" "<<z<<" "<<s<<"="<<in.y * (z * s)<<endl<<endl;4

	//out.x = in.x * (x * x * oneMinusC + (y == 1 ? (1. / c) : c)) + in.y * (z * s) + in.z * (-y * s);

	out.x = in.x * (x * x * oneMinusC + (y == 1 ? (1. / c) : c)) + in.y * (z * s) + in.z * (-y * s);
	out.y = in.y * (y * y * oneMinusC + (x == 1 ? (1. / c) : c)) + in.z * (x * s) + in.x * (-z * s);
	out.z = in.z * (z * z * oneMinusC + (z == 1 ? (1. / c) : c)) + in.x * (y * s) + in.y * (-x * s);


	out.w = in.w;

	in = out;
	return in;
}*/
template<class type>
RG::vec4<type> rgRotatefiat(double a, double x, double y, double z, RG::vec4<type>& in) {
	// Угол в радианах с инверсией
	double rad = -a * M_PI / 180.0; // Инвертируем угол
	double c = cos(rad);
	double s = sin(rad);
	double oneMinusC = 1.0 - c;
	double oneMinusS = 1.0 - s;

	RG::vec4<type> out;

	// Особое условие для осей с использованием 1/c	
	out.x = in.x * (x * x * oneMinusC + (y != 0 ? 1. / c : c)) + in.y * (-z * s);
	out.y = in.y * (y * y * oneMinusC + (x != 0 ? 1. / c : c)) + in.x * (z * s);
	out.z = in.z * (z * z * oneMinusC + 1. / c);
	out.w = in.w;

	in = out;
	return in;
}



template<class type>
RG::vec4<double> rgTranslatefat(double x, double y, double z, RG::vec4<type>& in) {
	RG::vec4<type> out;
	out.x = in.x + in.w * x;
	out.y = in.y + in.w * y;
	out.z = in.z + in.w * z;
	out.w = in.w;
	in = out;
	return in;
}