#include "pipe.h"
#include "cs.h"

#include <iomanip> // Для форматирования вывода
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

// Объявление
int indexPipe = 0;
int indexCS = 0;
unordered_set<Pipe, Pipe::Hash> pipes;
unordered_set<CS, CS::Hash> css;


void logInput(const string& message) {
	static string filename;
	if (filename.empty()) {
		auto now = chrono::system_clock::now();
		auto time_t_now = chrono::system_clock::to_time_t(now);
		char timeBuffer[26];
		ctime_s(timeBuffer, sizeof(timeBuffer), &time_t_now);
		string Time = timeBuffer;
		Time.erase(remove(Time.begin(), Time.end(), '\n'), Time.end());
		replace(Time.begin(), Time.end(), ' ', '_');
		replace(Time.begin(), Time.end(), ':', '-');

		ostringstream filePath;
		filePath << "logs/" << Time << ".txt";
		filename = filePath.str();
	}
	ofstream logFile(filename, ios::app);
	logFile << message << endl;
	logFile.close();
}

void addPipe() {
	++indexPipe;
	bool repairStatus;
	string name = getInput<string>("Введите имя трубы: ", 1, 1);
	int length = getInput<int>("Введите длину трубы (в метрах): ", 1, INT_MAX);
	int diameter = getInput<int>("Введите диаметр трубы (в миллиметрах): ", 1, INT_MAX);
	int status = getInput<int>("Введите характеристику в ремонте (1 - 'Требует ремонта', 0 - 'Не требует ремонта'): ", 0, 1);
	repairStatus = (status == 1);

	Pipe newPipe(indexPipe, name, length, diameter, repairStatus);
	auto result = pipes.insert(newPipe);
	if (result.second) {
		cout << "Труба добавлена..." << endl;
	}
	else {
		cout << "Труба с таким именем и характеристиками уже существует!" << endl;
	}
}

void addCS() {
	++indexCS;
	string name = getInput<string>("Введите имя КС: ", 0, 0);
	int quantity = getInput<int>("Введите кол-во цехов: ", 1, INT_MAX);
	int work_quantity = getInput<int>("Введите кол-во работающих цехов: ", 0, quantity);
	float effective_cs = work_quantity * 100.0f / quantity;

	CS newCS(indexCS, name, quantity, work_quantity, effective_cs);
	auto result = css.insert(newCS);
	if (result.second) {
		cout << "КС добавлена..." << endl;
	}
	else {
		cout << "КС с таким именем и характеристиками уже существует!" << endl;
	}
}

//void Print() {
//	cout << "1 - вывести все трубы\n2 - вывести все КС\n3 - вывести всё\n\n";
//	int input = getInput<int>("Команда ", 1, 3);
//	if (input == 1) {
//		cout << "---------------- ТРУБЫ ----------------" << endl;
//		if (pipes.empty()) {
//			cout << "Нет доступных труб." << endl;
//		}
//		else {
//			for (const auto& pipe : pipes) {
//				cout << "Индекс " << pipe.index << endl;
//				cout << "Имя трубы: " << pipe.name << endl;
//				cout << "Длина: " << pipe.length << " м" << endl;
//				cout << "Диаметр: " << pipe.diameter << " мм" << endl;
//				cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
//				cout << "---------------------------------------" << endl;
//			}
//		}
//	}
//	else if (input == 2) {
//		cout << "----------------- КС -----------------" << endl;
//		if (css.empty()) {
//			cout << "Нет доступных КС." << endl;
//		}
//		else {
//			for (const auto& cs : css) {
//				cout << "Индекс " << cs.index << endl;
//				cout << "Имя КС: " << cs.name << endl;
//				cout << "Кол-во цехов: " << cs.quantity << endl;
//				cout << "Кол-во рабочих чехов: " << cs.work_quantity << endl;
//				cout << "% рабочих цехов: " << cs.effective_cs << endl;
//				cout << "--------------------------------------" << endl;
//			}
//		}
//	}
//	else if (input == 3) {
//		cout << "---------------- ТРУБЫ ----------------" << endl;
//		if (pipes.empty()) {
//			cout << "Нет доступных труб." << endl;
//		}
//		else {
//			for (const auto& pipe : pipes) {
//				cout << "Индекс " << pipe.index << endl;
//				cout << "Имя трубы: " << pipe.name << endl;
//				cout << "Длина: " << pipe.length << " м" << endl;
//				cout << "Диаметр: " << pipe.diameter << " мм" << endl;
//				cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
//				cout << "---------------------------------------" << endl;
//			}
//		}
//		cout << "----------------- КС -----------------" << endl;
//		if (css.empty()) {
//			cout << "Нет доступных КС." << endl;
//		}
//		else {
//			for (const auto& cs : css) {
//				cout << "Индекс " << cs.index << endl;
//				cout << "Имя КС: " << cs.name << endl;
//				cout << "Кол-во цехов: " << cs.quantity << endl;
//				cout << "Кол-во рабочих чехов: " << cs.work_quantity << endl;
//				cout << "% рабочих цехов: " << cs.effective_cs << endl;
//				cout << "--------------------------------------" << endl;
//			}
//		}
//	}
//	cout << endl;
//
//}


