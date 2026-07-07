#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/context-gui"

enum LINK_GUI_TYPE {
	RG_GUI_LINK_NONE,
	RG_GUI_LINK_LEFT_TOP,
	RG_GUI_LINK_LEFT_BOTTOM,
	RG_GUI_LINK_LEFT_CENTER,

	RG_GUI_LINK_RIGHT_TOP,
	RG_GUI_LINK_RIGHT_BOTTOM,
	RG_GUI_LINK_RIGHT_CENTER,

	RG_GUI_LINK_CENTER_TOP,
	RG_GUI_LINK_CENTER_BOTTOM,
	RG_GUI_LINK_CENTER_CENTER,
};


RG_Matrix<float> RG_Get_Gui_Matrix(LINK_GUI_TYPE type, float sizeWin = 1, bool dim = false) {
	RG_Matrix<float> temp2(4, 4, IdentityMat);
	//temp2.fill(4, 4, IdentityMat);
	//double tempOtn = (RG_SYS_WINDOWSdow_Standart->set().resolution.x>RG_SYS_WINDOWSdow_Standart->set().resolution.y)?((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x/RG_SYS_WINDOWSdow_Standart->set().resolution.y):((double)RG_SYS_WINDOWSdow_Standart->set().resolution.y/RG_SYS_WINDOWSdow_Standart->set().resolution.x);
	//POINT2D<double> tempOtn;
	//tempOtn.x = (RG_SYS_WINDOWSdow_Standart->set().resolution.x > RG_SYS_WINDOWSdow_Standart->set().resolution.y) ? ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) : 1;
	//tempOtn.y = (double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y;
	switch (type) {
		case RG_GUI_LINK_LEFT_TOP: 			rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_BOTTOM: 	rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_CENTER: 	rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_RIGHT_TOP: 		rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_BOTTOM: 	rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_CENTER: 	rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_CENTER_TOP: 		rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_BOTTOM: rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_CENTER: rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_NONE: break; /////////////////////TODO PLZ DON'T FORGET!!!!
		default:
			RG_Debug::addl(RG_LOG_LOCK_WARNING, "Unknown GUI Link Type!");
	}
	return temp2;
}
void RG_Set_Gui_Matrix(RG_Matrix<float>& temp2, LINK_GUI_TYPE type, float sizeWin = 1, bool dim = false) {
	temp2.init(4, 4, IdentityMat);
	switch (type) {
		case RG_GUI_LINK_LEFT_TOP: 			rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_BOTTOM: 	rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_CENTER: 	rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_RIGHT_TOP: 		rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_BOTTOM: 	rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_CENTER: 	rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_CENTER_TOP: 		rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_BOTTOM: rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_CENTER: rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_NONE: break; /////////////////////TODO PLZ DON'T FORGET!!!!
		default:
			RG_Debug::addl(RG_LOG_LOCK_WARNING, "Unknown GUI Link Type!");
	}
}
void rgLoadGuiMatrix(LINK_GUI_TYPE type, float sizeWin = 1, bool dim = false) {
	static RG_Matrix<float> temp2;
	temp2.init(4, 4, IdentityMat);
	//double tempOtn = (RG_SYS_WINDOWSdow_Standart->set().resolution.x>RG_SYS_WINDOWSdow_Standart->set().resolution.y)?((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x/RG_SYS_WINDOWSdow_Standart->set().resolution.y):((double)RG_SYS_WINDOWSdow_Standart->set().resolution.y/RG_SYS_WINDOWSdow_Standart->set().resolution.x);
	//POINT2D<double> tempOtn;
	//tempOtn.x = (RG_SYS_WINDOWSdow_Standart->set().resolution.x > RG_SYS_WINDOWSdow_Standart->set().resolution.y) ? ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) : 1;
	//tempOtn.y = (double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y;
	switch (type) {
		case RG_GUI_LINK_LEFT_TOP: 			rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_BOTTOM: 	rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_CENTER: 	rgOrtho(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_RIGHT_TOP: 		rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_BOTTOM: 	rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_CENTER: 	rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_CENTER_TOP: 		rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_BOTTOM: rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_CENTER: rgOrtho(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_NONE: break; /////////////////////TODO PLZ DON'T FORGET!!!!
		default:	RG_Debug::addl(RG_LOG_LOCK_WARNING, "Unknown GUI Link Type!");
	}
	rgLoadMatrixf(temp2, rg_viewMat);
}

template<class T>
void RG_Point_To_GUI(RG::vec4<T>& temp2, LINK_GUI_TYPE type, float sizeWin = 1, bool dim = false) {
	switch (type) {
		case RG_GUI_LINK_LEFT_TOP: 			rgOrthofa(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_BOTTOM: 	rgOrthofa(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_CENTER: 	rgOrthofa(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_RIGHT_TOP: 		rgOrthofa(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_BOTTOM: 	rgOrthofa(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_CENTER: 	rgOrthofa(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin, 0, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;

		case RG_GUI_LINK_CENTER_TOP: 		rgOrthofa(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_BOTTOM: rgOrthofa(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_CENTER_CENTER: rgOrthofa(-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin, -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_NONE: break; /////////////////////TODO PLZ DON'T FORGET!!!!
		default:
			RG_Debug::addl(RG_LOG_LOCK_WARNING, "Unknown GUI Link Type!");
	}
}

template<class T>
void RG_Point_To_Invert_GUI(RG::vec4<T>& temp2, LINK_GUI_TYPE type, float sizeWin = 1, bool dim = false) {
	switch (type) {
		// case RG_GUI_LINK_LEFT_TOP: 			rgOrthofa(0, 1./(((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin), -2 * sizeWin, 0, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		// case RG_GUI_LINK_LEFT_BOTTOM: 	rgOrthofa(0, 1./(((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin), 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		// case RG_GUI_LINK_LEFT_CENTER: 	rgOrthofa(0, 1./(((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * 2 * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_LEFT_TOP:
			rgTranslatefat(1, -1, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;
		case RG_GUI_LINK_LEFT_BOTTOM:
			rgTranslatefat(1, 1, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;
		case RG_GUI_LINK_LEFT_CENTER:
			rgTranslatefat(1, 0, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;

		case RG_GUI_LINK_RIGHT_TOP: 		//rgOrthofa(0, ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x) * 2 * sizeWin, 0, 2 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			rgTranslatefat(-1, -1, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
		case RG_GUI_LINK_RIGHT_BOTTOM:
			rgTranslatefat(-1, 1, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;
		case RG_GUI_LINK_RIGHT_CENTER:
			rgTranslatefat(-1, 0, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;

		case RG_GUI_LINK_CENTER_TOP:
			rgTranslatefat(0, -1, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;
		case RG_GUI_LINK_CENTER_BOTTOM:
			rgTranslatefat(0, 1, 0, temp2);
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;
		case RG_GUI_LINK_CENTER_CENTER:
			rgOrthofa(1. / (-((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), 1. / (((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y) * sizeWin), -1 * sizeWin, 1 * sizeWin, -RG_Render_Distance2D[0] * sizeWin, RG_Render_Distance2D[1] * sizeWin, temp2); break;
			break;
		case RG_GUI_LINK_NONE: break; /////////////////////TODO PLZ DON'T FORGET!!!!
		default:
			RG_Debug::addl(RG_LOG_LOCK_WARNING, "Unknown GUI Link Type!");
	}
}