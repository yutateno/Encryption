#pragma once
#include "DxLib.h"

class Draw
{
private:
	int draw1, draw2;

public:
	Draw(int draw1, int draw2);
	~Draw();

	void Process();
};

