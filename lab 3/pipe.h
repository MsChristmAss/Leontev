#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <stdexcept>
using namespace std;
class Pipe {
public:
	int index;
	string name;                // имя трубы
	int length;                 // длина трубы
	int diameter;               // диаметр трубы
	bool repairStatus;          // характеристика в ремонте

	// Конструктор класса
	Pipe(int index, const string& name, int length, int diameter, bool repairStatus)
		: index(index), name(name), length(length), diameter(diameter), repairStatus(repairStatus) {}

	// Операторы для сравнения для использования в unordered_set
	bool operator==(const Pipe& other) const {
		return index == other.index && name == other.name && length == other.length && diameter == other.diameter && repairStatus == other.repairStatus;
	}

	// Описание хеш-функции для Pipe
	struct Hash {
		size_t operator()(const Pipe& p) const {
			return hash<int>()(p.index) ^ hash<string>()(p.name) ^ hash<int>()(p.length) ^ hash<int>()(p.diameter) ^ hash<bool>()(p.repairStatus);
		}
	};
};

void addPipe();
void Print();
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
			logInput(input);
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
	else if constexpr (is_same<T, float>::value || is_same<T, double>::value) {
		while (true) {
			cout << str;
			getline(cin, input);
			logInput(input);
			if (input.empty()) {
				cout << "Вы ничего не ввели..." << endl << endl;
				continue;
			}

			try {
				size_t pos;
				result = stof(input, &pos);  // Преобразование строки в float
				if (pos < input.size()) {
					cout << "Ошибка: некорректный ввод числа с плавающей точкой." << endl << endl;
				}
				else if (result < min || result > max) {
					cout << "Число вне допустимого диапазона (" << min << " - " << max << ")." << endl << endl;
				}
				else {
					return result;
				}
			}
			catch (const invalid_argument&) {
				cout << "Ошибка ввода числа с плавающей точкой." << endl << endl;
			}
			catch (const out_of_range&) {
				cout << "Число вне диапазона значений." << endl << endl;
			}
		}
	}
}

