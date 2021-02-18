#include "Window.hpp"

//コンストラクタ
Window::Window(MenuMove m,glm::ivec2 pos, glm::ivec2 size, std::string str)
{
	Menu = m;	//メニュー推移

	Move = MenuMove::Invalid;	//現在選択中

	mInput = std::make_shared<Input>();	//キー入力

	WindowTitle = str;	//タイトル
	window.pos = pos;	//座標
	window.size = size;	//大きさ

	ItemPos = window.pos;	//項目の座標
	Cursor = 0;				//カーソル
}

//シーンを指定
void Window::setChange(MenuMove m)
{
	Move = m;
}

//ゲーム内アイテムを設定
void Window::AddItem_Parameter(ItemData data)
{
	glm::ivec2 pos;
	//座標を修正
	pos.y += 20;
	pos.x = window.pos.x + 50;
	
	

	data.pos = pos;
	Game_Item.push_back(data);

}





//ウインドウに項目を追加
void Window::AddItem(MenuMove m,std::string name)
{
	Window_Item item;

	item.name = name;	//名前

	//座標を修正
	ItemPos.y += 20;
	ItemPos.x = window.pos.x + 50;
	item.pos = ItemPos;
	
	item.menu = m;

	Item.push_back(item);
}

//メニューを繰り替え
MenuMove Window::getChange()
{
	return Move;
}



//計算
void Window::Update()
{
	mInput->Update(); // キー入力更新

	//キー入力	
	if (mInput->getKeyDown(KEY_INPUT_UP) == true)
	{
		Cursor += -1;
		if (Cursor < 0)
		{
			Cursor = 0;
		}

	}
	else if (mInput->getKeyDown(KEY_INPUT_DOWN) == true)
	{
		Cursor += 1;
		if (Cursor > Item.size() - 1)
		{
			Cursor = (int)Item.size() - 1;
		}

	}
	else if (mInput->getKeyDown(KEY_INPUT_SPACE) == true)
	{
		//決定ボタン
		Move = Item.at(Cursor).menu;

	}	
}


//描画
void Window::Draw()
{
	DrawBox(window.pos.x, window.pos.y, window.size.x, window.size.y,GetColor(100,100,0), true);	//背景
	DrawFormatString(window.pos.x, window.pos.y, GetColor(0, 255, 0),"%s",WindowTitle.c_str());		//タイトル




	if (Item.size() > 0) {
		//項目を表示
		for (std::vector<Window_Item>::iterator itr = Item.begin(); itr != Item.end(); itr++)
		{

			Window_Item item = *itr;
			if (Item.at(Cursor).pos == item.pos)
			{
				//カーソルの場所
				DrawFormatString(itr->pos.x, itr->pos.y, GetColor(0, 0, 0), "->");		//カーソル
				DrawFormatString(itr->pos.x + 20, itr->pos.y, GetColor(0, 255, 0), "%s", itr->name.c_str());	//項目

			}
			else {
				DrawFormatString(itr->pos.x, itr->pos.y, GetColor(0, 255, 0), "%s", itr->name.c_str());	//項目
			}
		}

	}
	else if (Game_Item.size() > 0)
	{
		//項目を表示
		for (std::vector<ItemData>::iterator itr = Game_Item.begin(); itr != Game_Item.end(); itr++)
		{

			ItemData item = *itr;
			if (Game_Item.at(Cursor).pos == item.pos)
			{
				//カーソルの場所
				DrawFormatString(itr->pos.x, itr->pos.y, GetColor(0, 0, 0), "->");		//カーソル
				DrawFormatString(itr->pos.x + 20, itr->pos.y, GetColor(0, 255, 0), "%s", itr->name.c_str());	//項目

			}
			else {
				DrawFormatString(itr->pos.x, itr->pos.y, GetColor(0, 255, 0), "%s", itr->name.c_str());	//項目
			}
		}

	}




}



//デストラクタ
Window::~Window()
{

}


