#include "Enemy.hpp"


//コンストラクタ
Enemy::Enemy(glm::ivec2 pos ,int Enemy_sprite, int Enemy_Bullet_sprite, int Stage_HitEffect_sprite[3], int Player_HitEffect_sprite[3]) : Actor(nullptr)
{
	mPosition = pos;	//初期座標

	mEnemy_sprite = Enemy_sprite;	//エネミー
	mEnemy_Bullet_sprite = Enemy_Bullet_sprite;	//バレット

	//ステージ　ヒットエフェクト
	mStage_HitEffect_sprite[0] = Stage_HitEffect_sprite[0];
	mStage_HitEffect_sprite[1] = Stage_HitEffect_sprite[1];
	mStage_HitEffect_sprite[2] = Stage_HitEffect_sprite[2];
	
	//プレイヤー　ヒットフェクト
	mPlayer_HitEffect_sprite[0] = Player_HitEffect_sprite[0];
	mPlayer_HitEffect_sprite[1] = Player_HitEffect_sprite[1];
	mPlayer_HitEffect_sprite[2] = Player_HitEffect_sprite[2];


	islife = true;	//生きているかどうか？


//	Rand_Action = GetRand(3);		//乱数
	Rand_Action = 0;		//乱数
	//Rand_Action = 3; //GetRand(3);//乱数

	//Prev_Rand_Action = Rand_Action;	//前の乱数
	MovePixel = 0;					//移動した量

	
//	mSpeed = 10; //スピード
//	mSpeed = 2; //スピード

	//当たり判定
	mCol.setStageObjectType(StageObjectType::Enemy);


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
	islife = false;
}

//破壊されたかどうか？		
bool Enemy::getIsDestroy()
{
	return islife;
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
	
	//Rand_Attack = GetRand(50); //攻撃頻度
	Rand_Attack = GetRand(10); //攻撃頻度

	//攻撃
	if (Rand_Attack == 1)
	{
	//	printf("エネミー攻撃\n");
	//	bullet->push_back(Bullet(mPosition,mVector,mEnemy_Bullet_sprite,mStage_HitEffect_sprite, mPlayer_HitEffect_sprite));
	}



	/*
	//MovePixel += mSpeed;	//移動量に加算
	if (MovePixel > CELL * 2)
	{
		setMove_Rand();
		MovePixel = 0;	//移動量をリセット
	}
	*/


	//移動
//	mPosition.x += mVector.x * mSpeed;
//	mPosition.y += mVector.y * mSpeed;


	//バレット削除
	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end();)
	{
		if (itr->mIsDelete == true)
		{
			itr = bullet->erase(itr);
		}
		else 
		{
			itr->Update();
			itr++;
		}
	}
}

//移動乱数を再設定
void Enemy::setMove_Rand()
{
	Rand_Action = 0;

	/*
	//違う乱数を引くまで無限ループ
	while (true) {
		Rand_Action = GetRand(3);

		//同じ乱数を引いてない時
		if (Prev_Rand_Action != Rand_Action) {
			Prev_Rand_Action = Rand_Action;

			break;
		}
	}
	*/
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
	DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mEnemy_sprite, true, false);

	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
	{
		itr->Draw();
	}


}


//デストラクタ
Enemy::~Enemy()
{

}
