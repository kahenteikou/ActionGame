#include "Shop.hpp"



//コンストラクタ
Shop::Shop()
{

	//メインメニュー
	MainMenu = std::make_shared<Window>(MenuMove::Main,glm::ivec2(100, 100), glm::ivec2(500, 200), "ショップ　メニュー");
	MainMenu->AddItem(MenuMove::Buy_Menu,"買う");
	MainMenu->AddItem(MenuMove::Sell_Menu, "売る");
	MainMenu->AddItem(MenuMove::End,"戻る");

	//購入メニュー
	BuyMenu = std::make_shared<Window>(MenuMove::Buy_Menu,glm::ivec2(120,120),glm::ivec2(520,220),"購入　メニュー");
	BuyMenu->AddItem_Parameter(ItemData{ 1,0,0,  "回復" });
	BuyMenu->AddItem_Parameter(ItemData{ 0,1,0,  "防御" });
	BuyMenu->AddItem_Parameter(ItemData{0,0,1,  "攻撃" });
	
	//売るメニュー
	SellMenu = std::make_shared<Window>(MenuMove::Sell_Menu, glm::ivec2(120, 120), glm::ivec2(520, 220), "売る　メニュー");
	SellMenu->AddItem_Parameter(ItemData{ 1,0,0,  "回" });
	SellMenu->AddItem_Parameter(ItemData{ 1,0,0,  "回" });
	SellMenu->AddItem_Parameter(ItemData{ 1,0,0,  "回" });
	
	//ダイヤログ
	Dialogue = std::make_shared<Window>(MenuMove::Check, glm::ivec2(140, 140), glm::ivec2(540, 240), "確認");






	menu = MenuMove::Main;		//現在選択中のメニュー
	DrawMenu.push_back(menu);	//メニュー描画
	mIsNowShop = true;			//ウインドウを開いているかどうか？
}

//現在ショップ中かどうか？
bool Shop::getState()
{
	return mIsNowShop;
}

//更新
void Shop::Update(Player &player)
{
	switch (menu)
	{
		//メインメニュー
	case MenuMove::Main:
	{
		MainMenu->Update();	//更新

		//前のメニュー
		if (MainMenu->getChange() == MenuMove::End)
		{
			DrawMenu.erase(DrawMenu.begin() + DrawMenu.size() - 1);		//最後を削除
			menu = MainMenu->getChange();								//メニュー選択
			MainMenu->setChange(MenuMove::Invalid);						//選択を再初期化
		}
		else if (MainMenu->getChange() != MenuMove::Invalid)
		{
			menu = MainMenu->getChange();							//メニューを選択
			DrawMenu.push_back(MainMenu->getChange());				//描画メニューを設定
			MainMenu->setChange(MenuMove::Invalid);					//選択を再初期化
		}
	}break;

	//買うメニュー
	case MenuMove::Buy_Menu:
	{
		BuyMenu->Update();	//更新

		//前のメニュー
		if (BuyMenu->getChange() == MenuMove::Main)
		{
			DrawMenu.erase(DrawMenu.begin() + DrawMenu.size() - 1);	//最後を削除
			menu = BuyMenu->getChange();							//メニュー選択
			BuyMenu->setChange(MenuMove::Invalid);					//選択を再初期化
		}
		else if (BuyMenu->getChange() != MenuMove::Invalid)
		{
			menu = BuyMenu->getChange();							//メニュー選択
		}
	}break;

	//売るメニュー
	case MenuMove::Sell_Menu:
	{
		SellMenu->Update();	//更新

		//前のメニュー
		if (SellMenu->getChange() == MenuMove::Main)
		{
			DrawMenu.erase(DrawMenu.begin() + DrawMenu.size() - 1);	//最後を削除
			menu = SellMenu->getChange();							//メニュー選択
			SellMenu->setChange(MenuMove::Invalid);					//選択を再初期化
		}
		else if (SellMenu->getChange() != MenuMove::Invalid)
		{			
			menu = SellMenu->getChange();							//メニュー選択
		}
	}break;


		













	}

	//メニューを抜ける
	if (menu == MenuMove::End)
	{
		printf("あああ\n");
		mIsNowShop = false;
	}
}

//描画
void Shop::Draw()
{	


	for (std::vector<MenuMove>::iterator itr = DrawMenu.begin(); itr != DrawMenu.end(); itr++)
	{
		switch (*itr)
		{
			//メインメニュー
		case MenuMove::Main:
		{
//			printf("メインメニュー\n");
			MainMenu->Draw();

		}
		break;

		//購入メニュー
		case MenuMove::Buy_Menu:
		{
//			printf("購入メニュー\n");
			BuyMenu->Draw();
		}
		break;


		//売るメニュー
		case MenuMove::Sell_Menu:
		{
			//printf("売るメニュー\n");
			SellMenu->Draw();
		}
		break;
		};
	}







	/*
	switch (menu)
	{
		


	}
	*/
}

//デストラクタ
Shop::~Shop()
{

}
