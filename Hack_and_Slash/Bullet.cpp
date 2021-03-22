#include "Bullet.hpp"

//コンストラクタ
Bullet::Bullet(glm::vec2 pos , glm::vec2 vec, int handle,int MapEffect_Handle[3], int EnemyEffect_Handle[3]) : Actor(nullptr,pos,vec),anim(2)
{
	//GetGraphSize(handle,&(int)size.x, &(int)size.y);	//スプライトの大きさ

	speed = 8;		//バレットの速度
	sprite = handle;	//スプライト
	
	//マップとヒットした時のエフェクト
	mapEffectSprite[0] = MapEffect_Handle[0];
	mapEffectSprite[1] = MapEffect_Handle[1];
	mapEffectSprite[2] = MapEffect_Handle[2];

	//エネミーとヒットした時のエフェクト
	enemyEffectSprite[0] = EnemyEffect_Handle[0];
	enemyEffectSprite[1] = EnemyEffect_Handle[1];
	enemyEffectSprite[2] = EnemyEffect_Handle[2];
	

	//判定関係を初期化
	isMapHIt = false;
	isEenemyHit = false;
	isDelete = false;
}



//座標を修正
void Bullet::FixPos(glm::vec2 pos)
{
	if (vector == VECTOR_UP)
	{
		position.y = pos.y + (CELL);
	}
	else if (vector == VECTOR_DOWN)
	{
		position.y = pos.y;
	}
	else if (vector == VECTOR_LEFT)
	{
		position.x = pos.x + (CELL);
	}
	else if (vector == VECTOR_RIGHT)
	{
		position.x = pos.x;		
	}
}




//更新
void Bullet::Update()
{
}

//描画
void Bullet::Draw()
{
	//バレットを移動
	
	if (isMapHIt == false && isEenemyHit == false) 
	{
		//描画向き
		if (vector == VECTOR_UP)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, sprite, true, false);
		}
		else if (vector == VECTOR_DOWN)
		{
			DrawRotaGraph(position.x, position.y, 1.0, PI, sprite, true, false);
		}
		else if (vector == VECTOR_LEFT)
		{
			DrawRotaGraph(position.x, position.y, 1.0, -(PI * 2) / 4, sprite, true, true);
		}
		else if (vector == VECTOR_RIGHT)
		{
			DrawRotaGraph(position.x, position.y, 1.0, (PI * 2) / 4, sprite, true, true);
		}

	}
	else if (isMapHIt == true) 
	{
		//マップ　ヒットエフェクト

		int num = 0;
		if (anim.getClip(num, BULLET_EFFECT_SPEED) == false) {
			DrawRotaGraph(position.x, position.y, 1.0, 0, mapEffectSprite[num], true, false);
		}
		else
		{
			isDelete = true;
		}
	}
	else if (isEenemyHit == true)
	{
		//エネミー　ヒットエフェクト

		int num = 0;
		if (anim.getClip(num, BULLET_EFFECT_SPEED) == false) {
			DrawRotaGraph(position.x, position.y, 1.0, 0, enemyEffectSprite[num], true, false);
		}
		else
		{
			isDelete = true;
		}
	}






}

//デストラクタ
Bullet::~Bullet()
{

}
