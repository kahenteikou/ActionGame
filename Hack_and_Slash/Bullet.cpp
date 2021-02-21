#include "Bullet.hpp"

//コンストラクタ
Bullet::Bullet(glm::ivec2 pos , glm::ivec2 vec, int handle,int effectHandle[3]) : Actor(nullptr,pos,vec),anim(2)
{
	GetGraphSize(handle,&mSize.x, &mSize.y);	//スプライトの大きさ

	mSpeed = 10;		//バレットの速度
	mSprite = handle;	//スプライト
	isDelete = false;	//削除するかどうか？
	mEffectSprite[0] = effectHandle[0];
	mEffectSprite[1] = effectHandle[1];
	mEffectSprite[2] = effectHandle[2];


	mIsHit = false; //ヒットしたかどうか？
}



//座標を修正
void Bullet::FixPos(glm::ivec2 pos)
{
	if (mVector == VECTOR_UP)
	{
		mPosition.y = pos.y + (CELL);
	}
	else if (mVector == VECTOR_DOWN)
	{
		mPosition.y = pos.y;
	}
	else if (mVector == VECTOR_LEFT)
	{
		mPosition.x = pos.x + (CELL);
	}
	else if (mVector == VECTOR_RIGHT)
	{
		mPosition.x = pos.x;		
	}
}




//更新
void Bullet::Update()
{
	//バレットの弾道
	if (mIsHit == false) {
		//　移動
		if (mVector == VECTOR_UP)
		{
			//当たり判定を調整
			glm::ivec2 pos = mPosition;
			pos.x += -(mSize.x / 2);
			pos.y += -(mSize.y / 2);
			mCol.setPosition(pos);
			mCol.setSize(mSize);
			mCol.setTrigger(false);
			mCol.setVector(mVector);


			mPosition.y += -mSpeed;
		}
		else if (mVector == VECTOR_DOWN)
		{
			//当たり判定を調整
			glm::ivec2 pos = mPosition;
			pos.x += -(mSize.x / 2);
			pos.y += -(mSize.y / 2);
			mCol.setPosition(pos);
			mCol.setSize(mSize);
			mCol.setTrigger(false);

			mPosition.y += mSpeed;

		}
		else if (mVector == VECTOR_LEFT)
		{
			//当たり判定を調整
			glm::ivec2 pos = mPosition;
			pos.x += -(mSize.y / 2);
			pos.y += -(mSize.x / 2);
			mCol.setPosition(pos);
			glm::ivec2 size = glm::ivec2(mSize.y, mSize.x);
			mCol.setSize(size);
			mCol.setTrigger(false);

			mPosition.x += -mSpeed;

		}
		else if (mVector == VECTOR_RIGHT)
		{
			//当たり判定を調整
			glm::ivec2 pos = mPosition;
			pos.x += -(mSize.y / 2);
			pos.y += -(mSize.x / 2);
			mCol.setPosition(pos);
			glm::ivec2 size = glm::ivec2(mSize.y, mSize.x);
			mCol.setSize(size);
			mCol.setTrigger(false);

			mPosition.x += mSpeed;
		}
	}



}

//描画
void Bullet::Draw()
{
	//バレットを移動
	if (mIsHit == false) {
		//描画向き
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
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, -(PI * 2) / 4, mSprite, true, true);
		}
		else if (mVector == VECTOR_RIGHT)
		{
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, (PI * 2) / 4, mSprite, true, true);
		}
	}
	else {

		//ヒットエフェクト
		int num = 0;
		if (anim.getClip(num, BULLET_EFFECT_SPEED) == false) {
			DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mEffectSprite[num], true, false);
		}
		else {
			isDelete = true;

	//		printf("false\n");
		}

	}





}

//デストラクタ
Bullet::~Bullet()
{

}
