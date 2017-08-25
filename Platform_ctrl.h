#pragma once
#ifndef Platform_ctrl_H
#define Platform_ctrl_H

#include "cocos2d.h"

class platform_ctrl : cocos2d::CCObject
{
private:
	int platform_scale; // Размер платформы	
	int Answer; // Ответ на логическое выражение
public:
	std::string mt_str;
	cocos2d::Sprite* platform_sprite; // спрайт для платформы
	cocos2d::Label* math_str; // Математическое выражение

	int getPlatformScale();
	int getAnswer();
	void switch_math_str(); // Меняем математическое выражение
	void set_platform_scale(int scale); // Установка размера платформы
	virtual bool init();
	
	CREATE_FUNC(platform_ctrl);
};
#endif // Platform_ctrl_H
