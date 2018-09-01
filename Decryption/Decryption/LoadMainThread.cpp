#include "LoadMainThread.hpp"

LoadMainThread::LoadMainThread()
{
	draw = 0;
	MediaLoad::MyLoad("1.jyn", draw, ELOADFILE::graph);
}

LoadMainThread::~LoadMainThread()
{
	DeleteGraph(draw);
}

void LoadMainThread::Process(int num)
{
	DrawGraph(num * 64, 0, draw, false);
}
