#pragma once
#include <string>
using namespace std;

struct pipe {
	string name_pipe = "gleb"; //Километровая отметка(название)
	unsigned int length = 0; //Длина трубы
	unsigned int diameter = 0; //Диаметр трубы
	bool UnderRepair;
};
struct compressor_station {
	string name_cs = "gleb"; //Название КС
	unsigned int quantity = 0; // Кол-во цехов
	unsigned int quantity_cs = 0; // Кол-во цехов в работе
	unsigned int effective_cs = 0; //Эффективность
};

void add_pipe(pipe& p);
void add_cs(compressor_station& cs);
void view(const pipe& p, const compressor_station& cs);
void edit_pipe(pipe& p);
void edit_cs(compressor_station& cs);
void save_p_and_cs(const pipe& p, const compressor_station& cs);
void download_p_and_cs(pipe& p, compressor_station& cs);