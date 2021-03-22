#include "Player.hpp"

#include <iostream>
#include <vector>

#include "Entry.hpp"
#include "Input.hpp"
#include "Enemy_Mng.hpp"
#include "ItemID.hpp"
#include "MapChip.hpp"
#include "Collision.hpp"






//コンストラクタ
Player::Player(Entry* e, int Player_Handle[8], int Player_Bullet_Handle, int Enemy_HitEffect_Handle[3], int Stage_HitEffect_Handle[3]) : Actor(e),anim(1)
{

	//プレイヤー自機のスプライト
	playerSpriteUp[0] = Player_Handle[0];
	playerSpriteUp[1] = Player_Handle[1];

	playerSpriteLeft[0] = Player_Handle[2];
	playerSpriteLeft[1] = Player_Handle[3];

	playerSpriteDown[0] = Player_Handle[4];
	playerSpriteDown[1] = Player_Handle[5];

	playerSpriteRight[0] = Player_Handle[6];
	playerSpriteRight[1] = Player_Handle[7];



	playerBulletSprite = Player_Bullet_Handle;
	
	enemyHitEffectSprite[0] = Enemy_HitEffect_Handle[0];
	enemyHitEffectSprite[1] = Enemy_HitEffect_Handle[1];
	enemyHitEffectSprite[2] = Enemy_HitEffect_Handle[2];

	stageHitEffectSprite[0] = Stage_HitEffect_Handle[0];
	stageHitEffectSprite[1] = Stage_HitEffect_Handle[1];
	stageHitEffectSprite[2] = Stage_HitEffect_Handle[2];

	
	bullet = std::make_shared<std::vector<Bullet>>();

	speed = 0;
	


	//初期座標
	
	//スクリーン座標
	position.x = SCREEN_WIDTH / 2;		
	position.y = SCREEN_HEIGHT / 2;

	//ステージ座標
	stagePosition.x = STAGE_WIDTH / 2;
	stagePosition.y = STAGE_HEIGHT / 50 * 20;


	worldPosition.x = position.x +120;	//ワールド座標
	worldPosition.y = position.y + 440;	//ワールド座標

	vector = VECTOR_UP;	//初期方向
	mMenu = false;		//ショップを開くかどうか？


	//当たり判定	
	mCol = std::make_shared<BoxCollision>();
	size.x = CELL;
	size.y = CELL;

	mCol->setTag(Tag::Player);
	mCol->setMin(&minValue);
	mCol->setMax(&maxValue);





}

//座標を修正
void Player::FixPos(MapChip m)
{

}

//座標を開始地点に戻す。
void Player::setReset()
{
	//スクリーン座標
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;

	//ステージ座標
	stagePosition.x = STAGE_WIDTH / 2;
	stagePosition.y = STAGE_HEIGHT / 50 * 20;

	//ワールド座標
	worldPosition.x = position.x + 120;	
	worldPosition.y = position.y + 440;	

}

//位置のオフセット座標を修正
void Player::OffsetFixPos(glm::vec2  pos)
{
#define OFFSET 20

	//　上、下
	if (vector == VECTOR_UP || vector == VECTOR_DOWN)
	{
//
		//printf("VECTOR_UP , VECTOR_DOWN\n");
		//		printf("player: %d\n",position.x);
		//		printf("block: %d\n",pos.x);

		int PB = (position.x - (CELL / 2)) - pos.x;	//どっち側居るか？

		if (PB > 0)
		{
//			printf("Right: %d\n", PB);

			int cp = CELL - PB; // めり込み量
//			printf("めりこみ量　cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("Right 修正\n");
				position.x = pos.x + CELL + (CELL / 2);
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
				position.x = pos.x - CELL + (CELL / 2);
			}
		}
	}	
	else if (vector == VECTOR_LEFT || vector == VECTOR_RIGHT)
	{
		//左右

//		printf("VECTOR_LEFT , VECTOR_RIGHT\n");
		//		printf("player: %d\n",position.x);
		//		printf("block: %d\n",pos.x);

		int PB = (position.y - (CELL / 2)) - pos.y;	//どっち側居るか？

		if (PB > 0)
		{
//			printf("down: %d\n", PB);

			int cp = CELL - PB; // めり込み量
//			printf("めりこみ量　cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("down 修正\n");
				position.y = pos.y + CELL + (CELL / 2);
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
				position.y = pos.y - CELL + (CELL / 2);
			}
		}
	}
