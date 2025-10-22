#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	VECTOR3 eye = VECTOR3(0, 0, -6);
	VECTOR3 look = VECTOR3(0,1,0);
	GameDevice()->m_vEyePt = eye; // カメラ座標
	GameDevice()->m_vLookatPt = look; // 注視点
	GameDevice()->m_mView = XMMatrixLookAtLH(     // ビューマトリックス
		eye, look,
		VECTOR3(0, 1, 0));
	transform.rotation = VECTOR3(10.0f*DegToRad, 0, 0);
}

Camera::~Camera()
{
}
float clampMe(float& in, float minV, float maxV)
{
	if (in<minV) in = minV;
	if (in>maxV) in = maxV;
	return in;
}

void Camera::Update()
{
	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position;

	transform.rotation.y += RStickX() * 5.0f * DegToRad;
	transform.rotation.x += RStickY() * 5.0f * DegToRad;
	clampMe(transform.rotation.x, -30*DegToRad, 85*DegToRad);

	VECTOR3 eye = VECTOR3(0, 0, -6)
		* XMMatrixRotationX(transform.rotation.x)
		* XMMatrixRotationY(transform.rotation.y)
		+ VECTOR3(0, 1.2f, 0) + plPos;
	VECTOR3 look = VECTOR3(0, 2, 0) + plPos;
	GameDevice()->m_vEyePt = eye; // カメラ座標
	GameDevice()->m_vLookatPt = look; // 注視点
	GameDevice()->m_mView = XMMatrixLookAtLH(     // ビューマトリックス
		eye, look,
		VECTOR3(0, 1, 0));
}

float Camera::RStickX()
{
	if (GameDevice()->m_pDI->
		CheckKey(KD_DAT, DIK_RIGHT)) {
		return 1.0f;
	}
	if (GameDevice()->m_pDI->
		CheckKey(KD_DAT, DIK_LEFT)) {
		return -1.0f;
	}
	if (GameDevice()->m_pDI->GetJoyNum() == 0) {
		// Joyがつながってない
		return 0.0f;
	}
	auto inp = GameDevice()->m_pDI->GetJoyState();
	float x = (float)inp.lRx;
	x /= 65535.0f;
	x = x * 2.0f - 1.0f;
	if (x < 0.1f && x > -0.1f)
		x = 0.0f;
	return x;
}

float Camera::RStickY()
{
	if (GameDevice()->m_pDI->
		CheckKey(KD_DAT, DIK_DOWN)) {
		return 1.0f;
	}
	if (GameDevice()->m_pDI->
		CheckKey(KD_DAT, DIK_UP)) {
		return -1.0f;
	}
	if (GameDevice()->m_pDI->GetJoyNum() == 0) {
		// Joyがつながってない
		return 0.0f;
	}
	auto inp = GameDevice()->m_pDI->GetJoyState();
	float x = (float)inp.lRy;
	x /= 65535.0f;
	x = x * 2.0f - 1.0f;
	if (x < 0.1f && x > -0.1f)
		x = 0.0f;
	return x;
}
