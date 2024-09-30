#include "structure.h"

#include <iostream>
#include <conio.h>
int main()
{
	setlocale(LC_ALL, "ru");
	pipe p;
	compressor_station cs;
	while (true) {
		char choice;
		cout << "Меню\n\n";
		cout << "1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\n\nКоманда  ";
		cin >> choice;
		// Очистка оставшегося ввода после выбора        
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choice) {
		case '1':
			add_pipe(p);
			break;
		case '2':
			add_cs(cs);
			break;
		case '3':
			view(p, cs);
			break;
		case '4':
			//edit_pipe(p);
			break;
		case '5':
			//edit_cs(cs);
			break;
		case '6':
			//save_p_and_cs(p, cs);
			break;
		case '7':
			//download_p_and_cs(p, cs);
			break;
		case '0':
			exit(0);
			break;
		default:
			cout << "Неверный выбор. Попробуйте снова.\n";
			break;
		}
		cout << "\nГотово! Нажмите Enter...";
		cin.ignore(10000, '\n');
		system("cls");
	}

};
