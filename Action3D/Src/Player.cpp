#include "Player.h"
#include "../Libs/Imgui/imgui.h"

Player::Player()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Player/PlayerChara.mesh");
	mesh->LoadAnimation(0, "Data/Player/Run.anmx", true);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(0);
}

Player::~Player()
{
}

void Player::Update()
{
	animator->Update();
	auto inp = GameDevice()->m_pDI->GetJoyState();
	int x = inp.lRx;
	int y = inp.lRy;
	int b = inp.rgbButtons[0];
	ImGui::Begin("PAD");
	ImGui::InputInt("RX", &x);
	ImGui::InputInt("RY", &y);
	ImGui::InputInt("LB", &b);
	ImGui::End();
}