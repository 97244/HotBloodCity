#pragma once
#include "cocos2d.h"
#include "TextureController.h"
USING_NS_CC;
#define TAG_ANIMATE 0xfffffff0

//����
typedef enum
{
	FDirUp = 8,
	FDirLeftAndUp = 7,
	FDirLeft = 6,
	FDirDownAndLeft = 5,
	FDirDown = 4,
	FDirRightAndDown = 3,
	FDirRight = 2,
	FDirUpAndRight = 1,
	FDirNone = 0
}FigureDirectionType;
//״̬
typedef enum
{
	FStateDeath = 7,     //����
	FStateHurt = 6,     //����
	FStateCaster = 5,     //ʩ��
	FStateAttack = 4,     //����
	FStateRun = 3,     //��
	FStateWalk = 2,     //��
	FStateStand = 1,     //վ��
	FStateNone = 0
}FigureStateType;

class FigureDelegate;
class Figure :public Sprite
{
private:
	float m_frameRate;//�ȼ�

	unsigned int m_figureNumber;//���

	unsigned int m_hairNumber;//ͷ��

	unsigned int  m_weaponNumber;//����

	TexturePathType m_pathType; //����·��

	FigureDelegate* m_pDelegate;//����

public:
	Figure(TexturePathType type, unsigned int figureNumber);
	virtual ~Figure();

	virtual void onEnter();

	virtual void onExit();

	static Figure* create(TexturePathType type, unsigned int figureNumber);

	bool init();

	void setHair(unsigned int hairNumber);

	void setWeapon(unsigned int weaponNumber);

	void setFigureState(FigureStateType stateType, FigureDirectionType directionType);

	void setDelegate(FigureDelegate* delegate);
	//״̬
	CC_SYNTHESIZE_READONLY(FigureStateType, m_stateType, StateType);
	//����
	CC_SYNTHESIZE_READONLY(FigureDirectionType, m_directionType, DirectionType);
	//ͷ��
	CC_SYNTHESIZE_READONLY(Sprite*, m_hairSprite, HairSprite);
	//����
	CC_SYNTHESIZE_READONLY(Sprite*, m_weaponSprite, WeaponSprite);
	//���£�����
	Point getAnchorPointWithFoot();
	//ͷ������
	Point getAnchorPointWithHand();
	//�м䣭����
	Point getAnchorPointCenter();
	//͸����
	void setOpacity(GLubyte opacity);
private:

	void updateFigure();

	void runActions();

	ActionInterval* getRunActionsFromSprite(Sprite* sprite, std::string& path);
	//------------�ӿڷ���------
	void attackCompleted();

	void hurtCompleted();

	void deathCompleted();

	void attacking();
};

//�ӿ�
class FigureDelegate
{
public:
	//������
	virtual void attacking() = 0;
	//�������
	virtual void attackCompleted() = 0;
	//�ܵ�����
	virtual void underAttack() = 0;
	//����
	virtual void deathActionFinish() = 0;
	//ɾ��Delegate
	void removeDelegate(Figure* var);
};