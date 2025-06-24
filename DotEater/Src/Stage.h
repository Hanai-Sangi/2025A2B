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
	/// ���ƃX�e�[�W�Ƃ̓����蔻�������
	/// </summary>
	/// <param name="center">���̒��S���W</param>
	/// <param name="radius">���̔��a</param>
	/// <returns>�����Ԃ��x�N�g��(�������ĂȂ����(0,0,0)</returns>
	VECTOR3 CollideSphere(VECTOR3 center, float radius);
};






