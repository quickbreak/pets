#ifndef __TREE_BASE__H
#define __TREE_BASE__H
#include <vector>
#include <string>

using namespace std;

//extern int successful_tests_cnt; // глобальная переменная - количество успешно пройденных тестов

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
	const string get_my_name() const;
	// позвать моего предка
	const tree_base* get_my_parent() const;
	//string print(string filename_in) const;
	// позвать моего любимого потомка
	tree_base* get_my_fav_child(const string fav_child_name);
	// есть ли у меня уже потомок с именем new_name?
	bool is_new_name(const string new_name);
	// вывод дерева в глубину
	void dfs() const;
	// установить готовность
	void set_readiness(const int);
	// вывод дерева с готовностями в глубину
	void dfs_with_readiness() const;
	// возвращает указатель на чувака с текущей ветки с именем name
	tree_base* find_by_name_down(const string name);
	// возвращает указатель на чувака с именем name
	tree_base* find_by_name(const string name);

};

#endif
