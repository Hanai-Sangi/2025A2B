#pragma once
#include "Object3D.h"

class Player : public Object3D
{
public:
	Player();
	~Player();
	void Update() override;
private:
	VECTOR2 LStickVec();
	enum State {
		ST_NORMAL = 0,
		ST_ATTACK1,
		ST_ATTACK2,
		ST_ATTACK3,
	};
	State state; // ��Ԃ����ϐ�
	void UpdateNormal();
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();
};