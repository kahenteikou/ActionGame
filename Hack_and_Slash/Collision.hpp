#ifndef ___COLLISION_HPP_
#define ___COLLISION_HPP_

#include "glm/glm.hpp"
#include <iostream>
//タグ
typedef enum class Tag
{
	Player,
	Enemy,
	Wall,
	Item,
	None,		//未設定
	Block,
	Brick,
	Shop,

	Invalid,	//交差してない
}Tag;


//プリミティブ型

//線
typedef struct LineSegment
{
	glm::vec2 mStart;	
	glm::vec2 mEnd;		


}LineSegment;

//AABB
typedef struct AABB
{
	glm::vec2* mMin;	//最小値
	glm::vec2* mMax;	//最大値

}AABB;

//円
typedef struct Circle
{
	glm::vec2* mCenter;	//中心点
	float* mRadius;		//半径
}Circle;

//線分
typedef struct Segment {
	glm::vec2* mStart;	//始点
	glm::vec2* mEnd;	//終点
}Segment;



/*####################################################
* 当たり判定の基底クラス
######################################################*/
class Collision
{
public:
	Collision();	//コンストラクタ
	~Collision();	//デストラクタ
	
	//機能
	
	

	//設定　関係
	void setCol(bool b);				//当たったかどうか？
	void setColTag(Tag type);			//取得したタイプ設定
	void setVector(glm::vec2* vec);		//方向設定
	void setTriggerType(bool tri);		//トリガータイプを設定
	void setTag(Tag type);				//タグを設定
	void setSpeed(glm::vec2 *spp);		//速度を設定

	//取得　関係
	Tag getMyTag();				//タイプを取得
	bool getTriggerType();		//トリガータイプを取得
	glm::vec2 getVector();		//方向を取得
	bool getCol();				//当たったかどうか？
	Tag getTag();				//取得したタイプを取得
	glm::vec2 getSpeed();		//速度を取得

private:
	bool IsTrigger;		//トリガータイプかどうか？
	Tag my_TagType;		//自身タグ
	Tag col_TagType;	//取得タグ
	glm::vec2 *Vector;	//方向
	bool isCol;			//当たったかどうか？
	glm::vec2 *Speed;	//速度
};


/*####################################################
* 矩形の当たり判定
######################################################*/

class BoxCollision : public Collision
{
public:
	BoxCollision();		//コンストラクタ
	~BoxCollision();	//デストラクタ

//	void Intersect(BoxCollision &col);
	void Intersect(std::shared_ptr<BoxCollision> col);
	//取得　関係
	glm::vec2 getMax();
	glm::vec2 getMin();


	//設定　関係
	void setMax(glm::vec2 *max);
	void setMin(glm::vec2 *min);

	void setMaxValue(glm::vec2 &max);
	void setMinValue(glm::vec2 &min);

private:
	AABB box;
};




#endif