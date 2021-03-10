#include "Player.hpp"
#include "Enemy_Mng.hpp"

#include <iostream>
#include <vector>

#include "Entry.hpp"
#include "Entry.hpp"
#include "Input.hpp"
#include "Collision.hpp"






//コンストラクタ
Player::Player(Entry* e, int Player_Handle[8], int Player_Bullet_Handle, int Enemy_HitEffect_Handle[3], int Stage_HitEffect_Handle[3]) : Actor(e),anim(1)
{

	//プレイヤー自機のスプライト
	mPlayer_sprite_Up[0] = Player_Handle[0];
	mPlayer_sprite_Up[1] = Player_Handle[1];

	mPlayer_sprite_Left[0] = Player_Handle[2];
	mPlayer_sprite_Left[1] = Player_Handle[3];

	mPlayer_sprite_Down[0] = Player_Handle[4];
	mPlayer_sprite_Down[1] = Player_Handle[5];

	mPlayer_sprite_Right[0] = Player_Handle[6];
	mPlayer_sprite_Right[1] = Player_Handle[7];



	mPlayer_Bullet_sprite = Player_Bullet_Handle;
	
	mEnemy_HitEffect_sprite[0] = Enemy_HitEffect_Handle[0];
	mEnemy_HitEffect_sprite[1] = Enemy_HitEffect_Handle[1];
	mEnemy_HitEffect_sprite[2] = Enemy_HitEffect_Handle[2];

	mStage_HitEffect_sprite[0] = Stage_HitEffect_Handle[0];
	mStage_HitEffect_sprite[1] = Stage_HitEffect_Handle[1];
	mStage_HitEffect_sprite[2] = Stage_HitEffect_Handle[2];

	
	mBullet = std::make_shared<std::vector<Bullet>>();

	GetGraphSize(mPlayer_sprite_Up[0], &mSize.x, &mSize.y);	//サイズを設定
	//printf("size X: %d\n", mSize.x);
	//printf("size Y: %d\n", mSize.y);

	mSpeed = 0;
	mSpeed_Max = 10;	//最大速度


	//初期座標
	
	//スクリーン座標
	mPosition.x = SCREEN_WIDTH / 2;		
	mPosition.y = SCREEN_HEIGHT / 2;

	//ステージ座標
	mStagePosition.x = STAGE_WIDTH / 2;
	mStagePosition.y = STAGE_HEIGHT / 50 * 20;

	stagePosition = mStagePosition;	//ステージ内座標


	mVector = VECTOR_UP;	//初期方向
	mMenu = false;			//ショップを開くかどうか？
}

//座標を修正
void Player::FixPos(glm::ivec2 pos)
{
	if (mVector == VECTOR_UP)
	{
//		printf("UP\n"); 
		mPosition.y = pos.y + CELL + CELL / 2;
	}
	else if (mVector == VECTOR_DOWN)
	{
//		printf("DOWN\n");

		mPosition.y = pos.y - (CELL / 2);
	}
	else if (mVector == VECTOR_LEFT)
	{
//		printf("LEFT\n");

		mPosition.x = pos.x + (CELL + CELL / 2);
	}
	else if (mVector == VECTOR_RIGHT)
	{
//		printf("RIGHT\n");

		mPosition.x = pos.x - (CELL / 2);
	}
	else {
//		printf("None\n");
	}
}

//座標を開始地点に戻す。
void Player::setReset()
{
	//スクリーン座標
	mPosition.x = SCREEN_WIDTH / 2;
	mPosition.y = SCREEN_HEIGHT / 2;

	//ステージ座標
	mStagePosition.x = STAGE_WIDTH / 2;
	mStagePosition.y = STAGE_HEIGHT / 50 * 20;

	stagePosition = mStagePosition;	//ステージ座標と初期座標を一致させる。
}

//位置のオフセット座標を修正
void Player::OffsetFixPos(glm::ivec2 pos)
{
#define OFFSET 20

	//　上、下
	if (mVector == VECTOR_UP || mVector == VECTOR_DOWN)
	{
//
		//printf("VECTOR_UP , VECTOR_DOWN\n");
		//		printf("player: %d\n",mPosition.x);
		//		printf("block: %d\n",pos.x);

		int PB = (mPosition.x - (CELL / 2)) - pos.x;	//どっち側居るか？

		if (PB > 0)
		{
//			printf("Right: %d\n", PB);

			int cp = CELL - PB; // めり込み量
//			printf("めりこみ量　cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("Right 修正\n");
				mPosition.x = pos.x + CELL + (CELL / 2);
			}
		}
		else if (PB < 0)
		{
//			printf("Left: %d\n", PB);

			int cp = CELL - std::abs(PB); // めり込み量
//			printf("めりこみ量　cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("Left 修正\n");
				mPosition.x = pos.x - CELL + (CELL / 2);
			}
		}
	}	
	else if (mVector == VECTOR_LEFT || mVector == VECTOR_RIGHT)
	{
		//左右

//		printf("VECTOR_LEFT , VECTOR_RIGHT\n");
		//		printf("player: %d\n",mPosition.x);
		//		printf("block: %d\n",pos.x);

		int PB = (mPosition.y - (CELL / 2)) - pos.y;	//どっち側居るか？

		if (PB > 0)
		{
//			printf("down: %d\n", PB);

			int cp = CELL - PB; // めり込み量
//			printf("めりこみ量　cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("down 修正\n");
				mPosition.y = pos.y + CELL + (CELL / 2);
			}
		}
		else if (PB < 0)
		{
//			printf("Up: %d\n", PB);

			int cp = CELL - std::abs(PB); // めり込み量
//			printf("めりこみ量　cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("Up 修正\n");
				mPosition.y = pos.y - CELL + (CELL / 2);
			}
		}
	}
