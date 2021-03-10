#include "Enemy_Mng.hpp"
#include "Player.hpp"
#include "MapChip.hpp"


//コンストラクタ
Enemy_Mng::Enemy_Mng(int Enemy_Handle, int Enemy_Bullet_Hanlde, int Stage_HitEffect_Handle[3], int Player_HitEffect_Handle[3])
{
	enemy = std::make_shared<std::vector<Enemy>>();	//ベクター変数
	newStage = true;	//新しいステージになるかどうか？

	mEnemy_sprite = Enemy_Handle;
	mEnemy_Bullet_sprite = Enemy_Bullet_Hanlde;

	mStage_HitEffect_sprite[0] = Stage_HitEffect_Handle[0];
	mStage_HitEffect_sprite[1] = Stage_HitEffect_Handle[1];
	mStage_HitEffect_sprite[2] = Stage_HitEffect_Handle[2];

	mPlayer_HitEffect_sprite[0] = Player_HitEffect_Handle[0];
	mPlayer_HitEffect_sprite[1] = Player_HitEffect_Handle[1];
	mPlayer_HitEffect_sprite[2] = Player_HitEffect_Handle[2];




	//enemy->push_back(Enemy(mEnemy_sprite, mEnemy_Bullet_sprite, mStage_HitEffect_sprite, mPlayer_HitEffect_sprite));	//追加
}


//エネミーを返す
std::shared_ptr<std::vector<Enemy>> Enemy_Mng::getEnemy()
{
	return enemy;
}



//プレイヤーとバレットとの当たり判定
void Enemy_Mng::ColPlayer_Bullet(std::shared_ptr<Player> player)
{
	bool b = false;

	//エネミー
	for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end();)
	{
		

		//バレット
		for (std::vector<Bullet>::iterator b = player->getBullet()->begin(); b != player->getBullet()->end(); b++)
		{

			//交差判定
			if (Box_Collision::Intersect(itr->mCol, b->mCol) == true)
			{
				itr = enemy->erase(itr);
	
				b->mIsEnemyHit = true;				//ヒットエフェクトを再生
				//b->setPosition(itr->getPosition());	//座標を修正
			}	
		}	

		if (itr != enemy->end())
		{
			itr++;
		}
	}




}


//現在のエネミーの数を得る
int Enemy_Mng::getEnemyNum()
{
	//printf("enemy->size: %d\n", (int)enemy->size());
	return (int)enemy->size();
	
	//return (int)enemy->size();
}

//エネミーを出現させる
void Enemy_Mng::setEnemy(std::shared_ptr<Stage> stage)
{
	



	//新しいステージかどうか？
	if (newStage == true)
	{
		int x, y;
		x = y = 0;

			enemy->push_back(Enemy(glm::ivec2(0,0),mEnemy_sprite, mEnemy_Bullet_sprite, mStage_HitEffect_sprite, mPlayer_HitEffect_sprite));	//追加


		/*
		for (std::vector<std::vector<byte>>::iterator itr = stage->begin(); itr != stage->end(); itr++)
		{
			for (std::vector<byte>::iterator it = itr->begin(); it != itr->end(); it++)
			{
				if (*it == 0x00)
				{
					//出現確率
					if (GetRand(2000 ) == 1) {
					//	enemy->push_back(Enemy(glm::ivec2(x * CELL,y * CELL),mEnemy_sprite, mEnemy_Bullet_sprite, mStage_HitEffect_sprite, mPlayer_HitEffect_sprite));	//追加
					}
				}
				x++;
			}
			y++;
		}
		*/
		newStage = false;
	}


	//printf("size: %zd\n",enemy->size());
}




//更新
void Enemy_Mng::Update()
{
	if (getEnemyNum() == 0)
	{
		newStage = true;
	}

	//printf("enemey->size(): %d\n",enemy->size());


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

