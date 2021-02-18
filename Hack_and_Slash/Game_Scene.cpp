#include "Game_Scene.hpp"

//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t) : Scene_base(t)
{
	flag = false;
	player = std::make_shared<Player>();	//プレイヤー
	stage = std::make_shared<Stage>();		//ステージ
	shop = std::make_shared<Shop>();		//ショップメニュー
}

//更新
void Game_Scene::Update()
{
	//バトル
	if (player->getIsMenu() == false)
	{
		player->Update();			//プレイヤー更新
		stage->Update();			//ステージ更新
		stage->ColPlayer(*player);	//プレイヤーとマップとの当たり判定			
	}
	else
	{
		//ショップ画面
		if (shop->getState() == true)
		{
			shop->Update(*player);
		}
		else {
			player->setIsMenu(false);
			shop = std::make_shared <Shop>();
		}
	}



}

//描画
void Game_Scene::Draw()
{

	player->Draw();	//プレイヤー描画
	stage->Draw();	//ステージ描画

	//ショップ画面
	if (player->getIsMenu() == true)
	{
		shop->Draw();
	}

	

}

//デストラクタ
Game_Scene::~Game_Scene()
{

}
