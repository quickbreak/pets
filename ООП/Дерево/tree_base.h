#ifndef __TREE_BASE__H
#define __TREE_BASE__H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class tree_base {

public:
	tree_base* p_head_object; // указатель на предка
	vector<tree_base*>subordinate_objects; // список потомков
	string s_object_name; // имя объекта
	// конструктор
	tree_base(tree_base* p_head_object, string s_object_name = "Base_object"); 
	// сменить моё имя
	bool change_my_name(string new_name); 
	// вспомнить моё имя
	string get_my_name(); 
	// позвать моего предка
	tree_base* get_my_parent();
	// напечатать дерево
	void print(); 
	// позвать моего лююбимого потомка
	tree_base* get_my_fav_child(string fav_child_name);

};

#endif
