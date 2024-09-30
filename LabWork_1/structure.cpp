#include "structure.h"
#include <iostream>
#include <fstream>
#include <conio.h>

int readNumberWithGetLine() {
	int number;
	while (true) {
		cin >> number;
		if (cin.good() && number >= 0)
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
			cout << "Кол-во рабочих цехов не может быть больше кол-ва цехов!!!";
		}
	}	
	cout << "Введите эффективность:  ";
	cs.effective_cs = readNumberWithGetLine();

}

void view(const pipe& p, const compressor_station& cs)
{
	system("cls");
	cout << "-------------------------         ТРУБА         -------------------------" << endl;
	cout << "Название трубы: ";
	if (p.name_pipe == "") {
		cout << "Данные отсутствуют" << endl;
	}
	else {
		cout << p.name_pipe << endl;
	}
	cout << "Длина трубы: " << (p.length == 0 ? "Данные отсутствуют" : to_string(p.length)) << endl; //Тернарный оператор имеет вид condition ? value_if_true : value_if_false.
	cout << "Диаметр трубы: " << (p.diameter == 0 ? "Данные отсутствуют" : to_string(p.diameter)) << endl;
	if (p.UnderRepair) {
		cout << "Статус: ТРЕБУЕТСЯ РЕМОНТ" << endl;
	}
	else {
		cout << "Статус: ПОЙДЕТ" << endl;
	}
	cout << endl << "------------------------- КОМПРЕССОРНАЯ СТАНЦИЯ -------------------------" << endl;
	cout << "Название КС: ";
	if (cs.name_cs == "") {
		cout << "Данные отсутствуют" << endl;
	}
	else {
		cout << cs.name_cs << endl;
	}
	cout << "Количество цехов:  " << (cs.quantity == 0 ? "Нет цехов" : to_string(cs.quantity)) << endl;
	cout << "Количество цехов в работе:  " << (cs.quantity_cs == 0 ? "Нет рабочих цехов" : to_string(cs.quantity_cs)) << endl;
	cout << "Эффективность:  " << (cs.effective_cs == 0 ? "Данные отсутствуют" : to_string(cs.effective_cs)) << endl;

}

