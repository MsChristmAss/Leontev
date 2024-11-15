#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <fstream>
using namespace std;
class CS {
public:
	int index;
	string name;
	int quantity;
	int work_quantity;
	float effective_cs;

	// ����������� ������
	CS(int index, const string& name, int quantity, int work_quantity, float effective_cs)
		: index(index), name(name), quantity(quantity), work_quantity(work_quantity), effective_cs(effective_cs) {}

	// ��������� ��� ��������� ��� ������������� � unordered_set
	bool operator==(const CS& other) const {
		return index == other.index && name == other.name && quantity == other.quantity && work_quantity == other.work_quantity && effective_cs == other.effective_cs;
	}

	// �������� ���-������� ��� CS
	struct Hash {
		size_t operator()(const CS& cs) const {
			return hash<int>()(cs.index) ^ hash<string>()(cs.name) ^ hash<int>()(cs.quantity) ^ hash<int>()(cs.work_quantity) ^ hash<float>()(cs.effective_cs);
		}
	};
};

void addCS();
void save(int choice);
void savePipesToFile(const unordered_set<Pipe, Pipe::Hash>& pipes);
void saveCSsToFile(const unordered_set<CS, CS::Hash>& css);
void load();
void download(string file);

template<typename T>
bool validateInput(const string& input, T& result, int min, int max) {
    // �������� ���� string
    if constexpr (is_same<T, string>::value) {
        if (input.empty()) {
            cout << "������: ������ �����." << endl;
            return false;
        }
        result = input;
        return true;
    }
    // �������� ���� int
    else if constexpr (is_same<T, int>::value) {
        try {
            size_t pos;
            int value = stoi(input, &pos);
            if (pos < input.size()) {
                cout << "������: ������������ ���� �����." << endl;
                return false;
            }
            if (value < min || value > max) {
                cout << "������: �������� ��� ���������" << endl;
                return false;
            }
            result = value;
            return true;
        }
        catch (const invalid_argument&) {
            cout << "������: ������������ ���� �����." << endl;
            return false;
        }
        catch (const out_of_range&) {
            cout << "������: �������� ��� ��������� int." << endl;
            return false;
        }
    }
    // �������� ���� double
    else if constexpr (is_same<T, double>::value) {
        try {
            size_t pos;
            double value = stod(input, &pos);
            if (pos < input.size()) {
                cout << "������: ������������ ���� ����� � ��������� ������." << endl;
                return false;
            }
            if (value < min || value > max) {
                cout << "������: �������� ��� ���������" << endl;
                return false;
            }
            result = value;
            return true;
        }
        catch (const invalid_argument&) {
            cout << "������: ������������ ���� ����� � ��������� ������." << endl;
            return false;
        }
        catch (const out_of_range&) {
            cout << "������: �������� ��� ��������� double." << endl;
            return false;
        }
    }
    return false;
}