#undef OFFSET
}



//エネミーのバレットとの当たり判定
void Player::ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy)
{
	//エネミー
	for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
	{	
		//バレット
		for (std::vector<Bullet>::iterator it = itr->getBullet()->begin(); it != itr->getBullet()->end(); it++)
		{
			//交差判定	
			if (Box_Collision::Intersect(mCol, it->mCol) == true)
			{

				it->FixPos(mCol.getPosition());	//座標修正
				it->mIsEnemyHit = true;			//エネミーとヒット
			}
		}
	}
}




//バレット　更新
void Player::Bullet_Update()
{
	// 攻撃　バレット
	if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
	{
		//printf("攻撃\n");
		mBullet->push_back(Bullet(mPosition, mVector, mPlayer_Bullet_sprite, mStage_HitEffect_sprite, mEnemy_HitEffect_sprite));
	}

	//バレットを更新
	for (std::vector<Bullet>::iterator itr = mBullet->begin(); itr != mBullet->end(); itr++)
	{
		//printf("バレット更新\n");

		itr->Update();
	}
}


int Player::getSpeed()
{
	return mSpeed;
}

//更新
void Player::Update()
{
	DrawFormatString(0,0,GetColor(0,255,0),"Position: %d , %d ",mPosition.x,mPosition.y);



	//printf("%d\n",mSpeed_Max);

	Player_Update();	//プレイヤー更新
	Bullet_Update();	//バレットを更新
}

//ステータスを設定
void Player::set_Bulid(ItemData data)
{

	mSpeed_Max += data.mSpeed_Max;

	HP_Max += data.HP_Max;
	HP += data.HP_Rec;			
	HP_autoRec += data.HP_autoRec;

	Attack += data.Attack;

	Coin += data.Coin;

}





//プレイヤー　更新
void Player::Player_Update()
{
	//printf("いいいい\n");

	
	mSpeed = mSpeed_Max;
	//キー入力
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
	//	printf("LEFT\n");
		mVector = VECTOR_LEFT;	//方向
		stagePosition.x -= mSpeed;
	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
	//	printf("RIGHT\n");
		mVector = VECTOR_RIGHT;	//方向
		stagePosition.x += mSpeed;

	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
	{
	//	printf("UP\n");
		mVector = VECTOR_UP;	//方向
		stagePosition.y -= mSpeed;

	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
	//	printf("DOWN\n");
		mVector = VECTOR_DOWN;	//方向
		stagePosition.y += mSpeed;

	}
	else {
		mSpeed = 0;
	}



	mPosition += mVector * mSpeed;


	//当たり判定

	//スプライトの中心からのため修正
	glm::ivec2 pos = mPosition;
	pos.x += -(CELL / 2);
	pos.y += -(CELL / 2);
	mCol.setPosition(pos);
	mCol.setSize(mSize - 1);
	mCol.setTrigger(false);
	mCol.setVector(mVector);


}

//描画
void Player::Draw()
{
	Bullet_Draw();	//バレット描画
	Player_Draw();	//プレイヤー描画

	// デバッグ描画
	DrawFormatString(0,32,GetColor(255,255,255),"# Position: %d , %d  ",stagePosition.x,stagePosition.y);


}

//速度を設定
void Player::setSpeed(int speed)
{
	mSpeed = speed;
}



//プレイヤー　描画
void Player::Player_Draw()
{
#define ANIMETION_SPEED 5

	printf("%d\n",anim.getClip_loop(ANIMETION_SPEED));

	//方向
	if (mVector == VECTOR_UP)
	{
		if (mSpeed != 0)
		{
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mPlayer_sprite_Up[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mPlayer_sprite_Up[0], true, false);

		}
	}
	else if (mVector == VECTOR_DOWN)
	{
		if (mSpeed != 0)
		{
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mPlayer_sprite_Down[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(mPosition.x, mPosition.y,1.0, 0, mPlayer_sprite_Down[0], true, false);

		}

		//DrawRotaGraph(mPosition.x, mPosition.y, 1.0, PI, mPlayer_sprite, true, false);
	}
	else if (mVector == VECTOR_LEFT)
	{
		

		if (mSpeed != 0)
		{
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mPlayer_sprite_Left[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mPlayer_sprite_Left[0], true, false);

		}



		//DrawRotaGraph(mPosition.x, mPosition.y, 1.0, -(PI * 2) / 4, mPlayer_sprite, true, false);
	}
	else if (mVector == VECTOR_RIGHT)
	{

		if (mSpeed != 0)
		{
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mPlayer_sprite_Right[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mPlayer_sprite_Right[0], true, false);

		}




		//DrawRotaGraph(mPosition.x, mPosition.y, 1.0, (PI * 2) / 4, mPlayer_sprite, true, false);
	}

	//DrawPixel(mPosition.x, mPosition.y,GetColor(0,255,0));

#undef ANIMETION_SPEED
}


//バレット　描画
void Player::Bullet_Draw()
{
	for (std::vector<Bullet>::iterator itr = mBullet->begin(); itr != mBullet->end(); itr++)
	{		
		//printf("バレット更新\n");
		itr->Draw();	//バレット描画		
	}
}



//ショップ画面を開くかどうか？
bool Player::getIsMenu()
{
	return mMenu;
}

//ショップ画面を開くかどうか？
void Player::setIsMenu(bool b)
{
	mMenu = b;
}

//バレットを取得
std::shared_ptr<std::vector<Bullet>> Player::getBullet()
{
	return mBullet;
}



//デストラクタ
Player::~Player()
{

}
