#ifndef ___SHOP_HPP_
#define ___SHOP_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"


#include "Entry.hpp"
#include "Player.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include <array>
#include <vector>

//前方宣言
class Window;
enum class MenuMove;



/*####################################################
* ショップ
######################################################*/

class Shop
{
public:
	Shop();		//コンストラクタ	
	~Shop();	//デストラクタ

	void Update(Player& player);	//更新
	void Draw();	//描画


	bool getState();			//現在ショップ中かどうか？
	void setIs_State(bool b);
	void Reset_Flag();


private:

	std::shared_ptr<Window> MainMenu;	//メインメニュー
	std::shared_ptr<Window> BuyMenu;	//購入メニュー
	std::shared_ptr<Window> SellMenu;	//売るメニュー

	std::shared_ptr<Window> Dialogue;	//確認メニュー






	bool mIsNowShop;	//ショップを閉じるかどうか？
	MenuMove menu;	//現在の選択
	std::vector<MenuMove> DrawMenu;	//メニュー切り替え描画


};


#endif
