#include "pipe.h"
#include "cs.h"

#include <unordered_set>
#include <iostream>
#include <algorithm> // для distance
using namespace std;

// Объявление unordered_set для хранения труб
unordered_set<Pipe, Pipe::Hash> pipes;
unordered_set<CS, CS::Hash> css;

// Функция добавления трубы в unordered_set
void addPipe() {
	bool repairStatus;
	string name = getInput<string>("Введите имя трубы: ", 1, 1);
	int length = getInput<int>("Введите длину трубы (в метрах): ", 1, 2147483647);
	int diameter = getInput<int>("Введите диаметр трубы (в милиметрах): ", 1, 2147483647);
	int status = getInput<int>("Введите характеристику в ремонте (1 - 'Требует ремонта', 0 - 'Не требует ремонта'): ", 0, 1);
	if (status == 1) {
		repairStatus = true;
	}
	else {
		repairStatus = false;
	}
	Pipe newPipe(name, length, diameter, repairStatus);
	auto result = pipes.insert(newPipe);
	if (result.second) {
		cout << "Труба добавлена... " << endl;
	}
	else {
		cout << "Труба с таким именем и характеристиками уже существует!" << endl;
	}
}

void addCS() {
	string name = getInput<string>("Введите имя КС: ", 0, 0);
	int quantity = getInput<int>("Введите кол-во цехов: ", 1, 2147483647);;
	int work_quantity = getInput<int>("Введите кол-во работающих цехов: ", 0, quantity);
	float effective_cs = work_quantity * 100.0 / quantity;
	CS newCS(name, quantity, work_quantity, effective_cs);
	auto result = css.insert(newCS);
	if (result.second) {
		cout << "КС добавлена... " << endl;
	}
	else {
		cout << "КС с таким именем и характеристиками уже существует!" << endl;
	}
}

void Print() {
	cout << "1 - вывести все трубы\n2 - вывести все КС\n3 - вывести всё\n\n";
	int input = getInput<int>("Команда ", 1, 3);
	if (input == 1) {
		cout << "---------------- ТРУБЫ ----------------" << endl;
		if (pipes.empty()) {
			cout << "Нет доступных труб." << endl;
		}
		else {
			for (const auto& pipe : pipes) {
				cout << "Имя трубы: " << pipe.name << endl;
				cout << "Длина: " << pipe.length << " м" << endl;
				cout << "Диаметр: " << pipe.diameter << " мм" << endl;
				cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
				cout << "---------------------------------------" << endl;
			}
		}
	}
	else if (input == 2) {
		cout << "----------------- КС -----------------" << endl;
		if (css.empty()) {
			cout << "Нет доступных КС." << endl;
		}
		else {
			for (const auto& cs : css) {
				cout << "Имя КС: " << cs.name << endl;
				cout << "Кол-во цехов: " << cs.quantity << endl;
				cout << "Кол-во рабочих чехов: " << cs.work_quantity << endl;
				cout << "% рабочих цехов: " << cs.effective_cs << endl;
				cout << "--------------------------------------" << endl;
			}
		}
	}
	else if (input == 3) {
		cout << "---------------- ТРУБЫ ----------------" << endl;
		if (pipes.empty()) {
			cout << "Нет доступных труб." << endl;
		}
		else {
			for (const auto& pipe : pipes) {
				cout << "Имя трубы: " << pipe.name << endl;
				cout << "Длина: " << pipe.length << " м" << endl;
				cout << "Диаметр: " << pipe.diameter << " мм" << endl;
				cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
				cout << "---------------------------------------" << endl;
			}
		}
		cout << "----------------- КС -----------------" << endl;
		if (css.empty()) {
			cout << "Нет доступных КС." << endl;
		}
		else {
			for (const auto& cs : css) {
				cout << "Имя КС: " << cs.name << endl;
				cout << "Кол-во цехов: " << cs.quantity << endl;
				cout << "Кол-во рабочих чехов: " << cs.work_quantity << endl;
				cout << "% рабочих цехов: " << cs.effective_cs << endl;
				cout << "--------------------------------------" << endl;
			}
		}
	}
	cout << endl;

}

