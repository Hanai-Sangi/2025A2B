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
	for (auto& cx : cells) {
		for (Cell& cc : cx) {
			if (cc.offsetY > 0.0f) {
				cc.offsetY -= fallSpeed;
			} else if (cc.offsetY < 0.0f) {
				cc.offsetY += 1.0f;
				if (cc.offsetY > 0.0f) {
					cc.offsetY = 0;
				}
			}
		}
	}
	// 全部のoffsetYが0であれば、連鎖チェック
	bool found = false;
	fallSpeed += 1.3f;
	for (auto& cx : cells) {
		for (Cell& cc : cx) {
			if (cc.offsetY != 0.0f)
				found = true;
		}
	}
	if (not found) {
		ChainCheck();
	}
}

void Stage::Draw()
{
	// cellsのデータの通りに全て表示する
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			int col = cells[x][y].color;
			if (col != Puyo::C_NONE) {
				int off = static_cast<int>(cells[x][y].offsetY);
				spr->Draw(image, x * 32 + 100, y * 32 + 200 - off,
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
	//checkedを初期化
	for (auto& cx : cells) {
		for (Cell& cc : cx) {
			cc.checked = false;
		}
	}
	if (CheckConnect(x, y) >= 4) {
		//4個消す
		for (auto& cx : cells) {
			for (Cell& cc : cx) {
				if (cc.checked) {
					cc.color = Puyo::C_NONE;
				}
			}
		}
		Drop(); // 落とす処理を関数にしておく
	}
}

int Stage::CheckConnect(int x, int y)
{
	if (cells[x][y].checked)
		return 0;

	Puyo::Color c = cells[x][y].color;
	int ret = 1;
	cells[x][y].checked = true;
	if (cells[x + 1][y].color == c) {
		ret += CheckConnect(x + 1, y);
	}
	if (cells[x - 1][y].color == c) {
		ret += CheckConnect(x - 1, y);
	}
	if (cells[x][y + 1].color == c) {
		ret += CheckConnect(x, y + 1);
	}
	if (cells[x][y - 1].color == c) {
		ret += CheckConnect(x, y - 1);
	}
	return ret;
}

void Stage::Drop()
{
	fallSpeed = 1.0f;
	for (auto& line : cells) {
		// lineが縦１列の配列 Cells[15]
		int fallCount = 0;
		for (int y = HEIGHT - 2; y >= 0; y--) {// 一番下が壁なので
			if (line[y].color == Puyo::C_NONE) {
				fallCount += 1;
			} else {
				if (fallCount > 0) {
					//	このぷよをfallCount分落とす
					line[y + fallCount] = line[y];
					line[y + fallCount].offsetY = fallCount * 32; // 表示は落ちる前
					line[y].color = Puyo::C_NONE;
				}
			}
		}
	}
}

void Stage::ChainCheck()
{
	for (int x = 1; x < WIDTH-1; x++) {
		for (int y = 0; y < HEIGHT-1; y++) {

			//checkedを初期化
			for (auto& cx : cells) {
				for (Cell& cc : cx) {
					cc.checked = false;
				}
			}
			if (CheckConnect(x, y) >= 4) {
				//4個消す
				for (auto& cx : cells) {
					for (Cell& cc : cx) {
						if (cc.checked) {
							cc.color = Puyo::C_NONE;
						}
					}
				}
				Drop(); // 落とす処理を関数にしておく
			}
		}
	}
}
