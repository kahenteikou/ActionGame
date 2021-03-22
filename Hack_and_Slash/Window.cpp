#include "Window.hpp"

//�R���X�g���N�^
Window::Window(Entry * e,Window_Scene s, glm::vec2  pos, glm::vec2  size) : Actor(e)
{
	Scene = s;							//�E�C���h�E���
	Move_Scene = Window_Scene::Invalid;	//�ړ�����V�[��
	Cursor = 0;	//�J�[�\��


	setPosition(pos);								//���W
	setSize(size);									//�傫��
	BackGroundColor = GetColor(255,255,255);		//����@�w�i�F
	setTitle("���ݒ�^�C�g��",GetColor(0, 0, 0));		//����@�^�C�g��

	ItemPos = pos;
}


// ################## �ݒ�@�֌W


//�^�C�g��
void Window::setTitle(std::string name,unsigned int c)
{
	Title = name;	//�\������
	TitleColor = c;	//�`��F
}

//���W
void Window::setPosition(glm::vec2  pos)	
{
	position = pos;
}

//�T�C�Y
void Window::setSize(glm::vec2  size)	
{
	size.x = position.x + size.x;
	size.y = position.y + size.y;
}

//�w�i�F
void Window::setBackColor(unsigned int c)		
{
	BackGroundColor = c;
}

//�V�[���𐄈�
Window_Scene Window::getChangeScene()
{

	return Move_Scene;
}

void Window::Reset()
{
	ID = 0;
	Move_Scene = Window_Scene::Invalid;
}



/* �E�C���h�E�ɍ��ڂ�ǉ�
* 
* ����
* 
* ����
* �V�[���̐���
* ���O
* �A�C�e��ID
* �`��F
*/
void Window::AddList_Down(Window_Scene s,std::string name,unsigned char num,unsigned int c)
{
	//printf("������");
	List_Item item;

	item.name = name;	//���O
	item.Color = c;		//�J���[

	
	//���W
	ItemPos.y += 20;
	ItemPos.x = position.x + 50;
	item.pos = ItemPos;
	

	//�w�i�F�̕`��̑傫��
	item.size.x = GetDrawStringWidth(name.c_str(), (int)strlen(name.c_str())) + ItemPos.x + 50;
	item.size.y = ItemPos.y;



	item.winScene = s;	//�E�C���h�E�V�[��

	item.ID = num;	//�A�C�e��ID

	lists.push_back(item);
}

unsigned char Window::getItem()
{
	return ID;
}

//�v�Z
void Window::Update()
{
	//mInput->Update(); // �L�[���͍X�V

	//�L�[����	
	if (owner->InputKey->getKeyDown(KEY_INPUT_UP) == true)
	{
		Cursor += -1;
		if (Cursor < 0)
		{
			Cursor = 0;
		}
	}
	else if (owner->InputKey->getKeyDown(KEY_INPUT_DOWN) == true)
	{
		Cursor += 1;
		if (Cursor > lists.size() - 1)
		{
			Cursor = (int)lists.size() - 1;
		}
	}
	else if (owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
	{	
		Move_Scene = lists.at(Cursor).winScene;	//�V�[������
		ID = lists.at(Cursor).ID;	//�A�C�e��ID
	}	
}

//�`��
void Window::Draw()
{
#define FRAME_COLOR GetColor(0,100,0)	//�t���[���̐F
#define CURSOR_COLOR GetColor(0,0,0)	//�J�[�\���̐F

	DrawBox(position.x, position.y, size.x, size.y, BackGroundColor, true);	//�w�i

	DrawBox(position.x, position.y, size.x, size.y, FRAME_COLOR, false);	//�g
	DrawBox(position.x - 1, position.y - 1, size.x + 1, size.y + 1, FRAME_COLOR, false);	//�g
	DrawBox(position.x - 2, position.y - 2, size.x + 2, size.y + 2, FRAME_COLOR, false);	//�g
	DrawBox(position.x - 3, position.y - 3, size.x + 3, size.y + 3, FRAME_COLOR, false);	//�g
	DrawBox(position.x - 4, position.y - 4, size.x + 4, size.y + 4, FRAME_COLOR, false);	//�g
	

	DrawFormatString(position.x + 2, position.y + 4, TitleColor,"%s",Title.c_str());	//�^�C�g��


	//���ڂ�\��
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		List_Item item = *itr;
		if (lists.at(Cursor).pos == item.pos)
		{

			//�J�[�\���̏ꏊ
			DrawFormatString(itr->pos.x - 50, itr->pos.y, CURSOR_COLOR, "-->");		//�J�[�\��
			DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + 100, itr->pos.y + 16, GetColor(0,100,0), true);	//�w�i

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//����
		}
		else {

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//����
		}
	}
}


//�f�X�g���N�^
Window::~Window()
{

}


