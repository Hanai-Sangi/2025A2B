#include "Golem.h"
#include "Player.h"

enum ANIM_ID {
	A_IDLE = 0,
	A_WALK,
	A_ATTACK,
	A_DIE
};

Golem::Golem(VECTOR3 pos, float rotY)
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Golem/golem.mesh");
	mesh->LoadAnimation(A_IDLE, "Data/Golem/golem_stand.anmx", true);
	mesh->LoadAnimation(A_WALK, "Data/Golem/golem_walk.anmx", true);
	mesh->LoadAnimation(A_ATTACK, "Data/Golem/golem_attack.anmx", false);
	mesh->LoadAnimation(A_DIE, "Data/Golem/golem_die.anmx", false);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(A_IDLE);

	transform.position = pos;
	transform.rotation = VECTOR3(0, rotY, 0);
	transform.scale = VECTOR3(0.3, 0.3, 0.3);

	action = A_STAND;
	intent = I_WALK;
}

Golem::~Golem()
{
}

void Golem::Update()
{
	animator->Update();
	UpdateIntention();
	UpdateAction();
}

VECTOR3 Golem::CollideSphere(VECTOR3 center, float radius)
{
	VECTOR3 myCenter = transform.position + VECTOR3(0, 0.5, 0);
	float myRad = 1.0f;
	VECTOR3 v = center - myCenter;
	float d = magnitude(v);
	if ( d <= radius + myRad) {
		return normalize(v) * (radius + myRad - d);
	}
	return VECTOR3();
}

void Golem::UpdateIntention()
{
	switch (intent) {
	case I_WALK:
		IntWalk();
		break;
	case I_ATTACK:
		IntAttack();
		break;
	case I_BACK:
		IntBack();
		break;
	}
}

void Golem::ChangeIntention(Intent inte)
{
	if (intent == inte)
		return;
	switch (inte) {
	case I_WALK:
		break;
	case I_ATTACK:
		ChangeAction(A_MOVE);
		break;
	case I_BACK:
		break;
	}
	intent = inte;
}

void Golem::IntWalk()
{
	if (/*Playerが視界に入ったら*/) {
		ChangeIntention(I_ATTACK);
	}
}

void Golem::IntAttack()
{
}

void Golem::IntBack()
{
}

void Golem::UpdateAction()
{
	switch (action) {
	case A_MOVE:
		ActMove();
		break;
	case A_PUNCH:
		ActPunch();
		break;
	}
}

void Golem::ChangeAction(Action act)
{
	if (action == act)
		return;
	switch (act) {
	case A_PUNCH:
		animator->Play(ANIM_ID::A_ATTACK);
		animator->SetPlaySpeed(1.0f);
		break;
	case A_MOVE:
		animator->Play(ANIM_ID::A_WALK);
		break;
	}
	action = act;
}

void Golem::ActMove()
{
	float& rotY = transform.rotation.y;
	const float RotSpeed = 10.0f * DegToRad;

	animator->Play(A_WALK);
	animator->SetPlaySpeed(5.0f);
	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position; // プレイヤーの座標
	VECTOR3 v = plPos - transform.position;
	VECTOR3 vNorm = normalize(v); // 移動する向き
	VECTOR3 forward = VECTOR3(0, 0, 1) * XMMatrixRotationY(rotY);
	if (dot(vNorm, forward) >= cos(RotSpeed)) {
		rotY = atan2f(v.x, v.z);
	} else {
		VECTOR3 right = VECTOR3(1, 0, 0) * XMMatrixRotationY(rotY);
		if (dot(v, right) > 0) {
			rotY += RotSpeed;
		} else {
			rotY -= RotSpeed;
		}
	}
	transform.position += VECTOR3(0,0,0.05f)* XMMatrixRotationY(rotY);
	v = plPos - transform.position;
	if (v.Length() < 2.0f) {
		ChangeAction(A_PUNCH);
	}
}

void Golem::ActStand()
{
}

void Golem::ActPunch()
{
	if (animator->Finished()) {
		ChangeAction(A_MOVE);
	}
}