#undef OFFSET
}



//エネミーのバレットとの当たり判定
void Player::ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy)
{

}




//バレット　更新
void Player::Bullet_Update()
{
}


float Player::getSpeed()
{
	return speed;
}

//更新
void Player::Update()
{

	Player_Update();	//プレイヤー更新
	Bullet_Update();	//バレットを更新
}

//ステータスを設定
void Player::set_Bulid(ItemData data)
{



}





//プレイヤー　更新
void Player::Player_Update()
{

	
	speed = 10;
	//キー入力
	if (owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
	//	printf("LEFT\n");
		vector = VECTOR_LEFT;	//方向
		worldPosition.x += -speed;
	}
	else if (owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
	//	printf("RIGHT\n");
		vector = VECTOR_RIGHT;	//方向
		worldPosition.x += speed;
	}
	else if (owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
	{
	//	printf("UP\n");
		vector = VECTOR_UP;	//方向
		worldPosition.y += -speed;
	}
	else if (owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
	//	printf("DOWN\n");
		vector = VECTOR_DOWN;	//方向
		worldPosition.y += speed;
	}
	else {
		speed = 0;
	}


	//座標更新
	position += vector * speed;

	minValue.x = position.x - (CELL / 2);
	minValue.y = position.y - (CELL / 2);

	maxValue.x = minValue.x + CELL;
	maxValue.y = minValue.y + CELL;

	//当たり判定
	
}

//描画
void Player::Draw()
{
	Bullet_Draw();	//バレット描画
	Player_Draw();	//プレイヤー描画

	// デバッグ描画
	DrawFormatString(0,32,GetColor(255,255,255),"# Position: %d , %d  ",position.x,position.y);


}

//速度を設定
void Player::setSpeed(int speed)
{
	speed = speed;
}



//プレイヤー　描画
void Player::Player_Draw()
{
#define ANIMETION_SPEED 5

//	printf("%d\n",anim.getClip_loop(ANIMETION_SPEED));

	//方向
	if (vector == VECTOR_UP)
	{
		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteUp[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteUp[0], true, false);

		}
	}
	else if (vector == VECTOR_DOWN)
	{
		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteDown[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y,1.0, 0, playerSpriteDown[0], true, false);

		}

		//DrawRotaGraph(position.x, position.y, 1.0, PI, mPlayer_sprite, true, false);
	}
	else if (vector == VECTOR_LEFT)
	{
		

		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteLeft[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteLeft[0], true, false);

		}



		//DrawRotaGraph(position.x, position.y, 1.0, -(PI * 2) / 4, mPlayer_sprite, true, false);
	}
	else if (vector == VECTOR_RIGHT)
	{

		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteRight[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteRight[0], true, false);

		}




		//DrawRotaGraph(position.x, position.y, 1.0, (PI * 2) / 4, mPlayer_sprite, true, false);
	}

	//DrawPixel(position.x, position.y,GetColor(0,255,0));


	DrawCircle(maxValue.x, maxValue.y, 5, GetColor(0, 255, 0), true);
	DrawCircle(minValue.x, minValue.y, 5, GetColor(255, 0, 0), true);


#undef ANIMETION_SPEED
}


//バレット　描画
void Player::Bullet_Draw()
{
	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
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
	return bullet;
}


//ステージ座標を設定
void Player::setWorldPosition(glm::vec2  pos)
{
	worldPosition = pos;
}

//ステージ座標を取得
glm::vec2  Player::getWorldPosition()
{
	return worldPosition;
}



//デストラクタ
Player::~Player()
{

}
