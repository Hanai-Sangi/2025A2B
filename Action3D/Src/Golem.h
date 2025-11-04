#pragma once
#include "Object3D.h"

class Golem : public Object3D
{
public:
	Golem(VECTOR3 pos, float rotY);
	~Golem();
	void Update() override;
};