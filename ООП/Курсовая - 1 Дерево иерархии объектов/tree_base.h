#ifndef __TREE_BASE__H
#define __TREE_BASE__H
#include <vector>
#include <string>

using namespace std;

extern int successfull_tests_cnt; // глобальная переменная - количество успешно пройденных тестов

class tree_base{
	
	tree_base * p_head_object; // указатель на предка
	vector<tree_base*>subordinate_objects; // список потомков
	string s_object_name; // имя объекта
	
public:
	// конструктор
	tree_base(tree_base * p_head_object, string s_object_name = "Base_object");
	//изменение имени объекта
	bool change_name(string new_name); // сменить моё имя
	string get_my_name(); // вспомнить моё имя
	tree_base * get_my_parent(); // позвать моего предка
	void print(); // всех спалить
	string print(string filename_in);
	tree_base * get_my_fav_child(string fav_child_name); // позвать моего лююбимого потомка
	bool is_new_name(string new_name); // есть ли у меня уже потомок с именем new_name?
	
};

#endif
