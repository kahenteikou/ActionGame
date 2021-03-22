#ifndef ___ACTOR_HPP_
#define ___ACTOR_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"

//#include "Entry.hpp"
class Entry;
/*####################################################
* �A�N�^�[
* 
* ����
* �S�ẴQ�[���I�u�W�F�N�g�͂�����p������B
######################################################*/

class Actor
{
public:
	Actor(Entry* e,glm::vec2 pos = glm::vec2(0, 0), glm::vec2 vec = glm::vec2(0, 0));	//�R���X�g���N�^
	~Actor();	//�f�X�g���N�^

	void virtual Update() = 0;	//�v�Z
	void virtual Draw() = 0;	//�`��

	//�擾�@�֌W
	glm::vec2 getVector();		//����
	glm::vec2 getPosition();	//���W

	//�ݒ�@�֌W
	void setPosition(glm::vec2 pos);

protected:

	glm::vec2 position;	//���W
	glm::vec2 vector;	//����
	glm::vec2 size;		//�X�v���C�g�̃T�C�Y

	Entry* owner;			//Entry �N���X

};


#endif
