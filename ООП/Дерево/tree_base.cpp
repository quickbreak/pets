#include "tree_base.h"
#include <iostream>
#include <fstream>


tree_base::tree_base(tree_base * p_head_object, string s_object_name){
	this -> p_head_object = p_head_object; // указатель на предка
	this -> s_object_name = s_object_name; // имя потомка
	if (p_head_object != NULL){
		p_head_object -> subordinate_objects.push_back(this); // добавление предку нового потомка		
	}
}

void tree_base::print(){
	cout << this -> s_object_name; // назовём праотца
	tree_base* parent = this;
	int n;
	while(parent->subordinate_objects.size()>0){ // перечисляем непосредственных потомков текущего предка
		cout << '\n';
		cout << parent -> s_object_name; // называем предка
		n = parent->subordinate_objects.size();
		for(int i = 0; i < n; ++i){
			cout << "  " << parent->
				subordinate_objects[i]->
				s_object_name; // и его непосредственных потомков
		}
		// переходим к следующему колену
		parent = parent->subordinate_objects[n-1];
		
	}
}

string tree_base::print(int i) {

	string answer = "";
	//cout << this->s_object_name; // назовём праотца
	answer += this->s_object_name;
	tree_base* parent = this;
	int n;
	while (parent->subordinate_objects.size() > 0) { // перечисляем непосредственных потомков текущего предка
		//cout << '\n';
		answer += "\n";
		//cout << parent->s_object_name; // называем предка
		answer += parent->s_object_name;
		n = parent->subordinate_objects.size();
		for (int i = 0; i < n; ++i) {
			//cout << "  " << parent->subordinate_objects[i]->s_object_name; // и его непосредственных потомков
			answer += "  " + parent->subordinate_objects[i]->s_object_name;
		}
		// переходим к следующему колену
		parent = parent->subordinate_objects[n - 1];

	}

	ifstream file("test7_out.txt");
	string had_to_get;
	string s = "";
	getline(file, s, '\n');
	while (s!="eof") {
		had_to_get += s + "\n";
		getline(file, s, '\n');
	}
	file.close();
	cout << had_to_get;
	return (answer+"\n" == had_to_get) ? "Test Passed!" : "Test Failed.";
}

string tree_base::get_my_name(){
	return this->s_object_name;
}

tree_base * tree_base::get_my_parent(){
	return this->p_head_object;
}

tree_base * tree_base::get_my_fav_child(string fav_child_name){
	// любимый у меня может быть только непосредственнный потомок
	for(auto child : this->subordinate_objects){
		if(child->s_object_name == fav_child_name){
			return child;
		}
	}
	return NULL;
}

bool tree_base::is_new_name(string new_name){
	tree_base* me = this;
	// есть ли у меня уже потомок с именем new_name?
	for (auto sibling : me->subordinate_objects) {
		if (sibling->s_object_name == new_name) {
			return false;
		}
	}
	return true;
	
}

bool tree_base::change_name(string new_name){
	tree_base* parent = this->p_head_object;
	// хочу сменить имя, но будет не прикольно,
	// если у моих siblings есть такое имя:
	// нас же родители путать будут...
	if (parent == NULL || parent->is_new_name(new_name)){
		this->s_object_name = new_name;
		return true;
	}
	else return false;
}