#ifndef __TEST__H
#define __TEST__H

class Test {
	int hidden;
	void hidden_change();
public:
	int open;
	Test(int i_data);
	//~Test();
	void print();
	void call_hidden_change();
	void open_change();

};

#endif
