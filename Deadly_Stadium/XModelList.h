//----------------------------------------------------------------------------
//
//	XModelのリスト
//
//														 制作者：劉喆
//                                                       作成日：2018/11/07
//----------------------------------------------------------------------------
#pragma once

//---------------------------インクルード-------------------------------------

//---------------------------クラス定義---------------------------------------
typedef struct {
	char cFlieAddress[128];
	bool bTexture;
}XMODEL_URL;

class CXModelList
{
public:
	typedef enum {
		XM_CART,
		XM_PLAYER,
		XM_BUGATTI,
		XM_HEAD,
		XM_BODY,
		XM_RIGHT_ARM_01,
		XM_RIGHT_ARM_02,
		XM_LEFT_ARM_01,
		XM_LEFT_ARM_02,
		XM_RIGHT_LEG_01,
		XM_RIGHT_LEG_02,
		XM_LEFT_LEG_01,
		XM_LEFT_LEG_02,
		XM_LEXUS_NO_WHEEL,
		XM_LEXUS_WHEEL_LEFT,
		XM_LEXUS_WHEEL_RIGHT,
		XM_CLINDER,
		XM_CUBE,
		XM_MAX
	}LABEL_XMODEL;

	static XMODEL_URL GetStatus(LABEL_XMODEL LabelModel);
private:

};