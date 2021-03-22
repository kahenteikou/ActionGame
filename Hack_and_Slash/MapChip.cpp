#include "MapChip.hpp"

//�R���X�g���N�^
MapChip::MapChip(Tag t, glm::ivec2 pos, glm::ivec2 size,int handle) : Actor(nullptr)
{

	position = pos;			//���W
	worldPosition = position;	//���[���h���W
	size = size;				//�T�C�Y
	mSprite = handle;			//�X�v���C�g	
	

	mCol = std::make_shared<BoxCollision>();

	



}

//���[���h���W���擾
glm::ivec2 MapChip::getWorldPosition()
{
	return worldPosition;
}


//�f�t�H���g�R���X�g���N�^
MapChip::MapChip() : Actor(nullptr)
{

}

void MapChip::Update()
{
	
	

}

void MapChip::Draw()
{
	DrawGraph(position.x, position.y,mSprite,true);
}


//�f�X�g���N�^
MapChip::~MapChip()
{

}
