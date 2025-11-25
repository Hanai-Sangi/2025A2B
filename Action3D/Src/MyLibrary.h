#pragma once
#include "GameObject.h"

namespace MyLibrary {
	// 線分と球の当たり判定

	/// <summary>
	/// 球を表示する
	/// </summary>
	/// <param name="center">中心座標</param>
	/// <param name="radius">半径</param>
	/// <param name="color">表示色</param>
	void DrawSphere(const VECTOR3& center, float radius, DWORD color);
};
using namespace MyLibrary;