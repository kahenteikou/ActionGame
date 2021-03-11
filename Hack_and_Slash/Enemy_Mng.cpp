#include "Enemy_Mng.hpp"
#include "Player.hpp"
#include "MapChip.hpp"


//コンストラクタ
Enemy_Mng::Enemy_Mng(int Enemy_Handle, int Enemy_Bullet_Hanlde, int Stage_HitEffect_Handle[3], int Player_HitEffect_Handle[3])
{
	enemy = std::make_shared<std::vector<Enemy>>();	//ベクター変数
	enemy->clear();
	newStage = true;	//新しいステージになるかどうか？

	mEnemy_sprite = Enemy_Handle;
	mEnemy_Bullet_sprite = Enemy_Bullet_Hanlde;

	mStage_HitEffect_sprite[0] = Stage_HitEffect_Handle[0];
	mStage_HitEffect_sprite[1] = Stage_HitEffect_Handle[1];
	mStage_HitEffect_sprite[2] = Stage_HitEffect_Handle[2];

	mPlayer_HitEffect_sprite[0] = Player_HitEffect_Handle[0];
	mPlayer_HitEffect_sprite[1] = Player_HitEffect_Handle[1];
	mPlayer_HitEffect_sprite[2] = Player_HitEffect_Handle[2];
}


//エネミーを返す
std::shared_ptr<std::vector<Enemy>> Enemy_Mng::getEnemy()
{
	return enemy;
}



//プレイヤーとバレットとの当たり判定
void Enemy_Mng::ColPlayer_Bullet(std::shared_ptr<Player> player)
{
	printf("あああ\n");

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
				if (itr == enemy->end())
				{
					break;
				}
				b->mIsEnemyHit = true;				//ヒットエフェクトを再生
				//b->setPosition(itr->getPosition());	//座標を修正
			}	
		}	

		if (itr != enemy->end())
		{
			itr++;
		}

	}

	printf("いいいい");

}


//現在のエネミーの数を得る
bool Enemy_Mng::getEnemyEmpty()
{
//	std::shared_ptr<std::vector<Enemy>> getEnemy();					//エネミー情報

	return enemy->empty();

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

		newStage = false;
	}
}




//更新
void Enemy_Mng::Update()
{

	//printf("Size: %d\n",getEnemyNum());



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

