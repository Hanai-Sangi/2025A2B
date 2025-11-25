#include "Golem.h"
#include "Player.h"
#include "MyLibrary.h"

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

	teritoriCenter = pos;

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

void Golem::Draw()
{
	Object3D::Draw();
	DrawSphere(transform.position+VECTOR3(0,1,0), 1.0f, RED);
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
		ChangeAction(A_STAND);
		break;
	case I_ATTACK:
		ChangeAction(A_MOVE);
		break;
	case I_BACK:
		ChangeAction(A_STAND);
		break;
	}
	intent = inte;
}

bool InSight(const VECTOR3& pos, float len, float ang, const Transform& my)
{
	VECTOR3 toPlayer = pos - my.position;
	if (toPlayer.Length() > len)
		return false;
	VECTOR3 toPlayerNorm = normalize(toPlayer);
	VECTOR3 forward = VECTOR3(0, 0, 1) * XMMatrixRotationY(my.rotation.y);
	float ip = dot(toPlayerNorm, forward);
	return (ip >= cosf(ang));
}

void Golem::IntWalk()
{
	// プレイヤーの座標を求める
	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position; // プレイヤーの座標
	if (InSight(plPos, 5.0f, 30 * DegToRad, transform)) {
		ChangeIntention(I_ATTACK);
	}
}

void Golem::IntAttack()
{
	// プレイヤーの座標を求める
	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position; // プレイヤーの座標
	if (not InSight(plPos, 7.0f, 40 * DegToRad, transform)) { // 視野外
		ChangeIntention(I_WALK);
	}

	// テリトリーから外れたら帰るChangeIntention(I_BACK)
	VECTOR3 v = transform.position - teritoriCenter;
	if (v.Length() >= 10.0) {
		ChangeIntention(I_BACK);
	}
}

void Golem::IntBack()
{
	float& rotY = transform.rotation.y;
	const float RotSpeed = 10.0f * DegToRad;

	animator->Play(A_WALK);
	animator->SetPlaySpeed(2.0f);
	VECTOR3 v = teritoriCenter - transform.position;
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
	transform.position += VECTOR3(0, 0, 0.02f) * XMMatrixRotationY(rotY);
	// 戻るのをやめて待機する
	v = teritoriCenter - transform.position;
	if (v.Length() < 1.0f)
		ChangeIntention(I_WALK);
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
	// Playerに向かって移動
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
	// なぐるか？
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
