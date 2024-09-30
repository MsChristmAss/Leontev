#pragma once
#include <string>
using namespace std;

struct pipe {
	string name_pipe; //Километровая отметка(название)
	unsigned int length; //Длина трубы
	unsigned int diameter; //Диаметр трубы
	bool UnderRepair;
};
struct compressor_station {
	string name_cs; //Название КС
	unsigned int quantity; // Кол-во цехов
	unsigned int quantity_cs; // Кол-во цехов в работе
	int effective_cs; //Эффективность
};

void add_pipe(pipe& p);
void add_cs(compressor_station& cs);
void view(const pipe& p, const compressor_station& cs);
void edit_pipe(pipe& p);
void edit_cs(compressor_station& cs);
void save_p_and_cs(const pipe& p, const compressor_station& cs);
void download_p_and_cs(pipe& p, compressor_station& cs);