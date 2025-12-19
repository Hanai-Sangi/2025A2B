#pragma once
#include "GameObject.h"
#include "Puyo.h"

class FallPuyo : public GameObject {
public:
	FallPuyo();
	~FallPuyo();
	void Update() override;
	void Draw() override;
private:
	CSpriteImage* image;
	CSprite* spr;
	int x, y;
	Puyo::Color color;
	float timer; //	—Ž‚¿‚éŽžŠÔ‚ð‘ª‚é
};