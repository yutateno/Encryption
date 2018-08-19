#include "LoadMainThread.hpp"

LoadMainThread::LoadMainThread()
{
	draw = 0;
	flag = false;
	MediaLoad::MyLoad("1.jyn", draw, ELOADFILE::graph);
}

LoadMainThread::~LoadMainThread()
{
	DeleteGraph(draw);
}

void LoadMainThread::Process()
{
	int i = 0;
	do
	{
		ClearDrawScreen();
		DrawGraph(++i, 0, draw, false);
		ScreenFlip();
	} while (!flag);
}

void LoadMainThread::Run()
{
	main_thre = std::thread(&LoadMainThread::Process, this);
}

bool LoadMainThread::Stop()
{
	main_thre.join();
	return true;
}

void LoadMainThread::SetThreadEndFlag(bool flag)
{
	this->flag = flag;
}
