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
