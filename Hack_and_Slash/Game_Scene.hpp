#ifndef ___GAME_SCENE_HPP_
#define ___GAME_SCENE_HPP_

#include "Scene_base.hpp"
#include "Player.hpp"
#include "Stage.hpp"
#include "Shop.hpp"
//#include "Entry.hpp"

#include <iostream>


//前方宣言
class Player;
class Stage;
class Shop;
class Entry;
enum class Scene_Type;
//class Scene_base;
/*####################################################
* メインゲーム　シーン
*
* 説明
* メインのゲーム画面
######################################################*/
class Game_Scene : public Scene_base
{
public:
	Game_Scene(Scene_Type t,Entry* e);	//コンストラクタ
	~Game_Scene();						//デストラクタ

	void Update();	//更新
	void Draw();	//描画


private:

	std::shared_ptr<Player> player;	//プレイヤー
	std::shared_ptr<Stage> stage;	//ステージ
	std::shared_ptr<Shop> shop;	//ショップ
	
	bool flag;	//ショップかどうかのフラグ
	Entry* Owner;

};

#endif
