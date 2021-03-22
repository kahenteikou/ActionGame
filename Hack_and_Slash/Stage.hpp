#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"

#include "MapChip.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>

//�O���錾
class Player;
class MapChip;
class Bullet;
class Entry;
class Enemy;
class Enemy_Mng;

/*####################################################
* �X�e�[�W�`��
*
* ����
* �X�e�[�W��`�悷��
######################################################*/
class Stage
{
public:
	Stage(Entry *e,int Block_Handle, int Brick_Handle, int Shop_Handle);	//�R���X�g���N�^
	~Stage();			//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��
	
	std::shared_ptr<std::vector<std::vector<byte>>> getStage();

	//�����蔻�� �e��

	void ColPlayer(std::shared_ptr<Player> player);			//�v���C���[�Ƃ̓����蔻��
	void ColPlayer_Bullet(std::shared_ptr<Player> player);	//�v���C���[�̃o���b�g�Ƃ̓����蔻��

	void ColEnemy(std::shared_ptr<Enemy_Mng> enemy);		//�G�l�~�[�Ƃ̓����蔻��
	void ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy);	//�G�l�~�[�̃o���b�g�Ƃ̓����蔻��

	void setStage(std::shared_ptr<Enemy_Mng> enemy, std::shared_ptr<Player> player);		//�X�e�[�W��ǂݍ���


	void Scroll(std::shared_ptr<Player> player, std::shared_ptr<Enemy_Mng> enemy);	//��ʃX�N���[��

	

private:

	std::shared_ptr<std::vector<MapChip>> mStage;	//�}�b�v�f�[�^
	glm::vec2  mStageSize;			//��ʂɕ`�悷��Z����
	glm::vec2  mScroll_Vec;			//�X�N���[�����Ă������

	

	void LoadStage();	//�X�e�[�W��ǂݍ���
	std::shared_ptr<std::vector<std::vector<byte>>> Stage_Grid;	//�X�e�[�W
	glm::vec2  offsetCol;
	int col = 0;
	bool mGameStart;	//�Q�[�����n�܂��čŏ��̃t���[�������ǂ����H
	bool mIsShop;	//�V���b�v���I��������ǂ����H
	Entry* Owner;	//Entry�N���X

	std::vector<std::string> FileNameList;	//�X�e�[�W�t�@�C���̃��X�g

	//�T�C�Y�֌W
	glm::vec2  BlockSize;
	glm::vec2  BrickSize;
	glm::vec2  ShopSize;

	//�X�v���C�g
	int Block_sprite;	
	int Brick_sprite;
	int Shop_sprite;

};


#endif
	