#include "application.h"
#include "tree_base.h"
#include "node.h"
#include <iostream>
#include <fstream>

application::application(tree_base * p_head_object, string s_object_name): tree_base(p_head_object,s_object_name){};

void application::build_tree_objects (){
	string parent, child;
	tree_base* p_head_object = this;
	ifstream file("test7_in.txt");
	file >> parent; // узнаём праотца
	this -> change_name(parent);
	node* last_son = NULL;
	while(true){
		file >> parent >> child;
		if (parent == child) // конец дерева
			break;
		
		// ТОЛЬКО если родитель - крайний потомок текущего родителя
		// то он во главе нового колена
		if (parent != p_head_object->get_my_name()){
			if (last_son == NULL || parent == last_son->get_my_name()){
				p_head_object = last_son;
				last_son = new node(p_head_object, child);
			}
		}
		// можем назвать так (child) нового ребёнка,
		// если нет других детей с таким именем
		else{
			if (p_head_object->is_new_name(child)){
				last_son = new node(p_head_object, child);
			}
		}
			
	}
	file.close();
}
int application::exec_app(){
	// this -> print();
	string got = this->print(0);
	cout << got;
	return 0;
}