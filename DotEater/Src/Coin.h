#pragma once
#include "Object3D.h"

class Coin : public Object3D
{
public:
	Coin();
	Coin(VECTOR3 pos);
	~Coin();
	void Update() override;
private:
	bool gotten;
	float velocityY;
	int frameCount;

	int rotTime;
};