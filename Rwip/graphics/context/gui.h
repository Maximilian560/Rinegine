#pragma once

enum LINK_GUI_TYPE
{
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

void rgLoadGuiMatrix(LINK_GUI_TYPE type,float sizeWin = 1,bool dim = false)
{
	RG_Matrix<float> temp2;
	temp2.reInit(4,4,IdentityMat);
	switch(type)
		{
		case RG_GUI_LINK_LEFT_TOP: 		rgOrtho(0,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*2*sizeWin  , -2*sizeWin,0, -2*sizeWin,2*sizeWin,temp2); break;
		case RG_GUI_LINK_LEFT_BOTTOM: 	rgOrtho(0,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*2*sizeWin  ,  0,2*sizeWin, -2*sizeWin,2*sizeWin,temp2); break;
		case RG_GUI_LINK_LEFT_CENTER: 	rgOrtho(0,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*2*sizeWin  , -1*sizeWin,1*sizeWin, -2*sizeWin,2*sizeWin,temp2); break;
	
		case RG_GUI_LINK_RIGHT_TOP: 	rgOrtho( -((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*2*sizeWin,0, -2*sizeWin,0, -2*sizeWin,2*sizeWin,temp2); break;
		case RG_GUI_LINK_RIGHT_BOTTOM: 	rgOrtho( -((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*2*sizeWin,0,  0,2*sizeWin, -2*sizeWin,2*sizeWin,temp2); break;
		case RG_GUI_LINK_RIGHT_CENTER: 	rgOrtho( -((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*2*sizeWin,0, -1*sizeWin,1*sizeWin, -2*sizeWin,2*sizeWin,temp2); break;
	
		case RG_GUI_LINK_CENTER_TOP: 	rgOrtho( -((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*sizeWin,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*sizeWin, -2*sizeWin,0, -2*sizeWin,2*sizeWin,temp2); break;
		case RG_GUI_LINK_CENTER_BOTTOM: rgOrtho( -((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*sizeWin,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*sizeWin,  0,2*sizeWin, -2*sizeWin,2*sizeWin,temp2); break;
		case RG_GUI_LINK_CENTER_CENTER: rgOrtho( -((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*sizeWin,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*sizeWin, -1*sizeWin,1*sizeWin, -2*sizeWin,2*sizeWin,temp2); break;
		case RG_GUI_LINK_NONE: break;
		}
	rgLoadMatrixf(temp2,rg_viewMat);

}
