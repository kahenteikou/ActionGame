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
	MapChip(Tag t, glm::ivec2 pos, glm::ivec2 size, int handle);	//�R���X�g���N�^
	MapChip();	//�f�t�H���g�R���X�g���N�^

	~MapChip();																//�f�X�g���N�^


	glm::ivec2 getWorldPosition();	//���[���h���W���擾
	void Update();	//�v�Z
	void Draw();	//�`��
	
	//void setObjectType(StageObjectType type);	//�I�u�W�F�N�g�^�C�v��ݒ�
	void setSize(glm::ivec2 size);				//�T�C�Y��ݒ�
	void setHandle(int handle);					//�n���h����ݒ�



	glm::ivec2 worldPosition;	//���[���h���W
	std::shared_ptr<BoxCollision> mCol;
private:
	int mSprite;			//�X�v���C�g

};


#endif
