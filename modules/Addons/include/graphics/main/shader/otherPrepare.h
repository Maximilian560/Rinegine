#pragma once


void RG_PREPARE_SHADER(RG_Shader sh){
	RG_PREPARE_SHADER(sh.get_prog());
}