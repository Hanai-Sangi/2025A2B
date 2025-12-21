#pragma once
#include "GameObject.h"
#include <vector>
#include "Puyo.h"

class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	Puyo::Color Get(int x, int y) { return cells[x][y].color; }
	bool CanMove(int x, int y);
	void Set(int x, int y, Puyo::Color c);
	int CheckConnect(int x, int y);
	void Drop();
	void ChainCheck();
private:
	CSpriteImage* image;
	CSprite* spr;
	struct Cell {
		Puyo::Color color;
		bool checked; // 調べたマーク
		float offsetY; // Yをずらす値
		Cell() : color(Puyo::C_NONE), checked(false), offsetY(0) {}
	};
	float fallSpeed;

	static const int WIDTH = 8;
	static const int HEIGHT = 15;

	Cell cells[WIDTH][HEIGHT]; // 盤面のデータ
};