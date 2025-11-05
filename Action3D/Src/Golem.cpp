#include "Golem.h"

enum ANIM_ID {
	A_IDLE = 0,
};

Golem::Golem(VECTOR3 pos, float rotY)
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Golem/golem.mesh");
	mesh->LoadAnimation(A_IDLE, "Data/Golem/golem_stand.anmx", true);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(A_IDLE);

	transform.position = pos;
	transform.rotation = VECTOR3(0, rotY, 0);
	transform.scale = VECTOR3(0.3, 0.3, 0.3);
}

Golem::~Golem()
{
}

void Golem::Update()
{
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
