#include "MapChip.hpp"
#include "Entry.hpp"
//�R���X�g���N�^
MapChip::MapChip(Tag t, glm::vec2  pos, glm::vec2  colsize,int handle) : Actor(nullptr)
{


	position = pos;			//���W
	worldPosition = pos;	//���[���h���W
	sprite = handle;		//�X�v���C�g	
	//printf("%f\n",size.x);



	//�����蔻��
	size.x = CELL;
	size.y = CELL;


//	mCol = std::make_shared<BoxCollision>();
//	mCol = std::make_shared<BoxCollision>();

	minValue = position;
	maxValue = position + size;
	

	mCol.setTag(t);			//�^�O
	mCol.setMin(&minValue);	//�ŏ��l
	mCol.setMax(&maxValue);	//�ő�l


/*
	mCol->setTag(t);			//�^�O
	mCol->setMin(&minValue);	//�ŏ��l
	mCol->setMax(&maxValue);	//�ő�l
	*/
	//printf("���������@%f %f\n", mCol->getMax().x, mCol->getMax().y);
//	printf("���������@%f %f\n", mCol->getMin().x, mCol->getMin().y);

}

//���[���h���W���擾
glm::vec2  MapChip::getWorldPosition()
{
	return worldPosition;
}






//�f�t�H���g�R���X�g���N�^
MapChip::MapChip() : Actor(nullptr)
{

}

void MapChip::Update()
{
	minValue = position;	
	maxValue = position + size;


}

void MapChip::Draw()
{
	DrawGraph((int)position.x, (int)position.y,sprite,true);
	DrawCircle(maxValue.x, maxValue.y, 5, GetColor(0, 255, 0), true);
	DrawCircle(minValue.x, minValue.y ,5, GetColor(255, 0, 0), true);

}


//�f�X�g���N�^
MapChip::~MapChip()
{

}
