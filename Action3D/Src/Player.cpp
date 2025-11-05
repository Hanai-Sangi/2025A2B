#include "Player.h"
#include "../Libs/Imgui/imgui.h"
#include "Golem.h"

enum ANIM_ID {
	A_RUN = 0,
	A_ATTACK1 = 2,
	A_ATTACK2,
	A_ATTACK3,
};

Player::Player()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Player/PlayerChara.mesh");
	mesh->LoadAnimation(A_RUN, "Data/Player/Run.anmx", true);
	mesh->LoadAnimation(A_ATTACK1, "Data/Player/attack1.anmx", false);
	mesh->LoadAnimation(A_ATTACK2, "Data/Player/attack2.anmx", false);
	mesh->LoadAnimation(A_ATTACK3, "Data/Player/attack3.anmx", false);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(A_RUN);
	state = ST_NORMAL;
}

Player::~Player()
{
}

void Player::Update()
{
	switch (state) {
	case ST_NORMAL:
		UpdateNormal();
		break;
	case ST_ATTACK1:
		UpdateAttack1();
		break;
	case ST_ATTACK2:
		UpdateAttack2();
		break;
	case ST_ATTACK3:
		UpdateAttack3();
		break;
	}
	animator->Update();

	Golem* gom = ObjectManager::FindGameObject<Golem>();
	VECTOR3 push = gom->CollideSphere(
		transform.position+VECTOR3(0, 0.5, 0), 0.5f);
	transform.position += push;
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

void Player::UpdateNormal()
{
	VECTOR2 inp = LStickVec();
	VECTOR3 velocity = VECTOR3(inp.x, 0, -inp.y) * 0.05f;
	if (magnitude(velocity) > 0) {
		VECTOR3 camVec = GameDevice()->m_vLookatPt -
			GameDevice()->m_vEyePt;
		float th = atan2f(camVec.x, camVec.z);
		velocity = velocity * XMMatrixRotationY(th);
		transform.position += velocity;
		//		transform.rotation.y = atan2f(velocity.x, velocity.z);
#if false // 角度バージョン
		float ang = atan2f(velocity.x, velocity.z);
		float diff = ang - transform.rotation.y;
		// -180～180に収める
		while (diff < -XM_PI) diff += XM_2PI;
		while (diff > XM_PI) diff -= XM_2PI;
		if (diff > 20.0f * DegToRad) {
			transform.rotation.y += 20.0f * DegToRad;
		} else if (diff < -20.0f * DegToRad) {
			transform.rotation.y -= 20.0f * DegToRad;
		} else {
			transform.rotation.y = ang;
		}
#else //　内積バージョン
		VECTOR3 velNorm = normalize(velocity); //長さを１にする
		MATRIX4X4 mat = XMMatrixRotationY(transform.rotation.y);
		VECTOR3 forward = VECTOR3(0, 0, 1) * mat;
		float ip = dot(velNorm, forward); // これがcosθ
		if (ip >= cos(20.0f * DegToRad)) {
			transform.rotation.y = atan2f(velocity.x, velocity.z);
		} else {
			VECTOR3 right = VECTOR3(1, 0, 0) * mat;
			if (dot(right, velocity) > 0) {
				transform.rotation.y += 20.0f * DegToRad;
			} else {
				transform.rotation.y -= 20.0f * DegToRad;
			}
		}
#endif
	}
	float len = magnitude(inp);
	ImGui::Begin("PAD");
	ImGui::InputFloat("LX", &inp.x);
	ImGui::InputFloat("LY", &inp.y);
	ImGui::InputFloat("Len", &len);
	ImGui::End();

	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_M))
	{
		animator->MergePlay(A_ATTACK1);
		state = ST_ATTACK1;
		attackPushed = false;
	}
}

void Player::UpdateAttack1()
{
	if (animator->CurrentFrame() < 70.0f) {
		animator->SetPlaySpeed(2.0f);
	} else {
		animator->SetPlaySpeed(1.2f);
	}
	// 70フレームまでにMボタンを押していたら、
	if (animator->CurrentFrame() < 70.0f) { 
		if (GameDevice()->m_pDI->CheckKey(
									KD_TRG, DIK_M)) {
			attackPushed = true;
		}
	} else {
		if (attackPushed) {
			// アニメーションを切り替える
			animator->MergePlay(A_ATTACK2);
			state = ST_ATTACK2;
			attackPushed = false;
		}
	}

	if (animator->Finished()) {
		animator->Play(A_RUN);
		state = ST_NORMAL;
	}
}

void Player::UpdateAttack2()
{
	if (animator->CurrentFrame() < 70.0f) {
		animator->SetPlaySpeed(2.0f);
	} else {
		animator->SetPlaySpeed(1.2f);
	}
	// 70フレームまでにMボタンを押していたら、
	if (animator->CurrentFrame() < 70.0f) {
		if (GameDevice()->m_pDI->CheckKey(
			KD_TRG, DIK_M)) {
			attackPushed = true;
		}
	} else {
		if (attackPushed) {
			// アニメーションを切り替える
			animator->Play(A_ATTACK3);
			state = ST_ATTACK3;
			attackPushed = false;
		}
	}
	if (animator->Finished()) {
		animator->Play(A_RUN);
		state = ST_NORMAL;
	}

}

void Player::UpdateAttack3()
{
	if (animator->Finished()) {
		animator->Play(A_RUN);
		state = ST_NORMAL;
	}
}
