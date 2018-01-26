#include "LoginScene.h"
#include "RoleCreateLayer.h"
Scene*LoginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoginScene::init()
{
	bool isRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		auto wsize = Director::getInstance()->getWinSize();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/tlcangshan.mp3", true);
		auto bj = Sprite::create("logo.png");
		bj->setPosition(wsize.width / 2, wsize.height / 2);
		this->addChild(bj);

		auto login = MenuItemImage::create("btn_start_d.png",
			"btn_start_n.png", CC_CALLBACK_1(LoginScene::btnClick, this));
		login->setPosition(wsize.width / 2, login->getContentSize().height + 10);
		auto menu = Menu::create(login, NULL);
		menu->setAnchorPoint(Point::ZERO);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);
		isRet = true;
	} while (0);

	return isRet;
}

void LoginScene::btnClick(Ref*pSender)
{
	Director::getInstance()->replaceScene(RoleCreateLayer::createScene());
}