#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


//��������
typedef enum
{
	TexturePathFigure = 1,          //��ɫ
	TexturePathMonster = 2,         //����
	TexturePathHair = 3,            //ͷ��
	TexturePathWeapon = 4,          //����
	TexturePathSkillCaster = 5,     //����ʩ��
	TexturePathSkillLocus = 6,      //���ܹ켣
	TexturePathSkillExplosion = 7  //���ܱ�ը
}TexturePathType;

class TextureController {

public:

	static string getTextureRoute(TexturePathType type, unsigned int number);

	static string getTexturePath(TexturePathType type, unsigned int number);

	static void addSpriteFrames(TexturePathType type, unsigned int number, Ref *target = NULL, SEL_CallFunc selector = NULL);

	static void subSpriteFrames(TexturePathType type, unsigned int number);

	static void removeAllSpriteFrames();

};