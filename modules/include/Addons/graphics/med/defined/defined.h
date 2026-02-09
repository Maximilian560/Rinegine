#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/med/def"
struct RG_Standart {
	inline static RG_Window*& Window = RG_Window_Standart;
	inline static RG_Camera*& Camera = RG_Camera_StandartPtr;
	inline static RG_Timer*& Timer = RG_Timer_StandartPtr;
	inline static RG_Atlas*& Atlas = RG_Atlas_StandartPtr;
	inline static RG_Shader*& Shader = RG_Shader_StandartPtr;
	inline static RG_Shader_Raw*& RawShader = RG_Shader_Raw_StandartPtr;

	void operator=(const RG_Standart& in) {
		Window = in.Window;
		Camera = in.Camera;
		Timer = in.Timer;
		Atlas = in.Atlas;
		Shader = in.Shader;
		RawShader = in.RawShader;
		RG_Window_Standart = in.Window;
		RG_Camera_StandartPtr = in.Camera;
		RG_Timer_StandartPtr = in.Timer;
		RG_Atlas_StandartPtr = in.Atlas;
		RG_Shader_StandartPtr = in.Shader;
		RG_Shader_Raw_StandartPtr = in.RawShader;
	}
};