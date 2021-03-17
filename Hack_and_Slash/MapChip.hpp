#ifndef ___MAPCHIP_HPP_
#define ___MAPCHIP_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"

#include "Entry.hpp"
#include "Actor.hpp"
#include "Collision.hpp"

/*####################################################
* �}�b�v�`�b�v�N���X
*
* ����
* �X�e�[�W�̃}�b�v�`�b�v�̏��
######################################################*/

//�X�e�[�W�̃I�u�W�F�N�g�̎��
enum class StageObjectType
{
	None,


	Enemy,
	Player,
	Item,
	
	Block,
	Brick,

	Shop,

};

class MapChip : public Actor
{
public:
	MapChip(StageObjectType t, glm::ivec2 pos, glm::ivec2 size, int handle);	//�R���X�g���N�^
	MapChip();	//�f�t�H���g�R���X�g���N�^

	~MapChip();																//�f�X�g���N�^

	void Update();	//�v�Z
	void Draw();	//�`��
	
	void setObjectType(StageObjectType type);	//�I�u�W�F�N�g�^�C�v��ݒ�
	void setSize(glm::ivec2 size);				//�T�C�Y��ݒ�
	void setHandle(int handle);					//�n���h����ݒ�


	int HP;
	std::shared_ptr<Box_Collision> mCol;
private:
	int mSprite;			//�X�v���C�g

};


#endif
