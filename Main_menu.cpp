#include "Main_menu.h"
#include "World.h"
#include <fstream>
#include <string>
USING_NS_CC;

Scene* main_menu::createScene()
{
	return main_menu::create();
}

bool main_menu::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int tmp;
	// Считываем настройки
	std::ifstream settings_file("Settings.ini");
	settings_file >> width >> height >> pl_scale >> tmp;
	if (tmp == 0 || tmp == 1)
	{
		ctrlr = tmp;
		if(ctrlr)
			Controller_set = "Keyboard";
		else
			Controller_set = "Mouse";
	}
	else// Если кто-то подкорректировал настройки, то дефолтный контроллер - клавиатура
	{
		ctrlr = true;
		Controller_set = "Keyboard";
	}
	//CCLOG("width %d height %d Platform scale %d", width, height, pl_scale);
	// Создаем поля меню(новая игра, настройки, список лидеров, выход)
	auto menu_NewGame_item = MenuItemFont::create("New Game", CC_CALLBACK_1(main_menu::New_game, this));
	auto menu_Settings_item = MenuItemFont::create("Settings", CC_CALLBACK_1(main_menu::Settings, this));
	auto menu_Leaderboard_item = MenuItemFont::create("Leaderboard", CC_CALLBACK_1(main_menu::Leaderboard, this));
	auto menu_Exit_item = MenuItemFont::create("Exit", CC_CALLBACK_1(main_menu::Exit, this));

	// Создаем поля для пункта настройки
	set_layer = Layer::create();
	set_layer->setPosition(0,0);
	this->addChild(set_layer);
	menu_switch_controller = MenuItemFont::create(Controller_set, CC_CALLBACK_1(main_menu::switch_ctrl, this)); // Кнопка, для изменения контроллера(мышь / клавиатура)
	menu_add_w_button = MenuItemImage::create("add.png", "add_selected.png", CC_CALLBACK_1(main_menu::add_w, this)); // Кнопка, для увеличения длинны стакана
	menu_add_h_button = MenuItemImage::create("add.png", "add_selected.png", CC_CALLBACK_1(main_menu::add_h, this)); // Кнопка, для увеличения высоты стакана
	menu_add_s_button = MenuItemImage::create("add.png", "add_selected.png", CC_CALLBACK_1(main_menu::add_s, this)); // кнопка, для увеличения размера игрока
	menu_remove_w_button = MenuItemImage::create("remove.png", "remove_selected.png", CC_CALLBACK_1(main_menu::remove_w, this)); // кнопка, для уменьшения длинны стакана
	menu_remove_h_button = MenuItemImage::create("remove.png", "remove_selected.png", CC_CALLBACK_1(main_menu::remove_h, this)); // кнопка, для уменьшения высоты стакана
	menu_remove_s_button = MenuItemImage::create("remove.png", "remove_selected.png", CC_CALLBACK_1(main_menu::remove_s, this)); // кнопка, для уменьшения размера игрока

	menu_add_w_button->setPosition(origin.x + visibleSize.width - menu_add_w_button->getContentSize().width * 1.5, (visibleSize.height / 10) * 8 + 1);
	menu_add_h_button->setPosition(origin.x + visibleSize.width - menu_add_h_button->getContentSize().width * 1.5, (visibleSize.height / 10) * 7 + 1);
	menu_add_s_button->setPosition(origin.x + visibleSize.width - menu_add_s_button->getContentSize().width * 1.5, (visibleSize.height / 10) * 6 + 1);
	menu_remove_w_button->setPosition(origin.x + visibleSize.width - menu_remove_w_button->getContentSize().width * 2.5, (visibleSize.height / 10) * 8);
	menu_remove_h_button->setPosition(origin.x + visibleSize.width - menu_remove_h_button->getContentSize().width * 2.5, (visibleSize.height / 10) * 7);
	menu_remove_s_button->setPosition(origin.x + visibleSize.width - menu_remove_s_button->getContentSize().width * 2.5, (visibleSize.height / 10) * 6 );
	menu_switch_controller->setPosition(origin.x + visibleSize.width - menu_remove_w_button->getContentSize().width * 2, (visibleSize.height / 10) * 9 + 1);

	auto wl = Label::createWithSystemFont("Width", "Arial", 36);
	wl->setAnchorPoint(Vec2(1, 0.5));
	wl->setPosition(origin.x + visibleSize.width - menu_add_w_button->getContentSize().width * 3, (visibleSize.height / 10) * 8 + 1);
	set_layer->addChild(wl);
	auto hl = Label::createWithSystemFont("Height", "Arial", 36);
	hl->setAnchorPoint(Vec2(1, 0.5));
	hl->setPosition(origin.x + visibleSize.width - menu_add_h_button->getContentSize().width * 3, (visibleSize.height / 10) * 7 + 1);
	set_layer->addChild(hl);
	auto sc_l = Label::createWithSystemFont("Platform size", "Arial", 36);
	sc_l->setAnchorPoint(Vec2(1, 0.5));
	sc_l->setPosition(origin.x + visibleSize.width - menu_add_s_button->getContentSize().width * 3, (visibleSize.height / 10) * 6 + 1);
	set_layer->addChild(sc_l);

	width_l = Label::createWithSystemFont(std::to_string(width), "Arial", 36);
	width_l->setAnchorPoint(Vec2(0, 0.5));
	width_l->setPosition(origin.x + visibleSize.width - menu_add_w_button->getContentSize().width, (visibleSize.height / 10) * 8 + 1);
	set_layer->addChild(width_l);
	height_l = Label::createWithSystemFont(std::to_string(height), "Arial", 36);
	height_l->setAnchorPoint(Vec2(0, 0.5));
	height_l->setPosition(origin.x + visibleSize.width - menu_add_w_button->getContentSize().width, (visibleSize.height / 10) * 7 + 1);
	set_layer->addChild(height_l);
	Pl_scale_l = Label::createWithSystemFont(std::to_string(pl_scale), "Arial", 36);
	Pl_scale_l->setAnchorPoint(Vec2(0, 0.5));
	Pl_scale_l->setPosition(origin.x + visibleSize.width - menu_add_w_button->getContentSize().width, (visibleSize.height / 10) * 6 + 1);
	set_layer->addChild(Pl_scale_l);
	
	auto Apply_item = MenuItemFont::create("Apply", CC_CALLBACK_1(main_menu::apply_ch, this));
	Apply_item->setAnchorPoint(Vec2(1, 0));
	Apply_item->setPosition(Vec2(visibleSize.width * 0.9 + 30, visibleSize.height / 2 - 30));

	auto *Set_menu = Menu::create(menu_add_w_button, menu_add_h_button, menu_add_s_button, menu_remove_w_button, menu_remove_h_button, menu_remove_s_button, menu_switch_controller, Apply_item, NULL);
	Set_menu->setPosition(0,0);
	set_layer->addChild(Set_menu);

	// Ставим эти поля в центр экрана по ширине
	menu_NewGame_item->setPosition(origin.x + 24, (visibleSize.height / 8) * 7 + 5);
	menu_NewGame_item->setAnchorPoint(cocos2d::Vec2(0, 0));
	menu_Settings_item->setPosition(origin.x + 24, (visibleSize.height / 8) * 6 + 5);
	menu_Settings_item->setAnchorPoint(cocos2d::Vec2(0, 0));
	menu_Leaderboard_item->setPosition(origin.x + 24, (visibleSize.height / 8) * 5 + 5);
	menu_Leaderboard_item->setAnchorPoint(cocos2d::Vec2(0, 0));
	menu_Exit_item->setPosition(origin.x + 24, (visibleSize.height / 8) * 4 + 5);
	menu_Exit_item->setAnchorPoint(cocos2d::Vec2(0, 0));

	// И добавляем на сцену
	auto *menu = Menu::create(menu_NewGame_item, menu_Settings_item, menu_Leaderboard_item, menu_Exit_item, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);
	set_layer->setVisible(false);
	settings_file.close();
	return true;
}

