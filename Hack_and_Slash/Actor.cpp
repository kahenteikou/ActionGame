#include "Actor.hpp"

//コンストラクタ
Actor::Actor(Entry* e,glm::vec2 pos ,glm::vec2 vec )
{
	vector = vec;
	position = pos;
	size = glm::vec2(0,0);
	owner = e;
}

//方向を取得
glm::vec2 Actor::getVector()
{
	return vector;
}

//座標を取得
glm::vec2 Actor::getPosition()
{
	return position;
}

//座標を取得
void Actor::setPosition(glm::vec2 pos)
{
	position = pos;
}




//デストラクタ
Actor::~Actor()
{

}
