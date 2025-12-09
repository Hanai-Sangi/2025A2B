#pragma once
#include "Object3D.h"

class Golem : public Object3D
{
public:
	Golem(VECTOR3 pos, float rotY);
	~Golem();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 球と当たり判定する
	/// </summary>
	/// <param name="center">中心座標</param>
	/// <param name="radius">半径</param>
	/// <returns>押し戻すベクトル</returns>
	VECTOR3 CollideSphere(VECTOR3 center, float radius);

	bool CollideSword(VECTOR3 top, VECTOR3 btm);
private:
	void UpdateIntention();
	enum Intent {
		I_WALK = 0,
		I_ATTACK,
		I_BACK,
		I_DAMAGED,
	};
	Intent intent;
	void ChangeIntention(Intent inte);
	void IntWalk();
	void IntAttack();
	void IntBack();
	void IntDamaged();

	void UpdateAction();
	enum Action {
		A_MOVE = 0,
		A_STAND,
		A_PUNCH,
		A_DIE,
	};
	Action action;
	void ChangeAction(Action act);
	void ActMove();
	void ActStand();
	void ActPunch();
	void ActDie();

	VECTOR3 teritoriCenter;
	float dieTime;
};
