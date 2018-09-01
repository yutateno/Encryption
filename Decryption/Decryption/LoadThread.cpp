#include "LoadThread.hpp"

using namespace std;

std::mutex mtx;

void LoadThread::MyNextLoad(std::string path, int& file, ELOADFILE type)
{
	std::lock_guard<std::mutex> lock(mtx);

	MediaLoad::MyLoad(path, file, type);
}

LoadThread::LoadThread()
{
	num = 0; 
	maindraw = new LoadMainThread();
}

LoadThread::~LoadThread()
{
	delete maindraw;
}

void LoadThread::Run(int max, std::string* path, ELOADFILE* type)
{
	if (num < max)
	{
		fileName.push_back(0);
		ths = std::thread(&LoadThread::MyNextLoad, this, path[num], ref(fileName[num]), type[num]);
		ths.join();
		num++;
		ClearDrawScreen();
		maindraw->Process(num);			// ÉçÅ[ÉhâÊñ 
		ScreenFlip();
		Run(max, path, type);
	}
}

vector<int> LoadThread::GetFile()
{
	return fileName;
}
