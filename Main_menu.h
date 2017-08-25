#pragma once
#ifndef Main_menu_scene_H
#define Main_menu_scene_H

#include "cocos2d.h"

class main_menu : public cocos2d::Scene
{
private:
	cocos2d::Layer* set_layer;
	cocos2d::MenuItemFont* menu_switch_controller;
	cocos2d::MenuItemImage* menu_add_w_button;
	cocos2d::MenuItemImage* menu_add_h_button;
	cocos2d::MenuItemImage* menu_add_s_button;
	cocos2d::MenuItemImage* menu_remove_w_button;
	cocos2d::MenuItemImage* menu_remove_h_button;
	cocos2d::MenuItemImage* menu_remove_s_button;
	cocos2d::Label* width_l;
	cocos2d::Label* height_l;
	cocos2d::Label* Pl_scale_l;
	cocos2d::Menu* Settings_m;
	std::string Controller_set;
	int width;
	int height;
	int pl_scale;
	bool ctrlr;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void New_game(Ref *pSender);
	void Settings(Ref *pSender);
	void Leaderboard(Ref *pSender);
	void Exit(Ref *pSender);
	void add_w(Ref *pSender);
	void add_h(Ref *pSender);
	void add_s(Ref *pSender);
	void remove_w(Ref *pSender);
	void remove_h(Ref *pSender);
	void remove_s(Ref *pSender);
	void switch_ctrl(Ref *pSender);
	void apply_ch(Ref *pSender);
	CREATE_FUNC(main_menu);
};
#endif // Main_menu_scene_H
