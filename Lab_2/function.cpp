#include "pipe.h"
#include "cs.h"

#include <sstream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <iostream>
#include <algorithm> // ��� distance
using namespace std;

// ����������
int indexPipe = 0;
int indexCS = 0;
unordered_set<Pipe, Pipe::Hash> pipes;
unordered_set<CS, CS::Hash> css;


// ������� ��� ����������� ������� ������
void logInput(const string& message) {
	ofstream logFile("log.txt", ios::app);
	if (logFile.is_open()) {
		logFile << message << endl;
	}
	logFile.close();
}

// ������� ���������� ����� � unordered_set
void addPipe() {  // ������������� ������������ �������
	++indexPipe;
	bool repairStatus;
	string name = getInput<string>("������� ��� �����: ", 1, 1);
	int length = getInput<int>("������� ����� ����� (� ������): ", 1, INT_MAX);
	int diameter = getInput<int>("������� ������� ����� (� �����������): ", 1, INT_MAX);
	int status = getInput<int>("������� �������������� � ������� (1 - '������� �������', 0 - '�� ������� �������'): ", 0, 1);
	repairStatus = (status == 1);

	Pipe newPipe(indexPipe, name, length, diameter, repairStatus);
	auto result = pipes.insert(newPipe);
	if (result.second) {
		cout << "����� ���������..." << endl;
	}
	else {
		cout << "����� � ����� ������ � ���������������� ��� ����������!" << endl;
	}
}

// ������� ���������� �� � unordered_set
void addCS() {  // ������������� ������������ �������
	++indexCS;
	string name = getInput<string>("������� ��� ��: ", 0, 0);
	int quantity = getInput<int>("������� ���-�� �����: ", 1, INT_MAX);
	int work_quantity = getInput<int>("������� ���-�� ���������� �����: ", 0, quantity);
	float effective_cs = work_quantity * 100.0f / quantity;

	CS newCS(indexCS, name, quantity, work_quantity, effective_cs);
	auto result = css.insert(newCS);
	if (result.second) {
		cout << "�� ���������..." << endl;
	}
	else {
		cout << "�� � ����� ������ � ���������������� ��� ����������!" << endl;
	}
}

// ��������� ������� ���������� ����� ������������, ������� ��������� ������ ����� � ����������� ��������.


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
				cout << "������ " << pipe.index << endl;
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
				cout << "������ " << cs.index << endl;
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
				cout << "������ " << pipe.index << endl;
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
				cout << "������ " << cs.index << endl;
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
	cout << "�������:\n1 - �� �������\n2 - �� �����\n3 - �� �������\n4 - ��\n0 - �����" << endl << endl;
	int choice = getInput<int>("\n������� ", 1, 4);
	switch (choice)
	{
	case 0:
		return;
	case 1:
		removeByIndex(getInput<int>("������ ", 1, INT_MAX));
		break;
	case 2:
		removeByName(getInput<string>("��� ", 0, 1));
		break;
	case 3:
		bool status;
		if (getInput<int>("1 - '������� �������', 0 - '�� ������� �������': ", 0, 1) == 1) {
			status = true;
		}
		else {
			status = false;
		}
		removePipesByStatus(status);
		break;
	case 4:
		removeAll();
		break;
	}
}

void removeAll()
{
	cout << "1 - �����\n2 - ��" << endl;
	if (getInput<int>("������� �������� ���� ", 1, 2) == 1)
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

void removeByIndex(int ind) {
	int choice;
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == ind; });
	auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == ind; });
	if (pipeIt != pipes.end()) {
		cout << "����� � �������� " << ind << " �������." << endl;
		choice = getInput<int>("\n�������?\n�� - 1\n��� - 0\n", 0, 1);
		if (choice == 1) {
			pipes.erase(pipeIt);
			cout << "����� � �������� " << ind << " �������." << endl;
		}
	}
	else {
		cout << "����� � �������� " << ind << " �� �������." << endl;
	}
	if (csIt != css.end()) {
		cout << "�� � �������� " << ind << " �������." << endl;
		choice = getInput<int>("\n�������?\n�� - 1\n��� - 0\n", 0, 1);
		if (choice == 1) {
			css.erase(csIt);
			cout << "�� � �������� " << ind << " �������." << endl;
		}
	}
	else {
		cout << "�� � �������� " << ind << " �� �������." << endl;
	}

}



