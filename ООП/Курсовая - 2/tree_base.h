#ifndef __TREE_BASE__H
#define __TREE_BASE__H
#include <vector>
#include <string>

using namespace std;

//extern int successfull_tests_cnt; // глобальная переменная - количество успешно пройденных тестов

class tree_base{
	
	tree_base * p_head_object; // указатель на предка
	vector<tree_base*>subordinate_objects; // список потомков
	string s_object_name; // имя объекта
	int readiness = 0;
	
public:
	// конструктор
	tree_base(tree_base * p_head_object, string s_object_name = "Base_object");
	//изменение имени объекта
	bool change_name(string new_name); 
	// вспомнить моё имя
	string get_my_name(); 
	// позвать моего предка
	tree_base * get_my_parent(); 
	// всех спалить
	void print(); 
	//string print(string filename_in);
	// позвать моего лююбимого потомка
	tree_base * get_my_fav_child(string fav_child_name); 
	// есть ли у меня уже потомок с именем new_name?
	bool is_new_name(string new_name); 
	// вывод дерева в глубину
	void dfs(string otstup); 
	// установить готовность
	void set_readiness(int num);
	// вывод дерева с готовностями в глубину
	void dfs_with_readiness(string otstup);
	// возвращает указатель на чувака с текущей ветки с именем name
	tree_base* find_by_name_down(string name);
	// возвращает указатель на чувака с именем name
	tree_base* find_by_name(string name);
	
};

#endif
