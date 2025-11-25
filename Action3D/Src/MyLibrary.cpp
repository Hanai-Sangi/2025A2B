#include "MyLibrary.h"

bool MyLibrary::CollideSegmentToSphere(VECTOR3 seg1, VECTOR3 seg2, VECTOR3 center, float radius)
{
	VECTOR3 a = center - seg1;
	VECTOR3 b = seg2 - seg1;
	float len2 = b.LengthSquare();
	float t = dot(a, b) / len2;
	if (t < 0.0f) {
		VECTOR3 v = center - seg1;
		if (v.LengthSquare() < radius * radius) {
			return true;
		}
	} else if (t > 1.0f) {
		VECTOR3 v = center - seg2;
		if (v.LengthSquare() < radius * radius) {
			return true;
		}
	} else {
		float n2 = t*t * len2;
		float c2 = a.LengthSquare() - n2;
		if (c2 < radius*radius) {
			return true;
		}
	}
	return false;
}

void MyLibrary::DrawSphere(const VECTOR3& center, float radius, DWORD color)
{
	CSprite spr;
	for (int j = 0; j < 12; j++) {
		float rz = XM_PI * j / 12;
		float y = cos(rz)*radius ;
		float d = sin(rz)*radius;
		float rz2 = XM_PI * (j+1) / 12;
		float y2 = cos(rz2) * radius;
		float d2 = sin(rz2) * radius;
		for (int i = 0; i < 12; i++) {
			float r = XM_2PI * i / 12;
			float z = cos(r) * d;
			float x = sin(r) * d;
			float r2 = XM_2PI * (i + 1) / 12;
			float z2 = cos(r2) * d;
			float x2 = sin(r2) * d;
			spr.DrawLine3D(center + VECTOR3(x2, y, z2),
				center + VECTOR3(x, y, z), color);
			float z3 = cos(r) * d2;
			float x3 = sin(r) * d2;
			spr.DrawLine3D(center + VECTOR3(x, y, z),
				center + VECTOR3(x3, y2, z3), color);
		}
	}
}
