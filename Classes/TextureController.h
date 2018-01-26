#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


//纹理类型
typedef enum
{
	TexturePathFigure = 1,          //角色
	TexturePathMonster = 2,         //怪物
	TexturePathHair = 3,            //头像
	TexturePathWeapon = 4,          //武器
	TexturePathSkillCaster = 5,     //技能施法
	TexturePathSkillLocus = 6,      //技能轨迹
	TexturePathSkillExplosion = 7  //技能爆炸
}TexturePathType;

class TextureController {

public:

	static string getTextureRoute(TexturePathType type, unsigned int number);

	static string getTexturePath(TexturePathType type, unsigned int number);

	static void addSpriteFrames(TexturePathType type, unsigned int number, Ref *target = NULL, SEL_CallFunc selector = NULL);

	static void subSpriteFrames(TexturePathType type, unsigned int number);

	static void removeAllSpriteFrames();

};