void Print() {
	const int fieldWidth = 35; // Фиксированная ширина для каждого поля
	cout << string(fieldWidth * 2, '=') << endl;
	cout << setw(fieldWidth) << left << (string(15, ' ') + "Трубы");
	cout << setw(fieldWidth - 2) << left << ("|" + string(16, ' ') + "КС" + string(15, ' ') + "|") << endl;
	cout << string(fieldWidth * 2, '=') << endl;

	auto pipeIt = pipes.begin();
	auto csIt = css.begin();

	while (pipeIt != pipes.end() || csIt != css.end()) {
		// Индексы труб и КС
		if (pipeIt != pipes.end()) {
			cout << setw(fieldWidth) << left << ("Индекс: " + to_string(pipeIt->index));
		}
		else {
			cout << setw(fieldWidth) << " ";
		}

		if (csIt != css.end()) {
			cout << setw(fieldWidth) << left << ("Индекс: " + to_string(csIt->index));
		}
		else {
			cout << setw(fieldWidth) << " ";
		}
		cout << endl;

		// Имена труб и КС
		if (pipeIt != pipes.end()) {
			cout << setw(fieldWidth) << left << ("Имя: " + pipeIt->name);
		}
		else {
			cout << setw(fieldWidth) << " ";
		}

		if (csIt != css.end()) {
			cout << setw(fieldWidth) << left << ("Имя: " + csIt->name);
		}
		else {
			cout << setw(fieldWidth) << " ";
		}
		cout << endl;

		// Длина и количество цехов
		if (pipeIt != pipes.end()) {
			cout << setw(fieldWidth) << left << ("Длина: " + to_string(pipeIt->length) + " м");
		}
		else {
			cout << setw(fieldWidth) << " ";
		}

		if (csIt != css.end()) {
			cout << setw(fieldWidth) << left << ("Цехов: " + to_string(csIt->quantity));
		}
		else {
			cout << setw(fieldWidth) << " ";
		}
		cout << endl;

		// Диаметр и рабочие цехи
		if (pipeIt != pipes.end()) {
			cout << setw(fieldWidth) << left << ("Диаметр: " + to_string(pipeIt->diameter) + " мм");
		}
		else {
			cout << setw(fieldWidth) << " ";
		}

		if (csIt != css.end()) {
			cout << setw(fieldWidth) << left << ("Рабочих: " + to_string(csIt->work_quantity));
		}
		else {
			cout << setw(fieldWidth) << " ";
		}
		cout << endl;

		// Ремонт и эффективность
		if (pipeIt != pipes.end()) {
			cout << setw(fieldWidth) << left << ("Ремонт: " + string(pipeIt->repairStatus ? "Да" : "Нет"));
		}
		else {
			cout << setw(fieldWidth) << " ";
		}

		if (csIt != css.end()) {
			cout << setw(fieldWidth) << left << ("Эффект.: " + to_string(csIt->effective_cs) + "%");
		}
		else {
			cout << setw(fieldWidth) << " ";
		}
		cout << endl;

		cout << string(fieldWidth * 2, '-') << endl;

		// Переход к следующему объекту
		if (pipeIt != pipes.end()) ++pipeIt;
		if (csIt != css.end()) ++csIt;
	}
}


