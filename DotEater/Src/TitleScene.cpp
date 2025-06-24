#include "TitleScene.h"
#include "GameMain.h"
#include <fstream>

TitleScene::TitleScene()
{
	// ファイルを読む実験
	std::ifstream ifs("data/Stage00.csv"); // ファイルを開く
	std::string str;
	std::getline(ifs, str); // ファイルから１行読む
	int n = str.find(',');
	std::string s = str.substr(0, n); // 文字列を切り取る
	int x = stoi(s); // StringToInt：文字列を整数に変える
	OutputDebugString(str.c_str());
	OutputDebugString("\n");
	std::getline(ifs, str); // ファイルから１行読む
	OutputDebugString(str.c_str());
	OutputDebugString("\n");
	ifs.close(); // ファイルを閉じる
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (GameDevice()->m_pDI->
			CheckKey(KD_TRG, DIK_P)) {
		SceneManager::ChangeScene("PlayScene");
	}
}

void TitleScene::Draw()
{
	GameDevice()->m_pFont->Draw(
		20, 20, "TitleScene", 16, RGB(255, 0, 0));
}