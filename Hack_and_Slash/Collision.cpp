#include "Collision.hpp"
#include "Entry.hpp"


/*####################################################
* �����蔻��̊��N���X
######################################################*/

//�R���X�g���N�^
Collision::Collision()
{
	col_TagType = Tag::Invalid;	//�擾�@�^�O
	my_TagType = Tag::Invalid;	//���g�@�^�O

	IsTrigger = false;		//�g���K�[�^�C�v
	isCol = false;			//�����������ǂ����H
	Vector = nullptr;		//����
}

// #################################### �擾�@�֌W

//�g���K�[�^�C�v���擾
bool Collision::getTriggerType()
{
	return IsTrigger;
}

//�擾�����^�C�v���擾
Tag Collision::getTag()
{
	return col_TagType;
}

//�������擾
glm::vec2 Collision::getVector()
{
	return *Vector;
}

//�^�C�v���擾
Tag Collision::getMyTag()
{
	return my_TagType;
}

//�����������ǂ����H
bool Collision::getCol()
{
	return isCol;
}


//���x���擾
glm::vec2 Collision::getSpeed()
{
	return *Speed;
}

// #################################### �ݒ�@�֌W

//�g���K�[�^�C�v��ݒ�
void Collision::setTriggerType(bool tri)
{
	IsTrigger = tri;
}

//�^�O�^�C�v��ݒ�
void Collision::setTag(Tag type)
{	
	my_TagType = type;
}

//�I�u�W�F�N�g�^�C�v��ݒ�
void Collision::setVector(glm::vec2 *vec)
{
	Vector = vec;
}

//�����蔻��̃^�O��ݒ�
void Collision::setColTag(Tag type)
{
	col_TagType = type;
}

//�����蔻��̃^�O��ݒ�
void Collision::setCol(bool b)
{
	isCol = b;
}



//���x��ݒ�
void Collision::setSpeed(glm::vec2 *spp)
{
	Speed = spp;
}


//�f�X�g���N�^
Collision::~Collision()
{

}


/*##############################################################################################################################################*/

/*####################################################
* ��`�̓����蔻��
######################################################*/

//�R���X�g���N�^
BoxCollision::BoxCollision()
{
	box.mMax = nullptr;	//AABB������
	box.mMin = nullptr;	//AABB������
}


//��������
//void BoxCollision::Intersect(std::shared_ptr<BoxCollision> col)
void BoxCollision::Intersect(BoxCollision *col)
//void BoxCollision::Intersect(BoxCollision& col)
{
	//printf("������\n");
	//printf("%f , %f \n",box.mMin->x,box.mMin->y);
	//printf("%f , %f \n",box.mMax->x,box.mMax->y);
	// 

	//printf("%f , %f \n", col->getMin().x, col->getMin().y);
	//printf("%f , %f \n", col->getMax().x, col->getMax().y);

//	printf("col->getMin()");
	printf("\n\n");


	if ((col->getMax().x > box.mMin->x && box.mMax->x > col->getMin().x)
		&& (col->getMax().y > box.mMin->y && box.mMax->y > col->getMin().y))
	{
		printf("true \n");
		setCol(true);				//�����蔻���ݒ�
		setColTag(col->getMyTag());	//�^�O���擾
		col->setColTag(getMyTag());	//�^�O��ݒ�

	
		if(getTriggerType() == false)
		{

			//�T�C�Y���擾
			 
			//����
			glm::vec2 colSize = col->getMax() - col->getMin();
			colSize.x = colSize.x / 2;
			colSize.y = colSize.y / 2;

			//����
			glm::vec2 boxSize = *box.mMax - *box.mMin;
			boxSize.x = boxSize.x / 2;
			boxSize.y = boxSize.y / 2;

			float colCenterX = (col->getMin().x + colSize.x);
			float colCenterY = (col->getMin().y + colSize.y);
			float boxCenterX = (box.mMin->x + boxSize.x);
			float boxCenterY = (box.mMin->y + boxSize.y);


			float deltaX = boxCenterX - colCenterX; //���Ȃ�box���E�ɂ���
			float deltaY = boxCenterY - colCenterY; //���Ȃ�box����ɂ���
			float adjust = 0.0;

			if (fabs(deltaX) < fabs(deltaY))
			{
			//	printf(", Y adjust \n");
				if (deltaY > 0)
				{
					adjust = col->getMax().y - box.mMin->y + 0.001f; // +����
				}
				else
				{
					adjust = -(box.mMax->y - col->getMin().y + 0.001f); // -����
				}
				box.mMin->y += adjust;
				box.mMax->y += adjust;
			}
			else
			{
			//	printf(", X adjust \n");
				if (deltaX > 0)
				{
					adjust = col->getMax().x - box.mMin->x + 0.001f; // +����

				}
				else
				{
					adjust = -(box.mMax->x - col->getMin().x + 0.001f); // -����
				}
				box.mMin->x += adjust;
				box.mMax->x += adjust;
			}
		}
		else {
			//Trigger true
		}
	}
	else
	{
		
		//�������ĂȂ���
		setCol(false);
		setColTag(Tag::Invalid);
		col->setColTag(Tag::Invalid);

	}




}


// #################################### �擾�@�֌W

//�ő�l���擾
glm::vec2 BoxCollision::getMax()
{
	
	printf("getMax address %x\n", box.mMax);

	return *box.mMax;
}

//�ŏ��l���擾
glm::vec2 BoxCollision::getMin()
{
	printf("getMin address %x\n", box.mMin);

	return *box.mMin;
}




// #################################### �ݒ�@�֌W

//�ő�l��ݒ�
void BoxCollision::setMax(glm::vec2 *max)
{
	box.mMax = max;
	printf("setMax address %x\n", box.mMax);

}

//�ŏ��l��ݒ�
void BoxCollision::setMin(glm::vec2 *min)
{
	box.mMin = min;
	printf("setMin address %x\n",box.mMin);
}

//�ő�l�̒l��ݒ�
void BoxCollision::setMaxValue(glm::vec2& max)
{
	*box.mMax = max;
}

//�ŏ��l�̒l��ݒ�
void BoxCollision::setMinValue(glm::vec2& min)
{
	*box.mMin = min;

}



//�f�X�g���N�^
BoxCollision::~BoxCollision()
{

}

/*##############################################################################################################################################*/
