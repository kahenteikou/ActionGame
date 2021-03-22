#include "Shop.hpp"

//�R���X�g���N�^
Shop::Shop(Entry* e)
{

	Owner = e;	//Entry �N���X

#define ITEM_COLOR GetColor(0, 0, 0)		//���ڂ̐F
#define TITLE_COLOR GetColor(255, 0, 0)		//�^�C�g���̐F
#define BACK_COLOR GetColor(255, 255, 255)	//�E�C���h�E�̔w�i�F

	//���C�����j���[
	MainMenu = std::make_shared<Window>(Owner,Window_Scene::Main,glm::vec2 (100,100),glm::vec2 (200,200));
	MainMenu->setBackColor(BACK_COLOR);
	MainMenu->setTitle("�V���b�v���j���[", TITLE_COLOR);
	MainMenu->AddList_Down(Window_Scene::Buy_Menu, "Buy", 0, ITEM_COLOR);
	MainMenu->AddList_Down(Window_Scene::Sell_Menu, "Sell", 0, ITEM_COLOR);
	MainMenu->AddList_Down(Window_Scene::End, "���ǂ�", 0, ITEM_COLOR);

	//�������j���[
	BuyMenu = std::make_shared<Window>(Owner, Window_Scene::Buy_Menu, glm::vec2 (120, 120), glm::vec2 (220, 220));
	BuyMenu->setBackColor(BACK_COLOR);
	BuyMenu->setTitle("����", TITLE_COLOR);
	BuyMenu->AddList_Down(Window_Scene::Buy_Conf, "Item_A", 1, ITEM_COLOR);
	BuyMenu->AddList_Down(Window_Scene::Buy_Conf, "Item_B", 2, ITEM_COLOR);
	BuyMenu->AddList_Down(Window_Scene::Main, "���ǂ�", 0, ITEM_COLOR);

	//���郁�j���[
	SellMenu = std::make_shared<Window>(Owner, Window_Scene::Sell_Menu, glm::vec2 (120, 120), glm::vec2 (220, 220));
	SellMenu->setBackColor(BACK_COLOR);

	//�����m�F
	CheckMenu_Buy = std::make_shared<Window>(Owner, Window_Scene::Buy_Conf, glm::vec2 (140, 140), glm::vec2 (240, 240));
	CheckMenu_Buy->setBackColor(BACK_COLOR);
	CheckMenu_Buy->AddList_Down(Window_Scene::Yes, "Yes", 1, ITEM_COLOR);
	CheckMenu_Buy->AddList_Down(Window_Scene::Buy_Menu,"No", 1, ITEM_COLOR);



	mIsNowShop = true;			//�E�C���h�E���J���Ă��邩�ǂ����H
	Scene = Window_Scene::Main;	//�ŏ��̃V�[��
}

//���݃V���b�v�����ǂ����H
bool Shop::getState()
{
	return mIsNowShop;
}

//�X�V
void Shop::Update(Player& player)
{
	if (b == false)
	{

	}

	switch (Scene)
	{

		//���C���V�[��
	case Window_Scene::Main:
	{
		MainMenu->Update();	//�X�V
		if (MainMenu->getChangeScene() != Window_Scene::Invalid)
		{
			Scene = MainMenu->getChangeScene();	//
			MainMenu->Reset();	//�V�[���I�������Z�b�g
		}
	}break;

	//�����V�[��
	case Window_Scene::Buy_Menu:
	{
		BuyMenu->Update();	//�X�V
		if (BuyMenu->getChangeScene() != Window_Scene::Invalid)
		{
			Item_ID = BuyMenu->getItem();		//
			Scene = BuyMenu->getChangeScene();	//
			BuyMenu->Reset();	//�V�[���I�������Z�b�g
		}
	}break;

	//�����m�F
	case Window_Scene::Buy_Conf:
	{
	 	CheckMenu_Buy->Update();	//�X�V
		if (CheckMenu_Buy->getChangeScene() != Window_Scene::Invalid)
		{
			if (CheckMenu_Buy->getChangeScene() == Window_Scene::Yes)
			{

				//player.setItem_Bulid(3);



				Scene = Window_Scene::Buy_Menu;
				CheckMenu_Buy->Reset();	//�V�[���I�������Z�b�g


				WaitTimer(1000);
			}
			else {


				Item_ID = CheckMenu_Buy->getItem();			//
				Scene = CheckMenu_Buy->getChangeScene();	//
				CheckMenu_Buy->Reset();	//�V�[���I�������Z�b�g
			}
		}
	}break;
	}


	//�V���b�v�I��
	if (Scene == Window_Scene::End)
	{
		mIsNowShop = false;
	}
}

//�`��
void Shop::Draw()
{	
	
	switch (Scene)
	{
		//���C���V�[��
		case Window_Scene::Main:
		{
			MainMenu->Draw();
		}break;

		//�����V�[��
		case Window_Scene::Buy_Menu:
		{
			BuyMenu->Draw();	
		}break;

		//����V�[��
		case Window_Scene::Sell_Menu:
		{
			SellMenu->Draw();
		}break;


		//����m�F
		case Window_Scene::Buy_Conf:
		{
			CheckMenu_Buy->Draw();
		}break;

		//����m�F
		case Window_Scene::Sell_Conf:
		{
			CheckMenu_Sell->Draw();
		}break;
	}
}

//�f�X�g���N�^
Shop::~Shop()
{

}
