#ifndef ___PLAYER_HPP_
#define ___PLAYER_HPP_


#include <iostream>
#include <vector>

#include "Actor.hpp"
#include "Bullet.hpp"
#include "Animation.hpp"






/*####################################################
* �v���C���[�N���X
######################################################*/

//�O���錾

class Bullet;
class Animaiton;
class BoxCollision;
class Enemy_Mng;
class MapChip;
struct ItemData;

class Player : public Actor
{
public:
	Player(Entry* e,int Player_Handle[8], int Player_Bullet_Handle,int Enemy_HitEffect_Handle[3], int Stage_HitEffect_Handle[3]);	//�R���X�g���N�^
	~Player();	//�f�X�g���N�^

	
	void Update();	//�X�V
	void Draw();	//�`��
	
	// �o���b�g
	void Bullet_Update();	//�X�V
	void Bullet_Draw();		//�`��

	//�v���C���[
	void Player_Update();	//�X�V
	void Player_Draw();		//�`��


	// #################### �擾�@�֌W

	bool getIsMenu();	//�V���b�v��ʂ��J���Ă��邩�ǂ����H	
	std::shared_ptr<std::vector<Bullet>> getBullet();	//�o���b�g
	float getSpeed();		//���x���擾

	// ####################�@�ݒ�@�֌W

	void set_Bulid(ItemData data);			//�X�e�[�^�X��ݒ�
	void FixPos(MapChip m);					//�����蔻��ō��W���C��
	void OffsetFixPos(glm::vec2  pos);		//���W�̃I�t�Z�b�g���C��
	void setIsMenu(bool b);					//���j���[���J�����ǂ����ݒ�
	void setSpeed(int speed);				//���x��ݒ�
	void setReset();						//���W�����Z�b�g

	void setWorldPosition(glm::vec2  pos);			//�X�e�[�W���W��ݒ�
	glm::vec2  getWorldPosition();	//�X�e�[�W���W���擾





	void ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy);	//�G�l�~�[�̃o���b�g�Ƃ̓����蔻��


	glm::vec2  stagePosition;	//�X�e�[�W���̍��W


	std::shared_ptr<BoxCollision> mCol;	//�����蔻��
private:

	

	//�X�v���C�g
	int playerSpriteUp[2];
	int playerSpriteLeft[2];
	int playerSpriteDown[2];
	int playerSpriteRight[2];

	int enemyHitEffectSprite[3];
	int stageHitEffectSprite[3];
	int playerBulletSprite;

	glm::vec2 minValue;	//�ŏ��l
	glm::vec2 maxValue;	//�ő�l

	glm::vec2  worldPosition;	//���[���h���W
	//mPosition //�X�e�[�W���W

//	glm::vec2  stagePosition;	//�X�e�[�W���̍��W
	std::shared_ptr<std::vector<Bullet>> bullet;	//�o���b�g

	bool mMenu;	//�V���b�v��ʂ��J�����ǂ����H

	Animation anim;


// �X�e�[�^�X

	float speed;			//���x



};


#endif


