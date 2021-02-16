#include "Collision.hpp"

//コンストラクタ
Box_Collision::Box_Collision()
{

	mIsTrigger = false;
}


//矩形同士の交差判定
bool Box_Collision::Intersect( Box_Collision &a, Box_Collision &b)
{
//	printf("X: %d\n", a.getPosition().x);
//	printf("Y: %d\n",a.getPosition().y);

//	printf("size X: %d\n", a.getSize().x);
//	printf("size Y: %d\n",a.getSize().y);


	//printf("X: %d\n", b.getPosition().x);
	//printf("Y: %d\n",b.getPosition().y);

//	printf("size X: %d\n", b.getSize().x);
//	printf("size Y: %d\n",b.getSize().y);

	if ((a.getPosition().x + a.getSize().x > b.getPosition().x && b.getPosition().x + b.getSize().x > a.getPosition().x)
		&& (a.getPosition().y + a.getSize().y > b.getPosition().y && b.getPosition().y + b.getSize().y > a.getPosition().y))
	{
		return true;
	}
	else
	{
		return false;
	}
}




// #################################### 取得　関係

//トリガータイプを取得
bool Box_Collision::getTrigger()
{
	return mIsTrigger;
}


//座標を取得
glm::ivec2 Box_Collision::getPosition()
{
	return mPosition;
}

//サイズを取得
glm::ivec2 Box_Collision::getSize()
{
	return mSize;
}

//オブジェクトタイプを取得
StageObjectType Box_Collision::getObjectType()
{
	return Type;
}

//オブジェクトタイプを設定
glm::ivec2 Box_Collision::getVector()
{
	return mVector;
}



// #################################### 設定　関係

//トリガータイプを設定
void Box_Collision::setTrigger(bool tri)
{
	mIsTrigger = tri;
}


//座標を設定
void Box_Collision::setPosition(glm::ivec2 pos)
{
	mPosition = pos;
}

// サイズを設定
void Box_Collision::setSize(glm::ivec2 size)
{
	mSize = size;
}

//オブジェクトタイプを設定
void Box_Collision::setStageObjectType(StageObjectType type)
{
	Type = type;
}

//オブジェクトタイプを設定
void Box_Collision::setVector(glm::ivec2 vec)
{
	mVector = vec;
}


//デストラクタ
Box_Collision::~Box_Collision()
{

}