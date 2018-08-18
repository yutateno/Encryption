#include "Draw.hpp"


Draw::Draw(int draw1, int draw2)
{
	this->draw1 = draw1;
	this->draw2 = draw2;
}

Draw::~Draw()
{
	DeleteGraph(draw2);
	DeleteGraph(draw1);
}

void Draw::Process()
{
	DrawGraph(0, 0, draw1, false);
	DrawGraph(320, 0, draw2, false);
}
