#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_


#include "Game_Scene.hpp"
#include "Input.hpp"
#include <iostream>
#include <locale.h>
#include <Random>


#define CELL ((int)48)	//セル

//画面サイズ
#define SCREEN_WIDTH ((int)16 * 80)
#define SCREEN_HEIGHT ((int)9 * 80)

//ステージ
#define STAGE_WIDTH ((int)50 * CELL)
#define STAGE_HEIGHT ((int)50 * CELL)



//方向
#define VECTOR_UP glm::ivec2(0,-1)
#define VECTOR_DOWN glm::ivec2(0,1)
#define VECTOR_LEFT glm::ivec2(-1,0)
#define VECTOR_RIGHT glm::ivec2(1,0)

#define PI ((float)3.14159265359)	//PI



// シーンの種類
typedef  enum class Scene_Type
{
	Title,		//タイトル
	Game,		//メインゲーム
	GameOver,	//ゲームオーバー


	Menu,		//メニュー
	Pause,		//一時停止
}Scene_Type;


/*####################################################
* シーン推移
* 
* 説明
* シーンの推移を行う
######################################################*/
class Game_Scene;
class Entry
{
public:

	Entry();	//コンストラクタ
	~Entry();	//デストラクタ

	void Update();	//計算
	void Draw();	//描画
	int GetRand(int start, int end);	//乱数を取得
	
	int LoadSprite(const char* FileName);				//スプライトをロード


	std::shared_ptr<Input> InputKey;

private:

	std::shared_ptr<Game_Scene> game;

	Scene_Type type;

};


#endif

