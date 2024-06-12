#include "class_info.h"
#include<fstream>


void class_info::print_message(const std::string message)
{
	// std::cout << message;
	std::ofstream fout("output.txt", std::ios::app); // файл открывается на дозапись
	fout << message;
	fout.close();
}