void remove() {
	cout << "Удалить:\n1 - по индексу\n2 - по имени\n3 - по статусу\n4 - всё\n0 - выйти" << endl << endl;
	int choice = getInput<int>("\nКоманда ", 1, 4);
	switch (choice)
	{
	case 0:
		return;
	case 1:
		removeByIndex(getInput<int>("Индекс ", 1, INT_MAX));
		break;
	case 2:
		removeByName(getInput<string>("Имя ", 0, 1));
		break;
	case 3:
		bool status;
		if (getInput<int>("1 - 'Требует ремонта', 0 - 'Не требует ремонта': ", 0, 1) == 1) {
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
	cout << "1 - трубы\n2 - кс" << endl;
	if (getInput<int>("Команда удаления всех ", 1, 2) == 1)
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

void removeByIndex(int ind) {
	int choice;
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == ind; });
	auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == ind; });
	if (pipeIt != pipes.end()) {
		cout << "Труба с индексом " << ind << " найдена." << endl;
		choice = getInput<int>("\nУдалить?\nДА - 1\nНЕТ - 0\n", 0, 1);
		if (choice == 1) {
			pipes.erase(pipeIt);
			cout << "Труба с индексом " << ind << " удалена." << endl;
		}
	}
	else {
		cout << "Труба с индексом " << ind << " не найдена." << endl;
	}
	if (csIt != css.end()) {
		cout << "КС с индексом " << ind << " найдена." << endl;
		choice = getInput<int>("\nУдалить?\nДА - 1\nНЕТ - 0\n", 0, 1);
		if (choice == 1) {
			css.erase(csIt);
			cout << "КС с индексом " << ind << " удалена." << endl;
		}
	}
	else {
		cout << "КС с индексом " << ind << " не найдена." << endl;
	}

}



void removeByName(const string& name) {
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.name == name; });
	auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.name == name; });
	if (pipeIt != pipes.end()) {
		pipes.erase(pipeIt);
		cout << "Труба с именем \"" << name << "\" удалена." << endl;
	}
	else {
		cout << "Труба с таким именем не найдена." << endl;
	}

	if (csIt != css.end()) {
		css.erase(csIt);
		cout << "КС с именем \"" << name << "\" удалена." << endl;
	}
	else {
		cout << "КС с таким именем не найдена." << endl;
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



void edit() {
	int index = getInput<int>("Индекс ", 1, INT_MAX);
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == index; });
	auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == index; });

	if (pipeIt == pipes.end()) {
		cout << "Труба с указанным индексом не найдена." << endl;
		return;
	}
	Pipe updatedPipe = *pipeIt;
	updatedPipe.repairStatus = !updatedPipe.repairStatus;
	pipes.erase(pipeIt);
	pipes.insert(updatedPipe);
	cout << "Статус трубы с индексом " << index << " изменен на: " << (updatedPipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl << endl;

	if (csIt == css.end()) {
		cout << "КС с указанным индексом не найдена." << endl;
		return;
	}
	CS updatedCS = *csIt;
	updatedCS.work_quantity = getInput<int>("Введите новое количество работающих цехов: ", 0, updatedCS.quantity);
	updatedCS.effective_cs = updatedCS.work_quantity * 100.0f / updatedCS.quantity;
	css.erase(csIt);
	css.insert(updatedCS);
	cout << "КС с индексом " << index << " обновлена. Количество рабочих цехов: " << updatedCS.work_quantity << ", эффективность: " << updatedCS.effective_cs << "%" << endl;
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
	string fileName = getInput<string>("Имя файла ", 1, 1);
	ofstream outFile(fileName);
	if (outFile.is_open()) {
		if (pipes.size() == 0) {
			outFile << "Нет труб";
			return;
		}
		for (const auto& pipe : pipes) {
			outFile << "Pipe\n";
			outFile << pipe.index << "\n";
			outFile << pipe.name << "\n";
			outFile << pipe.length << "\n";
			outFile << pipe.diameter << "\n";
			outFile << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << "\n";
			outFile << "---------------------------------------\n";
		}
		outFile.close();
		cout << "Трубы успешно сохранены в файл" << endl;
	}
	else {
		cout << "Ошибка открытия файла для труб" << endl;
	}
}