void removeByName(const string& name) {
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.name == name; });
	auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.name == name; });
	if (pipeIt != pipes.end()) {
		pipes.erase(pipeIt);
		cout << "����� � ������ \"" << name << "\" �������." << endl;
	}
	else {
		cout << "����� � ����� ������ �� �������." << endl;
	}

	if (csIt != css.end()) {
		css.erase(csIt);
		cout << "�� � ������ \"" << name << "\" �������." << endl;
	}
	else {
		cout << "�� � ����� ������ �� �������." << endl;
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



void edit() {
	int index = getInput<int>("������ ", 1, INT_MAX);
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == index; });
	auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == index; });

	if (pipeIt == pipes.end()) {
		cout << "����� � ��������� �������� �� �������." << endl;
		return;
	}
	Pipe updatedPipe = *pipeIt;
	updatedPipe.repairStatus = !updatedPipe.repairStatus;
	pipes.erase(pipeIt);
	pipes.insert(updatedPipe);
	cout << "������ ����� � �������� " << index << " ������� ��: " << (updatedPipe.repairStatus ? "������� �������" : "�� ������� �������") << endl << endl;

	if (csIt == css.end()) {
		cout << "�� � ��������� �������� �� �������." << endl;
		return;
	}
	CS updatedCS = *csIt;
	updatedCS.work_quantity = getInput<int>("������� ����� ���������� ���������� �����: ", 0, updatedCS.quantity);
	updatedCS.effective_cs = updatedCS.work_quantity * 100.0f / updatedCS.quantity;
	css.erase(csIt);
	css.insert(updatedCS);
	cout << "�� � �������� " << index << " ���������. ���������� ������� �����: " << updatedCS.work_quantity << ", �������������: " << updatedCS.effective_cs << "%" << endl;
}

void save(int choice) {
	if (choice == 1) {
		savePipesToFile(pipes);
	}
	else if (choice == 2) {
		saveCSsToFile(css);
	}
	else {
		savePipesToFile(pipes);
		saveCSsToFile(css);
	}
}

void savePipesToFile(const unordered_set<Pipe, Pipe::Hash>& pipes) {
	string fileName = getInput<string>("��� ����� ", 1, 1);
	ofstream outFile(fileName);
	if (outFile.is_open()) {
		if (pipes.size() == 0) {
			outFile << "��� ����";
			return;
		}
		for (const auto& pipe : pipes) {
			outFile << "Pipe\n";
			outFile << pipe.index << "\n";
			outFile << pipe.name << "\n";
			outFile << pipe.length << "\n";
			outFile << pipe.diameter << "\n";
			outFile << (pipe.repairStatus ? "������� �������" : "�� ������� �������") << "\n";
			outFile << "---------------------------------------\n";
		}
		outFile.close();
		cout << "����� ������� ��������� � ����" << endl;
	}
	else {
		cout << "������ �������� ����� ��� ����" << endl;
	}
}

void saveCSsToFile(const unordered_set<CS, CS::Hash>& css) {
	string fileName = getInput<string>("��� ����� ", 1, 1);
	ofstream outFile(fileName);
	if (outFile.is_open()) {
		if (css.size() == 0) {
			outFile << "��� ��";
			return;
		}
		for (const auto& cs : css) {
			outFile << "CS\n";
			outFile << cs.index << "\n";
			outFile << cs.name << "\n";
			outFile << cs.quantity << "\n";
			outFile << cs.work_quantity << "\n";
			outFile << cs.effective_cs << "\n";
			outFile << "--------------------------------------\n";
		}
		outFile.close();
		cout << "�� ������� ��������� � ����" << endl;
	}
	else {
		cout << "������ �������� ����� ��� ��" << endl;
	}
}

void load() {
	string fileName = getInput<string>("��� �����, �� ��������\n����� ��������� ������: ", 1, 1);
	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		cout << "���� �� ������." << endl;
		return;
	}
	string input;
	getline(inFile, input);
	if (input == "��� ��" || input == "��� ����") {
		cout << "� ����� ������ ���..." << endl << endl;
		return;
	}
	download(fileName);
}

void download(string file) {
	int ind;
	int quantity;
	int work_quantity;
	bool repairStatus;
	string name;
	int length;
	int diameter;

	ifstream inFile(file);
	string str;
	{
		while (!inFile.eof()) {
			getline(inFile, str);
			if (str == "Pipe") {
				getline(inFile, str);
				if (validateInput(str, ind, 1, INT_MAX)) {
					ind = stoi(str);
					if (ind <= indexPipe) {
						ind = ++indexPipe;
					}
					else {
						indexPipe = ind;
					}
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, name, 1, 1)) {
					name = str;
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, length, 1, INT_MAX)) {
					length = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, diameter, 1, INT_MAX)) {
					diameter = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, str, 1, 1) && str == "������� �������") {
					repairStatus = true;
				}
				else if (validateInput(str, str, 1, 1) && str == "�� ������� �������") {
					repairStatus = false;
				}
				getline(inFile, str);
				Pipe newPipe(ind, name, length, diameter, repairStatus);
				pipes.insert(newPipe);
			}
			else if (str == "CS") {
				getline(inFile, str);
				if (validateInput(str, ind, 1, INT_MAX)) {
					ind = stoi(str);
					if (ind <= indexCS) {
						ind = ++indexCS;
					}
					else {
						indexCS = ind;
					}
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, name, 1, 1)) {
					name = str;
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, quantity, 1, INT_MAX)) {
					quantity = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, work_quantity, 1, quantity)) {
					work_quantity = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				float effective_cs = work_quantity * 100.0f / quantity;
				CS newCS(ind, name, quantity, work_quantity, effective_cs);
				css.insert(newCS);
				getline(inFile, str);
			}
		}
		inFile.close();
		cout << "������� ���������" << endl;
	}
}

