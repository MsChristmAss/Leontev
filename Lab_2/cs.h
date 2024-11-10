#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
class CS {
public:
	string name;
	int quantity;
	int work_quantity;
	float effective_cs;

	// Конструктор класса
	CS(const string& name, int quantity, int work_quantity, float effective_cs)
		: name(name), quantity(quantity), work_quantity(work_quantity), effective_cs(effective_cs) {}

	// Операторы для сравнения для использования в unordered_set
	bool operator==(const CS& other) const {
		return name == other.name && quantity == other.quantity && work_quantity == other.work_quantity && effective_cs == other.effective_cs;
	}

	// Описание хеш-функции для CS
	struct Hash {
		size_t operator()(const CS& cs) const {
			return hash<string>()(cs.name) ^ hash<int>()(cs.quantity) ^ hash<int>()(cs.work_quantity) ^ hash<float>()(cs.effective_cs);
		}
	};
};

void addCS();
void editCS(int index);