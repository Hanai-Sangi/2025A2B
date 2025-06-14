#include "PlayScene.h"
#include <fstream>
#include "CsvReader.h"
#include <assert.h>
#include "Player.h"
#include "Stage.h"

PlayScene::PlayScene()
{
	GameDevice()->m_mView = XMMatrixLookAtLH(
		VECTOR3(0, 10, -10), VECTOR3(0, 0, 0), 
		VECTOR3(0, 1, 0));

	new Stage();
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
