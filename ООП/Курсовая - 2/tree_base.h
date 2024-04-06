#ifndef __TREE_BASE__H
#define __TREE_BASE__H
#include <vector>
#include <string>

using namespace std;

//extern int successfull_tests_cnt; // глобальная переменная - количество успешно пройденных тестов

class tree_base {

	tree_base* p_head_object; // указатель на предка
	vector<tree_base*>subordinate_objects; // список потомков

	// mutable vector<tree_base*>subordinate_objects; // список потомков

	string s_object_name; // имя объекта
	int readiness = 0;

public:
	// конструктор
	tree_base(tree_base* p_head_object, const string s_object_name = "Base_object");
	//изменение имени объекта
	bool change_name(const string new_name);
	// вспомнить моё имя
	string get_my_name() const;
	// позвать моего предка
	tree_base* get_my_parent() const;
	// всех спалить
	void print() const;
	//string print(string filename_in) const;
	// позвать моего лююбимого потомка
	tree_base* get_my_fav_child(const string fav_child_name) const;
	// есть ли у меня уже потомок с именем new_name?
	bool is_new_name(const string new_name) const;
	// вывод дерева в глубину
	void dfs(const string otstup) const;
	// установить готовность
	void set_readiness(const int);
	// вывод дерева с готовностями в глубину
	void dfs_with_readiness(const string otstup) const;
	// возвращает указатель на чувака с текущей ветки с именем name
	tree_base* find_by_name_down(const string name);
	// возвращает указатель на чувака с именем name
	tree_base* find_by_name(const string name);

};

#endif
