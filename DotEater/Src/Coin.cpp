#include "Coin.h"
#include "Player.h"

Coin::Coin()
{
	mesh = new CFbxMesh();
	mesh->Load("data/LowPoly/Coin.mesh");
	gotten = false;
}

Coin::Coin(VECTOR3 pos)
{
	transform.position = pos;

	mesh = new CFbxMesh();
	mesh->Load("data/LowPoly/Coin.mesh");
	gotten = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	static const float JumpH = 2.0f;
	static const float JumpTime = 30.0f;
	if (gotten) {
		// 跳ねるプログラム
		transform.position.y += velocityY;
		velocityY -= 2 * JumpH / (JumpTime/2) / (JumpTime/2);
		// 水平にプレイヤーに近づく
		Player* player =
			ObjectManager::FindGameObject<Player>();
		VECTOR3 plPos = player->GetTransform().position;
		VECTOR3 diff = plPos - transform.position;
		diff.y = 0; // 水平に動かす
		transform.position += diff / frameCount;
		frameCount -= 1;
		// 跳ね終わったらDestroyMe();
		if (frameCount == 0) {
			DestroyMe();
		}
		transform.rotation.y += 60.0f * DegToRad;
		if (frameCount < 15) {
			transform.scale *= 0.9f;
		}
	} else {
		rotTime += 1;
		if (rotTime >= 60) {
			rotTime = 0;
		}
		if (rotTime <= 20) {
			transform.rotation.y =
				180.0f * DegToRad * rotTime / 20;
		}
		Player* player =
			ObjectManager::FindGameObject<Player>();
		VECTOR3 plPos = player->GetTransform().position;
		VECTOR3 diff = plPos - transform.position;
		if (diff.Length() < 0.4f + 0.4f) { // 当たっている
			gotten = true;
			velocityY = 2 * JumpH / (JumpTime/2);
			frameCount = JumpTime;
		}
	}
}
