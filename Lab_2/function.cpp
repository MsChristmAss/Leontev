#include "pipe.h"
#include "cs.h"

#include <unordered_set>
#include <iostream>
#include <algorithm> // ��� distance
using namespace std;

// ���������� unordered_set ��� �������� ����
unordered_set<Pipe, Pipe::Hash> pipes;
unordered_set<CS, CS::Hash> css;

// ������� ���������� ����� � unordered_set
void addPipe() {
	bool repairStatus;
	string name = getInput<string>("������� ��� �����: ", 1, 1);
	int length = getInput<int>("������� ����� ����� (� ������): ", 1, 2147483647);
	int diameter = getInput<int>("������� ������� ����� (� ����������): ", 1, 2147483647);
	int status = getInput<int>("������� �������������� � ������� (1 - '������� �������', 0 - '�� ������� �������'): ", 0, 1);
	if (status == 1) {
		repairStatus = true;
	}
	else {
		repairStatus = false;
	}
	Pipe newPipe(name, length, diameter, repairStatus);
	auto result = pipes.insert(newPipe);
	if (result.second) {
		cout << "����� ���������... " << endl;
	}
	else {
		cout << "����� � ����� ������ � ���������������� ��� ����������!" << endl;
	}
}

void addCS() {
	string name = getInput<string>("������� ��� ��: ", 0, 0);
	int quantity = getInput<int>("������� ���-�� �����: ", 1, 2147483647);;
	int work_quantity = getInput<int>("������� ���-�� ���������� �����: ", 0, quantity);
	float effective_cs = work_quantity * 100.0 / quantity;
	CS newCS(name, quantity, work_quantity, effective_cs);
	auto result = css.insert(newCS);
	if (result.second) {
		cout << "�� ���������... " << endl;
	}
	else {
		cout << "�� � ����� ������ � ���������������� ��� ����������!" << endl;
	}
}

void Print() {
	cout << "1 - ������� ��� �����\n2 - ������� ��� ��\n3 - ������� ��\n\n";
	int input = getInput<int>("������� ", 1, 3);
	if (input == 1) {
		cout << "---------------- ����� ----------------" << endl;
		if (pipes.empty()) {
			cout << "��� ��������� ����." << endl;
		}
		else {
			for (const auto& pipe : pipes) {
				cout << "��� �����: " << pipe.name << endl;
				cout << "�����: " << pipe.length << " �" << endl;
				cout << "�������: " << pipe.diameter << " ��" << endl;
				cout << "������ �������: " << (pipe.repairStatus ? "������� �������" : "�� ������� �������") << endl;
				cout << "---------------------------------------" << endl;
			}
		}
	}
	else if (input == 2) {
		cout << "----------------- �� -----------------" << endl;
		if (css.empty()) {
			cout << "��� ��������� ��." << endl;
		}
		else {
			for (const auto& cs : css) {
				cout << "��� ��: " << cs.name << endl;
				cout << "���-�� �����: " << cs.quantity << endl;
				cout << "���-�� ������� �����: " << cs.work_quantity << endl;
				cout << "% ������� �����: " << cs.effective_cs << endl;
				cout << "--------------------------------------" << endl;
			}
		}
	}
	else if (input == 3) {
		cout << "---------------- ����� ----------------" << endl;
		if (pipes.empty()) {
			cout << "��� ��������� ����." << endl;
		}
		else {
			for (const auto& pipe : pipes) {
				cout << "��� �����: " << pipe.name << endl;
				cout << "�����: " << pipe.length << " �" << endl;
				cout << "�������: " << pipe.diameter << " ��" << endl;
				cout << "������ �������: " << (pipe.repairStatus ? "������� �������" : "�� ������� �������") << endl;
				cout << "---------------------------------------" << endl;
			}
		}
		cout << "----------------- �� -----------------" << endl;
		if (css.empty()) {
			cout << "��� ��������� ��." << endl;
		}
		else {
			for (const auto& cs : css) {
				cout << "��� ��: " << cs.name << endl;
				cout << "���-�� �����: " << cs.quantity << endl;
				cout << "���-�� ������� �����: " << cs.work_quantity << endl;
				cout << "% ������� �����: " << cs.effective_cs << endl;
				cout << "--------------------------------------" << endl;
			}
		}
	}
	cout << endl;

}