void remove() {
	cout << "Удалить:\n1 - по индексу\n2 - по имени\n3 - по статусу\n4 - всё" << endl << endl;
	int input = getInput<int>("Выбор:\n1 - труба\n2 - кс\n\nКоманда ", 1, 2);
	int choice = getInput<int>("\nКоманда ", 1, 4);
	switch (choice)
	{
	case 1:
		removeByIndex(getInput<int>("Индекс ", 0, pipes.size()), input);
		break;
	case 2:
		removeByName(getInput<string>("Имя ", 0, 1), input);
		break;
	case 3:

	{
		bool status;
		if (getInput<int>("1 - 'Требует ремонта', 0 - 'Не требует ремонта': ", 0, 1) == 1) {
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
	cout << "1 - трубы\n2 - кс" << endl;
	if (getInput<int>("Команда ", 1, 2) == 1)
	{
		auto it = pipes.begin();
		while (it != pipes.end()) {
			it = pipes.erase(it);
		}
		cout << "Все трубы удалены..." << endl;
	}
	else
	{
		auto it = css.begin();
		while (it != css.end()) {
			it = css.erase(it);
		}
		cout << "Все КС удалены..." << endl;
	}

}

void removeByIndex(int index, int choice) {
	if (choice == 1)
	{
		if (index < 0 || index >= static_cast<int>(pipes.size())) {
			cout << "Неверный индекс." << endl;
			return;
		}
		auto it = pipes.begin();
		advance(it, index);
		pipes.erase(it);
		cout << "Труба удалена по индексу " << index << endl;
	}
	else
	{
		if (index < 0 || index >= static_cast<int>(css.size())) {
			cout << "Неверный индекс." << endl;
			return;
		}
		auto it = css.begin();
		advance(it, index);
		css.erase(it);
		cout << "КС удалена по индексу " << index << endl;
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
			cout << "Труба с именем \"" << name << "\" удалена." << endl;
		}
		else {
			cout << "Труба с таким именем не найдена." << endl;
		}
	}
	else{
		auto it = find_if(css.begin(), css.end(), [&](const CS& cs) {
			return cs.name == name;
			});
		if (it != css.end()) {
			css.erase(it);
			cout << "КС с именем \"" << name << "\" удалена." << endl;
		}
		else {
			cout << "КС с таким именем не найдена." << endl;
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
		cout << "Трубы со статусом \"" << (status ? "Требует ремонта" : "Не требует ремонта") << "\" удалены." << endl;
	}
	else {
		cout << "Трубы с таким статусом не найдены." << endl;
	}
}

void editPipe(int index) {	
	if (index < 0 || index >= static_cast<int>(pipes.size())) {
		cout << "Неверный индекс." << endl;
		return;
	}
	auto it = pipes.begin();
	advance(it, index);
	Pipe updatedPipe = *it;
	updatedPipe.repairStatus = !updatedPipe.repairStatus;

	// Удаляем оригинал и добавляем обновленную трубу
	pipes.erase(it);
	pipes.insert(updatedPipe);

	cout << "Статус трубы изменен на: "
		<< (updatedPipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
}

void editCS(int index) {	
	if (index < 0 || index >= static_cast<int>(css.size())) {
		cout << "Неверный индекс." << endl;
		return;
	}
	auto it = css.begin();
	advance(it, index);
	CS updatedCS = *it;
	updatedCS.work_quantity = getInput<int>("Введите кол-во рабочих цехов: ",1, updatedCS.quantity);
	css.erase(it);
	css.insert(updatedCS);
	cout << "Кол-во рабочих цехов изменено на " << updatedCS.work_quantity << endl;
}

void edit() {
	cout << "Реактирование:\n1 - трубы\n2 - кс\n\n";
	if (getInput<int>("Команда ", 1, 2) == 1) {
		if (pipes.size() == 0) {
			cout << "Нет труб для редактирования..." << endl;
			return;
		}
		editPipe(getInput<int>("Индекс ", 0, pipes.size()));
	}
	else {
		if (css.size() == 0) {
			cout << "Нет кс для редактирования..." << endl;
			return;
		}
		editCS(getInput<int>("Индекс ", 0, css.size()));
	}
}
