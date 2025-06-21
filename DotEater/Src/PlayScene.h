#pragma once
#include "SceneBase.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	void Go();
	bool CanMove();
private:
	// ��ԑJ��
	enum State {
		S_Ready = 0,
		S_Play,
		S_TimeUp,
	};
	State state;
};
