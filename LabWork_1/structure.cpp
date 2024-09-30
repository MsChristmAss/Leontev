#include "structure.h"
#include <iostream>
#include <fstream>
#include <conio.h>

int readNumberWithGetLine() {
	int number;
	while (true) {
		cin >> number;
		if (cin.good() && number >= 0)
		{
			return number;
		}
		else {
			cout << "������ �����, ������� ��� ���:  ";
		}
		cin.clear(); // ���������� ��������� ������
		cin.ignore(10000, '\n');
	}
}

void add_pipe(pipe& p)
{
	system("cls");
	//https://metanit.com/cpp/tutorial/5.8.php
	cout << "-------------------------         �����         -------------------------" << endl;
	cout << "������� �������� �����:  ";
	getline(cin, p.name_pipe);
	cout << "������� ����� �����:  ";
	p.length = readNumberWithGetLine();
	cout << "������� ������� �����:  ";
	p.diameter = readNumberWithGetLine();
	cout << "����� ����� ������? (y/n)  ";
	char B;
	while (true) {
		cin >> B;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (B == 'y' || B == 'n') {
			if (B == 'y') {
				p.UnderRepair = true;
			}
			else {
				p.UnderRepair = false;
			}
			break;
		}
		else {
			cout << "������ �����, ������� ��� ���:  ";
		}
	}
}

void add_cs(compressor_station& cs)
{
	system("cls");
	cout << endl << "------------------------- ������������� ������� -------------------------" << endl;
	cout << "������� �������� ��:  ";
	getline(cin, cs.name_cs);
	cout << "������� ���������� �����:  ";
	cs.quantity = readNumberWithGetLine();
	cout << "������� ���������� ������� �����:  ";
	while (true) {
		cs.quantity_cs = readNumberWithGetLine();
		if (cs.quantity_cs <= cs.quantity) {
			break;
		}
		else {
			cout << "���-�� ������� ����� �� ����� ���� ������ ���-�� �����!!!";
		}
	}	
	cout << "������� �������������:  ";
	cs.effective_cs = readNumberWithGetLine();

}

void view(const pipe& p, const compressor_station& cs)
{
	system("cls");
	cout << "-------------------------         �����         -------------------------" << endl;
	cout << "�������� �����: ";
	if (p.name_pipe == "") {
		cout << "������ �����������" << endl;
	}
	else {
		cout << p.name_pipe << endl;
	}
	cout << "����� �����: " << (p.length == 0 ? "������ �����������" : to_string(p.length)) << endl; //��������� �������� ����� ��� condition ? value_if_true : value_if_false.
	cout << "������� �����: " << (p.diameter == 0 ? "������ �����������" : to_string(p.diameter)) << endl;
	if (p.UnderRepair) {
		cout << "������: ��������� ������" << endl;
	}
	else {
		cout << "������: ������" << endl;
	}
	cout << endl << "------------------------- ������������� ������� -------------------------" << endl;
	cout << "�������� ��: ";
	if (cs.name_cs == "") {
		cout << "������ �����������" << endl;
	}
	else {
		cout << cs.name_cs << endl;
	}
	cout << "���������� �����:  " << (cs.quantity == 0 ? "��� �����" : to_string(cs.quantity)) << endl;
	cout << "���������� ����� � ������:  " << (cs.quantity_cs == 0 ? "��� ������� �����" : to_string(cs.quantity_cs)) << endl;
	cout << "�������������:  " << (cs.effective_cs == 0 ? "������ �����������" : to_string(cs.effective_cs)) << endl;

}

