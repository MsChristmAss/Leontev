#pragma once
#include <string>
using namespace std;

struct pipe {
	string name_pipe; //������������ �������(��������)
	unsigned int length; //����� �����
	unsigned int diameter; //������� �����
	bool UnderRepair;
};
struct compressor_station {
	string name_cs; //�������� ��
	unsigned int quantity; // ���-�� �����
	unsigned int quantity_cs; // ���-�� ����� � ������
	int effective_cs; //�������������
};

void add_pipe(pipe& p);
void add_cs(compressor_station& cs);
void view(const pipe& p, const compressor_station& cs);
void edit_pipe(pipe& p);
void edit_cs(compressor_station& cs);
void save_p_and_cs(const pipe& p, const compressor_station& cs);
void download_p_and_cs(pipe& p, compressor_station& cs);