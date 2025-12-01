#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/med/context"

void RG_TestGLError() {
	int glError = 0;
	RG_LOG_LOCK_INFO("Start test GL error");
	while ((glError = glGetError()) != GL_NO_ERROR) {
		switch (glError) {
			case GL_NO_ERROR:						RG_LOG_LOCK_ERROR("GL_NO_ERROR");break;
			case GL_INVALID_ENUM:				RG_LOG_LOCK_ERROR("GL_INVALID_ENUM");break;
			case GL_INVALID_VALUE:			RG_LOG_LOCK_ERROR("GL_INVALID_VALUE");break;
			case GL_INVALID_OPERATION:	RG_LOG_LOCK_ERROR("GL_INVALID_OPERATION");break;
			case GL_STACK_OVERFLOW:			RG_LOG_LOCK_ERROR("GL_STACK_OVERFLOW");break;
			case GL_STACK_UNDERFLOW:		RG_LOG_LOCK_ERROR("GL_STACK_UNDERFLOW");break;
			case GL_OUT_OF_MEMORY:			RG_LOG_LOCK_ERROR("GL_OUT_OF_MEMORY");break;
			default:										RG_LOG_LOCK_ERROR("Unknown error");break;
		};
	}
	RG_LOG_LOCK_INFO("Stop test GL error");
}

void RG_GL_Get_Error() {
	int glError = 0;
	RG_LOG_LOCK_INFO("Start test GL error");
	while ((glError = glGetError()) != GL_NO_ERROR) {
		switch (glError) {
			case GL_NO_ERROR:						RG_LOG_LOCK_ERROR("GL_NO_ERROR");break;
			case GL_INVALID_ENUM:				RG_LOG_LOCK_ERROR("GL_INVALID_ENUM");break;
			case GL_INVALID_VALUE:			RG_LOG_LOCK_ERROR("GL_INVALID_VALUE");break;
			case GL_INVALID_OPERATION:	RG_LOG_LOCK_ERROR("GL_INVALID_OPERATION");break;
			case GL_STACK_OVERFLOW:			RG_LOG_LOCK_ERROR("GL_STACK_OVERFLOW");break;
			case GL_STACK_UNDERFLOW:		RG_LOG_LOCK_ERROR("GL_STACK_UNDERFLOW");break;
			case GL_OUT_OF_MEMORY:			RG_LOG_LOCK_ERROR("GL_OUT_OF_MEMORY");break;
			default:										RG_LOG_LOCK_ERROR("Unknown error");break;
		};
	}
	RG_LOG_LOCK_INFO("Stop test GL error");
}


