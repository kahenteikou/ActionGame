#include "Player.hpp"

//コンストラクタ
Player::Player(Entry* e) : Actor(e)
{
	mSprite = LoadGraph("Assets/Player.png");			//プレイヤースプライト
	mBullet_Sprite = LoadGraph("Assets/Bullet.png");	//バレットスプライト

	int t = LoadDivGraph("Assets/Explosion.png",3,3,1,CELL * 3,CELL,mBulletEffect_Sprite);
	printf("ああああああ　%d\n",t);
	mBullet = std::make_shared<std::vector<Bullet>>();

	GetGraphSize(mSprite, &mSize.x, &mSize.y);	//サイズを設定
	//printf("size X: %d\n", mSize.x);
	//printf("size Y: %d\n", mSize.y);

	mSpeed = 0;
	mSpeed_Max = 10;


	
	//初期座標
	mPosition.x = SCREEN_WIDTH / 2;
	mPosition.y = SCREEN_HEIGHT / 2;

	mVector = VECTOR_UP;	//初期方向


	mMenu = false;	//ショップを開くかどうか？



}

//座標を修正
void Player::FixPos(glm::ivec2 pos)
{
	if (mVector == VECTOR_UP)
	{
		mPosition.y = pos.y + CELL + CELL / 2;
	}else if (mVector == VECTOR_DOWN)
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



//バレット　更新
void Player::Bullet_Update()
{
	// 攻撃　バレット
	if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
	{
		mBullet->push_back(Bullet(mPosition, mVector, mBullet_Sprite,mBulletEffect_Sprite));
	}

	//バレットを更新
	for (std::vector<Bullet>::iterator itr = mBullet->begin(); itr != mBullet->end(); itr++)
	{
		itr->Update();
	}
}

//更新
void Player::Update()
{
	//printf("%d\n",mSpeed_Max);
	Bullet_Update();	//バレットを更新
	Player_Update();	//プレイヤー更新
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
		mVector = VECTOR_LEFT;	//方向
		
		mPosition.x += -mSpeed;

	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
		mVector = VECTOR_RIGHT;	//方向
		
		mPosition.x += mSpeed;

	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
	{
		mVector = VECTOR_UP;	//方向
		
		mPosition.y += -mSpeed;

	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
		mVector = VECTOR_DOWN;	//方向
		
		mPosition.y += mSpeed;
	}
	else {
		mSpeed = 0;
	}

	//当たり判定

	//スプライトの中心からのため修正
	glm::ivec2 pos = mPosition;
	pos.x += -(CELL / 2);
	pos.y += -(CELL / 2);
	mCol.setPosition(pos);
	mCol.setSize(mSize);
	mCol.setTrigger(false);
	mCol.setVector(mVector);


}

//描画
void Player::Draw()
{
	Bullet_Draw();	//バレット描画
	Player_Draw();	//プレイヤー描画
}


//プレイヤー　描画
void Player::Player_Draw()
{
	//方向
	if (mVector == VECTOR_UP)
	{
		DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mSprite, true, false);
	}
	else if (mVector == VECTOR_DOWN)
	{
		DrawRotaGraph(mPosition.x, mPosition.y, 1.0, PI, mSprite, true, false);
	}
	else if (mVector == VECTOR_LEFT)
	{
		DrawRotaGraph(mPosition.x, mPosition.y, 1.0, -(PI * 2) / 4, mSprite, true, false);
	}
	else if (mVector == VECTOR_RIGHT)
	{
		DrawRotaGraph(mPosition.x, mPosition.y, 1.0, (PI * 2) / 4, mSprite, true, false);
	}

	DrawPixel(mPosition.x, mPosition.y,GetColor(0,255,0));
}


//バレット　描画
void Player::Bullet_Draw()
{
	for (std::vector<Bullet>::iterator itr = mBullet->begin(); itr != mBullet->end(); itr++)
	{		
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
