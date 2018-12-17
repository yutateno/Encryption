#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned char BYTE;
typedef unsigned int UINT;

// �t�@�C���T�C�Y��Ԃ�
UINT file_size(ifstream &fin);


int main(int argc, char *argv[])
{
	// �h���b�O�A���h�h���b�v�łȂ��N���̎�
	if (argc < 2)
	{
		cerr << "�t�@�C�����h���b�O�h���b�v���Ă�������" << endl;
		int charTemp = getchar();
		return -1;
	}

	// ���̓t�@�C���p�X
	string path = argv[1];

	// �t�@�C���f�[�^
	vector<BYTE> data;

	// �t�@�C���T�C�Y
	UINT size;

	// �Í��L�[
	int rad = 0x2546;

	// ���P�[���ݒ�
	setlocale(LC_ALL, "japanese");


	/// �t�@�C���̓ǂݍ���---------------------------------

	// �t�@�C���I�[�v��
	ifstream fin(path.c_str(), ios::binary);

	if (fin.fail()) return -1; // �t�@�C���ǂݍ��݃G���[

	// �t�@�C���T�C�Y�擾
	size = file_size(fin);

	// �������m��
	data.resize(size);

	// �ǂݍ���
	fin.read((char*)&data[0], size);

	// �t�@�C���N���[�Y
	fin.close();
	

	/// �Í���--------------------------------------------------

	// �S�f�[�^���[�v
	for (UINT i = 0; i < size; i += 5)
	{
		data[i] = (data[i] ^ rad);	// �r���I�_���a�����
	}
	
	/// �ۑ�------------------------------------------------------

	// �t�@�C���p�X�̉��u��
	string outstr = path;

	outstr.erase(outstr.end() - 2, outstr.end());	// �g���q�̌��2��ύX���邽�ߍ폜
	outstr.append("yn");							// �����p�Ɋg���q���쐬
	ofstream fout(outstr.c_str(), ios::binary);		// �o�C�i���f�[�^�Ƃ��ď������ނ悤�ݒ�
	fout.write((char*)&data[0], size);				// ��������
	fout.close();									// �t�@�C�����N���[�Y
	
	printf("�Í�������");			// �m�F�p�\��
	int charTemp = getchar();						// ���͑҂�

	return 0;

}

// �t�@�C���T�C�Y��Ԃ�
UINT file_size(ifstream &fin)
{
	UINT pos = fin.tellg();		// ���݈ʒu�ۑ�

	UINT size = fin.seekg(0, ios::end).tellg();		// �Ō�ɃV�[�N���Ĉʒu�擾���T�C�Y

	fin.seekg(pos);		// ���̈ʒu�ɖ߂�

	return size;	// �T�C�Y��Ԃ�
}