#include "application.h"
#include "node_2.h"
#include "node_3.h"
#include "node_4.h"
#include "node_5.h"
#include "node_6.h"
#include <iostream>

//application::application(tree_base * p_head_object, const string s_object_name): tree_base(p_head_object,s_object_name){};

int application::exec_app() {
	cout << "Object tree";
	this->dfs();
	string name; // имя вершины
	int num; // готовность
	tree_base* object;
	while (cin >> name) {
		cin >> num;
		object = this->find_by_name(name);
		object->set_readiness(num);
	}
	cout << "\nThe tree of objects and their readiness";
	this->dfs_with_readiness();

	return 0;
}

void application::build_tree_objects() {
	string parent, child; // предок, потомок
	// узнаём имя корня
	cin >> parent;
	this->change_name(parent);

	int class_number; // номер класса очередной вершины [2..6]
	tree_base* node; // очередная вершина
	while (true) {
		cin >> parent;
		if (parent == "endtree") // конец дерева
			break;
		cin >> child >> class_number;

		// если нет вершин с именем child
		if (this->find_by_name(child) == NULL) {
			// и есть родитель с именем parent
			if (this->find_by_name(parent) != NULL) {
				// то создаём новую вершину указанного класса
				if (class_number == 2) {
					node = new node_2(this->find_by_name(parent), child);
				}
				else if (class_number == 3) {
					node = new node_3(this->find_by_name(parent), child);
				}
				else if (class_number == 4) {
					node = new node_4(this->find_by_name(parent), child);
				}
				else if (class_number == 5) {
					node = new node_5(this->find_by_name(parent), child);
				}
				else if (class_number == 6) {
					node = new node_6(this->find_by_name(parent), child);
				}
			}

		}

	}
}
