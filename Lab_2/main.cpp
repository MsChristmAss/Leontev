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
	cout << "Меню: " << endl;
	cout << "1 - Добавить трубу" << endl;
	cout << "2 - Добавить компрессорную станцию" << endl;
	cout << "3 - Вывести объекты" << endl;
	cout << "4 - Удаление" << endl;
	cout << "5 - Редактирование" << endl;
	cout << "6 - Сохранение" << endl;
	cout << "7 - Загрузить" << endl;
	cout << "8 - Поиск по фильтрам" << endl;
	cout << "9 - Пакетное редактирование/удаление"<< endl;
	cout << "0 - Выход" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");
	Helper();

	int choice;
	while (true)
	{
		choice = getInput<int>("Команда ", 0, 9);
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
			remove();
			break;
		case 5:
			edit();
			break;
		case 6:
			save(getInput<int>("1 - труба\n2 - кс\n3 - всё\n\nВыбор ",1,3));
			break;
		case 7:
			load();
			break;
		case 8:
			filterSearch();
			break;
		case 9:
			batchEditOrRemove();
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