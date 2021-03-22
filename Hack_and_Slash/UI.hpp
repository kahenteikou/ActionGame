#ifndef ___UI_HPP_
#define ___UI_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"




//ウインドウの情報
typedef struct RectangleData
{
	glm::vec2  pos;		//座標
	glm::vec2  size;	//サイズ
}RectangleData;

void GetRectangleData(RectangleData& data, glm::vec2  pos, glm::vec2  size);	//矩形サイズを設定


/*####################################################
* ユーザーインターフェイス
*
* 説明
* プレイ画面のUI　未完成
######################################################*/

class UI
{
public:
	UI(glm::vec2  pos = glm::vec2 (0, 0), glm::vec2  vec = glm::vec2 (0, 0));	//コンストラクタ
	~UI();	//デストラクタ

	void virtual Update() = 0;	//計算
	void virtual Draw() = 0;	//描画

	//取得関係
	glm::vec2  getVector();		//方向
	glm::vec2  getPosition();	//座標
protected:

	glm::vec2  mPosition;	//座標
	glm::vec2  mVector;		//方向
	glm::vec2  mSize;		//スプライトのサイズ


};


#endif
