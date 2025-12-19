#include "Stage.h"

Stage::Stage()
{
	image = new CSpriteImage(GameDevice()->m_pShader, "Data/puyo_sozai.png");
	spr = new CSprite(image);

	// cellsに壁を作り、他はNONEにする
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			Puyo::Color c = Puyo::C_NONE;
			if (x == 0 || x == WIDTH-1 || y == HEIGHT-1) {
				c = Puyo::C_WALL;
			}
			cells[x][y].color = c;
		}
	}
	cells[3][4].color = Puyo::C_RED;
	cells[5][8].color = Puyo::C_BLUE;
}

Stage::~Stage()
{
	delete spr;
	delete image;
}

void Stage::Update()
{
}

void Stage::Draw()
{
	// cellsのデータの通りに全て表示する
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			int col = cells[x][y].color;
			if (col != Puyo::C_NONE) {
				spr->Draw(image, x * 32 + 100, y * 32 + 200,
					col * 32, 0, 32, 32);
			}
		}
	}
}

bool Stage::CanMove(int x, int y)
{
	if (cells[x][y].color != Puyo::C_NONE)
		return false;
	return true;
}

void Stage::Set(int x, int y, Puyo::Color c)
{
	cells[x][y].color = c;
}
