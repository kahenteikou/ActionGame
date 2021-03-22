#ifndef ___UI_HPP_
#define ___UI_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"




//�E�C���h�E�̏��
typedef struct RectangleData
{
	glm::vec2  pos;		//���W
	glm::vec2  size;	//�T�C�Y
}RectangleData;

void GetRectangleData(RectangleData& data, glm::vec2  pos, glm::vec2  size);	//��`�T�C�Y��ݒ�


/*####################################################
* ���[�U�[�C���^�[�t�F�C�X
*
* ����
* �v���C��ʂ�UI�@������
######################################################*/

class UI
{
public:
	UI(glm::vec2  pos = glm::vec2 (0, 0), glm::vec2  vec = glm::vec2 (0, 0));	//�R���X�g���N�^
	~UI();	//�f�X�g���N�^

	void virtual Update() = 0;	//�v�Z
	void virtual Draw() = 0;	//�`��

	//�擾�֌W
	glm::vec2  getVector();		//����
	glm::vec2  getPosition();	//���W
protected:

	glm::vec2  mPosition;	//���W
	glm::vec2  mVector;		//����
	glm::vec2  mSize;		//�X�v���C�g�̃T�C�Y


};


#endif
