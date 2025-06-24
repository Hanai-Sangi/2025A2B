#pragma once
#include "Object3D.h"

class Stage : public Object3D
{
public:
	Stage();
	Stage(int stageNo);
	~Stage();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 球とステージとの当たり判定をする
	/// </summary>
	/// <param name="center">球の中心座標</param>
	/// <param name="radius">球の半径</param>
	/// <returns>押し返すベクトル(当たってなければ(0,0,0)</returns>
	VECTOR3 CollideSphere(VECTOR3 center, float radius);
};






