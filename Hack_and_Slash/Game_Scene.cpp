#include "Game_Scene.hpp"

//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;


	flag = false;	//ショップ中かどうか？
	player = std::make_shared<Player>(e);	//プレイヤー
	stage = std::make_shared<Stage>(e);		//ステージ
	shop = std::make_shared<Shop>(e);		//ショップメニュー
}

//更新
void Game_Scene::Update()
{
	//バトル
	if (player->getIsMenu() == false)
	{
		stage->ScrollMap(*player);				//画面スクロール
		player->Update();						//プレイヤー更新
		stage->Update();						//ステージ更新
		stage->ColBullet(player->getBullet());	//バレットとマップとの当たり判定
		stage->ColPlayer(*player);				//プレイヤーとマップとの当たり判定

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
			shop = std::make_shared <Shop>(Owner);
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
