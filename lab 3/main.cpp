#include <iostream>
#include <string>
#include <unordered_set>
#include <chrono>
#include <type_traits>
#include <limits>
#include <cctype>

#include "pipe.h"
#include "cs.h"

using namespace std;



void Helper()
{
	cout << "		Меню: " << endl;
	cout << " 1 - Добавить трубу" << endl;
	cout << " 2 - Добавить компрессорную станцию" << endl;
	cout << " 3 - Вывести объекты" << endl;
	cout << " 4 - Сохранение" << endl;
	cout << " 5 - Загрузить" << endl;
    cout << " 6 - Редактирование по фильтрам" << endl;
	cout << " 7 - Добавить соединение" << endl;
	cout << " 8 - Вывести нефтегазотранспортную сеть" << endl;
	cout << " 9 - Топологическая сортировка" << endl;
	cout << " 0 - Выход" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");
	Helper();

	int choice;
	while (true)
	{
		choice = getInput<int>("Команда ", 0, 10);
		system("cls");
		switch (choice)
		{
		case 1:
			addPipe();
			break;
		case 2:
			addCS();
			break;
		case 3:
			Print();
			break;
		case 4:
			save();
			break;
		case 5:
			load();
			break;
		case 6:
			CoolFilters();
            break;
		case 7:
			Print();
			addConnection();
			break;
		case 8:
			saveConnections();
			printGraph();
			break;
		case 9:
			saveConnectionsToFile();
			//loadConnectionsFromFile();
			break;
		case 0:
			cout << "Выход..." << endl;
			return 0;
		}
		cout << "Нажмите Enter...";
		cin.ignore(10000, '\n');
		cerr << endl;
		system("cls");
		Helper();
	}
	return 0;
}


