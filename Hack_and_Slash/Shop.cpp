#include "Shop.hpp"

//コンストラクタ
Shop::Shop(Entry* e)
{

	Owner = e;	//Entry クラス

#define ITEM_COLOR GetColor(0, 0, 0)		//項目の色
#define TITLE_COLOR GetColor(255, 0, 0)		//タイトルの色
#define BACK_COLOR GetColor(255, 255, 255)	//ウインドウの背景色

	//メインメニュー
	MainMenu = std::make_shared<Window>(Owner,Window_Scene::Main,glm::vec2 (100,100),glm::vec2 (200,200));
	MainMenu->setBackColor(BACK_COLOR);
	MainMenu->setTitle("ショップメニュー", TITLE_COLOR);
	MainMenu->AddList_Down(Window_Scene::Buy_Menu, "Buy", 0, ITEM_COLOR);
	MainMenu->AddList_Down(Window_Scene::Sell_Menu, "Sell", 0, ITEM_COLOR);
	MainMenu->AddList_Down(Window_Scene::End, "もどる", 0, ITEM_COLOR);

	//買うメニュー
	BuyMenu = std::make_shared<Window>(Owner, Window_Scene::Buy_Menu, glm::vec2 (120, 120), glm::vec2 (220, 220));
	BuyMenu->setBackColor(BACK_COLOR);
	BuyMenu->setTitle("かう", TITLE_COLOR);
	BuyMenu->AddList_Down(Window_Scene::Buy_Conf, "Item_A", 1, ITEM_COLOR);
	BuyMenu->AddList_Down(Window_Scene::Buy_Conf, "Item_B", 2, ITEM_COLOR);
	BuyMenu->AddList_Down(Window_Scene::Main, "もどる", 0, ITEM_COLOR);

	//売るメニュー
	SellMenu = std::make_shared<Window>(Owner, Window_Scene::Sell_Menu, glm::vec2 (120, 120), glm::vec2 (220, 220));
	SellMenu->setBackColor(BACK_COLOR);

	//買う確認
	CheckMenu_Buy = std::make_shared<Window>(Owner, Window_Scene::Buy_Conf, glm::vec2 (140, 140), glm::vec2 (240, 240));
	CheckMenu_Buy->setBackColor(BACK_COLOR);
	CheckMenu_Buy->AddList_Down(Window_Scene::Yes, "Yes", 1, ITEM_COLOR);
	CheckMenu_Buy->AddList_Down(Window_Scene::Buy_Menu,"No", 1, ITEM_COLOR);



	mIsNowShop = true;			//ウインドウを開いているかどうか？
	Scene = Window_Scene::Main;	//最初のシーン
}

//現在ショップ中かどうか？
bool Shop::getState()
{
	return mIsNowShop;
}

//更新
void Shop::Update(Player& player)
{
	if (b == false)
	{

	}

	switch (Scene)
	{

		//メインシーン
	case Window_Scene::Main:
	{
		MainMenu->Update();	//更新
		if (MainMenu->getChangeScene() != Window_Scene::Invalid)
		{
			Scene = MainMenu->getChangeScene();	//
			MainMenu->Reset();	//シーン選択をリセット
		}
	}break;

	//買うシーン
	case Window_Scene::Buy_Menu:
	{
		BuyMenu->Update();	//更新
		if (BuyMenu->getChangeScene() != Window_Scene::Invalid)
		{
			Item_ID = BuyMenu->getItem();		//
			Scene = BuyMenu->getChangeScene();	//
			BuyMenu->Reset();	//シーン選択をリセット
		}
	}break;

	//買う確認
	case Window_Scene::Buy_Conf:
	{
	 	CheckMenu_Buy->Update();	//更新
		if (CheckMenu_Buy->getChangeScene() != Window_Scene::Invalid)
		{
			if (CheckMenu_Buy->getChangeScene() == Window_Scene::Yes)
			{

				//player.setItem_Bulid(3);



				Scene = Window_Scene::Buy_Menu;
				CheckMenu_Buy->Reset();	//シーン選択をリセット


				WaitTimer(1000);
			}
			else {


				Item_ID = CheckMenu_Buy->getItem();			//
				Scene = CheckMenu_Buy->getChangeScene();	//
				CheckMenu_Buy->Reset();	//シーン選択をリセット
			}
		}
	}break;
	}


	//ショップ終了
	if (Scene == Window_Scene::End)
	{
		mIsNowShop = false;
	}
}

//描画
void Shop::Draw()
{	
	
	switch (Scene)
	{
		//メインシーン
		case Window_Scene::Main:
		{
			MainMenu->Draw();
		}break;

		//買うシーン
		case Window_Scene::Buy_Menu:
		{
			BuyMenu->Draw();	
		}break;

		//売るシーン
		case Window_Scene::Sell_Menu:
		{
			SellMenu->Draw();
		}break;


		//売る確認
		case Window_Scene::Buy_Conf:
		{
			CheckMenu_Buy->Draw();
		}break;

		//売る確認
		case Window_Scene::Sell_Conf:
		{
			CheckMenu_Sell->Draw();
		}break;
	}
}

//デストラクタ
Shop::~Shop()
{

}
