#include "Actor.hpp"

//�R���X�g���N�^
Actor::Actor(Entry* e,glm::ivec2 pos ,glm::ivec2 vec )
{
	vector = vec;
	position = pos;
	size = glm::ivec2(0,0);
	owner = e;
}

//�������擾
glm::ivec2 Actor::getVector()
{
	return vector;
}

//���W���擾
glm::ivec2 Actor::getPosition()
{
	return position;
}

//���W���擾
void Actor::setPosition(glm::ivec2 pos)
{
	position = pos;
}




//�f�X�g���N�^
Actor::~Actor()
{

}
