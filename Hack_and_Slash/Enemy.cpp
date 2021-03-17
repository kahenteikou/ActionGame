#include "Enemy.hpp"


//�R���X�g���N�^
Enemy::Enemy(glm::ivec2 pos ,int Enemy_sprite, int Enemy_Bullet_sprite, int Stage_HitEffect_sprite[3], int Player_HitEffect_sprite[3]) : Actor(nullptr)
{
	mPosition = pos;	//�������W

	mEnemy_sprite = Enemy_sprite;	//�G�l�~�[
	mEnemy_Bullet_sprite = Enemy_Bullet_sprite;	//�o���b�g

	//�X�e�[�W�@�q�b�g�G�t�F�N�g
	mStage_HitEffect_sprite[0] = Stage_HitEffect_sprite[0];
	mStage_HitEffect_sprite[1] = Stage_HitEffect_sprite[1];
	mStage_HitEffect_sprite[2] = Stage_HitEffect_sprite[2];
	
	//�v���C���[�@�q�b�g�t�F�N�g
	mPlayer_HitEffect_sprite[0] = Player_HitEffect_sprite[0];
	mPlayer_HitEffect_sprite[1] = Player_HitEffect_sprite[1];
	mPlayer_HitEffect_sprite[2] = Player_HitEffect_sprite[2];


	islife = true;	//�����Ă��邩�ǂ����H


//	Rand_Action = GetRand(3);		//����
	Rand_Action = 0;		//����
	//Rand_Action = 3; //GetRand(3);//����

	//Prev_Rand_Action = Rand_Action;	//�O�̗���
	MovePixel = 0;					//�ړ�������

	
//	mSpeed = 10; //�X�s�[�h
//	mSpeed = 2; //�X�s�[�h

	//�����蔻��
	mCol.setStageObjectType(StageObjectType::Enemy);


	bullet = std::make_shared<std::vector<Bullet>>();

}

//�o���b�g���擾
std::shared_ptr<std::vector<Bullet>> Enemy::getBullet()
{
	return bullet;
}

//�j�󂷂�B		
void Enemy::Destroy()
{
	islife = false;
}

//�j�󂳂ꂽ���ǂ����H		
bool Enemy::getIsDestroy()
{
	return islife;
}


//�X�V
void Enemy::Update()
{
	
	//�����蔻��
	glm::ivec2 pos = mPosition;
	pos.y += -(CELL / 2);
	pos.x += -(CELL / 2);
	mCol.setPosition(pos);
	mCol.setSize(glm::ivec2(CELL - 1, CELL - 1));


	//����
	if (Rand_Action == 0)
	{
		mVector = VECTOR_UP;
	}
	else if (Rand_Action == 1)
	{
		mVector = VECTOR_RIGHT;
	}
	else if (Rand_Action == 2)
	{
		mVector = VECTOR_DOWN;
	}
	else if (Rand_Action == 3)
	{
		mVector = VECTOR_LEFT;
	}
	
	//Rand_Attack = GetRand(50); //�U���p�x
	Rand_Attack = GetRand(10); //�U���p�x

	//�U��
	if (Rand_Attack == 1)
	{
	//	printf("�G�l�~�[�U��\n");
	//	bullet->push_back(Bullet(mPosition,mVector,mEnemy_Bullet_sprite,mStage_HitEffect_sprite, mPlayer_HitEffect_sprite));
	}



	/*
	//MovePixel += mSpeed;	//�ړ��ʂɉ��Z
	if (MovePixel > CELL * 2)
	{
		setMove_Rand();
		MovePixel = 0;	//�ړ��ʂ����Z�b�g
	}
	*/


	//�ړ�
//	mPosition.x += mVector.x * mSpeed;
//	mPosition.y += mVector.y * mSpeed;


	//�o���b�g�폜
	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end();)
	{
		if (itr->mIsDelete == true)
		{
			itr = bullet->erase(itr);
		}
		else 
		{
			itr->Update();
			itr++;
		}
	}
}

//�ړ��������Đݒ�
void Enemy::setMove_Rand()
{
	Rand_Action = 0;

	/*
	//�Ⴄ�����������܂Ŗ������[�v
	while (true) {
		Rand_Action = GetRand(3);

		//���������������ĂȂ���
		if (Prev_Rand_Action != Rand_Action) {
			Prev_Rand_Action = Rand_Action;

			break;
		}
	}
	*/
}

//�ړ��ʂ����Z�b�g
void Enemy::setMovePixel()
{
	MovePixel = 0;
}


//���W���C��
void Enemy::FixPos(glm::ivec2 &pos)
{
	
	if (mVector == VECTOR_UP)
	{
		mPosition.y = pos.y + CELL + CELL / 2;
	}
	else if (mVector == VECTOR_DOWN)
	{
		mPosition.y = pos.y - (CELL / 2);
	}
	else if (mVector == VECTOR_LEFT)
	{
		mPosition.x = pos.x + (CELL + CELL / 2);
	}
	else if (mVector == VECTOR_RIGHT)
	{
		mPosition.x = pos.x - (CELL / 2);
	}

}

//�`��
void Enemy::Draw()
{
	DrawRotaGraph(mPosition.x, mPosition.y, 1.0, 0, mEnemy_sprite, true, false);

	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
	{
		itr->Draw();
	}


}


//�f�X�g���N�^
Enemy::~Enemy()
{

}
