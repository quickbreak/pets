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
	int readiness = 0; // готовность объекта

public:
	// конструктор
	tree_base(tree_base* p_head_object, const string s_object_name = "Base_object");
	// изменяет имя объекта на new_name
	bool change_my_name(const string new_name);
	// возвращает имя объекта
	const string get_my_name() const;
	// возвращает указатель на головной объект (на родителя)
	tree_base* get_my_parent() const;
	// возвращает указатель на непосредственного потомка по имени childname.
	// Гарантируется, что имена непосредственных потомков уникальны
	tree_base* get_my_child(const string child_name);
	// уникально ли имя new_name? (на всём дереве)
	bool is_new_name(const string new_name);
	// выводит дерево в глубину
	void print_tree() const;
	// устанавливает готовность 
	void set_readiness(const int);
	// выводит дерево с готовностями в глубину
	void print_tree_with_readiness() const;
	// возвращает указатель на объект поддерева с именем name (первый в порядке рекурсивного обхода)
	tree_base* find_by_name_down(const string name);
	// возвращает указатель на объект дерева с именем name (первый в порядке рекурсивного обхода)
	tree_base* find_by_name(const string name);

	// изменяет головного объекта на newparent
	bool change_my_parent(tree_base* newparent);
	// удаляет потомка текущего объекта по имени childname
	void remove_my_child(const string childname);
	// возвращает указатель на объект дерева по "координате" path
	tree_base* get_object(const string path);

};

#endif
