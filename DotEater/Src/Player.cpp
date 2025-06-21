#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
Player::Player()
{
	mesh = new CFbxMesh();
	mesh->Load("data/Mousey/Mousey.mesh");
	mesh->LoadAnimation(0, "data/Mousey/Anim_Run.anmx", true);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(0);
}

Player::Player(VECTOR3 pos)
{
	transform.position = pos;

	mesh = new CFbxMesh();
	mesh->Load("data/Mousey/Mousey.mesh");
	mesh->LoadAnimation(0, "data/Mousey/Anim_Run.anmx", true);
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

	PlayScene* scene =
		dynamic_cast<PlayScene*>(SceneManager::CurrentScene());
	if (scene->CanMove()) {

		CDirectInput* di = GameDevice()->m_pDI;
		if (di->CheckKey(KD_DAT, DIK_D)) {
			transform.rotation.y += 3.0f * DegToRad;
		}
		if (di->CheckKey(KD_DAT, DIK_A)) {
			transform.rotation.y -= 3.0f * DegToRad;
		}
		if (di->CheckKey(KD_DAT, DIK_W)) {
			float speed = 0.05f;
			VECTOR3 move = VECTOR3(0, 0, 1) * speed;
			MATRIX4X4 rotY = XMMatrixRotationY(
				transform.rotation.y);
			transform.position += move * rotY;

			// •Ç‚Æ“–‚½‚è”»’è‚·‚é
			Stage* stage = ObjectManager::FindGameObject<Stage>();
			VECTOR3 push = stage->CollideSphere(
				transform.position + VECTOR3(0, 0.5f, 0), 0.4f);
			transform.position += push;
			push = stage->CollideSphere(
				transform.position + VECTOR3(0, 0.5f, 0), 0.4f);
			transform.position += push;
		}
	}
	MATRIX4X4 rotY = XMMatrixRotationY(
		transform.rotation.y);
	VECTOR3 camPos = VECTOR3(0,10,-10)*rotY+transform.position;
	VECTOR3 camLook = transform.position + VECTOR3(0, 3.2f, 0);
	GameDevice()->m_mView = XMMatrixLookAtLH(
		camPos, camLook,
		VECTOR3(0, 1, 0));
}
