#include "Enemy.hpp"


//コンストラクタ
Enemy::Enemy(glm::ivec2 pos ,int Enemy_sprite, int Enemy_Bullet_sprite, int Stage_HitEffect_sprite[3], int Player_HitEffect_sprite[3]) : Actor(nullptr)
{
	position = pos;	//初期座標

	enemySprite = Enemy_sprite;	//エネミー
	enemy_Bullet_sprite = Enemy_Bullet_sprite;	//バレット

	//ステージ　ヒットエフェクト
	stageHitEffect_sprite[0] = Stage_HitEffect_sprite[0];
	stageHitEffect_sprite[1] = Stage_HitEffect_sprite[1];
	stageHitEffect_sprite[2] = Stage_HitEffect_sprite[2];
	
	//プレイヤー　ヒットフェクト
	playerHitEffect_sprite[0] = Player_HitEffect_sprite[0];
	playerHitEffect_sprite[1] = Player_HitEffect_sprite[1];
	playerHitEffect_sprite[2] = Player_HitEffect_sprite[2];


	isLefe = true;	//生きているかどうか？


	randMove = GetRand(3);		//乱数
	//randMove = 0;		//乱数
	//randMove = 3; //GetRand(3);//乱数

	//Prev_randMove = randMove;	//前の乱数
	moveValue = 0;					//移動した量

	
//	speed = 10; //スピード
	speed = 2; //スピード

	//当たり判定
	


	bullet = std::make_shared<std::vector<Bullet>>();

}

//バレットを取得
std::shared_ptr<std::vector<Bullet>> Enemy::getBullet()
{
	return bullet;
}

//破壊する。		
void Enemy::Destroy()
{
	isLefe = false;
}

//破壊されたかどうか？		
bool Enemy::getIsDestroy()
{
	return isLefe;
}


//更新
void Enemy::Update()
{
	
	randAttack = GetRand(50); //攻撃頻度

	//攻撃
	if (randAttack == 1)
	{
		//	printf("エネミー攻撃\n");
		bullet->push_back(Bullet(position, vector, enemy_Bullet_sprite, stageHitEffect_sprite,playerHitEffect_sprite));
	}

	//方向
	if (randMove == 0)
	{
		vector = VECTOR_UP;
	}
	else if (randMove == 1)
	{
		vector = VECTOR_RIGHT;
	}
	else if (randMove == 2)
	{
		vector = VECTOR_DOWN;
	}
	else if (randMove == 3)
	{
		vector = VECTOR_LEFT;
	}
	
	//randAttack = GetRand(50); //攻撃頻度

	


	//移動	
	moveValue += speed;	//移動量に加算
	if (moveValue > CELL * 2)
	{
		setMove_Rand();
		moveValue = 0;	//移動量をリセット
	}
	


	//移動
	position.x += vector.x * speed;
	position.y += vector.y * speed;


	





	
}

//移動乱数を再設定
void Enemy::setMove_Rand()
{
	randMove = GetRand(3);

	/*
	//違う乱数を引くまで無限ループ
	while (true) {
		randMove = GetRand(3);

		//同じ乱数を引いてない時
		if (Prev_randMove != randMove) {
			Prev_randMove = randMove;

			break;
		}
	}
	*/
}

//移動量をリセット
void Enemy::setMovePixel()
{
	moveValue = 0;
}


//座標を修正
void Enemy::FixPos(glm::ivec2 &pos)
{
	
	if (vector == VECTOR_UP)
	{
		position.y = pos.y + CELL + CELL / 2;
	}
	else if (vector == VECTOR_DOWN)
	{
		position.y = pos.y - (CELL / 2);
	}
	else if (vector == VECTOR_LEFT)
	{
		position.x = pos.x + (CELL + CELL / 2);
	}
	else if (vector == VECTOR_RIGHT)
	{
		position.x = pos.x - (CELL / 2);
	}

}

//描画
void Enemy::Draw()
{
	DrawRotaGraph(position.x, position.y, 1.0, 0, enemySprite, true, false);

	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
	{
		itr->Draw();
	}


}


//デストラクタ
Enemy::~Enemy()
{

}
