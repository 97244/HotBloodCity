#include "RoleCreateLayer.h"
#include "SimpleAudioEngine.h"
#include "FontChina.h"
#include "Figure.h"

RoleCreateLayer::RoleCreateLayer()
	:m_nickName("")
	, m_selected(NULL)
{
}

RoleCreateLayer::~RoleCreateLayer()
{
	Director::getInstance()->getTextureCache()->removeAllTextures();
}
Scene* RoleCreateLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = RoleCreateLayer::create();
	scene->addChild(layer);
	return scene;
}

bool RoleCreateLayer::init()
{
	bool isRet = false;
	do 
	{
		Size winSize = Director::getInstance()->getWinSize();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/tljinghu.mp3", true);

		auto bj = Sprite::create("bjrole.png");
		bj->setPosition(winSize.width / 2, winSize.height / 2);
		this->addChild(bj);

		auto Label1 = Label::createWithTTF(FontChina::G2U("血腥、暴力、耐打"), "fonts/FZKATJW.ttf",28);
		Label1->setPosition(Point(170, 120));
		Label1->setColor(Color3B::RED);
		Label1->enableOutline(Color4B(124, 66, 24, 255), 2);
		this->addChild(Label1);

		auto Label2 = Label::createWithTTF(FontChina::G2U("召唤、辅助、周旋"), "fonts/FZKATJW.ttf", 28);
		Label2->setPosition(Point(470, 80));
		Label2->setColor(Color3B::ORANGE);
		Label2->enableOutline(Color4B(124, 66, 24, 255), 2);
		this->addChild(Label2);


		auto Label3 = Label::createWithTTF(FontChina::G2U("强力、强力、还是强力"), "fonts/FZKATJW.ttf", 28);
		Label3->setPosition(Point(800, 60));
		Label3->setColor(Color3B::YELLOW);
		Label3->enableOutline(Color4B(124, 66, 24, 255), 2);
		this->addChild(Label3);

		RoleObj rb0;
		rb0.p = Point(100, 200);
		rb0.tag = 11001;

		RoleObj rb1;
		rb1.p = Point(250, 200);
		rb1.tag = 11002;

		RoleObj rb2;
		rb2.p = Point(403, 160);
		rb2.tag = 12001;

		RoleObj rb3;
		rb3.p = Point(556, 160);
		rb3.tag = 12002;

		RoleObj rb4;
		rb4.p = Point(720, 150);
		rb4.tag = 13001;

		RoleObj rb5;
		rb5.p = Point(880, 150);
		rb5.tag = 13002;

		RoleObj  ro[6] = { rb0,rb1,rb2,rb3,rb4,rb5 };


		for (int i = 0; i < 6; ++i)
		{
			auto button = ControlButton::create();
			button->setHighlighted(false);
			button->setPreferredSize(Size(120, 200));
			button->setPosition(ro[i].p);
			this->addChild(button);
			button->setTag(ro[i].tag);
			button->addTargetWithActionForControlEvents(this, cccontrol_selector(
				RoleCreateLayer::setSelector), Control::EventType::TOUCH_DOWN);
			int weapon = 1000 + i * 100;

			Figure* monomer = Figure::create(TexturePathFigure, ro[i].tag);
			monomer->setScale(1.5);
			monomer->setHair(ro[i].tag / 10 - 100);
			monomer->setWeapon(weapon);
			monomer->setPosition(button->getContentSize() / 2);
			monomer->setColor(Color3B(127, 127, 127));
			button->addChild(monomer);
			m_roleArray.pushBack(monomer);
		}


		auto back = MenuItemImage::create("enter_n.png",
			"enter_h.png", CC_CALLBACK_1(RoleCreateLayer::callBackEnter, this));
		back->setPosition(Point(winSize.width + 200, winSize.height - 10));
		auto menu = Menu::create(back, NULL);
		menu->setPosition(Point::ZERO);
		menu->setScale(0.5);
		menu->setTag(999);
		menu->setVisible(false);
		this->addChild(menu, 2);
		isRet = true;
	} while (0);

	return isRet;
}

void RoleCreateLayer::callBackEnter(Ref* pSender)
{
	GameSocket::sendRoleCreate(this, m_roleID, FontChina::G2U("古月"));//SOCKET
}

void RoleCreateLayer::setSelector(Ref *pSender, Control::EventType controlEven)
{
	ControlButton *btn = dynamic_cast<ControlButton*>(pSender);
	if (btn)
	{
		m_roleID = btn->getTag();
		if (m_selected)
		{
			Figure* monomer = (Figure*)m_selected;
			ControlButton* button = (ControlButton*)monomer->getParent();
			monomer->setFigureState(FStateStand, FDirDown);
			monomer->setColor(ccc3(127, 127, 127));
			ScaleTo* scaleTo = ScaleTo::create(0.15f, 1.0f);
			CallFunc* finish = CallFunc::create(monomer, callfunc_selector(Monomer::stopAllActions));
			CallFunc* finish2 = CallFunc::create(monomer->getWeaponSprite(), callfunc_selector(Sprite::stopAllActions));
			Sequence* actions = Sequence::create(scaleTo, finish, finish2, NULL);
			monomer->runAction(actions);
			button->setTouchEnabled(true);
		}

		for (int i = 0; i < m_roleArray.size(); i++)
		{
			Figure* monomer = (Figure*)m_roleArray.at(i);
			ControlButton* button = (ControlButton*)monomer->getParent();
			if (btn == (button))
			{
				button->setTouchEnabled(false);
				ScaleTo* scaleTo = ScaleTo::create(0.15, 1.2);
				monomer->runAction(scaleTo);
				monomer->setColor(ccWHITE);
				this->runActionsForFigure(monomer);
				m_selected = monomer;
			}
		}
		this->getChildByTag(999)->setVisible(true);
	}
}

void RoleCreateLayer::joinGame()
{
	//GameLoading::runGameLoading(200, 4);//地图200  传送编号1
	this->removeFromParent();
}

void RoleCreateLayer::runActionsForFigure(Ref *pSender)
{
	Figure* monomer = (Figure*)pSender;

	monomer->setFigureState(FStateAttack, FDirDown);
	 DelayTime* delayTime = DelayTime::create(2.f);
    CCCallFuncO* finish = CCCallFuncO::create(this, callfuncO_selector(RoleCreateLayer::runActionsForFigure), monomer);
    Sequence* actions = Sequence::create(delayTime, finish, NULL);
    monomer->runAction(actions);
}