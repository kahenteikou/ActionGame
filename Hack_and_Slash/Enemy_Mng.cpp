#include "Enemy_Mng.hpp"


//コンストラクタ
Enemy_Mng::Enemy_Mng()
{
	enemy = std::make_shared<std::vector<Enemy>>();	//ベクター変数

	//スプライトをロード
	Handle = LoadGraph("Assets/Enemy.png");					//エネミー
	Bullet_Handle = LoadGraph("Assets/Enemy_Bullet.png");	//バレット




	enemy->push_back(Enemy(Handle,Bullet_Handle));	//追加
}


//エネミーを返す
std::shared_ptr<std::vector<Enemy>> Enemy_Mng::getEnemy()
{
	return enemy;
}

//プレイヤーとの当たり判定
void Enemy_Mng::ColPlayer(std::shared_ptr<Player> player)
{
	for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
	{
		//交差判定
		if (Box_Collision::Intersect(itr->mCol, player->mCol) == true)
		{
			//player->FixPos(itr->mCol.getPosition());
		}
	}
}

//バレットとの当たり判定
void Enemy_Mng::ColBullet(std::shared_ptr<std::vector<Bullet>> bullet)
{
	for (std::vector<Bullet>::iterator it = bullet->begin(); it != bullet->end(); it++)
	{
		for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end();)
		{
			Enemy e = *itr;

			//交差
			if (Box_Collision::Intersect(e.mCol, it->mCol) == true)
			{
				it->mIsEnemyHit = true;		//エネミーとバレットがヒット
				itr = enemy->erase(itr);	//敵を削除
			}
			else {
				itr++;
			}
		}
	}
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
