#include "Game_Scene.hpp"

//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t) : Scene_base(t)
{
	player = std::make_shared<Player>();
	stage = std::make_shared<Stage>();
}

//更新
void Game_Scene::Update()
{
	player->Update();
	stage->Update();

	stage->ColPlayer(*player);	//プレイヤーとマップとの当たり判定




}

//描画
void Game_Scene::Draw()
{
	player->Draw();
	stage->Draw();
}

//デストラクタ
Game_Scene::~Game_Scene()
{

}
