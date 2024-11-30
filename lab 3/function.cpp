#include "pipe.h"
#include "cs.h"

#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <unordered_map>

using namespace std;

int indexPipe = 0;
int indexCS = 0;
unordered_set<Pipe, Pipe::Hash> pipes;
unordered_set<CS, CS::Hash> css;
unordered_map<int, unordered_set<int>> connections;


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
	if (name == "0") return;
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
	if (name == "0") return;
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

void Print() {
	const int fieldWidth = 35;
	cout << string(fieldWidth * 2, '=') << endl;
	cout << setw(fieldWidth) << left << (string(15, ' ') + "Трубы");
	cout << setw(fieldWidth - 2) << left << ("|" + string(16, ' ') + "КС" + string(15, ' ') + "|") << endl;
	cout << string(fieldWidth * 2, '=') << endl;

	auto pipeIt = pipes.begin();
	auto csIt = css.begin();

	while (pipeIt != pipes.end() || csIt != css.end()) {
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

		if (pipeIt != pipes.end()) ++pipeIt;
		if (csIt != css.end()) ++csIt;
	}
}

//void save() {
//	string fileName = getInput<string>("Имя файла ", 1, 1);
//	ofstream outFile(fileName);
//	if (outFile.is_open()) {
//		if (pipes.size() == 0) {
//			outFile << "Нет труб";
//		}
//		else {
//			for (const auto& pipe : pipes) {
//				outFile << "Pipe\n";
//				outFile << pipe.index << "\n";
//				outFile << pipe.name << "\n";
//				outFile << pipe.length << "\n";
//				outFile << pipe.diameter << "\n";
//				outFile << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << "\n";
//				outFile << "---------------------------------------\n";
//			}
//		}
//
//		if (css.size() == 0) {
//			outFile << "Нет кс";
//		}
//		else {
//			for (const auto& cs : css) {
//				outFile << "CS\n";
//				outFile << cs.index << "\n";
//				outFile << cs.name << "\n";
//				outFile << cs.quantity << "\n";
//				outFile << cs.work_quantity << "\n";
//				outFile << cs.effective_cs << "\n";
//				outFile << "--------------------------------------\n";
//			}
//			outFile.close();
//			cout << "Трубы и КС успешно сохранены в файл" << endl;
//		} {
//			for (const auto& connection : connections) {
//				int pipeID = connection.first;
//				const unordered_set<int>& csSet = connection.second;
//
//				// Сохраняем ID трубы и связанных КС
//				outFile << "Connection" << endl;
//				outFile << pipeID;
//				for (int csID : csSet) {
//					outFile << " " << csID;
//				}
//				outFile << "\n";
//			}
//		}
//	}
//	else {
//		cout << "Ошбка открытия файла" << endl;
//	}
//}
void save() {
	string fileName = getInput<string>("Имя файла ", 1, 1);
	ofstream outFile(fileName);
	if (!outFile.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return;
	}

	// Сохранение труб
	if (pipes.empty()) {
		outFile << "Нет труб\n";
	}
	else {
		for (const auto& pipe : pipes) {
			outFile << "Pipe\n";
			outFile << pipe.index << "\n";
			outFile << pipe.name << "\n";
			outFile << pipe.length << "\n";
			outFile << pipe.diameter << "\n";
			outFile << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << "\n";
			outFile << "---------------------------------------\n";
		}
	}

	// Сохранение КС
	if (css.empty()) {
		outFile << "Нет кс\n";
	}
	else {
		for (const auto& cs : css) {
			outFile << "CS\n";
			outFile << cs.index << "\n";
			outFile << cs.name << "\n";
			outFile << cs.quantity << "\n";
			outFile << cs.work_quantity << "\n";
			outFile << cs.effective_cs << "\n";
			outFile << "--------------------------------------\n";
		}
	}

	// Сохранение соединений
	if (connections.empty()) {
		outFile << "Нет соединений\n";
	}
	else {
		for (const auto& connection : connections) {
			int pipeID = connection.first;
			const unordered_set<int>& csSet = connection.second;

			outFile << "Connection\n";
			outFile << pipeID;
			for (int csID : csSet) {
				outFile << " " << csID;
			}
			outFile << "--------------------------------------\n";
			outFile << "\n";
		}
	}

	outFile.close();
	cout << "Данные успешно сохранены в файл" << endl;
}


