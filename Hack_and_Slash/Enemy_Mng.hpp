#ifndef ___ENEMY_MNG_HPP_
#define ___ENEMY_MNG_HPP_

#include "Enemy.hpp"
#include <vector>
#include <iostream>


//�O���錾
class Enemy;
class Player;
class MapChip;
class Stage;
/*####################################################
* �G�l�~�[�Ǘ�
*
* ����
* �G�̈ړ��ƍs������Ǘ�����N���X
######################################################*/
class Enemy_Mng {

public:

	Enemy_Mng(int Enemy_Handle, int Enemy_Bullet_Hanlde, int Stage_HitEffect_Handle[3], int Player_HitEffect_Handle[3]);	//�R���X�g���N�^
	~Enemy_Mng();	//�f�X�g���N�^


	void Update();	//�X�V
	void Draw();	//�`��
	bool getEnemyEmpty();

	void setEnemy(std::shared_ptr<Stage> stage);	//�G�l�~�[���o��


	std::shared_ptr<std::vector<Enemy>> getEnemy();					//�G�l�~�[���
	
	void ColPlayer_Bullet(std::shared_ptr<Player> player);			//�v���C���[�ƃo���b�g�Ƃ̓����蔻��
	bool newStage;	//�V�����X�e�[�W���ǂ����H

private:
	
	int enemySprite;
	int enemyBulletSprite;
	int stageHitEffectSprite[3];
	int playerHitEffectSprite[3];



	std::shared_ptr<std::vector<Enemy>> enemy;	//�G�l�~�[�@�N���X


};

#endif;