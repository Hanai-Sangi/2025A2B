#include "PlayTime.h"
#include "PlayScene.h"

PlayTime::PlayTime()
{
	image = new CSpriteImage(GameDevice()->m_pShader);
	image->Load("data/images/number.png");

	playTime = 20.0f; // ïb
}

PlayTime::~PlayTime()
{
}

void PlayTime::Update()
{
	PlayScene* scene =
		dynamic_cast<PlayScene*>(SceneManager::CurrentScene());
	if (scene->CanMove()) {
		playTime -= SceneManager::DeltaTime();
		if (playTime <= 0.0f) {
			playTime = 0.0f;
		}
	}
}

void PlayTime::Draw()
{
	CSprite spr;
	int w = image->m_dwImageWidth;
	int h = image->m_dwImageHeight;
	int sec = (int)playTime;
	// playTimeÇ«Ç®ÇËÇ…ï\é¶ÅAÇOÇ…Ç»Ç¡ÇΩÇÁé~ÇﬂÇÈ
	spr.Draw(image, 400, 10, (sec/10) * w / 10, 0, w / 10, h);
	spr.Draw(image, 520, 10, (sec%10) * w / 10, 0, w / 10, h);
}
