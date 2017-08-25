#include "Main_menu.h"
#include "World.h"
#include "Platform_ctrl.h"
#include <fstream>

USING_NS_CC;

Scene* World::createScene()
{
	return World::create();
}

bool World::init()
{
	if (!Scene::init())
	{
		return false;
	}
	srand(time(NULL));
	int tmp;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	middle = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	std::ifstream set_file("Settings.ini");
	set_file >> width >> height >> scale >> tmp;
	score = 0;
	ScoreBoard = cocos2d::Label::createWithSystemFont(std::to_string(score), "Arial", 36);
	ScoreBoard->setAnchorPoint(Vec2(0, 1));
	ScoreBoard->setPosition(Vec2(origin.x, visibleSize.height));
	this->addChild(ScoreBoard);
	if (tmp == 0 || tmp == 1)
	{
		ctrlr = tmp;
	}
	else// Если кто-то подкорректировал настройки, то дефолтный контроллер - клавиатура
	{
		ctrlr = true;
	}
	// Добавили платформу на сцену
	plat.set_platform_scale(scale);
	if (!plat.init())
		return false;
	plat.platform_sprite->setPosition(15 * width, origin.y + plat.platform_sprite->getContentSize().height);
	this->addChild(plat.platform_sprite);
	for (int i = 0; i < height; i++)
	{
		cocos2d::Sprite* left_spr = cocos2d::Sprite::create("border.png");
		cocos2d::Sprite* right_spr = cocos2d::Sprite::create("border.png");
		left_spr->setAnchorPoint(Vec2(1, 0));
		left_spr->setPosition(30, 30 * i);
		this->addChild(left_spr, 1);
		right_spr->setAnchorPoint(Vec2(0, 0));
		right_spr->setPosition(30 * width, 30 * i);
		this->addChild(right_spr, 1);
	}
	// Вызываем метод Update каждый фрейм
	block = Sprite::create("block.png");
	block->setAnchorPoint(Vec2(1, 0));
	block->setPosition(Vec2(60 + rand() % (30 * (width - 1) - 30), 30 * height));
	number = plat.getAnswer() + (-2 + rand() % 5);// Генерируем 5 чисел от -2 до 2 и прибавляем к ответу
	block_l = Label::createWithSystemFont(std::to_string(number), "Arial", 18);
	block_l->setPosition(block->getContentSize().width / 2, block->getContentSize().height / 2);
	block->addChild(block_l);
	this->addChild(block);
	block_act = MoveBy::create(5, Vec2(0, -500));
	block->runAction(block_act);
	this->scheduleUpdate();
	// Добавили считывателя с контроллера, выбор которого происходит в настройках
	if (ctrlr)
	{
		auto Listener = EventListenerKeyboard::create();
		Listener->onKeyPressed = CC_CALLBACK_2(World::keyPressed, this);
		Listener->onKeyReleased = CC_CALLBACK_2(World::keyReleased, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Listener, this);
	}
	else
	{
		auto Listener = EventListenerMouse::create();
		Listener->onMouseMove = CC_CALLBACK_1(World::onMouseMove, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Listener, this);
	}
	set_file.close();
	return true;
}

void World::update(float dt)
{
	
	if (block->getPositionY() < 0)
	{
		block->stopAction(block_act);
		repos_block();
	}
	if (block->getBoundingBox().intersectsRect(plat.platform_sprite->getBoundingBox()))
	{
		//CCLOG("Platform Left: %f, Right: %f, Top: %f, Bot: %f", plat.platform_sprite->getBoundingBox().getMinX(), 
		//	plat.platform_sprite->getBoundingBox().getMaxX(), 
		//	plat.platform_sprite->getBoundingBox().getMinY(),
		//	plat.platform_sprite->getBoundingBox().getMaxY());
		//CCLOG("Block Left: %f, Right: %f, Top: %f, Bot: %f", block->getBoundingBox().getMinX(),
		//	block->getBoundingBox().getMaxX(),
		//	block->getBoundingBox().getMinY(),
		//	block->getBoundingBox().getMaxY());
		if (number == plat.getAnswer())
		{
			score++;
			ScoreBoard->setString(std::to_string(score));
			plat.switch_math_str();
			block->stopAction(block_act);
			repos_block();
		}
		else
		{
			auto LOSER = cocos2d::Label::createWithSystemFont("You lose!", "Arial", 48);
			LOSER->setPosition(middle);
			this->addChild(LOSER, 2);
			block->stopAction(block_act);
			direction_x *= 50;
		}
	}
	if ((direction_x == -1) && (plat.platform_sprite->getBoundingBox().getMinX() > 30))
		plat.platform_sprite->setPosition(plat.platform_sprite->getPosition().x + direction_x * 1, plat.platform_sprite->getPosition().y);
	if ((direction_x == 1) && (plat.platform_sprite->getBoundingBox().getMaxX() < 30 * width))
		plat.platform_sprite->setPosition(plat.platform_sprite->getPosition().x + direction_x * 1, plat.platform_sprite->getPosition().y);
	//CCLOG("PosX %f, width %f", plat.platform_sprite->getPositionX(),plat.platform_sprite->getContentSize().width * 1.5 * plat.getPlatformScale());
	//CCLOG("Right collider %f and posX %f", plat.platform_sprite->getPositionX() + (plat.platform_sprite->getContentSize().width * plat.getPlatformScale() / 2, plat.platform_sprite->getPositionX()));
}

void World::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		direction_x--; // Если нажали влево и нет коллизий, то двигаемся влево по Х 
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		direction_x++; // Если нажали вправо, то двигаемся вправо по Х
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		auto MM = main_menu::createScene();
		Director::getInstance()->replaceScene(MM);
	}
}
void World::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) // Если одна из этих кнопок была отпущена, то перестаем двигаться
	{
		direction_x++;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) // Если одна из этих кнопок была отпущена, то перестаем двигаться
	{
		direction_x--;
	}
}
void World::onMouseMove(cocos2d::Event *event)
{
	cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
	if (e->getCursorX() > plat.platform_sprite->getPositionX())
		direction_x = 1;
	if (e->getCursorX() < plat.platform_sprite->getPositionX())
		direction_x = -1;
}
void World::repos_block()
{
	block->setPosition(Vec2(60 + rand() % (30 * (width - 1) - 30), 30 * height));
	number = plat.getAnswer() + (-2 + rand() % 5);// Генерируем числа от -2 до 2 и прибавляем к ответу
	block_l->setString(std::to_string(number));
	block_act = MoveBy::create(5, Vec2(0, -500));
	block->runAction(block_act);
}