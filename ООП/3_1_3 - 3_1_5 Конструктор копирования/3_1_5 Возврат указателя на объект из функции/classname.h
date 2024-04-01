#ifndef __CLASSNAME__H
#define __CLASSNAME__H
#include <vector>

class classname {
	int* a; // указатель на массив
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
	void half_sum();
	// метод 2
	void half_product();
	// вывод массива
	void print();
	// возвращает поле массив текущего объекта
	int* get_a();
	// присваивает полю массив текущего объекта переданный массив
	void set_a(int* array);
};

#endif
