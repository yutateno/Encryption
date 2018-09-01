#include "Draw.hpp"

Draw::Draw()
{
	MediaLoad::MyLoad("1.jyn", draw1, ELOADFILE::graph);	// ’Êíƒ[ƒh‚·‚é
	MediaLoad::MyLoad("2.jyn", draw2, ELOADFILE::graph);
}

Draw::Draw(int draw1, int draw2)
{
	this->draw1 = draw1;
	this->draw2 = draw2;
}

Draw::Draw(std::vector<int> draw)
{
	this->draw1 = draw[0];
	this->draw2 = draw[1];
	this->draw3 = draw[2];
	this->draw4 = draw[3];
	this->draw5 = draw[4];
	this->draw6 = draw[5];
	this->draw7 = draw[6];
	this->draw8 = draw[7];
	this->draw9 = draw[8];
	this->draw10 = draw[9];
}

Draw::~Draw()
{
	DeleteSoundMem(draw10);
	DeleteGraph(draw9);
	DeleteGraph(draw8);
	DeleteGraph(draw7);
	DeleteGraph(draw6);
	DeleteGraph(draw5);
	DeleteGraph(draw4);
	DeleteGraph(draw3);
	DeleteGraph(draw2);
	DeleteGraph(draw1);
}

void Draw::Process()
{
	DrawGraph(0, 0, draw1, false);
	DrawGraph(320, 0, draw2, false);
	DrawGraph(0, 96, draw3, false);
	DrawGraph(320, 96, draw4, false);
	DrawGraph(0, 192, draw5, false);
	DrawGraph(320, 192, draw6, false);
	DrawGraph(0, 288, draw7, false);
	DrawGraph(320, 288, draw8, false);
	DrawGraph(0, 470, draw9, false);
	PlaySoundMem(draw10, DX_PLAYTYPE_BACK, false);
}
