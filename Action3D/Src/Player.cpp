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
	VECTOR2 inp = LStickVec();
	VECTOR3 velocity = VECTOR3(inp.x,0,-inp.y)*0.05f;
	if (magnitude(velocity) > 0) {
		VECTOR3 camVec = GameDevice()->m_vLookatPt -
			GameDevice()->m_vEyePt;
		float th = atan2f(camVec.x, camVec.z);
		velocity = velocity * XMMatrixRotationY(th);
		transform.position += velocity;
		transform.rotation.y = atan2f(velocity.x, velocity.z);
	}
	float len = magnitude(inp);
	ImGui::Begin("PAD");
	ImGui::InputFloat("LX", &inp.x);
	ImGui::InputFloat("LY", &inp.y);
	ImGui::InputFloat("Len", &len);
	ImGui::End();

}

VECTOR2 Player::LStickVec()
{
	auto inp = GameDevice()->m_pDI->GetJoyState();
	float x = (float)inp.lX;
	float y = (float)inp.lY;
	x /= 1000.0f;
	y /= 1000.0f;
	if (x > -0.1f && x < 0.1f)
		x = 0.0f;
	if (y > -0.1f && y < 0.1f)
		y = 0.0f;
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_W))
		y = -1.0f;
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_S))
		y = 1.0f;
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_A))
		x = -1.0f;
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_D))
		x = 1.0f;
	VECTOR2 ret = VECTOR2(x, y);
	if (magnitude(ret) > 1.0) {
		ret = normalize(ret);
	}
	return ret;
}
