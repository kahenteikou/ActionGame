#include "Actor.hpp"

//�R���X�g���N�^
Actor::Actor(Entry* e,glm::vec2 pos ,glm::vec2 vec )
{
	vector = vec;
	position = pos;
	size = glm::vec2(0,0);
	owner = e;
}

//�������擾
glm::vec2 Actor::getVector()
{
	return vector;
}

//���W���擾
glm::vec2 Actor::getPosition()
{
	return position;
}

//���W���擾
void Actor::setPosition(glm::vec2 pos)
{
	position = pos;
}




//�f�X�g���N�^
Actor::~Actor()
{

}
