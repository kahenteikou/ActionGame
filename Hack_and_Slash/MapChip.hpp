#ifndef ___MAPCHIP_HPP_
#define ___MAPCHIP_HPP_

#include "glm/glm.hpp"
#include <dxlib.h>
#include <iostream>

#include "Actor.hpp"
#include "Collision.hpp"

/*####################################################
* �}�b�v�`�b�v�N���X
*
* ����
* �X�e�[�W�̃}�b�v�`�b�v�̏��
######################################################*/

class MapChip : public Actor
{
public:
	MapChip(Tag t, glm::vec2  pos, glm::vec2  colsize, int handle);	//�R���X�g���N�^
	MapChip();	//�f�t�H���g�R���X�g���N�^

	~MapChip();																//�f�X�g���N�^


	glm::vec2  getWorldPosition();	//���[���h���W���擾
	void Update();	//�v�Z
	void Draw();	//�`��
	
	
	void setSize(glm::vec2  size);				//�T�C�Y��ݒ�
	void setHandle(int handle);					//�n���h����ݒ�



	//std::shared_ptr<BoxCollision> mCol;
	BoxCollision mCol;
private:
	int sprite;			//�X�v���C�g
	glm::vec2  worldPosition;	//���[���h���W

	glm::vec2 minValue;	//
	glm::vec2 maxValue;	//



};


#endif
