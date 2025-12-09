#pragma once
#include "Object3D.h"
#include "Golem.h"
#include <list>

class EnemyManager : public Object3D
{
public:
	EnemyManager();
	~EnemyManager();
	bool CanAttack(Golem* golem);
	void CancelAttack(Golem* golem); // UŒ‚‚ğ‚â‚ß‚é
private:
	std::list<Golem*> waiting; // ‘Ò‚¿s—ñ
};
