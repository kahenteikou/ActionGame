#ifndef ___SHOP_HPP_
#define ___SHOP_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"
#include <array>
#include <vector>


#include "Entry.hpp"
//#include "Player.hpp"
#include "Window.hpp"
//#include "Input.hpp"
#include "ItemID.hpp"

//前方宣言
class Window;				//ウインドクラス
enum class Window_Scene;	//ウインドウシーン
class Player;
/*####################################################
* ショップ
######################################################*/

class Shop
{
public:
	Shop(Entry* e);		//コンストラクタ	
	~Shop();			//デストラクタ

	void Update(Player& player);	//更新
	void Draw();	//描画


	bool getState();			//現在ショップ中かどうか？
	void setIs_State(bool b);
	void Reset_Flag();


private:

	std::shared_ptr<Window> MainMenu;	//メインメニュー
	std::shared_ptr<Window> BuyMenu;	//購入メニュー
	std::shared_ptr<Window> SellMenu;	//売るメニュー

	std::shared_ptr<Window> CheckMenu_Buy;	//確認メニュー
	std::shared_ptr<Window> CheckMenu_Sell;	//確認メニュー


	unsigned char Item_ID;	//更新するアイテムのID




	bool b = false;
	bool mIsNowShop;	//ショップを閉じるかどうか？
	Window_Scene Scene;	//現在の選択
	std::vector<Window_Scene> DrawMenu;	//メニュー切り替え描画

	Entry* Owner;	//Entry クラス

};


#endif
