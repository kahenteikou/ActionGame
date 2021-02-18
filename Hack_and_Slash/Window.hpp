#ifndef ___WINDOW_HPP_
#define ___WINDOW_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"
#include <string>
#include <vector>
#include <iostream>

#include "Entry.hpp"
#include "Input.hpp"
#include "UI.hpp"





// メニュー推移
enum class MenuMove
{
	Main,//最初の画面

	Item,	//アイテム

	//メインメニュー
	Buy_Menu,
	Sell_Menu,

	//決定
	Buy_Conf,
	Sell_Conf,

	Check,


	//戻る　終了
	End,

	Back,


	Invalid,

};

//ウインドウの項目
typedef struct Window_Item
{
	glm::ivec2 pos;		//座標
	std::string name;	//名前
	MenuMove menu;		//メニュー推移

}Window_Item;


// ゲームアイテム
typedef struct ItemData
{
	int HP;		//体力
	int Diff;	//防御
	int Attak;	//攻撃
	glm::ivec2 pos;		//座標
	std::string name;	//アイテム名

}ItemData;

/*####################################################
* ウインドウ画面
*
* 説明
* 十字選択するメニュー画面
######################################################*/
class Window
{
public:

	Window(MenuMove m,glm::ivec2 pos,glm::ivec2 size, std::string str);	//コンストラクタ
	~Window();															//デストラクタ

	void AddItem(MenuMove m, std::string name);				//ウインドウに項目を追加
	void AddItem_Parameter(ItemData);						//アイテムを表示

	MenuMove getChange();						//シーン繰り替え
	void setChange(MenuMove m);					//シーン指定


	void Update();	//計算
	void Draw();	//描画

private:

	RectangleData window;			//画面サイズ
	std::shared_ptr<Input> mInput;	//キー入力

	glm::ivec2 mPosition;	//座標
	glm::ivec2 mSize;		//サイズ

	std::string WindowTitle;			//タイトル
	std::vector<Window_Item> Item;		//メニュー項目
	std::vector<ItemData> Game_Item;	//アイテムを取得
	int Cursor;		//カーソル移動

	MenuMove Menu;	//メニュジャンル
	MenuMove Move;	//メニュ推移






	//一時変数　関係
	glm::ivec2 ItemPos;	//項目の座標





};


#endif
