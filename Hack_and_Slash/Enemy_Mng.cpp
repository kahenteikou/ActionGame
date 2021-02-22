#include "Enemy_Mng.hpp"


//コンストラクタ
Enemy_Mng::Enemy_Mng()
{
	Handle = LoadGraph("Assets/Enemy.png");

	enemy = std::make_shared<std::vector<Enemy>>();

	enemy->push_back(Enemy(Handle));	//追加
}


//エネミーを返す
std::shared_ptr<std::vector<Enemy>> Enemy_Mng::getEnemy()
{
	return enemy;
}





//更新
void Enemy_Mng::Update()
{
	for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
	{
		itr->Update();
	}
}

//描画
void Enemy_Mng::Draw()
{
	for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
	{
		itr->Draw();
	}
}



//デストラクタ
Enemy_Mng::~Enemy_Mng()
{

}
