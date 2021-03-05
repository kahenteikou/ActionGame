#include "Game_Scene.hpp"

//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;	//Entry クラス


	// #####　スプライトをロード #####

	int Player_Handle = Owner->LoadSprite("Assets/Player/Player_0.png");	//プレイヤー
	int Enemy_Handle = Owner->LoadSprite("Assets/Enemy.png");				//エネミー		

	int Player_Bullet_Handle = Owner->LoadSprite("Assets/Player_Bullet.png");	//プレイヤーのバレット
	int Enemy_Bullet_Handle = Owner->LoadSprite("Assets/Enemy_Bullet.png");		//エネミーのバレット

	int Block_Handle = Owner->LoadSprite("Assets/Block.png");	//ブロック	
	int Brick_Handle = Owner->LoadSprite("Assets/Brick.png");	//レンガ
	int Shop_Handle = Owner->LoadSprite("Assets/Shop.png");		//ショップ
	


	//ヒットエフェクト
	int Enemy_HitEffect_Handle[3];	//エネミー
	int Stage_HitEffect_Handle[3];	//ステージ
	int Player_HitEffect_Handle[3];	//プレイヤー

	int a = LoadDivGraph("Assets/Enemy_Explosion.png", 3, 3, 1, CELL, CELL, Enemy_HitEffect_Handle);	//エネミー
	

	LoadDivGraph("Assets/Stage_Explosion.png", 3, 3, 1, CELL, CELL, Stage_HitEffect_Handle);	//ステージ
	

	LoadDivGraph("Assets/Player_Explosion.png", 3, 3, 1, CELL, CELL,Player_HitEffect_Handle);	//プレイヤー
	


	flag = false;	//ショップ中かどうか？
	player = std::make_shared<Player>(Owner,Player_Handle, Player_Bullet_Handle,Enemy_HitEffect_Handle, Stage_HitEffect_Handle);	//プレイヤー
	stage = std::make_shared<Stage>(Owner,Block_Handle, Brick_Handle, Shop_Handle);													//ステージ
	shop = std::make_shared<Shop>(Owner);																							//ショップメニュー
	enemy_mng = std::make_shared<Enemy_Mng>(Enemy_Handle,Enemy_Bullet_Handle,Stage_HitEffect_Handle, Player_HitEffect_Handle);		//エネミー管理



}

//更新
void Game_Scene::Update()
{
	//バトル
	if (player->getIsMenu() == false)
	{	



		enemy_mng->Update();												//エネミー更新
		stage->Update();													//ステージ更新
		player->Update();													//プレイヤー更新

		stage->Scroll(player, enemy_mng->getEnemy(), player->getBullet());	//画面スクロール


		stage->ColEnemy(enemy_mng->getEnemy());								//エネミーとの当たり判定
		stage->ColEnemy_Bullet(enemy_mng->getEnemy());						//エネミーのバレットとのマップのとの当たり判定
		

		stage->ColPlayer(player);											//プレイヤーと当たり判定
		stage->ColPlayer_Bullet(player->getBullet());						//プレイヤーのバレットの当たり判定

		player->ColEnemy_Bullet(enemy_mng->getEnemy());

		enemy_mng->ColPlayer(player);										//エネミーとプレイヤーとの当たり判定
		enemy_mng->ColBullet(player->getBullet());							//エネミーとプレイヤーのバレットの当たり判定




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
	enemy_mng->Draw();	//エネミー描画

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
