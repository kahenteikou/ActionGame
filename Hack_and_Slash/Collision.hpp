#ifndef ___COLLISION_HPP_
#define ___COLLISION_HPP_

#include "glm/glm.hpp"
#include <iostream>
//�^�O
typedef enum class Tag
{
	Player,
	Enemy,
	Wall,
	Item,
	None,		//���ݒ�
	Block,
	Brick,
	Shop,

	Invalid,	//�������ĂȂ�
}Tag;


//�v���~�e�B�u�^

//��
typedef struct LineSegment
{
	glm::vec2 mStart;	
	glm::vec2 mEnd;		


}LineSegment;

//AABB
typedef struct AABB
{
	glm::vec2* mMin;	//�ŏ��l
	glm::vec2* mMax;	//�ő�l

}AABB;

//�~
typedef struct Circle
{
	glm::vec2* mCenter;	//���S�_
	float* mRadius;		//���a
}Circle;

//����
typedef struct Segment {
	glm::vec2* mStart;	//�n�_
	glm::vec2* mEnd;	//�I�_
}Segment;



/*####################################################
* �����蔻��̊��N���X
######################################################*/
class Collision
{
public:
	Collision();	//�R���X�g���N�^
	~Collision();	//�f�X�g���N�^
	
	//�@�\
	
	

	//�ݒ�@�֌W
	void setCol(bool b);				//�����������ǂ����H
	void setColTag(Tag type);			//�擾�����^�C�v�ݒ�
	void setVector(glm::vec2* vec);		//�����ݒ�
	void setTriggerType(bool tri);		//�g���K�[�^�C�v��ݒ�
	void setTag(Tag type);				//�^�O��ݒ�
	void setSpeed(glm::vec2 *spp);		//���x��ݒ�

	//�擾�@�֌W
	Tag getMyTag();				//�^�C�v���擾
	bool getTriggerType();		//�g���K�[�^�C�v���擾
	glm::vec2 getVector();		//�������擾
	bool getCol();				//�����������ǂ����H
	Tag getTag();				//�擾�����^�C�v���擾
	glm::vec2 getSpeed();		//���x���擾

private:
	bool IsTrigger;		//�g���K�[�^�C�v���ǂ����H
	Tag my_TagType;		//���g�^�O
	Tag col_TagType;	//�擾�^�O
	glm::vec2 *Vector;	//����
	bool isCol;			//�����������ǂ����H
	glm::vec2 *Speed;	//���x
};


/*####################################################
* ��`�̓����蔻��
######################################################*/

class BoxCollision : public Collision
{
public:
	BoxCollision();		//�R���X�g���N�^
	~BoxCollision();	//�f�X�g���N�^

//	void Intersect(BoxCollision &col);
	void Intersect(std::shared_ptr<BoxCollision> col);
	//�擾�@�֌W
	glm::vec2 getMax();
	glm::vec2 getMin();


	//�ݒ�@�֌W
	void setMax(glm::vec2 *max);
	void setMin(glm::vec2 *min);

	void setMaxValue(glm::vec2 &max);
	void setMinValue(glm::vec2 &min);

private:
	AABB box;
};




#endif