void main_menu::New_game(cocos2d::Ref *pSender) 
{
	auto World_scene = World::createScene();
	Director::getInstance()->replaceScene(World_scene);
}
void main_menu::Settings(cocos2d::Ref *pSender) 
{
	set_layer->setVisible(!set_layer->isVisible());
}
void main_menu::Leaderboard(cocos2d::Ref *pSender) 
{

}
void main_menu::Exit(cocos2d::Ref *pSender)
{
	Director::getInstance()->end();
}
void main_menu::add_w(Ref *pSender) 
{
	if ( width < 13)
		width++;
	width_l->setString(std::to_string(width));
}
void main_menu::add_h(Ref *pSender)
{
	if (height < 11)
		height++;
	height_l->setString(std::to_string(height));
}
void main_menu::add_s(Ref *pSender)
{
	if (pl_scale < 6)
		pl_scale++;
	Pl_scale_l->setString(std::to_string(pl_scale));
}
void main_menu::remove_w(Ref *pSender)
{
	if (width > 8)
		width--;
	width_l->setString(std::to_string(width));
}
void main_menu::remove_h(Ref *pSender)
{
	if (height > 6)
		height--;
	height_l->setString(std::to_string(height));
}
void main_menu::remove_s(Ref *pSender)
{
	if (pl_scale > 3)
		pl_scale--;
	Pl_scale_l->setString(std::to_string(pl_scale));

}
void main_menu::switch_ctrl(Ref *pSender)
{
	ctrlr = !ctrlr;
	if (ctrlr)
		Controller_set = "Keyboard";
	else
		Controller_set = "Mouse";
	menu_switch_controller->setString(Controller_set);
}
void main_menu::apply_ch(Ref *pSender)
{
	std::ofstream apply_set("Settings.ini");
	apply_set << width  << std::endl << height << std::endl << pl_scale << std::endl << ctrlr;
	apply_set.close();
}