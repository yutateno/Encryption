#include "MediaLoad.hpp"

using namespace std;

// ファイルサイズを調べる
unsigned int MediaLoad::file_size(ifstream &fin)
{
	unsigned int pos = fin.tellg(); // 現在位置保存

	unsigned int size = fin.seekg(0, ios::end).tellg(); // 最後にシークして位置取得→サイズ

	fin.seekg(pos); // 元の位置に戻す

	return size; // サイズを返す
}

// ファイルの読み込み
void MediaLoad::MyLoad(string path, int& file, ELOADFILE type)
{
	vector<BYTE> data;  // ファイルデータ
	UINT size;          // ファイルサイズ
	string outstr;		// 出力するファイル名

	// ファイルの読み込み
	ifstream fin(path.c_str(), ios::binary); // ファイルオープン

	size = file_size(fin); // ファイルサイズ取得
	data.resize(size); // メモリ確保
	fin.read((char*)&data[0], size); // 読み込み
	fin.close();

	// 解読
	// 全データループ
	for (UINT i = 0; i < size; i += 5)
	{
		data[i] = (data[i] ^ rad);
	}

	//保存
	outstr = path;
	outstr.append("del");
	ofstream fout(outstr.c_str(), ios::binary);
	fout.write((char*)&data[0], size);
	fout.close();

	// ロードする
	switch (type)
	{
	case ELOADFILE::graph:
		file = LoadGraph(outstr.c_str());
		break;
	case ELOADFILE::soundmem:
		file = LoadSoundMem(outstr.c_str());
		break;
	case ELOADFILE::mv1model:
		file = MV1LoadModel(outstr.c_str());
		break;
	default:
		break;
	}

	// 一時出力したものを削除
	std::remove(outstr.c_str());
}