void filterPipeByName(const string& name) {
	cout << "���������� ������ ���� �� �����: \"" << name << "\":" << endl;
	bool found = false;
	for (const auto& pipe : pipes) {
		if (pipe.name.find(name) != string::npos) {  // ���� ��������� ���������
			found = true;
			cout << "������: " << pipe.index << endl;
			cout << "��� �����: " << pipe.name << endl;
			cout << "�����: " << pipe.length << " �" << endl;
			cout << "�������: " << pipe.diameter << " ��" << endl;
			cout << "������ �������: " << (pipe.repairStatus ? "������� �������" : "�� ������� �������") << endl;
			cout << "---------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "����� � ����� ������ �� �������." << endl;
	}
}

void filterCSByName(const string& name) {
	cout << "���������� ������ �� �� �����: \"" << name << "\":" << endl;
	bool found = false;
	for (const auto& cs : css) {
		if (cs.name.find(name) != string::npos) {  // ���� ��������� ���������
			found = true;
			cout << "������: " << cs.index << endl;
			cout << "��� ��: " << cs.name << endl;
			cout << "���������� �����: " << cs.quantity << endl;
			cout << "������� ����: " << cs.work_quantity << endl;
			cout << "�������������: " << cs.effective_cs << "%" << endl;
			cout << "--------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "�� � ����� ������ �� �������." << endl;
	}
}

void filterPipeByRepairStatus(bool repairStatus) {
	cout << "���������� ������ ���� �� ������� \"" << (repairStatus ? "������� �������" : "�� ������� �������") << "\":" << endl;
	bool found = false;
	for (const auto& pipe : pipes) {
		if (pipe.repairStatus == repairStatus) {
			found = true;
			cout << "������: " << pipe.index << endl;
			cout << "��� �����: " << pipe.name << endl;
			cout << "�����: " << pipe.length << " �" << endl;
			cout << "�������: " << pipe.diameter << " ��" << endl;
			cout << "������ �������: " << (pipe.repairStatus ? "������� �������" : "�� ������� �������") << endl;
			cout << "---------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "����� � ��������� �������� �� �������." << endl;
	}
}

void filterCSByUnusedPercentage(float percentage) {
	cout << "���������� ������ �� � ��������� ����������������� ����� >= " << percentage << "%:" << endl;
	bool found = false;
	for (const auto& cs : css) {
		float unusedPercentage = 100.0f - cs.effective_cs;
		if (unusedPercentage >= percentage) {
			found = true;
			cout << "������: " << cs.index << endl;
			cout << "��� ��: " << cs.name << endl;
			cout << "���������� �����: " << cs.quantity << endl;
			cout << "������� ����: " << cs.work_quantity << endl;
			cout << "�������������: " << cs.effective_cs << "%" << endl;
			cout << "����������������� ����: " << unusedPercentage << "%" << endl;
			cout << "--------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "�� � ��������� ��������� ����������������� ����� �� �������." << endl;
	}
}

void filterSearch() {
	cout << "�����:\n"
		<< "1 - ����� �� �����\n"
		<< "2 - ����� �� ������� �������\n"
		<< "3 - �� �� �����\n"
		<< "4 - �� �� �������� ����������������� �����\n"
		<< "0 - �����" << endl;

	int choice = getInput<int>("�������� �������: ", 0, 4);

	switch (choice) {
	case 1: {
		string name = getInput<string>("������� ��� �����: ", 1, 1);
		filterPipeByName(name);
		break;
	}
	case 2: {
		int status = getInput<int>("������� ������ ������� (1 - ������� �������, 0 - �� ������� �������): ", 0, 1);
		filterPipeByRepairStatus(status == 1);
		break;
	}
	case 3: {
		string name = getInput<string>("������� ��� ��: ", 1, 1);
		filterCSByName(name);
		break;
	}
	case 4: {
		float percentage = getInput<float>("������� ����������� ������� ����������������� �����: ", 0, 100);
		filterCSByUnusedPercentage(percentage);
		break;
	}
	case 0:
		return;
	default:
		cout << "�������� �����. ��������� �������." << endl;
	}
}

