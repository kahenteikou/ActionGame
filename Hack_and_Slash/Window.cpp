#include "Window.hpp"

//コンストラクタ
Window::Window(Entry * e,Window_Scene s, glm::vec2  pos, glm::vec2  size) : Actor(e)
{
	Scene = s;							//ウインドウ種別
	Move_Scene = Window_Scene::Invalid;	//移動するシーン
	Cursor = 0;	//カーソル


	setPosition(pos);								//座標
	setSize(size);									//大きさ
	BackGroundColor = GetColor(255,255,255);		//既定　背景色
	setTitle("未設定タイトル",GetColor(0, 0, 0));		//既定　タイトル

	ItemPos = pos;
}


// ################## 設定　関係


//タイトル
void Window::setTitle(std::string name,unsigned int c)
{
	Title = name;	//表示文字
	TitleColor = c;	//描画色
}

//座標
void Window::setPosition(glm::vec2  pos)	
{
	position = pos;
}

//サイズ
void Window::setSize(glm::vec2  size)	
{
	size.x = position.x + size.x;
	size.y = position.y + size.y;
}

//背景色
void Window::setBackColor(unsigned int c)		
{
	BackGroundColor = c;
}

//シーンを推移
Window_Scene Window::getChangeScene()
{

	return Move_Scene;
}

void Window::Reset()
{
	ID = 0;
	Move_Scene = Window_Scene::Invalid;
}



/* ウインドウに項目を追加
* 
* 説明
* 
* 引数
* シーンの推移
* 名前
* アイテムID
* 描画色
*/
void Window::AddList_Down(Window_Scene s,std::string name,unsigned char num,unsigned int c)
{
	//printf("あああ");
	List_Item item;

	item.name = name;	//名前
	item.Color = c;		//カラー

	
	//座標
	ItemPos.y += 20;
	ItemPos.x = position.x + 50;
	item.pos = ItemPos;
	

	//背景色の描画の大きさ
	item.size.x = GetDrawStringWidth(name.c_str(), (int)strlen(name.c_str())) + ItemPos.x + 50;
	item.size.y = ItemPos.y;



	item.winScene = s;	//ウインドウシーン

	item.ID = num;	//アイテムID

	lists.push_back(item);
}

unsigned char Window::getItem()
{
	return ID;
}

//計算
void Window::Update()
{
	//mInput->Update(); // キー入力更新

	//キー入力	
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
		Move_Scene = lists.at(Cursor).winScene;	//シーン推移
		ID = lists.at(Cursor).ID;	//アイテムID
	}	
}

//描画
void Window::Draw()
{
#define FRAME_COLOR GetColor(0,100,0)	//フレームの色
#define CURSOR_COLOR GetColor(0,0,0)	//カーソルの色

	DrawBox(position.x, position.y, size.x, size.y, BackGroundColor, true);	//背景

	DrawBox(position.x, position.y, size.x, size.y, FRAME_COLOR, false);	//枠
	DrawBox(position.x - 1, position.y - 1, size.x + 1, size.y + 1, FRAME_COLOR, false);	//枠
	DrawBox(position.x - 2, position.y - 2, size.x + 2, size.y + 2, FRAME_COLOR, false);	//枠
	DrawBox(position.x - 3, position.y - 3, size.x + 3, size.y + 3, FRAME_COLOR, false);	//枠
	DrawBox(position.x - 4, position.y - 4, size.x + 4, size.y + 4, FRAME_COLOR, false);	//枠
	

	DrawFormatString(position.x + 2, position.y + 4, TitleColor,"%s",Title.c_str());	//タイトル


	//項目を表示
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		List_Item item = *itr;
		if (lists.at(Cursor).pos == item.pos)
		{

			//カーソルの場所
			DrawFormatString(itr->pos.x - 50, itr->pos.y, CURSOR_COLOR, "-->");		//カーソル
			DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + 100, itr->pos.y + 16, GetColor(0,100,0), true);	//背景

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//項目
		}
		else {

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//項目
		}
	}
}


//デストラクタ
Window::~Window()
{

}


