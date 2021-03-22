#include "UI.hpp"

//矩形の座標をサイズを設定
void GetRectangleData(RectangleData& data, glm::vec2  pos, glm::vec2  size)
{
	data.pos = glm::vec2 (pos.x - size.x, pos.y - size.y);	//座標
	data.size = glm::vec2 (pos.x + size.x, pos.y + size.y);	//サイズ
}
