#include "FallPuyo.h"
#include "Stage.h"

FallPuyo::FallPuyo()
{
	image = new CSpriteImage(GameDevice()->m_pShader, "Data/puyo_sozai.png");
	spr = new CSprite(image);

	x = 4;
	y = 0;
	color = Puyo::C_RED;
	timer = 1.0f;
}

FallPuyo::~FallPuyo()
{
}

void FallPuyo::Update()
{
	Stage* st = ObjectManager::FindGameObject<Stage>();
	CDirectInput* di = GameDevice()->m_pDI;
	if (di->CheckKey(KD_TRG, DIK_A)) {
		if (st->CanMove(x - 1, y)) {
			x--;
		}
	}
	if (di->CheckKey(KD_TRG, DIK_D)) {
		if (st->CanMove(x + 1, y)) {
			x++;
		}
	}
#if _DEBUG
	if (di->CheckKey(KD_TRG, DIK_K)) {
		color = (Puyo::Color)((color+1)%5);
	}
#endif
	if (di->CheckKey(KD_DAT, DIK_S)) {
		//timer = 0.0f;
		// もしくは、若干遅くする場合
		if (timer >= 0.05f) {
			timer = 0.05f;//Sを押している時の落ちる時間（秒）
		}
	}
	timer -= SceneManager::DeltaTime();
	if (timer <= 0.0f) {
		if (st->CanMove(x, y+1)) {
			y++;
		} else {
			// ToDo:ステージに書く
			st->Set(x, y, color);
			// 上からやりなおし
			x = 4;
			y = 0;
			color = (Puyo::Color)(rand() % 5);
		}
		timer = 1.0f;//秒
	}
}

void FallPuyo::Draw()
{
	spr->Draw(image, x * 32 + 100, y * 32 + 200, color * 32, 0, 32, 32);
}
