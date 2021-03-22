#include "Enemy.hpp"


//�R���X�g���N�^
Enemy::Enemy(glm::ivec2 pos ,int Enemy_sprite, int Enemy_Bullet_sprite, int Stage_HitEffect_sprite[3], int Player_HitEffect_sprite[3]) : Actor(nullptr)
{
	position = pos;	//�������W

	enemySprite = Enemy_sprite;	//�G�l�~�[
	enemy_Bullet_sprite = Enemy_Bullet_sprite;	//�o���b�g

	//�X�e�[�W�@�q�b�g�G�t�F�N�g
	stageHitEffect_sprite[0] = Stage_HitEffect_sprite[0];
	stageHitEffect_sprite[1] = Stage_HitEffect_sprite[1];
	stageHitEffect_sprite[2] = Stage_HitEffect_sprite[2];
	
	//�v���C���[�@�q�b�g�t�F�N�g
	playerHitEffect_sprite[0] = Player_HitEffect_sprite[0];
	playerHitEffect_sprite[1] = Player_HitEffect_sprite[1];
	playerHitEffect_sprite[2] = Player_HitEffect_sprite[2];


	isLefe = true;	//�����Ă��邩�ǂ����H


	randMove = GetRand(3);		//����
	//randMove = 0;		//����
	//randMove = 3; //GetRand(3);//����

	//Prev_randMove = randMove;	//�O�̗���
	moveValue = 0;					//�ړ�������

	
//	speed = 10; //�X�s�[�h
	speed = 2; //�X�s�[�h

	//�����蔻��
	


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
	isLefe = false;
}

//�j�󂳂ꂽ���ǂ����H		
bool Enemy::getIsDestroy()
{
	return isLefe;
}


//�X�V
void Enemy::Update()
{
	
	randAttack = GetRand(50); //�U���p�x

	//�U��
	if (randAttack == 1)
	{
		//	printf("�G�l�~�[�U��\n");
		bullet->push_back(Bullet(position, vector, enemy_Bullet_sprite, stageHitEffect_sprite,playerHitEffect_sprite));
	}

	//����
	if (randMove == 0)
	{
		vector = VECTOR_UP;
	}
	else if (randMove == 1)
	{
		vector = VECTOR_RIGHT;
	}
	else if (randMove == 2)
	{
		vector = VECTOR_DOWN;
	}
	else if (randMove == 3)
	{
		vector = VECTOR_LEFT;
	}
	
	//randAttack = GetRand(50); //�U���p�x

	


	//�ړ�	
	moveValue += speed;	//�ړ��ʂɉ��Z
	if (moveValue > CELL * 2)
	{
		setMove_Rand();
		moveValue = 0;	//�ړ��ʂ����Z�b�g
	}
	


	//�ړ�
	position.x += vector.x * speed;
	position.y += vector.y * speed;


	





	
}

//�ړ��������Đݒ�
void Enemy::setMove_Rand()
{
	randMove = GetRand(3);

	/*
	//�Ⴄ�����������܂Ŗ������[�v
	while (true) {
		randMove = GetRand(3);

		//���������������ĂȂ���
		if (Prev_randMove != randMove) {
			Prev_randMove = randMove;

			break;
		}
	}
	*/
}

//�ړ��ʂ����Z�b�g
void Enemy::setMovePixel()
{
	moveValue = 0;
}


//���W���C��
void Enemy::FixPos(glm::ivec2 &pos)
{
	
	if (vector == VECTOR_UP)
	{
		position.y = pos.y + CELL + CELL / 2;
	}
	else if (vector == VECTOR_DOWN)
	{
		position.y = pos.y - (CELL / 2);
	}
	else if (vector == VECTOR_LEFT)
	{
		position.x = pos.x + (CELL + CELL / 2);
	}
	else if (vector == VECTOR_RIGHT)
	{
		position.x = pos.x - (CELL / 2);
	}

}

//�`��
void Enemy::Draw()
{
	DrawRotaGraph(position.x, position.y, 1.0, 0, enemySprite, true, false);

	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
	{
		itr->Draw();
	}


}


//�f�X�g���N�^
Enemy::~Enemy()
{

}
