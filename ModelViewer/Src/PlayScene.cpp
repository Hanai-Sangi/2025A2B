#include "PlayScene.h"
#include <fstream>
#include "CsvReader.h"
#include <assert.h>
#include "Axis.h"
#include "Camera.h"
#include "Player.h"
#include "Ghost.h"
#include "Dreyar.h"

PlayScene::PlayScene()
{
	new Axis();
	new Camera();
	new Ghost();
	new Player();
	new Dreyar();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
}

void PlayScene::Draw()
{
	GameDevice()->m_pFont->Draw(
		20, 20, "PlayScene", 16, RGB(255, 255, 0));
}