void remove() {
	cout << "�������:\n1 - �� �������\n2 - �� �����\n3 - �� �������\n4 - ��" << endl << endl;
	int input = getInput<int>("�����:\n1 - �����\n2 - ��\n\n������� ", 1, 2);
	int choice = getInput<int>("\n������� ", 1, 4);
	switch (choice)
	{
	case 1:
		removeByIndex(getInput<int>("������ ", 0, pipes.size()), input);
		break;
	case 2:
		removeByName(getInput<string>("��� ", 0, 1), input);
		break;
	case 3:

	{
		bool status;
		if (getInput<int>("1 - '������� �������', 0 - '�� ������� �������': ", 0, 1) == 1) {
			status = true;
		}
		else {
			status = false;
		}
		removePipesByStatus(status);
	}
		break;
	case 4:
		removeAll();
		break;
	}

}

void removeAll()
{
	cout << "1 - �����\n2 - ��" << endl;
	if (getInput<int>("������� ", 1, 2) == 1)
	{
		auto it = pipes.begin();
		while (it != pipes.end()) {
			it = pipes.erase(it);
		}
		cout << "��� ����� �������..." << endl;
	}
	else
	{
		auto it = css.begin();
		while (it != css.end()) {
			it = css.erase(it);
		}
		cout << "��� �� �������..." << endl;
	}

}

void removeByIndex(int index, int choice) {
	if (choice == 1)
	{
		if (index < 0 || index >= static_cast<int>(pipes.size())) {
			cout << "�������� ������." << endl;
			return;
		}
		auto it = pipes.begin();
		advance(it, index);
		pipes.erase(it);
		cout << "����� ������� �� ������� " << index << endl;
	}
	else
	{
		if (index < 0 || index >= static_cast<int>(css.size())) {
			cout << "�������� ������." << endl;
			return;
		}
		auto it = css.begin();
		advance(it, index);
		css.erase(it);
		cout << "�� ������� �� ������� " << index << endl;
	}
}

void removeByName(const string& name, int choice) {
	if (choice == 1)
	{
		auto it = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) {
			return pipe.name == name;
			});
		if (it != pipes.end()) {
			pipes.erase(it);
			cout << "����� � ������ \"" << name << "\" �������." << endl;
		}
		else {
			cout << "����� � ����� ������ �� �������." << endl;
		}
	}
	else{
		auto it = find_if(css.begin(), css.end(), [&](const CS& cs) {
			return cs.name == name;
			});
		if (it != css.end()) {
			css.erase(it);
			cout << "�� � ������ \"" << name << "\" �������." << endl;
		}
		else {
			cout << "�� � ����� ������ �� �������." << endl;
		}
	}
}

void removePipesByStatus(bool status) {
	auto it = pipes.begin();
	bool found = false;
	while (it != pipes.end()) {
		if (it->repairStatus == status) {
			it = pipes.erase(it);
			found = true;
		}
		else {
			++it;
		}
	}
	if (found) {
		cout << "����� �� �������� \"" << (status ? "������� �������" : "�� ������� �������") << "\" �������." << endl;
	}
	else {
		cout << "����� � ����� �������� �� �������." << endl;
	}
}

void editPipe(int index) {	
	if (index < 0 || index >= static_cast<int>(pipes.size())) {
		cout << "�������� ������." << endl;
		return;
	}
	auto it = pipes.begin();
	advance(it, index);
	Pipe updatedPipe = *it;
	updatedPipe.repairStatus = !updatedPipe.repairStatus;

	// ������� �������� � ��������� ����������� �����
	pipes.erase(it);
	pipes.insert(updatedPipe);

	cout << "������ ����� ������� ��: "
		<< (updatedPipe.repairStatus ? "������� �������" : "�� ������� �������") << endl;
}

void editCS(int index) {	
	if (index < 0 || index >= static_cast<int>(css.size())) {
		cout << "�������� ������." << endl;
		return;
	}
	auto it = css.begin();
	advance(it, index);
	CS updatedCS = *it;
	updatedCS.work_quantity = getInput<int>("������� ���-�� ������� �����: ",1, updatedCS.quantity);
	css.erase(it);
	css.insert(updatedCS);
	cout << "���-�� ������� ����� �������� �� " << updatedCS.work_quantity << endl;
}

void edit() {
	cout << "�������������:\n1 - �����\n2 - ��\n\n";
	if (getInput<int>("������� ", 1, 2) == 1) {
		if (pipes.size() == 0) {
			cout << "��� ���� ��� ��������������..." << endl;
			return;
		}
		editPipe(getInput<int>("������ ", 0, pipes.size()));
	}
	else {
		if (css.size() == 0) {
			cout << "��� �� ��� ��������������..." << endl;
			return;
		}
		editCS(getInput<int>("������ ", 0, css.size()));
	}
}
