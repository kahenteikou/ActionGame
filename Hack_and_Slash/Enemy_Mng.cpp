#include "Enemy_Mng.hpp"


//コンストラクタ
Enemy_Mng::Enemy_Mng(int Enemy_Handle, int Enemy_Bullet_Hanlde, int Stage_HitEffect_Handle[3], int Player_HitEffect_Handle[3])
{
	enemy = std::make_shared<std::vector<Enemy>>();	//ベクター変数


	mEnemy_sprite = Enemy_Handle;
	mEnemy_Bullet_sprite = Enemy_Bullet_Hanlde;

	mStage_HitEffect_sprite[0] = Stage_HitEffect_Handle[0];
	mStage_HitEffect_sprite[1] = Stage_HitEffect_Handle[1];
	mStage_HitEffect_sprite[2] = Stage_HitEffect_Handle[2];

	mPlayer_HitEffect_sprite[0] = Player_HitEffect_Handle[0];
	mPlayer_HitEffect_sprite[1] = Player_HitEffect_Handle[1];
	mPlayer_HitEffect_sprite[2] = Player_HitEffect_Handle[2];




	enemy->push_back(Enemy(mEnemy_sprite, mEnemy_Bullet_sprite, mStage_HitEffect_sprite, mPlayer_HitEffect_sprite));	//追加
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
