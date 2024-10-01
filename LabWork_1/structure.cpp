#include "structure.h"
#include <iostream>
#include <fstream>
#include <conio.h>

int readNumberWithGetLine() {
	int number;
	while (true) {
		cin >> number;
		if (cin.good() && number > 0)
		{
			return number;
		}
		else {
			cout << "Ошибка ввода, введите ещё раз:  ";
		}
		cin.clear(); // Сбрасываем состояние ошибки
		cin.ignore(10000, '\n');
	}
}

void add_pipe(pipe& p)
{
	system("cls");
	//https://metanit.com/cpp/tutorial/5.8.php
	cout << "-------------------------         ТРУБА         -------------------------" << endl;
	cout << "Введите название трубы:  ";
	getline(cin, p.name_pipe);
	cout << "Введите длину трубы:  ";
	p.length = readNumberWithGetLine();
	cout << "Введите диаметр трубы:  ";
	p.diameter = readNumberWithGetLine();
	cout << "Трубе нужен ремонт? (y/n)  ";
	char B;
	while (true) {
		cin >> B;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (B == 'y' || B == 'n') {
			if (B == 'y') {
				p.UnderRepair = true;
			}
			else {
				p.UnderRepair = false;
			}
			break;
		}
		else {
			cout << "Ошибка ввода, введите ещё раз:  ";
		}
	}
}

void add_cs(compressor_station& cs)
{
	system("cls");
	cout << endl << "------------------------- КОМПРЕССОРНАЯ СТАНЦИЯ -------------------------" << endl;
	cout << "Введите название КС:  ";
	getline(cin, cs.name_cs);
	cout << "Введите количество цехов:  ";
	cs.quantity = readNumberWithGetLine();
	cout << "Введите количество рабочих цехов:  ";
	while (true) {
		cs.quantity_cs = readNumberWithGetLine();
		if (cs.quantity_cs <= cs.quantity) {
			break;
		}
		else {
			cout << "Кол-во рабочих цехов не может быть больше кол-ва цехов:  ";
		}
	}
	cout << "Введите эффективность:  ";
	cs.effective_cs = readNumberWithGetLine();

}

void view(const pipe& p, const compressor_station& cs)
{
	system("cls");
	if (p.name_pipe == "gleb") {
		cout << "-------------------------         ТРУБА         -------------------------" << endl;
		cout << "Данные отсутствуют" << endl;
	}
	else {
		cout << "-------------------------         ТРУБА         -------------------------" << endl;
		cout << "Название трубы: ";
		cout << p.name_pipe << endl;
		cout << "Длина трубы: " << (p.length == 0 ? "Данные отсутствуют" : to_string(p.length)) << endl; //Тернарный оператор имеет вид condition ? value_if_true : value_if_false.
		cout << "Диаметр трубы: " << (p.diameter == 0 ? "Данные отсутствуют" : to_string(p.diameter)) << endl;
		if (p.UnderRepair) {
			cout << "Статус: ТРЕБУЕТСЯ РЕМОНТ" << endl;
		}
		else {
			cout << "Статус: ПОЙДЕТ" << endl;
		}
	}


	if (cs.name_cs == "gleb") {
		cout << endl << "------------------------- КОМПРЕССОРНАЯ СТАНЦИЯ -------------------------" << endl;
		cout << "Данные отсутствуют" << endl;
	}
	else {
		cout << endl << "------------------------- КОМПРЕССОРНАЯ СТАНЦИЯ -------------------------" << endl;
		cout << "Название КС: ";
		cout << cs.name_cs << endl;
		cout << "Количество цехов:  " << (cs.quantity == 0 ? "Нет цехов" : to_string(cs.quantity)) << endl;
		cout << "Количество цехов в работе:  " << (cs.quantity_cs == 0 ? "Нет рабочих цехов" : to_string(cs.quantity_cs)) << endl;
		cout << "Эффективность:  " << (cs.effective_cs == 0 ? "Данные отсутствуют" : to_string(cs.effective_cs)) << endl;
	}
}

void edit_pipe(pipe& p)
{
	system("cls");
	if (p.name_pipe == "gleb") {
		cout << "Нельзя редактировать то, чего нет)";
	}
	else {
		cout << "------------------------- РЕДАКТИРОВАНИЕ ТРУБЫ -------------------------" << endl;
		cout << "Труба в ремонте? (y/n)  ";
		char B;
		cin >> B;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (B == 'y') {
			p.UnderRepair = true;
		}
		else {
			p.UnderRepair = false;
		}
	}
}

void edit_cs(compressor_station& cs)
{
	system("cls");
	if (cs.name_cs == "gleb") {
		cout << "Нельзя редактировать то, чего нет)";
	}
	else {
		cout << "------------------------- КОМПРЕССОРНАЯ СТАНЦИЯ -------------------------" << endl;
		cout << "Количество рабочих цехов:  ";
		while (true) {
			cs.quantity_cs = readNumberWithGetLine();
			if (cs.quantity_cs <= cs.quantity) {
				break;
			}
			else {
				cout << "Кол-во рабочих цехов не может быть больше кол-ва цехов!!!";
			}
		}
	}
	
}


