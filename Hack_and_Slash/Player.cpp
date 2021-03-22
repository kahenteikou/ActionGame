#include "Player.hpp"

#include <iostream>
#include <vector>

#include "Entry.hpp"
#include "Input.hpp"
#include "Enemy_Mng.hpp"
#include "ItemID.hpp"
#include "MapChip.hpp"
#include "Collision.hpp"






//�R���X�g���N�^
Player::Player(Entry* e, int Player_Handle[8], int Player_Bullet_Handle, int Enemy_HitEffect_Handle[3], int Stage_HitEffect_Handle[3]) : Actor(e),anim(1)
{

	//�v���C���[���@�̃X�v���C�g
	playerSpriteUp[0] = Player_Handle[0];
	playerSpriteUp[1] = Player_Handle[1];

	playerSpriteLeft[0] = Player_Handle[2];
	playerSpriteLeft[1] = Player_Handle[3];

	playerSpriteDown[0] = Player_Handle[4];
	playerSpriteDown[1] = Player_Handle[5];

	playerSpriteRight[0] = Player_Handle[6];
	playerSpriteRight[1] = Player_Handle[7];



	playerBulletSprite = Player_Bullet_Handle;
	
	enemyHitEffectSprite[0] = Enemy_HitEffect_Handle[0];
	enemyHitEffectSprite[1] = Enemy_HitEffect_Handle[1];
	enemyHitEffectSprite[2] = Enemy_HitEffect_Handle[2];

	stageHitEffectSprite[0] = Stage_HitEffect_Handle[0];
	stageHitEffectSprite[1] = Stage_HitEffect_Handle[1];
	stageHitEffectSprite[2] = Stage_HitEffect_Handle[2];

	
	bullet = std::make_shared<std::vector<Bullet>>();

	speed = 0;
	


	//�������W
	
	//�X�N���[�����W
	position.x = SCREEN_WIDTH / 2;		
	position.y = SCREEN_HEIGHT / 2;

	//�X�e�[�W���W
	stagePosition.x = STAGE_WIDTH / 2;
	stagePosition.y = STAGE_HEIGHT / 50 * 20;


	worldPosition.x = position.x +120;	//���[���h���W
	worldPosition.y = position.y + 440;	//���[���h���W

	vector = VECTOR_UP;	//��������
	mMenu = false;		//�V���b�v���J�����ǂ����H


	//�����蔻��	
	mCol = std::make_shared<BoxCollision>();
	size.x = CELL;
	size.y = CELL;

	mCol->setTag(Tag::Player);
	mCol->setMin(&minValue);
	mCol->setMax(&maxValue);





}

//���W���C��
void Player::FixPos(MapChip m)
{

}

//���W���J�n�n�_�ɖ߂��B
void Player::setReset()
{
	//�X�N���[�����W
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;

	//�X�e�[�W���W
	stagePosition.x = STAGE_WIDTH / 2;
	stagePosition.y = STAGE_HEIGHT / 50 * 20;

	//���[���h���W
	worldPosition.x = position.x + 120;	
	worldPosition.y = position.y + 440;	

}

//�ʒu�̃I�t�Z�b�g���W���C��
void Player::OffsetFixPos(glm::vec2  pos)
{
#define OFFSET 20

	//�@��A��
	if (vector == VECTOR_UP || vector == VECTOR_DOWN)
	{
//
		//printf("VECTOR_UP , VECTOR_DOWN\n");
		//		printf("player: %d\n",position.x);
		//		printf("block: %d\n",pos.x);

		int PB = (position.x - (CELL / 2)) - pos.x;	//�ǂ��������邩�H

		if (PB > 0)
		{
//			printf("Right: %d\n", PB);

			int cp = CELL - PB; // �߂荞�ݗ�
//			printf("�߂肱�ݗʁ@cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("Right �C��\n");
				position.x = pos.x + CELL + (CELL / 2);
			}
		}
		else if (PB < 0)
		{
//			printf("Left: %d\n", PB);

			int cp = CELL - std::abs(PB); // �߂荞�ݗ�
//			printf("�߂肱�ݗʁ@cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("Left �C��\n");
				position.x = pos.x - CELL + (CELL / 2);
			}
		}
	}	
	else if (vector == VECTOR_LEFT || vector == VECTOR_RIGHT)
	{
		//���E

//		printf("VECTOR_LEFT , VECTOR_RIGHT\n");
		//		printf("player: %d\n",position.x);
		//		printf("block: %d\n",pos.x);

		int PB = (position.y - (CELL / 2)) - pos.y;	//�ǂ��������邩�H

		if (PB > 0)
		{
//			printf("down: %d\n", PB);

			int cp = CELL - PB; // �߂荞�ݗ�
//			printf("�߂肱�ݗʁ@cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("down �C��\n");
				position.y = pos.y + CELL + (CELL / 2);
			}
		}
		else if (PB < 0)
		{
//			printf("Up: %d\n", PB);

			int cp = CELL - std::abs(PB); // �߂荞�ݗ�
//			printf("�߂肱�ݗʁ@cp: %d\n", cp);

			if (cp < OFFSET)
			{
//				printf("Up �C��\n");
				position.y = pos.y - CELL + (CELL / 2);
			}
		}
	}
