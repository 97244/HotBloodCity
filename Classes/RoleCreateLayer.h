#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


struct RoleObj {
	Point p;
	int tag;
};

class RoleCreateLayer :public Layer {
private:
	Ref *m_selected;
	std::string m_nickName;
	int m_roleID;
	Vector<Ref*>m_roleArray;
public:
	RoleCreateLayer();
	virtual ~RoleCreateLayer();
	virtual bool init();
	static Scene*createScene();
	CREATE_FUNC(RoleCreateLayer);
	void joinGame();
	void setSelector(Ref *pSender, Control::EventType controlEven);
	/*
	void randomNickName(Ref* pSender);
	void sendMessage(Ref* pSender);
	  */
	void callBackEnter(Ref* pSender);
	void runActionsForFigure(Ref *pSender);
};