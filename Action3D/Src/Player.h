#pragma once
#include "Object3D.h"

class Player : public Object3D
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
private:
	VECTOR3 swordTop, swordBtm;
	VECTOR2 LStickVec();
	enum State {
		ST_NORMAL = 0,
		ST_ATTACK1,
		ST_ATTACK2,
		ST_ATTACK3,
	};
	State state; // ó‘Ô‚ğ‚Â•Ï”
	void UpdateNormal();
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();
	bool attackPushed;
};