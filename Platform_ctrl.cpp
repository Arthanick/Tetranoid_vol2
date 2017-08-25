#include "Platform_ctrl.h"
#include <string.h>

USING_NS_CC;

bool platform_ctrl::init()
{
	srand(time(NULL));
	if (platform_scale < 3 || platform_scale > 6)
		return false;
	platform_sprite = Sprite::create("platform.png");
	platform_sprite->setAnchorPoint(cocos2d::Vec2(0.5, 1)); // Цепляем спрайт за центр и верхнюю точку
	math_str = Label::createWithSystemFont(" ", "Arial", 18); // Устанавливаем выражение
	math_str->setColor(Color3B::BLACK);
	math_str->setAnchorPoint(cocos2d::Vec2(0.5, 0.5)); // Цепляем текст за центр 
	math_str->setPosition(platform_sprite->getContentSize().width / 2, platform_sprite->getContentSize().height / 2); // И ставим в центр спрайта
	platform_sprite->addChild(math_str);
	platform_sprite->setScaleX(platform_sprite->getScaleX() * platform_scale); // Умножаем стандартный размер платформы по Х на размер платформы из настроек
	math_str->setScaleX(math_str->getScaleX() / platform_scale);
	// Высчитываем размер коллайдера
	switch_math_str();
	//math_str->setScale(0.1f);
	return true;
}

void platform_ctrl::set_platform_scale(int scale)
{
	platform_scale = scale;
}

void platform_ctrl::switch_math_str()
{
	int b = rand() % 10;
	int a = rand() % 10 - 10;
	int queue_a_b = rand() % 3;
	Answer = a + b;
	switch (queue_a_b)
	{
	case 0:
		mt_str =  std::to_string(a) + " + " + std::to_string(b) + "= x";;
		break;
	case 1:
		mt_str = "x - " + std::to_string(b) + " = " + std::to_string(a);
		break;
	case 2:
		mt_str = std::to_string(a) + " - x = -" + std::to_string(b);
		break;
	}
	math_str->setString(mt_str);
}

int platform_ctrl::getPlatformScale()
{
	return platform_scale;
}
int platform_ctrl::getAnswer()
{
	return Answer;
}