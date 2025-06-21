#include "ReadyGo.h"
#include "PlayScene.h"
#include "Lerp.h"

ReadyGo::ReadyGo()
{
	readyImage = new CSpriteImage(GameDevice()->m_pShader);
	readyImage->Load("data/images/ready.png");
	goImage = new CSpriteImage(GameDevice()->m_pShader);
	goImage->Load("data/images/go.png");

	readyCounter = 0;
	startPos = VECTOR2(WINDOW_WIDTH, WINDOW_HEIGHT/2);
	endPos = VECTOR2(400, WINDOW_HEIGHT/2);
	position = startPos;
}

ReadyGo::~ReadyGo()
{
}

void ReadyGo::Update()
{
	readyCounter++;
	if (readyCounter <= 60) {
		// startPos→endPosへ60フレームで移動するときの、
		// readyCounterフレーム後の位置を求める
		float rate = (float)readyCounter / 60.0f;
		rate = easeOutBounce(rate);
		position = Lerp(startPos, endPos, rate);
	}
	if (readyCounter == 120) {
		PlayScene* scene = 
			dynamic_cast<PlayScene*>(SceneManager::CurrentScene());
		scene->Go();
	}
}

void ReadyGo::Draw()
{
	CSpriteImage* now;
	if (readyCounter < 120) {
		now = readyImage;
	} else {
		now = goImage;
	}
	CSprite spr;
	int w = now->m_dwImageWidth;
	int h = now->m_dwImageHeight;
	spr.Draw(now, position.x, position.y, 0, 0, w, h);
}