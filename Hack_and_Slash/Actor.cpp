#include "Actor.hpp"

//コンストラクタ
Actor::Actor(Entry* e,glm::ivec2 pos ,glm::ivec2 vec )
{
	vector = vec;
	position = pos;
	size = glm::ivec2(0,0);
	owner = e;
}

//方向を取得
glm::ivec2 Actor::getVector()
{
	return vector;
}

//座標を取得
glm::ivec2 Actor::getPosition()
{
	return position;
}

//座標を取得
void Actor::setPosition(glm::ivec2 pos)
{
	position = pos;
}




//デストラクタ
Actor::~Actor()
{

}
