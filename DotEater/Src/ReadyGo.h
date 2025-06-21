#pragma once
#include "GameObject.h"

class ReadyGo : public GameObject
{
public:
	ReadyGo();
	~ReadyGo();
	void Update() override;
	void Draw() override;
private:
	CSpriteImage* readyImage;
	CSpriteImage* goImage;
	int readyCounter;

	VECTOR2 startPos;
	VECTOR2 endPos;
	VECTOR2 position;
};