#include "Enemy.hpp"


//コンストラクタ
Enemy::Enemy(int handle, int Bullet_handle) : Actor(nullptr)
{
	//スプライト
	mSprite = handle;					//エネミーハンドル
	mBullet_Sprite = Bullet_handle;		//バレットハンドル

	Rand_Action = GetRand(3);		//乱数
	Prev_Rand_Action = Rand_Action;	//前の乱数
	MovePixel = 0;					//移動量

	// 初期座標
	mPosition.x = SCREEN_WIDTH / 2;
	mPosition.y = SCREEN_HEIGHT / 2 - CELL * 4;

	mSpeed = 10; //スピード

	//当たり判定
	mCol.setStageObjectType(StageObjectType::Enemy);


	bullet = std::make_shared<std::vector<Bullet>>();

}

//更新
void Enemy::Update()
{
	
	//当たり判定
	glm::ivec2 pos = mPosition;
	pos.y += -(CELL / 2);
	pos.x += -(CELL / 2);
	mCol.setPosition(pos);
	mCol.setSize(glm::ivec2(CELL - 1, CELL - 1));

	Rand_Attack = GetRand(5);

	//方向
	if (Rand_Action == 0)
	{
		mVector = VECTOR_UP;
	}
	else if (Rand_Action == 1)
	{
		mVector = VECTOR_RIGHT;
	}
	else if (Rand_Action == 2)
	{
		mVector = VECTOR_DOWN;
	}
	else if (Rand_Action == 3)
	{
		mVector = VECTOR_LEFT;
	}
	
	//攻撃
	if (Rand_Attack == 1)
	{
	//	bullet->push_back(Bullet(mPosition,mVector,mBullet_sprite,mEffect_sprite));
	}




	MovePixel += mSpeed;	//移動量に加算
	if (MovePixel > CELL * 2)
	{
		setMove_Rand();
		MovePixel = 0;	//移動量をリセット
	}



	//移動
	mPosition.x += mVector.x * mSpeed;
	mPosition.y += mVector.y * mSpeed;


}

//移動乱数を再設定
void Enemy::setMove_Rand()
{
	//違う乱数を引くまで無限ループ
	while (true) {
		Rand_Action = GetRand(3);

		//同じ乱数を引いてない時
		if (Prev_Rand_Action != Rand_Action) {
			Prev_Rand_Action = Rand_Action;

			break;
		}
	}

}

//移動量をリセット
void Enemy::setMovePixel()
{
	MovePixel = 0;
}


//座標を修正
void Enemy::FixPos(glm::ivec2 pos)
{
	
	if (mVector == VECTOR_UP)
	{
		mPosition.y = pos.y + CELL + CELL / 2;
	}
	else if (mVector == VECTOR_DOWN)
	{
		mPosition.y = pos.y - (CELL / 2);
	}
	else if (mVector == VECTOR_LEFT)
	{
		mPosition.x = pos.x + (CELL + CELL / 2);
	}
	else if (mVector == VECTOR_RIGHT)
	{
		mPosition.x = pos.x - (CELL / 2);
	}

}

//描画
void Enemy::Draw()
{
	DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mSprite, true, false);

}


//デストラクタ
Enemy::~Enemy()
{

}
