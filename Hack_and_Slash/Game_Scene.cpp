#include "Game_Scene.hpp"

//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;	//Entry クラス


	// #####　スプライトをロード #####

//	int Player_Handle = Owner->LoadSprite("Assets/Player/Player_0.png");	//プレイヤー

	int Player_Handle[8];
	LoadDivGraph("Assets/Sprite/Player.png", 8, 8, 1, CELL, CELL, Player_Handle);	//プレイヤー

	int Enemy_Handle = Owner->LoadSprite("Assets/Sprite/Enemy.png");					//エネミー		

	int Player_Bullet_Handle = Owner->LoadSprite("Assets/Sprite/Player_Bullet.png");	//プレイヤーのバレット
	int Enemy_Bullet_Handle = Owner->LoadSprite("Assets/Sprite/Enemy_Bullet.png");		//エネミーのバレット

	int Block_Handle = Owner->LoadSprite("Assets/Sprite/Block.png");	//ブロック	
	int Brick_Handle = Owner->LoadSprite("Assets/Sprite/Brick.png");	//レンガ
	int Shop_Handle = Owner->LoadSprite("Assets/Sprite/Shop.png");		//ショップ
	
	//ヒットエフェクト
	int Enemy_HitEffect_Handle[3];	//エネミー
	int Stage_HitEffect_Handle[3];	//ステージ
	int Player_HitEffect_Handle[3];	//プレイヤー
	LoadDivGraph("Assets/Sprite/Enemy_Explosion.png", 3, 3, 1, CELL, CELL, Enemy_HitEffect_Handle);	//エネミー
	LoadDivGraph("Assets/Sprite/Stage_Explosion.png", 3, 3, 1, CELL, CELL, Stage_HitEffect_Handle);	//ステージ
	LoadDivGraph("Assets/Sprite/Player_Explosion.png", 3, 3, 1, CELL, CELL,Player_HitEffect_Handle);	//プレイヤー
	

	player = std::make_shared<Player>(Owner,Player_Handle, Player_Bullet_Handle,Enemy_HitEffect_Handle, Stage_HitEffect_Handle);	//プレイヤー
	stage = std::make_shared<Stage>(Owner,Block_Handle, Brick_Handle, Shop_Handle);													//ステージ
	shop = std::make_shared<Shop>(Owner);																							//ショップメニュー
	enemy_mng = std::make_shared<Enemy_Mng>(Enemy_Handle,Enemy_Bullet_Handle,Stage_HitEffect_Handle, Player_HitEffect_Handle);		//エネミー管理

}

//更新
void Game_Scene::Update()
{

	
//	enemy_mng->Update();	//エネミー更新
	stage->Update();		//ステージ更新
	player->Update();		//プレイヤー更新






	//　#####　当たり判定 #####
	
	//エネミーとステージ


	//stage->ColEnemy(enemy_mng);			//　5

	int n = GetNowCount();
//
	//stage->ColEnemy_Bullet(enemy_mng);	//0


	//プレイヤーとステージ
//	stage->ColPlayer_Bullet(player);	// 26
	// 
	stage->ColPlayer(player);			// 16

	//printf("time: %d\n", (GetNowCount() - n));


	//プレイヤーとエネミー
//	player->ColEnemy_Bullet(enemy_mng);		//



//	enemy_mng->ColPlayer_Bullet(player);	//

	//　##### #####	


//	stage->Scroll(player, enemy_mng);	//画面スクロール	//14


}

//描画
void Game_Scene::Draw()
{
	stage->Draw();		//ステージ描画
	player->Draw();		//プレイヤー描画
	enemy_mng->Draw();	//エネミー描画
}

//デストラクタ
Game_Scene::~Game_Scene()
{

}
