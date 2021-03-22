#ifndef ___BULLET_HPP_
#define ___BULLET_HPP_

#include "DxLib.h"
#include "glm/glm.hpp"
#include "Actor.hpp"
#include "Entry.hpp"
#include "Collision.hpp"

#include "Animation.hpp"


#define BULLET_EFFECT_SPEED  30//�q�b�g�G�t�F�N�g�̍Đ����x

/*####################################################
* �o���b�g(�e)
*
* ����
* vector�ŊǗ�
* �v���C���[�̍U��
* 
######################################################*/

class Bullet : public Actor
{
public:

	/*�R���X�g���N�^����
	* 
	*�@���W
	* ����
	* �o���b�g�̃n���h��
	* �}�b�v�Ƀq�b�g�����Ƃ��̃G�t�F�N�g
	* �G�l�~�[�ƃq�b�g�������̃G�t�F�N�g 
	*/


	Bullet(glm::ivec2 pos, glm::ivec2 vec, int handle, int MapEffect_Handle[3], int EnemyEffect_Handle[3]);	//�R���X�g���N�^
	~Bullet();																								//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��

	void FixPos(glm::ivec2 pos);	//���W���C��

	BoxCollision mCol;	//�����蔻��

	
private:
	Animation anim;			//�A�j���[�V�����N���X
	int sprite;			//�X�v���C�g
	bool isMapHIt;			//�}�b�v�ƃq�b�g�������ǂ����H
	bool isEenemyHit;		//�G�l�~�[�ƃq�b�g�������ǂ����H
	bool isDelete;			//�폜���邩�ǂ����H

	int mapEffectSprite[3];	// �}�b�v�q�b�g�̃G�t�F�N�g�X�v���C�g
	int enemyEffectSprite[3];	// �G�l�~�[�q�b�g�̃G�t�F�N�g�X�v���C�g

	int speed;				//�o���b�g�̑��x
	
};


#endif






