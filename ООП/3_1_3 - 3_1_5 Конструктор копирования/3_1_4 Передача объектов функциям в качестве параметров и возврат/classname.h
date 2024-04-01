#ifndef __CLASSNAME__H
#define __CLASSNAME__H
#include <vector>

class classname {
	std::vector<int>a; // массив
	int len_a = 0; // размер массива
public:
	// конструктор по умолчанию
	classname(); 
	// параметризированный конструктор
	classname(int n); 
	// конструктор копирования
	classname(const classname& obj); 
	// стандартный деструктор
	~classname(); 
	// создание массива
	void create_a(); 
	// ввод массива 
	void fill_a();
	// сумма элементов массива
	int sum_a(); 
	// метод 1
	int half_sum(); 
	// метод 2
	int half_product();
	// вывод массива
	void print(); 
};

#endif
