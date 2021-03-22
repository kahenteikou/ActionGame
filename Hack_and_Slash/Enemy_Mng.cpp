#include "Enemy_Mng.hpp"
#include "Player.hpp"
#include "MapChip.hpp"


//コンストラクタ
Enemy_Mng::Enemy_Mng(int Enemy_Handle, int Enemy_Bullet_Hanlde, int Stage_HitEffect_Handle[3], int Player_HitEffect_Handle[3])
{
	enemy = std::make_shared<std::vector<Enemy>>();	//ベクター変数
	enemy->clear();
	newStage = true;	//新しいステージになるかどうか？

	enemySprite = Enemy_Handle;
	enemyBulletSprite = Enemy_Bullet_Hanlde;

	stageHitEffectSprite[0] = Stage_HitEffect_Handle[0];
	stageHitEffectSprite[1] = Stage_HitEffect_Handle[1];
	stageHitEffectSprite[2] = Stage_HitEffect_Handle[2];

	playerHitEffectSprite[0] = Player_HitEffect_Handle[0];
	playerHitEffectSprite[1] = Player_HitEffect_Handle[1];
	playerHitEffectSprite[2] = Player_HitEffect_Handle[2];
}


//エネミーを返す
std::shared_ptr<std::vector<Enemy>> Enemy_Mng::getEnemy()
{
	return enemy;
}



//プレイヤーとバレットとの当たり判定
void Enemy_Mng::ColPlayer_Bullet(std::shared_ptr<Player> player)
{


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
			enemy->push_back(Enemy(glm::vec2 (760,530),enemySprite, enemyBulletSprite, stageHitEffectSprite,playerHitEffectSprite));	//追加

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

