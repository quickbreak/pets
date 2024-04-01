#ifndef __CLASSNAME__H
#define __CLASSNAME__H
#include <vector>

class classname {
	std::vector<int> a;
	int len_a;
public:
	classname();
	classname(int n);
	classname(const classname& obj);
	~classname();
	void fill_a();
	int sum_a();
	int half_sum();
	int half_product();
};

#endif