#undef OFFSET
}



//�G�l�~�[�̃o���b�g�Ƃ̓����蔻��
void Player::ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy)
{

}




//�o���b�g�@�X�V
void Player::Bullet_Update()
{
}


float Player::getSpeed()
{
	return speed;
}

//�X�V
void Player::Update()
{

	Player_Update();	//�v���C���[�X�V
	Bullet_Update();	//�o���b�g���X�V
}

//�X�e�[�^�X��ݒ�
void Player::set_Bulid(ItemData data)
{



}





//�v���C���[�@�X�V
void Player::Player_Update()
{

	
	speed = 10;
	//�L�[����
	if (owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
	//	printf("LEFT\n");
		vector = VECTOR_LEFT;	//����
		worldPosition.x += -speed;
	}
	else if (owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
	//	printf("RIGHT\n");
		vector = VECTOR_RIGHT;	//����
		worldPosition.x += speed;
	}
	else if (owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
	{
	//	printf("UP\n");
		vector = VECTOR_UP;	//����
		worldPosition.y += -speed;
	}
	else if (owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
	//	printf("DOWN\n");
		vector = VECTOR_DOWN;	//����
		worldPosition.y += speed;
	}
	else {
		speed = 0;
	}


	//���W�X�V
	position += vector * speed;

	minValue.x = position.x - (CELL / 2);
	minValue.y = position.y - (CELL / 2);

	maxValue.x = minValue.x + CELL;
	maxValue.y = minValue.y + CELL;

	//�����蔻��
	
}

//�`��
void Player::Draw()
{
	Bullet_Draw();	//�o���b�g�`��
	Player_Draw();	//�v���C���[�`��

	// �f�o�b�O�`��
	DrawFormatString(0,32,GetColor(255,255,255),"# Position: %d , %d  ",position.x,position.y);


}

//���x��ݒ�
void Player::setSpeed(int speed)
{
	speed = speed;
}



//�v���C���[�@�`��
void Player::Player_Draw()
{
#define ANIMETION_SPEED 5

//	printf("%d\n",anim.getClip_loop(ANIMETION_SPEED));

	//����
	if (vector == VECTOR_UP)
	{
		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteUp[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteUp[0], true, false);

		}
	}
	else if (vector == VECTOR_DOWN)
	{
		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteDown[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y,1.0, 0, playerSpriteDown[0], true, false);

		}

		//DrawRotaGraph(position.x, position.y, 1.0, PI, mPlayer_sprite, true, false);
	}
	else if (vector == VECTOR_LEFT)
	{
		

		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteLeft[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteLeft[0], true, false);

		}



		//DrawRotaGraph(position.x, position.y, 1.0, -(PI * 2) / 4, mPlayer_sprite, true, false);
	}
	else if (vector == VECTOR_RIGHT)
	{

		if (speed != 0)
		{
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteRight[anim.getClip_loop(ANIMETION_SPEED)], true, false);
		}
		else {
			DrawRotaGraph(position.x, position.y, 1.0, 0, playerSpriteRight[0], true, false);

		}




		//DrawRotaGraph(position.x, position.y, 1.0, (PI * 2) / 4, mPlayer_sprite, true, false);
	}

	//DrawPixel(position.x, position.y,GetColor(0,255,0));


	DrawCircle(maxValue.x, maxValue.y, 5, GetColor(0, 255, 0), true);
	DrawCircle(minValue.x, minValue.y, 5, GetColor(255, 0, 0), true);


#undef ANIMETION_SPEED
}


//�o���b�g�@�`��
void Player::Bullet_Draw()
{
	for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
	{		
		//printf("�o���b�g�X�V\n");
		itr->Draw();	//�o���b�g�`��		
	}
}



//�V���b�v��ʂ��J�����ǂ����H
bool Player::getIsMenu()
{
	return mMenu;
}

//�V���b�v��ʂ��J�����ǂ����H
void Player::setIsMenu(bool b)
{
	mMenu = b;
}

//�o���b�g���擾
std::shared_ptr<std::vector<Bullet>> Player::getBullet()
{
	return bullet;
}


//�X�e�[�W���W��ݒ�
void Player::setWorldPosition(glm::vec2  pos)
{
	worldPosition = pos;
}

//�X�e�[�W���W���擾
glm::vec2  Player::getWorldPosition()
{
	return worldPosition;
}



//�f�X�g���N�^
Player::~Player()
{

}
