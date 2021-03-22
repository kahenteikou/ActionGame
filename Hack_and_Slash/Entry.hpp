#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_


#include "Game_Scene.hpp"
#include "Input.hpp"
#include <iostream>
#include <locale.h>
#include <Random>


#define CELL ((int)48)	//�Z��

//��ʃT�C�Y
#define SCREEN_WIDTH ((int)16 * 80)
#define SCREEN_HEIGHT ((int)9 * 80)

//�X�e�[�W
#define STAGE_WIDTH ((int)50 * CELL)
#define STAGE_HEIGHT ((int)50 * CELL)



//����
#define VECTOR_UP glm::vec2 (0,-1)
#define VECTOR_DOWN glm::vec2 (0,1)
#define VECTOR_LEFT glm::vec2 (-1,0)
#define VECTOR_RIGHT glm::vec2 (1,0)

#define PI ((float)3.14159265359)	//PI



// �V�[���̎��
typedef  enum class Scene_Type
{
	Title,		//�^�C�g��
	Game,		//���C���Q�[��
	GameOver,	//�Q�[���I�[�o�[


	Menu,		//���j���[
	Pause,		//�ꎞ��~
}Scene_Type;


/*####################################################
* �V�[������
* 
* ����
* �V�[���̐��ڂ��s��
######################################################*/
class Game_Scene;
class Entry
{
public:

	Entry();	//�R���X�g���N�^
	~Entry();	//�f�X�g���N�^

	void Update();	//�v�Z
	void Draw();	//�`��
	int GetRand(int start, int end);	//�������擾
	
	int LoadSprite(const char* FileName);				//�X�v���C�g�����[�h


	std::shared_ptr<Input> InputKey;

private:

	std::shared_ptr<Game_Scene> game;

	Scene_Type type;

};


#endif

