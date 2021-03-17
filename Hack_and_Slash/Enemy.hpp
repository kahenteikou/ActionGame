#ifndef ___ENEMY_HPP_
#define ___ENEMY_HPP_

#include <iostream>
#include <vector>

#include "Actor.hpp"
#include "Collision.hpp"
#include "Entry.hpp"
#include "Entry.hpp"
#include "Input.hpp"
#include "Bullet.hpp"
#include "Collision.hpp"
#include "ItemID.hpp"



class Entry;
class Bullet;
/*####################################################
* �G�l�~�[
* 
* ����
* �G�̈ړ��ƍs������N���X
######################################################*/

class Enemy :public Actor
{
public:

	/*�R���X�g���N�^����
	* 
	* �G�l�~�[�X�v���C�g
	* �o���b�g�X�v���C�g
	* �X�e�[�W�q�b�g�G�t�F�N�g
	* �v���C���[�q�b�g�G�t�F�N�g 
	*/


	Enemy(glm::ivec2 pos, int Enemy_sprite,int Enemy_Bullet_sprite,int Stage_HitEffect_sprite[3],int Player_HitEffect_sprite[3]);	//�R���X�g���N�^
	~Enemy();			//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��

	// ### �ݒ�@�֌W
	void FixPos(glm::ivec2 &pos);	//���W���C��
	void setMove_Rand();			//�ړ��������Đݒ�
	void setMovePixel();			//�ړ��ʂ����Z�b�g

	std::shared_ptr<std::vector<Bullet>> getBullet();
	
	void Destroy();		//�j�󂷂�B
	bool getIsDestroy();//�j�󂳂ꂽ���ǂ����H		

	Box_Collision mCol;	//�����蔻��
private:

	//�X�v���C�g
	int mEnemy_sprite;					//�G�l�~�[
	int mEnemy_Bullet_sprite;			//�o���b�g
	int mStage_HitEffect_sprite[3];		//�X�e�[�W�@�q�b�g�G�t�F�N�g
	int mPlayer_HitEffect_sprite[3];	//�v���C���[�@�q�b�g�G�t�F�N�g




	int Rand_Action;		//�s���̗���
	int Rand_Attack;		//�U�����邩�ǂ����H

	int Prev_Rand_Action;	//�O�̍s���̗���
	int mSpeed;				//�ړ����x
	int MovePixel;			//�ړ���


	bool islife; //�����Ă��邩�ǂ����H

	std::shared_ptr<std::vector<Bullet>> bullet;	//�o���b�g




};


#endif

