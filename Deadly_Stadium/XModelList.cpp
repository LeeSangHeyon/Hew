//----------------------------------------------------------------------------
//
//	XModel�̃��X�g
//
//														 ����ҁF����
//                                                       �쐬���F2018/11/07
//----------------------------------------------------------------------------

//---------------------------�C���N���[�h-------------------------------------
#include "XModelList.h"

//---------------------------�O���[�o���ϐ�-----------------------------------
static const XMODEL_URL gc_XModelURL[CXModelList::LABEL_XMODEL::XM_MAX] =
{
	{ "Data/XModel/cart/cart.x",true } ,
	{ "Data/XModel/player/pumpkin.x",true } ,
	{ "Data/XModel/Lexus/Lexus.x",true } ,
	{ "Data/XModel/Head.x",true } ,
	{ "Data/XModel/Body.x",true } ,
	{ "Data/XModel/RightArm01.x",true } ,
	{ "Data/XModel/RightArm02.x",true } ,
	{ "Data/XModel/LeftArm01.x",true } ,
	{ "Data/XModel/LeftArm02.x",true } ,
	{ "Data/XModel/RightLeg01.x",true } ,
	{ "Data/XModel/RightLeg02.x",true } ,
	{ "Data/XModel/LeftLeg01.x",true } ,
	{ "Data/XModel/LeftLeg02.x",true } ,
	{ "Data/XModel/Lexus/LexusNoWheel.x",true } ,
	{ "Data/XModel/Lexus/LexusWheelLeft.x",true } ,
	{ "Data/XModel/Lexus/LexusWheelRight.x",true } ,
	{ "Data/XModel/Clinder.x",true } ,
	{ "Data/XModel/Cube.x",true } ,
};

//---------------------------�v���g�^�C�v�錾---------------------------------
XMODEL_URL CXModelList::GetStatus(LABEL_XMODEL LabelModel)
{
	return gc_XModelURL[LabelModel];
}