#include "MediaLoad.hpp"

using namespace std;

// �t�@�C���T�C�Y�𒲂ׂ�
unsigned int MediaLoad::file_size(ifstream &fin)
{
	unsigned int pos = fin.tellg(); // ���݈ʒu�ۑ�

	unsigned int size = fin.seekg(0, ios::end).tellg(); // �Ō�ɃV�[�N���Ĉʒu�擾���T�C�Y

	fin.seekg(pos); // ���̈ʒu�ɖ߂�

	return size; // �T�C�Y��Ԃ�
}

// �t�@�C���̓ǂݍ���
void MediaLoad::MyLoad(string path, int& file, ELOADFILE type)
{
	vector<BYTE> data;  // �t�@�C���f�[�^
	UINT size;          // �t�@�C���T�C�Y
	string outstr;		// �o�͂���t�@�C����

	// �t�@�C���̓ǂݍ���
	ifstream fin(path.c_str(), ios::binary); // �t�@�C���I�[�v��

	size = file_size(fin); // �t�@�C���T�C�Y�擾
	data.resize(size); // �������m��
	fin.read((char*)&data[0], size); // �ǂݍ���
	fin.close();

	// ���
	// �S�f�[�^���[�v
	for (UINT i = 0; i < size; i += 5)
	{
		data[i] = (data[i] ^ rad);
	}

	//�ۑ�
	outstr = path;
	outstr.append("del");
	ofstream fout(outstr.c_str(), ios::binary);
	fout.write((char*)&data[0], size);
	fout.close();

	// ���[�h����
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

	// �ꎞ�o�͂������̂��폜
	std::remove(outstr.c_str());
}
