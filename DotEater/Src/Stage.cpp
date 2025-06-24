#include "Stage.h"
#include <vector>
#include "Player.h"
#include "Coin.h"
#include "CsvReader.h"

//std::vector<std::vector<int>> map =
//{
//	{ 1, 1, 0, 1, 1, 1, 1 },
//	{ 1, 1, 0, 3, 0, 3, 1 },
//	{ 1, 2, 0, 1, 1, 0, 1 },
//	{ 1, 1, 1, 1, 1, 1, 1 },
//};
std::vector<std::vector<int>> map;

Stage::Stage() : Stage(0) {}

Stage::Stage(int stageNo)
{
	mesh = new CFbxMesh();
	mesh->Load("data/LowPoly/WallStone.mesh");
	meshCol = new MeshCollider();
	meshCol->MakeFromMesh(mesh); // 当たり判定モデルを作る

	// csvを読んでmapを作る
	char filename[60];
	sprintf_s<60>(filename, "data/Stage%02d.csv", stageNo);
	CsvReader* csv = new CsvReader(filename);
	int lines = csv->GetLines();
	map.resize(lines);
	for (int z = 0; z < lines; z++) {
		int cols = csv->GetColumns(z);
		map[z].resize(cols);
		for (int x = 0; x < cols; x++) {
			map[z][x] = csv->GetInt(z, x);
		}
	}
	delete csv;

	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 2) {
				new Player(VECTOR3(x, 0, -z));
			}
			if (map[z][x] == 3) {
				new Coin(VECTOR3(x, 0, -z));
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 1) {
				transform.position = VECTOR3(x, 0, -z);
				mesh->Render(transform.matrix());
			}
		}
	}
}

VECTOR3 Stage::CollideSphere(VECTOR3 center, float radius)
{
	VECTOR3 pushVec = VECTOR3(0, 0, 0); // 一番大きいベクトル
	float maxLen = 0; // 一番大きいベクトルの長さ
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 1) {
				transform.position = VECTOR3(x, 0, -z);
				SphereCollider coll;
				coll.center = center;
				coll.radius = radius;
				MeshCollider::CollInfo info;
				if (HitSphereToMesh(coll, &info)) {
					// 当たっているので、押し返すベクトルを返す
					VECTOR3 v = center - info.hitPosition;
					VECTOR3 vNorm = v.Norm(); // 向き
					float pushSize = radius - v.Length();
					if (pushSize > maxLen) {
						maxLen = pushSize;
						pushVec = vNorm * pushSize;
					}
				}
			}
		}
	}
	return pushVec;
}