void load() {
	string fileName = getInput<string>("Имя файла, из которого будем выгружать данные:\n", 1, 1);
	if (fileName == "" || fileName == "0") return;
	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		cout << "Файл не найден." << endl;
		return;
	}
	string str;

	int ind;
	int quantity;
	int work_quantity;
	bool repairStatus;
	string name;
	int length;
	int diameter;
	{
		while (!inFile.eof()) {
			getline(inFile, str);
			if (str == "Нет кс") {
				cout << "В файле нет кс..." << endl;
				continue;
			}
			if (str == "Нет труб") {
				cout << "В файле нет..." << endl;
				continue;
			}
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
			else if (str == "Connection") {
				stringstream ss(str);
				int pipeID;
				ss >> pipeID;
				unordered_set<int> csSet;
				int csID;
				while (ss >> csID) {
					csSet.insert(csID);
				}
				connections[pipeID] = csSet;
			}
		}
		inFile.close();
		cout << "Данные успешно загружены" << endl;
	}
}

void CoolFilters() {
	Print();
	cout << "Поиск:\n"
		<< "1 - трубы по имени\n"
		<< "2 - трубы по статусу ремонта\n"
		<< "3 - КС по имени\n"
		<< "4 - КС по проценту незадействованных цехов\n"
		<< "0 - выйти" << endl;
	int choice = getInput<int>("Выберите команду: ", 0, 4);
	unordered_set<int> selectedIndices;
	switch (choice) {
	case 1: {
		string name = getInput<string>("Введите имя трубы: ", 1, 1);
		cout << endl << "Результаты поиска труб по имени: \"" << name << "\":" << endl << endl;
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
				selectedIndices.insert(pipe.index);
			}
		}
		if (!found) {
			cout << "Трубы с таким именем не найдены." << endl;
		}
		break;
	}
	case 2: {
		int status = getInput<int>("Введите статус ремонта (1 - требует ремонта, 0 - не требует ремонта): ", 0, 1);
		bool repairStatus = (status == 1 ? true : false);
		cout << endl << "Результаты поиска труб по статусу \"" << (repairStatus ? "Требует ремонта" : "Не требует ремонта") << "\":" << endl << endl;
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
				selectedIndices.insert(pipe.index);
			}
		}
		if (!found) {
			cout << "Трубы с указанным статусом не найдены." << endl;
		}
		break;
	}
	case 3: {
		string name = getInput<string>("Введите имя КС: ", 1, 1);
		cout << endl << "Результаты поиска КС по имени: \"" << name << "\":" << endl << endl;
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
				selectedIndices.insert(cs.index);
			}
		}
		if (!found) {
			cout << "КС с таким именем не найдены." << endl;
		}
		break;
	}
	case 4: {
		float percentage = getInput<float>("Введите минимальный процент незадействованных цехов: ", 0, 100);
		cout << endl << "Результаты поиска КС с процентом незадействованных цехов >= " << percentage << "%:" << endl << endl;
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
				selectedIndices.insert(cs.index);
			}
		}
		if (!found) {
			cout << "КС с указанным процентом незадействованных цехов не найдены." << endl;
		}
		break;
	}
	case 0:
		return;
	}

	cout << "\nВыберите действие для найденных объектов:\n"
		<< "1 - Редактировать все\n"
		<< "2 - Удалить все\n"
		<< "3 - Редактировать по индексам\n"
		<< "4 - Удалить по индексам\n"
		<< "0 - Выйти\n";
	int action = getInput<int>("Ваш выбор: ", 0, 4);
	cout << endl;
	if (action == 0) return;

	if (action == 3 || action == 4) {
		cout << "Введите индексы для обработки (разделите пробелами, например: 1 2 3): ";
		string input;
		selectedIndices.clear();
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
	}

	if (action == 1 || action == 3) { // Редактирование
		for (const auto& idx : selectedIndices) {
			auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == idx; });
			auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == idx; });

			if (pipeIt != pipes.end() && (choice == 1 || choice == 2)) {
				Pipe updatedPipe = *pipeIt;
				updatedPipe.repairStatus = !updatedPipe.repairStatus; // Пример изменения статуса
				pipes.erase(pipeIt);
				pipes.insert(updatedPipe);
				cout << "Труба с индексом " << idx << " обновлена." << endl;
			}

			if (csIt != css.end() && (choice == 3 || choice == 4)) {
				CS updatedCS = *csIt;
				updatedCS.work_quantity = getInput<int>("Новое количество работающих цехов для КС с индексом " + to_string(idx) + ": ", 0, updatedCS.quantity);
				updatedCS.effective_cs = updatedCS.work_quantity * 100.0f / updatedCS.quantity;
				css.erase(csIt);
				css.insert(updatedCS);
				cout << "КС с индексом " << idx << " обновлена." << endl;
			}
		}
	}
	else if (action == 2 || action == 4) { // Удаление
		for (const auto& idx : selectedIndices) {
			auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == idx; });
			auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == idx; });

			if (pipeIt != pipes.end() && (choice == 1 || choice == 2)) {
				pipes.erase(pipeIt);
				cout << "Труба с индексом " << idx << " удалена." << endl;
			}

			if (csIt != css.end() && (choice == 3 || choice == 4)) {
				css.erase(csIt);
				cout << "КС с индексом " << idx << " удалена." << endl;
			}
		}
	}
}

