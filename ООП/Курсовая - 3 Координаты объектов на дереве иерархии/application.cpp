#include "application.h"
#include "node_2.h"
#include "node_3.h"
#include "node_4.h"
#include "node_5.h"
#include "node_6.h"
#include <iostream>

//application::application(tree_base * p_head_object, const string s_object_name): tree_base(p_head_object,s_object_name){};

int application::exec_app() {
	string command = "";
	tree_base* currentobjptr = this;
	while (true) {
		cin >> command;
		if (command == "END") {
			cout << "\nCurrent object hierarchy tree";
			this->print_tree();
			break;
		}
		if (command == "SET") {
			string path; cin >> path;
			currentobjptr = currentobjptr->get_object(path);
			if (currentobjptr != NULL)
				cout << "\nObject is set: " << currentobjptr->get_my_name();
			else
				cout << "\nThe object was not found at the specified coordinate: " << path;
		}
		else if (command == "FIND") {
			string path; cin >> path;
			tree_base* objptr = currentobjptr->get_object(path);
			cout << '\n' << path << "     ";
			if (objptr != NULL)
				cout << "Object name: " << objptr->get_my_name();
			else
				cout << "Object is not found";
		}
		else if (command == "MOVE") {	
			string path; cin >> path;
			tree_base* newparentobjptr = currentobjptr->get_object(path);

			// родительский объект вообще не найден
			if (newparentobjptr == NULL) {
				cout << '\n' << path << "     " << "Head object is not found";
				continue;
			}
			if (currentobjptr->change_my_parent(newparentobjptr)) {
				cout << "\nNew head object: " << (currentobjptr->get_my_parent()->get_my_name());
				continue;
			}
			else {
				// нельзя прикрепиться к newparent, потому что
				// у него есть НЕПОСРЕДСТВЕННЫЙ потомок с таким же именем, как у текущего 
				if (newparentobjptr->get_my_child(currentobjptr->get_my_name())) {
					cout << '\n' << path << "     " << "Dubbing the names of subordinate objects";
					continue;
				}
				// нельзя, чтобы новым родителем был потомок текущего
				if (currentobjptr->find_by_name_down(newparentobjptr->get_my_name()) != NULL) {
					cout << '\n' << path << "     " << "Redefining the head object failed";
					continue;
				}
				// else
				cout << '\n' << path << "     " << "Redefining the head object failed";
			}
		}
		else if (command == "DELETE") {
			string childname; cin >> childname;

			// проверяем, удастся ли удалить
			tree_base* removeptr = currentobjptr->get_my_child(childname);
			// если нашли объект с таким именем, значит удалим
			if (removeptr != NULL) {
				// удаляем
				currentobjptr->remove_my_child(childname);
				// выводим сообщение об успехе
				const tree_base* objptr = removeptr;
				string absolutepath = "";
				while (objptr->get_my_parent() != NULL) {
					absolutepath = "/" + objptr->get_my_name() + absolutepath;
					objptr = objptr->get_my_parent();
				}
				cout << "\nThe object " << absolutepath << " has been deleted";
			}
		}

	}

	return 0;
}

void application::build_tree_objects() {
	string path, childname; // путь, имя нового объекта
	// узнаём имя корня
	cin >> childname;
	this->change_my_name(childname);

	int class_number; // номер класса очередной вершины [2..6]
	tree_base* node; // очередная вершина
	while (true) {
		cin >> path;
		if (path == "endtree") // конец дерева
			break;
		cin >> childname >> class_number;

		
		tree_base* parent = this->get_object(path); // ищем родителя
		if (parent == NULL) { // если не нашли родителя, дерево дальше не собирается, гг вп
			cout << "Object tree";
			this->print_tree();
			cout << "\nThe head object " << path << " is not found";
			exit(1);
		}

		// проверяем, нет ли уже у родителя потомка с нашим именем
		tree_base* found = parent->get_my_child(childname); 
		if (!found) { // если наше имя уникально
			// то создаём новую вершину указанного класса
			if (class_number == 2) {
				node = new node_2(parent, childname);
			}
			else if (class_number == 3) {
				node = new node_3(parent, childname);
			}
			else if (class_number == 4) {
				node = new node_4(parent, childname);
			}
			else if (class_number == 5) {
				node = new node_5(parent, childname);
			}
			else if (class_number == 6) {
				node = new node_6(parent, childname);
			}
		}
		else {
			cout << path << "     " << "Dubbing the names of subordinate objects\n";
		}
	}

	cout << "Object tree";
	this->print_tree();
}
