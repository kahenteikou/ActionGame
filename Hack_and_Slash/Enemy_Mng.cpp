#include "Enemy_Mng.hpp"
#include "Player.hpp"
#include "MapChip.hpp"


//�R���X�g���N�^
Enemy_Mng::Enemy_Mng(int Enemy_Handle, int Enemy_Bullet_Hanlde, int Stage_HitEffect_Handle[3], int Player_HitEffect_Handle[3])
{
	enemy = std::make_shared<std::vector<Enemy>>();	//�x�N�^�[�ϐ�
	enemy->clear();
	newStage = true;	//�V�����X�e�[�W�ɂȂ邩�ǂ����H

	enemySprite = Enemy_Handle;
	enemyBulletSprite = Enemy_Bullet_Hanlde;

	stageHitEffectSprite[0] = Stage_HitEffect_Handle[0];
	stageHitEffectSprite[1] = Stage_HitEffect_Handle[1];
	stageHitEffectSprite[2] = Stage_HitEffect_Handle[2];

	playerHitEffectSprite[0] = Player_HitEffect_Handle[0];
	playerHitEffectSprite[1] = Player_HitEffect_Handle[1];
	playerHitEffectSprite[2] = Player_HitEffect_Handle[2];
}


//�G�l�~�[��Ԃ�
std::shared_ptr<std::vector<Enemy>> Enemy_Mng::getEnemy()
{
	return enemy;
}



//�v���C���[�ƃo���b�g�Ƃ̓����蔻��
void Enemy_Mng::ColPlayer_Bullet(std::shared_ptr<Player> player)
{


}


//���݂̃G�l�~�[�̐��𓾂�
bool Enemy_Mng::getEnemyEmpty()
{
//	std::shared_ptr<std::vector<Enemy>> getEnemy();					//�G�l�~�[���

	return enemy->empty();

}

//�G�l�~�[���o��������
void Enemy_Mng::setEnemy(std::shared_ptr<Stage> stage)
{
	//�V�����X�e�[�W���ǂ����H	
	if (newStage == true)
	{
		int x, y;
		x = y = 0;
			enemy->push_back(Enemy(glm::vec2 (760,530),enemySprite, enemyBulletSprite, stageHitEffectSprite,playerHitEffectSprite));	//�ǉ�

		newStage = false;
	}
}




//�X�V
void Enemy_Mng::Update()
{

	//printf("Size: %d\n",getEnemyNum());



	for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
	{
		itr->Update();
	}
}

//�`��
void Enemy_Mng::Draw()
{
	for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
	{
		itr->Draw();
	}
}



//�f�X�g���N�^
Enemy_Mng::~Enemy_Mng()
{

}

