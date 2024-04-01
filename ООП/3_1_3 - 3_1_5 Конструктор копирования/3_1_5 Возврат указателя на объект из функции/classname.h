#ifndef __CLASSNAME__H
#define __CLASSNAME__H
#include <vector>

class classname {
	int* a; // ��������� �� ������
	int len_a = 0; // ������ �������
public:
	// ����������� �� ���������
	classname();
	// ������������������� �����������
	classname(int n);
	// ����������� �����������
	classname(const classname& obj);
	// ����������� ����������
	~classname();
	// �������� �������
	void create_a();
	// ���� ������� 
	void fill_a();
	// ����� ��������� �������
	int sum_a();
	// ����� 1
	void half_sum();
	// ����� 2
	void half_product();
	// ����� �������
	void print();
	// ���������� ���� ������ �������� �������
	int* get_a();
	// ����������� ���� ������ �������� ������� ���������� ������
	void set_a(int* array);
};

#endif
