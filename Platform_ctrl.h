#pragma once
#ifndef Platform_ctrl_H
#define Platform_ctrl_H

#include "cocos2d.h"

class platform_ctrl : cocos2d::CCObject
{
private:
	int platform_scale; // ������ ���������	
	int Answer; // ����� �� ���������� ���������
public:
	std::string mt_str;
	cocos2d::Sprite* platform_sprite; // ������ ��� ���������
	cocos2d::Label* math_str; // �������������� ���������

	int getPlatformScale();
	int getAnswer();
	void switch_math_str(); // ������ �������������� ���������
	void set_platform_scale(int scale); // ��������� ������� ���������
	virtual bool init();
	
	CREATE_FUNC(platform_ctrl);
};
#endif // Platform_ctrl_H
