#pragma once
#ifndef World_H
#define World_H

#include "cocos2d.h"
#include "Platform_ctrl.h"

class World : public cocos2d::Scene
{
private:
	int scale, width, height, number, score;
	bool ctrlr; // Контроллер
	cocos2d::Sprite* block;
	cocos2d::Label* block_l;
	cocos2d::Label* ScoreBoard;
	cocos2d::MoveBy* block_act;
	cocos2d::Vec2 middle;
public:
	platform_ctrl plat; // Перед вызовом функции init() необходимо вызвать функцию set_platform_scale()
	int direction_x; // Направление движения
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onMouseMove(cocos2d::Event *event);
	void repos_block();
	//virtual void update(float delta_time);
	CREATE_FUNC(World);
};
#endif // World_H
