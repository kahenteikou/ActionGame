#include "Actor.hpp"

//コンストラクタ
Actor::Actor(glm::ivec2 pos ,glm::ivec2 vec )
{
	mVector = vec;
	mPosition = pos;
	mSize = glm::ivec2(0,0);
}

//方向を取得
glm::ivec2 Actor::getVector()
{
	return mVector;
}

//座標を取得
glm::ivec2 Actor::getPosition()
{
	return mPosition;
}

//デストラクタ
Actor::~Actor()
{

}
