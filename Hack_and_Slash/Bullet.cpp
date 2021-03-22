#include "Bullet.hpp"

//�R���X�g���N�^
Bullet::Bullet(glm::vec2 pos , glm::vec2 vec, int handle,int MapEffect_Handle[3], int EnemyEffect_Handle[3]) : Actor(nullptr,pos,vec),anim(2)
{
	//GetGraphSize(handle,&(int)size.x, &(int)size.y);	//�X�v���C�g�̑傫��

	speed = 8;		//�o���b�g�̑��x
	sprite = handle;	//�X�v���C�g
	
	//�}�b�v�ƃq�b�g�������̃G�t�F�N�g
	mapEffectSprite[0] = MapEffect_Handle[0];
	mapEffectSprite[1] = MapEffect_Handle[1];
	mapEffectSprite[2] = MapEffect_Handle[2];

	//�G�l�~�[�ƃq�b�g�������̃G�t�F�N�g
	enemyEffectSprite[0] = EnemyEffect_Handle[0];
	enemyEffectSprite[1] = EnemyEffect_Handle[1];
	enemyEffectSprite[2] = EnemyEffect_Handle[2];
	

	//����֌W��������
	isMapHIt = false;
	isEenemyHit = false;
	isDelete = false;
}



//���W���C��
void Bullet::FixPos(glm::vec2 pos)
{
	if (vector == VECTOR_UP)
	{
		position.y = pos.y + (CELL);
	}
	else if (vector == VECTOR_DOWN)
	{
		position.y = pos.y;
	}
	else if (vector == VECTOR_LEFT)
	{
		position.x = pos.x + (CELL);
	}
	else if (vector == VECTOR_RIGHT)
	{
		position.x = pos.x;		
	}
}




//�X�V
void Bullet::Update()
{
}

//�`��
void Bullet::Draw()
{
	//�o���b�g���ړ�
	
	if (isMapHIt == false && isEenemyHit == false) 
	{
		//�`�����
		if (vector == VECTOR_UP)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, sprite, true, false);
		}
		else if (vector == VECTOR_DOWN)
		{
			DrawRotaGraph(position.x, position.y, 1.0, PI, sprite, true, false);
		}
		else if (vector == VECTOR_LEFT)
		{
			DrawRotaGraph(position.x, position.y, 1.0, -(PI * 2) / 4, sprite, true, true);
		}
		else if (vector == VECTOR_RIGHT)
		{
			DrawRotaGraph(position.x, position.y, 1.0, (PI * 2) / 4, sprite, true, true);
		}

	}
	else if (isMapHIt == true) 
	{
		//�}�b�v�@�q�b�g�G�t�F�N�g

		int num = 0;
		if (anim.getClip(num, BULLET_EFFECT_SPEED) == false) {
			DrawRotaGraph(position.x, position.y, 1.0, 0, mapEffectSprite[num], true, false);
		}
		else
		{
			isDelete = true;
		}
	}
	else if (isEenemyHit == true)
	{
		//�G�l�~�[�@�q�b�g�G�t�F�N�g

		int num = 0;
		if (anim.getClip(num, BULLET_EFFECT_SPEED) == false) {
			DrawRotaGraph(position.x, position.y, 1.0, 0, enemyEffectSprite[num], true, false);
		}
		else
		{
			isDelete = true;
		}
	}






}

//�f�X�g���N�^
Bullet::~Bullet()
{

}
