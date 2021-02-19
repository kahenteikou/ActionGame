#include "Bullet.hpp"

//コンストラクタ
Bullet::Bullet(glm::ivec2 pos , glm::ivec2 vec, int handle) : Actor(nullptr,pos,vec)
{
	GetGraphSize(handle,&mSize.x, &mSize.y);	//スプライトの大きさ

	mSpeed = 10;		//バレットの速度
	mSprite = handle;	//スプライト
}

//更新
void Bullet::Update()
{



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

//描画
void Bullet::Draw()
{
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

//デストラクタ
Bullet::~Bullet()
{

}
