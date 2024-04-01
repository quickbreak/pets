#ifndef __CLASSNAME__H
#define __CLASSNAME__H
#include <vector>

class classname {
	std::vector<int>a; // ������
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
	int half_sum(); 
	// ����� 2
	int half_product();
	// ����� �������
	void print(); 
};

#endif