void saveCSsToFile(const unordered_set<CS, CS::Hash>& css) {
	string fileName = getInput<string>("Имя файла ", 1, 1);
	ofstream outFile(fileName);
	if (outFile.is_open()) {
		if (css.size() == 0) {
			outFile << "Нет кс";
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
		cout << "КС успешно сохранены в файл" << endl;
	}
	else {
		cout << "Ошибка открытия файла для КС" << endl;
	}
}

void load() {
	string fileName = getInput<string>("Имя файла, из которого\nбудем выгружать данные: ", 1, 1);
	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		cout << "Файл не найден." << endl;
		return;
	}
	string input;
	getline(inFile, input);
	if (input == "Нет кс" || input == "Нет труб") {
		cout << "В файле ничего нет..." << endl << endl;
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
				if (validateInput(str, str, 1, 1) && str == "Требует ремонта") {
					repairStatus = true;
				}
				else if (validateInput(str, str, 1, 1) && str == "Не требует ремонта") {
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
		cout << "Успешно загружены" << endl;
	}
}

void filterPipeByName(const string& name) {
	cout << "Результаты поиска труб по имени: \"" << name << "\":" << endl;
	bool found = false;
	for (const auto& pipe : pipes) {
		if (pipe.name.find(name) != string::npos) {  // Ищем вхождение подстроки
			found = true;
			cout << "Индекс: " << pipe.index << endl;
			cout << "Имя трубы: " << pipe.name << endl;
			cout << "Длина: " << pipe.length << " м" << endl;
			cout << "Диаметр: " << pipe.diameter << " мм" << endl;
			cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
			cout << "---------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "Трубы с таким именем не найдены." << endl;
	}
}

void filterCSByName(const string& name) {
	cout << "Результаты поиска КС по имени: \"" << name << "\":" << endl;
	bool found = false;
	for (const auto& cs : css) {
		if (cs.name.find(name) != string::npos) {  // Ищем вхождение подстроки
			found = true;
			cout << "Индекс: " << cs.index << endl;
			cout << "Имя КС: " << cs.name << endl;
			cout << "Количество цехов: " << cs.quantity << endl;
			cout << "Рабочие цехи: " << cs.work_quantity << endl;
			cout << "Эффективность: " << cs.effective_cs << "%" << endl;
			cout << "--------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "КС с таким именем не найдены." << endl;
	}
}

void filterPipeByRepairStatus(bool repairStatus) {
	cout << "Результаты поиска труб по статусу \"" << (repairStatus ? "Требует ремонта" : "Не требует ремонта") << "\":" << endl;
	bool found = false;
	for (const auto& pipe : pipes) {
		if (pipe.repairStatus == repairStatus) {
			found = true;
			cout << "Индекс: " << pipe.index << endl;
			cout << "Имя трубы: " << pipe.name << endl;
			cout << "Длина: " << pipe.length << " м" << endl;
			cout << "Диаметр: " << pipe.diameter << " мм" << endl;
			cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
			cout << "---------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "Трубы с указанным статусом не найдены." << endl;
	}
}

void filterCSByUnusedPercentage(float percentage) {
	cout << "Результаты поиска КС с процентом незадействованных цехов >= " << percentage << "%:" << endl;
	bool found = false;
	for (const auto& cs : css) {
		float unusedPercentage = 100.0f - cs.effective_cs;
		if (unusedPercentage >= percentage) {
			found = true;
			cout << "Индекс: " << cs.index << endl;
			cout << "Имя КС: " << cs.name << endl;
			cout << "Количество цехов: " << cs.quantity << endl;
			cout << "Рабочие цехи: " << cs.work_quantity << endl;
			cout << "Эффективность: " << cs.effective_cs << "%" << endl;
			cout << "Незадействованные цехи: " << unusedPercentage << "%" << endl;
			cout << "--------------------------------------" << endl;
		}
	}
	if (!found) {
		cout << "КС с указанным процентом незадействованных цехов не найдены." << endl;
	}
}

void filterSearch() {
	cout << "Поиск:\n"
		<< "1 - трубы по имени\n"
		<< "2 - трубы по статусу ремонта\n"
		<< "3 - КС по имени\n"
		<< "4 - КС по проценту незадействованных цехов\n"
		<< "0 - выйти" << endl;

	int choice = getInput<int>("Выберите команду: ", 0, 4);

	switch (choice) {
	case 1: {
		string name = getInput<string>("Введите имя трубы: ", 1, 1);
		filterPipeByName(name);
		break;
	}
	case 2: {
		int status = getInput<int>("Введите статус ремонта (1 - требует ремонта, 0 - не требует ремонта): ", 0, 1);
		filterPipeByRepairStatus(status == 1);
		break;
	}
	case 3: {
		string name = getInput<string>("Введите имя КС: ", 1, 1);
		filterCSByName(name);
		break;
	}
	case 4: {
		float percentage = getInput<float>("Введите минимальный процент незадействованных цехов: ", 0, 100);
		filterCSByUnusedPercentage(percentage);
		break;
	}
	case 0:
		return;
	default:
		cout << "Неверный выбор. Повторите попытку." << endl;
	}
}

void batchEditOrRemove() {
	Print();
	cout << "\nПакетное редактирование:\n"
		<< "1 - Редактировать трубы\n"
		<< "2 - Удалить трубы\n"
		<< "3 - Редактировать КС\n"
		<< "4 - Удалить КС\n"
		<< "0 - Выход\n";
	int choice = getInput<int>("Выберите команду: ", 0, 4);

	if (choice == 0) return;

	unordered_set<int> selectedIndices;

	cout << "Введите индексы для обработки (разделите пробелами, например: 1 2 3): ";
	string input;
	getline(cin, input);
	stringstream ss(input);
	int index;
	while (ss >> index) {
		selectedIndices.insert(index);
	}

	if (selectedIndices.empty()) {
		cout << "Не выбрано ни одного индекса." << endl;
		return;
	}

	if (choice == 1 || choice == 3) { // Редактирование
		for (int idx : selectedIndices) {
			if (choice == 1) { // Редактирование труб
				auto it = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == idx; });
				if (it != pipes.end()) {
					Pipe updatedPipe = *it;
					updatedPipe.repairStatus = !updatedPipe.repairStatus; // Пример изменения статуса
					pipes.erase(it);
					pipes.insert(updatedPipe);
					cout << "Труба с индексом " << idx << " обновлена." << endl;
				}
				else {
					cout << "Труба с индексом " << idx << " не найдена." << endl;
				}
			}
			else { // Редактирование КС
				auto it = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == idx; });
				if (it != css.end()) {
					CS updatedCS = *it;
					updatedCS.work_quantity = getInput<int>(
						"Введите новое количество работающих цехов для КС с индексом " + to_string(idx) + ": ",
						0, updatedCS.quantity
					);
					updatedCS.effective_cs = updatedCS.work_quantity * 100.0f / updatedCS.quantity;
					css.erase(it);
					css.insert(updatedCS);
					cout << "КС с индексом " << idx << " обновлена." << endl;
				}
				else {
					cout << "КС с индексом " << idx << " не найдена." << endl;
				}
			}
		}
	}
	else { // Удаление
		for (int idx : selectedIndices) {
			if (choice == 2) { // Удаление труб
				auto it = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == idx; });
				if (it != pipes.end()) {
					pipes.erase(it);
					cout << "Труба с индексом " << idx << " удалена." << endl;
				}
				else {
					cout << "Труба с индексом " << idx << " не найдена." << endl;
				}
			}
			else { // Удаление КС
				auto it = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == idx; });
				if (it != css.end()) {
					css.erase(it);
					cout << "КС с индексом " << idx << " удалена." << endl;
				}
				else {
					cout << "КС с индексом " << idx << " не найдена." << endl;
				}
			}
		}
	}
}
