#include "LoadThread.hpp"

using namespace std;

std::mutex mtx;

void LoadThread::MyNextLoad(std::string path, int& file, ELOADFILE type)
{
	std::lock_guard<std::mutex> lock(mtx);

	MediaLoad::MyLoad(path, file, type);
}

void LoadThread::Run(int max, std::string* path, ELOADFILE* type)
{
	for (int i = 0; i != max; ++i)
	{
		ths.push_back(std::thread(&LoadThread::MyNextLoad, this, path[i], ref(fileName[i]), type[i]));
	}
}

bool LoadThread::Stop()
{
	for (auto &th : ths)
	{
		th.join();
	}
	return true;
}

int LoadThread::GetFile(int number)
{
	return fileName[number];
}
