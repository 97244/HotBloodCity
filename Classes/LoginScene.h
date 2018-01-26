#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class LoginScene :public Layer {
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(LoginScene);
	//void joinGame();
	void btnClick(Ref*pSender);
};