void save_p_and_cs(const pipe& p, const compressor_station& cs)
{
	system("cls");
	ofstream file("lab1.txt");
	if (file.is_open()) {
		{
			system("cls");
			if (p.name_pipe == "gleb") {
				file << "-------------------------         ТРУБА         -------------------------" << endl;
				file << "Данные отсутствуют" << endl;
			}
			else {
				file << "-------------------------         ТРУБА         -------------------------" << endl;
				file << "Название трубы: ";
				file << p.name_pipe << endl;
				file << "Длина трубы: " << (p.length == 0 ? "Данные отсутствуют" : to_string(p.length)) << endl; //Тернарный оператор имеет вид condition ? value_if_true : value_if_false.
				file << "Диаметр трубы: " << (p.diameter == 0 ? "Данные отсутствуют" : to_string(p.diameter)) << endl;
				if (p.UnderRepair) {
					file << "Статус: ТРЕБУЕТСЯ РЕМОНТ" << endl;
				}
				else {
					file << "Статус: ПОЙДЕТ" << endl;
				}
			}
			if (cs.name_cs == "gleb") {
				file << endl << "------------------------- КОМПРЕССОРНАЯ СТАНЦИЯ -------------------------" << endl;
				file << "Данные отсутствуют" << endl;
			}
			else {
				file << endl << "------------------------- КОМПРЕССОРНАЯ СТАНЦИЯ -------------------------" << endl;
				file << "Название КС: ";
				file << cs.name_cs << endl;
				file << "Количество цехов:  " << (cs.quantity == 0 ? "Нет цехов" : to_string(cs.quantity)) << endl;
				file << "Количество цехов в работе:  " << (cs.quantity_cs == 0 ? "Нет рабочих цехов" : to_string(cs.quantity_cs)) << endl;
				file << "Эффективность:  " << (cs.effective_cs == 0 ? "Данные отсутствуют" : to_string(cs.effective_cs)) << endl;
			}
		}


	}
}

void download_p_and_cs(pipe& p, compressor_station& cs)
{
	system("cls");
	ifstream file("lab1.txt");
	if (!file) {
		cerr << "Ошибка открытия файла." << endl;
		return;
	}
	if (file.peek() == EOF) {//https://www.studyplan.dev/pro-cpp/input-streams/q/use-of-peek-method
		cout << "Файл пустой!" << endl;
		return;
	}
	string str;
	getline(file, str);
	if (str == "-------------------------         ТРУБА         -------------------------") {
		getline(file, str);
		if (str == "Данные отсутствуют") {
			p.name_pipe = "gleb";
		}
		else {
			p.name_pipe = str.substr(16);
			try {
				getline(file, str);
				p.length = stoi(str.substr(13));
			}
			catch (const invalid_argument& e) {
				cerr << "Ошибка: Длина не является числом." << endl;
			}
			try {
				getline(file, str);
				p.diameter = stoi(str.substr(15));
			}
			catch (const invalid_argument& e) {
				cerr << "Ошибка: Диаметр не является числом." << endl;
			}
			getline(file, str);
			if (str == "Статус: ТРЕБУЕТСЯ РЕМОНТ") {
				p.UnderRepair = true;
			}
			else {
				p.UnderRepair = false;
			}
		}

		getline(file, str);
		getline(file, str);
		getline(file, str);
		if (str == "Данные отсутствуют") {
			cs.name_cs = "gleb";
		}
		else {
			cs.name_cs = str.substr(13);
			try {
				getline(file, str);
				cs.quantity = stoi(str.substr(19));
			}
			catch (const invalid_argument& e) {
				cerr << "Ошибка: Кол-во цехов не является числом." << endl;
			}

			try {
				getline(file, str);
				cs.quantity_cs = stoi(str.substr(28));
			}
			catch (const invalid_argument& e) {
				cerr << "Ошибка: Кол-во рабочих цехов не является числом." << endl;
			}


			try {
				getline(file, str);
				cs.effective_cs = stoi(str.substr(16));
			}
			catch (const invalid_argument& e) {
				cerr << "Ошибка: Эффективность не является числом." << endl;
			}
		}

	}
	else {
		getline(file, str);
		getline(file, str);
		cs.name_cs = str.substr(13);
		try {
			getline(file, str);
			cs.quantity_cs = stoi(str.substr(19));
		}
		catch (const invalid_argument& e) {
			cerr << "Ошибка: Кол-во цехов не является числом." << endl;
		}

		try {
			getline(file, str);
			cs.quantity = stoi(str.substr(28));
		}
		catch (const invalid_argument& e) {
			cerr << "Ошибка: Кол-во рабочих цехов не является числом." << endl;
		}

		try {
			getline(file, str);
			cs.effective_cs = stoi(str.substr(16));
		}
		catch (const invalid_argument& e) {
			cerr << "Ошибка: Эффективность не является числом." << endl;
		}
		getline(file, str);
		getline(file, str);
		getline(file, str);
		p.name_pipe = str.substr(16);
		try {
			getline(file, str);
			p.length = stoi(str.substr(13));
		}
		catch (const invalid_argument& e) {
			cerr << "Ошибка: Длина не является числом." << endl;
		}
		try {
			getline(file, str);
			p.diameter = stoi(str.substr(15));
		}
		catch (const invalid_argument& e) {
			cerr << "Ошибка: Диаметр не является числом." << endl;
		}
		getline(file, str);
		if (str == "Статус: ТРЕБУЕТСЯ РЕМОНТ") {
			p.UnderRepair = true;
		}
		else {
			p.UnderRepair = false;
		}
	}
	file.close();

}
