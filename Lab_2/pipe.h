#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <stdexcept>
using namespace std;
class Pipe {
public:
	string name;                // имя трубы
	int length;                 // длина трубы
	int diameter;               // диаметр трубы
	bool repairStatus;          // характеристика в ремонте

	// Конструктор класса
	Pipe(const string& name, int length, int diameter, bool repairStatus)
		: name(name), length(length), diameter(diameter), repairStatus(repairStatus) {}

	// Операторы для сравнения для использования в unordered_set
	bool operator==(const Pipe& other) const {
		return name == other.name && length == other.length && diameter == other.diameter && repairStatus == other.repairStatus;
	}

	// Описание хеш-функции для Pipe
	struct Hash {
		size_t operator()(const Pipe& p) const {
			return hash<string>()(p.name) ^ hash<int>()(p.length) ^ hash<int>()(p.diameter) ^ hash<bool>()(p.repairStatus);
		}
	};
};

void addPipe();
void Print();
void removeByIndex(int index, int choice);
void removeByName(const string& name, int choice);
void removePipesByStatus(bool status);
void removeAll();
void remove();
void editPipe(int index);
void edit();


template<typename T>
T getInput(string str, int min, int max) {
	string input;
	T result;
	if constexpr (is_same<T, string>::value) {
		while (true) {
			cout << str;
			getline(cin, input);
			if (input.empty()) {
				cout << "Вы ничего не ввели..." << endl << endl;
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
			if (input.empty()) {
				cout << "Вы ничего не ввели..." << endl << endl;
				continue;
			}

			bool isValid = true;
			for (char c : input) {
				if (!isdigit(c)) {
					cout << "Ошибка ввода числа..." << endl << endl;
					isValid = false;
					break;
				}
			}
			if (isValid) {
				try {
					if (input[0] == '0' && input.size() > 1) {
						cout << "Число не может начинаться с нуля..." << endl << endl;
						continue;
					}
					result = stoi(input);
					if (min <= result && result <= max) {
						return result;
					}
					else {
						cout << "Число не проходит по диапазону..." << endl << endl;
					}
				}
				catch (const invalid_argument& e) {
					cout << "Ошибка ввода числа..." << endl << endl;
				}
				catch (const out_of_range& e) {
					cout << "Число вне диапазона значений..." << endl << endl;
				}
			}
		}
	}
}
//int a = getInput<int>("str", 0, 100);