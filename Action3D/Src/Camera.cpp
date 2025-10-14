#include "Camera.h"

Camera::Camera()
{
	VECTOR3 eye = VECTOR3(0, 2, -5);
	VECTOR3 look = VECTOR3(0,1,0);
	GameDevice()->m_vEyePt = eye; // カメラ座標
	GameDevice()->m_vLookatPt = look; // 注視点
	GameDevice()->m_mView = XMMatrixLookAtLH(     // ビューマトリックス
		eye, look,
		VECTOR3(0, 1, 0));
}

Camera::~Camera()
{
}

void Camera::Update()
{
	transform.rotation.y += RStickX() * 5.0f * DegToRad;

	VECTOR3 eye = VECTOR3(0, 2, -5)
		* XMMatrixRotationY(transform.rotation.y);
	VECTOR3 look = VECTOR3(0, 1, 0);
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
