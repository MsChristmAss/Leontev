#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <stdexcept>
using namespace std;
class Pipe {
public:
	int index;
	string name;                // ��� �����
	int length;                 // ����� �����
	int diameter;               // ������� �����
	bool repairStatus;          // �������������� � �������

	// ����������� ������
	Pipe(int index, const string& name, int length, int diameter, bool repairStatus)
		: index(index), name(name), length(length), diameter(diameter), repairStatus(repairStatus) {}

	// ��������� ��� ��������� ��� ������������� � unordered_set
	bool operator==(const Pipe& other) const {
		return index == other.index && name == other.name && length == other.length && diameter == other.diameter && repairStatus == other.repairStatus;
	}

	// �������� ���-������� ��� Pipe
	struct Hash {
		size_t operator()(const Pipe& p) const {
			return hash<int>()(p.index) ^ hash<string>()(p.name) ^ hash<int>()(p.length) ^ hash<int>()(p.diameter) ^ hash<bool>()(p.repairStatus);
		}
	};
};

void addPipe();
void Print();
void removeByIndex(int index);
void removeByName(const string& name);
void removePipesByStatus(bool status);
void removeAll();
void remove();
void edit();
void logInput(const string& message);


template<typename T>
T getInput(string str, int min, int max) {
	string input;
	T result;
	if constexpr (is_same<T, string>::value) {
		while (true) {
			cout << str;
			getline(cin, input);
			logInput(input);
			if (input.empty()) {
				cout << "�� ������ �� �����..." << endl << endl;
				continue;
			}
			result = input;
			return result;
		}
	}
	else if constexpr (is_same<T, int>::value) {
		while (true) {
			cout << str;
			getline(cin, input);
			logInput(input);
			if (input.empty()) {
				cout << "�� ������ �� �����..." << endl << endl;
				continue;
			}

			bool isValid = true;
			for (char c : input) {
				if (!isdigit(c)) {
					cout << "������ ����� �����..." << endl << endl;
					isValid = false;
					break;
				}
			}
			if (isValid) {
				try {
					if (input[0] == '0' && input.size() > 1) {
						cout << "����� �� ����� ���������� � ����..." << endl << endl;
						continue;
					}
					result = stoi(input);
					if (min <= result && result <= max) {
						return result;
					}
					else {
						cout << "����� �� �������� �� ���������..." << endl << endl;
					}
				}
				catch (const invalid_argument& e) {
					cout << "������ ����� �����..." << endl << endl;
				}
				catch (const out_of_range& e) {
					cout << "����� ��� ��������� ��������..." << endl << endl;
				}
			}
		}
	}
}

