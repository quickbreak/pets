#ifndef __TREE_BASE__H
#define __TREE_BASE__H
#include<vector>
#include<string>
#include<iostream>
#include<queue>


class tree_base;

// для получения указателя на метод сигнала объекта
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(& signal_f)
// для получения указателя на метод обработчика объекта
#define HANDLER_D(handler_f)(TYPE_HANDLER)(& handler_f)

// тип указатель на метод сигнала объекта
typedef void (tree_base::* TYPE_SIGNAL)(std::string&);
// тип указатель на метод обработчика объекта
typedef void (tree_base::* TYPE_HANDLER)(std::string);


// using namespace std;


class tree_base {

	struct type_connect // Структура, хранящая информациюю о связи (одной)
	{
	public:
		TYPE_SIGNAL signal_pointer; // Указатель на метод сигнала
		tree_base* target_object_pointer; // Указатель на целевой объект
		TYPE_HANDLER handler_pointer; // Указатель на метод обработчика

		/*bool operator == (const tree_base::type_connect& connect_2)
		{
			return 
				this->signal_pointer == connect_2.signal_pointer &&
				this->handler_pointer == connect_2.handler_pointer &&
				this->target_object_pointer == connect_2.target_object_pointer;
		}*/
	};

	std::vector<type_connect*>connects; // список установленных связей


	tree_base* p_head_object; // указатель на предка
	std::vector<tree_base*>subordinate_objects; // список потомков

	// mutable vector<tree_base*>subordinate_objects; // список потомков

	std::string s_object_name; // имя объекта
	int readiness = 0; // готовность объекта

public:
	// конструктор
	tree_base(tree_base* p_head_object, const std::string s_object_name = "Base_object");
	// изменяет имя объекта на new_name
	bool change_my_name(const std::string new_name);
	// возвращает имя объекта
	const std::string get_my_name() const;
	// возвращает указатель на головной объект (на родителя)
	tree_base* get_my_parent() const;
	// возвращает указатель на непосредственного потомка по имени childname.
	// Гарантируется, что имена непосредственных потомков уникальны
	tree_base* get_my_child(const std::string child_name);
	// выводит дерево в глубину
	void print_tree() const;
	/*// устанавливает готовность 
	void set_readiness(const int);*/
	// выводит дерево с готовностями в глубину
	void print_tree_with_readiness() const;
	// возвращает указатель на объект поддерева с именем name (первый в порядке рекурсивного обхода)
	tree_base* find_by_name_down(const std::string name);
	// возвращает указатель на объект дерева с именем name (первый в порядке рекурсивного обхода)
	tree_base* find_by_name(const std::string name);
	// изменяет головного объекта на newparent
	bool change_my_parent(tree_base* newparent);
	// удаляет потомка текущего объекта по имени childname
	void remove_my_child(const std::string childname);
	// возвращает указатель на объект дерева по "координате" path
	tree_base* get_object(const std::string path);

	// метод установки связи
	void set_connect(TYPE_SIGNAL signal_pointer, tree_base* target_object_pointer, TYPE_HANDLER handler_pointer);
	// метод выдачи сигнала и обработки соответствующих обработчиков
	void emit_signal(TYPE_SIGNAL p_signal, std::string& s_command);
	// возвращает абсолютный путь (от корня) до текущего объекта
	std::string get_my_absolute_path() const;
	// возвращает значение поля готовность текущего объекта
	int get_my_readiness() const;
	// устанавливает значение готовности текущего объекта
	void set_my_readiness(const int);
	// метод разрыва связи
	void remove_connect(TYPE_SIGNAL signal_pointer, tree_base* target_object_pointer, TYPE_HANDLER handler_pointer);
	// ну вы пон
	std::vector<tree_base*>get_my_subordinate_objects() const;
	virtual void signal(std::string&) const = 0;
	virtual void handler(const std::string) const = 0;
	// возвращает указатель на сигнал-метод того типа, что и у объекта
	virtual TYPE_SIGNAL get_signal_pointer() const = 0;
	// возвращает указатель на хэндлер-метод того типа, что и у объекта
	virtual TYPE_HANDLER get_handler_pointer() const = 0;
};

#endif
