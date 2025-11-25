#pragma once
#include "GameObject.h"

namespace MyLibrary {
	/// <summary>
	/// 線分と球の当たり判定をする
	/// </summary>
	/// <param name="seg1">線分の始点</param>
	/// <param name="seg2">線分の終点</param>
	/// <param name="center">球の中心座標</param>
	/// <param name="radius">球の半径</param>
	/// <returns>当たってたらtrue</returns>
	bool CollideSegmentToSphere(VECTOR3 seg1, VECTOR3 seg2, 
										VECTOR3 center, float radius);

	/// <summary>
	/// 球を表示する
	/// </summary>
	/// <param name="center">中心座標</param>
	/// <param name="radius">半径</param>
	/// <param name="color">表示色</param>
	void DrawSphere(const VECTOR3& center, float radius, DWORD color);

	static const DWORD RED   = 0x0000ff;
	static const DWORD GREEN = 0x00ff00;
	static const DWORD BLUE  = 0xff0000;
};
using namespace MyLibrary;