void addConnection() {
	int csID1 = getInput<int>("Введите ID входного КС 1: ", 1, INT_MAX);
	int pipeID = getInput<int>("Введите ID трубы: ", 1, INT_MAX);
	int csID2 = getInput<int>("Введите ID выходного КС 2: ", 1, INT_MAX);

	// Проверка существования трубы
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& p) { return p.index == pipeID; });
	if (pipeIt == pipes.end()) {
		cout << "Ошибка: Труба с ID " << pipeID << " не найдена." << endl;
		return;
	}

	// Проверка существования первой КС
	auto csIt1 = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == csID1; });
	if (csIt1 == css.end()) {
		cout << "Ошибка: КС с ID " << csID1 << " не найдена." << endl;
		return;
	}

	// Проверка существования второй КС
	auto csIt2 = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == csID2; });
	if (csIt2 == css.end()) {
		cout << "Ошибка: КС с ID " << csID2 << " не найдена." << endl;
		return;
	}

	// Проверка на существование соединений
	if (connections[pipeID].count(csID1) || connections[pipeID].count(csID2)) {
		cout << "Соединение между трубой " << pipeID << " и одной из КС уже существует." << endl;
		return;
	}

	// Добавление соединений
	connections[pipeID].insert(csID1);
	connections[pipeID].insert(csID2);

	cout << "Соединение: КС " << csID1 << " -> труба " << pipeID << " -> КС " << csID2 << " успешно создано." << endl;
}


void printGraph() {
	if (system("dot -Tpng graph.dot -o graph.png") != 0) {
		cout << "Ошибка: Убедитесь, что утилита Graphviz установлена и доступна.\n";
		return;
	}

	if (system("graph.png") != 0) {
		cout << "Ошибка: Не удалось открыть файл graph.png\n";
	}
}


void saveConnections() {
	ofstream outFile("graph.dot");
	if (!outFile.is_open()) {
		cout << "Ошибка: Не удалось открыть файл для записи.\n";
		return;
	}

	outFile << "digraph G {\n";
	outFile << "    node[shape=box, color=blue, penwidth=3];\n";
	outFile << "    edge[color=blue, penwidth=3];\n";

	if (connections.empty()) {
		cout << "Соединений для сохранения нет.\n";
		outFile << "}\n";
		return;
	}

	for (const auto& connection : connections) {
		int pipeID = connection.first;
		const unordered_set<int>& csSet = connection.second;

		// Сохраняем соединения между всеми КС, связанными этой трубой
		vector<int> csList(csSet.begin(), csSet.end());
		for (size_t i = 0; i + 1 < csList.size(); i += 2) {
			int csID1 = csList[i];
			int csID2 = csList[i + 1];
			outFile << "    cs" << csID1 << " -> cs" << csID2
				<< " [label=\"truba" << pipeID << "\"];\n";
		}
	}

	outFile << "}\n";
	outFile.close();
	cout << "Соединения успешно сохранены в файл: graph.dot\n";
}

void saveConnectionsToFile() {
	//	string fileName = getInput<string>("Введите имя файла для сохранения соединений: ", 1, 1);
	//	ofstream outFile(fileName);
	//	if (!outFile.is_open()) {
	//		cout << "Ошибка: Не удалось открыть файл для записи.\n";
	//		return;
	//	}
	//
	//	for (const auto& connection : connections) {
	//		int pipeID = connection.first;
	//		const unordered_set<int>& csSet = connection.second;
	//
	//		// Сохраняем ID трубы и связанных КС
	//		outFile << "Connection" << endl;
	//		outFile << pipeID;
	//		for (int csID : csSet) {
	//			outFile << " " << csID;
	//		}
	//		outFile << "\n";
	//	}
	//	outFile.close();
	//	cout << "Соединения успешно сохранены в файл: " << fileName << "\n";
}

void loadConnectionsFromFile() {
	//	string fileName = getInput<string>("Введите имя файла для загрузки соединений: ", 1, 1);
	//	ifstream inFile(fileName);
	//	if (!inFile.is_open()) {
	//		cout << "Ошибка: Не удалось открыть файл.\n";
	//		return;
	//	}
	//	string line;
	//	while (getline(inFile, line)) {
	//		stringstream ss(line);
	//		int pipeID;
	//		ss >> pipeID;
	//		unordered_set<int> csSet;
	//		int csID;
	//		while (ss >> csID) {
	//			csSet.insert(csID);
	//		}
	//		connections[pipeID] = csSet;
	//	}
	//	inFile.close();
	//	cout << "Соединения успешно загружены из файла: " << fileName << "\n";
}
